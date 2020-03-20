import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQml.Models 2.3

RowLayout {
    id: description
    width: parent.width
    clip: true

    property bool isOpened: false
    property alias bankIndex: regs_list_model.rootIndex

    Behavior on isOpened {
        NumberAnimation {
            target: description; property: "height"; from: height;
            to: cfg.hasChildren(bankIndex) && !isOpened ? Math.max(regs_list.height, picture.height) + 2 * row.padding : 0;
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
                Label {
                    text: "regs count: " + regs_list.count
                }
            }

            ListView {
                id: regs_list
                clip: true
                height: 10 * 36
                width: 320
                Layout.alignment: Qt.AlignCenter
                Layout.maximumHeight: 5 * 36
                model: DelegateModel {
                    id: regs_list_model
                    model: cfg
                    delegate: Row {
                        TextField {
                            text: coefficient
                            implicitWidth: regs_list.width
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
}
