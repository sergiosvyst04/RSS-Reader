import QtQuick 2.5
import QtQuick.Controls 2.5
import Rss 1.0
import ApplicationVM 1.0


Item{
    width: 300
    height: 200
    visible: false


    RssModel {
        id: rssModel

        Component.onCompleted: {
            initialize(ApplicationViewModel);
        }
    }

    ListView{
        id: rssListView

        model: rssModel
        delegate: rssDelegate
        width: parent.width
        height: parent.height

        clip: true
    }

    Component{
        id: rssDelegate

        Button{
            width: 300
            height: 30

            Text{
                id: delText
                text: description + " " + title

                anchors.left: parent.left
            }
        }
    }
}









