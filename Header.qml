import QtQuick 2.0
import QtQuick.Controls 2.5
import Request 1.0

ToolBar {
    id: toolBar

//    RequestSender{
//        id:requestSender
//    }

    ToolButton{
        id: listViewButton

        icon.name: "document-download"
        onClicked: {
            requestSender.setUrl(urlInput.text)
        }

        Rectangle{
            id: urlForm
            anchors.left: listViewButton.right
            anchors.rightMargin: 15
            border.width: 1
            border.color: "black"
            radius: 8
            height: toolBar.height - 2
            width: 400
            TextInput{
                id: urlInput
                anchors.fill: parent
            }
        }
    }
}
