#include "plugins/ClockPlugin.h"

ClockPlugin::ClockPlugin() : 
              OutlineX { 8, 9,10,11,12,13,14,
                        15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
                        14,13,12,11,10, 9, 8, 7, 6, 5, 4, 3, 2, 1,
                         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                         1, 2, 3, 4, 5, 6, 7}, 
              OutlineY { 0, 0, 0, 0, 0, 0, 0,
                         0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,
                        15,15,15,15,15,15,15,15,15,15,15,15,15,15,
                        15,14,13,12,11,10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0,
                         0, 0, 0, 0, 0, 0, 0} {}


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

  previousState = -1;
  state = 2;

}


void ClockPlugin::loop()
{
  if (getLocalTime(&timeinfo))
  {
    if (previousHour != timeinfo.tm_hour || previousMinutes != timeinfo.tm_min)
    {

      // Determine state
      if (timeinfo.tm_hour >= DIM_START || timeinfo.tm_hour < DIM_END)
      {
        if (timeinfo.tm_hour >= OFF_START || timeinfo.tm_hour < OFF_END) {
          state = 0;
        } else {
          state = 1;
        }
      } else {
        state = 2;
      }

      // Update brightness
      if (state != previousState) {
        if (state == 1) {
          Screen.setBrightness(5);
        } else if (state == 2) {
          Screen.setBrightness(255);
        }
      }

      Screen.clear();
      if (state != 0) {
        Screen.drawNumbers(3, 2, {(timeinfo.tm_hour - timeinfo.tm_hour % 10) / 10, timeinfo.tm_hour % 10});
        Screen.drawNumbers(3, 9, {(timeinfo.tm_min - timeinfo.tm_min % 10) / 10, timeinfo.tm_min % 10});
      }
      previousState = state;
    }

    previousMinutes = timeinfo.tm_min;
    previousHour = timeinfo.tm_hour;
  }
  if (state == 2 && previousSeconds != timeinfo.tm_sec)
  {
    // Draw outline
    // for (int i = 0; i < timeinfo.tm_sec + 1; i++) // Draw one more pixel to close the rectangle completely
    // {
    //   Screen.setPixel(OutlineX[i], OutlineY[i], 1, 5);
    // }
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
