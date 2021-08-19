import QtQuick 2.0

Item {

    id: root

    property double zoom: 1
    property double zoom_point_x: 0
    property double zoom_point_y: 0
    property bool isDragged: false

    function setZoom(zoom, zoom_point_x, zoom_point_y) {
        if (zoom < 0.1) {
            zoom = 0.1
        }

        var prev_zoom_point_x = root.zoom_point_x
        var prev_zoom_point_y = root.zoom_point_y
        var prev_zoom = root.zoom

        root.zoom_point_x = zoom_point_x
        root.zoom_point_y = zoom_point_y
        root.zoom = zoom

        root.x = root.x + (prev_zoom_point_x - zoom_point_x)*(1 - prev_zoom)
        root.y = root.y + (prev_zoom_point_y - zoom_point_y)*(1 - prev_zoom)
    }

    MouseArea {
        id: mouseArea
        hoverEnabled: true
        anchors.fill: root

        property real lastZ: parent.z

        // It also should be draggable
        drag.target: root
        drag.axis: Drag.XAndYAxis

        onWheel: {
            var sign = wheel.angleDelta.y > 0 ? 1 : -1
            setZoom(zoom + 0.1 * sign, mouseX, mouseY)
        }

        onReleased: {
            parent.z = lastZ
            parent.isDragged = false
        }
        onPressed: {
            lastZ = parent.z
            parent.z = 1000
            parent.isDragged = true
        }
    }

    transform: Scale {
        id: scaler
        origin.x: zoom_point_x
        origin.y: zoom_point_y
        xScale: zoom
        yScale: zoom
    }

}
