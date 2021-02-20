#include "event.h"

Event::Event(EventOpcode event_type) : event_type(event_type) {}

Event::Event(std::string map, EventOpcode event_type, Id player_id) : 
            map_(map), event_type(event_type), player_id(player_id) {}

Event::Event(std::string map, EventOpcode event_type, Id player_id,
            uint32_t pos_x, uint32_t pos_y, float angle, int is_moving,
            int is_shoting) : 
            map_(map), event_type(event_type), player_id(player_id), pos_x(pos_x),
            pos_y(pos_y), angle(angle), is_moving((uint8_t)is_moving),
            is_shoting((uint8_t)is_shoting) {}

Event::Event(std::string map, EventOpcode event_type, Id player_id,
            uint32_t pos_x, uint32_t pos_y, float angle, int life, int resurrected,
            int treasure, int bullets) : 
            map_(map), event_type(event_type), player_id(player_id), pos_x(pos_x),
            pos_y(pos_y), angle(angle), life((uint32_t)life), resurrected((uint8_t)resurrected),
            treasure((uint32_t)treasure), bullets((uint32_t)bullets) {}

Event::Event(std::string map, EventOpcode event_type, Id player_id, int value) : 
            map_(map), event_type(event_type), player_id(player_id), 
            value((uint32_t)value) {}

Event::Event(std::string map, EventOpcode event_type, Id player_id,
            uint32_t pos_x, uint32_t pos_y) : 
            map_(map), event_type(event_type), player_id(player_id),
            pos_x(pos_x), pos_y(pos_y) {}

Event::Event(std::string map, EventOpcode event_type, int num_player, 
            std::string& name_1, int treasure_1, int kills_1, int score_1, 
            std::string& name_2, int treasure_2, int kills_2, int score_2, 
            std::string& name_3, int treasure_3, int kills_3, int score_3, 
            std::string& name_4, int treasure_4, int kills_4, int score_4, 
            std::string& name_5, int treasure_5, int kills_5, int score_5) : 
            map_(map), event_type(event_type), num_players((uint32_t)num_player),
            name_1(name_1), treasure_1((uint32_t)treasure_1), kills_1((uint32_t)kills_1), score_1((uint32_t)score_1), 
            name_2(name_2), treasure_2((uint32_t)treasure_2), kills_2((uint32_t)kills_2), score_2((uint32_t)score_2), 
            name_3(name_3), treasure_3((uint32_t)treasure_3), kills_3((uint32_t)kills_3), score_3((uint32_t)score_3), 
            name_4(name_4), treasure_4((uint32_t)treasure_4), kills_4((uint32_t)kills_4), score_4((uint32_t)score_4), 
            name_5(name_5), treasure_5((uint32_t)treasure_5), kills_5((uint32_t)kills_5), score_5((uint32_t)score_5) {}

Event::~Event() {}
        
Event::Event(const Event& other) {
    this->map_ = other.map_;
    this->event_type = other.event_type;
    this->player_id = other.player_id;
    this->pos_x = other.pos_x;
    this->pos_y = other.pos_y;
    this->angle = other.angle;
    this->is_moving = other.is_moving;
    this->is_shoting = other.is_shoting;
    this->life = other.life;
    this->resurrected = other.resurrected;
    this->treasure = other.treasure;
    this->bullets = other.bullets;
    this->value = other.value;
}

Event& Event::operator=(const Event& other) {
    this->map_ = other.map_;
    this->event_type = other.event_type;
    this->player_id = other.player_id;
    this->pos_x = other.pos_x;
    this->pos_y = other.pos_y;
    this->angle = other.angle;
    this->is_moving = other.is_moving;
    this->is_shoting = other.is_shoting;
    this->life = other.life;
    this->resurrected = other.resurrected;
    this->treasure = other.treasure;
    this->bullets = other.bullets;
    this->value = other.value;
    return *this;
}

bool Event::send(const ConnectionId sender, const Socket& peer) {
    std::cout <<"Event: comienza el send()"<< std::endl;
    try{
        uint8_t buffer[2];
        buffer[0] = EVENT_OPCODE;
        std::cout << "Event opcode es" << unsigned(buffer[0]) << std::endl;
        buffer[1] = event_type;
        peer.send((char *)buffer, sizeof(buffer));
        std::cout << "event type es: " << unsigned(event_type) <<std::endl;
        switch (event_type) {
            case MOVEMENT_EV: { //id del jugador, coordenada x, coordenada y, angulo del jugador, moviendo (1-si o 0-no), disparando (si o no)
                //std::cout << "id es: " << player_id <<std::endl;
                //std::cout << "posx es: " << pos_x <<std::endl;
                //std::cout << "posy es: " << pos_y <<std::endl;
                //std::cout << "angle es: " << angle <<std::endl;
                //std::cout << "isMoving es: " << unsigned(is_moving) <<std::endl;
                //std::cout << "isShooting es: " << unsigned(is_shoting) <<std::endl;
                this->player_id = htole32(this->player_id);
                peer.send((char *)&player_id, sizeof(player_id));
                this->pos_x = htole32(this->pos_x);
                this->pos_y = htole32(this->pos_y);
                this->angle= htole32(this->angle);
                peer.send((char *)&pos_x, sizeof(pos_x));
                peer.send((char *)&pos_y, sizeof(pos_y));
                peer.send((char *)&angle, sizeof(angle));
                peer.send((char *)&is_moving, sizeof(is_moving));
                peer.send((char *)&is_shoting, sizeof(is_shoting));
                /*peer.send((char *)&gun_type, sizeof(gun_type));
                std::cout << "gun_type es: " << gun_type <<std::endl;*/
                break;
            }
            case NEW_PLAYER_EV:
            case RESURRECT_EV: { //id del jugador, id del mapa a abrir, coordenada x, coordenada y, angulo del jugador,vida , las vidas, puntaje, balas
                //std::cout << "player_id es: " << player_id <<std::endl;
                //std::cout << "map es: " << map_ <<std::endl;
                //std::cout << "posx es: " << pos_x <<std::endl;
                //std::cout << "posy es: " << pos_y <<std::endl;
                //std::cout << "angle es: " << angle <<std::endl;
                //std::cout << "life es" << life <<std::endl;
                //std::cout << "resurrected es: " << (unsigned)resurrected <<std::endl;
                //std::cout << "treasure es: " << treasure <<std::endl;
                //std::cout << "bullets es: " << bullets <<std::endl;
                this->player_id = htole32(this->player_id);
                peer.send((char *)&player_id, sizeof(player_id));
                int len_map=map_.length();
                char map[len_map];
                strcpy(map, map_.c_str());
                //char map[12]= "Fortified_6";
                uint32_t map_size[1];
                map_size[0]=strlen(map);
                std::cout << "MAP ACA ES" << map << std::endl;
                map_size[0] = htole32(map_size[0]);
                peer.send((char*)map_size, sizeof(map_size));
                std::cout << "ENVIE" << sizeof(map) << "BYTES" << std::endl;
                peer.send(map,sizeof(map));
                this->pos_x = htole32(this->pos_x);
                this->pos_y = htole32(this->pos_y);
                peer.send((char *)&pos_x, sizeof(pos_x));
                peer.send((char *)&pos_y, sizeof(pos_y));
                this->angle = htole32(this->angle);
                peer.send((char *)&angle, sizeof(angle));
                this->life = htole32(this->life);
                peer.send((char *)&life, sizeof(life));
                peer.send((char *)&resurrected, sizeof(resurrected));
                this->treasure = htole32(this->treasure);
                peer.send((char *)&treasure, sizeof(treasure));
                this->bullets = htole32(this->bullets);
                peer.send((char *)&bullets, sizeof(bullets));
                break;
            }
            /*case DELETE_PLAYER_EV: { //id del jugador
                std::cout << "Event: DELETE_PLAYER_EV" <<std::endl;
                this->player_id = htole32(this->player_id);
                peer.send((char *)&player_id, sizeof(player_id));
                break;
            }*/
            case ATTACK_EV:
            case BE_ATTACKED_EV:
            case CHANGE_WEAPON_EV: { //id del jugador, value
                //std::cout << "player_id es: " << player_id <<std::endl;
                //std::cout << "value es: " << value <<std::endl;
                this->player_id = htole32(this->player_id);
                peer.send((char *)&player_id, sizeof(player_id));
                this->value = htole32(this->value);
                peer.send((char *)&value, sizeof(value));
                break;
            }
            case DEATH_EV: { //id del jugador, coordenada x, coordenada y (la llegada de este evento tambien implica que se dropean los objetos a la hora de la muerte)
                std::cout << "Event: DEATH_EV" <<std::endl;
                this->player_id = htole32(this->player_id);
                peer.send((char *)&player_id, sizeof(player_id));
                this->pos_x = htole32(this->pos_x);
                this->pos_y = htole32(this->pos_y);
                peer.send((char *)&pos_x, sizeof(pos_x));
                peer.send((char *)&pos_y, sizeof(pos_y));
                break;
            }
            case SCORES_EV: {
                this->num_players = htole32(this->num_players);
                std::cout << "num_players es: " << num_players <<std::endl;
                peer.send((char *)&num_players, sizeof(num_players));
                
                //PLAYER 1
                int len_name_1 = name_1.length();
                char char_name_1[len_name_1];
                strcpy(char_name_1, name_1.c_str());
                uint32_t name_1_size[1];
                name_1_size[0] = strlen(char_name_1);
                name_1_size[0] = htole32(name_1_size[0]);
                std::cout << "NAME_1 BYTES: " << sizeof(char_name_1) << std::endl;
                peer.send((char *)name_1_size, sizeof(name_1_size));
                std::cout << "NAME_1: " << char_name_1 << std::endl;
                peer.send(char_name_1, sizeof(char_name_1));
                //treasure
                this->treasure_1 = htole32(this->treasure_1);
                std::cout << "TREASURE_1: " << treasure_1 << std::endl;
                peer.send((char *)&treasure_1, sizeof(treasure_1));
                //kills
                this->kills_1 = htole32(this->kills_1);
                std::cout << "KILLS_1: " << kills_1 << std::endl;
                peer.send((char *)&kills_1, sizeof(kills_1));
                //score
                this->score_1 = htole32(this->score_1);
                std::cout << "SCORE_1: " << score_1 << std::endl;
                peer.send((char *)&score_1, sizeof(score_1));
                //PLAYER 2
                int len_name_2 = name_2.length();
                char char_name_2[len_name_2];
                strcpy(char_name_2, name_2.c_str());
                uint32_t name_2_size[1];
                name_2_size[0] = strlen(char_name_2);
                name_2_size[0] = htole32(name_2_size[0]);
                std::cout << "NAME_2: " << char_name_2 << std::endl;
                std::cout << "NAME_2 BYTES: " <<  sizeof(char_name_2) << std::endl;
                peer.send((char *)name_2_size, sizeof(name_2_size));
                peer.send(char_name_2, sizeof(char_name_2));
                //treasure
                this->treasure_2 = htole32(this->treasure_2);
                std::cout << "TREASURE_2: " << treasure_2 << std::endl;
                peer.send((char *)&treasure_2, sizeof(treasure_2));
                //kills
                this->kills_2 = htole32(this->kills_2);
                std::cout << "KILLS_2: " << kills_2 << std::endl;
                peer.send((char *)&kills_2, sizeof(kills_2));
                //score
                this->score_2 = htole32(this->score_2);
                std::cout << "SCORE_2: " << score_2 << std::endl;
                peer.send((char *)&score_2, sizeof(score_2));
                //PLAYER 3
                int len_name_3 = name_3.length();
                char char_name_3[len_name_3];
                strcpy(char_name_3, name_3.c_str());
                uint32_t name_3_size[1];
                name_3_size[0] = strlen(char_name_3);
                name_3_size[0] = htole32(name_3_size[0]);
                std::cout << "NAME_3: " << char_name_3 << std::endl;
                std::cout << "NAME_3 BYTES: " <<  sizeof(char_name_3) << std::endl;
                peer.send((char *)name_3_size, sizeof(name_3_size));
                peer.send(char_name_3, sizeof(char_name_3));
                //treasure
                this->treasure_3 = htole32(this->treasure_3);
                std::cout << "TREASURE_3: " << treasure_3 << std::endl;
                peer.send((char *)&treasure_3, sizeof(treasure_3));
                //kills
                this->kills_3 = htole32(this->kills_3);
                std::cout << "KILLS_3: " << kills_3 << std::endl;
                peer.send((char *)&kills_3, sizeof(kills_3));
                //score
                this->score_3= htole32(this->score_3);
                std::cout << "SCORE_3: " << score_3 << std::endl;
                peer.send((char *)&score_3, sizeof(score_3));
                //PLAYER 4
                int len_name_4 = name_4.length();
                char char_name_4[len_name_4];
                strcpy(char_name_4, name_4.c_str());
                uint32_t name_4_size[1];
                name_4_size[0] = strlen(char_name_4);
                name_4_size[0] = htole32(name_4_size[0]);
                std::cout << "NAME_4: " << char_name_4 << std::endl;
                std::cout << "NAME_4 BYTES: " <<  sizeof(char_name_4) << std::endl;
                peer.send((char *)name_4_size, sizeof(name_4_size));
                peer.send(char_name_4, sizeof(char_name_4));
                //treasure
                this->treasure_4 = htole32(this->treasure_4);
                std::cout << "TREASURE_4: " << treasure_4 << std::endl;
                peer.send((char *)&treasure_4, sizeof(treasure_4));
                //kills
                this->kills_4 = htole32(this->kills_4);
                std::cout << "KILLS_4: " << kills_4 << std::endl;
                peer.send((char *)&kills_4, sizeof(kills_4));
                //score
                this->score_4 = htole32(this->score_4);
                std::cout << "SCORE_4: " << score_4 << std::endl;
                peer.send((char *)&score_4, sizeof(score_4));
                //PLAYER 5
                int len_name_5 = name_5.length();
                char char_name_5[len_name_5];
                strcpy(char_name_5, name_5.c_str());
                uint32_t name_5_size[1];
                name_5_size[0] = strlen(char_name_5);
                name_5_size[0] = htole32(name_5_size[0]);
                std::cout << "NAME_5: " << char_name_5 << std::endl;
                std::cout << "NAME_5 BYTES: " <<  sizeof(char_name_5) << std::endl;
                peer.send((char *)name_5_size, sizeof(name_5_size));
                peer.send(char_name_5, sizeof(char_name_5));
                //treasure
                this->treasure_5 = htole32(this->treasure_5);
                std::cout << "TREASURE_5: " << treasure_5 << std::endl;
                peer.send((char *)&treasure_5, sizeof(treasure_5));
                //kills
                this->kills_5 = htole32(this->kills_5);
                std::cout << "KILLS_5: " << kills_5 << std::endl;
                peer.send((char *)&kills_5, sizeof(kills_5));
                //score
                this->score_5= htole32(this->score_5);
                std::cout << "SCORE_5: " << score_5 << std::endl;
                peer.send((char *)&score_5, sizeof(score_5));
                break;
            }
            case DELETE_PLAYER_EV:
            case START_EV: {
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