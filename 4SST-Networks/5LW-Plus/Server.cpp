#include "Server.hpp"

using second_t = std::chrono::duration<double, std::ratio<1>>;
void* get_in_addr(sockaddr* sa);

// Server side
Server::Server(fd binded, ServerOptions options) : c(options.cl)
{
    if (binded < 0)
        throw new std::runtime_error("Invalid socket fd");

    activeClient = std::list<std::string>();
    socketFd = binded;
    noReply = options.noReply;
    this->options = options;
    if (options.method == ServerOptions::byTimeout)
        timer = Timer();
    pollFd[0].fd = socketFd;
    pollFd[0].events = POLLIN;
    pollFd[0].revents = 0;
}
Server& Server::operator=(const Server& s)
{
    options = s.options;
    activeClient = s.activeClient;
    status = s.status;
    address = s.address;
    socketFd = s.socketFd;
    noReply = s.noReply;
    pollFd[0] = s.pollFd[0];
    if (status == ServiceStatus::Running) {
        Read();
    }
    return *this;
}
Server::Server(const Server& s) : c(s.options.cl)
{
    *this = s;
}

std::string to_string(sockaddr_storage addr)
{
    std::string result = std::string(INET6_ADDRSTRLEN, '\0');
    if (addr.ss_family == AF_INET6)
        inet_ntop(addr.ss_family,
            &((sockaddr_in6*)&addr)->sin6_addr,
            result.data(), result.size());
    else if (addr.ss_family == AF_INET)
        inet_ntop(addr.ss_family,
            &((sockaddr_in*)&addr)->sin_addr,
            result.data(), result.size());
    result.shrink_to_fit();
    return result;
}

std::string to_string(sockaddr addr)
{
    return to_string(*reinterpret_cast<sockaddr_storage*>(&addr));
}
void InitTheirAddr(sockaddr_in& addr, ServerOptions opt)
{
    addr.sin_family = AF_INET; // host byte order
    addr.sin_port = htons(opt.port); // short, network byte order
    addr.sin_addr = *((struct in_addr*)opt.destination.h_addr);
    for (size_t i = 0; i < sizeof addr.sin_zero; i++) {
        addr.sin_zero[i] = '\0';
    }
}

void Server::updateClients(ClientServerMessage message, sockaddr_storage address)
{
    std::string strAddress = to_string(address);

    switch (message) {
    case ClientServerMessage::SERVER_REPLY_OK:
        std::cout << "Sucessfuly connected to " << strAddress << "\n";
        break;
    case ClientServerMessage::RUNNING: {
        sockaddr_in tmp;
        InitTheirAddr(tmp, options);
        options.cl->SendReply();
        std::cout << "[Server] Send SERVER_REPLY_OK to " << strAddress << "\n";
        if (std::find(activeClient.begin(), activeClient.end(), strAddress) == activeClient.end()) {
            activeClient.push_back(strAddress);
        }
    } break;
    case ClientServerMessage::STOPPED:
        if (options.method == ServerOptions::byPacket && std::find(activeClient.begin(), activeClient.end(), strAddress) != activeClient.end()) {
            activeClient.remove(strAddress);
        }
    default:
        break;
    }
}

void* get_in_addr(sockaddr* sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((sockaddr_in*)sa)->sin_addr);
    }

    return &(((sockaddr_in6*)sa)->sin6_addr);
}

void initBuffer(buffer_t buffer)
{
    for (size_t i = 0; i < sizeof(buffer_t); ++i) {
        buffer[i] = '\0';
    }
}

void Server::mainLoop(fd* socket, char s[INET6_ADDRSTRLEN])
{
    if (status == ServiceStatus::Running) {
        buffer_t tmp;
        initBuffer(tmp);

        sockaddr_storage their_address;
        socklen_t addr_len = sizeof(their_address);
        int bytesReceived = -1;
        int err_count = 0;
        sockaddr* casted = reinterpret_cast<sockaddr*>(&their_address);

        int poll_result = 0;
        poll_result = poll(pollFd, 1, 1);

        if (poll_result == -1) {
            perror("[Server] poll");
            if (err_count < 5)
                ++err_count;
            else
                throw std::runtime_error("[Server] Too many poll errors");
        } else if (poll_result > 0) {
            while (poll_result > 0) {
                if (!(pollFd[0].revents & POLLIN))
                    break;

                if (options.debugOutput)
                    std::cout << "[Server] Receive packet from " << inet_ntop(casted->sa_family, get_in_addr(casted), s, INET6_ADDRSTRLEN) << "\n";
                bytesReceived = recvfrom(*socket,
                    tmp, sizeof(tmp), 0, casted, &addr_len); // receive normal data

                if (bytesReceived == -1) {
                    perror("[Server] recvfrom");
                    std::cerr << "[Server] Error occured in recvfrom\n";
                    return;
                }

                tmp[bytesReceived] = '\0';
                ClientServerMessage message = static_cast<ClientServerMessage>(std::atoi(tmp));
                updateClients(message, their_address);
                poll_result = poll(pollFd, 1, 1);
            }
        }
    }
    delete socket;
}

std::vector<std::string> Server::GetClients() const
{
    std::vector<std::string> result = std::vector<std::string>();
    {
        size_t length = activeClient.size();
        result.resize(length);

        size_t index = 0;
        for (auto i = activeClient.cbegin(); i != activeClient.cend(); ++i, ++index) {
            result[index] = *i;
        }
    }

    return result;
}

void Server::Read()
{
    char buffer[INET6_ADDRSTRLEN];
    mainLoop(new fd(socketFd), buffer);
}

void Server::Start()
{
    char buffer[INET6_ADDRSTRLEN];
    status = ServiceStatus::Running;
    if (options.addSelfAddress)
        activeClient.push_back(to_string(options.selfaddress));
    mainLoop(new fd(socketFd), buffer);
}

void Server::Stop()
{
    if (options.addSelfAddress)
        activeClient.remove(to_string(options.selfaddress));
    status = ServiceStatus::Stopped;
}

Server::~Server()
{
}
