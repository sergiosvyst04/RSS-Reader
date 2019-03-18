#include "RssModel.hpp"
#include <QDomDocument>
#include <RequestSender.hpp>
#include <Item.hpp>

RssModel::RssModel(QObject *parent)
    : QAbstractListModel(parent)
{
    requestsender = new RequestSender();
    qDebug() << "call in constructor";

//    connect(requestsender, &RequestSender::filled, this, &RssModel::fillItemList );

}

//==============================================================================

int RssModel::rowCount(const QModelIndex &parent) const
{
    return _itemList.size();
}

//==============================================================================

QVariant RssModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    Item item = _itemList.at(index.row());

//    switch (role) {
//    case DescriptionRole:
//        return item.description();
//        break;
//    case TitleRole:
//        return item.title();
//    default:
//        break;
//    }
}

//==============================================================================

bool RssModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        // FIXME: Implement me!
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

//==============================================================================

Qt::ItemFlags RssModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable; // FIXME: Implement me!
}

QHash <int, QByteArray> RssModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[DescriptionRole] = "description";
    names[TitleRole] = "title";

    return names;
}

//==============================================================================

//void RssModel::fillItemList()
//{
//    beginResetModel();
//    endResetModel();
//    QStringList titles = requestsender->returnTitlesList();
//    QStringList descriptions = requestsender->returnDescriptionsList();

//    qDebug() << "fill from " << requestsender->returnUrl();

//    Item item;

//    int j = 2;
//    for(int i = 0; i < titles.size(); i++)
//    {
//        item.setTitle(titles.at(j));
//        item.setDescription(descriptions.at(i));

//        beginInsertRows(QModelIndex(), rowCount(QModelIndex()), rowCount(QModelIndex()));
//        _itemList.append(item);
//        endInsertRows();
//        j++;
//        if(j == descriptions.size() - 2)
//            break;
//    }

//    qDebug() << "count of Items : " << _itemList.size();
//}
