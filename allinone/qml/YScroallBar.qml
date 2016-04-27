import QtQuick 2.5

Rectangle{/*Y scroall bar*/
    id:scroallBarID;
    width: 12;
    height: view.height;
    anchors.top: view.top;
    anchors.right: view.right;
    color: Qt.rgba(0.2,0.5,0.6,0.3);
    property var view;

    Rectangle{
        id:scroallBarItem;
        width:parent.width;
        height: 36;
        gradient: Gradient {
            GradientStop {
                position: 0.00;
                color: Qt.rgba(0.9,0.9,0.9,0.8);
            }
            GradientStop {
                position: 1.00;
                color: Qt.rgba(0.95,0.9,0.9,0.1);
            }
        }

        anchors.left: parent.left;

        y:(function(){
            if(parent.height>=view.contentHeight){
                return 0;
            }
            var varPercent=(view.contentY/(view.contentHeight-parent.height));
            return Math.max(0,varPercent*(parent.height-height));
        }/*~function*/)();

        MouseArea{
            id:scroallBarItemMouseAreaID;
            anchors.fill: parent;
            drag.target: parent;
            drag.axis: Drag.YAxis;
            drag.minimumY: 0;
            drag.maximumY: Math.max(0,scroallBarID.height-height);

        }

        onYChanged: {
            if(scroallBarItemMouseAreaID.drag.active===false){return;}
            var varHeight=view.contentHeight-scroallBarID.height;
            if(varHeight<0){return;}
            if(height>=scroallBarID.height){return;}
            var persent=scroallBarItem.y/(scroallBarID.height-height) ;
            if(persent<0){return;}
            var varY=varHeight*persent;
            if(Math.abs(view.contentY-varY)>0.005){
                view.contentY=varY;
            }
        }

    }

}/*~Y scroall bar*/
