/*
 * QML Material - An application framework implementing Material Design.
 * Copyright (C) 2015 Ricardo Vieira <ricardo.vieira@tecnico.ulisboa.pt>
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
   \qmltype SectionHeader
   \inqmlmodule Material.ListItems

   \brief A list item that serves as the the header for an expandable list section.
 */
BaseListItem {
    id: listItem

    property alias text: label.text
    property alias iconName: icon.iconName
    property bool expanded: false

    height: 48

    RowLayout {
        anchors.fill: parent

        anchors.leftMargin: listItem.margins
        anchors.rightMargin: listItem.margins

        spacing: 16

        Item {
            Layout.preferredWidth: 40
            Layout.preferredHeight: width
            Layout.alignment: Qt.AlignCenter

            visible: children.length > 1 || iconName != ""

            Icon {
                id: icon

                anchors {
                    verticalCenter: parent.verticalCenter
                    left: parent.left
                }

                visible: name != ""

                size: 24
            }
        }

        Label {
            id: label

            Layout.alignment: Qt.AlignVCenter
            Layout.fillWidth: true
            font{
                family: "Microsoft YaHei Mono"
                pixelSize: 16
            }
            elide: Text.ElideRight

            color: "#ecf0f1"
        }

        Item {
            Layout.preferredWidth: 40
            Layout.preferredHeight: width
            Layout.alignment: Qt.AlignRight

            Icon {
                anchors {
                    verticalCenter: parent.verticalCenter
                    left: parent.left
                }

                iconName: "expand_more"
                rotation: listItem.expanded ? 180 : 0
                size: 24

                Behavior on rotation {
                    NumberAnimation { duration: 200 }
                }
            }
        }
    }

    onClicked: listItem.expanded = !listItem.expanded
}
