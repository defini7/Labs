#ifndef _MouseObserver_h_
#define _MouseObserver_h_

#include <QtGui>
#include <QtWidgets>

class MouseObserver : public QLabel
{
public:
    MouseObserver(QWidget* pwgt = 0);

protected:
    void mousePressEvent (QMouseEvent* pe) override;
    void mouseReleaseEvent(QMouseEvent* pe) override;
    void mouseMoveEvent (QMouseEvent* pe) override;

    void dumpEvent (QMouseEvent* pe, const QString& strMessage);

    QString modifiersInfo (QMouseEvent* pe );
    QString buttonsInfo (QMouseEvent* pe );
};

#endif //_MouseObserver_h_
