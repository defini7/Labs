#include "Main.h"
#include "TextUtils.h"

Main::Main() : QMainWindow(nullptr)
{
    setWindowTitle("Strings pt. 1");

    QWidget* central = new QWidget(this);
    QGridLayout* layout = new QGridLayout(central);

    m_InputEdit = new QTextEdit(central);
    m_OutputEdit = new QTextEdit(central);

    m_OutputEdit->setReadOnly(true);

    QLabel* taskLabel = new QLabel("Find palindromes in a text", central);

    QLabel* inputLabel = new QLabel("&Input", central);
    QLabel* outputLabel = new QLabel("&Output", central);

    inputLabel->setBuddy(m_InputEdit);
    outputLabel->setBuddy(m_OutputEdit);

    m_ClearInputBtn = new QPushButton("Clear", central);
    m_ClearOutputBtn = new QPushButton("Clear", central);

    m_InputEdit->connect(m_ClearInputBtn, SIGNAL(clicked()), SLOT(clear()));
    m_OutputEdit->connect(m_ClearOutputBtn, SIGNAL(clicked()), SLOT(clear()));

    QObject::connect(m_InputEdit, SIGNAL(textChanged()), m_OutputEdit, SLOT(clear()));

    m_ExecuteBtn = new QPushButton("Execute", central);

    connect(m_ExecuteBtn, SIGNAL(clicked()), SLOT(OnSubmit()));

    layout->setColumnStretch(3, 3);

    layout->addWidget(taskLabel, 0, 0, 1, 2);
    layout->addWidget(inputLabel, 1, 0);
    layout->addWidget(outputLabel, 1, 1);

    layout->addWidget(m_InputEdit, 2, 0);
    layout->addWidget(m_OutputEdit, 2, 1);

    layout->addWidget(m_ClearInputBtn, 3, 0);
    layout->addWidget(m_ClearOutputBtn, 3, 1);
    layout->addWidget(m_ExecuteBtn, 4, 0, 1, 2, Qt::AlignCenter);

    central->setLayout(layout);
    setCentralWidget(central);
}

void Main::OnSubmit()
{
    const QString input = m_InputEdit->toPlainText();
    const QVector<QString> palindromes = FindPalindromes(input);

    QString output;

    for (const QString& word : palindromes)
        output += word + "\n";

    m_OutputEdit->append(output);
}
