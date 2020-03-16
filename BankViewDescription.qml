import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import Config 1.0

RowLayout {
    id: description
    width: parent.width
    clip: true

    property bool isOpened: false

    Behavior on isOpened {
        NumberAnimation {
            target: description; property: "height"; from: height;
            to: isOpened ? 0 : Math.max(regs.height, picture.height) + 2 * row.padding;
            duration: 600; easing.type: Easing.InOutCirc
        }
    }

    Row {
        id: row
        Layout.alignment: Qt.AlignCenter
        padding: 10

        RowLayout {
            spacing: 20

            Rectangle {
                id: picture
                width: 200
                height: 200
                color: "#62f9c1"
                Layout.alignment: Qt.AlignCenter
            }

            ListView {
                id: regs
                clip: true
                height: coefficientsNumber * 36
                width: 320
                Layout.alignment: Qt.AlignCenter
                Layout.maximumHeight: 5 * 36
                model: coefficientsNumber
                delegate: Row {
                    TextField {
                        text: index
                        implicitWidth: regs.width
                        height: 36
                        background: Rectangle {
                            anchors.fill: parent
                            color: "#F2F402"
                        }
                    }
                }
            }
        }
    }
}
