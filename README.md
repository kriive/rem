# REM (Radiation Exposure Monitor)
REM is a digital wrapper around SV500 german geiger counter.
It was developed as a final assignment for SEI class in Università di Parma.

It features a LCD display, a pushbutton to change unit measures and a potentiometer. And of course a geiger counter.

## Pins and connections
### LCD display
PC8, PC6, PC5, PA12, PA11, PB12 used by display.
Can't use PD8, PB11/PE9 for mechanical reasons.

### I/O input impluse
PB4 -> D5.

### I/O input pushbutton
PB5 -> D4.

### I/O input potentiometer
PA1 -> A1.
