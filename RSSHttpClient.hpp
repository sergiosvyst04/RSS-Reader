#ifndef RSSHTTPCLIENT_HPP
#define RSSHTTPCLIENT_HPP

#include <QObject>
#include <QPointer>
#include <memory>
#include <RequestSender.hpp>
#include <AbstractRSSHttpClient.hpp>

class RSSHttpClient : public AbstractRSSHttpClient
{
    Q_OBJECT
public:
    explicit RSSHttpClient(std::unique_ptr<RequestSender> &&requestSender ,QObject *parent = nullptr);

signals:

public slots:
   void getContent(QUrl url) override;

private:
    std::unique_ptr<RequestSender> _requestSender;
};

#endif // RSSHTTPCLIENT_HPP
