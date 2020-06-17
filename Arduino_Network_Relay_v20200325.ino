/*
  Arduino Relay for Companion module. https://bitfocus.io/companion/
  March 28, 2020
  by Karsten Wolf in quarantine on an island

  Tested with arduino nano and ENC28J60 ethernet module


  Majortity of code taken from: https://www.arduino.cc/en/Tutorial/WebServer
  Some code taken from: https://create.arduino.cc/projecthub/adachsoft_com/how-to-make-lan-ethernet-relay-switch-using-arduino-uno-cb54fd

  Circuit:
  Ethernet shield attached to pins 10, 11, 12, 13
  Relays attached A0 thru A7

*/

#include <SPI.h>
#include <UIPEthernet.h>
#include <string.h>

#define PIN_LED 2
#define PIN_RELAY_0 A0
#define PIN_RELAY_1 A1
#define PIN_RELAY_2 A2
#define PIN_RELAY_3 A3
#define PIN_RELAY_4 A4
#define PIN_RELAY_5 A5
#define PIN_RELAY_6 A6
#define PIN_RELAY_7 A7

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(10, 0, 0, 222);

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  // print Start
  Serial.print("START");
  // sets up the pin mode to output
  pinMode(PIN_RELAY_0, OUTPUT);
  pinMode(PIN_RELAY_1, OUTPUT);
  pinMode(PIN_RELAY_2, OUTPUT);
  pinMode(PIN_RELAY_3, OUTPUT);
  pinMode(PIN_RELAY_4, OUTPUT);
  pinMode(PIN_RELAY_5, OUTPUT);
  pinMode(PIN_RELAY_6, OUTPUT);
  pinMode(PIN_RELAY_7, OUTPUT);

  // Sets the default mode to off for all pins
  SW(0, 0);
  SW(1, 0);
  SW(2, 0);
  SW(3, 0);
  SW(4, 0);
  SW(5, 0);
  SW(6, 0);
  SW(7, 0);

  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}


void loop() {

  char clientline[BUFSIZ];
  int index = 0;

  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");

    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply

        // If it isn't a new line, add the character to the buffer
        if (c != '\n' && c != '\r') {
          clientline[index] = c;
          index++;
          // are we too big for the buffer? start tossing out data
          if (index >= BUFSIZ)
            index = BUFSIZ - 1;

          // continue to read more data!
          continue;
        }

        // got a \n or \r new line, which means the string is done
        clientline[index] = 0;

        char * pch;
        pch = strtok (clientline, "&");
        while (pch != NULL)
        {
          if (isDigit(pch[0])) {
            //   int temp1;
            byte temp1 = (byte)pch[0] - '0';
            //    bool temp2;
            bool temp2 = (int)pch[2] - '0';

            //Calls the switch function
            SW(temp1, temp2);

            /* debugging prints out variables from the above
              Serial.print('\n');
              //Serial.print(pch);
              Serial.print('\n');
              //Serial.print(pch[0]);
              Serial.print('\n');
              //Serial.print(pch[2]);
              Serial.print('\n');
            */
          }

          // This does something and seems important
          pch = strtok (NULL, "&");
        }

        if (c == '\n' && currentLineIsBlank) {

          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.print(c);
          client.print("Hi thank you for your interest in tactical defenestration.");

          // optinally add a meta refresh tag, so the browser pulls again every 30 seconds:
          // client.println("<meta http-equiv=\"refresh\" content=\"30\">");

          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(10);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}

// Can be used to impliment a way to read current state
bool SW_state(byte num) {
  bool val;
  switch (num) {
    case 0: val = digitalRead(PIN_RELAY_0);
      break;
    case 1: val = digitalRead(PIN_RELAY_1);
      break;
    case 2: val = digitalRead(PIN_RELAY_2);
      break;
    case 3: val = digitalRead(PIN_RELAY_3);
      break;
    case 4: val = digitalRead(PIN_RELAY_4);
      break;
    case 5: val = digitalRead(PIN_RELAY_5);
      break;
    case 6: val = digitalRead(PIN_RELAY_6);
      break;
    case 7: val = digitalRead(PIN_RELAY_7);
      break;
  }
  return !val;
}

// used to set Pin state
void SW(int num, int val) {
  val = !val;
  switch (num) {
    case 0: digitalWrite(PIN_RELAY_0, val);
      break;
    case 1: digitalWrite(PIN_RELAY_1, val);
      break;
    case 2: digitalWrite(PIN_RELAY_2, val);
      break;
    case 3: digitalWrite(PIN_RELAY_3, val);
      break;
    case 4: digitalWrite(PIN_RELAY_4, val);
      break;
    case 5: digitalWrite(PIN_RELAY_5, val);
      break;
    case 6: digitalWrite(PIN_RELAY_6, val);
      break;
    case 7: digitalWrite(PIN_RELAY_7, val);
      break;
  }
}
