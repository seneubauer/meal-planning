#include "databaseconnection.h"

#include <QDebug>
#include <QSqlError>

databaseConnection::databaseConnection() {}
databaseConnection::~databaseConnection() {
    disconnect();
}

bool databaseConnection::connect(QString serverAddress, QString databaseName, QString connectionName) {

    QString connStr = QString("Driver=%1;Server=%2;Database=%3;Trusted_Connection=Yes;").arg(sqlDriver, serverAddress, databaseName);
    db = QSqlDatabase::addDatabase(qtDriver, connectionName);
    db.setDatabaseName(connStr);

    isConnected = db.open();
    if (isConnected) {
        qDebug() << QString("connection to [%1].[%2] as '%3' succeeded").arg(serverAddress, databaseName, connectionName);
    } else {
        qDebug() << QString("connection to [%1].[%2] as '%3' failed").arg(serverAddress, databaseName, connectionName);
        qDebug() << db.lastError().text();
    }
    return isConnected;
}

void databaseConnection::disconnect() {
    db.close();
    isConnected = false;
}
