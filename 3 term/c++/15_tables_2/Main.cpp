#include "Main.hpp"

MainWindow::MainWindow() : QMainWindow(nullptr)
{
    setWindowTitle("Tables");

    QWidget* central = new QWidget(this);

    QGridLayout* layout = new QGridLayout(central);
    layout->setAlignment(Qt::AlignCenter);

    central->setLayout(layout);

    m_InputTable = new QTableWidget(1, 1);
    m_OutputTable = new QTableWidget(1, 1);

    m_Tabs = new QTabWidget(central);

    m_ExecuteBtn = new QPushButton("Execute", this);

    layout->setColumnStretch(0, 3);

    layout->addWidget(m_Tabs, 0, 0, 1, 3);
    layout->addWidget(m_ExecuteBtn, 1, 0, 1, 1, Qt::AlignCenter);

    m_Tabs->addTab(m_InputTable, "Input");
    m_Tabs->addTab(m_OutputTable, "Output");

    QMenuBar* mb = menuBar();

    QMenu* general = mb->addMenu("General");
    QAction* resizeAct = general->addAction("Resize");

    resize(800, 600);

    setCentralWidget(central);

    m_InputTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_InputTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    m_OutputTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_OutputTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(resizeAct, &QAction::triggered, [&](bool)
    {
        m_InputDialog.show();
    });

    QObject::connect(&m_InputDialog, &InputConfigDialog::Submitted, this, &MainWindow::PopulateMatrices);
    QObject::connect(m_ExecuteBtn, &QPushButton::clicked, this, &MainWindow::GenerateOutput);
}

void MainWindow::PopulateMatrices(int width, int height, bool randomly)
{
    m_InputTable->setColumnCount(width);
    m_InputTable->setRowCount(height);

    m_OutputTable->setColumnCount(width);
    m_OutputTable->setRowCount(height);

    auto clear = [](QTableWidget* table, int row, int col, double value, bool editable = true)
    {
        QTableWidgetItem* item = table->item(row, col);

        QString valueStr = QString::number(value);

        if (item)
            item->setText(valueStr);
        else
        {
            item = new QTableWidgetItem(valueStr);
            table->setItem(row, col, item);
        }

        if (!editable)
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    };

    if (randomly)
    {
        m_InputRange.show();

        if (m_InputRange.exec() == QDialog::Accepted)
        {
            double min = m_InputRange.GetMin();
            double max = m_InputRange.GetMax();

            for (int row = 0; row < height; row++)
                for (int col = 0; col < width; col++)
                {
                    clear(m_InputTable, row, col, QRandomGenerator::global()->bounded(max - min) + min);
                    clear(m_OutputTable, row, col, 0.0, false);
                }
        }

        m_InputRange.hide();
    }
    else
    {
        for (int row = 0; row < height; row++)
            for (int col = 0; col < width; col++)
            {
                clear(m_InputTable, row, col, 0.0);
                clear(m_OutputTable, row, col, 0.0, false);
            }
    }

    m_InputDialog.hide();
}

void MainWindow::GenerateOutput()
{
    // Если матрица симметрична,
    // то сортируем столбцы по элементам в последней строке по убыванию,
    // а иначе - по возрастанию

    int height = m_OutputTable->rowCount();
    int width = m_OutputTable->columnCount();

    QVector<QVector<double>> inp(height);
    QVector<QVector<double>> out(height);

    for (QVector<double>& row : inp) row.resize(width);
    for (QVector<double>& row : out) row.resize(width);

    for (int row = 0; row < height; row++)
        for (int col = 0; col < width; col++)
        {
            QTableWidgetItem* item = m_InputTable->item(row, col);
            inp[row][col] = item->text().toDouble();
        }

    bool sortAscending = false;

    if (width == height)
    {
        for (int i = 0; i < width && !sortAscending; ++i)
            for (int j = 0; j < width; ++j)
            {
                if (fabs(inp[i][j] - inp[j][i]) > 0.001)
                {
                    sortAscending = true;
                    break;
                }
            }
    }
    else
        sortAscending = true;

    for (int i = 0; i < width; ++i)
    {
        out[height - 2][i] = inp[height - 1][i];
        out[height - 1][i] = i;
    }

    for (int i = 0; i < width - 1; ++i)
    {
        bool swapped = false;

        for (int j = 0; j < width - 1 - i; ++j)
        {
            double a = out[height - 2][j];
            double b = out[height - 2][j + 1];

            if ((a > b && sortAscending) || (a < b && !sortAscending))
            {
                qSwap(out[height - 2][j], out[height - 2][j + 1]);
                qSwap(out[height - 1][j], out[height - 1][j + 1]);
                swapped = true;
            }
        }

        if (!swapped)
            break;
    }

    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
            out[i][j] = inp[i][(int)out[height - 1][j]];

    for (int row = 0; row < height; row++)
        for (int col = 0; col < width; col++)
        {
            QTableWidgetItem* item = m_OutputTable->item(row, col);
            item->setText(QString::number(out[row][col]));
        }
}
