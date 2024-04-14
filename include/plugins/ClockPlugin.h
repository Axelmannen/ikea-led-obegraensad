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
  int DIM_START {21};
  int OFF_START {22};
  int OFF_END {7};
  int DIM_END {9};

  int previousState;
  int state;

  short OutlineX[60];
  short OutlineY[60];

public:
  ClockPlugin();
  void setup() override;
  void loop() override;
  const char *getName() const override;
};