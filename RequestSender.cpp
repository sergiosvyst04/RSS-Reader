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
        QByteArray response = reply->readAll();
        responseHandler(response);
    }
    else{
        int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        qDebug() << "HTTP error : " << statusCode;
        errorHandler(reply->errorString());
    }
}

//==============================================================================
