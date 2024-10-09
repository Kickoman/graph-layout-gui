import QtQuick 2.0
import QtQml.Models 2.12
import QtQml 2.0

// Main Field
Rectangle {
    id: root
    color: "gray"
    anchors.fill: parent

    property alias nodeDelegate: nodesRepeater.delegate
    property alias edgeDelegate: linesRepeater.delegate
    property var model: null

    function getNodeX(index) {
        let item = nodesRepeater.itemAt(index);
        if (item === null)
            return 0;
        return item.x + item.width / 2;
    }

    function getNodeY(index) {
        let item = nodesRepeater.itemAt(index);
        if (item === null)
            return 0;
        return item.y + item.height / 2;
    }

    function getNodeWidth() {
        let width = 0;
        if (nodesRepeater.count > 0)
            width = nodesRepeater.itemAt(0).width
        return width
    }

    function getNodeHeight() {
        let height = 0;
        if (nodesRepeater.count > 0)
            height = nodesRepeater.itemAt(0).height
        return height
    }

    Image {
        id: mainGrid
        anchors.fill: parent

        width: 50; height: 50
        fillMode: Image.Tile

        source: "qrc:///assets/bg.png"
    }

    Repeater {
        id: nodesRepeater
        model: if (root.model) root.model.nodesModel
        onCountChanged: {
            linesRepeater.model = null
            linesRepeater.model = root.model.edgesModel
        }
    }

    Repeater {
        id: linesRepeater
        model: if (root.model) root.model.edgesModel
        delegate: GraphLine {
            z: parent.z + 1
            startX: getNodeX(model.startNodeIndex)
            startY: getNodeY(model.startNodeIndex)
            finishX: getNodeX(model.finishNodeIndex)
            finishY: getNodeY(model.finishNodeIndex)
        }
    }

    onHeightChanged: if (model) model.setFrameSize(root.width, root.height)
    onWidthChanged: if (model) model.setFrameSize(root.width, root.height)
}
