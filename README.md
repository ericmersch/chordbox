# chordbox
A DIY project inspired from the Omnichord that allows you to play chord using everyday objects

You can see a demo as using a DAW here : https://youtu.be/DtHRvjEAXro
and using everyday objets here: https://youtu.be/59gXW6P6Y7c

This project is composed of two parts that can be operated separately.

1. BoiteaClous.ino
The first part is a code for Arduino that can be used to build a midi controller inspired from the Omnichord and the corce of fifths.
I used and Arduino Pro Micro and 4 MPR121 chips for capacitive touch sensors.

2. modal_unit.pd and modal_synth.pd

These puredata pactch can be used to tranform the sound of everyday objects to tones or chords unsing any midi controller, for example, the one that you can built using BoiteaClous.ino.
