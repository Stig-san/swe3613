import QtQuick 1.0

Rectangle {
    id: page
    width: 400; height: 300
    color: "white"

    Text {
        id: helloText
        text: "Code Converter"
        y: 20
        x: 20
        color: "black"
        font.pointSize: 25; font.bold: true
    }

    Text {
        id: h2Text
        text: "-Convert Icd9 to Icd10"
        y: 55
        x: 100
        color: "black"
        font.pointSize: 10; font.bold: true
    }

    Image {
        source: "transfer.jpg"
        x:140
        y:100

        MouseArea {
            anchors.fill: parent
            onEntered: {parent.sourceSize.width = parent.sourceSize.width * 1.1; parent.sourceSize.height = parent.sourceSize.height * 1.1; output.text=""}
            onExited: {parent.sourceSize.width = parent.sourceSize.width * 0.9; parent.sourceSize.height = parent.sourceSize.height * 0.95; output.text=printList(byIcd9());}
        }
    }

    Text {
        id: icd9Title
        text: "ICD-9"
        y: 120
        x: 45
        color: "black"
        font.pointSize: 25; font.bold: true
    }

    Item {
        property alias text: input.text
        width: 70; height: 28
        x:50
        y:160
        BorderImage {
            source: "lineedit.sci"
            anchors.fill: parent
        }
        TextInput {
            id: input
            color: "#151515"; selectionColor: "green"
            font.pixelSize: 16; font.bold: true
            width: parent.width-16
            maximumLength: 16
            anchors.centerIn: parent
            focus: true
        }
    }

    Text {
        id: icd10Title
        text: "ICD-10"
        y: 120
        x: 250
        color: "black"
        font.pointSize: 25; font.bold: true
    }

    Item {
        property alias text: input.text
        width: 70; height: 28
        x:265
        y:160
        BorderImage {
            source: "lineedit.sci"
            anchors.fill: parent
        }
        TextInput {
            id: output
            color: "#151515"; selectionColor: "green"
            font.pixelSize: 16; font.bold: true
            width: parent.width-16
            maximumLength: 16
            anchors.centerIn: parent
            focus: true
            enabled: false
        }
    }
}
