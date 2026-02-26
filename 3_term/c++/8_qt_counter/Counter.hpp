#pragma once

#include <QtCore/QtCore>

class Counter : public QObject
{
    Q_OBJECT

public:
    Counter(QObject* parent = nullptr);

public slots:
    void Increment();
    void Decrement();

signals:
    void OnIncrement(int);
    //void OnDecrement(int);
    void DoSomeMagicStuffOnCounterEquals5();

private:
    int m_Value = 0;

};
