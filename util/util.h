#ifndef UTIL_H
#define UTIL_H

#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QComboBox>
#include <QStandardItemModel>
#include <QtNetwork/QNetworkAccessManager>

class Util
{
public:
    Util();
    inline static QNetworkAccessManager *networkAccessManager;
    inline static QString serviceURL;
    inline static QString accessToken;
    static void PerformWebPost(QWidget *widget, QString url, QJsonObject requestObj, std::function<void (QJsonObject response)> successCallback = nullptr, std::function<void (QString errorMessage)> errorCallback = nullptr);
    static void PerformWebPost(QWidget *widget, QString url, QJsonObject requestObj, std::function<void (QJsonArray response)> successCallback = nullptr, std::function<void (QString errorMessage)> errorCallback = nullptr);
    static void InfoAlert(QString title, QString message);
    static void ErrorAlert(QString title, QString message);
    static bool WarningConfirm(QString title, QString message);
    static int Round(double value);
    static int Ceil(double value);
    static int FindInModel(QStandardItemModel *model, int item);
};

#endif // UTIL_H
