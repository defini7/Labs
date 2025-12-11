#pragma once

#include <QtWidgets>

#include "Dialog_SavePDF.hpp"

class Dialog_Save : public QDialog
{
    Q_OBJECT

public:
    Dialog_Save(QWidget* canvas);

private:
    QPushButton* m_PrinterButton;
    QPushButton* m_SaveButton;

    Dialog_SavePDF* m_SavePdfDialog;

};
