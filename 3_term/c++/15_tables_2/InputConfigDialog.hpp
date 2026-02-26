#pragma once

#include <QtWidgets>

class InputConfigDialog : public QDialog
{
    Q_OBJECT

public:
    InputConfigDialog();

signals:
    void Submitted(int width, int height, bool randomly);

private:
    QLineEdit* m_WidthEdit;
    QLineEdit* m_HeightEdit;

    QRadioButton* m_ManualRadio;
    QRadioButton* m_RandomRadio;

    QPushButton* m_SubmitButton;

};
