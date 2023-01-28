#include "util.h"
#include <QMessageBox>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QJsonDocument>

Util::Util()
{
}

void Util::PerformWebPost(QWidget *widget, QString url, QJsonObject requestObj, std::function<void (QJsonObject response)> successCallback, std::function<void (QString errorMessage)> errorCallback)
{
    QString fullUrl = Util::serviceURL + url;
    const QUrl requestUrl(fullUrl);
    QNetworkRequest request(requestUrl);
    if (Util::accessToken != nullptr) {
        request.setRawHeader("Access-Token", Util::accessToken.toUtf8());
    }
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonDocument doc(requestObj);
    QByteArray data = doc.toJson(QJsonDocument::Compact);
    QNetworkReply *reply = Util::networkAccessManager->post(request, data);
    bool *widgetDestroyed = new bool;
    QMetaObject::Connection connection = QObject::connect(widget, &QWidget::destroyed, [widgetDestroyed](){
        *widgetDestroyed = true;
    });
    QObject::connect(reply, &QNetworkReply::finished, [=](){
        QObject::disconnect(connection);
        if (reply->error() == QNetworkReply::NoError) {
            QJsonDocument response = QJsonDocument::fromJson(reply->readAll());
            QJsonObject responseObject = response.object();
            if (responseObject["Error"].isObject() && responseObject["Error"].toObject()["HasError"].isBool() && responseObject["Error"].toObject()["HasError"].toBool(false)) {
                QString errorMessage = responseObject["Error"].toObject()["Message"].toString("Error desconocido.");
                if (!*widgetDestroyed) {
                    errorCallback(errorMessage);
                }
                delete widgetDestroyed;
            } else {
                QJsonObject responseContent = responseObject["content"].toObject();
                if (!*widgetDestroyed) {
                    successCallback(responseContent);
                }
                delete widgetDestroyed;
            }
        } else {
            QJsonDocument response = QJsonDocument::fromJson(reply->readAll());
            QString errorMessage = "Error desconocido.";
            if (!(response.isNull() || response.isEmpty())) {
                QJsonObject responseObject = response.object();
                errorMessage = responseObject["Error"].toObject()["Message"].toString("Error desconocido.");
            }
            if (errorCallback != nullptr) {
                if (!*widgetDestroyed) {
                    errorCallback(errorMessage);
                }
                delete widgetDestroyed;
            }
        }
    });
}

void Util::PerformWebPost(QWidget *widget, QString url, QJsonObject requestObj, std::function<void (QJsonArray response)> successCallback, std::function<void (QString errorMessage)> errorCallback)
{
    QString fullUrl = Util::serviceURL + url;
    const QUrl requestUrl(fullUrl);
    QNetworkRequest request(requestUrl);
    if (Util::accessToken != nullptr) {
        request.setRawHeader("Access-Token", Util::accessToken.toUtf8());
    }
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonDocument doc(requestObj);
    QByteArray data = doc.toJson(QJsonDocument::Compact);
    QNetworkReply *reply = Util::networkAccessManager->post(request, data);
    bool *widgetDestroyed = new bool;
    QMetaObject::Connection connection = QObject::connect(widget, &QWidget::destroyed, [widgetDestroyed](){
        *widgetDestroyed = true;
    });
    QObject::connect(reply, &QNetworkReply::finished, [=](){
        QObject::disconnect(connection);
        if (reply->error() == QNetworkReply::NoError) {
            QJsonDocument response = QJsonDocument::fromJson(reply->readAll());
            QJsonObject responseObject = response.object();
            if (responseObject["Error"].isObject() && responseObject["Error"].toObject()["HasError"].isBool() && responseObject["Error"].toObject()["HasError"].toBool(false)) {
                QString errorMessage = responseObject["Error"].toObject()["Message"].toString("Error desconocido.");
                if (!*widgetDestroyed) {
                    errorCallback(errorMessage);
                }
                delete widgetDestroyed;
            } else {
                QJsonArray responseContent = responseObject["content"].toArray();
                if (!*widgetDestroyed) {
                    successCallback(responseContent);
                }
                delete widgetDestroyed;
            }
        } else {
            QJsonDocument response = QJsonDocument::fromJson(reply->readAll());
            QString errorMessage = "Error desconocido.";
            if (!(response.isNull() || response.isEmpty())) {
                QJsonObject responseObject = response.object();
                errorMessage = responseObject["Error"].toObject()["Message"].toString("Error desconocido.");
            }
            if (errorCallback != nullptr) {
                if (!*widgetDestroyed) {
                    errorCallback(errorMessage);
                }
                delete widgetDestroyed;
            }
        }
    });
}

void Util::InfoAlert(QString title, QString message)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle(title);
    msgBox.setText(message);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.setIcon(QMessageBox::Information);
    msgBox.exec();
}

void Util::ErrorAlert(QString title, QString message)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle(title);
    msgBox.setText(message);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.exec();
}

bool Util::WarningConfirm(QString title, QString message)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle(title);
    msgBox.setText(message);
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    msgBox.setIcon(QMessageBox::Warning);
    if (msgBox.exec() == QMessageBox::Yes) {
        return true;
    }
    return false;
}

int Util::Round(double value) {
    value = value + 0.5 - (value<0); // x is now 55.499999...
    return (int)value;
}

int Util::Ceil(double value) {
    int inum = (int)value;
    if (value == (double)inum) {
        return inum;
    }
    return inum + 1;
}

int Util::FindInModel(QStandardItemModel *model, int item)
{
    for (int i = 0; i < model->rowCount(); ++i) {
        QVariant data = model->item(i)->data();
        if (data == item) {
            return i;
        }
    }
    return -1;
}
