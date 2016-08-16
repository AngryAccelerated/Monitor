import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import "qrc:/Components/Components"
import "qrc:/Images/Images"
import "qrc:/ListItems/ListItems"
import "qrc:/Pages/Pages"

Rectangle {
    id: ctl
    property string iconName
    property int size: 36
    property color iconColor
    property bool checked: true
    signal triggered
    height: size + 4
    color: "#00000000"
    Icon{
        id: img
        iconName: ctl.iconName
        size: ctl.size - 4
        anchors.centerIn: parent
        iconColor: ctl.iconColor
    }


    MouseArea{
        anchors.fill: parent
        onClicked: triggered()
    }
}
