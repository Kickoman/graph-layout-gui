import QtQuick 2.0

ZoomableObject {
    id: field

    default property alias children: canvas.children
    property alias canvasBackgroundColor: canvas.color

    property alias contentX: canvas.x
    property alias contentY: canvas.y
    property alias contentWidth: canvas.width
    property alias contentHeight: canvas.height

    Rectangle {
        id: canvas
        anchors.fill: parent
    }
}
