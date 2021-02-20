#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>

#include "./../objects/scene/blocking_objects/blocking_object.h"
#include "./player_info.h"
#include "./player_position.h"
#include "./player_state.h"
#include "../../../Common/defs.h"
#include "../response.h"
#include "../constants/config_player.h"
#include "./../objects/items/weapons/knife.h"
#include "./../objects/items/weapons/gun.h"
#include "./../objects/items/weapons/machine_gun.h"
#include "./../objects/items/weapons/chain_cannon.h"
#include "../constants/YamlConfig.h"

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
  Knife* knife;
  Gun* gun;
  MachineGun* machine_gun;
  ChainCannon* chain_cannon;
  int rate;

  void _die();

public:
      Player(int pos_x, int pos_y, int width, 
          int height, std::string& nickname, 
          Id id_player, const int& rate);
      Player(int width, int height, 
          std::string& nickname, Id id_player, 
          const int& rate);
      ~Player();
      int life_cooldown;
      int machine_gun_cooldown;
      int chain_cannon_cooldown;
      bool gun_can_shoot;
      bool forced_weapon;
      int weapon_equiped_before;
      PlayerPosition getPos();
      PlayerInfo getInfo();
      State* getState();
      std::string getNickname(); 
      Id getId(); 
      bool isAlive();
      bool isMoving();
      bool isRotating();
      bool isShooting();
      void updateMovement();
      void updateRotation();
      Response updateLife(int& iteration);
      Response updateShooting(double& distance, int& damage, int& iteration);
      Response receiveAttack(int& damage);
      Response resurrect();
      Response changeWeapon(const int& weapon);
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
      void addLife(int life);
      void addBullets(int bullets);
      void addNumKeys(int key);
      void addTreasure(int treasure);
      void addNumResurrection();
      void addKill();
      void reduceLife(int life);
      void reduceBullets(int bullets);
      void reduceNumKeys(int key);
      void reduceTreasure(int treasure);
      void addInventory(int weapon);
      void deleteInventory(int weapon);
      void setPosition(int x, int y);
};

#endif   // PLAYER_H