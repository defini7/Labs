#include "Main.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    Main window;
    window.show();

    return app.exec();
}
