import QtQuick 2.0
import Kaj.Rest 1.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
WebRequest {
    id: service
    url: "http://httpbin.org/post"
    loadingText: "Posting data"
    data: JsonPostData {
        data: ({
                   name: 'hamed',
                   n: 1
               })
    }

    response: JsonResponse {
        onFinished: output.text = JSON.stringify(data)
        onError: console.log("error", descript)
    }
}

    ColumnLayout {
        Button {
            text: "Send"
            onClicked: service.send()
        }
        TextArea {
            id: output
            Layout.fillHeight: true
            Layout.fillWidth: true
            wrapMode: "WordWrap"
        }
    }

}
