#include "meal_planning.h"
#include "ui_meal_planning.h"

meal_planning::meal_planning(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::meal_planning)
{
    ui->setupUi(this);
}

meal_planning::~meal_planning()
{
    delete ui;
}
