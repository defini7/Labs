#pragma once

#include <QMainWindow>
#include <QtWidgets/QtWidgets>

#include "Counter.hpp"

class MainWindow : public QMainWindow
{
public:
    MainWindow();

public slots:
    void Decrement();

private:
    QLabel* m_Label;
    QPushButton* m_Button;
    QPushButton* m_DecrBtn;
    Counter m_Counter;

};
