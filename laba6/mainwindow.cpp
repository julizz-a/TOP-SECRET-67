#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Rectangle.hpp"
#include "Circle.hpp"
#include "Triangle.hpp"

#include <QMessageBox>
#include <QDoubleValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Установка валидаторов для полей ввода
    QDoubleValidator* doubleValidator = new QDoubleValidator(0.01, 10000.0, 2, this); //QDoubleValidator ограничивает ввод только числами
    doubleValidator->setNotation(QDoubleValidator::StandardNotation);

    ui->param1LineEdit->setValidator(doubleValidator);
    ui->param2LineEdit->setValidator(doubleValidator);
    ui->param3LineEdit->setValidator(doubleValidator);

    // Установка подсказок
    ui->param1LineEdit->setPlaceholderText("Введите положительное число");
    ui->param2LineEdit->setPlaceholderText("Введите положительное число");
    ui->param3LineEdit->setPlaceholderText("Введите положительное число");

    // Начальная настройка видимости полей
    updateParamVisibility(0);

    ui->statusbar->showMessage("Готов к работе");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateParamVisibility(int index)
{
    // Сброс видимости
    ui->param2Label->setVisible(true);
    ui->param2LineEdit->setVisible(true);
    ui->param3Label->setVisible(false);
    ui->param3LineEdit->setVisible(false);

    switch (index) {
    case 0: // Прямоугольник
        ui->param1Label->setText("Ширина:");
        ui->param2Label->setText("Высота:");
        ui->param2Label->setVisible(true);
        ui->param2LineEdit->setVisible(true);
        break;

    case 1: // Круг
        ui->param1Label->setText("Радиус:");
        ui->param2Label->setVisible(false);
        ui->param2LineEdit->setVisible(false);
        break;

    case 2: // Треугольник
        ui->param1Label->setText("Сторона A:");
        ui->param2Label->setText("Сторона B:");
        ui->param3Label->setText("Сторона C:");
        ui->param3Label->setVisible(true);
        ui->param3LineEdit->setVisible(true);
        break;
    }

    clearInputs();
}

bool MainWindow::validateInputs()
{
    bool ok1, ok2, ok3;
    double val1 = ui->param1LineEdit->text().toDouble(&ok1);

    // Проверка первого параметра
    if (!ok1 || val1 <= 0) {
        QMessageBox::warning(this, "Ошибка ввода",
                             "Первый параметр должен быть положительным числом");
        ui->param1LineEdit->setFocus();
        return false;
    }

    int index = ui->shapeTypeComboBox->currentIndex();

    // Проверка в зависимости от типа фигуры
    if (index == 0) { // Прямоугольник
        double val2 = ui->param2LineEdit->text().toDouble(&ok2);
        if (!ok2 || val2 <= 0) {
            QMessageBox::warning(this, "Ошибка ввода",
                                 "Высота должна быть положительным числом");
            ui->param2LineEdit->setFocus();
            return false;
        }
    }
    else if (index == 2) { // Треугольник
        double val2 = ui->param2LineEdit->text().toDouble(&ok2);
        double val3 = ui->param3LineEdit->text().toDouble(&ok3);

        if (!ok2 || val2 <= 0) {
            QMessageBox::warning(this, "Ошибка ввода",
                                 "Сторона B должна быть положительным числом");
            ui->param2LineEdit->setFocus();
            return false;
        }

        if (!ok3 || val3 <= 0) {
            QMessageBox::warning(this, "Ошибка ввода",
                                 "Сторона C должна быть положительным числом");
            ui->param3LineEdit->setFocus();
            return false;
        }

        // Проверка существования треугольника
        Triangle testTriangle(val1, val2, val3);
        if (!testTriangle.isValid()) {
            QMessageBox::warning(this, "Ошибка",
                                 "Треугольник с такими сторонами не существует.\n"
                                 "Сумма любых двух сторон должна быть больше третьей.");
            return false;
        }
    }

    return true;
}

void MainWindow::clearInputs()
{
    ui->param1LineEdit->clear();
    ui->param2LineEdit->clear();
    ui->param3LineEdit->clear();
}

void MainWindow::updateShapesList()
{
    ui->shapesListWidget->clear();

    for (int i = 0; i < shapes.size(); ++i) {
        const auto& shape = shapes[i];
        QString itemText = QString("%1. %2 (S=%3, P=%4)")
                               .arg(i + 1)
                               .arg(shape->name())
                               .arg(shape->area())
                               .arg(shape->perimeter());

        ui->shapesListWidget->addItem(itemText);
    }

    ui->statusbar->showMessage("Список обновлен", 2000);
}

void MainWindow::on_shapeTypeComboBox_currentIndexChanged(int index)
{
    updateParamVisibility(index);
}

void MainWindow::on_addButton_clicked()
{
    if (!validateInputs()) {
        return;
    }

    int index = ui->shapeTypeComboBox->currentIndex();
    double val1 = ui->param1LineEdit->text().toDouble();
    double val2 = ui->param2LineEdit->text().toDouble();
    double val3 = ui->param3LineEdit->text().toDouble();

//std::make_shared<T> - создает объект и умный указатель на него
    std::shared_ptr<Shape> shape; //создаем объекты разных классов, но храним их через указатель на базовый класс (полиморфизм)

    try {
        switch (index) {
        case 0: // Прямоугольник
            shape = std::make_shared<Rectangle>(val1, val2);
            break;
        case 1: // Круг
            shape = std::make_shared<Circle>(val1);
            break;
        case 2: // Треугольник
            shape = std::make_shared<Triangle>(val1, val2, val3);
            break;
        }

        if (shape) {
            shapes.append(shape);
            updateShapesList();
            clearInputs();

            ui->statusbar->showMessage(QString("%1 добавлен").arg(shape->name()), 3000);
        }
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Ошибка",
                              QString("Не удалось создать фигуру: %1").arg(e.what()));
    }
}

void MainWindow::on_calculateButton_clicked()
{
    if (shapes.isEmpty()) {
        QMessageBox::information(this, "Информация",
                                 "Список фигур пуст. Добавьте хотя бы одну фигуру.");
        return;
    }

    QString result;
    double totalArea = 0;
    double totalPerimeter = 0;

    result += "ИНФОРМАЦИЯ О ВСЕХ ФИГУРАХ:\n";
    result += "\n\n";

    for (int i = 0; i < shapes.size(); ++i) {
        const auto& shape = shapes[i];
        result += QString("%1. %2\n").arg(i + 1).arg(shape->getInfo());

        totalArea += shape->area();
        totalPerimeter += shape->perimeter();
    }

    result += "\n\n";
    result += QString("ОБЩИЕ ИТОГИ:\n");
    result += QString("Всего фигур: %1\n").arg(shapes.size());
    result += QString("Суммарная площадь: %1\n").arg(totalArea);
    result += QString("Суммарный периметр: %1").arg(totalPerimeter);

    ui->resultTextEdit->setPlainText(result);
    ui->statusbar->showMessage("Расчет выполнен", 3000);
}

void MainWindow::on_clearButton_clicked()
{
    if (!shapes.isEmpty()) {
        int reply = QMessageBox::question(this, "Подтверждение",
                                          "Вы действительно хотите очистить все фигуры?",
                                          QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            shapes.clear();
            updateShapesList();
            ui->resultTextEdit->clear();
            ui->statusbar->showMessage("Список очищен", 3000);
        }
    }
}
