
#include <stdio.h>
#include <stdlib.h>

#include <wiringPi.h>
#include <maxdetect.h>

#define DEFAULT_PIN 7
#define RETRIES     3
#define TEMP_MIN (-40)
#define TEMP_MAX   80
#define RHUM_MIN    0
#define RHUM_MAX  100

int main(int argc, char *argv[])
{
  int pin, raw_temp, raw_rh, loop, success, status;
  double temp, rh;

  if (argc >= 2) {
    pin = atoi(argv[1]);
    fprintf(stderr, "Using pin %d\n", pin);
  }
  else {
    pin = DEFAULT_PIN;
    fprintf(stderr, "Using default pin %d\n", pin);
  }

  // Setup WiringPi
  wiringPiSetup();
  piHiPri(55);

  // Read sensor
  temp = rh = -1;
  loop = success = 0;

  while ((!success) && (loop++ <= RETRIES + 1)) {
    delay(loop * 1000);

    fprintf(stderr, "Reading... (%d) ", loop);
    status = readRHT03 (pin, &raw_temp, &raw_rh);
    temp = raw_temp / 10.0;
    rh = raw_rh / 10.0;

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
