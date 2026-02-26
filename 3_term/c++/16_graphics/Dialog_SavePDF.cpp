#include "Dialog_SavePDF.hpp"

#include <QPrinter>
#include <QPainter>
#include <QFileDialog>
#include <QPageLayout>
#include <QPageSize>
#include <QMessageBox>

Dialog_SavePDF::Dialog_SavePDF(QWidget* canvas) : QDialog(canvas)
{
    QVBoxLayout* vbox = new QVBoxLayout(this);

    vbox->addWidget(new QLabel("Orientation:"));

    m_OrientList = new QComboBox(this);
    m_OrientList->addItem("Landscape");
    m_OrientList->addItem("Portrait");
    vbox->addWidget(m_OrientList);

    vbox->addWidget(new QLabel("Colour:"));

    m_ColorPrintRadio = new QRadioButton("Colourful", this);
    m_GreyScalePrintRadio = new QRadioButton("Greyscale", this);
    m_ColorPrintRadio->setChecked(true);
    vbox->addWidget(m_ColorPrintRadio);
    vbox->addWidget(m_GreyScalePrintRadio);

    m_OkButton = new QPushButton("Ok", this);
    vbox->addWidget(m_OkButton);

    connect(m_OkButton, &QPushButton::clicked, this, [this]()
    {
        QString filePath = QFileDialog::getSaveFileName(this, "Save to PDF", "", "PDF Files (*.pdf)");

        if (filePath.isEmpty())
            return;

        QPrinter printer;
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(filePath);

        using Orientation = QPageLayout::Orientation;
        Orientation orientation = (m_OrientList->currentIndex() == 0) ? Orientation::Landscape : Orientation::Portrait;

        static constexpr int DPI = 300;

        printer.setPageLayout(QPageLayout(QPageSize(QPageSize::A4), orientation, QMarginsF()));
        printer.setResolution(DPI);

        QRectF pagePts = printer.pageLayout().fullRect(QPageLayout::Point);
        double pxPerPoint = DPI / 72.0; // 72 points = 1 inch
        QSize imageSizePx(qRound(pagePts.width() * pxPerPoint),
                          qRound(pagePts.height() * pxPerPoint));

        QImage img(imageSizePx, QImage::Format_ARGB32);
        img.setDevicePixelRatio(1.0);
        img.fill(Qt::white);

        QWidget* canvas = static_cast<QWidget*>(parent());

        QPainter imgPainter(&img);
        QSize widgetSize = canvas->size();

        double sx = (double)imageSizePx.width() / widgetSize.width();
        double sy = (double)imageSizePx.height() / widgetSize.height();
        imgPainter.scale(sx, sy);

        canvas->render(&imgPainter);
        imgPainter.end();

        QImage outImage = m_GreyScalePrintRadio->isChecked()
                          ? img.convertToFormat(QImage::Format_Grayscale8)
                          : img;

        QPainter pdfPainter;

        if (!pdfPainter.begin(&printer))
        {
            QMessageBox::critical(this, "Error", "Cannot begin PDF painting");
            return;
        }

        QRect targetRect(0, 0, imageSizePx.width(), imageSizePx.height());
        pdfPainter.drawImage(targetRect, outImage);
        pdfPainter.end();

        accept();
    });
}
