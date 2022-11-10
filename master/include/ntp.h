#ifndef NTP_H
#define NTP_H

#include <WiFiUdp.h>
#include <ESP8266WiFi.h>
#include <TimeLib.h>

// NTP Servers:
static const char ntp_server_name[] = "pool.ntp.org";
//static const char ntp_server_name[] = "time.nist.gov";

int _time_zone = 1; // Central European Time
// const int time_zone = -5;  // Eastern Standard Time (USA)
// const int time_zone = -4;  // Eastern Daylight Time (USA)
// const int time_zone = -8;  // Pacific Standard Time (USA)
// const int time_zone = -7;  // Pacific Daylight Time (USA)

WiFiUDP Udp;
unsigned int local_port = 8888; // local port to listen for UDP packets

const int NTP_PACKET_SIZE = 48;     // NTP time is in the first 48 bytes of message
byte packet_buffer[NTP_PACKET_SIZE]; // buffer to hold incoming & outgoing packets

void begin_NTP();
time_t get_NTP_time();
void send_NTP_packet(IPAddress &address);

void begin_NTP()
{
  Udp.begin(local_port);
}

time_t get_NTP_time()
{
  IPAddress ntp_server_IP; // NTP server's ip address

  while (Udp.parsePacket() > 0)
    ; // discard any previously received packets
  Serial.println("Transmit NTP Request");
  // get a random server from the pool
  WiFi.hostByName(ntp_server_name, ntp_server_IP);
  Serial.print(ntp_server_name);
  Serial.print(": ");
  Serial.println(ntp_server_IP);
  send_NTP_packet(ntp_server_IP);
  uint32_t begin_wait = millis();
  while (millis() - begin_wait < 1500)
  {
    int size = Udp.parsePacket();
    if (size >= NTP_PACKET_SIZE)
    {
      Serial.println("Receive NTP Response");
      Udp.read(packet_buffer, NTP_PACKET_SIZE); // read packet into the buffer
      unsigned long secs_since_1900;
      // convert four bytes starting at location 40 to a long integer
      secs_since_1900 = (unsigned long)packet_buffer[40] << 24;
      secs_since_1900 |= (unsigned long)packet_buffer[41] << 16;
      secs_since_1900 |= (unsigned long)packet_buffer[42] << 8;
      secs_since_1900 |= (unsigned long)packet_buffer[43];
      return secs_since_1900 - 2208988800UL + _time_zone * SECS_PER_HOUR;
    }
  }
  Serial.println("No NTP Response :-(");
  return 0; // return 0 if unable to get the time
}

// send an NTP request to the time server at the given address
void send_NTP_packet(IPAddress &address)
{
  // set all bytes in the buffer to 0
  memset(packet_buffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packet_buffer[0] = 0b11100011; // LI, Version, Mode
  packet_buffer[1] = 0;          // Stratum, or type of clock
  packet_buffer[2] = 6;          // Polling Interval
  packet_buffer[3] = 0xEC;       // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packet_buffer[12] = 49;
  packet_buffer[13] = 0x4E;
  packet_buffer[14] = 49;
  packet_buffer[15] = 52;
  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  Udp.beginPacket(address, 123); // NTP requests are to port 123
  Udp.write(packet_buffer, NTP_PACKET_SIZE);
  Udp.endPacket();
}

void set_ntp_timezone(int value)
{
  _time_zone = value;
}

int get_ntp_timezone()
{
  return _time_zone;
}
#endif