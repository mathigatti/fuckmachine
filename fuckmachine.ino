#ifdef ESP8266
#include <WiFiUdp.h>
#include <OSCMessage.h>
#include <OSCBundle.h>
#include <OSCData.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h> // Include this for WiFiClientSecure

// https://github.com/CNMAT/OSC/tree/master

char ssid[] = "internet cel";
char pass[] = "1nt3rn3t";

WiFiUDP Udp;
const unsigned int localPort = 10000;

const int in1 = 5;  // Please change this pin according to your connection
const int in2 = 4;  // Please change this pin according to your connection
const int en = 0;   // Please change this pin according to your connection

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(en, OUTPUT);

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWriteRange(1024);
  analogWriteFreq(20000):
  analogWrite(en, 1023); // 10% duty cycle (since the ESP uses 10 bit PWM, 1023 is full throttle)

  Serial.begin(115200);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Starting UDP");
  Udp.begin(localPort);
  Serial.print("Local port: ");
#ifdef ESP32
  Serial.println(localPort);
#else
  Serial.println(Udp.localPort());
#endif
}

void postIP() {
  #ifdef ESP8266

  String postData = String("{\"USER_ID\":\"test1\", \"IP\":\"") + WiFi.localIP().toString() + "\"}";
  String host = "us-central1-my-project-1470448662992.cloudfunctions.net";
  const int port = 443;  // HTTPS port
  WiFiClientSecure client;

  if (client.connect(host.c_str(), port)) {
      client.print(String("POST /fuckmachine/ HTTP/1.1\r\n") +
                  "Host: " + host + "\r\n" +
                  "Connection: close\r\n" +
                  "Content-Type: application/json\r\n" +
                  "Content-Length: " + postData.length() + "\r\n" +
                  "\r\n" +
                  postData + "\r\n");             
  } else {
    Serial.println("No me pude conectar :(");
  }

  delay(10);  // Give server some time to receive
  
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      break;
    }
  }

  String response = client.readStringUntil('\n');
  Serial.println(response);

  #endif
}

void getWiFiCredentials() {
  #ifdef ESP8266
  HTTPClient http;
  WiFiClient client;
  http.begin(client, String("https://us-central1-my-project-1470448662992.cloudfunctions.net/fuckmachine-wifi/?USER_ID=test1"));
  int httpResponseCode = http.GET();
  if(httpResponseCode>0){
    String response = http.getString();
    Serial.println(httpResponseCode);
    Serial.println(response);
    
    // Suponiendo que la respuesta tiene el formato {"SSID":"mySSID", "PASS":"myPassword"}
    int ssidStart = response.indexOf("\"SSID\":\"") + 8;
    int ssidEnd = response.indexOf("\"", ssidStart);
    int passStart = response.indexOf("\"PASS\":\"") + 8;
    int passEnd = response.indexOf("\"", passStart);
    
    if(ssidStart > 7 && ssidEnd > ssidStart && passStart > 7 && passEnd > passStart) {
      response.substring(ssidStart, ssidEnd).toCharArray(ssid, sizeof(ssid));
      response.substring(passStart, passEnd).toCharArray(pass, sizeof(pass));

      // Guardar las credenciales en el sistema de archivos
      File configFile = SPIFFS.open("/config.txt", "w");
      if(!configFile) {
        Serial.println("Failed to open config file for writing");
        return;
      }
      configFile.println(ssid);
      configFile.println(pass);
      configFile.close();
    }
  } else {
    Serial.print("Error on sending GET: ");
    Serial.println(httpResponseCode);
  }
  http.end();
  #endif
}

void toggleHandler(OSCMessage &msg) {
  int state = (int) msg.getFloat(0);
  if (state == 0) {
    stop();
  } else {
    start();
  }
  Serial.println(state);
}

void sliderHandler(OSCMessage &msg) {
  float volume = msg.getFloat(0);
  int speed = (int)(volume * 1023);  // Convert volume [0,1] to duty cycle [0,1023], The ESP8266's PWM is 10-bit, so its range is [0,1023]. 
  motorSpeed(speed);
  Serial.println(speed);
}

void motorSpeed(int speed) {
  analogWrite(en, speed);
}

void stop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}

void start() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
}

void loop() {
  OSCBundle bundle;
  int size = Udp.parsePacket();

  if (size > 0) {
    while (size--) {
      bundle.fill(Udp.read());
    }
    if (!bundle.hasError()) {
      bundle.dispatch("/oscControl/toggle1", toggleHandler);
      bundle.dispatch("/oscControl/slider1", sliderHandler);
    } else {
      OSCErrorCode error = bundle.getError();
      Serial.print("error: ");
      Serial.println(error);
    }
  }
}
