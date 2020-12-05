#include <SDL2/SDL.h>
#include "SdlWindow.h"


struct position{
    int x;
    int y;
};


class Editor{
private:
    bool is_clicked;
    struct position initial_position;
    struct position final_position;
    SdlWindow& window;
   // int initial_x;
    //int initial_y;
    //int final_x;
    //int final_y;

public:
    Editor(SdlWindow& Window):is_clicked(false),window(Window){

    }

    void HandleLeftClickPress(SDL_Event* event);

    void draw();

    void HandleLeftClickRelease(SDL_Event* event);

	~Editor();
};