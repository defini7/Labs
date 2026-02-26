#include "MainWindow.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    MainWindow window;
    window.show();

    qDebug() << "Window class: " << window.metaObject()->className() << ", window class parent: " << window.parent();

    return app.exec();
}
