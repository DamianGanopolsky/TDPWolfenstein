#ifndef DOOR_H_
#define DOOR_H

#include "./../object.h"
class Door: public Object {
public:
    Door();
    bool isOpened();
    void open();
    ~Door();
private:
    int is_opened;
};

#endif    // DOOR_H_
