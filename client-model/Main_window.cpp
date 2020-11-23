#include "Main_window.h"
#include <QPaintEvent>
#include <QPainter>

Main_window::Main_window(std::string image_root) : image(image_root.c_str()){
    setMinimumSize(this->image.size());
}

Main_window::~Main_window() {
}

void Main_window::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    QRect rect = event->rect();
    painter.drawImage(rect, this->image);

}

