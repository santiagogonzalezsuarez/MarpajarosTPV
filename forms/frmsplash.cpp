#include "frmsplash.h"
#include "ui_frmsplash.h"

frmSplash::frmSplash(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmSplash)
{
    ui->setupUi(this);

    QRect screenGeometry = QGuiApplication::screens().at(0)->geometry();
    int x = (screenGeometry.width() - this->width()) / 2;
    int y = (screenGeometry.height() - this->height()) / 2;
    this->move(x, y);

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_TransparentForMouseEvents);

    QTimer::singleShot(1000, this, [this](){
        this->accept();
    });
}

frmSplash::~frmSplash()
{
    delete ui;
}
