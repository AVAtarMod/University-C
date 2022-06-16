#ifndef TYPES_LIB
#define TYPES_LIB

#include <cstdint>
#include <cstring>
#include <functional>
#include <string>
#include <sys/socket.h>
#include <unordered_map>

/**
 * @brief File descriptor type. Contain descriptor's ID
 */
struct fd {
    int id;

    fd(int value = 0)
    {
        id = value;
    }

    operator int()
    {
        return id;
    }
};

enum class ServiceStatus {
    Running,
    Stopped
};

enum class ClientServerMessage {
    RUNNING,
    STOPPED,
    SERVER_REPLY_OK
};

using buffer_t = char[INT32_WIDTH];

bool operator==(const sockaddr& a, const sockaddr& b);

// ! Has bugs, can be reason of crash
// The specialized hash function for `unordered_map` keys
struct sockaddr_hash {
    std::size_t operator()(const sockaddr& node) const
    {
        std::string data = std::string(sizeof(sockaddr::sa_data), '\0');
        for (size_t i = 0; i < data.size(); i++) {
            data[i] = node.sa_data[i];
        }

        std::size_t h1 = std::hash<std::string>()(data);
        std::size_t h2 = std::hash<sa_family_t>()(node.sa_family);

        return h1 ^ (h2 << 1);
    }
};

#endif // TYPES_LIB
