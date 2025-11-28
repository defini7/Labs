#include <QtGui>
#include "MouseObserver.h"

class ResizeObserver : public QLabel
{
public:
    ResizeObserver(QWidget* pwgt = 0) : QLabel(pwgt)
    {
        setAlignment(Qt::AlignCenter);
    }

protected:
    void resizeEvent(QResizeEvent* pe) override
    {
        setText(QString("Resized")
            + "\n width()=" + QString::number(pe->size().width())
            + "\n height()=" + QString::number(pe->size().height())
        );
    }
};

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    MouseObserver mo;

    mo.resize(250, 130);
    mo.show();

    // Specifically on macOS we should call raise method
    // so the window pops up and it won't be hidden under all other windows
    mo.raise();

    ResizeObserver ro;

    ro.resize(250, 130);
    ro.show();

    ro.raise();

    return app.exec();
}
