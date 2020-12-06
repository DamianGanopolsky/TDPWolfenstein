#include <SDL2/SDL.h>
#include "SdlClasses/SdlWindow.h"
#include "Scene.h"


class Editor{
private:
    struct position initial_position;
    struct position final_position;
    SdlWindow& window;
    Scene scene;

public:
    Editor(SdlWindow& Window);

    void HandleLeftClickPress(SDL_Event* event);

    void draw();

    void HandleLeftClickRelease(SDL_Event* event);

	~Editor();
};