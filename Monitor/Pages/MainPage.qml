import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

import "qrc:/Pages/Pages"
import "qrc:/Images/Images"
import "qrc:/ListItems/ListItems"
import "qrc:/Components/Components"

Page {
    id: mainPage
    title: "主页"
    signal refresh
    signal settings
    property bool canGoBack: false
    property alias _lstModel: lstModel
    header: TopBar{
        title: mainPage.title
        canGoBack: mainPage.canGoBack
        actions: [
            IconButton{
                name: "refresh"
                onTriggered: {
                    console.log("REFRESH!")
                }
            },
            IconButton{
                name: "delete"
                onTriggered: {
                    console.log("DELETE!")
                    lstModel.clear()
                }
            },
            IconButton{
                name: "settings"
                onTriggered: {
                    var comObj = Qt.createComponent(Qt.resolvedUrl("SettingsPage.qml"))
                    if(comObj.status === Component.Ready)
                    {
                        console.log("hi!")
                        var obj = comObj.createObject(pageStack,{
                                                          "mainWin" : mainPage
                                                      });
                        pageStack.push(obj)

                    }
                }
            }


        ]

    }
    ListModel{
        id: lstModel
        onCountChanged: lstView.positionViewAtBeginning()
    }

    ListView{
        id: lstView
        anchors.fill: parent
        model: lstModel
        delegate: DigestContext{
            logInfo: info
        }
        add: Transition {
            NumberAnimation {
                id: ad
                easing.type: Easing.OutCirc
                properties: "y";
                from: -ad.target.height;
                duration: 750
            }
        }

        addDisplaced: Transition {
            NumberAnimation {
                id: anim
                easing.type: Easing.OutCirc
                properties: "y";
                from: anim.target.y - anim.target.height;
                duration: 750
            }
        }
        remove: Transition {
            ParallelAnimation {
                NumberAnimation { property: "opacity"; to: 0; duration: 450 }
            }
        }
    }



}
