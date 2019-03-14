import QtQuick 2.0

Rectangle{
    width: root.width
    height: root.height * 2/3

    visible: true
    border.color: "black"
    border.width: 1
    radius: 10


    function setArticle (aTitle, aDescription)
    {
        titleText.text = aTitle
        descriptionText.text = aDescription
    }

    Text{
        id: titleText
        anchors.top: parent.top
        width: parent.width
        height: 40
//        text: title
        font.pixelSize: 30
        horizontalAlignment: Text.AlignHCenter
        font.family: "Times New Roman"
    }

    Text{
        id: descriptionText
        anchors.top: titleText.bottom
        anchors.topMargin: 15
        anchors.left: parent.left
        anchors.leftMargin: 8
        width: parent.width
        height: parent.height
//        text: ddescription
    }

}


