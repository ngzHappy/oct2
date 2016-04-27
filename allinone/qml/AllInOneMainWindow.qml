/*all in one main window*/
import QtQuick 2.5
import QtQml.Models 2.2

/*rootWindow*/

Rectangle {
    width: 1000;
    height: 1000;
    color: Qt.rgba(0.5,0.6,0.5,1);
    id : rootItem;

    function getProjectName(n){
        if(n>=itemModel.count){return "@nil";}
        return itemModel.get(n).projectName;
    }
    function getStartString(n){
        if(n>=itemModel.count){return "@nil";}
        return itemModel.get(n).startString;
    }

    ObjectModel {
        id: itemModel;
        AllInOneItem{projectName:"0";startString:"";width: rootItem.width;}
        AllInOneItem{projectName:"1";startString:"";width: rootItem.width;}
        AllInOneItem{projectName:"2";startString:"";width: rootItem.width;}
        AllInOneItem{projectName:"1";startString:"";width: rootItem.width;}
        AllInOneItem{projectName:"1";startString:"";width: rootItem.width;}
        AllInOneItem{projectName:"1";startString:"";width: rootItem.width;}
        AllInOneItem{projectName:"1";startString:"";width: rootItem.width;}
        AllInOneItem{projectName:"1";startString:"";width: rootItem.width;}
        AllInOneItem{projectName:"1";startString:"";width: rootItem.width;}
        AllInOneItem{projectName:"1";startString:"";width: rootItem.width;}
        AllInOneItem{projectName:"1";startString:"";width: rootItem.width;}
        AllInOneItem{projectName:"1";startString:"";width: rootItem.width;}
        AllInOneItem{projectName:"1";startString:"";width: rootItem.width;}
        AllInOneItem{projectName:"1";startString:"";width: rootItem.width;}
        AllInOneItem{projectName:"1";startString:"";width: rootItem.width;}
        AllInOneItem{projectName:"1";startString:"";width: rootItem.width;}
        AllInOneItem{projectName:"0";startString:"";width: rootItem.width;}
    }

    ListView {
        width: parent.width;
        anchors.fill: parent;
        model: itemModel;
        YScroallBar{view:parent;}
    }

}










