# Fuck Machine scripts

WIP code for controlling a fuck machine

## Software

`fuckmachine.ino` will create an OSC server and regulate the voltage of the motor.

- Install Arduino IDE and this OSC library: `https://github.com/CNMAT/OSC/tree/master`

- Using the Arduino IDE load fuckmachine.ino into the ESP8266

Then you should be able to connect to the osc server using [this app](https://play.google.com/store/apps/details?id=com.ffsmultimedia.osccontroller) or a similar one.

## Hardware

- Electronics
    - ESP8266
    - L298N Driver
    - [5v regulator, step down dc-dc transformer](https://tienda.starware.com.ar/producto/modulo-regulador-reductor-voltaje-diymall-dc-dc-step-down-usb-8-32v-a-5v-3a-dcp/)
    - Laptop charger to power the geared motor with 24V
    - Antenna: https://www.instructables.com/External-Antenna-for-ESP8266/

## Related Links

- https://youtu.be/2bganVdLg5Q
- https://www.thingiverse.com/
