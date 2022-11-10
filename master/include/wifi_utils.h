#ifndef WIFI_UTILS_H
#define WIFI_UTILS_H

#include <Arduino.h>
#include <ESP8266WiFi.h> 
#include <ESP8266mDNS.h>

const int max_wifi_retries = 50;

bool wifi_connect(const char *ssid, const char *password)
{
  Serial.printf("\nConnecting to %s\n", ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  int i = max_wifi_retries;
  while (WiFi.status() != WL_CONNECTED && i-- > 0)
  {
    delay(500);
    Serial.print(".");
  }
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.printf("\nWiFi not connected: max wifi retries reached\n");
    return false;
  }
  if (!MDNS.begin("clockclock24", WiFi.localIP())) 
  { // Start the mDNS responder for clockclok24.local
    Serial.println("Error setting up MDNS responder!");
  } 
  else 
  {
    MDNS.addService("http", "tcp", 80);
  }
  Serial.println("WiFi connected");
  Serial.println("mDNS started: http://clockclock24.local");
  Serial.println("IP address: " + WiFi.localIP().toString());
  return true;
}

bool wifi_create_AP()
{
  // Set static IP
  IPAddress AP_LOCAL_IP(192, 168, 1, 10);
  IPAddress AP_GATEWAY_IP(192, 168, 1, 254);
  IPAddress AP_NETWORK_MASK(255, 255, 255, 0);
  Serial.println("\nCreating access point");
  if (!WiFi.softAPConfig(AP_LOCAL_IP, AP_GATEWAY_IP, AP_NETWORK_MASK))
  {
    Serial.println("AP Config Failed");
    return false;
  }
  WiFi.softAP("ClockClock24", NULL);
  IPAddress IP = WiFi.softAPIP();
  if (!MDNS.begin("clockclock24", IP)) 
  { // Start the mDNS responder for clockclok24.local
    Serial.println("Error setting up MDNS responder!");
  }
  else 
  {
    MDNS.addService("http", "tcp", 80);
  }
  Serial.println("mDNS started: http://clockclock24.local");
  Serial.println("IP address: " + AP_LOCAL_IP.toString());
  Serial.println("Gateway IP: " + AP_GATEWAY_IP.toString());
  return true;
}

void update_MDNS()
{
  MDNS.update();
}

bool is_connected()
{
  return WiFi.status() == WL_CONNECTED;
}

#endif