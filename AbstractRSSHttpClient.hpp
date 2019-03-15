#ifndef ABSTRACTRSSHTTPCLIENT_HPP
#define ABSTRACTRSSHTTPCLIENT_HPP

#include <QObject>

class AbstractRSSHttpClient : public QObject
{
    Q_OBJECT
public:
    explicit AbstractRSSHttpClient(QObject *parent = nullptr);
    virtual ~AbstractRSSHttpClient();
    virtual void getTransactionsForAddress(QString address, size_t limit, QString order, unsigned assetID, QString lastSeenTxid) = 0;

    struct Error{
        int errorCode;
        QString errorString;
    };

signals:
    void getTransactionsForAddressFinished(QString address, unsigned assetID, QByteArray response);
    void getTransactionsForAddressFailed(QString address, Error error);

public slots:
};

#endif // ABSTRACTRSSHTTPCLIENT_HPP
