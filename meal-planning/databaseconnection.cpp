#include "databaseconnection.h"

databaseConnection::databaseConnection(QObject *parent) : QObject{parent} { _isConnected = false; _activeTransaction = false; }
databaseConnection::~databaseConnection() {
    disconnect();
    delete _db;
}

bool databaseConnection::connect(const QString &serverAddress, const QString &databaseName, const QString &connectionName) {

    QString connectionString = QString("Driver=%1;Server=%2;Database=%3;Trusted_Connection=Yes;").arg(_sqlDriver, serverAddress, databaseName);
    *_db = QSqlDatabase::addDatabase(_qtDriver, connectionName);
    _db->setDatabaseName(connectionString);

    _isConnected = _db->open();
    if (_isConnected) {
        emit connectionSuccess(serverAddress, databaseName, connectionName);
    } else {
        emit connectionFailure(serverAddress, databaseName, connectionName, _db->lastError().text());
    }

    return _isConnected;
}

void databaseConnection::disconnect() {
    _db->removeDatabase(_db->connectionName());
    _db->close();
    _isConnected = false;
}

bool databaseConnection::openTransaction() {
    if (_activeTransaction)
        return true;

    _activeTransaction = _db->transaction();
    if (!_activeTransaction) {
        emit transactionError(_db->lastError().text());
        _activeTransaction = false;
    }

    return _activeTransaction;
}

bool databaseConnection::commitTransaction() {
    if (!_activeTransaction)
        return false;

    if (!_db->commit()) {
        emit transactionError(_db->lastError().text());
        return false;
    }

    return true;
}

bool databaseConnection::rollbackTransaction() {
    if (!_activeTransaction)
        return false;

    if (!_db->rollback()) {
        emit transactionError(_db->lastError().text());
        return false;
    }

    return true;
}

QVector<QVector<QVariant>> databaseConnection::select(QSqlQuery &query) {
    QVector<QVector<QVariant>> output;
    if (query.exec()) {
        int fieldCount = query.record().count();
        QVector<QVariant> row;
        while (query.next()) {
            for (int i = 0; i < fieldCount; ++i) {
                row.append(query.value(i));
            }
            output.append(row);
            row.clear();
        }
        return output;
    } else {
        emit queryFailed(query);
        return output;
    }
}

QVector<QVector<QVariant>> databaseConnection::select(const QString &&sql) {
    QSqlQuery query = QSqlQuery(*_db);
    query.prepare(sql);
    return select(query);
}






























