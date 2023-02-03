#ifndef USERCONTENTFRAME_H
#define USERCONTENTFRAME_H

#include <QFrame>

namespace Ui {
class UserContentFrame;
}

class UserContentFrame : public QFrame
{
    Q_OBJECT

public:
    explicit UserContentFrame(QWidget *parent = nullptr);
    ~UserContentFrame();

private:
    Ui::UserContentFrame *ui;
};

#endif // USERCONTENTFRAME_H
