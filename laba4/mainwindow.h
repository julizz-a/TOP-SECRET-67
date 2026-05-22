#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include "matrixlib.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_create_matrix_clicked();

    void on_Calculate_clicked();

    void on_increment1_clicked();

    void on_increment2_clicked();
private:
    bool ReadMatrix(mt::Matrix& matrix, QTableWidget* table);
    void showResult(const mt::Matrix& matrix);
    Ui::MainWindow *ui;
    mt::Matrix matrix1;
    mt::Matrix matrix2;
    mt::Matrix result;
};
#endif // MAINWINDOW_H
