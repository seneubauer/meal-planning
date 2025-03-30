#ifndef MEAL_PLANNING_H
#define MEAL_PLANNING_H

#include "databaseconnection.h"
#include "dropdownquerymodel.h"

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QList>

QT_BEGIN_NAMESPACE
namespace Ui {
class meal_planning;
}
QT_END_NAMESPACE

class meal_planning : public QMainWindow
{
    Q_OBJECT

public:
    meal_planning(QWidget *parent = nullptr);
    ~meal_planning();
    void initialization();
    databaseConnection mainConnection;
    dropDownQueryModel *vitaminModel;

private slots:
    void vitaminSelected(int index);

private:
    Ui::meal_planning *ui;
};

#endif // MEAL_PLANNING_H
