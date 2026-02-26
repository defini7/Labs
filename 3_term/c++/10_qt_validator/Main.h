#pragma once

#include <QtWidgets>

class Main : public QWidget
{
Q_OBJECT

public:
    Main();

public slots:
    void OnSubmit();

private:
    QLineEdit* m_NameEdit;
    QDateEdit* m_DateEdit;
    QSpinBox* m_AgeEdit;
    QPushButton* m_SubmitButton;

};
