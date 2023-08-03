# Fuck Machine scripts

WIP code for controlling a fuck machine

## Software

`fuckmachine.py` will create an OSC server and regulate the voltage of the motor.

- Install requirements: `pip install -r requirements.txt`

- Run: `python fuckmachine.py`

Then you should be able to connect to the osc server using [this app](https://play.google.com/store/apps/details?id=com.ffsmultimedia.osccontroller) or a similar one.

## Hardware

- Raspberry pi
- L298N Driver
- [Geared motors](http://www.ignismotor.com/DESKTOP/AR/motoreductor.html)
- Laptop charger to power the geared motor with 24V

## Useful Links

- https://youtu.be/2bganVdLg5Q
- https://play.google.com/store/apps/details?id=com.ffsmultimedia.osccontroller