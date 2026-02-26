#pragma once

#include <QtWidgets>

void ResetTableCell(QTableWidget* table, int row, int col, double value, bool editable = true);

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

    void FillTablesRandomly(double min, double max);

signals:
    void OnResizeTrigger();
    void OnRandomTrigger();
    void OnResizeHide();

public slots:
    void PopulateMatrices(int width, int height, bool randomly);
    void GenerateOutput();

private:
    QTabWidget* m_Tabs;

    QTableWidget* m_InputTable;
    QTableWidget* m_OutputTable;

    QPushButton* m_ExecuteBtn;

};
