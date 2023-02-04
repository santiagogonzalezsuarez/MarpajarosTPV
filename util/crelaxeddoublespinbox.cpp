#include "crelaxeddoublespinbox.h"
#include <QLocale>

CRelaxedDoubleSpinBox::CRelaxedDoubleSpinBox(QWidget *parent, double minVal, double maxVal) : QDoubleSpinBox(parent)
{
    setMinimum(minVal);
    setMaximum(maxVal);
    setAlignment(Qt::AlignRight);

    QLocale curLocale;
    decimalStr = curLocale.decimalPoint();
    doConvert = curLocale.decimalPoint() != ".";
}

QValidator::State CRelaxedDoubleSpinBox::validate(QString &text, int &pos) const
{
    QString s(text);
    if (doConvert)
        s = s.replace(".", decimalStr);
    return QDoubleSpinBox::validate(s, pos);
}

double CRelaxedDoubleSpinBox::valueFromText(const QString &text) const
{
    QString s(text);
    if (doConvert)
        s = s.replace(".", decimalStr);
    return QDoubleSpinBox::valueFromText(s);
}
