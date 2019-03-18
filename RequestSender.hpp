#ifndef REQUESTSENDER_HPP
#define REQUESTSENDER_HPP

#include <QObject>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QFile>
#include <QDomDocument>
#include <functional>
#include <Item.hpp>

class RequestSender : public QObject
{
    Q_OBJECT
public:
    using RequestMaker  = std::function<QNetworkReply*()>;
//    using Responsehandler = std::function<void(QByteArray&)>;
    using Responsehandler = std::function<void(QList<Item> &list)>;
    using ErrorHandler = std::function<void( const QString&)>;

public:
    RequestSender(QObject *parent = nullptr);
    RequestSender(QNetworkAccessManager *networkManager, const QString &path,  QObject *parent = nullptr);
    void makeGetRequest(QUrl &url, ErrorHandler errorHandler, Responsehandler responseHandler, int retryAtemts = 0);



private slots:
    void proccesResponse(QNetworkReply* reply, Responsehandler responseHandler, ErrorHandler errorHandler);

private:
    void proccesRequest(RequestMaker requestMaker, ErrorHandler errorHandler, Responsehandler responseHandler, int retryAtempts = 0);

//    QUrl buildUrl(const QString& path, const QVariantMap& params = QVariantMap());

    QNetworkAccessManager *_networkAccessManager;
//    QString _basePath;
};

#endif // REQUESTSENDER_HPP
