import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQml.Models 2.3
//import Config 1.0

Rectangle {
    id: bank_view
    width: parent.width
    height: bank_view_column.height
    color: "#946782"

    Column {
        id: bank_view_column
        spacing: 0
        clip: true

        BankViewHeader {
            id: checker
            text: qsTr("Bank " + model.index)
            checked: true
            implicitWidth: bank_view.width
        }

        BankViewDescription {
            id: description
            isOpened: checker.checked
            width: bank_view.width
        }
    }

    Component.onCompleted: checker.checked = false
}
