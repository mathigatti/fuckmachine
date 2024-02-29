# Fuck Machine scripts

WIP code for controlling a fuck machine

## Software

`fuckmachine.ino` will create an OSC server and regulate the voltage of the motor.

- Install Arduino IDE and this OSC library: `https://github.com/CNMAT/OSC/tree/master`

- Using the Arduino IDE load fuckmachine.ino into the ESP8266

Then you should be able to connect to the osc server using [this app](https://play.google.com/store/apps/details?id=com.ffsmultimedia.osccontroller) or a similar one.

## Hardware

- Electronics by [Mathi Gatti](https://mathigatti.com)
    - ESP8266
    - L298N Driver
    - [5v regulator, step down dc-dc transformer](https://tienda.starware.com.ar/producto/modulo-regulador-reductor-voltaje-diymall-dc-dc-step-down-usb-8-32v-a-5v-3a-dcp/)
    - Laptop charger to power the geared motor with 24V
    - Antenna: https://www.instructables.com/External-Antenna-for-ESP8266/

- Mechanics by [KinkyToyMaker](https://www.instagram.com/kinkytoymaker/)
    - [Geared motors](http://www.ignismotor.com/DESKTOP/AR/motoreductor.html)
    - Corredora lineal
        - https://ingia.com.ar/producto/lmk8uu/
    - Caja de hierro hecha en la [escueladeherrerialesbiana](https://www.instagram.com/escueladeherrerialesbiana/)
    - Partes de plastico: Modeladas en 3D e impresas
    - Varillas de aluminio
    - Madera

## Related Links

- https://youtu.be/2bganVdLg5Q
- https://www.thingiverse.com/