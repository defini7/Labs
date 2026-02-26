#include "Main.h"
#include "TextUtils.h"
#include <QToolBar>

const QString Main::s_FileFilter = "All Files (*.*);;Text Files (*.txt)";

Main::Main() : QMainWindow(nullptr)
{
    setWindowTitle("Strings pt. 1");

    QWidget* central = new QWidget(this);
    QGridLayout* layout = new QGridLayout(central);

    m_InputEdit = new QTextEdit(central);
    m_OutputEdit = new QTextEdit(central);

    QSplitter* splitter = new QSplitter(Qt::Orientation::Horizontal, this);
    splitter->addWidget(m_InputEdit);
    splitter->addWidget(m_OutputEdit);

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

    //layout->addWidget(m_InputEdit, 2, 0);
    //layout->addWidget(m_OutputEdit, 2, 1);
    layout->addWidget(splitter, 2, 0, 1, 2);

    layout->addWidget(m_ClearInputBtn, 3, 0);
    layout->addWidget(m_ClearOutputBtn, 3, 1);
    layout->addWidget(m_ExecuteBtn, 4, 0, 1, 2, Qt::AlignCenter);

    central->setLayout(layout);
    setCentralWidget(central);

    QMenu* fileMenu = menuBar()->addMenu("&File");
    QMenu* viewMenu = menuBar()->addMenu("&View");

    fileMenu->setTearOffEnabled(true);
    viewMenu->setTearOffEnabled(true);

    QCommonStyle style;

    QAction* openFileAct = fileMenu->addAction(style.standardIcon(QStyle::SP_FileIcon), "&Open");
    QAction* saveFileAct = fileMenu->addAction(style.standardIcon(QStyle::SP_FileIcon), "&Save");

    openFileAct->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_O));
    saveFileAct->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_S));

    connect(openFileAct, &QAction::triggered, [&](bool)
    {
        QString fileName = QFileDialog::getOpenFileName(this, "Open File", "", s_FileFilter);

        if (!fileName.isEmpty())
            LoadFile(fileName);
    });

    connect(saveFileAct, &QAction::triggered, [&](bool)
    {
        QString fileName = QFileDialog::getSaveFileName(this, "Save File", "", s_FileFilter);

        if (!fileName.isEmpty())
            SaveFile(fileName);
    });

    QAction* fontAct = viewMenu->addAction("&Font");

    fontAct->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_F));

    connect(fontAct, &QAction::triggered, [&](bool)
    {
        bool ok;
        QFont font = QFontDialog::getFont(&ok, m_OutputEdit->font(), this, "Choose font");

        if (ok)
            m_OutputEdit->setFont(font);
    });

    //setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    adjustSize();
    setFixedSize(size());
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

void Main::LoadFile(const QString& fileName)
{
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream ts(&file);

    m_InputEdit->setPlainText(ts.readAll());
}

void Main::SaveFile(const QString& fileName)
{
    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream ts(&file);

    QString text = m_OutputEdit->toPlainText();
    ts << text;
}
