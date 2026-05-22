#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QRegularExpression>
#include <QMessageBox>
#include <QDateTime>
#include <stdexcept>
#include <QResizeEvent>
#include <QPixmap>
#include <QPalette>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

   setWindowTitle("Калькулятор v1.0");

    this->setStyleSheet(
        "QLabel, QPushButton, QGroupBox, QLineEdit {"
        "   color: #000000;"
        "}"
        "QLineEdit, QTextBrowser {"
        "   background-color: #ffffff;"
        "   color: #000000;"
        "}"
        );

    ui->Secret->setStyleSheet(
        "QPushButton {"
        "   background-color: transparent;"
        "   border: none;"
        "   color: #000000;"
        "}"
        "QPushButton:hover {"
        "   background-color: rgba(200, 200, 200, 50);"
        "}"
        );

    QPixmap bkgnd("C:/Users/user/Documents/lab5/1642658051_1-abrakadabra-fun-p-kotiki-milie-nyashnie-multyashnie-8.png");
    if (!bkgnd.isNull()) {
        bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        QPalette palette;
        palette.setBrush(QPalette::Window, bkgnd);
        this->setPalette(palette);
    }
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

    QPixmap catPixmap("");
    if (!catPixmap.isNull()) {
        catPixmap = catPixmap.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        msgBox.setIconPixmap(catPixmap);
    }
}

mt::BigInt MainWindow::getFirstNumber() {
    QString text = ui->input_number_1->text().trimmed();
    if (text.isEmpty()) {
        throw std::runtime_error("Первое число не введено");
    }
    if (!validateNumber(text)) {
        throw std::runtime_error("Неправильно введено 1 число");
    }
    if (text.length()>=1000) {
        throw std::runtime_error("1 число слишком длинное");
    }
    return mt::BigInt(text.toStdString());
}

mt::BigInt MainWindow::getSecondNumber() {
    QString text = ui->input_number_2->text().trimmed();
    if (text.isEmpty()) {
        throw std::runtime_error("Второе число не введено");
    }
    if (!validateNumber(text)) {
        throw std::runtime_error("Неправильно введено 2 число");
    }
    if (text.length()>=1000) {
        throw std::runtime_error("2 число слишком длинное");
    }
    return mt::BigInt(text.toStdString());
}

bool MainWindow::validateNumber(const QString& text) {
    if (text.isEmpty()) return true;
    for (int i = 0; i < text.length(); ++i) {
        QChar ch = text[i];

        if (i == 0 && ch == '-') {
            continue;
        }

        if (!ch.isDigit()) {
            return false;
        }
    }
    if (text.startsWith('-') && text.length() == 1) {
        return false;
    }
    return true;
}

void MainWindow::showResult(const QString& result) {
    ui->result->setText(result);
}

void MainWindow::showError(const QString& message) {
    ui->error_output->setPlainText((QString("%1").arg(message)));
}

void MainWindow::on_addition_clicked()
{
    try {
        mt::BigInt a = getFirstNumber();
        mt::BigInt b = getSecondNumber();
        mt::BigInt result = a + b;
        showResult(QString::fromStdString(result.toString()));
        showError(QString(" "));
    } catch (const std::exception& e) {
        showError(e.what());
    }
}


void MainWindow::on_addition_assignment_clicked()
{
    try {
        mt::BigInt a = getFirstNumber();
        mt::BigInt b = getSecondNumber();
        a += b;
        ui->input_number_1->setText((QString::fromStdString(a.toString())));
        showError(QString(" "));
    } catch (const std::exception& e) {
        showError(e.what());
    }
}


void MainWindow::on_increment_prefix_clicked()
{
    try {
        mt::BigInt a = getFirstNumber();
        ++a;
        ui->input_number_1->setText((QString::fromStdString(a.toString())));
        showError(QString(" "));
    } catch (const std::exception& e) {
        showError(e.what());
    }
}


void MainWindow::on_increment_postfix_clicked()
{
    try {
        mt::BigInt b = getSecondNumber();
        b++;
        ui->input_number_2->setText((QString::fromStdString(b.toString())));
        showError(QString(" "));
    } catch (const std::exception& e) {
        showError(e.what());
    }
}


void MainWindow::on_subtraction_clicked()
{
    try {
        mt::BigInt a = getFirstNumber();
        mt::BigInt b = getSecondNumber();
        mt::BigInt result = a - b;
        showResult(QString::fromStdString(result.toString()));
        showError(QString(" "));
    } catch (const std::exception& e) {
        showError(e.what());
    }
}


void MainWindow::on_subtraction_assignment_clicked()
{
    try {
        mt::BigInt a = getFirstNumber();
        mt::BigInt b = getSecondNumber();
        a -= b;
        ui->input_number_1->setText((QString::fromStdString(a.toString())));
        showError(QString(" "));
    } catch (const std::exception& e) {
        showError(e.what());
    }
}


void MainWindow::on_multiplication_clicked()
{
    try {
        mt::BigInt a = getFirstNumber();
        mt::BigInt b = getSecondNumber();
        mt::BigInt result = a * b;
        showResult(QString::fromStdString(result.toString()));
        showError(QString(" "));
    } catch (const std::exception& e) {
        showError(e.what());
    }
}


void MainWindow::on_multiplication_assignment_clicked()
{
    try {
        mt::BigInt a = getFirstNumber();
        mt::BigInt b = getSecondNumber();
        a *= b;
        ui->input_number_1->setText((QString::fromStdString(a.toString())));
        showError(QString(" "));
    } catch (const std::exception& e) {
        showError(e.what());
    }
}


void MainWindow::on_division_clicked()
{
    try {
        mt::BigInt a = getFirstNumber();
        mt::BigInt b = getSecondNumber();
        mt::BigInt result = a / b;
        showResult(QString::fromStdString(result.toString()));
        showError(QString(" "));
    } catch (const std::exception& e) {
        showError(e.what());
    }
}


void MainWindow::on_division_assignment_clicked()
{
    try {
        mt::BigInt a = getFirstNumber();
        mt::BigInt b = getSecondNumber();
        a /= b;
        ui->input_number_1->setText((QString::fromStdString(a.toString())));
        showError(QString(" "));
    } catch (const std::exception& e) {
        showError(e.what());
    }
}


void MainWindow::on_remainder_clicked()
{
    try {
        mt::BigInt a = getFirstNumber();
        mt::BigInt b = getSecondNumber();
        mt::BigInt result = a % b;
        showResult(QString::fromStdString(result.toString()));
        showError(QString(" "));
    } catch (const std::exception& e) {
        showError(e.what());
    }
}


void MainWindow::on_remainder_assignment_clicked()
{
    try {
        mt::BigInt a = getFirstNumber();
        mt::BigInt b = getSecondNumber();
        a %= b;
        ui->input_number_1->setText((QString::fromStdString(a.toString())));
        showError(QString(" "));
    } catch (const std::exception& e) {
        showError(e.what());
    }
}




void MainWindow::on_less_clicked()
{
    try {
        mt::BigInt a = getFirstNumber();
        mt::BigInt b = getSecondNumber();

        bool result = (a < b);
        showResult(result ? "true" : "false");
    } catch (const std::exception& e) {
        showError(e.what());
    }
}


void MainWindow::on_more_clicked()
{
    try {
        mt::BigInt a = getFirstNumber();
        mt::BigInt b = getSecondNumber();

        bool result = (a > b);
        showResult(result ? "true" : "false");
    } catch (const std::exception& e) {
        showError(e.what());
    }
}


void MainWindow::on_equals_clicked()
{
    try {
        mt::BigInt a = getFirstNumber();
        mt::BigInt b = getSecondNumber();

        bool result = (a == b);
        showResult(result ? "true" : "false");
    } catch (const std::exception& e) {
        showError(e.what());
    }
}


void MainWindow::on_not_equals_clicked()
{
    try {
        mt::BigInt a = getFirstNumber();
        mt::BigInt b = getSecondNumber();

        bool result = (a != b);
        showResult(result ? "true" : "false");
    } catch (const std::exception& e) {
        showError(e.what());
    }
}


void MainWindow::on_degree_clicked()
{
    try {
        mt::BigInt a = getFirstNumber();
        mt::BigInt b = getSecondNumber();
        if (b< mt::BigInt(0)) {
            showError("Степень не может быть отрицательной");
            return;
        }
        std::string expStr = b.toString();
        int exp = std::stoi(expStr);
        mt::BigInt result = a.pow(exp);
        showResult(QString::fromStdString(result.toString()));
    } catch (const std::exception& e) {
        showError(e.what());
    }
}


void MainWindow::on_root_clicked()
{
    try {
        mt::BigInt a = getFirstNumber();
        mt::BigInt b = getSecondNumber();
        if (b< mt::BigInt(0)) {
            showError("Степень не может быть отрицательной");
            return;
        }
        std::string expStr = b.toString();
        int exp = std::stoi(expStr);
        mt::BigInt result = a.nRoot(exp);
        showResult(QString::fromStdString(result.toString()));
    } catch (const std::exception& e) {
        showError(e.what());
    }
}


void MainWindow::on_Secret_clicked()
{
    QDialog* catDialog = new QDialog(this);
    catDialog->setWindowTitle("Тык");
    catDialog->setFixedSize(500, 500);
    QVBoxLayout* layout = new QVBoxLayout(catDialog);
    QLabel* imageLabel = new QLabel();
    QPixmap catPixmap("C:/Users/user/Documents/lab5/png-klev-club-5ehf-p-milii-kot-png-21.png");

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



