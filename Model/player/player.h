#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "./player_info.h"
#include "./player_position.h"
#include "./player_state.h"
#include "./def.h"
#include "../response.h"
#include "../constants/config_player.h"
#include "../constants/const_object_map.h"
#include "../Model/map/object_map.h"

class Player {
  Id player_id;
  PlayerPosition pos;
  PlayerInfo info;
  State* state;
  ObjectMap objMap; 
  std::string nickname;
  Id map;
  //Race race;
  bool alive;
  bool _move(Id map, std::pair<int, int> next_pos);
  bool _changeCell(PlayerPosition &pos, std::pair<int, int> &next_pos);

  public:
    Player(PlayerInfo &info, PlayerPosition &pos, std::string& nickname, Id map);
    PlayerPosition getPos();
    PlayerInfo getInfo();
    State* getState();
    std::string getNickname(); 
    //Race getRace();
    bool isAlive();
    Response useWeapon(Id id, Id id_target, Player* target, int& damage);
    void receiveAttack(int& damage);
    void die();
    Response resurrect();
    void changeWeapon(Weapon& weapon);
    Response moveUp();
    Response moveDown();
    Response moveLeft();
    Response moveRight();
    Response stopMoving();
    Response rotateLeft();
    Response rotateRight();
    Response stopRotating();
};

#endif   // PLAYER_H
