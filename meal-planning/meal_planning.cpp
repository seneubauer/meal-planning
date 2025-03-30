#include "meal_planning.h"
#include "ui_meal_planning.h"

#include <QDebug>

meal_planning::meal_planning(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::meal_planning)
{
    ui->setupUi(this);
    initialization();
}

meal_planning::~meal_planning()
{
    delete ui;
}

void meal_planning::initialization() {

    QComboBox::connect(ui->comboBox, &QComboBox::currentIndexChanged, this, &meal_planning::vitaminSelected);


    mainConnection.connect(mainConnection.hostServer, mainConnection.hostDatabase, "main");

    vitaminModel = new dropDownQueryModel(this);
    vitaminModel->setQuery("SELECT v.vitaminID, v.name FROM mealPlanning.dbo.vitamin v ORDER BY v.name ASC", mainConnection.db);
    ui->comboBox->setModel(vitaminModel);
    ui->comboBox->setModelColumn(1);
}

void meal_planning::vitaminSelected(int index)
{
    if (vitaminModel->index(index, 0).isValid()) {
        qDebug() << vitaminModel->index(index, 1).data(Qt::UserRole) << vitaminModel->index(index, 1).data(Qt::DisplayRole);
    }
}
