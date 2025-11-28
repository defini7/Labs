#pragma once

#include <QtWidgets>

class InputRangeDialog : public QDialog
{
    Q_OBJECT

public:
    InputRangeDialog();

    double GetMin() const;
    double GetMax() const;

private:
    QLineEdit* m_MinEdit;
    QLineEdit* m_MaxEdit;

    QPushButton* m_SubmitButton;

};
