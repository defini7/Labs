#include "Main.hpp"

#include "InputConfigDialog.hpp"
#include "InputRangeDialog.hpp"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    InputConfigDialog inputDialog;
    InputRangeDialog inputRangeDialog;

    MainWindow window;

    QObject::connect(&window, &MainWindow::OnResizeTrigger, &inputDialog, &InputConfigDialog::show);
    QObject::connect(&inputDialog, &InputConfigDialog::Submitted, &window, &MainWindow::PopulateMatrices);

    QObject::connect(&window, &MainWindow::OnResizeHide, &inputDialog, &InputConfigDialog::hide);
    QObject::connect(&window, &MainWindow::OnRandomTrigger, &inputRangeDialog, [&]()
    {
        inputRangeDialog.show();

        if (inputRangeDialog.exec() == QDialog::Accepted)
        {
            double min = inputRangeDialog.GetMin();
            double max = inputRangeDialog.GetMax();

            window.FillTablesRandomly(min, max);
        }

        inputRangeDialog.hide();
    });

    window.show();

    return app.exec();
}
