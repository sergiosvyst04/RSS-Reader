import QtQuick 2.5
import QtQuick.Controls 2.5
import Rss 1.0
import ApplicationVM 1.0

Item {

    width: root.width
    height: root.height / 3
    visible: true
    property alias rssModelfromTitlesMenu: rssModel

    signal articleSelected(string aTitle, string aDescription)

    RssModel {
        id: rssModel

        Component.onCompleted: {
            initialize(ApplicationViewModel);
        }
    }

    ListView{
        anchors.fill: parent
        width: parent.width
        height: parent.height

        model: rssModel
        delegate: titleDelegate

        clip: true
    }

    Component{
        id:titleDelegate


        Button{
            width: root.width
            height: 40
            Text{
                id:delText
                text: title
                anchors.centerIn: parent
            }
            Text{
                id:deskText
                text: description
                visible: false
            }

            onClicked: {
                articleSelected(delText.text, deskText.text)
            }
        }
    }


}
