#pragma once

#include <QtWidgets>

class Dialog_SavePDF : public QDialog
{
    Q_OBJECT

public:
    Dialog_SavePDF(QWidget* canvas);

private:
    QComboBox* m_OrientList;

    QRadioButton* m_ColorPrintRadio;
    QRadioButton* m_GreyScalePrintRadio;

    QPushButton* m_OkButton;

};
