import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtGraphicalEffects 1.0
import QtQuick.Controls.Material 2.0
import "qrc:/Components/Components"
import "qrc:/Images/Images"
import "qrc:/ListItems/ListItems"
import "qrc:/Pages/Pages"

Image {
    id: img
    property int size: 24
    property string iconName
    property color iconColor: "white"

    sourceSize.width: size
    sourceSize.height: size
    source: iconName.length > 0 ? "qrc:/Images/Images/" + img.iconName + ".svg" : ""


    ColorOverlay {
        anchors.fill: parent
        source: parent
        color: iconColor
    }
}
