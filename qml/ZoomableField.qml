import QtQuick 2.0

Flickable {
    id: flickable
    anchors.fill: parent
    clip: true

    default property alias children : canvas.children
    property alias zoom: canvas.zoom
    property alias canvasBackgroundColor: canvas.color
    property alias canvasWidth: canvas.width
    property alias canvasHeight: canvas.height
    property alias contentWidth: flickable.contentWidth
    property alias contentHeight: flickable.contentHeight
    property alias canvas: canvas

    function setZoom(zoom, zoom_point_x, zoom_point_y) {
        if (zoom < 0.1) {
            zoom = 0.1
        }

        var prev_zoom_point_x = canvas.zoom_point_x
        var prev_zoom_point_y = canvas.zoom_point_y
        var prev_zoom = canvas.zoom

        canvas.zoom_point_x = zoom_point_x
        canvas.zoom_point_y = zoom_point_y
        canvas.zoom = zoom

        // move canvas
        canvas.x = canvas.x + (prev_zoom_point_x - zoom_point_x)*(1 - prev_zoom)
        canvas.y = canvas.y + (prev_zoom_point_y - zoom_point_y)*(1 - prev_zoom)

        flickable.returnToBounds()
    }

    contentWidth: 10000
    contentHeight: 10000

    Rectangle {
        id: canvas
        width: controls.widthSliderValue
        height: controls.heightSliderValue
        z: mouseArea.z + 1

        property double zoom: 1
        property double zoom_point_x: 0
        property double zoom_point_y: 0

        Behavior on width { SmoothedAnimation { velocity: 750 } }
        Behavior on height { SmoothedAnimation { velocity: 750 } }

        transform: Scale {
            id: scaler
            origin.x: canvas.zoom_point_x
            origin.y: canvas.zoom_point_y
            xScale: canvas.zoom
            yScale: canvas.zoom
        }

    }
    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onWheel: {
            var sign = wheel.angleDelta.y > 0 ? 1 : -1
            setZoom(canvas.zoom + 0.1 * sign, mouseX, mouseY)
        }
    }
}

