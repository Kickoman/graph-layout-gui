import QtQuick 2.6
import QtQuick.Controls 2.15
import "Graph"
import QtQuick.Shapes 1.12

Rectangle {
    id: root
    width: 1200
    height: 600

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
        color: "#276678"
        title: "QmlApplication"
    }

    Rectangle {
        id: workplace
        color: "#d3e0ea"

        anchors {
            top: header.bottom
            right: controlsScroll.left
            left: parent.left
            bottom: parent.bottom
        }

        ZoomableField {
            id: field
            canvasBackgroundColor: "#f6f5f5"

            anchors.fill: parent

            GraphView {
                model: graphModel
                nodeDelegate: GraphNode { }
            }
        }

        Text {
            id: debugText
            text: "Actual canvas size: " + field.width + "x" + field.height +
                  "\nZoom: " + field.zoom +
                  "\nFlickable size: " + field.width + "x" + field.height +
                  "\nPosition: " + field.contentX + ", " + field.contentY +
                  "\nContent size:" + field.contentWidth + "x" + field.contentHeight

            width: 300
            height: 100
            z: 10
            anchors.bottom: parent.bottom
            anchors.left: parent.left
        }
    }

    ScrollView {
        id: controlsScroll

        width: 300
        clip: true

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
            width: 300
            z: 10

            backgroundColor: "#1687a7"
            border.width: 0

//            anchors.fill: parent
            height: 1000


            onGraphRearrangeRequested: {
                graphModel.setRepulsiveForce(controls.repulsiveFormula)
                graphModel.setAttractiveForce(controls.attractiveFormula)
                graphModel.recalculatePositions()
            }

            onGraphRandomizeRequested: {
                graphModel.setRandomPositions()
            }
        }
    }
}
