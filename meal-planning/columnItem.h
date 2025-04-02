#ifndef COLUMNITEM_H
#define COLUMNITEM_H

#include <QVariant>
#include <QString>

struct columnItem {
    QString label;
    QString field;
    bool isPrimaryKey;
    bool isReadOnly;
    bool isToggleable;
    bool isDropDown;
    QVariant defaultValue;
    bool requiresQuotes;
    bool isNullable;
};

#endif // COLUMNITEM_H
