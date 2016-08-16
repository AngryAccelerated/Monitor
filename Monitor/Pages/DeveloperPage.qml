import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

import "qrc:/Pages/Pages"
import "qrc:/Images/Images"
import "qrc:/ListItems/ListItems"
import "qrc:/Components/Components"

Page{
    id: settingsPage
    title: "开发者"
    property bool canGoBack: true
    header: TopBar{
        title: settingsPage.title
        canGoBack: settingsPage.canGoBack
        onGoBack: {
            pageStack.pop()
            settingsPage.destroy(300)
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
            Subheader{
                text: "客户端"
            }

            Subtitled {
                text: "Accelerated"
                action: Icon {
                    anchors.centerIn: parent
                    iconName: "mobile"
                    size: 32
                    iconColor: "#2980b9"
                }
            }
            Subheader{
                text: "服务端"
            }

            Subtitled {
                text: "Accelerated"
                action: Icon {
                    anchors.centerIn: parent
                    iconName: "server"
                    size: 32
                    iconColor: "#2980b9"
                }
            }
            Subheader{
                text: "代码"
            }

            Subtitled {
                text: "Github"
                onClicked: {
                    Qt.openUrlExternally("https://github.com/AngryAccelerated/MonitorV2")
                }

                action: Icon {
                    anchors.centerIn: parent
                    iconName: "github"
                    size: 32
                    iconColor: "#2980b9"
                }
            }
        }
    }
}
