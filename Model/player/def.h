#ifndef DEF_H
#define DEF_H

#include <cstdint>

#ifndef ID
#define ID
typedef uint32_t Id;
#endif

enum Race { 
    GUARD = 0,
    SS,
    OFFICIAL
};

#endif