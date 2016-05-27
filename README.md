This Node-RED node reads current air temperature and relative humidity from a DHT22 sensor, without the need to run Node-RED as a privileged user.

h1. Limitations
Currently only runs on Raspberry Pi 2 with sensor on hardware pin 7. Work around these limitations by building from source. Or wait for an update :)

h1. Prerequisites
* wiringPi must be installed
* Node-RED must run as a user that can use `sudo`

h1. Building from source
The npm package comes with a precompiled 'th' executable build on a Raspberry Pi 2. If you want to run it on another platform you will have to build th from source. You can fetch the source on https://github.com/jorne/node-red-contrib-thsense/tree/master/src/
