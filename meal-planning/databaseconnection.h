#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <QSqlDatabase>
#include <QString>

class databaseConnection
{
private:
    QString qtDriver = "QODBC";
    QString sqlDriver = "{ODBC Driver 17 for SQL Server}";

public:
    databaseConnection();
    ~databaseConnection();

    QString hostServer = "ainulindale";
    QString hostDatabase = "mealPlanning";
    QSqlDatabase db;
    bool isConnected = false;

    bool connect(QString serverAddress, QString databaseName, QString connectionName);
    void disconnect();
};

#endif // DATABASECONNECTION_H
