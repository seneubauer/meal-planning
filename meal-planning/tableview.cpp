#include "tableview.h"

tableView::tableView(QWidget *parent) : QTableView{parent} {
    this->setSelectionMode(QAbstractItemView::SingleSelection);
}
