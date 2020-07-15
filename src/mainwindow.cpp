#include "include/mainwindow.h"
#include "ui_mainwindow.h"
#include "image.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QString filepath = QFileDialog::getOpenFileName(this);
    QImage image(filepath);
    ui->ImageLabel->setPixmap(QPixmap::fromImage(image));
    this->log("Image loaded: " + filepath);
    this->log("");
}

// This function is work in progress, does nothing useful.
void MainWindow::on_CalcColorButton_clicked()
{
    // Loading image back from label
    QImage image = ui->ImageLabel->pixmap(Qt::ReturnByValueConstant()).toImage();
    QColor color = ui->kcolorbutton->color();


    this->log("Calculating colors...");

    float color_percent = float(Image::calc_color(image, 255, color)) / float(image.height() * image.width());

    this->log("Color " + color.name() + ": " + QString::number(color_percent));



    // Fill example
    //image.fill(QColor("red"));

    // Getting color of a pixel
    //this->log("Color at pixel 0,0: " + image.pixelColor(0, 0).name());

    // Getting color data as bytes
    //this->log("Bits:");
    //uchar* image_bits = image.bits();
    //this->log(QString::number(int(image_bits[0])));

    this->log("");
}

void MainWindow::log(QString message)
{
    ui->ImageInfoTextEdit->appendPlainText(message);
}
