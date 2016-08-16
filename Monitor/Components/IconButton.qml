import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import "qrc:/Components/Components"
import "qrc:/Images/Images"
import "qrc:/ListItems/ListItems"
import "qrc:/Pages/Pages"
Item {
    id: iconBtn
    property int size: 24
    property string name
    property color color: "white"
    signal triggered
    width: size + 4
    height: size + 4
    Icon{
        id: icn
        anchors.centerIn: parent
        size: iconBtn.size - 4
        iconName: name
        iconColor: iconBtn.color
    }
    Ink{
        anchors.centerIn: parent
        centered: true
        enabled: iconBtn.enabled
        circular: true
        onClicked: {
            triggered()
        }

        width: size + 4
        height: size + 4
    }
}
