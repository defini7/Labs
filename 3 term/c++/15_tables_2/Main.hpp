#pragma once

#include <QtWidgets>

#include "InputConfigDialog.hpp"
#include "InputRangeDialog.hpp"

class MainWindow : public QMainWindow
{
public:
    MainWindow();

public slots:
    void PopulateMatrices(int width, int height, bool randomly);
    void GenerateOutput();

private:
    QTabWidget* m_Tabs;

    QTableWidget* m_InputTable;
    QTableWidget* m_OutputTable;

    InputConfigDialog m_InputDialog;
    InputRangeDialog m_InputRange;

    QPushButton* m_ExecuteBtn;

};
