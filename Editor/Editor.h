#include <SDL2/SDL.h>
#include "SdlWindow.h"
#include "Scene.h"

/*
struct position{
    int x;
    int y;
};*/


class Editor{
private:
    bool is_clicked;
    struct position initial_position;
    struct position final_position;
    SdlWindow& window;
    Scene scene;
   // int initial_x;
    //int initial_y;
    //int final_x;
    //int final_y;

public:
    Editor(SdlWindow& Window);

    void HandleLeftClickPress(SDL_Event* event);

    void draw();

    void HandleLeftClickRelease(SDL_Event* event);

	~Editor();
};