#include "include/mainwindow.h"
#include "ui_mainwindow.h"

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

void MainWindow::on_CalcColorButton_clicked()
{
    this->log("Calculating colors...");
    this->log("Color " + ui->kcolorbutton->color().name());
    this->log("");
}

void MainWindow::log(QString message)
{
    ui->ImageInfoTextEdit->appendPlainText(message);
}
