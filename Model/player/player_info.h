#ifndef PLAYER_INFO_H_
#define PLAYER_INFO_H_

#include <list>
#include "../objects/items/weapons/weapon.h"
class PlayerInfo {
 public:
    explicit PlayerInfo();
    int getLife();
    int getNumBullets();
    int getKey();
    int getTreasure();
    void addLife(int life);
    void addBullets(int bullets);
    void addNumKeys(int key);
    void addTreasure(int treasure);
    void reduceLife(int life);
    void reduceBullets(int bullets);
    void reduceNumKeys(int key);
    void reduceTreasure(int treasure);
    
    std::list <Weapon> getInventory();
    void addInventory(Weapon &weapon);
    //bool hasWeapon(Weapon &weapon);
    ~PlayerInfo();
 private:
    int life;
    int bullets;
    int keys;
    int treasure;
    std::list <Weapon> inventory;
    
};

#endif    // PLAYER_INFO_H_
