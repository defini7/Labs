#ifndef MAIN_HPP
#define MAIN_HPP

#include "Scene.hpp"
#include "Dialog_Save.hpp"

class MainFrame : public QMainWindow
{
    Q_OBJECT

public:
    MainFrame();

protected:
    void resizeEvent(QResizeEvent*) override;

signals:
    void OnTintSelect(const QColor&);

private:
    Scene* m_Scene;
    Dialog_Save* m_SaveDialog;

};

#endif
