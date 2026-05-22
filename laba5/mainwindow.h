#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "bigint.h"


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
protected:
    void resizeEvent(QResizeEvent *event) override;
private slots:
    void on_addition_clicked();
    void on_addition_assignment_clicked();
    void on_increment_prefix_clicked();
    void on_increment_postfix_clicked();
    void on_subtraction_clicked();
    void on_subtraction_assignment_clicked();
    void on_multiplication_clicked();
    void on_multiplication_assignment_clicked();
    void on_division_clicked();
    void on_division_assignment_clicked();
    void on_remainder_clicked();
    void on_remainder_assignment_clicked();
    void on_less_clicked();
    void on_more_clicked();
    void on_equals_clicked();
    void on_not_equals_clicked();
    void on_degree_clicked();
    void on_root_clicked();

    void on_Secret_clicked();


private:
    Ui::MainWindow *ui;
    mt::BigInt getFirstNumber();
    mt::BigInt getSecondNumber();
    bool validateNumber(const QString& text);
    void showResult(const QString& result);
    void showError(const QString& message);
    void showWarningWithCat(const QString& message);
};
#endif // MAINWINDOW_H
