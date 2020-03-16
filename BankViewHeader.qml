import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3


CheckBox {
    ButtonGroup.group: bg_banks
    background: Rectangle {
        anchors.fill: parent
        color: "#22a6ad"
    }
    implicitHeight: 36
    implicitWidth: parent.width
}
