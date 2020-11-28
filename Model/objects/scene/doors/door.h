#ifndef DOOR_H_
#define DOOR_H_

class Door {
public:
    Door();
    bool isOpened();
    void open();
    ~Door();
private:
    int is_opened;
};

#endif    // DOOR_H_
