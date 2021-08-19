import QtQuick 2.0

ZoomableObject {
    id: field

    default property alias children: canvas.children
    property alias canvasBackgroundColor: canvas.color

    Rectangle {
        id: canvas
        anchors.fill: parent
    }
}
