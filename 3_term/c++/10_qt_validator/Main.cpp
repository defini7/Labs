#include "Main.h"
#include "NameValidator.h"

Main::Main() : QWidget(nullptr)
{
    // Constructing layout
    QVBoxLayout* layout = new QVBoxLayout(this);

    // Constructing name text control
    m_NameEdit = new QLineEdit;
    m_NameEdit->setValidator(new NameValidator(m_NameEdit));

    // Constructing name label
    QLabel* nameLabel = new QLabel;
    nameLabel->setText("&Name");
    nameLabel->setBuddy(m_NameEdit);

    // Constructing birthdate edit
    m_DateEdit = new QDateEdit;

    // Constructing date label
    QLabel* dateLabel = new QLabel;
    dateLabel->setText("&Date");
    dateLabel->setBuddy(m_DateEdit);

    // Constructing age spinbox
    m_AgeEdit = new QSpinBox;
    m_AgeEdit->setRange(1, 150);
    m_AgeEdit->setButtonSymbols(QSpinBox::PlusMinus);
    m_AgeEdit->setWrapping(true);

    // Constructing age label
    QLabel* ageLabel = new QLabel;
    ageLabel->setText("&Age");
    ageLabel->setBuddy(m_AgeEdit);

    // Constructing submit button
    m_SubmitButton = new QPushButton;
    m_SubmitButton->setText("Submit");

    connect(m_SubmitButton, SIGNAL(clicked()), SLOT(OnSubmit()));

    // Constructing layout
    layout->addWidget(nameLabel);
    layout->addWidget(m_NameEdit);
    layout->addWidget(dateLabel);
    layout->addWidget(m_DateEdit);
    layout->addWidget(ageLabel);
    layout->addWidget(m_AgeEdit);
    layout->addWidget(m_SubmitButton);

    setLayout(layout);
}

void Main::OnSubmit()
{
    QString name = m_NameEdit->text();
    int pos = 0;

    if (m_NameEdit->validator()->validate(name, pos) != QValidator::Acceptable)
    {
        QMessageBox::critical(this, "Name", "Name is invalid!");
        return;
    }

    const QDate today = QDate::currentDate();
    const QDate birth = m_DateEdit->date();

    if (birth > today)
    {
        QMessageBox::critical(this, tr("Birthday"), tr("Birthdate you've specified is in the future"));
        return;
    }

    int age = today.year() - m_DateEdit->date().year();

    // If the birth day/month haven't arrived yet then decrease the age
    if (QDate(today.year(), birth.month(), birth.day()) > today) age--;

    if (age == m_AgeEdit->value())
        QMessageBox::information(this, tr("Birthday"), tr("Age is correct!"));
    else
        QMessageBox::critical(this, tr("Birthday"), tr("Age you've specified is incorrect"));
}
