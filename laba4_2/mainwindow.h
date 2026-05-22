#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *event) override;  // для фона с котиком

private slots:
    void on_createButton_clicked();
    void on_sumButton_clicked();
    void on_inc1Button_clicked();
    void on_inc2Button_clicked();

    void on_pushButton_clicked();
private:
    Ui::MainWindow *ui;

    std::vector<std::vector<QLineEdit*>> matrix1Inputs;
    std::vector<std::vector<QLineEdit*>> matrix2Inputs;
    std::vector<std::vector<QLabel*>> resultLabels;

    void clearMatrixLayout(QLayout* layout, std::vector<std::vector<QLineEdit*>>& inputs);
    void clearResultLayout();

    void showWarningWithCat(const QString& message);
    bool isNumber(const QString& str);
};
#endif // MAINWINDOW_H
