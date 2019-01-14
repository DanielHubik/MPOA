#include <Arduino.h>
#include <cc1101.h>
#include <ccpacket.h>

// Attach CC1101 pins to their corresponding SPI pins
// Uno pins:
// CSN (SS) => 10
// MOSI => 11
// MISO => 12
// SCK => 13
// GD0 => A valid interrupt pin for your platform (defined below this)


#define CC1101Interrupt 0 // Pin 2
#define CC1101_GDO0 2


CC1101 radio;

byte syncWord[2] = {199, 10};
bool packetWaiting;

unsigned long lastSend = 0;
unsigned int sendDelay = 200;

void messageReceived() {
  packetWaiting = true;
}

void setup() {
  radio.init();
  radio.setSyncWord(syncWord);
  radio.setCarrierFreq(CFREQ_433);
  radio.disableAddressCheck();
  radio.setTxPowerAmp(PA_LongDistance);

  Serial.begin(9600);
  Serial.print(F("CC1101_PARTNUM "));
  Serial.println(radio.readReg(CC1101_PARTNUM, CC1101_STATUS_REGISTER));
  Serial.print(F("CC1101_VERSION "));
  Serial.println(radio.readReg(CC1101_VERSION, CC1101_STATUS_REGISTER));
  Serial.print(F("CC1101_MARCSTATE "));
  Serial.println(radio.readReg(CC1101_MARCSTATE, CC1101_STATUS_REGISTER) & 0x1f);

  Serial.println(F("CC1101 radio initialized."));

  pinMode(5, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);



}

// Get signal strength indicator in dBm.
// See: http://www.ti.com/lit/an/swra114d/swra114d.pdf
int rssi(char raw) {
  uint8_t rssi_dec;
  // TODO: This rssi_offset is dependent on baud and MHz; this is for 38.4kbps and 433 MHz.
  uint8_t rssi_offset = 74;
  rssi_dec = (uint8_t) raw;
  if (rssi_dec >= 128)
    return ((int)( rssi_dec - 256) / 2) - rssi_offset;
  else
    return (rssi_dec / 2) - rssi_offset;
}

// Get link quality indicator.
int lqi(char raw) {
  return 0x3F - raw;
}

void loop() {

  int Down = digitalRead(5);
  int Up = digitalRead(9);
  int Left = digitalRead(7);
  int Right = digitalRead(8);
  int Lock=0;
  unsigned long now = millis();
  if (now > lastSend + sendDelay) {
    char message[30];
     char buffera[30];
    lastSend = now;
Lock=0;
    if (Up == LOW) {
      sprintf(message,"UP");
      Serial.println("88888888888888");
    } else if (Down == LOW) {
       Serial.println("2222222222222");
       sprintf(message,"DOWN");
    } else if (Left == LOW) {
       sprintf(message,"LEFT");
          Serial.println("444444444444");
          sendDelay = 200;
    } else if (Right == LOW) {
       sprintf(message,"RIGHT");
          Serial.println("6666666666666");
          if(sendDelay>=20){
           sendDelay-=10;
          }
         
          sprintf(buffera,"%d",sendDelay);
          Serial.println(buffera);
    } else {
      Lock=1;
    }
    if (!Lock){
    CCPACKET packet;
    // We also need to include the 0 byte at the end of the string
    packet.length = strlen(message)  + 1;
    strncpy((char *) packet.data, message, packet.length);

    radio.sendData(packet);
    Serial.println(F("Sent packet..."));
    Serial.println(message);
    
    }
  }
}
