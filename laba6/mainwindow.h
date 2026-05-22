#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QVector>
#include <memory>
#include "Shape.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_shapeTypeComboBox_currentIndexChanged(int index);
    void on_addButton_clicked();
    void on_calculateButton_clicked();
    void on_clearButton_clicked();

private:
    Ui::MainWindow *ui;
    QVector<std::shared_ptr<Shape>> shapes;

    void updateParamVisibility(int index);
    bool validateInputs();
    void clearInputs();
    void updateShapesList();
};

#endif // MAINWINDOW_HPP
