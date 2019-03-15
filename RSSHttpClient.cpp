#include "RSSHttpClient.hpp"
#include <QNetworkAccessManager>
#include <AbstractRSSHttpClient.hpp>


RSSHttpClient::RSSHttpClient(std::unique_ptr<RequestSender> &&requestSender, QObject *parent)
    :AbstractRSSHttpClient(parent),
      _requestSender(std::move(requestSender))
{

}
//==============================================================================

void RSSHttpClient::getTransactionsForAddress(QString address, size_t limit, QString order, unsigned assetID, QString lastSeenTxid)
{
    Q_ASSERT (!address.isEmpty());

    auto errorHandler = [this, address] (int errorCode, QString errorString) {
        emit getTransactionsForAddressFailed(address, Error{errorCode, errorString});
    };

    auto responseHandler = [this, assetID, address] (const QByteArray &response) {
        emit getTransactionsForAddressFinished(address, assetID, response);
    };

    QVariantMap params = {
        {"limit", QString::number(limit)},
        {"order", order}
    };

    if(!lastSeenTxid.isEmpty())
    {
        params.insert("lastSeenTxid", lastSeenTxid);
    }

    const QString url = QString("/v2/addresses/%1/transactions").arg(QString(QUrl::toPercentEncoding(address)));


    _requestSender->makeGetRequest(url, params, errorHandler, responseHandler);
}

