import QtQuick 2.0
import "Graph"

GraphNode {
    id: root

    property bool debug: false

    height: 70
    width: 70
    Rectangle {
        anchors.fill: parent

        color: "#1687a7"
        border.color: "#163fa7"
        border.width: 2

        radius: 30

        Text {
            text: model.data
            anchors.centerIn: parent
        }

        Text {
            visible: root.debug
            text: "{" + root.x + "; " + root.y + "}"
            anchors.bottom: parent.bottom
        }
    }
}
