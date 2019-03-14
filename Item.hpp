#ifndef ITEM_HPP
#define ITEM_HPP
#include <QString>

class Item
{
public:
    Item(const QString im, const QString tit);

    void setTitle(QString title);
    void setDescription(QString description);
    const QString title();
    const QString description();

private:
    QString _title;
    QString _description;
};

#endif // ITEM_HPP
