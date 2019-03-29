#ifndef RSSMODEL_HPP
#define RSSMODEL_HPP

#include <QAbstractListModel>
#include <Item.hpp>
#include <AbstractRSSHttpClient.hpp>
#include <RequestSender.hpp>
#include <QPointer>
#include <memory>
#include <ApplicationViewModel.hpp>
#include <RSSHttpClient.hpp>

class RssModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit RssModel(QObject *parent = nullptr);

    enum {
        DescriptionRole = Qt::UserRole,
        TitleRole
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    QHash<int, QByteArray> roleNames() const;

public slots:
    void initialize(ApplicationViewModel *applicationViewModel);
    void fillItemList (QList<Item> &list);
    void setUrl (const QString &urlStr);

private:
    QList<Item> _itemList;
    AbstractRSSHttpClient* _abstractHttpClient = nullptr;
};

#endif // RSSMODEL_HPP
