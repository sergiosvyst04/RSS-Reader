#ifndef ITEM_HPP
#define ITEM_HPP
#include <QString>

class Item
{
public:
    Item(QString im,QString tit);
    Item();

    void setTitle(QString title);
    void setDescription(QString description);
    QString title();
    QString description();

private:
    QString _title;
    QString _description;
};

#endif // ITEM_HPP
