#include "TextBox.h"
#include "SdlClasses/SdlText.h"
#include "SdlClasses/SdlWindow.h"
#include <vector>

class InputTextView{

private:
    TextBox textbox;
    SdlText texto;
    std::vector<SdlText> caracteres;
    std::vector<SDL_Texture*> texture_of_caracter;
    SdlWindow& window;
    SDL_Texture* texture_of_text;
    SDL_Texture* save_menu_texture;
    size_t max_length_file;

public:

    InputTextView(SdlWindow& Window);

    void render();

    bool is_active();

    void set_active();

    bool IsSaveButtonPressed(int x,int y);

    std::string getMapName();

    void Update(SDL_Event* event);

};