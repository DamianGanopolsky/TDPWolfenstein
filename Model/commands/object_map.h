#ifndef OBJECT_MAP_H_
#define OBJECT_MAP_H_

#include "./../objects/object.h"
#include <unordered_map>

class ObjectMap {
 public:
    ObjectMap();
    Object getObject(int code);
 private:
    std::unordered_map <int,Object> map;

    void setMap();
};

#endif   // OBJECT_MAP_H_
