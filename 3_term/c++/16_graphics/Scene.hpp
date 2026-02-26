#pragma once

#include <QtWidgets>

QColor MixColors(const QColor& a, const QColor& b);

class Scene : public QWidget
{
    Q_OBJECT

public:
    Scene(QWidget* parent);

private:
    void paintEvent(QPaintEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void keyPressEvent(QKeyEvent*) override;

    void FillCircle(QPainter& ctx, const QPointF& pos, float radius);

public slots:
    void SelectTint(const QColor&);

private:
    QPolygonF m_UnitCircle;
    QPoint m_MousePos;

    static constexpr float s_AngleIncrement = 0.1f;

    static QColor s_TintedGreen;
    static QColor s_TintedDarkGreen;
    static QColor s_TintedBrown;

    float m_Shear = 0.0f;
    float m_Scale = 1.0f;

};
