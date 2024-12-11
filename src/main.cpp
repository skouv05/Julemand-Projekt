/*********
  Rui Santos
  Complete instructions at https://RandomNerdTutorials.com/build-web-servers-ebook/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

mko:
Der er nu lavet en åbning fra 152.115.47.170 -> 

10.34.144.55 på port 80/443. Så den er klar til i sætter serveren op.
Subnet 255.255.248.0
gateway 10.34.144.1

*********/

#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>

// Replace with your network credentials
const char* ssid = "SESG-GUEST";//netværksnavn
const char* password = "SolsortQ4"; //password

//mko ret herunder
IPAddress ip(192, 168, 1, 53);
IPAddress gateway(192, 168, 1, 254);
IPAddress subnet(255, 255, 255, 0);
IPAddress dns(192, 168, 1, 254); //primaryDNS
IPAddress secondaryDNS(1, 1, 1, 1); // optional

// Json Variable to Hold Sensor Readings
JsonDocument readings;

// button input

// variables will change:
int buttonState = 0;  // variable for reading the pushbutton status
int sendButton = 0; //value to send to mobilephone. zero no button pressed

// button input
const int buttonPin = 17;  // the number of the pushbutton pin
// variables will change:

int time1 = millis();
unsigned long x = 5000;
bool test = false;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

/*String website1 = "<!DOCTYPE html><html><head><title>Julemand</title></head><body style='background-color: #EEEEEE;'><span style='color: #003366;'>  <p id='test1'> <audio id='a2' preload='auto'><source src='https://www.helseviden.dk/juleb/Click.mp3' type='audio/mpeg'></audio> <audio id='a1' preload='auto'><source src='https://www.helseviden.dk/juleb/s2.mp3' type='audio/mpeg'></audio> ";
String website2 = "</p></span> <video id='video', width='320' height='240'> </video><script>";
String javasc1 = "const Audio2 = document.getElementById('a2');const Audio=document.getElementById('a1');const myp=document.getElementById('test1');myp.innerHTML='Button';let timer=setInterval(update,500);function update(){fetch('/button').then((e=>e.json())).then((e=>{'1'==e.button&&(myp.innerHtml=e.button,playspeak(),SendImageServer(TakePhoto()))}))}function playspeak(){Audio.play(); Audio2.play();}function TakePhoto(){let e=document.createElement('canvas'),t=document.getElementById('video');e.width=1920,e.height=1080,e.getContext('2d').drawImage(t,0,0,e.width,e.height);let n=e.toDataURL('image/jpeg');return console.log(n),n}function SendImageServer(e){fetch('https://www.helseviden.dk/juleb/upload1.php',{method:'POST',headers:{'Content-Type':'application/json','Access-Control-Allow-Origin':'*'},'mode':'no-cors',body:JSON.stringify({image:e})}).then((e=>e.json())).then((e=>{console.log('Success:',e)})).catch((e=>{console.error('Error:',e)}))}const constraints={audio:!1,video:{width:1280,height:720}};navigator.mediaDevices.getUserMedia(constraints).then((e=>{const t=document.querySelector('video');t.srcObject=e,t.onloadedmetadata=()=>{t.play()}})).catch((e=>{console.error(`${e.name}: ${e.message}`)}));";
String website3 = "</script></body></html>";
String website = "";*/

String website1 = "<!DOCTYPE html><html lang='da'><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>Julemand</title><style>body { background-color: #8B0000; color: white; text-align: center; margin: 0; padding: 0; } h1 { text-align: center; color: white; text-shadow: 2px 2px 0px green; } #video { display: block; margin: 0 auto; border: 5px solid white; box-sizing: border-box; position: relative; width: 180px; height: 320px; } #snowflakes { position: fixed; top: 0; left: 0; width: 100%; height: 100%; pointer-events: none; z-index: 1000; } .snowflake { position: absolute; top: -10px; background: white; width: 10px; height: 10px; border-radius: 50%; opacity: 0.8; animation: fall linear infinite; } @keyframes fall { to { transform: translateY(100vh); } } @media (orientation: portrait) { #video, .gallery img { width: 100%; height: auto; aspect-ratio: 16/9; } } @media (orientation: landscape) { #video, .gallery img { width: auto; height: 100%; aspect-ratio: 16/9; } }</style></head><body><h1>Glædeligt jul</h1><div id='snowflakes'></div><span style='color: #003366;'> <p id='test1'> <audio id='a2' preload='auto'><source src='https://www.helseviden.dk/juleb/Click.mp3' type='audio/mpeg'></audio> <audio id='a1' preload='auto'><source src='https://www.helseviden.dk/juleb/s2.mp3' type='audio/mpeg'></audio> ";
String website2 = "</p></span> <video id='video'></video><script>";
String javasc1 = "const Audio2 = document.getElementById('a2');const Audio=document.getElementById('a1');const myp=document.getElementById('test1');myp.innerHTML='Button';let timer=setInterval(update,500);function update(){fetch('/button').then((e=>e.json())).then((e=>{'1'==e.button&&(myp.innerHTML=e.button,playspeak(),SendImageServer(TakePhoto()))}))}function playspeak(){Audio.play(); Audio2.play();}function TakePhoto(){let e=document.createElement('canvas'),t=document.getElementById('video');e.width=1920,e.height=1080,e.getContext('2d').drawImage(t,0,0,e.width,e.height);let n=e.toDataURL('image/jpeg');return console.log(n),n}function SendImageServer(e){fetch('https://www.helseviden.dk/juleb/upload1.php',{method:'POST',headers:{'Content-Type':'application/json','Access-Control-Allow-Origin':'*'},'mode':'no-cors',body:JSON.stringify({image:e})}).then((e=>e.json())).then((e=>{console.log('Success:',e)})).catch((e=>{console.error('Error:',e)}))}const constraints={audio:!1,video:{width:720,height:1280}};navigator.mediaDevices.getUserMedia(constraints).then((e=>{const t=document.querySelector('video');t.srcObject=e,t.onloadedmetadata=()=>{t.play()}})).catch((e=>{console.error(`${e.name}: ${e.message}`)}));";
String website3 = "</script><script>function createSnowflake() { const snowflake = document.createElement('div'); snowflake.className = 'snowflake'; snowflake.style.left = Math.random() * 100 + 'vw'; snowflake.style.animationDuration = Math.random() * 3 + 2 + 's'; document.getElementById('snowflakes').appendChild(snowflake); setTimeout(() => { snowflake.remove(); }, 5000); } setInterval(createSnowflake, 100);</script></body></html>";

String website = "";

void initWiFi() {
  WiFi.mode(WIFI_STA);
  //WiFi.config(ip, dns, gateway, subnet); 
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}

// Get Sensor Readings and return JSON object
String getSensorReadings(){
  
  readings["button"] = String(sendButton);
  String jsonString;
  serializeJson(readings, jsonString);
  return jsonString;
}

void setup() {
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);

  // Serial port for debugging purposes
  Serial.begin(115200);
  initWiFi();
  website = website1 + website2+""+javasc1+""+website3;
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", website);
  });

  // Request for the latest sensor readings
  server.on("/button", HTTP_GET, [](AsyncWebServerRequest *request) {
    String json = getSensorReadings();
    request->send(200, "application/json", json);
    json = String();
    sendButton=0;
  });

  // Start server
  server.begin();
}

void loop() {
  buttonState = digitalRead(buttonPin);
  if ((millis()-time1) > x){
    test=true;
  }
  if ((buttonState==1) && test==true){
    test=false;
    buttonState=0;
    time1=millis();
    sendButton=1;
    Serial.println("Button Pressed"); 
}
}
  