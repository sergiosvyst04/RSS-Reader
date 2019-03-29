#include "ApplicationViewModel.hpp"
#include "RSSHttpClient.hpp"

//==============================================================================

ApplicationViewModel::ApplicationViewModel(QObject *parent)
{
    std::unique_ptr<RequestSender> reqSen(new RequestSender);
   _abstractRssHttpClient.reset(new RSSHttpClient(std::move(reqSen)));

}

//==============================================================================

AbstractRSSHttpClient* ApplicationViewModel::getAbstractHttpClient() const
{
    return _abstractRssHttpClient.get();
}

//==============================================================================

ApplicationViewModel *ApplicationViewModel::Instance()
{
    static ApplicationViewModel instance;
    return &instance;
}

//==============================================================================
