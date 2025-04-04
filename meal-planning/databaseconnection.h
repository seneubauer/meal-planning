#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <QProperty>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QVariant>
#include <QVector>
#include <QString>
#include <QHash>

class databaseConnection : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString qtDriver READ getQtDriver() WRITE setQtDriver() NOTIFY qtDriverUpdated)
    Q_PROPERTY(QString sqDriver READ getSqlDriver() WRITE setSqlDriver() NOTIFY sqlDriverUpdated)


private:
    QSqlDatabase *_db;
    QString _qtDriver;
    QString _sqlDriver;
    bool _isConnected;
    bool _activeTransaction;

public:
    databaseConnection(QObject *parent = nullptr);
    ~databaseConnection();

    enum SqlDataType {
        INT,
        VARCHAR,
        SMALLDATETIME,
        REAL,
        BIT
    };

    bool connect(const QString &serverAddress, const QString &databaseName, const QString &connectionName);
    void disconnect();
    bool openTransaction();
    bool commitTransaction();
    bool rollbackTransaction();
    QVector<QVector<QVariant>> select(QSqlQuery &query);
    QVector<QVector<QVariant>> select(const QString &&sql);
    QSqlDatabase* getDB() { return _db; }
    QString getConnectionName() { if (_db) { return _db->connectionName(); } else { emit databaseMissing(); return ""; }}
    QString getServerName() { if (_db) { return _db->hostName(); } else { emit databaseMissing(); return ""; }}
    QString getDatabaseName() { if (_db) { return _db->databaseName(); } else { emit databaseMissing(); return ""; }}
    bool isConnected() { return _isConnected; }
    bool activeTransaction() { return _activeTransaction; }

    QString getQtDriver() { return _qtDriver; }
    void setQtDriver(const QString &value) {
        if (_qtDriver != value) {
            _qtDriver = value;
            emit qtDriverUpdated(_qtDriver);
        }
    }
    QString getSqlDriver() { return _sqlDriver; }
    void setSqlDriver(const QString &value) {
        if (_sqlDriver != value) {
            _sqlDriver = value;
            emit sqlDriverUpdated(_sqlDriver);
        }
    }

signals:
    void queryFinished(const QVector<QHash<QString, QVariant>> &results);
    void queryFailed(const QSqlQuery &query);
    void qtDriverUpdated(const QString &qtDriver);
    void sqlDriverUpdated(const QString &sqlDriver);
    void connectionSuccess(const QString &serverAddress, const QString &databaseName, const QString &connectionName);
    void connectionFailure(const QString &serverAddress, const QString &databaseName, const QString &connectionName, const QString &error);
    void transactionError(const QString &error);
    void databaseMissing();

};

#endif // DATABASECONNECTION_H
