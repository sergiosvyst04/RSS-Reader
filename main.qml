import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.4
import QtQuick 2.5
//import Rss 1.0
//import "../common"

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    color: "#D01C1C"
    id: root

    header: Header {
       id: header
    }

    RssModelView {
        id:listViewRect
    }

    TitlesMenu{
        id: titlesMenu
        anchors.top : header.bottom
        anchors.topMargin: 2

        onArticleSelected: {
           articleText.setArticle(aTitle, aDescription)
        }
    }

    ArticleText{
        id: articleText
        anchors.top: titlesMenu.bottom
        anchors.topMargin: 3
    }
    
}
