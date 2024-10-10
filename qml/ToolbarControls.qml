import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Rectangle {
    id: root

    property string backgroundColor: "blue"
    property string borderColor: "black"
    property string textColor: "black"

    property alias heightSliderValue: heightSlider.value
    property alias widthSliderValue: widthSlider.value

    property alias repulsiveFormula: repulsiveInput.text
    property alias attractiveFormula: attractiveInput.text
    property alias edgesRepulsiveFormula: edgesRepulsiveInput.text
    property alias linesRepulsiveFormula: linesRepulsiveInput.text

    color: backgroundColor
    border.color: borderColor

    signal canvasWidthSliderChanged(double value)
    signal canvasHeightSliderChanged(double value)
    signal graphRearrangeRequested()
    signal graphRandomizeRequested()

    ColumnLayout {
        anchors.fill: parent
        spacing: 10

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
            id: graphControlsGroupBox
            title: "Graph controls"

            Layout.alignment: Qt.AlignTop
            Layout.fillWidth: true

            GridLayout {
                anchors.fill: parent
                anchors.margins: 5
                columns: 2
                rowSpacing: 10
                columnSpacing: 10

                Text {
                    color: root.textColor
                    text: "Attractive formula:"
                }

                TextField {
                    color: root.textColor
                    Layout.fillWidth: true
                    width: 50
                    id: attractiveInput
                    // text: "exp((x-100)/1000)"
                    text: "x/10"
                }

                Text {
                    color: root.textColor
                    text: "Repulsive formula:"
                }
                TextField {
                    color: root.textColor
                    Layout.fillWidth: true
                    id: repulsiveInput
                    // text: "exp(-(x-500)/70)"
                    text: "1000/(((x+100)/100)^2)"
                }

                Text {
                    color: root.textColor
                    text: "Edges repulsive formula:"
                }
                TextField {
                    color: root.textColor
                    Layout.fillWidth: true
                    id: edgesRepulsiveInput
                    // text: "exp(-(x-500)/70)/7"
                    text: "100/(((x+150)/100))"
                }

                Text {
                    color: root.textColor
                    text: "Lines repulsive formula:"
                }
                TextField {
                    color: root.textColor
                    Layout.fillWidth: true
                    id: linesRepulsiveInput
                    text: "exp(-(x-500)/70)/500"
                }

                Button {
                    background: Rectangle {
                        anchors.fill: parent
                        color: "#2274A5"
                    }
                    contentItem: Text {
                        text: "Rearrange graph"
                        color: "#E9F1F7"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }

                    Layout.columnSpan: 2
                    Layout.fillWidth: true
                    onClicked: graphRearrangeRequested()
                }

                Button {
                    background: Rectangle {
                        anchors.fill: parent
                        color: "#2274A5"
                    }
                    contentItem: Text {
                        text: "Random positions"
                        color: "#E9F1F7"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }

                    Layout.columnSpan: 2
                    Layout.fillWidth: true
                    onClicked: graphRandomizeRequested()
                }
            }
        }

        Item {
            id: filler
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }
}
