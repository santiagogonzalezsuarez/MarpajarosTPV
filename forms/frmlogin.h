#ifndef FRMLOGIN_H
#define FRMLOGIN_H

#include <QDialog>
#include <QScreen>
#include <QWidget>
#include <QGuiApplication>
#include <QJsonObject>

namespace Ui {
class frmLogin;
}

class frmLogin : public QDialog
{
    Q_OBJECT

public:
    explicit frmLogin(QWidget *parent = nullptr);
    ~frmLogin();

signals:
    void successfulLogin(QJsonObject login);

private slots:
    void doLogin();

private:
    Ui::frmLogin *ui;
};

#endif // FRMLOGIN_H
