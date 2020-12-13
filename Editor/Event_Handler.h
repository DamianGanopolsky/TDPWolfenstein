#include <SDL2/SDL.h>
#include "Editor.h"

class Event_Handler{
private:
    SDL_Event event;
    bool quit;

public:
    Event_Handler(){

    }

    bool handleEvents(Editor& editor);

	~Event_Handler();
};