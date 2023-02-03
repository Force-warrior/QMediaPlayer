#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MediaPlayerFrame;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
    bool initialize();
    void unInitialize();
    void connectEvent();
    void disConnectEvent();

private slots:
    void on_btn_mycontent_clicked();

private:
    Ui::MainWindow *ui;
    MediaPlayerFrame* mediaplayer;

};
#endif // MAINWINDOW_H
