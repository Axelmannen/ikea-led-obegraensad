#include "mode/clock.h"

#ifdef ENABLE_SERVER

struct tm timeinfo;

int previousSeconds;
int previousMinutes;
int previousHour;

void clockSetup()
{
  previousSeconds = -1;
  previousMinutes = -1;
  previousHour = -1;
}

int modeButtonState2 = 0;
int lastModeButtonState2 = 0;

bool nightMode = false;

// List of coordinates
short OutlineX[60] = { 8, 9,10,11,12,13,14,
                      15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
                      14,13,12,11,10, 9, 8, 7, 6, 5, 4, 3, 2, 1,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       1, 2, 3, 4, 5, 6, 7};
short OutlineY[60] = { 0, 0, 0, 0, 0, 0, 0,
                       0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,
                      15,15,15,15,15,15,15,15,15,15,15,15,15,15,
                      15, 14,13,12,11,10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0,
                        0, 0, 0, 0, 0, 0, 0};

void clockLoop()
{
  if (!getLocalTime(&timeinfo))
  {
    Serial.println("Failed to obtain time");
  }
  else
  {
    if (previousHour != timeinfo.tm_hour || previousMinutes != timeinfo.tm_min)
    {
      // Toggle night mode
      if (!nightMode && (timeinfo.tm_hour >= 21 || timeinfo.tm_hour < 7))
      {
        nightMode = true;
        Screen.setBrightness(5);
      }
      else if (nightMode && (timeinfo.tm_hour >= 7 && timeinfo.tm_hour < 21))
      {
        nightMode = false;
        Screen.setBrightness(255);
      }

      Screen.clear();
      Screen.drawNumbers(3, 2, {(timeinfo.tm_hour - timeinfo.tm_hour % 10) / 10, timeinfo.tm_hour % 10});
      Screen.drawNumbers(3, 9, {(timeinfo.tm_min - timeinfo.tm_min % 10) / 10, timeinfo.tm_min % 10});

    }

    previousMinutes = timeinfo.tm_min;
    previousHour = timeinfo.tm_hour;
  }
  if (!nightMode && previousSeconds != timeinfo.tm_sec)
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

#endif
