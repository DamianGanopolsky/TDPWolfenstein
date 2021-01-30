#include "notification.h"

Notification::Notification() {}

Notification::~Notification() {}

/*friend size_t Notification::operator<<(const uint32_t& number, const Socket& peer) {
    uint32_t num = htole32(number);
    return peer.send((char *)&num, sizeof(num));
}

friend size_t Notification::operator<<(const int& number, const Socket& peer) {
    return peer.send((char *)&number, sizeof(number));
}

friend size_t Notification::operator<<(const float& number, const Socket& peer) {
    return peer.send((char *)&number, sizeof(number));
}*/