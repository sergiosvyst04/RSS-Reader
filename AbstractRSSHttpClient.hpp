#ifndef ABSTRACTRSSHTTPCLIENT_HPP
#define ABSTRACTRSSHTTPCLIENT_HPP

#include <QObject>
#include <Item.hpp>
//#include <QUrl>

class AbstractRSSHttpClient : public QObject
{
    Q_OBJECT
public:
    explicit AbstractRSSHttpClient(QObject *parent = nullptr);
    virtual ~AbstractRSSHttpClient();
    virtual void getContent(QUrl url) = 0;

    struct Error{
        //        int errorCode;
        QString errorString;
    };

signals:
    void getContentFinished(QList<Item> &list);
    void getContentFailed(QString error);
public slots:
};

#endif // ABSTRACTRSSHTTPCLIENT_HPP
