#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "MediaPlayerFrame.h"
#include "UserContentFrame.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mediaplayer(nullptr)
{
    ui->setupUi(this);
    initialize();
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::initialize(){
    connectEvent();
    return true;
}

void MainWindow::connectEvent(){

}

void MainWindow::unInitialize(){
    disConnectEvent();
}

void MainWindow::disConnectEvent(){

}

void MainWindow::on_btn_mycontent_clicked(){
    UserContentFrame* user_content = new UserContentFrame();
    ui->frame_content->layout()->addWidget(user_content);
    user_content->show();
    ui->frame_content->show();
}

