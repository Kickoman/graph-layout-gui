import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.0

Rectangle {
    id: mainApplication

    width: 1000
    height: 500

    property bool showLoading: false

    Text {
        anchors.centerIn: parent
        text: "loading..."
        visible: showLoading && !graphModel.graphLayout
    }

    GroupBox {
        id: generatorGroupBox
        title: "Generator settings"
        visible: !graphModel.graphLayout && !showLoading
        anchors.centerIn: parent

        width: 500

        GridLayout {
            anchors.fill: parent
            anchors.margins: 10
            columns: 2
            rowSpacing: 10
            columnSpacing: 10

            Text {
                id: nodesCountLabel
                text: "Nodes count"
            }

            TextField {
                Layout.fillWidth: true
                width: 50
                id: nodesCountInput
                validator: IntValidator {bottom: 1; top: 150;}
            }

            Text {
                id: edgesCountLabel
                text: "Edges count"
            }

            TextField {
                Layout.fillWidth: true
                width: 50
                id: edgesCountInput
                validator: IntValidator {bottom: 0; top: 75*149;}
            }

            Button {
                Layout.columnSpan: 2
                Layout.fillWidth: true
                text: "Generate!"
                onClicked: {
                    if (nodesCountInput.acceptableInput
                            && edgesCountInput.acceptableInput) {
                        showLoading = true
                        graphModel.generateGraph(nodesCountInput.text,
                                                 edgesCountInput.text)
                    } else {
                        console.log("No!");
                    }
                }
            }
        }
    }

    GraphField {
        anchors.fill: parent
        visible: graphModel.graphLayout
        graphLayout: graphModel.graphLayout
    }
}
