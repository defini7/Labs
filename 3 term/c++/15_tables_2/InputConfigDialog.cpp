#include "InputConfigDialog.hpp"

InputConfigDialog::InputConfigDialog() : QDialog(nullptr)
{
    QVBoxLayout* layout = new QVBoxLayout;

    setLayout(layout);

    QLabel* widthLabel = new QLabel(this);
    widthLabel->setText("Width:");

    QLabel* heightLabel = new QLabel(this);
    heightLabel->setText("Height:");

    m_WidthEdit = new QLineEdit(this);
    m_HeightEdit = new QLineEdit(this);

    m_WidthEdit->setValidator(new QIntValidator(m_WidthEdit));
    m_HeightEdit->setValidator(new QIntValidator(m_HeightEdit));

    m_ManualRadio = new QRadioButton("Manual", this);
    m_RandomRadio = new QRadioButton("Random", this);

    m_SubmitButton = new QPushButton("Submit", this);

    layout->addWidget(widthLabel);
    layout->addWidget(m_WidthEdit);
    layout->addWidget(heightLabel);
    layout->addWidget(m_HeightEdit);
    layout->addWidget(m_ManualRadio);
    layout->addWidget(m_RandomRadio);
    layout->addWidget(m_SubmitButton);

    connect(m_SubmitButton, &QPushButton::clicked, [this](bool)
    {
        int w = m_WidthEdit->text().toInt();
        int h = m_HeightEdit->text().toInt();

        if (w < 2 || h < 2)
        {
            QMessageBox::critical(this, "Error!", "Matrix must be at least 2x2");
            return;
        }

        bool randomly = m_RandomRadio->isChecked();

        emit Submitted(w, h, randomly);
    });
}
