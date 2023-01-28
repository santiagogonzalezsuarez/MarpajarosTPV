#ifndef FRMSPLASH_H
#define FRMSPLASH_H

#include <QDialog>
#include <QScreen>
#include <QWidget>
#include <QGuiApplication>
#include <QTimer>

namespace Ui {
class frmSplash;
}

class frmSplash : public QDialog
{
    Q_OBJECT

public:
    explicit frmSplash(QWidget *parent = nullptr);
    ~frmSplash();

private:
    Ui::frmSplash *ui;
};

#endif // FRMSPLASH_H
