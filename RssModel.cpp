#include "RssModel.hpp"
#include <QDomDocument>
#include <RequestSender.hpp>
#include <Item.hpp>

RssModel::RssModel(QObject *parent)
    : QAbstractListModel(parent)
{

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

    switch (role) {
    case DescriptionRole:
        return item.description();
        break;
    case TitleRole:
        return item.title();
        break;
    default:
        break;
    }

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

void RssModel::initialize(ApplicationViewModel *applicationViewModel)
{
    _abstractHttpClient = applicationViewModel->getAbstractHttpClient();
}

//==============================================================================

void RssModel::fillItemList(QList<Item> &list)
{
    beginResetModel();
    _itemList = list;
    endResetModel();
    qDebug() << "_itemList.size() = " << _itemList.size();
}

//==============================================================================

void RssModel::setUrl(const QString &urlStr)
{
    _abstractHttpClient->getContent(QUrl(urlStr));
    connect(_abstractHttpClient, &AbstractRSSHttpClient::getContentFinished, this, &RssModel::fillItemList);
}
