//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Set the Text via Web Server
/*
 * The original source code to "running Text" : https://github.com/busel7/DMDESP/blob/master/examples/TeksDiamdanJalan/TeksDiamdanJalan.ino by  busel7
 * Links to download the DMDESP library : https://github.com/busel7/DMDESP
*/

//----------------------------------------Include Library
//----------------------------------------see here: https://www.youtube.com/watch?v=8jMr94B8iN0 to add NodeMCU ESP8266 library and board
#include <ESP8266WebServer.h>
#include <DMDESP.h>
#include <DMD2.h>
#include <fonts/DejaVuSansBold9.h>
#include <fonts/ElektronMart6x12.h>
#include <fonts/Droid_Sans_12.h>
#include <fonts/Arial_Black_16.h>
//----------------------------------------

#include "PageInd.h" //--> Include the contents of the User Interface Web page, stored in the same folder as the .ino file

//----------------------------------------Make a wifi name and password as access point
const char* ssid = "WEMOS";
const char* password = "DMD12345";
//----------------------------------------

ESP8266WebServer server(80); //--> Server on port 80

//----------------------------------------DMD Configuration (P10 Panel)
#define DISPLAYS_WIDE 4 //--> Panel Columns
#define DISPLAYS_HIGH 1 //--> Panel Rows
DMDESP Disp(DISPLAYS_WIDE, DISPLAYS_HIGH);  //--> Number of Panels P10 used (Column, Row)
//----------------------------------------

char *Text[] = {"BY ALI.."}; //--> Variable for scrolling Text. Don't leave this variable blank
String Incoming_Text = ""; //--> Variable to hold the text that is sent from a web server (web page)

//========================================================================This routine is executed when you open NodeMCU ESP8266 IP Address in browser
void handleRoot() {
  server.send(200, "text/html", MAIN_page); //--> Send web page
}
//========================================================================

//========================================================================Subroutines to handle incoming Text Data
void handle_Incoming_Text() {
  Incoming_Text = server.arg("TextContents");
  server.send(200, "text/plane", ""); //--> Send web page
  Process_Incoming_Text();
}
//========================================================================

//========================================================================Subroutines for processing incoming Text to be displayed in the P10 Panel
void Process_Incoming_Text() {
  delay(500);
  Serial.println("Incoming text : ");
  Serial.println(Incoming_Text);
  Serial.println();
  int str_len = Incoming_Text.length() + 1;
  char char_array[str_len];
  Incoming_Text.toCharArray(char_array, str_len);
  strcpy(Text[0], char_array);
  Incoming_Text = "";
}
//========================================================================

//========================================================================VOID SETUP()
void setup(){
  Serial.begin(115200);
  delay(500);

  //----------------------------------------DMDESP Setup
  Disp.start(); //--> Run the DMDESP library
  Disp.setBrightness(255); //--> Brightness level
  Disp.setFont(Arial_Black_16); //--> Determine the font used
  Disp.drawRect(0, 0, 127, 15);
  //----------------------------------------
  
  WiFi.softAP(ssid, password);  //--> Start Making ESP8266 NodeMCU as an access point
  Serial.println("");
  
  IPAddress apip = WiFi.softAPIP(); //--> Get the IP server
  Serial.print("Connect your wifi laptop/mobile phone to this NodeMCU Access Point : ");
  Serial.println(ssid);
  Serial.print("Visit this IP : ");
  Serial.print(apip); //--> Prints the IP address of the server to be visited
  Serial.println(" in your browser.");
 
  server.on("/", handleRoot); //--> Routine to handle at root location. This is to display web page.
  server.on("/setText", handle_Incoming_Text);  //--> Routine to handle handle_Incoming_Text Subroutines
  
  server.begin(); //--> Start server
  Serial.println("HTTP server started");
}
//========================================================================

//========================================================================VOID LOOP()
void loop(){
  server.handleClient();  //--> Handle client requests

  Disp.loop(); //--> Run "Disp.loop" to refresh the LED
  //Disp.drawText(4, 0, "ROUTE"); //--> Display text "Disp.drawText(x position, y position, text)"
  Scrolling_Text(1, 500); //--> Show running text "Scrolling_Text(y position, speed);"
}
//========================================================================

//========================================================================Subroutines for scrolling Text
void Scrolling_Text(int y, uint8_t scrolling_speed) {
  static uint32_t pM;
  static uint32_t x;
  int width = Disp.width();
  Disp.setFont(Arial_Black_16);
  int fullScroll = Disp.textWidth(Text[0]) + width;
  if((millis() - pM) > scrolling_speed) { 
    pM = millis();
    if (x < fullScroll) {
      ++x;
    } else {
      x = 0;
      return;
    }
    Disp.drawText(width - x, y, Text[0]);
  }  
}
//========================================================================
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
