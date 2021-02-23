#ifndef __CONST_H__
#define __CONST_H__
#include <string>

#define PANEL_HEIGHT 400
#define PANEL_WIDTH 320

#define PANEL_DISTANCE 277
#define WALL_HEIGHT 64.0
#define FLOOR_COLOR 6908265   // Esto es el techo
#define CEILING_COLOR 2631720 // Esto es el piso
#define PANEL_TITLE "WOLFENSTEIN"
#define ENEMY_HEIGHT 64
#define ENEMY_WIDTH 64


#define CUADRICULA 64

#define SIZE_BOX 64 //Este valor debe ser una potencia de base 2
#define BIT_OFFSET 6 //Este valor debe ser el Log de base 2 de SIZE_BOX

#define FOV 90.0
#define TOTAL_BOX 256

enum Sounds_ {
    KNIFE_ATTACK = 0,
    GUNSHOT_ATTACK,
    AUTOMATIC_GUN_ATTACK,
    CHAIN_CANNON_ATTACK,
    DEATH,
    EQUIP_WEAPON
};

struct Player_stats{
    std::string Nickname;
    uint32_t final_score;
    uint32_t score;
    uint32_t kills;
};

//para panel status
#define TOTAL_FACES 8
#define IMAGE_FACES_PATH "../client/panel_status/images/face"
#define MAX_HEALTH 100.0

#define TOTAL_WEAPONS 4
#define IMAGE_WEAPONS_PATH "../client/panel_status/images/weapon"

#define TOTAL_NUMBERS 10
#define IMAGE_NUMBERS_PATH "../client/panel_status/images/number"

#define TOTAL_GUARDIAS 8
#define IMAGE_GUARDIAS_PATH "../client/panel_status/images/guardia"

#define TOTAL_GUARDIAS_DEATH 4
#define IMAGE_DEATH_GUARDIAS_PATH "../client/panel_status/images/DeadGuard"

#define TOTAL_GUARDIAS_SHOOTING 1
#define IMAGE_GUARDIAS_SHOOTING_PATH "../client/panel_status/images/GuardiaShooting"

#define TOTAL_KNIFES 3
#define IMAGE_KNIFE_PATH "../client/panel_status/images/Knife"

#define TOTAL_PISTOLAS 3
#define IMAGE_PISTOLA_PATH "../client/panel_status/images/pistola"

#define TOTAL_AUTOMATICGUNS 7
#define IMAGE_AUTOMATICGUN_PATH "../client/panel_status/images/AutomaticGun"

#define TOTAL_CHAINCANNONS 3
#define IMAGE_CHAINCANNON_PATH "../client/panel_status/images/ChainCannon"

#define TOTAL_ELITE_GUARDIAS 8
#define IMAGE_ELITE_GUARDIAS_PATH "../client/panel_status/images/Elite_guard/EGuard"

#define TOTAL_GUARDIAS_MOVING 8
#define IMAGE_GUARDIAS_MOVING_PATH "../client/panel_status/images/GuardMoving"

#define TOTAL_ELITE_GUARDIAS_MOVING 8
#define IMAGE_ELITE_GUARDIAS_MOVING_PATH "../client/panel_status/images/Elite_guard/EGuardMoving"

#define TOTAL_EGUARDS_DEAD 4
#define IMAGE_EGUARDS_DEAD_PATH "../client/panel_status/images/Elite_guard/DeadEGuard"

#define TOTAL_EGUARDIAS_SHOOTING 1
#define IMAGE_EGUARDIAS_SHOOTING_PATH "../client/panel_status/images/Elite_guard/EGuardShooting"

#define TOTAL_OFFICER_GUARDIAS 8
#define IMAGE_OFFICER_GUARDIAS_PATH "../client/panel_status/images/Oficial/Officer"

#define TOTAL_OFFICER_GUARDIAS_MOVING 8
#define IMAGE_OFFICER_GUARDIAS_MOVING_PATH "../client/panel_status/images/Oficial/OfficerMoving"

#define TOTAL_OFFICER_GUARDIAS_DEAD 4
#define IMAGE_OFFICER_GUARDIAS_DEAD_PATH "../client/panel_status/images/Oficial/DeadOfficer"

#define TOTAL_OFFICER_SHOOTING 1
#define IMAGE_OFFICER_SHOOTING_PATH "../client/panel_status/images/Oficial/OfficerShooting"

#define TOTAL_BULLETS 1
#define IMAGE_BULLETS_PATH "../client/panel_status/images/BulletsOriginal"

#define TOTAL_KEYS 1
#define IMAGE_KEY_PATH "../client/panel_status/images/Key_"

#define TOTAL_AUTOMATIC_GUNS 1
#define IMAGE_AUTOMATIC_GUN_PATH "../client/panel_status/images/AutomaticGun_"

#define TOTAL_CHAIN_CANNONS 1
#define IMAGE_CHAIN_CANNON_PATH "../client/panel_status/images/ChainCannon_"

#define TOTAL_FOOD 1
#define IMAGE_FOOD_PATH "../client/panel_status/images/Food"

#define TOTAL_MEDICAL_KIT 1
#define IMAGE_MEDICAL_KIT_PATH "../client/panel_status/images/MedicalKit"

#define TOTAL_TREASURES 1
#define IMAGE_TREASURE_PATH "../client/panel_status/images/Treasure"

#define TEXTURE_PATH "../client/sprites/wall"
#define TOTAL_TEXTURES_WALLS 2 

#endif
