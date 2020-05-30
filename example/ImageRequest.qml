import QtQuick 2.0
import Kaj.Rest 1.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
    WebRequest {
        id: service
        url: "https://avatars1.githubusercontent.com/u/13809362?s=460&u=b94ba941164f4658455759f7063d43d537cb451f&v=4"
        loadingText: "Getting github avatar"

        expireTime.minute: 10

        response: ImageResponse {
            id: imageResponse
//            onFinished: avatar.source = fileName
            onError: console.log("Error ", code, descript)
        }
    }

    ColumnLayout {
        anchors.fill: parent
        Button {
            text: "Get avatar"
            onClicked: service.send()
        }
        Image {
            id: avatar
            source: imageResponse.fileName
            fillMode: Image.PreserveAspectFit
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }

}
