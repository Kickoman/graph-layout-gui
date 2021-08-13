import QtQuick 2.0

Rectangle {
    property string backgroundColor: "#276678"
    property string borderColor: "black"
    property string title: "The title"
    property alias textColor: idTitle.color

    color: backgroundColor
    border.color: borderColor
    border.width: 5

    Text {
        id: idTitle
        text: title

        anchors.left: parent.left
        anchors.top: parent.top
        anchors.margins: 10

        fontSizeMode: Text.Fit
        font.pixelSize: 20
    }
}
