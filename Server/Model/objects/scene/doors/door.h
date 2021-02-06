#ifndef DOOR_H_
#define DOOR_H

#include "./../../object.h"
class Door: public Object {
public:
    Door();
    ~Door();
    bool isOpened();
    void open();
    bool isItem() override;
    bool isBlocking() override;
private:
    int is_opened;
};

#endif    // DOOR_H_
