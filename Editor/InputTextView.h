#include "TextBox.h"
#include "SdlClasses/SdlText.h"
#include "SdlClasses/SdlWindow.h"

class InputTextView{

private:
    TextBox textbox;
    SdlText texto;
    SdlWindow& window;
    SDL_Texture* texture_of_text;
    SDL_Texture* save_menu_texture;

public:

    InputTextView(SdlWindow& Window);

    void render();

    bool is_active();

    void set_active();

    void Update(SDL_Event* event);

};