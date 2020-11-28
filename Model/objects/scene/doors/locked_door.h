#ifndef LOCKED_DOOR_H_
#define LOCKED_DOOR_H_

class LockedDoor {
public:
    LockedDoor();
    bool isOpened();
    void open();
    ~LockedDoor();
private:
    int is_opened;
};

#endif    // LOCKED_DOOR_H_
