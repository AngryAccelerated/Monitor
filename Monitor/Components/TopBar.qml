import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import "qrc:/Components/Components"
import "qrc:/Images/Images"
import "qrc:/ListItems/ListItems"
import "qrc:/Pages/Pages"

ToolBar{
    id: toolBar
    property string title: "Main"
    implicitHeight: 48
    implicitWidth: parent.width
    property bool canGoBack: true
    property int iconSpacing: 16
    property string leftIconName
    property list<IconButton> actions

    signal goBack
    signal leftIconTriggered

    Material.primary: "#2980b9"
    IconButton{
        id: back
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: iconSpacing
        name: "navigate_before"
        size: parent.height - iconSpacing
        enabled: canGoBack
        visible: canGoBack
        onTriggered: {
            goBack()
            console.log("GO BACK!")
        }
        z: 1
    }
    IconButton{
        id: lefticon
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: iconSpacing
        name: leftIconName
        size: parent.height - iconSpacing
        enabled: !canGoBack
        visible: !canGoBack
        onTriggered: {
            leftIconTriggered()
            console.log("CLICKED!")
        }
        z: 0
    }
    Text {
        id: titleAction
        anchors{
            verticalCenter: parent.verticalCenter
            left: parent.left
            leftMargin: canGoBack ? iconSpacing / 2 + iconSpacing + back.width : iconSpacing
        }
        font.family: "Microsoft YaHei Mono"
        font.pixelSize: 20
        color: "white"
        text: title
    }
    Row{
        anchors{
            verticalCenter: parent.verticalCenter
            right: parent.right
            rightMargin: iconSpacing
        }
        spacing: iconSpacing
        Repeater{
            model: actions.length
            delegate: IconButton{
                anchors{
                    verticalCenter: parent.verticalCenter
                }
                name: actions[index].name
                size: toolBar.height - iconSpacing
                onTriggered: actions[index].triggered()
            }
        }
    }
}

