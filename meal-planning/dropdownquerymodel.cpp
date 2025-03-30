#include "dropdownquerymodel.h"
#include <QVariant>

QVariant dropDownQueryModel::data(const QModelIndex &index, int role) const {

    if (!index.isValid()) {
        return QVariant();
    }

    if (role == Qt::UserRole && index.column() == 1) {
        return QSqlQueryModel::data(this->index(index.row(), 0), Qt::DisplayRole);
    } else {
        return QSqlQueryModel::data(index, role);
    }
}
