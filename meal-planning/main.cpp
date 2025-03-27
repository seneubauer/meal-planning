#include "meal_planning.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    meal_planning w;
    w.show();
    return a.exec();
}
