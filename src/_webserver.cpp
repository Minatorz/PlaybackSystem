#include "_webserver.h"
#include "_file.h"
#include "_midi.h"

WebServer server(80);
String cueDataJson = "[]";
int currentCueIndex = 0;

void getWebFiles() {
    // Define route to serve the HTML file
    server.on("/", []() {
        File file = openFile("/index.html", "r");
        if (!file) {
            Serial.println("Failed to open file for reading");
            server.send(404, "text/plain", "File Not Found");
            return;
        }
        server.streamFile(file, "text/html");
        file.close();
    });

    // Serve CSS file
    server.on("/styles.css", []() {
        File file = openFile("/styles.css", "r");
        if (!file) {
            Serial.println("Failed to open CSS file for reading");
            server.send(404, "text/plain", "File Not Found");
            return;
        }
        server.streamFile(file, "text/css");
        file.close();
    });

    // Serve JavaScript file
    server.on("/script.js", []() {
        File file = openFile("/script.js", "r");
        if (!file) {
            Serial.println("Failed to open JS file for reading");
            server.send(404, "text/plain", "File Not Found");
            return;
        }
        server.streamFile(file, "application/javascript");
        file.close();
    });
}

void StartButton(){  
    server.on("/start", []() {
        digitalWrite(LED_BUILTIN, HIGH);
        MIDInoteSent(60, 127, 1);
        server.send(200, "text/plain", "START");
    });
}

void StopButton() {
    server.on("/stop", []() {
        digitalWrite(LED_BUILTIN, LOW);
        MIDInoteSent(61, 127, 1);
        server.send(200, "text/plain", "STOP");
    });
}

void SelectSongButton() {
    server.on("/select_song", HTTP_POST, []() {
    Serial.println("Received request for /select_song");

    // Instead of server.hasArg("plain"), we will directly read the body
    if (server.hasArg("plain")) {
        String body = server.arg("plain");
        Serial.println("Body: " + body);

        // Create a JSON document to parse the received cue data
        DynamicJsonDocument doc(1024);
        DeserializationError error = deserializeJson(doc, body);

        if (!error) {
            // Extract index
            int index = doc["index"];
            Serial.printf("Selected song index: %d\n", index);
            MIDInoteSent(64 + index, 127, 1);
            server.send(200, "text/plain", "Song index received");
        } else {
            Serial.println("Failed to parse JSON data");
            server.send(400, "text/plain", "Invalid JSON format");
        }
    } else {
        Serial.println("No data received");
        server.send(400, "text/plain", "No data received");
    }
});
}

void CueData() {
    server.on("/current_song", HTTP_GET, []() {
        // Create a JSON response with the current song index
        DynamicJsonDocument responseDoc(1024);
        responseDoc["currentIndex"] = currentCueIndex;

        String jsonResponse;
        serializeJson(responseDoc, jsonResponse);

        server.send(200, "application/json", jsonResponse);
        Serial.println("Sent current song index to client: " + jsonResponse);
        });


    server.on("/cue_data", HTTP_POST, []() {
        if (server.hasArg("plain")) {
            cueDataJson = server.arg("plain"); // Update the cue data
            Serial.println("Received Cue Data: " + cueDataJson);
            server.send(200, "text/plain", "Cue data received");
        } else {
            server.send(400, "text/plain", "No data received");
        }
    });

    server.on("/cue_data", HTTP_GET, []() {
        server.send(200, "application/json", cueDataJson);
    });

}

void initializeWebServer() {
    getWebFiles();
    StartButton();
    StopButton();
    SelectSongButton();
    CueData();
    // Start the server
    server.begin();
    Serial.println("Start the Web Server!");
}

void handleWebServer() {
    server.handleClient();
}