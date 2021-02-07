#include "event.h"

Event::Event(const Id map, EventOpcode event_type, Id player_id) : 
            map(map), event_type(event_type), player_id(player_id) {}

Event::Event(const Id map, EventOpcode event_type, Id player_id,
            uint32_t pos_x, uint32_t pos_y, float angle, int is_moving,
            int is_shoting) : 
            map(map), event_type(event_type), player_id(player_id), pos_x(pos_x),
            pos_y(pos_y), angle(angle), is_moving((uint8_t)is_moving),
            is_shoting((uint8_t)is_shoting) {}

Event::Event(const Id map, EventOpcode event_type, Id player_id,
            uint32_t pos_x, uint32_t pos_y, float angle, int life, int resurrected,
            int treasure, int bullets) : 
            map(map), event_type(event_type), player_id(player_id), pos_x(pos_x),
            pos_y(pos_y), angle(angle), life((uint32_t)life), resurrected((uint8_t)resurrected),
            treasure((uint32_t)treasure), bullets((uint32_t)bullets) {}

Event::Event(const Id map, EventOpcode event_type, Id player_id, int value) : 
            map(map), event_type(event_type), player_id(player_id), 
            value((uint32_t)value) {}
Event::Event(const Id map, EventOpcode event_type, Id player_id,
            uint32_t pos_x, uint32_t pos_y) : 
            map(map), event_type(event_type), player_id(player_id),
            pos_x(pos_x), pos_y(pos_y) {}

Event::~Event() {}
        
Event::Event(const Event& other) {
    this->map = other.map;
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
    this->map = other.map;
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
        buffer[1] = event_type;
        peer.send((char *)buffer, 2);
        std::cout << "event type es: " << unsigned(event_type) <<std::endl;
        switch (event_type) {
            case MOVEMENT_EV: { //id del jugador, coordenada x, coordenada y, angulo del jugador, moviendo (1-si o 0-no), disparando (si o no)
                std::cout << "id es: " << player_id <<std::endl;
                std::cout << "posx es: " << pos_x <<std::endl;
                std::cout << "posy es: " << pos_y <<std::endl;
                std::cout << "angle es: " << angle <<std::endl;
                std::cout << "isMoving es: " << is_moving <<std::endl;
                std::cout << "isShooting es: " << is_shoting <<std::endl;
                this->player_id = htonl(this->player_id);
                peer.send((char *)&player_id, sizeof(player_id));
                this->pos_x = htonl(this->pos_x);
                this->pos_y = htonl(this->pos_y);
                this->angle= htonl(this->angle);
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
                std::cout << "map es: " << map <<std::endl;
                std::cout << "posx es: " << pos_x <<std::endl;
                std::cout << "posy es: " << pos_y <<std::endl;
                std::cout << "angle es: " << angle <<std::endl;
                std::cout << "life es" << life <<std::endl;
                std::cout << "resurrected es: " << (unsigned)resurrected <<std::endl;
                std::cout << "treasure es: " << treasure <<std::endl;
                std::cout << "bullets es: " << bullets <<std::endl;
                this->player_id = htonl(this->player_id);
                peer.send((char *)&player_id, sizeof(player_id));
                this->map = htonl(this->map);
                peer.send((char *)&map, sizeof(map));
                this->pos_x = htonl(this->pos_x);
                this->pos_y = htonl(this->pos_y);
                peer.send((char *)&pos_x, sizeof(pos_x));
                peer.send((char *)&pos_y, sizeof(pos_y));
                this->angle = htonl(this->angle);
                peer.send((char *)&angle, sizeof(angle));
                this->life = htonl(this->life);
                peer.send((char *)&life, sizeof(life));
                peer.send((char *)&resurrected, sizeof(resurrected));
                this->treasure = htonl(this->treasure);
                peer.send((char *)&treasure, sizeof(treasure));
                this->bullets = htonl(this->bullets);
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
            case CHANGE_WEAPON_EV: { //id del jugador, disparando (si o no)
                this->player_id = htonl(this->player_id);
                peer.send((char *)&player_id, sizeof(player_id));
                this->value = htonl(this->value);
                peer.send((char *)&value, sizeof(value));
                break;
            }
            case DEATH_EV: { //id del jugador, coordenada x, coordenada y (la llegada de este evento tambien implica que se dropean los objetos a la hora de la muerte)
                this->player_id = htonl(this->player_id);
                peer.send((char *)&player_id, sizeof(player_id));
                this->pos_x = htonl(this->pos_x);
                this->pos_y = htonl(this->pos_y);
                peer.send((char *)&pos_x, sizeof(pos_x));
                peer.send((char *)&pos_y, sizeof(pos_y));
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