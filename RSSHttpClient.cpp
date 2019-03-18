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
//    QList<Item> list;
    auto errorHandler = [this, url] (QString errorString){
        emit getContentFailed(errorString);
    };

    auto responseHandler = [this] (QList<Item> &list) {
        emit getContentFinished(list);
    };

    _requestSender->makeGetRequest(url, errorHandler, responseHandler);
}

