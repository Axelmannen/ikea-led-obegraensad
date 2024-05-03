#pragma once

#include "PluginManager.h"

class ClockPlugin : public Plugin
{
private:
  struct tm timeinfo;

  int previousSeconds;
  int previousMinutes;
  int previousHour;

  // Dim time must encapsulate off time
  int DIM_START;
  int OFF_START;
  int OFF_END;
  int DIM_END;

  int brightness;

  short OutlineX[60];
  short OutlineY[60];

public:
  ClockPlugin();
  void setup() override;
  void loop() override;
  const char *getName() const override;
};