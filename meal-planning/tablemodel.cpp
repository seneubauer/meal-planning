#include "tablemodel.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

tableModel::tableModel(QObject *parent) : QAbstractTableModel{parent} {
    _editedCells = QHash<QModelIndex, editedCell> {};
    _data = QVector<QVector<QVariant>> {};
}

bool tableModel::getData(QSqlDatabase &db) {

    QSqlQuery query = QSqlQuery(db);
    query.prepare(
        "SELECT v.vitaminID, v.name, v.alias, v.healthEffects, v.solubilityTypeID "
        "FROM mealPlanning.dbo.vitamin v"
    );

    if (query.exec()) {
        _data.clear();
        QVector<QVector<QVariant>> newData;
        while (query.next()) {
            newData.append({ query.value("vitaminID").toInt(), query.value("name").toString(), query.value("alias").toString(), query.value("healthEffects").toString(), query.value("solubilityTypeID").toInt()});
        }
        qDebug() << newData;
        beginInsertRows(QModelIndex(), 1, newData.count());
        _data.append(newData);
        endInsertRows();

    } else {
        qDebug() << query.lastError().text();
        return false;
    }
    return true;
}

void tableModel::setDatabaseName(QString databaseName) {
    _databaseName = databaseName;
    _qualifiedTableName = QString("%1.dbo.%2").arg(_databaseName, _tableName);
}

void tableModel::setTableName(QString tableName) {
    _tableName = tableName;
    _qualifiedTableName = QString("%1.dbo.%2").arg(_databaseName, _tableName);
}

void tableModel::setColumns(QVector<columnItem> &columns) {
    _columnItems = columns;
    _fieldNames = "";
    for (int i = 0; i < _columnItems.count(); ++i) {
        this->setHeaderData(i, Qt::Horizontal, columns[i].label);
        _fieldNames += _columnItems[i].field + ", ";
    }
    _fieldNames.chop(2);
}

QHash<EditType, QVector<QString>> tableModel::getSQL() {

    QHash<EditType, QVector<QString>> output;
    if (_tableName == "" || _editedCells.count() == 0)
        return output;

    QModelIndex _index;

    // assemble DELETE and INSERT statement
    QString deleteWHERE;
    QString insertVALUE;
    for (int i = 0; i < this->rowCount(); ++i) {
        _index = this->index(i, 0);
        if (_editedCells.contains(_index)) {
            if (_editedCells[_index].editType == EditType::DELETE) {
                deleteWHERE += QString::number(_editedCells[_index].id) + ", ";
            } else if (_editedCells[_index].editType == EditType::INSERT) {

                insertVALUE += "\r\n(";
                for (int j = 1; j < _columnItems.count(); ++j) {
                    _index = this->index(i, j);
                    if (_columnItems[j].requiresQuotes) {
                        insertVALUE += "'" + _editedCells[_index].value.toString() + "', ";
                    } else {
                        insertVALUE += _editedCells[_index].value.toString() + ", ";
                    }
                }
                insertVALUE.chop(2);
                insertVALUE += "),";
            }
        }
    }
    deleteWHERE.chop(2);
    insertVALUE.chop(2);
    output[EditType::DELETE].append(QString("DELETE x FROM %1 x WHERE x.%2 IN (%3)").arg(_qualifiedTableName, _columnItems[0].field, deleteWHERE));
    output[EditType::INSERT].append(QString("INSERT INTO %1 (%2)\r\nVALUES\r\n%3").arg(_qualifiedTableName, _fieldNames, insertVALUE));

    // assemble UPDATE statements
    QHashIterator<QModelIndex, editedCell> iterator(_editedCells);
    while (iterator.hasNext()) {
        iterator.next();
        editedCell cell = iterator.value();
        if (cell.editType == EditType::UPDATE) {
            output[EditType::UPDATE].append(
                QString("UPDATE x SET %1 = %2 FROM %3 x WHERE x.%4 = %5").arg(cell.field, cell.value.toString(), _qualifiedTableName, _columnItems[0].field, QString::number(cell.id))
            );
        }
    }

    return output;
}

int tableModel::rowCount(const QModelIndex &parent) const {
    if (!parent.isValid())
        return 0;

    return _data.count();
}

int tableModel::columnCount(const QModelIndex &parent) const {
    if (!parent.isValid())
        return 0;

    return _data[0].count();
}

QVariant tableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::ItemDataRole::DisplayRole) {
        if (orientation == Qt::Orientation::Horizontal) {
            columnItem column = _columnItems[section];

            if (column.isPrimaryKey) {
                return QVariant();
            } else {
                return column.field;
            }

        } else {
            return QString("%1").arg(section + 1);
        }
    } else {
        return QVariant();
    }
}

void tableModel::insertRow(int row, const QModelIndex &parent) {
    if (row < 0 || row > _data.count())
        return;

    QVector<QVariant> defaultValues;
    for (int i = 1; i < _columnItems.count(); ++i) {
        defaultValues.append(_columnItems[i].defaultValue);
    }

    beginInsertRows(parent, row, row);
    _data.insert(row, defaultValues);
    endInsertRows();

    for (int i = 1; i < _columnItems.count(); ++i) {
        QModelIndex _index = this->index(row, i, parent);
        if (_editedCells.contains(_index)) {
            if (_editedCells[_index].editType == EditType::DELETE) {
                _editedCells.remove(_index);
            } else {
                _editedCells[_index].id = -1;
                _editedCells[_index].editType = EditType::INSERT;
            }
        } else {
            _editedCells.insert(this->index(row, i, parent), editedCell { -1, _columnItems[i].field, _columnItems[i].defaultValue, _columnItems[i].defaultValue, EditType::INSERT });
        }
    }
}

void tableModel::removeRow(int row, const QModelIndex &parent) {
    if (row < 0 || row > _data.count())
        return;

    QModelIndex _index = this->index(row, 0, parent);
    if (_editedCells.contains(_index)) {
        if (_editedCells[_index].editType == EditType::INSERT) {
            _editedCells.remove(_index);
        } else if (_editedCells[_index].editType == EditType::UPDATE) {
            _editedCells[_index].id = _data[row][0].toInt();
            _editedCells[_index].editType = EditType::DELETE;
        }
    } else {
        _editedCells.insert(this->index(row, 0, parent), editedCell { _data[row][0].toInt(), _columnItems[0].field, _columnItems[0].defaultValue, _columnItems[0].defaultValue, EditType::DELETE });
    }

    beginRemoveRows(parent, row, row);
    _data.remove(row);
    endRemoveRows();
}

bool tableModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (index.isValid() && role == Qt::ItemDataRole::EditRole) {
        _data[index.row()][index.column()] = value;

        columnItem column = _columnItems[index.column()];

        if (!_editedCells.contains(index)) {
            _editedCells.insert(index, editedCell { _data[index.row()][0].toInt(), column.field, _data[index.row()][index.column()], value, EditType::UPDATE });
        } else {
            if (_editedCells[index].originalValue == value) {
                _editedCells.remove(index);
            } else {
                _editedCells[index].value = value;
            }
        }

        emit dataChanged(index, index, { role });
        return true;
    } else {
        return false;
    }
}

QVariant tableModel::data(const QModelIndex &index, int role) const {

    if (!index.isValid())
        return QVariant();

    columnItem column = _columnItems[index.column()];

    if (role == Qt::ItemDataRole::DisplayRole) {
        if (column.isPrimaryKey) {
            return QVariant();
        } else {
            return _data[index.row()][index.column()];
        }
    } else {
        return QVariant();
    }
}

Qt::ItemFlags tableModel::flags(const QModelIndex &index) const {

    if (!index.isValid())
        return Qt::ItemFlag::NoItemFlags;

    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    columnItem column = _columnItems[index.column()];

    if (column.isPrimaryKey) {
        flags &= ~Qt::ItemFlag::ItemIsSelectable;
        flags &= ~Qt::ItemFlag::ItemIsEnabled;
        flags &= ~Qt::ItemFlag::ItemIsEditable;
    } else if (column.isReadOnly) {
        flags &= ~Qt::ItemFlag::ItemIsEditable;
    } else if (column.isToggleable && !column.isNullable) {
        flags |= Qt::ItemFlag::ItemIsUserCheckable;
    } else if (column.isToggleable && column.isNullable) {
        flags |= Qt::ItemFlag::ItemIsUserTristate;
    }

    return flags;
}
