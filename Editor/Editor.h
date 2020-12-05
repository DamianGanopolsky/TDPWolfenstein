#include <SDL2/SDL.h>

struct position{
    int x;
    int y;
};


class Editor{
private:
    bool is_clicked;
    struct position initial_position;
    struct position final_position;
   // int initial_x;
    //int initial_y;
    //int final_x;
    //int final_y;

public:
    Editor():is_clicked(false){

    }

    void HandleLeftClickPress(SDL_Event* event);

    void HandleLeftClickRelease(SDL_Event* event);

	~Editor();
};