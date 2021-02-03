import QtQuick 2.6
import QtQuick.Controls 2.0

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

        color: "gray"
        title: "QmlApplication"
    }

    Rectangle {
        id: workplace
        color: "red"

        anchors {
            top: header.bottom
            right: controls.left
            left: parent.left
            bottom: parent.bottom
        }

        //
        Flickable {
            id: flickable
            property double zoom: 1

            anchors.fill: parent

            contentWidth: 10000
            contentHeight: 10000

            onZoomChanged: {
//                var zoomPoint = Qt.point(width / 2 + contentX,
//                                         height / 2 + contentY)
//                resizeContent(canvas.width * zoom, canvas.height * zoom, zoomPoint)
                contentWidth = canvas.width * zoom
                contentHeight = canvas.height * zoom
                returnToBounds()
            }

            Rectangle {
                id: canvas
                width: controls.widthSliderValue
                height: controls.heightSliderValue

                Behavior on width { SmoothedAnimation { velocity: 750 } }
                Behavior on height { SmoothedAnimation { velocity: 750 } }

                gradient: Gradient {
                    GradientStop {
                        position: 0.0
                        color: "lightgreen"
                    }
                    GradientStop {
                        position: 1.1
                        color: "green"
                    }
                }

                Rectangle {
                    id: item
                    width: 10
                    height: 10
                    color: "pink"

                    Behavior on x { SmoothedAnimation { velocity: 100 } }
                    Behavior on y { SmoothedAnimation { velocity: 100 } }
                }
            }

            MouseArea {
                id: mouseArea
                anchors.fill: parent
                onWheel: {
                    var angleDeltaY = wheel.angleDelta.y
                    var zoomIn = angleDeltaY > 0
                    if (zoomIn)
                    {
                        flickable.zoom = flickable.zoom + angleDeltaY
                    }
                    else
                    {
                        flickable.zoom = flickable.zoom + angleDeltaY
                        if (flickable.zoom < 1) flickable.zoom = 1
                    }
                }
            }
        }

        Text {
            id: debugText
            text: "Actual canvas size: " + canvas.width + "x" + canvas.height +
                  "\nZoom: " + flickable.zoom +
                  "\nFlickable size: " + flickable.width + "x" + flickable.height +
                  "\nPosition: " + flickable.contentX + ", " + flickable.contentY +
                  "\nContent size:" + flickable.contentWidth + "x" + flickable.contentHeight

            width: 300
            height: 100
            z: 10
            anchors.bottom: parent.bottom
            anchors.left: parent.left
        }
    }

    ToolbarControls {
        id: controls
        width: 300

        anchors {
            top: header.bottom
            right: parent.right
            bottom: parent.bottom
        }

        onRectanglePositionChangeRequested: {
            item.x = x
            item.y = y
        }
    }

//    Rectangle {
//        id: controls
//        color: "blue"
//        width: 300

//        anchors {
//            top: header.bottom
//            right: parent.right
//            bottom: parent.bottom
//        }
//    }
}
