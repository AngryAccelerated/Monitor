import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

import "qrc:/Pages/Pages"
import "qrc:/Images/Images"
import "qrc:/ListItems/ListItems"
import "qrc:/Components/Components"

Page{
    id: settingsPage
    title: "设置"

    property var mainWin
    property bool canGoBack: true
    header: TopBar{
        title: settingsPage.title
        canGoBack: settingsPage.canGoBack
        onGoBack: {
            pageStack.pop()
            settingsPage.destroy(300);
        }
    }
    Flickable {
        id: flick
        width: parent.width
        height: parent.height
        contentWidth: parent.width
        contentHeight: column.height
        Column{
            id: column
            width: parent.width
            Subtitled {
                text: "动态提醒"
                secondaryItem: Switch {
                    id: enablingSwitch
                    anchors.verticalCenter: parent.verticalCenter
                    Material.accent: "#2980b9"
                }
                onClicked: {
                    enablingSwitch.checked = !enablingSwitch.checked
                    appWin.openReminder = enablingSwitch.checked
                }
                action: Icon {
                    anchors.centerIn: parent
                    iconName: "alarm"
                    size: 32
                    iconColor: "#2980b9"
                }
            }
            Subtitled {
                text: "开发者"
                onClicked: {
                    var comObj = Qt.createComponent(Qt.resolvedUrl("qrc:/Pages/Pages/DeveloperPage.qml"))
                    if(comObj.status === Component.Ready)
                    {
                        var obj = comObj.createObject(pageStack);
                        pageStack.push(obj)

                    }
                }

                action: Icon {
                    anchors.centerIn: parent
                    iconName: "code"
                    size: 32
                    iconColor: "#2980b9"
                }
            }
            Subtitled {
                text: "退出"
                action: Icon {
                    anchors.centerIn: parent
                    iconName: "exit_to_app"
                    size: 32
                    iconColor: "#2980b9"
                }
                onClicked: appWin.closeApp()
            }
        }
    }
}
