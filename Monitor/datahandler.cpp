#include "datahandler.h"

DataHandler::DataHandler(QObject *parent) : QObject(parent)
{
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
}

QString DataHandler::buildData(const QVariantMap &map)
{
    QJsonObject json = QJsonObject::fromVariantMap(map);
    json.insert("dataRandomFlag",(int)(qrand()%99999));
    QJsonDocument document;
    document.setObject(json);
    QByteArray byte_array = document.toJson(QJsonDocument::Compact);
    QString json_str(byte_array);

    json_str = QString::number(json_str.length()).rightJustified(10,'0') + json_str;
    return json_str;
}

QJsonObject DataHandler::convertDataToJson(const QString &data)
{
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8(),&error);
    if(error.error == QJsonParseError::NoError)
        if(doc.isObject())
            return doc.object();
}
int DataHandler::getRandomNumber(int min, int max)
{
    return (int)min+qrand()%(max-min);
}

void DataHandler::handleData(QByteArray data)
{
    buffer += data;
    QString str(buffer);
    bool end = false;
    while(!end)
    {
        if( str.left(1) == "0")
        {
            int len = str.left(10).toInt();
            if(str.length() >= len)
            {
                if(len > 10)
                {
                    QString body = str.left(len + 10).right(len);
                    str = str.remove(0,len + 10);
                    QJsonObject obj = convertDataToJson(body);
                    emit newObject(obj);
                }
            }
            else if(len > str.length() && str != ""){
                qDebug() << "str" << str;
                qDebug() << "data broken";
                end = true;
            }
            else if(str == "")
                end = true;
        }
        else if(str != ""){
            qDebug() << "str" << str;
            qDebug() << "data broken";
            end = true;
        }
        if(str == "")
            end = true;

    }
    buffer = str.toUtf8();
}

