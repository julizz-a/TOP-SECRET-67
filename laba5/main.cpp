#include "mainwindow.h"

#include <QApplication>


int main(int argc, char *argv[])
    {
        QApplication app(argc, argv);

        // Устанавливаем стиль для всего приложения
        app.setStyleSheet(
            // Скругленные кнопки
            "QPushButton {"
            "   border: 1px solid #999999;"
            "   border-radius: 10px;"        // Радиус скругления
            "   padding: 5px 10px;"
            "   background-color: #f0f0f0;"
            "}"
            "QPushButton:hover {"
            "   background-color: #e0e0e0;"
            "}"
            "QPushButton:pressed {"
            "   background-color: #d0d0d0;"
            "}"

            // Скругленные поля ввода
            "QLineEdit {"
            "   border: 1px solid #999999;"
            "   border-radius: 8px;"          // Радиус скругления
            "   padding: 3px 5px;"
            "   background-color: #ffffff;"
            "}"

            // Скругленный TextBrowser
            "QTextBrowser {"
            "   border: 1px solid #999999;"
            "   border-radius: 8px;"
            "   background-color: #ffffff;"
            "}"

            // Скругленная группа
            "QGroupBox {"
            "   border: 1px solid #999999;"
            "   border-radius: 10px;"
            "   margin-top: 10px;"
            "   padding-top: 10px;"
            "}"
            "QGroupBox::title {"
            "   subcontrol-origin: margin;"
            "   left: 10px;"
            "   padding: 0 5px;"
            "}"
            );

        MainWindow w;
        w.show();

        return app.exec();
    }
