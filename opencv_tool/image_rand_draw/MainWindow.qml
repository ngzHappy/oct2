import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.1

Rectangle {
    id:rootItemID
    width: 1000;
    height:1000;
    color: "#29b3d1"

    function setImage(image_name){
        imageID.source=image_name
    }

    ColumnLayout {
        anchors.fill: parent
        width: 339
        height: 540
        spacing: 0

        RowLayout {
            id: rowLayout1
            width: 428
            height: 100
            spacing: 0
            Button {
                id: sourceButtonID
                text: qsTr("选择源文件")
                Layout.fillWidth: true
                onClicked: {rootWindow.selectImage()}
            }

            Button {
                id: targetButtionID
                text: qsTr("保存目录")
                Layout.fillWidth: true
                onClicked: {rootWindow.selectDir()}
            }

            Button {
                id: saveButtonID
                text: qsTr("保存")
                Layout.fillWidth: true
                visible: dirViewID.text
                onClicked: {rootWindow.save()}
            }
        }
        TextField{
            id:dirViewID
            text:rootWindow.dstDir
            readOnly: true
            font.pointSize: 16
            Layout.fillWidth: true
            height: 16
            style: TextFieldStyle{
                textColor: "black";
                background: Rectangle {color: Qt.rgba(.3,.3,.3,.0);}
            }
            verticalAlignment: Text.AlignVCenter;
            horizontalAlignment: Text.AlignLeft;
            visible: text
        }
        Rectangle {
            id: rectangle1
            color: Qt.rgba(0,0,0,0)
            clip: true
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.minimumHeight: 100
            Layout.minimumWidth: 100

            Image {
                id: imageID
                fillMode: Image.PreserveAspectFit
                source: rootWindow.imageQmlPath
                anchors.centerIn: parent;
            }

        }

    }



}
