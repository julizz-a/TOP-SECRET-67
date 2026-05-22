#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Установка стиля для более современного вида
    app.setStyle("Fusion");

    MainWindow window;
    window.show();

    return app.exec();
}
