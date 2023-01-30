#include "util.h"
#include <QMessageBox>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QJsonDocument>
#include <QStandardPaths>
#include <QStringList>
#include <QByteArray>
#include <QFile>
#include <QDir>
#include <QTextStream>

Util::Util()
{
}

void Util::PerformWebPost(QWidget *widget, QString url, QJsonObject requestObj, std::function<void (QJsonObject response)> successCallback, std::function<void (QString errorMessage)> errorCallback)
{
    QString fullUrl = Util::GetConfigString("API.URL") + url;
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
    QString fullUrl = Util::GetConfigString("API.URL") + url;
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

void Util::LoadConfig()
{
    QString fileName = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + QDir::separator() + "config.json";
    QFile file(fileName);
    if (file.open( QIODevice::ReadOnly )) {
        QByteArray bytes = file.readAll();
        file.close();

        QJsonParseError jsonError;
        QJsonDocument document = QJsonDocument::fromJson( bytes, &jsonError );
        if (jsonError.error != QJsonParseError::NoError) {
            QJsonObject newConfig;
            Util::config = newConfig;
        }
        if (document.isObject()) {
            QJsonObject loadedConfig = document.object();
            Util::config = loadedConfig;
        }
    } else {
        QJsonObject newConfig;
        Util::config = newConfig;
    }
}

void Util::SaveConfig()
{
    QDir path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    if (!path.exists()) {
        QDir().mkdir(path.path());
    }
    QString fileName = path.path() + QDir::separator() + "config.json";
    QJsonDocument document(Util::config);
    QByteArray bytes = document.toJson(QJsonDocument::Indented);
    QFile file(fileName);
    if (file.open( QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate ))
    {
        QTextStream iStream( &file );
        iStream.setEncoding(QStringConverter::Utf8);
        iStream << bytes;
        file.close();
    }
    else
    {
        QString errMsg = file.errorString();
        Util::ErrorAlert("Mar pájaros TPV", "No se ha podido guardar la configuración.\n\nNo se ha podido abrir el archivo: " + fileName + "\n\nEl mensaje de error fue: " + errMsg);
    }
}

void Util::SetConfigString(QString path, QString value)
{
    Util::config = Util::SetConfigStringPath(Util::config, path, value);
}

QJsonObject Util::SetConfigStringPath(QJsonObject obj, QString path, QString value)
{
    if (path.contains('.')) {
        QString part = path.split('.').first();
        QString remainder = path.right(path.length() - part.length() - 1);
        if (obj[part].isObject()) {
            QJsonObject objPart = obj[part].toObject();
            objPart = Util::SetConfigStringPath(objPart, remainder, value);
            obj[part] = objPart;
            return obj;
        } else {
            QJsonObject tmpObj;
            obj[part] = tmpObj;
            QJsonObject objPart = obj[part].toObject();
            objPart = Util::SetConfigStringPath(objPart, remainder, value);
            obj[part] = objPart;
            return obj;
        }
    } else {
        obj[path] = value;
        return obj;
    }

}

QString Util::GetConfigString(QString path)
{
    QStringList parts = path.split('.');
    QJsonObject obj = Util::config;
    for (QStringList::Iterator i = parts.begin(); i != parts.end(); ++i) {
        if (*i == parts.last()) {
            return obj[*i].toString(nullptr);
        } else {
            if (!obj[*i].isObject()) {
                return nullptr;
            }
            obj = obj[*i].toObject();
        }
    }
    return nullptr;
}

void Util::SetConfigInt(QString path, int value)
{
    Util::config = Util::SetConfigIntPath(Util::config, path, value);
}

QJsonObject Util::SetConfigIntPath(QJsonObject obj, QString path, int value)
{
    if (path.contains('.')) {
        QString part = path.split('.').first();
        QString remainder = path.right(path.length() - part.length() - 1);
        if (obj[part].isObject()) {
            QJsonObject objPart = obj[part].toObject();
            objPart = Util::SetConfigIntPath(objPart, remainder, value);
            obj[part] = objPart;
            return obj;
        } else {
            QJsonObject tmpObj;
            obj[part] = tmpObj;
            QJsonObject objPart = obj[part].toObject();
            objPart = Util::SetConfigIntPath(objPart, remainder, value);
            obj[part] = objPart;
            return obj;
        }
    } else {
        obj[path] = value;
        return obj;
    }
}

int Util::GetConfigInt(QString path, int defaultValue)
{
    QStringList parts = path.split('.');
    QJsonObject obj = Util::config;
    for (QStringList::Iterator i = parts.begin(); i != parts.end(); ++i) {
        if (*i == parts.last()) {
            return obj[*i].toInt(defaultValue);
        } else {
            if (!obj[*i].isObject()) {
                return defaultValue;
            }
            obj = obj[*i].toObject();
        }
    }
    return defaultValue;
}
