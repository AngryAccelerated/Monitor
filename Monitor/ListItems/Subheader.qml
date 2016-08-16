/*
 * QML Material - An application framework implementing Material Design.
 * Copyright (C) 2014-2015 Michael Spencer <sonrisesoftware@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 2.1 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import "qrc:/Components/Components"
import "qrc:/Images/Images"
import "qrc:/ListItems/ListItems"
import "qrc:/Pages/Pages"
/*!
   \qmltype Subheader
   \inqmlmodule Material.ListItems

   \brief Subheaders are special list tiles that delineate distinct sections of a list or grid list.
 */
View {
    id: listItem

    //----- STYLE PROPERTIES -----//

    height: 48
    property int margins: 16

    anchors {
        left: parent.left
        right: parent.right
    }

    property int spacing

    property alias text: label.text
    property alias textColor: label.color

    Label {
        id: label

        font.weight: Font.DemiBold
        font{
            family: "Microsoft YaHei Mono"
            pixelSize: 20
        }
        anchors {
            verticalCenter: parent.verticalCenter
            left: parent.left
            right: parent.right
            margins: margins
        }

        color: "#34495e"
    }

    property bool showDivider: false

    ThinDivider {
        anchors.bottom: parent.bottom
        visible: showDivider
    }
}
