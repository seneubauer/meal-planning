#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include "columnItem.h"
#include "editedCell.h"
#include <QSqlDatabase>
#include <QAbstractTableModel>
#include <QVector>
#include <QHash>

class tableModel : public QAbstractTableModel {
    Q_OBJECT

private:
    QVector<QVector<QVariant>> _data;
    QVector<columnItem> _columnItems;
    QHash<QModelIndex, editedCell> _editedCells;
    QString _databaseName;
    QString _tableName;
    QString _qualifiedTableName;
    QString _fieldNames;

public:
    explicit tableModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    void insertRow(int row, const QModelIndex &parent = QModelIndex());
    void removeRow(int row, const QModelIndex &parent = QModelIndex());

    bool getData(QSqlDatabase &db);
    void setDatabaseName(QString databaseName);
    void setTableName(QString tableName);
    void setColumns(QVector<columnItem> &columns);
    QHash<EditType, QVector<QString>> getSQL();

signals:
};

#endif // TABLEMODEL_H
