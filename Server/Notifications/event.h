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
    uint32_t treasure_1;
    uint32_t kills_1;
    uint32_t score_1;
    std::string name_2;
    uint32_t treasure_2;
    uint32_t kills_2;
    uint32_t score_2;
    std::string name_3;
    uint32_t treasure_3;
    uint32_t kills_3;
    uint32_t score_3;
    std::string name_4;
    uint32_t treasure_4;
    uint32_t kills_4;
    uint32_t score_4;
    std::string name_5;
    uint32_t treasure_5;
    uint32_t kills_5;
    uint32_t score_5;


    public:
        Event(EventOpcode event_type);
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
            std::string& name_1, int treasure_1, int kills_1, int score_1, 
            std::string& name_2, int treasure_2, int kills_2, int score_2, 
            std::string& name_3, int treasure_3, int kills_3, int score_3, 
            std::string& name_4, int treasure_4, int kills_4, int score_4, 
            std::string& name_5, int treasure_5, int kills_5, int score_5);

        virtual ~Event();
        
        Event(const Event&) = delete;
        Event& operator=(const Event&) = delete;
        Event(Event&& other) = delete;
        Event& operator=(Event&&) = delete;

        virtual bool send(const ConnectionId sender, const Socket& peer);
};

#endif