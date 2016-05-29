
#include <stdio.h>

#include <wiringPi.h>
#include <maxdetect.h>

#define DEFAULT_PIN 7
#define RETRIES     3
#define TEMP_MIN  -40
#define TEMP_MAX   80
#define RHUM_MIN    0
#define RHUM_MAX  100

int main(int argc, char *argv[])
{
  int pin, temp, rh, loop, success, status;

  pin = argv[1] || DEFAULT_PIN;

  // Setup WiringPi
  wiringPiSetup();
  piHiPri(55);

  // Read sensor
  temp = rh = -1;
  loop = RETRIES + 1;
  success = 0;

  while ((!success) && loop--) {
      if (loop < RETRIES) delay(3000);

      status = readRHT03 (pin, &temp, &rh);
      temp = temp / 10.0;
      rh = rh / 10.0;

      if (!status) {
        fprintf(stderr, "Read failed\n");
      }
      else if (temp < TEMP_MIN || temp > TEMP_MAX) {
        fprintf(stderr, "Invalid temperature\n");
      }
      else if (rh < RHUM_MIN || rh > RHUM_MAX) {
        fprintf(stderr, "Invalid relative humidity\n");
      }
      else {
        success = 1;
      }
  }

  fflush(stdout);

  // Print measurement in JSON
  printf("{\"measurement\":{\"temperature\":%5.1f,\"relative_humidity\":%5.1f}}\n", temp, rh);

  return 0;
}
