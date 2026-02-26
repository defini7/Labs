#include "Scene.hpp"

QColor MixColors(const QColor& a, const QColor& b)
{
    return QColor::fromRgbF(
        (a.redF() + b.redF()) * 0.5f,
        (a.greenF() + b.greenF()) * 0.5f,
        (a.blueF() + b.blueF()) * 0.5f);
}

QColor Scene::s_TintedGreen = Qt::green;
QColor Scene::s_TintedDarkGreen = Qt::darkGreen;
QColor Scene::s_TintedBrown = QColorConstants::Svg::brown;

Scene::Scene(QWidget* parent) : QWidget(parent)
{
    resize(800, 600);

    // Constructing a unit circle at (0,0) with radius of 1
    // to reduce computationally intensive cos/sin calls
    for (float a = 0.0f; a < 2.0f * M_PI; a += s_AngleIncrement)
        m_UnitCircle << QPointF(cosf(a), -sinf(a));

    // If no buttons were pressed then mouse position still will be tracked
    setMouseTracking(true);
}

void Scene::paintEvent(QPaintEvent* evt)
{
    QWidget::paintEvent(evt);

    QPainter ctx(this);
    ctx.setRenderHint(QPainter::RenderHint::Antialiasing);

    ctx.translate(m_MousePos);
    ctx.shear(m_Shear, 0.0f);
    ctx.scale(m_Scale, m_Scale);

    ctx.setBrush(QBrush(s_TintedGreen));
    ctx.setPen(QPen(s_TintedGreen));

    int squareSize = 200;
    QPointF bushPos(-squareSize / 2, -squareSize / 2);

    ctx.fillRect({ bushPos, bushPos + QPointF(squareSize, squareSize) }, QBrush(s_TintedGreen));

    constexpr static int s_ApplesCount = 30;

    while (bushPos.y() < squareSize / 2)
    {
        ctx.setPen(QPen(s_TintedDarkGreen));

        for (int i = 0; i < s_ApplesCount; i++)
            ctx.drawPoint(bushPos.x() + (float)i / (float)s_ApplesCount * squareSize, bushPos.y());

        ctx.setPen(QPen(s_TintedGreen));
        FillCircle(ctx, bushPos, 45.0f);
        bushPos.ry() += squareSize * 0.3f;
    }

    bushPos.ry() -= squareSize + 45.0f;

    while (bushPos.x() < squareSize / 2)
    {
        FillCircle(ctx, bushPos, 45.0f);
        bushPos.rx() += squareSize * 0.3f;
    }

    bushPos.rx() -= 45.0f;

    while (bushPos.y() < squareSize / 2)
    {
        FillCircle(ctx, bushPos, 45.0f);
        bushPos.ry() += squareSize * 0.3f;
    }

    int trunkY = squareSize / 2;

    ctx.setPen(QPen(s_TintedBrown));
    ctx.setBrush(QBrush(s_TintedBrown));

    ctx.drawLine(0, trunkY, 0, trunkY += 200);
    ctx.drawChord(QRect(-40, trunkY, 80, 100), 0, 180 * 16);
}

void Scene::mouseMoveEvent(QMouseEvent* evt)
{
    QWidget::mouseMoveEvent(evt);

    m_MousePos = evt->pos();
    QWidget::update();
}

void Scene::keyPressEvent(QKeyEvent* evt)
{
    switch (evt->key())
    {
    case Qt::Key_Left: m_Shear -= 0.1f; break;
    case Qt::Key_Right: m_Shear += 0.1f; break;
    case Qt::Key_Up: m_Scale *= 1.05f; break;
    case Qt::Key_Down: m_Scale *= 0.95f; break;
    }

    if (m_Scale < 0.0f)
        m_Scale = 0.0f;

    update();
}

void Scene::FillCircle(QPainter& ctx, const QPointF& pos, float radius)
{
    QPolygonF circle = m_UnitCircle;

    for (QPointF& v : circle)
        v *= radius;

    circle.translate(pos);
    ctx.drawPolygon(circle);
}

void Scene::SelectTint(const QColor& tint)
{
    s_TintedGreen = MixColors(Qt::green, tint);
    s_TintedDarkGreen = MixColors(Qt::darkGreen, tint);
    s_TintedBrown = MixColors(QColorConstants::Svg::brown, tint);
}
