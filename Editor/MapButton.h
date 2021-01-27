#include "SdlClasses/SdlWindow.h"


class MapButton{

private:

    SdlWindow& window;

public:

    MapButton(SdlWindow& Window);

    void render();

    bool is_clicked(int x, int y);


};