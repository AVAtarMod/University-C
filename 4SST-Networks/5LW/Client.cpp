#include "Client.hpp"

// Client side
Client::Client(fd binded, ClientOptions options, int port, hostent destination)
{
    listeners = std::list<sockaddr>();
    socketFd = binded;
    this->options = options;
    this->port = port;
    this->destination = destination;
}

void Client::FinishLoop(sockaddr_in their_addr)
{
    const char* finishMessage = std::to_string(static_cast<int>(ClientServerMessage::STOPPED)).c_str();
    int result = sendto(socketFd, finishMessage, strlen(finishMessage), 0,
        (struct sockaddr*)&their_addr, sizeof their_addr);
    if (result == -1) {
        perror("[Client] sendto");
        throw new std::runtime_error("[Client] Cannot send data");
    } else {
        if (options.debugOutput)
            std::cout << "[Client] "
                      << "finish message of size " << result << " sent to " << inet_ntoa(their_addr.sin_addr) << "\n";
    }
}

void Client::InitTheirAddr(sockaddr_in& addr)
{
    addr.sin_family = AF_INET; // host byte order
    addr.sin_port = htons(port); // short, network byte order
    addr.sin_addr = *((struct in_addr*)destination.h_addr);
    for (size_t i = 0; i < sizeof addr.sin_zero; i++) {
        addr.sin_zero[i] = '\0';
    }
}

void Client::sendMessage()
{
    const char* message = std::to_string(static_cast<int>(ClientServerMessage::RUNNING)).c_str();
    sockaddr_in their_addr; // connector's address information
    InitTheirAddr(their_addr);

    if (status == ServiceStatus::Running) {
        int result = sendto(socketFd, message, strlen(message), 0,
            (struct sockaddr*)&their_addr, sizeof their_addr);

        if (result == -1) {
            perror("[Client] sendto");
            throw new std::runtime_error("[Client] Cannot send data");
        } else {
            if (options.debugOutput)
                std::cout << "[Client] " << result << " bytes sent to " << inet_ntoa(their_addr.sin_addr) << "\n";
        }
        std::this_thread::sleep_for(options.timeout);
    } else
        FinishLoop(their_addr);
}

Client& Client::operator=(const Client& c)
{
    options = c.options;
    listeners = c.listeners;
    status = c.status;
    port = c.port;
    destination = c.destination;
    socketFd = c.socketFd;
    if (status == ServiceStatus::Running) {
        Start();
    }
    return *this;
}

Client::Client(const Client& c)
{
    *this = c;
}

void Client::Send()
{
    sendMessage();
}

void Client::Start()
{
    status = ServiceStatus::Running;
    sendMessage();
}
void Client::Stop()
{
    status = ServiceStatus::Stopped;
    sendMessage();
}

Client::~Client()
{
}
