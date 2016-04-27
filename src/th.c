
#include <stdio.h>

#include <wiringPi.h>
#include <maxdetect.h>

#define RHT03_PIN       7
#define RETRIES         3

int main()
{
  int temp, rh, loop, status;

  // Setup WiringPi
  wiringPiSetup () ;
  piHiPri       (55) ;

  // Read sensor
  temp = rh = -1;
  loop=RETRIES;

  status = readRHT03 (RHT03_PIN, &temp, &rh);
  while ((!status) && loop--)
  {
      printf("-Retry-");
      fflush(stdout);
      delay(3000);
      status = readRHT03 (RHT03_PIN, &temp, &rh);
  }

  fflush(stdout);

  // Print measurement
  printf("Current Temp: %5.1f, RH: %5.1f\n",(temp / 10.0),(rh / 10.0)) ;

  return 0;
}
