#ifndef MEAL_PLANNING_H
#define MEAL_PLANNING_H

#include <QMainWindow>

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

private:
    Ui::meal_planning *ui;
};
#endif // MEAL_PLANNING_H
