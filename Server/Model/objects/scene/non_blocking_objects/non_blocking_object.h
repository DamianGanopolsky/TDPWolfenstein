#ifndef NON_BLOCKING_OBJECT_H_
#define NON_BLOCKING_OBJECT_H_

#include "./../../object.h"
class NonBlockingObject: public Object {
 public:
    NonBlockingObject();
    virtual ~NonBlockingObject();
    bool isItem() override;
    bool isBlocking() override;
};

#endif    // NON_BLOCKING_OBJECT_H_
