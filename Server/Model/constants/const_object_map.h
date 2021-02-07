#ifndef CONST_MAPECT_MAP_H_
#define CONST_MAPECT_MAP_H_

#define POINTS_PER_CELL 64

enum ObjectsInMap {
    MAP_NONE            = 0,
    MAP_BULLET          = 1,
    MAP_BLOOD           = 2,
    MAP_FOOD            = 4,
    MAP_KIT             = 8,
    MAP_CHEST           = 16,
    MAP_CROSS           = 32,
    MAP_CROWN           = 64,
    MAP_CUP             = 128,
    MAP_CHAIN_CANNON    = 256,
    MAP_GUN             = 512,
    MAP_MACHINE_GUN     = 1024,
    MAP_KNIFE           = 2048,
    MAP_ROCKET_LAUNCHER = 4096,
    MAP_KEY             = 8192,
    MAP_BARREL          = 16384,
    MAP_TABLE           = 32768,
    MAP_WALL            = 65536,
    MAP_STAIN_BLOOD     = 131072,
    MAP_STAIN_WATER     = 262144,
    MAP_DOOR            = 524288,
    MAP_LOCKED_DOOR     = 1048576,
    MAP_PLAYER          = 2097152,

};
/*
//#define std::uint_fast24_t BITS_BULLET{0x000001}
#define std::uint_fast24_t MAP_NONE{0x000000}
//#define MAP_NONE 0
// ITEMS:
// Bullets:
#define std::uint_fast24_t MAP_BULLET{0x000001}
//#define MAP_BULLET -1
// Healers: 
#define std::uint_fast24_t MAP_BLOOD{0x000002}
//#define MAP_BLOOD -100
#define std::uint_fast24_t MAP_FOOD{0x000004}
//#define MAP_FOOD -101
#define std::uint_fast24_t MAP_KIT{0x000008}
//#define MAP_KIT -102
// Treasures:
#define std::uint_fast24_t MAP_CHEST{0x000010}
//#define MAP_CHEST -200
#define std::uint_fast24_t MAP_CROSS{0x000020}
//#define MAP_CROSS -201
#define std::uint_fast24_t MAP_CROWN{0x000040}
//#define MAP_CROWN -202
#define std::uint_fast24_t MAP_CUP{0x000080}
//#define MAP_CUP -203
// Weapons:
#define std::uint_fast24_t MAP_CHAIN_CANNON{0x000100}
//#define MAP_CHAIN_CANNON -300
#define std::uint_fast24_t MAP_GUN{0x000200}
//#define MAP_GUN -301
#define std::uint_fast24_t MAP_MACHINE_GUN{0x000400}
//#define MAP_MACHINE_GUN -302
#define std::uint_fast24_t MAP_KNIFE{0x000800}
//#define MAP_KNIFE -303
#define std::uint_fast24_t MAP_ROCKET_LAUNCHER{0x001000}
//#define MAP_ROCKET_LAUNCHER -304
// Key:
#define std::uint_fast24_t MAP_KEY{0x002000}
//#define MAP_KEY -400

// SCENE:
// blocking MAPects
#define std::uint_fast24_t MAP_BARREL{0x004000}
//#define MAP_BARREL -500
#define std::uint_fast24_t MAP_TABLE{0x008000}
//#define MAP_TABLE -501
#define std::uint_fast24_t MAP_WALL{0x010000}
//#define MAP_WALL -502
// non blocking MAPects
#define std::uint_fast24_t MAP_STAIN_BLOOD{0x020000}
//#define MAP_STAIN_BLOOD -600
#define std::uint_fast24_t MAP_STAIN_WATER{0x040000}
//#define MAP_STAIN_WATER -601
// doors
#define std::uint_fast24_t MAP_DOOR{0x080000}
//#define MAP_DOOR -700
#define std::uint_fast24_t MAP_LOCKED_DOOR{0x100000}
//#define MAP_LOCKED_DOOR -701
// hidden MAPect
#define std::uint_fast24_t MAP_SECRET_PASSAGE{0x200000}
//#define MAP_SECRET_PASSAGE -800
*/
#endif    // CONST_MAPECT_MAP_H_