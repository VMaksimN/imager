#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

    void on_CalcColorButton_clicked();

    void on_NextImageToolButton_clicked();

    void on_PrevImageToolButton_clicked();

    void on_CriticalRadiusSlider_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    void log(QString message);
    void update_current_image_preview();

    std::vector<QImage> Images;
    int current_image_index;
};

#endif // MAINWINDOW_H
