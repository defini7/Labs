#include "MainWindow.h"

MainWindow::MainWindow() : QMainWindow()
{
    setWindowTitle("Hello, QT!");

    QWidget *central = new QWidget(this);

    m_Label = new QLabel(central);
    m_Button = new QPushButton(central);

    QGridLayout *grid = new QGridLayout(central);

    grid->addWidget(m_Label, 0, 0);
    grid->addWidget(m_Button, 1, 0);

    m_Button->setText("Click me!");
    m_Label->setAlignment(Qt::AlignCenter);

    central->setLayout(grid);

    setCentralWidget(central);

    QObject::connect(
        m_Button, &QPushButton::clicked,
        &m_Counter, &Counter::Increment);

    QObject::connect(
        &m_Counter, SIGNAL(OnIncrement(int)),
        m_Label, SLOT(setNum(int)));

    m_DecrBtn = new QPushButton();
    m_DecrBtn->show();

    QObject::connect(m_DecrBtn, SIGNAL(clicked()), &m_Counter, SLOT(Decrement()));
    //QObject::connect(&m_Counter, SIGNAL(OnDecrement(int)), m_Label, SLOT(setNum(int)));

    connect(&m_Counter, &Counter::DoSomeMagicStuffOnCounterEquals5, &QApplication::quit);
}
