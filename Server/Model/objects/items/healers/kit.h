#ifndef KIT_H_
#define KIT_H_

#include "healer.h"

class Kit: public Healer {
    public:
        Kit();
        int getItemType() override;
};

#endif    // KIT_H_
