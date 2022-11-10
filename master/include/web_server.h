#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include <Arduino.h>
#include <ESP8266WebServer.h>

#include "web_page.h"
#include "clock_manager.h"
#include "clock_config.h"

typedef struct browser_time
{
  int hour;
  int minute;
  int second;
  int day;
  int month;
  int year;
} t_browser_time;

void server_start();

void handle_webclient();

void server_stop();

void handle_get();

void handle_post_time();

void handle_post_adjust();

void handle_get_config();

void handle_post_adjust();

void handle_post_mode();

void handle_post_sleep();

void handle_post_connection();

bool is_time_changed_browser();

t_browser_time get_browser_time();

#endif