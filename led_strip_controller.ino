#include <ESP8266WiFi.h>
WiFiClient client;
WiFiServer server(80);

/* WIFI settings */
const char* ssid = "Fios-S3W4G";   //WIFI SSID
const char* password = "ripe689crow9356paw";    //WIFI PASSWORD

/* data received from application */
String  data =""; 

/* define LED strip pins */
int rLED = 14;    //D5
int gLED = 12;    //D6
int bLED = 13;     //D7

/* Brightness variables */
int brightness = 200; //max is 255
float rBright = 0;
float gBright = 0;
float bBright = 0;

/* ON/OFF */
int power = 1;
float rHold = 0;
float gHold = 0;
float bHold = 0;

void setup()
{
  /* initialize LED strip pins as output */
  pinMode(rLED, OUTPUT);
  pinMode(gLED, OUTPUT); 
  pinMode(bLED, OUTPUT); 

  digitalWrite(rLED,LOW);
  digitalWrite(gLED,LOW);
  digitalWrite(bLED,LOW);
  
  /* start server communication */
  Serial.begin(115200);
  connectWiFi();
  server.begin();
}

void loop()
{
    /* If the server available, run the "checkClient" function */  
    client = server.available();
    if (!client) return; 
    data = checkClient ();
Serial.print(data);
/************************ Run function according to incoming data from application *************************/

    if (data.substring(6,7) == "!"){
      brightness = data.substring(7).toInt();
      Serial.print(data.substring(7));
    }
    
    if (data == "ON"){
      power = 1;
      rBright = rHold;
      gBright = gHold;
      bBright = bHold;
    }
    if (data == "OFF"){
      power = 0;
      rBright = 0;
      gBright = 0;
      bBright = 0;
    }
    
    if ((data == "RED" && power == 1)){ 
      rBright = 1.0;
      gBright = 0;
      bBright = 0;
      rHold = 1.0;
      gHold = 0;
      bHold = 0;
    }
    else if (data == "GREEN" && power == 1){ 
      rBright = 0;
      gBright = 1.0;
      bBright = 0;
      rHold = 0;
      gHold = 1.0;
      bHold = 0;
    }
    else if (data == "BLUE" && power == 1){ 
      rBright = 0;
      gBright = 0;
      bBright = 1.0;
      rHold = 0;
      gHold = 0;
      bHold = 1.0;
    }
    else if (data == "MAGENTA" && power == 1){ 
      rBright = 1.0;
      gBright = 0;
      bBright = 1.0;
      rHold = 1.0;
      gHold = 0;
      bHold = 1.0;
    }
    else if (data == "CYAN" && power == 1){ 
      rBright = 0;
      gBright = 1.0;
      bBright = 1.0;
      rHold = 0;
      gHold = 1.0;
      bHold = 1.0;
    }
    else if (data == "YELLOW" && power == 1){ 
      rBright = 1.0;
      gBright = 1.0;
      bBright = 0;
      rHold = 1.0;
      gHold = 1.0;
      bHold = 0;
    }
    else if (data == "ORANGE" && power == 1){ 
      rBright = 1.0;
      gBright = 0.5;
      bBright = 0;
      rHold = 1.0;
      gHold = 1.0;
      bHold = 0;
    }
    else if (data == "ROSE" && power == 1){ 
      rBright = 1.0;
      gBright = 0;
      bBright = 0.5;
      rHold = 1.0;
      gHold = 0;
      bHold = 0.5;
    }
    else if (data == "VIOLET" && power == 1){ 
      rBright = 0.5;
      gBright = 0;
      bBright = 1.0;
      rHold = 0.5;
      gHold = 0;
      bHold = 1.0;
    }
    else if (data == "AZURE" && power == 1){ 
      rBright = 0;
      gBright = 0.5;
      bBright = 1.0;
      rHold = 0;
      gHold = 0.5;
      bHold = 1.0;
    }
    else if (data == "SPRINGGREEN" && power == 1){ 
      rBright = 0;
      gBright = 1.0;
      bBright = 0.5;
      rHold = 0;
      gHold = 1.0;
      bHold = 0.5;
    }
    else if (data == "CHARTREUSE" && power == 1){ 
      rBright = 0.5;
      gBright = 1.0;
      bBright = 0;
      rHold = 0.5;
      gHold = 1.0;
      bHold = 0;
    }
    

      setColor(rBright, gBright, bBright, brightness);
} 

void setColor (float r,float g,float b, int brightness){
  analogWrite(rLED,round(brightness * r));
  analogWrite(gLED,round(brightness * g));
  analogWrite(bLED,round(brightness * b));
}

void connectWiFi()
{
  Serial.println("Connecting to WIFI");
  WiFi.begin(ssid, password);
  while ((!(WiFi.status() == WL_CONNECTED)))
  {
    delay(300);
    Serial.print("..");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("NodeMCU Local IP is : ");
  Serial.print((WiFi.localIP()));
}
/********************************** RECEIVE DATA FROM the APP ******************************************/
String checkClient (void)
{
  while(!client.available()) delay(1); 
  String request = client.readStringUntil('\r');
  request.remove(0, 5);
  request.remove(request.length()-9,9);
  return request;
}
