#ifndef ITEM_CHANGED_H
#define ITEM_CHANGED_H

#include "notification.h"
#include "../Common/protocol.h"
#include "../Model/player/player.h"

class ItemChanged : public Notification {
    ItemOpcode item_type;
    const Id map;
    const Id player_id;
    uint32_t pos_x;
    uint32_t pos_y;
    int player_life;
    int player_keys;
    int player_treasure;
    int player_bullets;

    public:
        ItemChanged(const Id map, ItemOpcode item_type, Id player_id, 
                    uint32_t pos_x, uint32_t pos_y);
        ItemChanged(const Id map, ItemOpcode item_type, Id player_id, 
                    uint32_t pos_x, uint32_t pos_y, int player_life);
        ItemChanged(const Id map, ItemOpcode item_type, Id player_id, 
                    uint32_t pos_x, uint32_t pos_y, int player_keys);
        ItemChanged(const Id map, ItemOpcode item_type, Id player_id, 
                    uint32_t pos_x, uint32_t pos_y, int player_treasure);
        ItemChanged(const Id map, ItemOpcode item_type, Id player_id, 
                    uint32_t pos_x, uint32_t pos_y, int player_bullets);
        virtual ~ItemChanged();
        
        ItemChanged(const ItemChanged& other);
        ItemChanged& operator=(const ItemChanged& other);

        virtual bool send(const ConnectionId sender, const Socket& peer);
};

#endif