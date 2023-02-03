#include "UserContentFrame.h"
#include "ui_UserContentFrame.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include "MediaPlayerFrame.h"


UserContentFrame::UserContentFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::UserContentFrame)
{
    ui->setupUi(this);
    QHBoxLayout *hboxlayout = new QHBoxLayout();
    QLabel*   lebal_title = new QLabel();
    lebal_title->setText("title");
    hboxlayout->addWidget(lebal_title);
    hboxlayout->addStretch();
    QVBoxLayout *vboxlayout = new QVBoxLayout();
    MediaPlayerFrame*  mediaplayer = new MediaPlayerFrame();

    vboxlayout->addItem(hboxlayout);
    vboxlayout->addWidget(mediaplayer);
    vboxlayout->addStretch();
    this->setLayout(vboxlayout);
}

UserContentFrame::~UserContentFrame()
{
    delete ui;
}
