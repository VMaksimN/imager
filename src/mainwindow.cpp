#include <cmath>

#include "include/mainwindow.h"
#include "ui_mainwindow.h"
#include "image.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->current_image_index = -1;

    // Checking if current theme is dark or bright
    QPalette current_palette = this->palette();
    QColor button_color = current_palette.color(QPalette::Active, QPalette::Button);

    if (button_color.red() + button_color.green() + button_color.blue() < 450) {
        this->log("Working in dark mode");
        ui->NextImageToolButton->setIcon(QIcon(":/icons_dark/icons/dark/go-next.svg"));
        ui->PrevImageToolButton->setIcon(QIcon(":/icons_dark/icons/dark/go-previous.svg"));
    }
    else{
        this->log("Working in bright mode");
        ui->NextImageToolButton->setIcon(QIcon(":/icons_light/icons/light/go-next.svg"));
        ui->PrevImageToolButton->setIcon(QIcon(":/icons_light/icons/light/go-previous.svg"));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QStringList filepaths = QFileDialog::getOpenFileNames(this);

    this->Images.clear();

    for (QString filepath : filepaths){
        QImage image(filepath);
        this->Images.push_back(image);
    }

    this->current_image_index = 0;
    this->update_current_image_preview();

    this->log("Image(s) loaded");
    this->log("");
}

void MainWindow::on_CalcColorButton_clicked()
{
    // Loading image back from label
    QImage image = ui->ImageLabel->pixmap(Qt::ReturnByValueConstant()).toImage();
    QColor color = ui->kcolorbutton->color();

    this->log("Calculating colors...");
    // Max sphere radius = 255 * sqrt(3) = 442
    float color_percent = float(Image::calc_color(image, ui->CriticalRadiusSlider->value(), color)) / float(image.height() * image.width());

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

void MainWindow::on_NextImageToolButton_clicked()
{
    if (this->Images.size() == 0){
        return;
    }

    this->current_image_index += 1;

    if (this->current_image_index >= this->Images.size()){
        this->current_image_index = 0;
    }

    this->update_current_image_preview();
}

void MainWindow::update_current_image_preview()
{
    ui->ImageLabel->setPixmap(QPixmap::fromImage(this->Images[this->current_image_index]));
    ui->CurrentImageLabel->setText("Image " + QString::number(current_image_index + 1) + " of " + QString::number(this->Images.size()));
}

void MainWindow::on_PrevImageToolButton_clicked()
{
    if (this->Images.size() == 0){
        return;
    }

    this->current_image_index -= 1;

    if (this->current_image_index < 0){
        this->current_image_index = this->Images.size() - 1;
    }

    this->update_current_image_preview();
}

void MainWindow::on_CriticalRadiusSlider_valueChanged(int value)
{
    ui->CriticalRadiusLabel->setText("Critical radius: " + QString::number(value));
}

// Not finished
void MainWindow::on_checkBox_stateChanged(int arg1)
{
    QImage image(290, 290, QImage::Format_RGB32);

    for (int i = 0; i < 290; i++)
    {
        for (int j = 0; j < 290; j++)
        {
            float x = i / 0.87;
            float y = j / 0.87;
            float z = 0.5 * i + 0.5 * j;
            QColor color((int)x, (int)y, (int)z);
            image.setPixelColor(i, j, color);
        }
    }

    ui->ImageLabel->setPixmap(QPixmap::fromImage(image));

}
