#include "RequestSender.hpp"
#include "RssModel.hpp"


#include <QtNetwork>
#include <QUrl>
#include <QDesktopServices>
#include <QDomDocument>


//RequestSender::RequestSender(QObject *parent)
//    : QObject(parent)
//{
//    startRequest(urlName);
//}

RequestSender::RequestSender(QNetworkAccessManager *networkManager, const QString &path, QObject *parent)
    : QObject(parent),
      _networkAccessManager(networkManager),
      _basePath(path)
{

}

//==============================================================================

void RequestSender::makeGetRequest(const QString &path, const QVariantMap &params, ErrorHandler errorHandler,
                                   Responsehandler responseHandler, int retryAtemts)
{
    QNetworkRequest request(buildUrl(path, params));

    RequestMaker requestMaker = [this, request](){
        return _networkAccessManager->get(request);
    };

    proccesRequest(requestMaker, errorHandler, responseHandler, retryAtemts);
}

//==============================================================================

void RequestSender::proccesRequest(RequestMaker requestMaker, ErrorHandler errorHandler,
                                   Responsehandler responseHandler, int retryAtempts)
{
    auto reply = requestMaker();
    connect(reply, &QNetworkReply::finished, this, [=](){
        if(reply.error == QNetworkReply::OperationCanceledError && retryAtempts > 0)
        {
            qDebug() << "Retrying request, attempts : " << retryAtempts;
            proccesRequest(requestMaker, errorHandler, responseHandler, retryAtempts - 1);
        }
        else{
            proccesResponse(reply, responseHandler, errorHandler);
        }
    });

}

//==============================================================================

void RequestSender::proccesResponse(QNetworkReply *reply, Responsehandler responseHandler,
                                     ErrorHandler errorHandler)
{
    if(reply->error == QNetworkReply::NoError)
    {
        QByteArray response = reply->readAll();
        responseHandler(response);
    }
    else{
        int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        qDebug() << "HTTP error : " << statusCode;
        errorHandler(statusCode, reply->errorString());
    }
}

//==============================================================================

QUrl RequestSender::buildUrl(const QString &path, const QVariantMap &params){
    QUrl url(QString("%1%2").arg(_basePath).arg(path));

    QUrlQuery query;

    for(auto it : params.toStdMap())
    {
        query.addQueryItem(it.first, QUrl::toPercentEncoding(it.second.toString()));
    }

    url.setQuery(query);
    return url;
}
