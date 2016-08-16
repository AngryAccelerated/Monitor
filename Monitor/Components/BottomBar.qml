import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls.Material 2.0


ToolBar {
    id: topBar

    property list<Action> actions
    property bool canGoBack: true
    property string title: parent.title
    property int iconSpacing: 12
    property int iconSize: topBar.height - iconSpacing
    property color backgroundColor: "#2980b9"
    Material.primary: backgroundColor

    Row{
        anchors{
            centerIn: parent
        }
        spacing: {
            if(actions.length == 1)
                return 0;
            else{
                var wd = topBar.width == 0 ? topBar.implicitWidth : topBar.width
                return (wd - 2 * iconSpacing - iconSize * (actions.length)) / (actions.length - 1)
            }
        }
        Repeater{
            model: actions.length
            Action{
                anchors{
                    verticalCenter: parent.verticalCenter
                }
                iconName: actions[index].iconName
                actionText: actions[index].actionText
                width: topBar.height - iconSpacing
                height: topBar.height - iconSpacing
            }
        }
    }
}
