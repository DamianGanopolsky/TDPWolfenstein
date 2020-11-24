#ifndef PLAYER_INFO_H_
#define PLAYER_INFO_H_

#include <set>
#include "./../objects/items/weapons/weapon.h"

class PlayerInfo {
 public:
    explicit PlayerInfo();
    int getLife();
    int getNumBullets();
    int getKey();
    //int getInventory();
    void addLife(int life);
    void addBullets(int bullets);
    void addNumKeys(int key);
    void addTreasure(int treasure);
    void addInventory(Weapon &weapon);
    bool hasWeapon(Weapon &weapon);
    ~PlayerInfo();
 private:
    int life;
    int bullets;
    int keys;
    int treasure;
    std::set <Weapon> inventory;
    
};

#endif    // PLAYER_INFO_H_
