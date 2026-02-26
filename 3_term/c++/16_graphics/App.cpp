#include "Main.hpp"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    MainFrame frame;
    frame.show();

    return app.exec();
}
