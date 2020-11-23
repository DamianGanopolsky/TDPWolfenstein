#include <QApplication>
#include "Main_window.h"

int main(int argc, char** argv) {
    QApplication a(argc, argv);
	Main_window mainWindow("../client-model/image.jpg");
    mainWindow.show();
    return a.exec();
}