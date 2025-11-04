#include "Counter.hpp"

Counter::Counter(QObject* parent) : QObject(parent)
{

}

void Counter::Increment()
{
    emit OnIncrement(++m_Value);

    if (m_Value == 5)
        emit DoSomeMagicStuffOnCounterEquals5();
}


void Counter::Decrement()
{
    emit OnIncrement(--m_Value);
}
