import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Rectangle {
    property string backgroundColor: "blue"
    property string borderColor: "black"
    property string textColor: "black"

    property alias heightSliderValue: heightSlider.value
    property alias widthSliderValue: widthSlider.value

    property alias repulsiveFormula: repulsiveInput.text
    property alias attractiveFormula: attractiveInput.text

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
                anchors.margins: 10
                columns: 2
                rowSpacing: 10
                columnSpacing: 10

                Text {
                    text: "Attractive formula:"
                }
                TextInput {
                    id: attractiveInput
                    text: "log10(x/10)"
                }

                Text {
                    text: "Repulsive formula:"
                }
                TextInput {
                    id: repulsiveInput
                    text: "log10(x/10)"
                }

                Button {
                    Layout.columnSpan: 2
                    Layout.fillWidth: true
                    text: "Rearrange graph"
                    onClicked: graphRearrangeRequested()
                }

                Button {
                    Layout.columnSpan: 2
                    Layout.fillWidth: true
                    text: "Random positions"
                    onClicked: graphRandomizeRequested()
                }
            }
        }

        Item {
            id: filler
            Layout.fillHeight: true
        }
    }
}
