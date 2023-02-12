#include "util.h"
#include <QMessageBox>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QJsonDocument>
#include <QStandardPaths>
#include <QStringList>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QAbstractButton>
#include <QTimer>
#include <QList>
#include "../controls/treeitem.h"

Util::Util()
{
}

void Util::PerformWebPost(QWidget *widget, QString url, QJsonObject requestObj, std::function<void (QJsonObject response)> successCallback, std::function<void (QString errorMessage)> errorCallback)
{
    QString fullUrl = Util::GetConfigString("API.URL") + url;
    const QUrl requestUrl(fullUrl);
    QNetworkRequest request(requestUrl);
    request.setTransferTimeout(30000);
    if (Util::accessToken != nullptr) {
        request.setRawHeader("Access-Token", Util::accessToken.toUtf8());
    }
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonDocument doc(requestObj);
    QByteArray data = doc.toJson(QJsonDocument::Compact);
    QNetworkReply *reply = Util::networkAccessManager->post(request, data);
    QTimer *timer = new QTimer();
    timer->setSingleShot(true);
    QObject::connect(timer, &QTimer::timeout, widget, [=](){
        reply->disconnect();
        delete timer;
        reply->abort();
        delete reply;
        if (errorCallback != nullptr) {
            errorCallback("Ocurrió un error al realizar la solicitud a la API.");
        }
    });
    timer->start(30000);
    QObject::connect(reply, &QNetworkReply::finished, widget, [=](){
        timer->disconnect();
        delete timer;
        if (reply->error() == QNetworkReply::NoError) {
            QJsonDocument response = QJsonDocument::fromJson(reply->readAll());
            delete reply;
            QJsonObject responseObject = response.object();
            if (responseObject["Error"].isObject() && responseObject["Error"].toObject()["HasError"].isBool() && responseObject["Error"].toObject()["HasError"].toBool(false)) {
                QString errorMessage = responseObject["Error"].toObject()["Message"].toString("Error desconocido.");
                if (errorCallback != nullptr) {
                    errorCallback(errorMessage);
                }
            } else {
                QJsonObject responseContent = responseObject["content"].toObject();
                if (successCallback != nullptr) {
                    successCallback(responseContent);
                }
            }
        } else {
            QJsonDocument response = QJsonDocument::fromJson(reply->readAll());
            delete reply;
            QString errorMessage = "Error desconocido.";
            if (!(response.isNull() || response.isEmpty())) {
                QJsonObject responseObject = response.object();
                errorMessage = responseObject["Error"].toObject()["Message"].toString("Error desconocido.");
            }
            if (errorCallback != nullptr) {
                errorCallback(errorMessage);
            }
        }
    });
}

void Util::PerformWebPost(QWidget *widget, QString url, QJsonObject requestObj, std::function<void (QJsonArray response)> successCallback, std::function<void (QString errorMessage)> errorCallback)
{
    QString fullUrl = Util::GetConfigString("API.URL") + url;
    const QUrl requestUrl(fullUrl);
    QNetworkRequest request(requestUrl);
    request.setTransferTimeout(30000);
    if (Util::accessToken != nullptr) {
        request.setRawHeader("Access-Token", Util::accessToken.toUtf8());
    }
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonDocument doc(requestObj);
    QByteArray data = doc.toJson(QJsonDocument::Compact);
    QNetworkReply *reply = Util::networkAccessManager->post(request, data);
    QTimer *timer = new QTimer();
    timer->setSingleShot(true);
    QObject::connect(timer, &QTimer::timeout, widget, [=](){
        reply->disconnect();
        delete timer;
        reply->abort();
        delete reply;
        if (errorCallback != nullptr) {
            errorCallback("Ocurrió un error al realizar la solicitud a la API.");
        }
    });
    timer->start(30000);
    QObject::connect(reply, &QNetworkReply::finished, widget, [=](){
        timer->disconnect();
        delete timer;
        if (reply->error() == QNetworkReply::NoError) {
            QJsonDocument response = QJsonDocument::fromJson(reply->readAll());
            delete reply;
            QJsonObject responseObject = response.object();
            if (responseObject["Error"].isObject() && responseObject["Error"].toObject()["HasError"].isBool() && responseObject["Error"].toObject()["HasError"].toBool(false)) {
                QString errorMessage = responseObject["Error"].toObject()["Message"].toString("Error desconocido.");
                if (errorCallback != nullptr) {
                    errorCallback(errorMessage);
                }
            } else {
                QJsonArray responseContent = responseObject["content"].toArray();
                if (successCallback != nullptr) {
                    successCallback(responseContent);
                }
            }
        } else {
            QJsonDocument response = QJsonDocument::fromJson(reply->readAll());
            delete reply;
            QString errorMessage = "Error desconocido.";
            if (!(response.isNull() || response.isEmpty())) {
                QJsonObject responseObject = response.object();
                errorMessage = responseObject["Error"].toObject()["Message"].toString("Error desconocido.");
            }
            if (errorCallback != nullptr) {
                errorCallback(errorMessage);
            }
        }
    });
}

void Util::PerformWebPost(QWidget *widget, QString url, QJsonObject requestObj, std::function<void (QByteArray response)> successCallback, std::function<void (QString errorMessage)> errorCallback)
{
    QString fullUrl = Util::GetConfigString("API.URL") + url;
    const QUrl requestUrl(fullUrl);
    QNetworkRequest request(requestUrl);
    request.setTransferTimeout(30000);
    if (Util::accessToken != nullptr) {
        request.setRawHeader("Access-Token", Util::accessToken.toUtf8());
    }
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonDocument doc(requestObj);
    QByteArray data = doc.toJson(QJsonDocument::Compact);
    QNetworkReply *reply = Util::networkAccessManager->post(request, data);
    QTimer *timer = new QTimer();
    timer->setSingleShot(true);
    QObject::connect(timer, &QTimer::timeout, widget, [=](){
        reply->disconnect();
        delete timer;
        reply->abort();
        delete reply;
        if (errorCallback != nullptr) {
            errorCallback("Ocurrió un error al realizar la solicitud a la API.");
        }
    });
    timer->start(30000);
    QObject::connect(reply, &QNetworkReply::finished, widget, [=](){
        timer->disconnect();
        delete timer;
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray responseBytes = reply->readAll();
            delete reply;
            if (successCallback != nullptr) {
                successCallback(responseBytes);
            }
        } else {
            QJsonDocument response = QJsonDocument::fromJson(reply->readAll());
            delete reply;
            QString errorMessage = "Error desconocido.";
            if (!(response.isNull() || response.isEmpty())) {
                QJsonObject responseObject = response.object();
                errorMessage = responseObject["Error"].toObject()["Message"].toString("Error desconocido.");
            }
            if (errorCallback != nullptr) {
                errorCallback(errorMessage);
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
    QList<QAbstractButton*> buttons = msgBox.buttons();
    buttons.first()->setText("&Aceptar");
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
    QList<QAbstractButton*> buttons = msgBox.buttons();
    buttons.first()->setText("&Aceptar");
    msgBox.exec();
}

bool Util::InfoConfirm(QString title, QString message)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle(title);
    msgBox.setText(message);
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    msgBox.setIcon(QMessageBox::Warning);
    QList<QAbstractButton*> buttons = msgBox.buttons();
    buttons.first()->setText("&Sí");
    buttons.last()->setText("&No");
    if (msgBox.exec() == QMessageBox::Yes) {
        return true;
    }
    return false;
}

bool Util::WarningConfirm(QString title, QString message)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle(title);
    msgBox.setText(message);
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    msgBox.setIcon(QMessageBox::Warning);
    QList<QAbstractButton*> buttons = msgBox.buttons();
    buttons.first()->setText("&Sí");
    buttons.last()->setText("&No");
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

double Util::FixDoubleForCurrency(double value)
{
    return ((double)Util::Round(value * 100)) / 100;
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

int Util::FindInModel(QStandardItemModel *model, double item)
{
    for (int i = 0; i < model->rowCount(); ++i) {
        QVariant data = model->item(i)->data();
        if (data == item) {
            return i;
        }
    }
    return -1;
}

QModelIndex Util::FindInModel(TreeModel *model, int item)
{

    QList<QModelIndex> parents;
    QList<int> iteration;
    int i = -1;
    while (true) {
        ++i;
        QModelIndex parent;
        if (parents.count() > 0) {
            parent = parents.last();
        }
        int rows = model->rowCount(parent);
        if (i >= rows) {
            if (parents.count() < 1) {
                break;
            } else {
                parents.pop_back();
                i = iteration.last();
                iteration.pop_back();
            }
        } else {
            QModelIndex itemIndex = model->index(i, 1, parent);
            if (itemIndex.isValid()) {
                TreeItem* ti = (TreeItem*)itemIndex.internalPointer();
                if (ti->data(1).toInt(0) == item) {
                    return itemIndex;
                }
                // Si este item tiene al menos 1 hijo, el índice en fila 0 columna 0 debería ser válido.
                QModelIndex firstChild = model->index(0, 0, model->index(i, 0, parent));
                if (firstChild.isValid()) {
                    parents.push_back(model->index(i, 0, parent));
                    iteration.push_back(i);
                    i = -1;
                }
            }
        }
    }

    return QModelIndex();
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
