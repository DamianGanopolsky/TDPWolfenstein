#ifndef DEFS_H
#define DEFS_H

#include <cstdint>


#define SUCCESS 0
#define ERROR 1
#define EXPECTED_ARGS_CLIENT 1
#define EXPECTED_ARGS_EDITOR 1

#ifndef ID
#define ID
typedef uint32_t Id;
#endif

#ifndef CONNEXION_ID
#define CONNEXION_ID
typedef uint32_t ConnectionId;
#endif

#endif