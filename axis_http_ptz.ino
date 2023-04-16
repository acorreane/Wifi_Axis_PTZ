#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define LED_BUILTIN 2

#define pin_ch_up 4
#define pin_ch_dw 5
#define pin_up 16
#define pin_dw 14
#define pin_lt 12
#define pin_rt 13

const char* ssid     = "Your SSID";
const char* password = "Your PASS";   

byte act_channel = 1;

void setup() 
{
  pinMode(LED_BUILTIN, OUTPUT);
  
  pinMode(pin_ch_up, INPUT_PULLUP); pinMode(pin_ch_dw, INPUT_PULLUP);
  pinMode(pin_up, INPUT_PULLUP); pinMode(pin_dw, INPUT_PULLUP);
  pinMode(pin_lt, INPUT_PULLUP); pinMode(pin_rt, INPUT_PULLUP);
  
  delay(200);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(250);
    digitalWrite(LED_BUILTIN, LOW);
    delay(250);
  }
}

void ptz_left(uint8_t ch)
{
 HTTPClient http;
 if (ch == 1) { http.begin("http://192.168.5.101:80/PSIA/YG/PTZCtrl/channels/0/continuous?pan=-1&tilt=0"); }
 if (ch == 2) { http.begin("http://192.168.5.102:80/PSIA/YG/PTZCtrl/channels/0/continuous?pan=-1&tilt=0"); }
 if (ch == 3) { http.begin("http://192.168.5.103:80/PSIA/YG/PTZCtrl/channels/0/continuous?pan=-1&tilt=0"); }
 if (ch == 4) { http.begin("http://192.168.5.104:80/PSIA/YG/PTZCtrl/channels/0/continuous?pan=-1&tilt=0"); }
 http.sendRequest("PUT", "{\"on\":false}"); http.end(); 
}

void ptz_right(uint8_t ch)
{
 HTTPClient http;
 if (ch == 1) { http.begin("http://192.168.5.101:80/PSIA/YG/PTZCtrl/channels/0/continuous?pan=1&tilt=0"); }
 if (ch == 2) { http.begin("http://192.168.5.102:80/PSIA/YG/PTZCtrl/channels/0/continuous?pan=1&tilt=0"); }
 if (ch == 3) { http.begin("http://192.168.5.103:80/PSIA/YG/PTZCtrl/channels/0/continuous?pan=1&tilt=0"); }
 if (ch == 4) { http.begin("http://192.168.5.104:80/PSIA/YG/PTZCtrl/channels/0/continuous?pan=1&tilt=0"); }
 http.sendRequest("PUT", "{\"on\":false}"); http.end(); 
}

void ptz_up(uint8_t ch)
{
 HTTPClient http;
 if (ch == 1) { http.begin("http://192.168.5.101:80/PSIA/YG/PTZCtrl/channels/0/continuous?pan=0&tilt=1"); }
 if (ch == 2) { http.begin("http://192.168.5.102:80/PSIA/YG/PTZCtrl/channels/0/continuous?pan=0&tilt=1"); }
 if (ch == 3) { http.begin("http://192.168.5.103:80/PSIA/YG/PTZCtrl/channels/0/continuous?pan=0&tilt=1"); }
 if (ch == 4) { http.begin("http://192.168.5.104:80/PSIA/YG/PTZCtrl/channels/0/continuous?pan=0&tilt=1"); }
 http.sendRequest("PUT", "{\"on\":false}"); http.end(); 
}

void ptz_down(uint8_t ch)
{
 HTTPClient http;
 if (ch == 1) { http.begin("http://192.168.5.101:80/PSIA/YG/PTZCtrl/channels/0/continuous?pan=0&tilt=-1"); }
 if (ch == 2) { http.begin("http://192.168.5.102:80/PSIA/YG/PTZCtrl/channels/0/continuous?pan=0&tilt=-1"); }
 if (ch == 3) { http.begin("http://192.168.5.103:80/PSIA/YG/PTZCtrl/channels/0/continuous?pan=0&tilt=-1"); }
 if (ch == 4) { http.begin("http://192.168.5.104:80/PSIA/YG/PTZCtrl/channels/0/continuous?pan=0&tilt=-1"); }
 http.sendRequest("PUT", "{\"on\":false}"); http.end(); 
}

void ptz_stop(uint8_t ch)
{
 HTTPClient http;
 if (ch == 1) { http.begin("http://192.168.5.101:80/PSIA/YG/PTZCtrl/channels/0/continuous?pan=0&tilt=0"); }
 if (ch == 2) { http.begin("http://192.168.5.102:80/PSIA/YG/PTZCtrl/channels/0/continuous?pan=0&tilt=0"); }
 if (ch == 3) { http.begin("http://192.168.5.103:80/PSIA/YG/PTZCtrl/channels/0/continuous?pan=0&tilt=0"); }
 if (ch == 4) { http.begin("http://192.168.5.104:80/PSIA/YG/PTZCtrl/channels/0/continuous?pan=0&tilt=0"); }
 http.sendRequest("PUT", "{\"on\":false}"); http.end(); 
}

void loop() 
{
 if (!digitalRead(pin_ch_up))
  {
   led(0);
   delay(10);
   act_channel++;
   if (act_channel >4) { act_channel = 4; }
   while (!digitalRead(pin_ch_up)){ delay(100); }
   led(1);
  }

  if (!digitalRead(pin_ch_dw))
  {
   led(0);
   delay(10);
   act_channel--;
   if (act_channel <1) { act_channel = 1; }
   while (!digitalRead(pin_ch_dw)){ delay(100); }
   led(1);
  }
  
 if (!digitalRead(pin_up))
  {
   led(0);
   delay(10); char cmd; byte chan;
   chan = act_channel;   // channel char
   cmd = 'U';           // command char
   call_ptz(cmd, chan);
   while (!digitalRead(pin_up)){ delay(50); led(1); delay(50); led(0); }
   chan = act_channel;   // channel char
   cmd = 'S';           // command char
   call_ptz(cmd, chan); 
   led(1);
  }

  if (!digitalRead(pin_dw))
  {
   led(0);
   delay(10); char cmd; byte chan;
   chan = act_channel;   // channel char
   cmd = 'D';           // command char
   call_ptz(cmd, chan);
   while (!digitalRead(pin_dw)){ delay(50); led(1); delay(50); led(0); }
   chan = act_channel;   // channel char
   cmd = 'S';           // command char
   call_ptz(cmd, chan); 
   led(1);
  }

  if (!digitalRead(pin_lt))
  {
   led(0);
   delay(10); char cmd; byte chan;
   chan = act_channel;   // channel char
   cmd = 'L';           // command char
   call_ptz(cmd, chan);
   while (!digitalRead(pin_lt)){ delay(50); led(1); delay(50); led(0); }
   chan = act_channel;   // channel char
   cmd = 'S';           // command char
   call_ptz(cmd, chan); 
   led(1);
  }

  if (!digitalRead(pin_rt))
  {
   led(0);
   delay(10); char cmd; byte chan;
   chan = act_channel;   // channel char
   cmd = 'R';           // command char
   call_ptz(cmd, chan); 
   while (!digitalRead(pin_rt)){ delay(50); led(1); delay(50); led(0); }
   chan = act_channel;   // channel char
   cmd = 'S';           // command char
   call_ptz(cmd, chan); 
   led(1);
  }
  delay(50);
}
    
void call_ptz(char cmd, byte chan)
{
 if (cmd == 'L') { ptz_left(chan);  }
 if (cmd == 'R') { ptz_right(chan); }
 if (cmd == 'U') { ptz_up(chan);    }
 if (cmd == 'D') { ptz_down(chan);  }
 if (cmd == 'S') { ptz_stop(chan);  }
}

void led(boolean b)
{
 if (b) { digitalWrite(LED_BUILTIN, LOW); } else { digitalWrite(LED_BUILTIN, HIGH); }
}


