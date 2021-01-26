#include "InputTextView.h"

InputTextView::InputTextView(){
    textbox.box_content="";
    textbox.active=false;
}
/*
void InputTextView::Update(){

}*/

bool InputTextView::is_active(){
    return textbox.active;
}

void InputTextView::set_active(){
    textbox.active=true;
}