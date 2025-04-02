#ifndef EDITEDCELL_H
#define EDITEDCELL_H

#include <QVariant>
#include <QString>

enum EditType {
    UPDATE,
    DELETE,
    INSERT
};

struct editedCell {
    int id;
    QString field;
    QVariant originalValue;
    QVariant value;
    EditType editType;
};

#endif // EDITEDCELL_H
