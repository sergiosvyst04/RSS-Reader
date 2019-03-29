#ifndef APPLICATIONVIEWMODEL_HPP
#define APPLICATIONVIEWMODEL_HPP

#include <AbstractRSSHttpClient.hpp>
#include <QPointer>
#include <memory>
#include <QQmlEngine>


class ApplicationViewModel : public QObject
{
public:
    AbstractRSSHttpClient* getAbstractHttpClient() const;

    static ApplicationViewModel *Instance();

private:
    ApplicationViewModel(QObject *parent = nullptr);

private:
    std::unique_ptr<AbstractRSSHttpClient> _abstractRssHttpClient;
};

#endif // APPLICATIONVIEWMODEL_HPP
