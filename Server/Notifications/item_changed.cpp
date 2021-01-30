#include "item_changed.h"

ItemChanged::ItemChanged(const Id map, ItemOpcode item_type, Id player_id, 
                        uint32_t pos_x, uint32_t pos_y) :
                        map(map),
                        item_type(item_type),
                        player_id(player_id),
                        pos_x(pos_x),
                        pos_y(pos_y) {}

ItemChanged::ItemChanged(const Id map, ItemOpcode item_type, Id player_id, 
                        uint32_t pos_x, uint32_t pos_y, int player_life) :
                        map(map),
                        item_type(item_type),
                        player_id(player_id),
                        pos_x(pos_x),
                        pos_y(pos_y), 
                        player_life(player_life) {}

ItemChanged::ItemChanged(const Id map, ItemOpcode item_type, Id player_id, 
                        uint32_t pos_x, uint32_t pos_y, int player_keys) :
                        map(map),
                        item_type(item_type),
                        player_id(player_id),
                        pos_x(pos_x),
                        pos_y(pos_y), 
                        player_keys(player_keys) {}

ItemChanged::ItemChanged(const Id map, ItemOpcode item_type, Id player_id, 
                        uint32_t pos_x, uint32_t pos_y, int player_treasure) :
                        map(map),
                        item_type(item_type),
                        player_id(player_id),
                        pos_x(pos_x),
                        pos_y(pos_y), 
                        player_treasure(player_treasure) {}

ItemChanged::ItemChanged(const Id map, ItemOpcode item_type, Id player_id, 
                        uint32_t pos_x, uint32_t pos_y, int player_bullets) :
                        map(map),
                        item_type(item_type),
                        player_id(player_id),
                        pos_x(pos_x),
                        pos_y(pos_y), 
                        player_bullets(player_bullets) {}

ItemChanged::~ItemChanged() {}
        
ItemChanged::ItemChanged(const ItemChanged& other) {}
ItemChanged& ItemChanged::operator=(const ItemChanged& other) {}

bool ItemChanged::send(const ConnectionId sender, const Socket& peer) {
    try{
        uint8_t buffer[2];
        buffer[0] = ITEM_CHANGED_OPCODE;
        buffer[1] = item_type;
        peer.send((char *)buffer, 2);
        switch (item_type) {
            case CLOSE_DOOR_ITM: { //  pos x, pos y (posicion de la puerta)
                this->pos_x = htole32(this->pos_x);
                this->pos_y = htole32(this->pos_y);
                peer.send((char *)&pos_x, sizeof(pos_x));
                peer.send((char *)&pos_y, sizeof(pos_y));
                break;
            }
            case OPEN_DOOR_ITM: { // pos x, pos y (posicion de la puerta)
                uint32_t buffer[8];
                //buffer[0] = ;
                //buffer[1] = ;
                peer.send((char *)buffer, 9);
                break;
            }
            case MEDICAL_KIT_TAKEN_ITM: { //id del jugador que lo agarra, pos x, pos y, vida del jugador
                uint32_t buffer[1];
                //buffer[0] = ;
                //buffer[1] = ;
                peer.send((char *)buffer, 2);
                break;
            }
            case FOOD_TAKEN_ITM: { //id del jugador que lo agarra, pos x, pos y, vida del jugador
                uint32_t buffer[1];
                //buffer[0] = ;
                //buffer[1] = ;
                peer.send((char *)buffer, 2);
                break;
            }
            case BLOOD_TAKEN_ITM: { //id del jugador que lo agarra, pos x, pos y, vida del jugador
                uint32_t buffer[2];
                //buffer[0] = ;
                //buffer[1] = ;
                peer.send((char *)buffer, 3);
                break;
            }
            case KEY_TAKEN_ITM: { // id del jugador que lo agarra, pos x, pos y, keys del jugador
                uint32_t buffer[7];
                //buffer[0] = ;
                //buffer[1] = ;
                peer.send((char *)buffer, 8);
                break;
            }
            case WEAPON_TAKEN_ITM: { // id del jugador que lo agarra, pos x, pos y
                uint32_t buffer[3];
                //buffer[0] = ;
                //buffer[1] = ;
                peer.send((char *)buffer, 4);
                break;
            }
            case TREASURE_TAKEN_ITM: { //id del jugador que lo agarra, pos x, pos y, puntaje del jugador
                uint32_t buffer[3];
                //buffer[0] = ;
                //buffer[1] = ;
                peer.send((char *)buffer, 4);
                break;
            }
            case BULLETS_TAKEN_ITM: { //id del jugador que lo agarra, pos x, pos y, balas del jugador
                uint32_t buffer[3];
                //buffer[0] = ;
                //buffer[1] = ;
                peer.send((char *)buffer, 4);
                break;
            }
            default:
                throw Exception("Unknown event type.");
                break;
            }

    } catch (const std::exception& e) {
        return false;
    }
    return true;
}