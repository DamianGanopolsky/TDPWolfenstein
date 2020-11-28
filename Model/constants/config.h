// ATENCION: config temporal (después pasar a formato YAML)

#ifndef CONFIG_H_
#define CONFIG_H_

// healers:

#define KIT_POINTS 20
#define BLOOD_POINTS 1
#define BLOOD_MINIMUN_TO_HEAL 11
#define FOOD_POINTS 10
#define MAX_LIFE 20

// weapons:

#define KNIFE_PRECISION 1 //config
#define KNIFE_ACCURACY 1 //config
#define KNIFE_DAMAGE 1 //config

#define GUN_PRECISION 1 // config
#define GUN_ACCURACY 1 // config
#define GUN_DAMAGE 1 // config 
#define GUN_BULLETS_BLAST 1
#define GUN_PERIOD_BLAST 0

#define MACHINE_GUN_PRECISION 1 // config
#define MACHINE_GUN_ACCURACY 1 // config
#define MACHINE_GUN_DAMAGE 1 // config 
#define MACHINE_GUN_BULLETS_BLAST 1/0.3
#define MACHINE_GUN_PERIOD_BLAST 1/0.3

#define CHAIN_CANNON_PRECISION 1 // config
#define CHAIN_CANNON_ACCURACY 1 // config
#define CHAIN_CANNON_DAMAGE 1 // config
#define CHAIN_CANNON_BULLETS_BLAST 5
#define CHAIN_CANNON_PERIOD_BLAST 10

#define ROCKET_LAUNCHER_PRECISION 1 // config
#define ROCKET_LAUNCHER_ACCURACY 1 // config
#define ROCKET_LAUNCHER_DAMAGE 1 // config
#define ROCKET_LAUNCHER_BULLETS_BLAST 5
#define ROCKET_LAUNCHER_PERIOD_BLAST 0

// tresures
#define CROSS_POINTS 10
#define CUP_POINTS 50
#define CROWN_POINTS 100
#define CHEST_POINTS 200

// bullets
#define NUM_BULLETS_PICKED_UP 5
#define MAX_BULLETS 10 // config

// Inition pos
#define PLAYER_INITIAL_POS_X 0 // config
#define PLAYER_INITIAL_POS_Y 0 // config

// MAP SIZE

#define MAP_WIDTH 320// config
#define MAP_HEIGHT 200 // config

#endif    // CONFIG_H_
