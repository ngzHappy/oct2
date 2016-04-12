import QtQuick 2.5
import QtQml.Models 2.2

/*rootWindow*/

Rectangle {
    width: 1000;
    height: 1000;
    color: Qt.rgba(0.5,0.6,0.5,1)
    id : rootItem

    ObjectModel {
        id: itemModel
        AllInOneItem{projectName:"2332";width: rootItem.width;onClicked: {rootWindow.startDataView(startString)}}
        AllInOneItem{projectName:"2332";width: rootItem.width;onClicked: {rootWindow.startDataView(startString)}}
    }

    ListView {
        anchors.fill: parent
        model: itemModel
    }

}


