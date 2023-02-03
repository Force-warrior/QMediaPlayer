#ifndef MEDIAPLAYERFRAME_H
#define MEDIAPLAYERFRAME_H

#include <QFrame>
#include <QtMultimedia>
#include <QtMultimediaWidgets>

namespace Ui {
class MediaPlayerFrame;
}
enum ControlState
{
    StoppedState,
    PlayingState,
    PausedState
};
class MediaPlayerFrame : public QFrame
{
    Q_OBJECT

public:
    explicit MediaPlayerFrame(QWidget *parent = nullptr);
    ~MediaPlayerFrame();
    bool initialize();
    void unInitialize();
    void connectEvent();
    void disConnectEvent();
public:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;
public:
    void setPlayerUrl(QUrl &url);
    void setPlayerVolume(qint64 volume);
    void setPlayStatus(ControlState);
private slots:
    void slot_OnStateChanged(QMediaPlayer::State);
    void slot_OnPosChanged(qint64 position);
    void slot_OnDurationChanged(qint64 duration);

private slots:
    void on_btn_control_clicked();
    void on_hSlider_videoproc_valueChanged(int value);
    void on_hSlider_videoproc_sliderPressed();
    void on_hSlider_videoproc_sliderReleased();
private:
    Ui::MediaPlayerFrame *ui;
    QMediaPlayer* m_mediaplayer_;
    QMediaPlaylist *m_MediaPlaylist_;

    qint64 m_videoproc_volue_;
    bool m_videoproc_change_;
    bool m_init_;
};

#endif // MEDIAPLAYERFRAME_H
