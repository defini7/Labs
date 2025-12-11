#include "Main.hpp"

MainFrame::MainFrame() : QMainWindow(nullptr)
{
    setWindowTitle("A fully transformed tree");

    m_Scene = new Scene(this);
    m_SaveDialog = new Dialog_Save(m_Scene);

    QMenu* gnlMenu = menuBar()->addMenu("General");

    QAction* tintAct = gnlMenu->addAction("Change tint");
    QAction* saveAct = gnlMenu->addAction("Save");

    QObject::connect(tintAct, &QAction::triggered, this, [this]()
    {
        QColor tint = QColorDialog::getColor(Qt::white, this, "Choose tint");
        emit OnTintSelect(tint);
    });

    QObject::connect(saveAct, &QAction::triggered, this, [this]()
    {
        m_SaveDialog->show();
    });

    QObject::connect(this, &MainFrame::OnTintSelect, m_Scene, &Scene::SelectTint);

    resize(800, 600);
    m_Scene->setFocus();
}

void MainFrame::resizeEvent(QResizeEvent* evt)
{
    m_Scene->resize(evt->size());
}
