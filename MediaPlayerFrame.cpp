#include "MediaPlayerFrame.h"
#include "ui_MediaPlayerFrame.h"

#include <QDebug>

MediaPlayerFrame::MediaPlayerFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::MediaPlayerFrame),
    m_init_(false),
    m_videoproc_change_(false),
    m_mediaplayer_(nullptr),
    m_MediaPlaylist_(nullptr),
    m_videoproc_volue_(0)
{
    ui->setupUi(this);
    initialize();
}

MediaPlayerFrame::~MediaPlayerFrame()
{
    delete ui;
}

bool MediaPlayerFrame::initialize(){
    if(!m_mediaplayer_){
        m_mediaplayer_ = new QMediaPlayer();
    }

    m_mediaplayer_->setVideoOutput(ui->widget_videorender);
    if(!m_MediaPlaylist_){
        m_MediaPlaylist_ = new QMediaPlaylist(m_mediaplayer_);
    }
    connectEvent();
    m_init_ = true;
    return true;
}

void MediaPlayerFrame::unInitialize(){
    m_init_ = false;
    disConnectEvent();
    if(m_mediaplayer_){
        delete  m_mediaplayer_;
        m_mediaplayer_ = nullptr;
    }
    if(m_MediaPlaylist_){
        delete  m_MediaPlaylist_;
        m_MediaPlaylist_ = nullptr;
    }
}

void MediaPlayerFrame::connectEvent(){
    if(!m_mediaplayer_)
        return;
    connect(m_mediaplayer_,SIGNAL(stateChanged(QMediaPlayer::State)),this,SLOT(slot_OnStateChanged(QMediaPlayer::State)));
    connect(m_mediaplayer_,SIGNAL(positionChanged(qint64)),this,SLOT(slot_OnPosChanged(qint64)));
    connect(m_mediaplayer_,SIGNAL(durationChanged(qint64)),this,SLOT(slot_OnDurationChanged(qint64)));
}

void MediaPlayerFrame::disConnectEvent(){

}

void MediaPlayerFrame::paintEvent(QPaintEvent *event){
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void MediaPlayerFrame::resizeEvent(QResizeEvent *event){
    ui->widget_videorender->setMinimumHeight(ui->widget_videorender->width()*3/4);
}

void MediaPlayerFrame::setPlayerUrl(QUrl &url){
    qDebug() << __FILE__ << __LINE__ << url;
    m_MediaPlaylist_->clear();
    m_MediaPlaylist_->addMedia(url);
    m_MediaPlaylist_->setCurrentIndex(0);
    m_mediaplayer_->setPlaylist(m_MediaPlaylist_);
    m_mediaplayer_->setVolume(20);
}

void MediaPlayerFrame::setPlayerVolume(qint64 volume){
    m_mediaplayer_->setVolume(volume);
}

void MediaPlayerFrame::setPlayStatus(ControlState status){
    switch (status){
    case PlayingState:
        m_mediaplayer_->play();
        ui->btn_control->setText("paused");
        break;
    case PausedState:
        m_mediaplayer_->pause();
        ui->btn_control->setText("start");
        break;
    case StoppedState:
        m_mediaplayer_->stop();
        break;
    default:
        break;
    }
}

void MediaPlayerFrame::slot_OnStateChanged(QMediaPlayer::State enumState){
    switch (enumState)
    {
    case QMediaPlayer::PlayingState:
        qDebug()<<"---zgm---   video playing "<< endl;
        break;
    case QMediaPlayer::PausedState:
        qDebug()<<"---zgm---   video paused "<< endl;
        break;
    case QMediaPlayer::StoppedState:
        qDebug()<<"---zgm---   video stoped "<< endl;
        break;
    default:
        break;
    }
}

void MediaPlayerFrame::slot_OnPosChanged(qint64 position){
    if(m_videoproc_change_)
        return;
    qint64  numb = position == 0? 0 :qRound((position*1000.0)/m_mediaplayer_->duration());
    qDebug()<<"---zgm---   video OnPosChanged "<< position <<endl;
    ui->hSlider_videoproc->setValue(numb);
    ui->hSlider_videoproc->setPageStep(1);
}

void MediaPlayerFrame::slot_OnDurationChanged(qint64 duration){
    ui->hSlider_videoproc->setRange(0, 1000);
}

void MediaPlayerFrame::on_btn_control_clicked(){
    QString ctrl_status = ui->btn_control->text();
    ControlState status = ControlState::StoppedState;
    if(ctrl_status == "start"){
        status = PlayingState;
    }
    else if(ctrl_status == "paused"){
        status = PausedState;
    }
    setPlayStatus(status);
}

void MediaPlayerFrame::on_hSlider_videoproc_valueChanged(int value){
    m_videoproc_volue_ = (value > 0 ? qRound((value* m_mediaplayer_->duration())/1000.0) : 0);
}

void MediaPlayerFrame::on_hSlider_videoproc_sliderPressed(){
     m_videoproc_change_ = true;
}

void MediaPlayerFrame::on_hSlider_videoproc_sliderReleased(){
    m_videoproc_change_ = false;
    m_mediaplayer_->setPosition(m_videoproc_volue_);
}
