#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "matrix.hpp"
#include <QMessageBox>
#include <QResizeEvent>
#include <QPixmap>
#include <QPalette>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->pushButton->setStyleSheet("color: red;");

    // Загружаем фото по прямому пути
    QPixmap bkgnd("C:/Users/user/Downloads/tmb_280147_892002");

    // Проверяем, загрузилось ли фото
    if (!bkgnd.isNull()) {
        // Масштабируем под размер окна
        bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

        // Устанавливаем фон через палитру
        QPalette palette;
        palette.setBrush(QPalette::Window, bkgnd);
        this->setPalette(palette);
    } else {
        // Если фото не загрузилось, устанавливаем голубой фон
        this->setStyleSheet("background-color: lightblue;");
    }
}  // для фона

bool MainWindow::isNumber(const QString& str)
{
    bool ok;
    str.toInt(&ok);
    return ok;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

}

void MainWindow::showWarningWithCat(const QString& message)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Caterror!");
    msgBox.setText(message);

    QPixmap catPixmap("C:/Users/user/Downloads/1638558088_3-koshka-top-p-samie-milie-kotiki-na-svete-3.jpg");
    if (!catPixmap.isNull()) {
        catPixmap = catPixmap.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        msgBox.setIconPixmap(catPixmap);
    }

    msgBox.exec();
}

void MainWindow::clearMatrixLayout(QLayout* layout, std::vector<std::vector<QLineEdit*>>& inputs)
{
    if (!layout) return;

    // Очищаем вектор
    for (auto& row : inputs) {
        for (auto& edit : row) {
            if (edit) delete edit;
        }
    }
    inputs.clear();
}

void MainWindow::clearResultLayout()
{
    // Очищаем результат
    for (auto& row : resultLabels) {
        for (auto& label : row) {
            if (label) delete label;
        }
    }
    resultLabels.clear();
}

void MainWindow::on_createButton_clicked()
{
    bool ok1, ok2, ok3, ok4;
    int r1 = ui->rows1Edit->text().toInt(&ok1);
    int c1 = ui->cols1Edit->text().toInt(&ok2);
    int r2 = ui->rows2Edit->text().toInt(&ok3);
    int c2 = ui->cols2Edit->text().toInt(&ok4);

    if (!ok1 || !ok2 || !ok3 || !ok4 || r1 <= 0 || c1 <= 0 || r2 <= 0 || c2 <= 0) {
        showWarningWithCat("Введите корректные положительные числа для размерностей");
        return;
    }
    // Очистка старых полей
    clearMatrixLayout(ui->matrix1Layout, matrix1Inputs);
    clearMatrixLayout(ui->matrix2Layout, matrix2Inputs);
    clearResultLayout();

    // Создание полей для матрицы 1
    matrix1Inputs.resize(r1);
    for (int i = 0; i < r1; ++i) {
        matrix1Inputs[i].resize(c1);
        for (int j = 0; j < c1; ++j) {
            matrix1Inputs[i][j] = new QLineEdit();
            matrix1Inputs[i][j]->setPlaceholderText("0");
            matrix1Inputs[i][j]->setFixedWidth(50);
            matrix1Inputs[i][j]->setAlignment(Qt::AlignCenter);
            ui->matrix1Layout->addWidget(matrix1Inputs[i][j], i, j);
        }
    }

    // Создание полей для матрицы 2
    matrix2Inputs.resize(r2);
    for (int i = 0; i < r2; ++i) {
        matrix2Inputs[i].resize(c2);
        for (int j = 0; j < c2; ++j) {
            matrix2Inputs[i][j] = new QLineEdit();
            matrix2Inputs[i][j]->setPlaceholderText("0");
            matrix2Inputs[i][j]->setFixedWidth(50);
            matrix2Inputs[i][j]->setAlignment(Qt::AlignCenter);
            ui->matrix2Layout->addWidget(matrix2Inputs[i][j], i, j);
        }
    }
}

void MainWindow::on_sumButton_clicked()
{
    QString text = matrix1Inputs[0][0]->text();

    if (!isNumber(text) && !text.isEmpty()) {
        showWarningWithCat("Введите число!");
        return;
    }
    try {
        int r1 = matrix1Inputs.size();
        int c1 = (r1 > 0) ? matrix1Inputs[0].size() : 0;
        int r2 = matrix2Inputs.size();
        int c2 = (r2 > 0) ? matrix2Inputs[0].size() : 0;

        if (r1 != r2 || c1 != c2) {
            showWarningWithCat("Размерности матриц должны совпадать для сложения");
            return;
        }

        mt::Matrix m1(r1, c1);
        mt::Matrix m2(r2, c2);

        // Заполнение матрицы 1
        for (int i = 0; i < r1; ++i) {
            for (int j = 0; j < c1; ++j) {
                bool ok;
                int val = matrix1Inputs[i][j]->text().toInt(&ok);
                if (!ok) val = 0;
                m1.Set(i, j, val);
            }
        }

        // Заполнение матрицы 2
        for (int i = 0; i < r2; ++i) {
            for (int j = 0; j < c2; ++j) {
                bool ok;
                int val = matrix2Inputs[i][j]->text().toInt(&ok);
                if (!ok) val = 0;
                m2.Set(i, j, val);
            }
        }

        // Сложение матриц
        mt::Matrix result = m1 + m2;

        // Очистка старого результата
        clearResultLayout();

        // Отображение результата
        resultLabels.resize(r1);
        QString resultText = "Результат сложения:\n";
        for (int i = 0; i < r1; ++i) {
            resultLabels[i].resize(c1);
            for (int j = 0; j < c1; ++j) {
                int val = result.Get(i, j);
                QLabel* label = new QLabel(QString::number(val));
                label->setFixedWidth(50);
                label->setAlignment(Qt::AlignCenter);
                ui->resultLayout->addWidget(label, i, j);
                resultLabels[i][j] = label;

                resultText += QString::number(val) + " ";
            }
            resultText += "\n";
        }
        ui->resultText->setText(resultText);

    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Ошибка", e.what());
    }
}

void MainWindow::on_inc1Button_clicked()
{
    int r = matrix1Inputs.size();
    int c = (r > 0) ? matrix1Inputs[0].size() : 0;

    if (r == 0) {
       showWarningWithCat("Сначала создайте матрицу");
        return;
    }

    mt::Matrix m(r, c);

    // Заполнение матрицы
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            bool ok;
            int val = matrix1Inputs[i][j]->text().toInt(&ok);
            if (!ok) val = 0;
            m.Set(i, j, val);
        }
    }

    // Префиксный инкремент
    ++m;

    // Обновление полей ввода
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            matrix1Inputs[i][j]->setText(QString::number(m.Get(i, j)));
        }
    }
}

void MainWindow::on_inc2Button_clicked()
{
    int r = matrix2Inputs.size();
    int c = (r > 0) ? matrix2Inputs[0].size() : 0;

    if (r == 0) {
        showWarningWithCat("Сначала создайте матрицу");
        return;
    }

    mt::Matrix m(r, c);

    // Заполнение матрицы
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            bool ok;
            int val = matrix2Inputs[i][j]->text().toInt(&ok);
            if (!ok) val = 0;
            m.Set(i, j, val);
        }
    }

    // Постфиксный инкремент
    m++;

    // Обновление полей ввода
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            matrix2Inputs[i][j]->setText(QString::number(m.Get(i, j)));
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    QDialog* catDialog = new QDialog(this);
    catDialog->setWindowTitle("Милый котик");
    catDialog->setFixedSize(500, 500);
    QVBoxLayout* layout = new QVBoxLayout(catDialog);
    QLabel* imageLabel = new QLabel();
    QPixmap catPixmap("C:/Users/user/Downloads/1638558088_3-koshka-top-p-samie-milie-kotiki-na-svete-3.jpg");

    if (!catPixmap.isNull()) {
        catPixmap = catPixmap.scaled(450, 400, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        imageLabel->setPixmap(catPixmap);
        imageLabel->setAlignment(Qt::AlignCenter);
    }
    layout->addWidget(imageLabel);
    QPushButton* closeButton = new QPushButton("Закрыть");
    closeButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #4CAF50;"
        "   color: white;"
        "}"
        );
    layout->addWidget(closeButton);
    connect(closeButton, &QPushButton::clicked, catDialog, &QDialog::accept);
    catDialog->exec();
}


