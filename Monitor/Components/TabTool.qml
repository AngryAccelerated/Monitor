import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import "qrc:/Components/Components"
import "qrc:/Images/Images"
import "qrc:/ListItems/ListItems"
import "qrc:/Pages/Pages"

Rectangle {
    id: ctrl
    color: "#ffffff"
    property color topBorderColor: "#2980b9"
    property bool topBorderShow: false
    Rectangle{
        id: topBorder
        width: parent.width
        height: 1
        visible: topBorderShow
        anchors.top:parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        color: topBorderColor
    }
}
