#include "plugins/ClockPlugin.h"

ClockPlugin::ClockPlugin() {
    // List of coordinates
    int OutlineX[60] = { 8, 9,10,11,12,13,14,
                        15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
                        14,13,12,11,10, 9, 8, 7, 6, 5, 4, 3, 2, 1,
                         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                         1, 2, 3, 4, 5, 6, 7};
    int OutlineY[60] = { 0, 0, 0, 0, 0, 0, 0,
                        0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,
                        15,15,15,15,15,15,15,15,15,15,15,15,15,15,
                        15, 14,13,12,11,10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0,
                          0, 0, 0, 0, 0, 0, 0};
}

void ClockPlugin::setup()
{
  // loading screen
  Screen.setPixel(4, 7, 1);
  Screen.setPixel(5, 7, 1);
  Screen.setPixel(7, 7, 1);
  Screen.setPixel(8, 7, 1);
  Screen.setPixel(10, 7, 1);
  Screen.setPixel(11, 7, 1);

  previousSeconds = -1;
  previousMinutes = -1;
  previousHour = -1;

  dimMode = false;
  offMode = false;
}

void ClockPlugin::loop()
{
  if (getLocalTime(&timeinfo))
  {
    if (previousHour != timeinfo.tm_hour || previousMinutes != timeinfo.tm_min)
    {
      // Toggle dim mode
      if (!dimMode && (timeinfo.tm_hour >= DIM_START || timeinfo.tm_hour < DIM_END))
      {
        dimMode = true;
        Screen.setBrightness(5);
      }
      else if (dimMode && (timeinfo.tm_hour >= DIM_END && timeinfo.tm_hour < DIM_START))
      {
        dimMode = false;
        Screen.setBrightness(255);
      }

      // Toggle off mode 
       if (!offMode && (timeinfo.tm_hour >= OFF_START || timeinfo.tm_hour < OFF_END))
      {
        offMode = true;
        Screen.setBrightness(0);
      }
      else if (offMode && (timeinfo.tm_hour >= OFF_END && timeinfo.tm_hour < OFF_START))
      {
        offMode = false;
        Screen.setBrightness(5);
      }




      Screen.clear();
      Screen.drawNumbers(3, 2, {(timeinfo.tm_hour - timeinfo.tm_hour % 10) / 10, timeinfo.tm_hour % 10});
      Screen.drawNumbers(3, 9, {(timeinfo.tm_min - timeinfo.tm_min % 10) / 10, timeinfo.tm_min % 10});
    }

    previousMinutes = timeinfo.tm_min;
    previousHour = timeinfo.tm_hour;
  }
  if (!dimMode && previousSeconds != timeinfo.tm_sec)
  {
    // Draw outline
    for (int i = 0; i < timeinfo.tm_sec + 1; i++) // Draw one more pixel to close the rectangle completely
    {
      Screen.setPixel(OutlineX[i], OutlineY[i], 1, 5);
    }
    // Draw seconds
    Screen.setPixel(OutlineX[timeinfo.tm_sec], OutlineY[timeinfo.tm_sec], 1, 5);
    Screen.setPixel(OutlineX[previousSeconds], OutlineY[previousSeconds], 0, 5);
    previousSeconds = timeinfo.tm_sec;
  }
}

const char *ClockPlugin::getName() const
{
  return "Clock";
}
