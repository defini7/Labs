#pragma once

#include <QWidget>
#include <QStack>
#include <QLCDNumber>
#include <QGridLayout>
#include <QPushButton>
#include <QRegularExpression>

class Calculator : public QWidget
{
Q_OBJECT

private:
    QLCDNumber* m_LcdDisplay;
    QStack<QString> m_Stack;

    QString m_Number;

public:
    Calculator(QWidget* parent = nullptr);

    QPushButton* CreateButton(const QString& text);

    void Calculate();

public slots:
    void ButtonClicked();

};
