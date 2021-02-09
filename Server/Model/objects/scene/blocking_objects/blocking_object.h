#ifndef BLOCKING_OBJECT_H_
#define BLOCKING_OBJECT_H_

#include "./../../object.h"
class BlockingObject: public Object {
    public:
        BlockingObject();
        virtual ~BlockingObject();
        bool isItem() override;
        bool isBlocking() override;
        Item* getItem() override;

};

#endif    // BLOCKING_OBJECT_H_
