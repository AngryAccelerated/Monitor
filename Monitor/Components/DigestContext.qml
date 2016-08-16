import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

//import "qrc:/Pages/Pages"
import "qrc:/Images/Images"
import "qrc:/ListItems/ListItems"
import "qrc:/Components/Components"

Subtitled {
    id: summary

    property var logInfo

    property var detailStyle: {
        "Warning": {
            "iconName": "warning",
            "iconColor": "#f39c12"

        },
        "Information": {
            "iconName": "info",
            "iconColor": "#3498db"
        },
        "Notice": {
            "iconName": "info",
            "iconColor": "#e67e22"
        },
        "Verbose": {
            "iconName": "info",
            "iconColor": "grey"
        },
        "Error": {
            "iconName": "info",
            "iconColor": "#c0392b"
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
    width: parent.width
    text: logInfo.senderKey
    valueText: logInfo.time
    subText: logInfo.context
    secondaryItem: IconButton {
        id: enablingSwitch
        anchors.centerIn: parent
        color: getStyle().iconColor
        name: "navigate_next"
        onTriggered: {
            var detailObj = Qt.createComponent(Qt.resolvedUrl("qrc:/Pages/Pages/DetailPage.qml"))
            console.log(pageStack.depth)
            if(detailObj.status === Component.Ready)
            {
                console.log("READY!")
                var obj = detailObj.createObject(pageStack,{
                                                     "logInfo" : logInfo
                                                 });
                pageStack.push(obj)

            }
        }
    }
    action: Icon {
        anchors.centerIn: parent
        iconName: getStyle().iconName
        size: 32
        iconColor: getStyle().iconColor
    }
}

