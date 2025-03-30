#ifndef DROPDOWNQUERYMODEL_H
#define DROPDOWNQUERYMODEL_H

#include <QSqlQueryModel>

class dropDownQueryModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    dropDownQueryModel(QObject *parent = nullptr) : QSqlQueryModel(parent) {}
    QVariant data(const QModelIndex &index, int role) const override;
};

#endif // DROPDOWNQUERYMODEL_H
