
#include <Preferences.h>
Preferences prefs;

typedef struct {
  uint8_t hour;
  uint8_t minute;
  uint8_t setting1;
  uint8_t setting2;
} schedule_t;

schedule_t schedule[16]; // buffer for the data (max 16 entries)

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println();

  prefs.begin("my-app"); // use "my-app" namespace

  if (not prefs.isKey("schedule")) {
    uint8_t content[] = {9, 30, 235, 255, 20, 15, 0, 1}; // two entries
    prefs.putBytes("schedule", content, sizeof(content));
  }

  size_t schLen = prefs.getBytesLength("schedule");
  // simple check that data fits
  if (0 == schLen || schLen % sizeof(schedule_t) || schLen > sizeof(schedule)) {
    Serial.printf("Invalid size of schedule array: %zu\n", schLen);
    return;
  }
  prefs.getBytes("schedule", schedule, schLen);
  Serial.printf("%02d:%02d %d/%d\n",
    schedule[1].hour, schedule[1].minute,
    schedule[1].setting1, schedule[1].setting2);

  // add a third entry
  schedule[2] = {8, 30, 20, 21};
  prefs.putBytes("schedule", schedule, 3*sizeof(schedule_t));

  // print result
  schLen = prefs.getBytesLength("schedule");
  char buffer2[schLen];
  prefs.getBytes("schedule", buffer2, schLen);
  for (int i=0; i<schLen; i++) {
    Serial.printf("%02X ", buffer2[i]);
  }
  Serial.println(); 
}

void loop() {}
