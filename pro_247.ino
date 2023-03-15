#include <WiFi.h>
#include <WebServer.h>

const char ssid[]= "ishu_7521";
const char password[]="ishu@20088";

const byte r_pin=18;
const byte g_pin=19;
const byte b_pin=21;

const byte r_channel=0;
const byte g_channel=1;
const byte b_channel=2;

const int frequency=5000;
const int resolution=8;

WebServer server(80);

void setup() {
  // put your setup code here, to run once:
  ledcSetup(r_channel, frequency, resolution);
  ledcSetup(g_channel, frequency, resolution);
  ledcSetup(b_channel, frequency, resolution);

  ledcAttachPin(r_pin, r_channel);
  ledcAttachPin(g_pin, g_channel);
  ledcAttachPin(b_pin, b_channel);

  Serial.begin(115200);

  Serial.print("Connecting with: ");
  Serial.println(ssid);
  WiFi.begin(ssid,password);
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(450);
  }
  Serial.println();
  Serial.println("Connected with the network! ");
  Serial.print("IP Address assigned by the access point: ");
  Serial.println(WiFi.localIP());

  server.on("/",handle_root);
  server.on("/red",handle_red);
  server.on("/green",handle_green);
  server.on("/blue",handle_blue);
  server.on("/yellow",handle_yellow);
  server.on("/cyan",handle_cyan);
  server.on("/magenta",handle_magenta);
  server.on("/orange",handle_orange);
  server.on("/purple",handle_purple);
  server.on("/black",handle_black);
  server.on("/white",handle_white);
  server.on("/brown",handle_brown);
  server.on("/sea",handle_sea);

  server.onNotFound(handle_notfound);

  server.begin();
  Serial.println("HTTP SERVER STARTED");

}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
}

void handle_root(){
  Serial.println("No color");
  String html=generate_html();
  server.send(200, "text/html",html);
}

void handle_red(){
  Serial.println("Red color");
  String html=generate_html();
  color_generator(255,0,0);
  server.send(200, "text/html",html);
}

void handle_green(){
  Serial.println("Green color");
  String html=generate_html();
  color_generator(0,255,0);
  server.send(200, "text/html",html);
}

void handle_blue(){
  Serial.println("Blue color");
  String html=generate_html();
  color_generator(0,0,255);
  server.send(200, "text/html",html);
}

void handle_orange(){
  Serial.println("Orange color");
  String html=generate_html();
  color_generator(255,147,0);
  server.send(200, "text/html",html);
}

void handle_cyan(){
  Serial.println("Cyan color");
  String html=generate_html();
  color_generator(0,255,255);
  server.send(200, "text/html",html);
}

void handle_magenta(){
  Serial.println("Magenta color");
  String html=generate_html();
  color_generator(255,0,255);
  server.send(200, "text/html",html);
}

void handle_yellow(){
  Serial.println("Yellow color");
  String html=generate_html();
  color_generator(255, 195, 0);
  server.send(200, "text/html",html);
}

void handle_purple(){
  Serial.println("Purple color");
  String html=generate_html();
  color_generator(142, 68, 173);
  server.send(200, "text/html",html);
}

void handle_black(){
  Serial.println("Black color");
  String html=generate_html();
  color_generator(0, 4, 3);
  server.send(200, "text/html",html);
}

void handle_white(){
  Serial.println("White color");
  String html=generate_html();
  color_generator(255, 255, 255);
  server.send(200, "text/html",html);
}

void handle_brown(){
  Serial.println("Brown color");
  String html=generate_html();
  color_generator(199, 0, 57 );
  server.send(200, "text/html",html);
}

void handle_sea(){
  Serial.println("Sea color");
  String html=generate_html();
  color_generator(22, 160, 133);
  server.send(200, "text/html",html);
}

void handle_notfound(){
  server.send(200,"text/palin","Can't find anything! Please try again later!");
}

void color_generator(int r, int g, int b){
  ledcWrite(r_channel, r);
  ledcWrite(g_channel, g);
  ledcWrite(b_channel, b);
}

String generate_html(){

  String html = "<!DOCTYPE html>\n";
         html += "<html lang=\"en\">\n";
         html += "<head>\n";
         html += "<meta charset=\"UTF-8\">\n";
         html += "<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n";
         html += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
         html += "<title>ESP32 RGB CONTROLLER</title>\n";
         html += "</head>\n";
         html += "<body>\n";
         html += "<div style=\"padding-left: 50%; padding-top: 10%;\">\n";
         html += "<h1>COLOR GENERATOR</h1>\n";
         html += "</div>\n";

         html += "<div style=\"padding-left: 40%;\">\n";
         html += "<a href=\"/red\"><button>Red</button></a>\n";
         html += "<a href=\"/green\"><button>Green</button></a>\n";
         html += "<a href=\"/blue\"><button>Blue</button></a>\n";
         html += "<a href=\"/yellow\"><button>Yellow</button></a>\n";
         html += "<a href=\"/cyan\"><button>Cyan</button></a>\n";
         html += "<a href=\"/magenta\"><button>Magenta</button></a>\n";
         html += "<a href=\"/orange\"><button>Orange</button></a>\n";
         html += "<a href=\"/purple\"><button>Purple</button></a>\n";
         html += "<a href=\"/black\"><button>Black</button></a>\n";
         html += "<a href=\"/white\"><button>White</button></a>\n";
         html += "<a href=\"/brown\"><button>Brown</button></a>\n";
         html += "<a href=\"/sea\"><button>Sea_Green</button></a>\n";
         html += "</div>\n";
    
         html += "</body>\n";
         html += "</html>\n";
  
  return html;  

}
