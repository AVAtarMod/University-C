#ifndef TYPES_LIB
#define TYPES_LIB

#include <cstdint>
#include <cstring>
#include <sys/socket.h>

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
bool operator<(const sockaddr& a, const sockaddr& b);
#endif // TYPES_LIB
