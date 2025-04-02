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

    QVector<columnItem> columnItems;
    columnItems.append(columnItem { "ID", "vitaminID", true, true, false, false, -1, false, false });
    columnItems.append(columnItem { "Name", "name", false, false, false, false, "vitamin", true, false });
    columnItems.append(columnItem { "Alias", "alias", false, false, false, false, "alias", true, false });
    columnItems.append(columnItem { "Health Effects", "healthEffects", false, false, false, false, "health effects", true, true });
    columnItems.append(columnItem { "Solubility", "solubilityTypeID", false, false, false, true, 1, false, false });

    model = new tableModel(this);
    model->setTableName("vitamin");
    model->setDatabaseName("mealPlanning");
    model->setColumns(columnItems);

    ui->vitaminTable->setModel(model);
    model->getData(mainConnection.db);
}

void meal_planning::vitaminSelected(int index)
{
    if (vitaminModel->index(index, 0).isValid()) {
        // qDebug() << vitaminModel->index(index, 1).data(Qt::UserRole) << vitaminModel->index(index, 1).data(Qt::DisplayRole);
    }
}
