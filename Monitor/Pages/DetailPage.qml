import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

import "qrc:/Pages/Pages"
import "qrc:/Images/Images"
import "qrc:/ListItems/ListItems"
import "qrc:/Components/Components"


Page {
    id: detail
    property bool canGoBack: true

    title: "详细"

    property var logInfo: {
        "type": 3,
        "time": "2016/08/04 13:39:40",
        "senderKey": "2333333",
        "note": "TEST",
        "result": false,
        "context": "TESTING!!!"
    }
    property var detailStyle: {
        "Warning": {
            "iconName": "warning",
            "iconColor": "#f39c12",
            "text": "警告"

        },
        "Information": {
            "iconName": "info",
            "iconColor": "#3498db",
            "text": "消息"
        },
        "Notice": {
            "iconName": "info",
            "iconColor": "#e67e22",
            "text": "提醒"
        },
        "Verbose": {
            "iconName": "info",
            "iconColor": "grey",
            "text": "说明"
        },
        "Error": {
            "iconName": "info",
            "iconColor": "#c0392b",
            "text": "错误"
        }
    }

    property var resultStyle: {
        "True": {
            "iconName": "done",
            "iconColor": "#2980b9",
            "text": "True"

        },
        "False": {
            "iconName": "close",
            "iconColor": "#c0392b",
            "text": "False"
        }
    }

    function getResultStyle()
    {
        return logInfo.result ? resultStyle["True"] : resultStyle["False"]
    }

    function getStyle()
    {
        switch(logInfo.type)
        {
        case 0:
            return detailStyle["Warning"];
            break;
        case 1:
            return detailStyle["Information"];
            break;
        case 2:
            return detailStyle["Notice"];
            break;
        case 3:
            return detailStyle["Verbose"];
            break;
        case 4:
            return detailStyle["Error"];
            break;
        }
    }

    header: TopBar{
        title: detail.title
        canGoBack: detail.canGoBack
        onGoBack: {
            pageStack.pop()
            detail.destroy(300)
        }
    }

    Component.onCompleted: {
        console.log(parent.width)
        console.log(parent.height)
    }
    View{
        elevation: 2
        anchors.fill: parent
        anchors.margins: 4
        Flickable {
            id: flick
            width: parent.width
            height: parent.height
            contentWidth: parent.width
            contentHeight: column.height
            ScrollBar.vertical: ScrollBar {

            }

            Column{
                id: column
                width: parent.width

                Subheader{
                    text: "类型"
                }
                Subtitled {
                    text: getStyle().text

                    action: Icon {
                        anchors.centerIn: parent
                        iconName: getStyle().iconName
                        size: 32
                        iconColor: getStyle().iconColor
                    }
                }
                Subheader{
                    text: "时间"
                }
                Subtitled {
                    text: logInfo.time

                    action: Icon {
                        anchors.centerIn: parent
                        iconName: "access_time"
                        size: 32
                        iconColor: "#2980b9"
                    }
                }
                Subheader{
                    text: "发送ID"
                }
                Subtitled {
                    text: logInfo.senderKey

                    action: Icon {
                        anchors.centerIn: parent
                        iconName: "computer"
                        size: 32
                        iconColor: "#2980b9"
                    }
                }
                Subheader{
                    text: "内容"
                }
                Subtitled {
                    text: logInfo.context

                    action: Icon {
                        anchors.centerIn: parent
                        iconName: "details"
                        size: 32
                        iconColor: "#2980b9"
                    }
                }
                Subheader{
                    text: "备注"
                }
                Subtitled {
                    text: logInfo.note
                    action: Icon {
                        anchors.centerIn: parent
                        iconName: "event_note"
                        size: 32
                        iconColor: "#2980b9"
                    }
                }
                Subheader{
                    text: "结果"
                }
                Subtitled {
                    text: getResultStyle().text
                    action: Icon {
                        anchors.centerIn: parent
                        iconName: getResultStyle().iconName
                        size: 32
                        iconColor: getResultStyle().iconColor
                    }
                }
            }
        }


    }


}
