import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Rectangle {
    property string backgroundColor: "blue"
    property string borderColor: "black"
    property string textColor: "black"

    property alias heightSliderValue: heightSlider.value
    property alias widthSliderValue: widthSlider.value

    color: backgroundColor
    border.color: borderColor

    signal canvasWidthSliderChanged(double value)
    signal canvasHeightSliderChanged(double value)
    signal rectanglePositionChangeRequested(double x, double y)

    ColumnLayout {
        anchors.fill: parent

        GroupBox {
            id: canvasControlsGroupBox
            title: "Canvas controls"

            Layout.alignment: Qt.AlignTop
            Layout.fillWidth: true

            GridLayout {
                anchors.fill: parent
                anchors.margins: 10
                columns: 2
                rowSpacing: 10
                columnSpacing: 10

                Text {
                    id: canvasInfo
                    Layout.columnSpan: 2
                    text: "Current canvas size: " + heightSlider.value + "x" + widthSlider.value
                }

                Text {
                    text: "Height:"
                }

                Slider {
                    id: heightSlider
                    from: 100
                    value: 1000
                    to: 10000
                    stepSize: 1

                    onValueChanged: canvasHeightSliderChanged(heightSlider.value)
                }

                Text {
                    text: "Width:"
                }

                Slider {
                    id: widthSlider
                    from: 100
                    value: 1000
                    to: 10000
                    stepSize: 1

                    onValueChanged: canvasWidthSliderChanged(widthSlider.value)
                }
            }
        }

        GroupBox {
            id: tempButtonGroupBox
            title: "Temporary buttons"

            Layout.alignment: Qt.AlignTop
            Layout.fillWidth: true

            GridLayout {
                anchors.fill: parent
                anchors.margins: 10
                columns: 2
                rowSpacing: 10
                columnSpacing: 10

                Text {
                    text: "X position"
                }

                TextInput {
                    id: xPosition
                    text: "100"
                }

                Text {
                    text: "Y position"
                }

                TextInput {
                    id: yPosition
                    text: "100"
                }

                Button {
                    id: requestPositionChangeButton
                    text: "Move rectangle"
                    onClicked: {
                        var xpos = parseInt(xPosition.text)
                        var ypos = parseInt(yPosition.text)
                        rectanglePositionChangeRequested(xpos, ypos)
                    }
                }
            }
        }
    }
}
