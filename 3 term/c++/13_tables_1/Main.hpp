#pragma once

#include <QtWidgets>

class MainWindow : public QMainWindow
{
public:
    MainWindow();

    void PopulateMatrices();

private:
    QTabWidget* m_Tabs;

    QTableWidget* m_Table;
    QTableWidget* m_TableTransposed;

};
