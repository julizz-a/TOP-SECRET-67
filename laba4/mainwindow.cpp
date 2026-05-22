#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "matrixlib.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , matrix1()
    , matrix2()
    , result()
{
    ui->setupUi(this);
}

bool MainWindow::ReadMatrix(mt::Matrix& matrix, QTableWidget* table){
    int rows = matrix.get_rows();
    int cols = matrix.get_cols();
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            QLineEdit* lineEdit = qobject_cast<QLineEdit*>(table->cellWidget(i, j));
            if (lineEdit) {
                QString text = lineEdit->text();
                bool ok;
                double v = text.toDouble(&ok);
                if (ok) {
                    //matrix.Data(i, j) = v; //?? почему не matrix.Set(i,j,v);
                    matrix.Set(i,j,v);
                    ui->error_output2->setPlainText("Матрица введена верно");
                } else {
                    ui->error_output2->setPlainText("Ошибка ввода значений матрицы");
                    return false;
                }
            }
        }
    }

    return true;
}

void MainWindow::showResult(const mt::Matrix& matrix)
{
    int rows = matrix.get_rows();
    int cols = matrix.get_cols();

    ui->Result->setRowCount(rows);
    ui->Result->setColumnCount(cols);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            double v = matrix.Data(i, j);
            QString text = QString::number(v);
            QTableWidgetItem* item = new QTableWidgetItem(text);
            item->setTextAlignment(Qt::AlignCenter);
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            ui->Result->setItem(i, j, item);
        }
    }

    ui->Result->resizeColumnsToContents();
}

MainWindow::~MainWindow()
{
    /*if (matrix1) {
        qDebug() << "Удаляем matrix1" << matrix1;
        delete matrix1;
        matrix1 = nullptr;
    }
    if (matrix2) {
        qDebug() << "Удаляем matrix2" << matrix2;
        delete matrix2;
        matrix2 = nullptr;
    }
    if (result) {
        qDebug() << "Удаляем result" << result;
        delete result;
        result = nullptr;
    }*/
    qDebug() << "Удаляем ui" << ui;
    delete ui;
}

void MainWindow::on_create_matrix_clicked()
{
    QString qa = ui->Rows->text();
    bool ok1;
    int rows = qa.toInt(&ok1);
    QString qb = ui->Cols->text();
    bool ok2;
    int cols = qb.toInt(&ok2);
    if ((!ok1) || (rows <= 0)) {
        ui->error_output1->setPlainText("Неверно введено количество строк :(");
        return;
    }
    if ((!ok2) || (cols <= 0)) {
        ui->error_output1->setPlainText("Неверно введено количество столбцов :(");
        return;
    }
    ui->error_output1->setPlainText("Матрицы созданы успешно");

    /*if (matrix1) {
        delete matrix1;
        matrix1 = nullptr;
    }
    if (matrix2) {
        delete matrix2;
        matrix2 = nullptr;
    }
    if (result) {
        delete result;
        result = nullptr;
    }*/
    matrix1 = mt::Matrix(rows, cols);
    ui->Matrix1->setRowCount(rows);
    ui->Matrix1->setColumnCount(cols);
    ui->Matrix1->setEnabled(true);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            QLineEdit *lineEdit = new QLineEdit("0");
            lineEdit->setAlignment(Qt::AlignCenter);  // текст по центру
            lineEdit->setMaximumWidth(70);            // ограничиваем ширину
            QRegularExpressionValidator* test = new QRegularExpressionValidator(lineEdit);
            lineEdit->setValidator(test);
            ui->Matrix1->setCellWidget(i, j, lineEdit);
        }
    }
    ui->Matrix1->resizeColumnsToContents();
    matrix2 = mt::Matrix(rows, cols);
    ui->Matrix2->setRowCount(rows);
    ui->Matrix2->setColumnCount(cols);
    ui->Matrix2->setEnabled(true);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            QLineEdit *lineEdit = new QLineEdit("0");
            lineEdit->setAlignment(Qt::AlignCenter);  // текст по центру
            lineEdit->setMaximumWidth(70);            // ограничиваем ширину
            QRegularExpressionValidator* test = new QRegularExpressionValidator(lineEdit);
            lineEdit->setValidator(test);
            ui->Matrix2->setCellWidget(i, j, lineEdit);
        }
    }
    ui->Matrix2->resizeColumnsToContents();
}


void MainWindow::on_Calculate_clicked()
{
    if (!ReadMatrix(matrix1, ui->Matrix1)) {
        return;
    }
    if (!ReadMatrix(matrix2, ui->Matrix2)) {
        return;
    }
    //result = new mt::Matrix(*matrix1 + *matrix2);// ??
    result= matrix1 + matrix2;
    showResult(result);
    ui->error_output2->setPlainText("Сумма матриц успешно вычислена!");
}

void MainWindow::on_increment1_clicked()
{
    /*if (!matrix1) {
        ui->error_output2->setPlainText("Сначала создайте матрицу!");
        return;
    }*/
    if (!ReadMatrix(matrix1, ui->Matrix1)) {
        return;
    }
    ++(matrix1);
    showResult(matrix1);
    ui->error_output2->setPlainText("Матрица увеличена на 1");
}


void MainWindow::on_increment2_clicked()
{
    /*if (!matrix1) {
        ui->error_output2->setPlainText("Сначала создайте матрицу!");
        return;
    }*/
    if (!ReadMatrix(matrix1, ui->Matrix1)) {
        return;
    }
    (matrix1)++;
    showResult(matrix1);
    ui->error_output2->setPlainText("Матрица увеличена на 1");
}

