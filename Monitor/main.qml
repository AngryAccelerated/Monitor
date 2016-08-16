import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import Mobile 1.0
import "qrc:/Components/Components"
import "qrc:/Images/Images"
import "qrc:/ListItems/ListItems"
import "qrc:/Pages/Pages"

ApplicationWindow {
    id: appWin
    visible: true
    width: 445
    height: 775

    property bool openReminder: false

    Popup{
        id: waitingPopup
        width: lbl.width + 24
        height: indicator.height + lbl.height + 36
        contentHeight: indicator.height + lbl.height + 36
        modal: true
        x: (parent.width - width) / 2
        y: (parent.height - height) / 2
        BusyIndicator{
            id: indicator
            width: 64
            height: 64
            running: true
            Material.accent: "#2980b9"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
        }
        Label{
            id: lbl
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: indicator.bottom
            anchors.topMargin: 12
            text: "正在连接服务器"
            font.pixelSize: 18
            font.family: "Microsoft YaHei Mono"
        }

    }
    Component.onCompleted:
        waitingPopup.open()
    Mobile{
        id: mobile
        onConnectedToServer: {
            loginPage._snackBar.open("已连接服务器")
            waitingPopup.close()
        }
        onLoggedInToServer: {
            mainSnack.open("登录成功");
            pageStack.pop();
        }
        onSyncedFromServer: {
            mainPage._lstModel.insert(0,obj)
        }
        onUserDisconnected: {
            loginPage._snackBar.open("连接服务器失败")
            mainSnack.open("连接服务器失败")
        }
        onLoggedOutFromServer: {
            loginPage._snackBar.open("连接服务器失败")
            mainSnack.open("连接服务器失败")
        }

        onLoggedFaild: {
            loginPage._snackBar.open("登录失败")
            loginPage.enabled = true
        }
    }
    function closeApp(){
        mobile.logout();
        pageStack.clear();
        pageStack.push(mainPage);
        pageStack.push(loginPage);
        loginPage.enabled = true
        mainPage._lstModel.clear();
    }

    StackView{
        id: pageStack
        anchors.fill: parent

        initialItem: MainPage{
            id: mainPage
            canGoBack: false
            Component.onCompleted: pageStack.push(loginPage)
            Snackbar{
                id: mainSnack
            }
        }
    }
    LoginPage{
        id: loginPage
        canGoBack: false
        onLogin: {
            loginPage.enabled = false
            mobile.loginAccount(accountKey)
        }
    }

}
