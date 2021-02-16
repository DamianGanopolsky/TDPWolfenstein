#include "event.h"

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
            std::string& name_1, int score_1, std::string& name_2,
            int score_2, std::string& name_3, int score_3, 
            std::string& name_4, int score_4, std::string& name_5, 
            int score_5) : 
            map_(map), event_type(event_type), num_players((uint32_t)num_player),
            name_1(name_1), score_1((uint32_t)score_1), name_2(name_2), 
            score_2((uint32_t)score_2), name_3(name_3), score_3((uint32_t)score_3), 
            name_4(name_4), score_4((uint32_t)score_4), name_5(name_5), 
            score_5((uint32_t)score_5) {}

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
                std::cout << "id es: " << player_id <<std::endl;
                std::cout << "posx es: " << pos_x <<std::endl;
                std::cout << "posy es: " << pos_y <<std::endl;
                std::cout << "angle es: " << angle <<std::endl;
                std::cout << "isMoving es: " << unsigned(is_moving) <<std::endl;
                std::cout << "isShooting es: " << unsigned(is_shoting) <<std::endl;
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
                std::cout << "player_id es: " << player_id <<std::endl;
                std::cout << "map es: " << map_ <<std::endl;
                std::cout << "posx es: " << pos_x <<std::endl;
                std::cout << "posy es: " << pos_y <<std::endl;
                std::cout << "angle es: " << angle <<std::endl;
                std::cout << "life es" << life <<std::endl;
                std::cout << "resurrected es: " << (unsigned)resurrected <<std::endl;
                std::cout << "treasure es: " << treasure <<std::endl;
                std::cout << "bullets es: " << bullets <<std::endl;
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
            case DELETE_PLAYER_EV: { //id del jugador
                this->player_id = htole32(this->player_id);
                peer.send((char *)&player_id, sizeof(player_id));
                break;
            }
            case ATTACK_EV:
            case BE_ATTACKED_EV:
            case CHANGE_WEAPON_EV: { //id del jugador, value
                std::cout << "player_id es: " << player_id <<std::endl;
                std::cout << "value es: " << value <<std::endl;
                this->player_id = htole32(this->player_id);
                peer.send((char *)&player_id, sizeof(player_id));
                this->value = htole32(this->value);
                peer.send((char *)&value, sizeof(value));
                break;
            }
            case DEATH_EV: { //id del jugador, coordenada x, coordenada y (la llegada de este evento tambien implica que se dropean los objetos a la hora de la muerte)
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
                peer.send((char *)&num_players, sizeof(num_players));
                //player 1
                const char* char_name_1 = name_1.c_str();
                uint32_t name_1_size[1];
                name_1_size[0] = strlen(char_name_1);
                name_1_size[0] = htole32(name_1_size[0]);
                std::cout << "NAME_1: " << char_name_1 << std::endl;
                std::cout << "NAME_1 SIZE: " << name_1_size << std::endl;
                peer.send((char *)name_1_size, sizeof(name_1_size));
                peer.send(char_name_1, sizeof(char_name_1));
                this->score_1 = htole32(this->score_1);
                peer.send((char *)&score_1, sizeof(score_1));
                //player 2
                const char* char_name_2 = name_2.c_str();
                uint32_t name_2_size[1];
                name_2_size[0] = strlen(char_name_2);
                name_2_size[0] = htole32(name_2_size[0]);
                std::cout << "NAME_2: " << char_name_2 << std::endl;
                std::cout << "NAME_2 SIZE: " << name_2_size << std::endl;
                peer.send((char *)name_2_size, sizeof(name_2_size));
                peer.send(char_name_2, sizeof(char_name_2));
                this->score_2 = htole32(this->score_2);
                peer.send((char *)&score_2, sizeof(score_2));
                //player 3
                const char* char_name_3 = name_3.c_str();
                uint32_t name_3_size[1];
                name_3_size[0] = strlen(char_name_3);
                name_3_size[0] = htole32(name_3_size[0]);
                std::cout << "NAME_3: " << char_name_3 << std::endl;
                std::cout << "NAME_3 SIZE: " << name_3_size << std::endl;
                peer.send((char *)name_3_size, sizeof(name_3_size));
                peer.send(char_name_3, sizeof(char_name_3));
                this->score_3= htole32(this->score_3);
                peer.send((char *)&score_3, sizeof(score_3));
                //player 4
                const char* char_name_4 = name_4.c_str();
                uint32_t name_4_size[1];
                name_4_size[0] = strlen(char_name_4);
                name_4_size[0] = htole32(name_4_size[0]);
                std::cout << "NAME_4: " << char_name_4 << std::endl;
                std::cout << "NAME_4 SIZE: " << name_4_size << std::endl;
                peer.send((char *)name_4_size, sizeof(name_4_size));
                peer.send(char_name_4, sizeof(char_name_4));
                this->score_4 = htole32(this->score_4);
                peer.send((char *)&score_4, sizeof(score_4));
                //player 5
                const char* char_name_5 = name_5.c_str();
                uint32_t name_5_size[1];
                name_5_size[0] = strlen(char_name_5);
                name_5_size[0] = htole32(name_5_size[0]);
                std::cout << "NAME_5: " << char_name_5 << std::endl;
                std::cout << "NAME_5 SIZE: " << name_5_size << std::endl;
                peer.send((char *)name_5_size, sizeof(name_5_size));
                peer.send(char_name_5, sizeof(char_name_5));
                this->score_5= htole32(this->score_5);
                peer.send((char *)&score_5, sizeof(score_5));
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