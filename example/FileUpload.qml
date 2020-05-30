import QtQuick 2.0
import Kaj.Rest 1.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import Qt.labs.platform 1.1

Item {
    WebRequest {
        id: service
        url: "https://srv-file16.gofile.io/upload"
        loadingText: "Uploading file"
        useCache: false

        data: FilePostData {
            id: postData
            data: ({
                       category: "file",
                       comments: 0
                   })
        }

        response: StringResponse {
            onFinished: output.text = JSON.stringify(data)
            onError: console.log(descript)
        }
    }

    FileDialog {
        id: fileDialog
        fileMode: FileDialog.OpenFiles
        onAccepted: postData.addFile("filesUploaded", file)
    }

    ColumnLayout {

        Button {
            text: "Select file"
            onClicked: fileDialog.open()
        }

        TextArea {
            id: output
            Layout.fillHeight: true
            Layout.fillWidth: true
            wrapMode: "WordWrap"
            textFormat: "RichText"
        }
        Button {
            text: "Upload"
            onClicked: service.send()
        }
    }

}
