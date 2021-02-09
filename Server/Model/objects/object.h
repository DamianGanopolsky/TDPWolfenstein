#ifndef OBJECT_H_
#define OBJECT_H_

class Item; 

class Object {
 public:
    Object();
    virtual ~Object();
    virtual bool isItem() = 0;
    virtual bool isBlocking() = 0;
    //virtual int getObjectType() = 0;
    virtual Item* getItem() = 0;
};

#endif    // OBJECT_H_
