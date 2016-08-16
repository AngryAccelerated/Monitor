import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import "qrc:/Components/Components"
import "qrc:/Images/Images"
import "qrc:/ListItems/ListItems"
import "qrc:/Pages/Pages"

Page {
    id: loginPage
    title: "登录"
    signal login(var accountKey)
    property alias _snackBar: snackBar
    property bool canGoBack: true
    header: TopBar{
        title: loginPage.title
        canGoBack: loginPage.canGoBack
        onGoBack:
            pageStack.pop()

    }
    Snackbar{
        id: snackBar
    }

    Column{
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 36
        spacing: 24

        TextField{
            id: accountText
            width: loginPage.width * 3 / 4
            height: 64
            font.family: "Microsoft YaHei Mono"
            font.pixelSize: 18
            placeholderText: " 密钥"
            Material.accent: "#2980b9"
        }
        Button{
            id: loginBtn
            width: loginPage.width * 3 / 4
            height: 64
            text: "登录"
            font.family: "Microsoft YaHei Mono"
            Material.foreground: "white"
            Material.background: "#2980b9"
            onClicked: {
                if(accountText.text.length > 0){
                    login(accountText.text)
                    accountText.text = ""
                }
                else
                    snackBar.open("密钥不能为空")

            }
        }
    }

}
