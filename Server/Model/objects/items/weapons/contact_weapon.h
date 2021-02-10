#ifndef CONTACT_WEAPON_H_
#define CONTACT_WEAPON_H_

#include "weapon.h"

class ContactWeapon: public Weapon {
 public:
    ContactWeapon() {};
    virtual const int getType() = 0;
    static bool inRange() {
        /*establezco si el oponente esta en el radio del jugador*/
        return true;
    }
};

#endif   // CONTACT_WEAPON_H_
