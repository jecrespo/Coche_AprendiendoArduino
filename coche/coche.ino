#include <Bridge.h>
#include <BridgeServer.h>
#include <BridgeClient.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN_IZQ 7
#define PIN_DCHA 8

int R_color = 0;
int G_color = 0;
int B_color = 0;
int brigtness = 1;

BridgeServer server;

Adafruit_NeoPixel strip_IZQ = Adafruit_NeoPixel(12, PIN_IZQ, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_DCHA = Adafruit_NeoPixel(12, PIN_DCHA, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  Bridge.begin();
  server.listenOnLocalhost();
  server.begin();
  strip_IZQ.begin();
  strip_IZQ.show(); // Initialize all pixels to 'off'
  strip_IZQ.setBrightness(brigtness);  //brillo inicial de 0 a 255

  strip_DCHA.begin();
  strip_DCHA.show(); // Initialize all pixels to 'off'
  strip_DCHA.setBrightness(brigtness); //brillo inicial de 0 a 255

}

void loop() {

  //En cada ciclo compruebo que funcione
  BridgeClient client = server.accept();
  if (client) {
    String command = client.readStringUntil('/');
    Serial.println(command);
    if (command == "R") {
      R_color = client.parseInt();
      uint32_t color_IZQ = strip_IZQ.Color(R_color, G_color, B_color);
      uint32_t color_DCHA = strip_DCHA.Color(R_color, G_color, B_color);
      color_D(color_DCHA);
      color_I(color_IZQ);
      Serial.println(R_color);
    }
    if (command == "G") {
      G_color = client.parseInt();
      uint32_t color_IZQ = strip_IZQ.Color(R_color, G_color, B_color);
      uint32_t color_DCHA = strip_DCHA.Color(R_color, G_color, B_color);
      color_D(color_DCHA);
      color_I(color_IZQ);
      Serial.println(G_color);
    }
    if (command == "B") {
      B_color = client.parseInt();
      uint32_t color_IZQ = strip_IZQ.Color(R_color, G_color, B_color);
      uint32_t color_DCHA = strip_DCHA.Color(R_color, G_color, B_color);
      color_D(color_DCHA);
      color_I(color_IZQ);
      Serial.println(B_color);
    }
    if (command == "S") { //Brillo
      brigtness = client.parseInt();
      strip_IZQ.setBrightness(brigtness);
      strip_DCHA.setBrightness(brigtness);
      strip_DCHA.show();
      strip_IZQ.show();
      Serial.println(brigtness);
    }
    if (command.startsWith("F")) { //Forward
      //Serial.println(command);
      digitalWrite(3,LOW);
      digitalWrite(4,HIGH);
      digitalWrite(5,HIGH);
      digitalWrite(6,LOW);
    }
    if (command.startsWith("K")) { //Backward
      //Serial.println(command);
      digitalWrite(3,HIGH);
      digitalWrite(4,LOW);
      digitalWrite(5,LOW);
      digitalWrite(6,HIGH);
    }
    if (command.startsWith("H")) { //Right
      //Serial.println(command);
      digitalWrite(3,LOW);
      digitalWrite(4,LOW);
      digitalWrite(5,HIGH);
      digitalWrite(6,LOW);
    }
    if (command.startsWith("L")) { //Left
      //Serial.println(command);
      digitalWrite(3,LOW);
      digitalWrite(4,HIGH);
      digitalWrite(5,LOW);
      digitalWrite(6,LOW);
    }
    if (command.startsWith("P")) { //Stop
      //Serial.println(command);
      digitalWrite(3,LOW);
      digitalWrite(4,LOW);
      digitalWrite(5,LOW);
      digitalWrite(6,LOW);
    }
    client.stop();
  }
}

void color_D(uint32_t c) {
  for(uint16_t i=0; i<strip_DCHA.numPixels(); i++) {
    strip_DCHA.setPixelColor(i, c);
    strip_DCHA.show();
  }
}

void color_I(uint32_t c) {
  for(uint16_t i=0; i<strip_IZQ.numPixels(); i++) {
    strip_IZQ.setPixelColor(i, c);
    strip_IZQ.show();
  }
}
