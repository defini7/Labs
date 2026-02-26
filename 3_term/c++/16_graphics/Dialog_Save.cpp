#include "Dialog_Save.hpp"

#include <QPrintDialog>

Dialog_Save::Dialog_Save(QWidget* canvas) : QDialog(canvas)
{
    QVBoxLayout* vbox = new QVBoxLayout(this);

    m_PrinterButton = new QPushButton("Print");
    m_SaveButton = new QPushButton("Save");

    m_SavePdfDialog = new Dialog_SavePDF(canvas);

    vbox->addWidget(m_PrinterButton);
    vbox->addWidget(m_SaveButton);

    setLayout(vbox);

    QObject::connect(m_PrinterButton, &QPushButton::clicked, this, [this]()
    {
        QPrintDialog dlg(this);
        dlg.exec();
    });

    QObject::connect(m_SaveButton, &QPushButton::clicked, this, [this]()
    {
        m_SavePdfDialog->exec();
    });
}
