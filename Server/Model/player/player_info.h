#ifndef PLAYER_INFO_H_
#define PLAYER_INFO_H_

#include <list>
#include <unordered_map>
#include "../objects/items/weapons/weapon.h"

class PlayerInfo {
   friend class Player;
   private:
      int life;
      int bullets;
      int keys;
      int treasure;
      int resurrected;
      Weapon* equiped;
      std::list <int> inventory;
   
   public:
      explicit PlayerInfo();
      ~PlayerInfo();
      int getLife();
      int getNumBullets();
      int getKey();
      int getTreasure();
      int getNumResurrection();
      Weapon* getWeaponEquiped();
      /*void addLife(int life);
      void addBullets(int bullets);
      void addNumKeys(int key);
      void addTreasure(int treasure);
      void addNumResurrection();
      void reduceLife(int life);
      void reduceBullets(int bullets);
      void reduceNumKeys(int key);
      void reduceTreasure(int treasure);*/
      //void changeWeaponEquiped(Weapon* &weapon);
      
      std::list <int>getInventory();
      void addInventory(int weapon);
      bool hasWeapon(int weapon);
};

#endif    // PLAYER_INFO_H_
