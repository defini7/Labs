#include "Main.hpp"

static constexpr int MAX_TABLE_WIDTH = 10;

MainWindow::MainWindow() : QMainWindow(nullptr)
{
    setWindowTitle("Tables");

    QWidget* central = new QWidget(this);

    QVBoxLayout* layout = new QVBoxLayout(central);
    central->setLayout(layout);

    m_Table = new QTableWidget(1, 1);
    m_TableTransposed = new QTableWidget(1, 1);

    m_Tabs = new QTabWidget;

    layout->addWidget(m_Tabs);

    QIcon icon("/Users/def1ni7/Programming/qtProjects/untitled1/matrix.png");

    m_Tabs->addTab(m_Table, icon, "Matrix");
    m_Tabs->addTab(m_TableTransposed, icon, "Transposed Matrix");

    QLabel* widthLabel = new QLabel("Width:");
    QLabel* heightLabel = new QLabel("Height:");

    QComboBox* widthBox = new QComboBox;
    QComboBox* heightBox = new QComboBox;

    QHBoxLayout* widthLayout = new QHBoxLayout(central);
    widthLayout->addWidget(widthLabel);
    widthLayout->addWidget(widthBox);

    QHBoxLayout* heightLayout = new QHBoxLayout(central);
    heightLayout->addWidget(heightLabel);
    heightLayout->addWidget(heightBox);

    layout->addLayout(widthLayout);
    layout->addLayout(heightLayout);

    widthLayout->addStretch();
    heightLayout->addStretch();

    for (int i = 0; i < MAX_TABLE_WIDTH; i++)
    {
        QString s = QString::number(i);

        widthBox->addItem(s);
        heightBox->addItem(s);
    }

    connect(heightBox, &QComboBox::currentTextChanged, [this](const QString& text)
    {
        int n = text.toInt();

        m_Table->setRowCount(n);
        m_TableTransposed->setColumnCount(n);

        PopulateMatrices();
    });

    connect(widthBox, &QComboBox::currentTextChanged, [this](const QString& text)
    {
        int n = text.toInt();

        m_Table->setColumnCount(n);
        m_TableTransposed->setRowCount(n);

        PopulateMatrices();
    });

    m_Tabs->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_Tabs->setFixedSize(500, 500);

    setCentralWidget(central);

    m_Table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_Table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    m_TableTransposed->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_TableTransposed->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    PopulateMatrices();

    setFixedSize(525, 600);
}

void MainWindow::PopulateMatrices()
{
    int rows = m_Table->rowCount();
    int cols = m_Table->columnCount();

    for (int row = 0; row < rows; row++)
        for (int col = 0; col < cols; col++)
        {
            QTableWidgetItem* item1 = m_Table->item(row, col);
            QTableWidgetItem* item2 = m_TableTransposed->item(col, row);

            if (!item1)
            {
                item1 = new QTableWidgetItem();
                item1->setTextAlignment(Qt::AlignCenter);
                m_Table->setItem(row, col, item1);
            }

            if (!item2)
            {
                item2 = new QTableWidgetItem();
                item2->setTextAlignment(Qt::AlignCenter);
                m_TableTransposed->setItem(col, row, item2);
            }

            QString buf = QString::number(QRandomGenerator::global()->bounded(100));

            item1->setText(buf);
            item2->setText(buf);
        }
}
