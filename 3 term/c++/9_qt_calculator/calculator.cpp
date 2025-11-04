#include "calculator.h"

Calculator::Calculator(QWidget* parent) : QWidget(parent)
{
    setWindowTitle("Calculator");
    resize(230, 200);

    m_LcdDisplay = new QLCDNumber(12);
    m_LcdDisplay->setSegmentStyle(QLCDNumber::Flat);
    m_LcdDisplay->setMinimumSize(150, 50);

    constexpr QChar buttons[4][4] =
        {{'7', '8', '9', '/'},
         {'4', '5', '6', '*'},
         {'1', '2', '3', '-'},
         {'0', '.', '=', '+'}};

    QGridLayout* topGrid = new QGridLayout;
    topGrid->addWidget(m_LcdDisplay, 0, 0, 1, 4);
    topGrid->addWidget(CreateButton("CE"), 1, 3);

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            topGrid->addWidget(CreateButton(buttons[i][j]), i + 2, j);

    setLayout(topGrid);
}

QPushButton* Calculator::CreateButton(const QString& str)
{
    QPushButton* btn = new QPushButton(str);

    btn->setMinimumSize(40, 40);
    connect(btn, SIGNAL(clicked()), this, SLOT(ButtonClicked()));

    return btn;
}

void Calculator::Calculate()
{
    double rhs = m_Stack.pop().toDouble();

    QString op = m_Stack.pop();

    double lhs = m_Stack.pop().toDouble();
    double res = 0.0;

    switch (op[0].toLatin1())
    {
    case '+': res = lhs + rhs; break;
    case '-': res = lhs - rhs; break;
    case '/':
    {
        if (rhs == 0.0)
        {
            m_LcdDisplay->display("Err");
            return;
        }
        else
            res = lhs / rhs;
    }
    break;

    case '*': res = lhs * rhs; break;
    }

    m_LcdDisplay->display(res);
}

void Calculator::ButtonClicked()
{
    QString text = ((QPushButton*)sender())->text();

    if (text == "CE")
    {
        m_Stack.clear();
        m_Number = "";
        m_LcdDisplay->display("0");
    }
    else if (text.contains(QRegularExpression("[0-9]")))
    {
        m_Number += text;
        m_LcdDisplay->display(m_Number);
    }
    else if (text == ".")
    {
        if (m_Number.count('.') == 0)
        {
            if (m_Number.isEmpty())
                m_Number = "0";

            m_Number.append('.');
            m_LcdDisplay->display(m_Number);
        }
    }
    else
    {
        if (m_Stack.count() >= 2)
        {
            m_Stack.push(QString::number(m_LcdDisplay->value()));

            Calculate();

            m_Stack.clear();
            m_Stack.push(QString::number(m_LcdDisplay->value()));

            if (text != "=")
                m_Stack.push(text);

            m_Number.clear();
        }
        else
        {
            m_Stack.push(QString::number(m_LcdDisplay->value()));
            m_Stack.push(text);

            m_Number.clear();
            m_LcdDisplay->display("0");
        }
    }
}
