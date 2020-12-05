#include <SDL2/SDL.h>


class Editor{
private:
    bool is_clicked;
    int initial_x;
    int initial_y;
    int final_x;
    int final_y;

public:
    Editor():is_clicked(false){

    }

    void HandleLeftClickPress(SDL_Event* event);

    void HandleLeftClickRelease(SDL_Event* event);

	~Editor();
};