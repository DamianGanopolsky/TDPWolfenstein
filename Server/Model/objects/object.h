#ifndef OBJECT_H_
#define OBJECT_H_

class Object {
 public:
    Object();
    virtual ~Object();
    virtual bool isItem() = 0;
    virtual bool isBlocking() = 0;
};

#endif    // OBJECT_H_
