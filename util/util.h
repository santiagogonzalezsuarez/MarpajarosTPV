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
    inline static QString accessToken;
    static void PerformWebPost(QWidget *widget, QString url, QJsonObject requestObj, std::function<void (QJsonObject response)> successCallback = nullptr, std::function<void (QString errorMessage)> errorCallback = nullptr);
    static void PerformWebPost(QWidget *widget, QString url, QJsonObject requestObj, std::function<void (QJsonArray response)> successCallback = nullptr, std::function<void (QString errorMessage)> errorCallback = nullptr);
    static void InfoAlert(QString title, QString message);
    static void ErrorAlert(QString title, QString message);
    static bool WarningConfirm(QString title, QString message);
    static int Round(double value);
    static int Ceil(double value);
    static int FindInModel(QStandardItemModel *model, int item);
    static void LoadConfig();
    static void SaveConfig();
    static QString GetConfigString(QString path);
    static void SetConfigString(QString path, QString value);
    static QJsonObject SetConfigStringPath(QJsonObject obj, QString path, QString value);
    static int GetConfigInt(QString path, int defaultValue = 0);
    static void SetConfigInt(QString path, int value);
    static QJsonObject SetConfigIntPath(QJsonObject obj, QString path, int value);
private :
    inline static QJsonObject config;
};

#endif // UTIL_H
