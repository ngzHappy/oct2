import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

MouseArea {
    id:rootMouseArea;
    hoverEnabled: true;
    height: 32;
    acceptedButtons: Qt.LeftButton;
    property string projectName: "";
    property alias startString: startStringID.text;
    onClicked: {rootWindow.startApplication(projectName,startString)}
    Rectangle {
        id:thisRect
        anchors.fill: parent;
        color: Qt.rgba(
                   0.32+Math.random()/3.5,
                   0.32+Math.random()/3.5,
                   0.32+Math.random()/3.5,
                   1);
        border.color: "black";

        states: [
            State{
                name: "mouseOn"
                PropertyChanges { target: thisRect; color: Qt.rgba(0.6,0.7,0.8,1)}
                when:rootMouseArea.containsMouse;
            }
        ]

        Row {
            x:16;
            height:thisRect.height;
            Text {
                id:projectNameID;
                width: 300;
                height: rootMouseArea.height;
                color: "#f5eeee"
                text: projectName+" :";
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignRight
                font.pixelSize: rootMouseArea.height/2;
            }
            TextField {
                id:startStringID
                text:"";
                width:rootMouseArea.width-projectNameID.width;
                font.pixelSize: rootMouseArea.height-8;
                verticalAlignment: Text.AlignVCenter;
                horizontalAlignment: Text.AlignLeft;
                height: rootMouseArea.height;
                placeholderText: qsTr("启动参数")
                style: TextFieldStyle{
                    textColor: "black";
                    background: Rectangle {color: Qt.rgba(.3,.3,.3,.2);}
                }
                }
        }


    }
}










