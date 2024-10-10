import QtQuick 2.6
import QtQuick.Controls 2.12
import GraphLayout 1.0
import QtQuick.Shapes 1.12

Rectangle {
    id: root
    width: 1200
    height: 600

    property var graphLayout: null

    Header {
        id: header
        height: 50
        z: 10
        anchors {
            top: parent.top
            right: parent.right
            left: parent.left
        }

        border.width: 0
        color: "#816C61"
        title: "Graph arranging example"
        textColor: "#E7DFC6"
    }

    Rectangle {
        id: workplace
        color: "#E9F1F7"

        anchors {
            top: header.bottom
            right: controlsScroll.left
            left: parent.left
            bottom: parent.bottom
        }

        ZoomableField {
            id: field
            canvasBackgroundColor: "#E9F1F7"

            width: controls.widthSliderValue
            height: controls.heightSliderValue

            GraphView {
                id: graphView
                model: graphLayout
                nodeDelegate: RoundGraphNode { debug: true }
                // edgeDelegate: GraphLine { debug: true }
                // nodeDelegate: RectangleGraphNode { }
            }
        }

        Text {
            id: debugText
            text: "Size: " + field.width + "x" + field.height +
                  "\nZoom: " + field.zoom +
                  "\nContent size:" + field.contentWidth + "x" + field.contentHeight

            z: 1000
            anchors.bottom: parent.bottom
            anchors.left: parent.left
        }

        Slider {
            visible: controlsScroll.visible
            id: zoomSlider
            from: 0.1
            value: field.zoom
            to: 10
            stepSize: 0.1
            onValueChanged: field.zoom = value
        }
    }

    ScrollView {
        id: controlsScroll

        width: 300
        clip: true

        function toggleVisibility() {
            if (visible) {
                width = 0
                visible = false
            } else {
                width = 300
                visible = true
            }
        }

        anchors {
            top: header.bottom
            right: parent.right
            bottom: parent.bottom
        }

        contentWidth: 300
        contentHeight: controls.height
        ScrollBar.vertical.policy: ScrollBar.AlwaysOn
        ToolbarControls {
            id: controls

            z: 10

            backgroundColor: "#E7DFC6"
            border.width: 0
            textColor: "#131B23"

            anchors.fill: parent
            height: 1000


            onGraphRearrangeRequested: {
                graphLayout.setRepulsiveForce(controls.repulsiveFormula)
                graphLayout.setAttractiveForce(controls.attractiveFormula)
                graphLayout.setEdgesRepulsiveForce(controls.edgesRepulsiveFormula)
                graphLayout.setLinesRepulsiveForce(controls.linesRepulsiveFormula)
                graphLayout.setFrameSize(field.width, field.height)
                graphLayout.setNodeSize(graphView.getNodeWidth(), graphView.getNodeHeight())
                graphLayout.recalculatePositions()
            }

            onGraphRandomizeRequested: {
                graphLayout.setRandomPositions()
            }
        }
    }
}
