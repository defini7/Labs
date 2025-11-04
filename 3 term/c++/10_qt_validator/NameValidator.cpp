#include "NameValidator.h"

NameValidator::NameValidator(QObject* parent) : QValidator(parent)
{

}

NameValidator::State NameValidator::validate(QString& input, int& pos) const
{
    Q_UNUSED(pos)

    if (input.isEmpty())
        return Intermediate;

    // Tests:
    // Anna-Maria Barr-M
    // Anna Barr
    // Anna-Maria Barr
    // Anna Maria-Barr

    static const QRegularExpression finalRe("^[A-Z][a-z]*(-[A-Z][a-z]*)? [A-Z][a-z]*(-[A-Z][a-z]*)?$");
    if (finalRe.match(input).hasMatch()) return Acceptable;

    static const QRegularExpression interRe("^[A-Z][a-z]*-?(-[A-Z][a-z]*)?((?<!-) )?( [A-Z][a-z]*-?(-[A-Z][a-z]*)?)?$");
    if (interRe.match(input).hasMatch()) return Intermediate;

    return Invalid;
}
