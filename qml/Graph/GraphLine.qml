import QtQuick 2.0
import QtQuick.Shapes 1.12

Shape {
    id: root

    property int startX: 0
    property int startY: 0
    property int finishX: 0
    property int finishY: 0
    property bool debug: false

    width: Math.abs(startX - finishX)
    height: Math.abs(startY - finishY)

    visible: startX != finishX || startY != finishY

    ShapePath {
        strokeColor: "black"
        strokeWidth: 2

        startX: root.startX
        startY: root.startY

        PathLine {
            x: root.finishX
            y: root.finishY
        }
    }

    Text {
        // visible: root.debug
        text: Math.sqrt(Math.pow(root.startX - root.finishX, 2) + Math.pow(root.startY - root.finishY, 2))
        x: (root.startX + root.finishX) / 2
        y: (root.startY + root.finishY) / 2
    }
}
