#ifndef CRELAXEDDOUBLESPINBOX_H
#define CRELAXEDDOUBLESPINBOX_H

#include <QDoubleSpinBox>
#include <QValidator>

class CRelaxedDoubleSpinBox : public QDoubleSpinBox
{
    Q_OBJECT
public:
    CRelaxedDoubleSpinBox(QWidget *parent = 0, double minVal = -100, double maxVal = 100.);
    virtual QValidator::State validate(QString &text, int &pos) const;
    double valueFromText(const QString &text) const;
private:
    bool doConvert = false;
    QString decimalStr;
};

#endif // CRELAXEDDOUBLESPINBOX_H
