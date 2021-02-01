
#include <SDL2/SDL.h>
#include "Editor.h"
#include <iostream>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
//#include "SdlClasses/SdlText.h"
#include "SdlClasses/SdlWindow.h"
#include "Event_Handler.h"
#include "YamlParser.h"
#include <fstream>  
#include <stdexcept>

class EditorManager{
private:

public:
    EditorManager();
    void start();
    ~EditorManager();
};
