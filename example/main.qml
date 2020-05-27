import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import Kaj.Rest 1.0 as Rest

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    ColumnLayout {
        anchors.fill: parent

        TabBar {
            id: tab
            Layout.fillWidth: true
            TabButton{
                text: "Get"
            }
            TabButton{
                text: "Post"
            }
            TabButton{
                text: "Image"
            }
            TabButton{
                text: "File upload"
            }
        }

        StackLayout {
            currentIndex: tab.currentIndex

            Layout.fillWidth: true
            Layout.fillHeight: true
            Get {}
            Post {}
            ImageRequest {}
            FileUpload {}
        }
        Text {
            text: "Is database cache enabled: " + Rest.WebRequestCacheInstance.databaseEnabled

        }

    }

    Pane {
        visible: Rest.WebRequestManagerInstance.loadingTexts.length > 0
        anchors.centerIn: parent
        ColumnLayout {
            Repeater {
                model: Rest.WebRequestManagerInstance.loadingTexts
                Text {
                    text: modelData
                }
            }
        }
    }
}
