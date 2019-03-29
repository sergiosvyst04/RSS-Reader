#include "Item.hpp"

Item::Item(QString im, QString tit){
    _description = im;
    _title = tit;
}

void Item::setDescription(QString description)
{
    _description = description;
}

void Item::setTitle(QString title)
{
    _title = title;
}

Item::Item()
{

}

QString Item::description()
{
    return _description;
}


QString Item::title()
{
    return _title;
}
