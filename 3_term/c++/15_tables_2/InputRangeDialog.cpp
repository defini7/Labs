#include "InputRangeDialog.hpp"

InputRangeDialog::InputRangeDialog() : QDialog(nullptr)
{
    QVBoxLayout* layout = new QVBoxLayout;

    setLayout(layout);

    QLabel* minLabel = new QLabel("Min:", this);
    QLabel* maxLabel = new QLabel("Max:", this);

    m_MinEdit = new QLineEdit(this);
    m_MaxEdit = new QLineEdit(this);

    m_MinEdit->setValidator(new QDoubleValidator(m_MinEdit));
    m_MaxEdit->setValidator(new QDoubleValidator(m_MaxEdit));

    m_SubmitButton = new QPushButton("Submit", this);

    QObject::connect(m_SubmitButton, &QPushButton::clicked, this, &InputRangeDialog::accept);

    layout->addWidget(minLabel);
    layout->addWidget(m_MinEdit);
    layout->addWidget(maxLabel);
    layout->addWidget(m_MaxEdit);
    layout->addWidget(m_SubmitButton);
}

double InputRangeDialog::GetMin() const
{
    return m_MinEdit->text().toDouble();
}

double InputRangeDialog::GetMax() const
{
    return m_MaxEdit->text().toDouble();
}
