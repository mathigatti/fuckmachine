# Fuck Machine scripts

WIP code for controlling a fuck machine

## Software

`fuckmachine.ino` will create an OSC server and regulate the voltage of the motor.

- Install Arduino IDE and this OSC libray: `https://github.com/CNMAT/OSC/tree/master`

- Using the Arduino IDE load fuckmachine.ino into the ESP8266

Then you should be able to connect to the osc server using [this app](https://play.google.com/store/apps/details?id=com.ffsmultimedia.osccontroller) or a similar one.

## Hardware

- ESP8266
- L298N Driver
- [Geared motors](http://www.ignismotor.com/DESKTOP/AR/motoreductor.html)
- Laptop charger to power the geared motor with 24V

## Useful Links

- https://youtu.be/2bganVdLg5Q
- https://play.google.com/store/apps/details?id=com.ffsmultimedia.osccontroller