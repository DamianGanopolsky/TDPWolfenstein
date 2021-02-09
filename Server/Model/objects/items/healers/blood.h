#ifndef BLOOD_H_
#define BLOOD_H_

#include "healer.h"

class Blood: public Healer {
    public:
        Blood();
        int getItemType() override;
};

#endif    // BLOOD_H_
