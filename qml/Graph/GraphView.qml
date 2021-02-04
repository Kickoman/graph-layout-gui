import QtQuick 2.0

Rectangle {
    id: root
    color: "gray"
    anchors.fill: parent

//    property alias nodeDelegate: repeater.delegate
    property var model: null

    Grid {
        id: mainGrid
        anchors.fill: parent

        property int squareSize: 50

        spacing: 0
        rows: parent.height / squareSize
        columns: parent.width / squareSize

        Repeater {
            model: mainGrid.rows * mainGrid.columns

            Rectangle {
                width: mainGrid.squareSize
                height: mainGrid.squareSize

                function getRowNumber() { return Math.floor(index / mainGrid.columns) }
                function getColNumber() { return index - (mainGrid.columns * getRowNumber()) }

                function getColor() {
                    var rowNumber = getRowNumber()
                    var colNumber = getColNumber()

                    if (rowNumber % 2 == 0)
                        return colNumber % 2 ? "#f6f5f5" : "#d3e0ea"
                    return colNumber % 2 ? "#d3e0ea" : "#f6f5f5"
                }

                color: getColor()
            }
        }
    }

}
