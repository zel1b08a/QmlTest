import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQml.Models 2.3
//import Config 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    ButtonGroup {
        id: bg_banks
        exclusive: false
    }

    RowLayout {
        anchors.fill: parent
        spacing: 0

        Frame {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignCenter

            ListView {
                id: bank_list
                anchors.fill: parent
                model: DelegateModel {
                    model: cfg
                    delegate: BankView {
                        bankIndex: cfg.index(index, 0)
                    }
                }
            }
        }
        Rectangle {
            width: 200
            Layout.fillHeight: true
            color: "#721f0f"

            Button {
                width: 150
                height: 60
                text: qsTr("make request")
                anchors.centerIn: parent
                onClicked: {
                    client.makeRequest()
                }
            }
        }
    }
}
