#pragma once

#include <QtWidgets>

class Main : public QMainWindow
{
    Q_OBJECT

public:
    Main();

private slots:
    void OnSubmit();

private:
    QTextEdit* m_InputEdit;
    QTextEdit* m_OutputEdit;

    QPushButton* m_ClearInputBtn;
    QPushButton* m_ClearOutputBtn;

    QPushButton* m_ExecuteBtn;

};
