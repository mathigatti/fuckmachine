#ifdef ESP8266
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif
#include <WiFiUdp.h>
#include <OSCMessage.h>
#include <OSCBundle.h>
#include <OSCData.h>

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
