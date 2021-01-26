#include "TextBox.h"

class InputTextView{

private:
    TextBox textbox;

public:

    InputTextView();

    void render();

    bool is_active();

    void set_active();

};