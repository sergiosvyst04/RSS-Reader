#include "RSSHttpClient.hpp"
#include <QNetworkAccessManager>
#include <AbstractRSSHttpClient.hpp>


RSSHttpClient::RSSHttpClient(std::unique_ptr<RequestSender> &&requestSender, QObject *parent)
    :AbstractRSSHttpClient(parent),
      _requestSender(std::move(requestSender))
{

}
//==============================================================================

void RSSHttpClient::getContent(QUrl url)
{
    auto errorHandler = [this, url] (QString errorString){
        emit getContentFailed(errorString);
    };

    auto responseHandler = [this] (QByteArray &response) {
        QList<Item> list = rssParser(response);
        emit getContentFinished(list);
    };

    _requestSender->makeGetRequest(url, errorHandler, responseHandler);
}

//==============================================================================

QList<Item> RSSHttpClient::rssParser(const QByteArray &response)
{
    QDomDocument doc;
    doc.setContent(response);
    QList<Item> list;

    auto titles = doc.elementsByTagName("title");
    auto descriptions = doc.elementsByTagName("description");

    Item item;

    for(int i = 0; i < titles.size(); i++)
    {
        QString title = titles.at(i).toElement().text();
        QString description = descriptions.at(i).toElement().text();

        item.setTitle(title);
        item.setDescription(description);

        list.append(item);
    }
    return list;
}

//==============================================================================

