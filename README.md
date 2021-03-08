# projects
# A simple midi controller. It's for an avr microcontroller. Pretty much any of them should do, I think.
# It uses an MCP3008 ADC using SPI to allow for up to 8 sensors. You could put up to 5 straight into the avr but I 
# wanted a complete octave. It is designed for ldr's which have a range of 100ohms to 150kohms. But
# it could use many different kinds of sensors and it's mainly resistors in the circuit which determine
# the sensitivity. All it does is midi note on if the resistance of the sensor decreases below a threshold.
# When the resistance goes up again it sends a midi not off. Each sensor control a different note in the
# octave. The idea is to space these sensors down a hallway or on stairs and peoples shadow on the sensors
# should turn the notes on and off. It defaults to C Major key. But the stuff is there to generate the notes
# for all the major and minor keys (but not the harmonic and melodic minor keys yet). The next stage is a
# separate project to produce a key selector. This will interface through I2C to enable key changes.
