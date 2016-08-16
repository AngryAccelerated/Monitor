import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtGraphicalEffects 1.0
import "qrc:/Components/Components"
import "qrc:/Images/Images"
import "qrc:/ListItems/ListItems"
import "qrc:/Pages/Pages"

Item {
    property url src: "qrc:/Images/testtx.png"
    property int size: 80
    property int borderSize: 1
    width: size
    height: size
/*
    Canvas{
        id: imgcanvas
        anchors.centerIn: parent
        width: size
        height: size
        antialiasing: true
        onPaint: {
            var ctx = getContext("2d");
            ctx.lineWidth = 1;
            ctx.strokeStyle = "#ecf0f1";
            ctx.beginPath();
            ctx.arc(size / 2,size / 2, size / 2,0, Math.PI * 2,true);
            ctx.clip();
            ctx.closePath();
            ctx.drawImage(src,0,0,size,size);
            ctx.stroke();
        }
        Component.onCompleted: loadImage(src)
        onImageLoaded: requestPaint()
    }
*/

    Rectangle{
        id: rectsrc
        color: "#fffffffff"
        border.width: borderSize
        border.color: "#3498db"
        width: size
        height: size
        radius: size
        visible: false
        smooth: true
    }

    Image {
        id: image
        source: src
        sourceSize.width: size
        sourceSize.height: size
        visible: false
        smooth: true
    }
    OpacityMask{
        source: image
        maskSource: rectsrc
        width: size
        height: size
        anchors.centerIn: parent
    }


}
