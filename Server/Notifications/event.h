#ifndef EVENT_H
#define EVENT_H

#include "notification.h"
#include "../../Common/protocol.h"
#include "./../Model/player/player.h"

class Event : public Notification {
    Id map;
    EventOpcode event_type;
    Id player_id;
    uint32_t pos_x;
    uint32_t pos_y;
    float angle;
    uint8_t is_moving;
    uint8_t is_shoting;
    uint32_t life;
    uint8_t resurrected;
    uint32_t treasure;
    uint32_t bullets;
    uint32_t value;

    public:
        Event(const Id map, EventOpcode event_type, Id player_id,
            uint32_t pos_x, uint32_t pos_y, float angle, int is_moving, int is_shoting);
        Event(const Id map, EventOpcode event_type, Id player_id,
            uint32_t pos_x, uint32_t pos_y, float angle, int life, int resurrected,
            int treasure, int bullets);
        Event(const Id map, EventOpcode event_type, Id player_id, int value);
        Event(const Id map, EventOpcode event_type, Id player_id,
            uint32_t pos_x, uint32_t pos_y);

        virtual ~Event();
        
        Event(const Event& other);
        Event& operator=(const Event& other);

        virtual bool send(const ConnectionId sender, const Socket& peer);
};

#endif