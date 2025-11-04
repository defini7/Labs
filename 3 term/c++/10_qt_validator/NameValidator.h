#pragma once

#include <QtWidgets>

class NameValidator : public QValidator
{
Q_OBJECT

public:
    NameValidator(QObject* parent = nullptr);

    State validate(QString& input, int& pos) const override;
};
