#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>

#include "./../objects/scene/blocking_objects/blocking_object.h"
#include "./player_info.h"
#include "./player_position.h"
#include "./player_state.h"
#include "./def.h"
#include "../response.h"
#include "../constants/config_player.h"

class Player : public BlockingObject {
  Id player_id;
  PlayerPosition pos;
  PlayerInfo info;
  State* state;
  std::string nickname;
  bool alive;
  bool moving;
  bool rotating;
  bool shooting;
  void _die();

  public:
    Player(int pos_x, int pos_y, int width, 
          int height, std::string& nickname, 
          Id id_player);
    Player(int width, int height, 
          std::string& nickname, Id id_player);
    ~Player();
    PlayerPosition getPos();
    PlayerInfo getInfo();
    State* getState();
    std::string getNickname(); 
    Id getId(); 
    bool isAlive();
    bool isMoving();
    bool isRotating();
    bool isShooting();
    void update();
    Response useWeapon(double& distance, int& damage);
    Response receiveAttack(int& damage);
    Response resurrect();
    Response changeWeapon(Weapon* weapon);
    Response startMovingUp();
    Response startMovingDown();
    Response startMovingLeft();
    Response startMovingRight();
    Response stopMoving();
    Response startRotatingLeft();
    Response startRotatingRight();
    Response stopRotating();
    Response startShooting();
    Response stopShooting();
};

#endif   // PLAYER_H