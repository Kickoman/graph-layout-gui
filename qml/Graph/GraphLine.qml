import QtQuick 2.0
import QtQuick.Shapes 1.12

//Item {

//    property var startObject: null
//    property var endObject: null

//    visible: startObject && endObject

//    function centerX(obj) { console.log(obj.x); return obj.x + obj.width / 2 }
//    function centerY(obj) { return obj.y + obj.height / 2 }

//    ShapePath {
//        strokeColor: "black"
//        strokeWidth: 5

//        startX: startObject ? centerX(startObject) : 0
//        startY: startObject ? centerY(startObject) : 0

//        PathLine {
//            x: endObject ? centerX(endObject) : 0
//            y: endObject ? centerY(endObject) : 0
//        }
//    }

//}


Shape {
    id: root

    property int startX: 0
    property int startY: 0
    property int finishX: 0
    property int finishY: 0

    width: Math.abs(startX - finishX)
    height: Math.abs(startY - finishY)

    visible: startX != finishX || startY != finishY

    ShapePath {
        strokeColor: "black"
        strokeWidth: 2

        startX: root.startX
        startY: root.startY

        PathLine {
            x: root.finishX
            y: root.finishY
        }
    }

//    Behavior on startX {
//        SmoothedAnimation {
//            id: startXAnimation
//            velocity: 100
//        }
//    }
//    Behavior on startY {
//        SmoothedAnimation {
//            id: startYAnimation
//            velocity: 100
//        }
//    }
//    Behavior on finishX {
//        SmoothedAnimation {
//            id: finishXAnimation
//            velocity: 100
//        }
//    }
//    Behavior on finishY {
//        SmoothedAnimation {
//            id: finishYAnimation
//            velocity: 100
//        }
//    }
}
