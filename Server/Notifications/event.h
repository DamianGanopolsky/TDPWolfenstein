#ifndef EVENT_H
#define EVENT_H

#include "notification.h"
#include "../../Common/protocol.h"
#include "./../Model/player/player.h"

class Event : public Notification {
    std::string map_;
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
    uint32_t num_players;
    std::string name_1;
    uint32_t score_1;
    std::string name_2;
    uint32_t score_2;
    std::string name_3;
    uint32_t score_3;
    std::string name_4;
    uint32_t score_4;
    std::string name_5;
    uint32_t score_5;


    public:
        Event(std::string map, EventOpcode event_type, Id player_id);
        Event(std::string map, EventOpcode event_type, Id player_id,
            uint32_t pos_x, uint32_t pos_y, float angle, int is_moving,
            int is_shoting);
        Event(std::string map, EventOpcode event_type, Id player_id,
            uint32_t pos_x, uint32_t pos_y, float angle, int life, int resurrected,
            int treasure, int bullets);
        Event(std::string map, EventOpcode event_type, Id player_id, int value);
        Event(std::string map, EventOpcode event_type, Id player_id,
            uint32_t pos_x, uint32_t pos_y);
        Event(std::string map, EventOpcode event_type, int num_player, 
            std::string& name_1, int score_1, std::string& name_2,
            int score_2, std::string& name_3, int score_3, 
            std::string& name_4, int score_4, std::string& name_5, 
            int score_5);

        virtual ~Event();
        
        Event(const Event& other);
        Event& operator=(const Event& other);

        virtual bool send(const ConnectionId sender, const Socket& peer);
};

#endif