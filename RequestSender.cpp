#include "RequestSender.hpp"
#include "RssModel.hpp"


#include <QtNetwork>
#include <QUrl>
#include <QDesktopServices>
#include <QDomDocument>


RequestSender::RequestSender(QObject *parent)
    : QObject(parent)
{

}

RequestSender::RequestSender(QNetworkAccessManager *networkManager, const QString &path, QObject *parent)
    : QObject(parent),
      _networkAccessManager(networkManager)
//      _basePath(path)
{

}

//==============================================================================

void RequestSender::makeGetRequest(QUrl &url, ErrorHandler errorHandler,
                                   Responsehandler responseHandler, int retryAtemts)
{
    QNetworkRequest request(url);

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
        if(reply->error() == QNetworkReply::OperationCanceledError && retryAtempts > 0)
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
    if(reply->error() == QNetworkReply::NoError)
    {
        QDomDocument doc;
        doc.setContent(reply->readAll());

        QList<Item> response;
        Item item;

        auto elements = doc.elementsByTagName("title");
        auto elements2  = doc.elementsByTagName("description");

        for(int i = 0; i < elements.size(); i++)
        {
            QString title = elements.at(i).toElement().text();
            QString description = elements2.at(i).toElement().text();

            item.setDescription(description);
            item.setTitle(title);

            response.append(item);
        }
        responseHandler(response);
    }
    else{
        int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        qDebug() << "HTTP error : " << statusCode;
        errorHandler(reply->errorString());
    }
}

//==============================================================================

//QUrl RequestSender::buildUrl(const QString &path){
//    QUrl url(QString("%1%2").arg(_basePath).arg(path));

//    QUrlQuery query;

//    for(auto it : params.toStdMap())
//    {
//        query.addQueryItem(it.first, QUrl::toPercentEncoding(it.second.toString()));
//    }

//    url.setQuery(query);
//    return url;
//}
