#include <Wire.h>
#include "MIDIUSB.h"
#include "Adafruit_MPR121.h"

#ifndef _BV
#define _BV(bit) (1 << (bit)) 
#endif

// You can have up to 4 on one i2c bus but one is enough for testing!
Adafruit_MPR121 cap1 = Adafruit_MPR121();
Adafruit_MPR121 cap2 = Adafruit_MPR121();
Adafruit_MPR121 cap3 = Adafruit_MPR121();
Adafruit_MPR121 cap4 = Adafruit_MPR121();


int Mchord[] = {-1,0,4,7,11,12,16,19,23,24};
int mchord[] = {-2,0,3,7,10,12,15,19,22,24};
int Mnotes[] = {0,2,4,5,7,9,11,12,14,16,17,19,21,23,24};
int mnotes[] = {0,2,3,5,7,8,10,12,14,15,17,19,20,22,24};
int Mdegree[] = {3,-2,5,0,-5,2,-3};
int mdegree[] = {0,-5,2,-3,4,-1,6};
int rootN = 48;
int rootC = 48;


int chord[] = {-1,0,4,7,11,12,16,19,23,24};
int notes[] = {0,2,4,5,7,9,11,12,14,16,17,19,21,23,24};


// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouched1 = 0;
uint16_t currtouched1 = 0;
uint16_t lasttouched2 = 0;
uint16_t currtouched2 = 0;
uint16_t lasttouched3 = 0;
uint16_t currtouched3 = 0;
uint16_t lasttouched4 = 0;
uint16_t currtouched4 = 0;

void setup() {
/*  Serial.begin(9600);

  while (!Serial) { // needed to keep leonardo/micro from starting too fast!
    delay(10);
  }
  */
  //Serial.println("Adafruit MPR121 Capacitive Touch sensor test"); 
  // Default address is 0x5A, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5C and ifSCL then 0x5D
  if (!cap1.begin(0x5A)) {
    //Serial.println("MPR121A not found, check wiring?");
  }
  if (!cap2.begin(0x5B)) {
    //Serial.println("MPR121B not found, check wiring?");
  }
  if (!cap3.begin(0x5C)) {
    //Serial.println("MPR121C not found, check wiring?");
  }
  if (!cap4.begin(0x5D)) {
    //Serial.println("MPR121D not found, check wiring?");
  }
  //Serial.println("MPR121ABCD found!");

  cap1.setThresholds(15, 2);
  cap2.setThresholds(15, 2);
  cap3.setThresholds(15, 2);
  cap4.setThresholds(15, 2);

    for(int i = 0;i<10;i++){
      chord[i] = Mchord[i]+Mdegree[3]+rootC;
    }
    for(int i = 0;i<15;i++){
      notes[i] = Mnotes[i]+Mdegree[3]+rootN;
    }
}

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}

void programChange(byte channel, byte program) {
  midiEventPacket_t pc = {0x0C, 0xC0 | channel, program, 0};
  MidiUSB.sendMIDI(pc);
}

void sendControlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}

void play_note(int i) {
  noteOn(0, i, 102);
  MidiUSB.flush();
}

void release_note(int i) {
  noteOff(0, i, 102);
  MidiUSB.flush();
}

void release_all(){
  for (int k = 0; k < 10; k++) {
        release_note(chord[k]);
      }
  for (int k = 0; k < 15; k++) {
        release_note(notes[k]);
      }
}

void loop() {
  // Get the currently touched pads
  currtouched1 = cap1.touched();
  currtouched2 = cap2.touched();
  currtouched3 = cap3.touched();
  currtouched4 = cap4.touched();



// SET CHORDS AND NOTES


///// A
  if ((currtouched1 & _BV(0)) && !(lasttouched1 & _BV(0)) ) {
    release_all();
    for(int i = 0;i<10;i++){
      chord[i] = Mchord[i]+Mdegree[6]+rootC;
      }
    for(int i = 0;i<15;i++){
      notes[i] = Mnotes[i]+Mdegree[6]+rootN;
    }
  }

  if ((currtouched1 & _BV(1)) && !(lasttouched1 & _BV(1)) ) {
    release_all();
    for(int i = 0;i<10;i++){
      chord[i] = Mchord[i]+Mdegree[5]+rootC;
      }
    for(int i = 0;i<15;i++){
      notes[i] = Mnotes[i]+Mdegree[5]+rootN;
    }
  }

  if ((currtouched1 & _BV(2)) && !(lasttouched1 & _BV(2)) ) {
    release_all();
    for(int i = 0;i<10;i++){
      chord[i] = mchord[i]+mdegree[6]+rootC;
      }
    for(int i = 0;i<15;i++){
      notes[i] = mnotes[i]+mdegree[6]+rootN;
    }
  }

  if ((currtouched1 & _BV(3)) && !(lasttouched1 & _BV(3)) ) {
    release_all();
    for(int i = 0;i<10;i++){
      chord[i] = mchord[i]+mdegree[4]+rootC;
      }
    for(int i = 0;i<15;i++){
      notes[i] = mnotes[i]+mdegree[4]+rootN;
    }
  }

  if ((currtouched1 & _BV(4)) && !(lasttouched1 & _BV(4)) ) {
    release_all();
    for(int i = 0;i<10;i++){
      chord[i] = mchord[i]+mdegree[5]+rootC;
      }
    for(int i = 0;i<15;i++){
      notes[i] = mnotes[i]+mdegree[5]+rootN;
    }
  }

  if ((currtouched1 & _BV(5)) && !(lasttouched1 & _BV(5)) ) {
    release_all();
    for(int i = 0;i<10;i++){
      chord[i] = mchord[i]+mdegree[3]+rootC;
      }
    for(int i = 0;i<15;i++){
      notes[i] = mnotes[i]+mdegree[3]+rootN;
    }
  }

  if ((currtouched1 & _BV(6)) && !(lasttouched1 & _BV(6)) ) {
    release_all();
    for(int i = 0;i<10;i++){
      chord[i] = Mchord[i]+Mdegree[2]+rootC;
      }
    for(int i = 0;i<15;i++){
      notes[i] = Mnotes[i]+Mdegree[2]+rootN;
    }
  }

    if ((currtouched1 & _BV(7)) && !(lasttouched1 & _BV(7)) ) {
    release_all();
    for(int i = 0;i<10;i++){
      chord[i] = mchord[i]+mdegree[2]+rootC;
    }
    for(int i = 0;i<15;i++){
      notes[i] = mnotes[i]+mdegree[2]+rootN;
    }
  }

  if ((currtouched1 & _BV(8)) && !(lasttouched1 & _BV(8)) ) {
    release_all();
    for(int i = 0;i<10;i++){
      chord[i] = Mchord[i]+Mdegree[1]+rootC;
      }
    for(int i = 0;i<15;i++){
      notes[i] = Mnotes[i]+Mdegree[1]+rootN;
    }
  }

  if ((currtouched1 & _BV(9)) && !(lasttouched1 & _BV(9)) ) {
    release_all();
    for(int i = 0;i<10;i++){
      chord[i] = mchord[i]+mdegree[1]+rootC;
      }
    for(int i = 0;i<15;i++){
      notes[i] = mnotes[i]+mdegree[1]+rootN;
    }
  }

  if ((currtouched1 & _BV(10)) && !(lasttouched1 & _BV(10)) ) {
    release_all();
    for(int i = 0;i<10;i++){
      chord[i] = mchord[i]+mdegree[0]+rootC;
      }
    for(int i = 0;i<15;i++){
      notes[i] = mnotes[i]+mdegree[0]+rootN;
    }
  }

  if ((currtouched1 & _BV(11)) && !(lasttouched1 & _BV(11)) ) {
    release_all();
    for(int i = 0;i<10;i++){
      chord[i] = Mchord[i]+Mdegree[0]+rootC;
    }
    for(int i = 0;i<15;i++){
      notes[i] = Mnotes[i]+Mdegree[0]+rootN;
    }
  }


  ////////// B


  if ((currtouched2 & _BV(0)) && !(lasttouched2 & _BV(0)) ) {
    play_note(notes[14]);
  }
  if (!(currtouched2 & _BV(0)) && (lasttouched2 & _BV(0)) ) {
      release_note(notes[14]);
    }

  if ((currtouched2 & _BV(1)) && !(lasttouched2 & _BV(1)) ) {
    play_note(notes[13]);
  }
  if (!(currtouched2 & _BV(1)) && (lasttouched2 & _BV(1)) ) {
      release_note(notes[13]);
    }

  if ((currtouched2 & _BV(2)) && !(lasttouched2 & _BV(2)) ) {
    play_note(notes[12]);
  }
  if (!(currtouched2 & _BV(2)) && (lasttouched2 & _BV(2)) ) {
      release_note(notes[12]);
    }

  if ((currtouched2 & _BV(3)) && !(lasttouched2 & _BV(3)) ) {
    play_note(notes[11]);
  }
  if (!(currtouched2 & _BV(3)) && (lasttouched2 & _BV(3)) ) {
      release_note(notes[11]);
    }
    

  if ((currtouched2 & _BV(4)) && !(lasttouched2 & _BV(4)) ) {
      play_note(notes[10]);
  }
  if (!(currtouched2 & _BV(4)) && (lasttouched2 & _BV(4)) ) {
      release_note(notes[10]);
    }

  if ((currtouched2 & _BV(5)) && !(lasttouched2 & _BV(5)) ) {
    play_note(notes[9]);
  }
  if (!(currtouched2 & _BV(5)) && (lasttouched2 & _BV(5)) ) {
      release_note(notes[9]);
    }

  if ((currtouched2 & _BV(6)) && !(lasttouched2 & _BV(6)) ) {
    play_note(notes[8]);
  }
  if (!(currtouched2 & _BV(6)) && (lasttouched2 & _BV(6)) ) {
      release_note(notes[8]);
    }

  if ((currtouched2 & _BV(7)) && !(lasttouched2 & _BV(7)) ) {
    release_all();
    for(int i = 0;i<10;i++){
      chord[i] = Mchord[i]+Mdegree[4]+rootC;
    }
    for(int i = 0;i<15;i++){
      notes[i] = Mnotes[i]+Mdegree[4]+rootN;
    }
  }

  if ((currtouched2 & _BV(8)) && !(lasttouched2 & _BV(8)) ) {
    release_all();
    for(int i = 0;i<10;i++){
      chord[i] = Mchord[i]+Mdegree[3]+rootC;
      }
    for(int i = 0;i<15;i++){
      notes[i] = Mnotes[i]+Mdegree[3]+rootN;
    }
  }

  if ((currtouched2 & _BV(9)) && !(lasttouched2 & _BV(9)) ) {
    sendControlChange(0,48,127);//STOP ALL
    MidiUSB.flush();
  }
  if (!(currtouched2 & _BV(9)) && (lasttouched2 & _BV(9)) ) {
    sendControlChange(0,48,0);
    MidiUSB.flush();
    }

  if ((currtouched2 & _BV(10)) && !(lasttouched2 & _BV(10)) ) {
    sendControlChange(0,49,127);//STOP LAYER
    MidiUSB.flush();
  }
  if (!(currtouched2 & _BV(10)) && (lasttouched2 & _BV(10)) ) {
    sendControlChange(0,49,0);
    MidiUSB.flush();
    }

  if ((currtouched2 & _BV(11)) && !(lasttouched2 & _BV(11)) ) {
    sendControlChange(0,50,127);//REC
    MidiUSB.flush();
  }
  if (!(currtouched2 & _BV(11)) && (lasttouched2 & _BV(11)) ) {
    sendControlChange(0,50,0);
    MidiUSB.flush();
    }


  ////////// C

  if ((currtouched3 & _BV(0)) && !(lasttouched3 & _BV(0)) ) {
    play_note(notes[7]);
  }
  if (!(currtouched3 & _BV(0)) && (lasttouched3 & _BV(0)) ) {
      release_note(notes[7]);
    }

  if ((currtouched3 & _BV(1)) && !(lasttouched3 & _BV(1)) ) {
    play_note(notes[6]);
  }
  if (!(currtouched3 & _BV(1)) && (lasttouched3 & _BV(1)) ) {
      release_note(notes[6]);
    }

  if ((currtouched3 & _BV(2)) && !(lasttouched3 & _BV(2)) ) {
    play_note(notes[5]);
  }
  if (!(currtouched3 & _BV(2)) && (lasttouched3 & _BV(2)) ) {
      release_note(notes[5]);
    }

  if ((currtouched3 & _BV(3)) && !(lasttouched3 & _BV(3)) ) {
    play_note(notes[4]);
  }
  if (!(currtouched3 & _BV(3)) && (lasttouched3 & _BV(3)) ) {
      release_note(notes[4]);
    }

  if ((currtouched3 & _BV(4)) && !(lasttouched3 & _BV(4)) ) {
    rootN=min(rootN+12,110);
    for(int i = 0; i < 15; i ++){
      notes[i]=notes[i]+12;
    }
  }
  if ((currtouched3 & _BV(5)) && !(lasttouched3 & _BV(5)) ) {
      play_note(notes[3]);
  }
  if (!(currtouched3 & _BV(5)) && (lasttouched3 & _BV(5)) ) {
      release_note(notes[3]);
    }
  if ((currtouched3 & _BV(6)) && !(lasttouched3 & _BV(6)) ) {
    play_note(notes[2]);
  }
  if (!(currtouched3 & _BV(6)) && (lasttouched3 & _BV(6)) ) {
      release_note(notes[2]);
    }

  if ((currtouched3 & _BV(7)) && !(lasttouched3 & _BV(7)) ) {
    rootN=max(rootN-12,10);
    for(int i = 0; i < 15; i ++){
      notes[i]=notes[i]-12;
    }
  }

  if ((currtouched3 & _BV(8)) && !(lasttouched3 & _BV(8)) ) {
    play_note(notes[1]);
  }
  if (!(currtouched3 & _BV(8)) && (lasttouched3 & _BV(8)) ) {
      release_note(notes[1]);
    }

  if ((currtouched3 & _BV(9)) && !(lasttouched3 & _BV(9)) ) {
    play_note(chord[8]);
  }
  if (!(currtouched3 & _BV(9)) && (lasttouched3 & _BV(9)) ) {
      release_note(chord[8]);
    }

  if ((currtouched3 & _BV(10)) && !(lasttouched3 & _BV(10)) ) {
    play_note(notes[0]);
  }
  if (!(currtouched3 & _BV(10)) && (lasttouched3 & _BV(10)) ) {
      release_note(notes[0]);
    }

  if ((currtouched3 & _BV(11)) && !(lasttouched3 & _BV(11)) ) {
    play_note(chord[9]);
  }
  if (!(currtouched3 & _BV(11)) && (lasttouched3 & _BV(11)) ) {
      release_note(chord[9]);
    }


  ////////// D

  if ((currtouched4 & _BV(0)) && !(lasttouched4 & _BV(0)) ) {
    //WHEEL++
  }

  if ((currtouched4 & _BV(1)) && !(lasttouched4 & _BV(1)) ) {
    //WHEEL--
  }

  if ((currtouched4 & _BV(2)) && !(lasttouched4 & _BV(2)) ) {
    play_note(chord[7]);
  }
  if (!(currtouched4 & _BV(2)) && (lasttouched4 & _BV(2)) ) {
      release_note(chord[7]);
    }

  if ((currtouched4 & _BV(3)) && !(lasttouched4 & _BV(3)) ) {
    play_note(chord[6]);
  }
  if (!(currtouched4 & _BV(3)) && (lasttouched4 & _BV(3)) ) {
      release_note(chord[6]);
    }

  if ((currtouched4 & _BV(4)) && !(lasttouched4 & _BV(4)) ) {
      play_note(chord[4]);
  }
  if (!(currtouched4 & _BV(4)) && (lasttouched4 & _BV(4)) ) {
      release_note(chord[4]);
    }

  if ((currtouched4 & _BV(5)) && !(lasttouched4 & _BV(5)) ) {
      play_note(chord[5]);
  }
  if (!(currtouched4 & _BV(5)) && (lasttouched4 & _BV(5)) ) {
      release_note(chord[5]);
    }

  if ((currtouched4 & _BV(6)) && !(lasttouched4 & _BV(6)) ) {
      play_note(chord[3]);
  }
  if (!(currtouched4 & _BV(6)) && (lasttouched4 & _BV(6)) ) {
      release_note(chord[3]);
    }

  if ((currtouched4 & _BV(7)) && !(lasttouched4 & _BV(7)) ) {
        play_note(chord[2]);
  }
  if (!(currtouched4 & _BV(7)) && (lasttouched4 & _BV(7)) ) {
      release_note(chord[2]);
    }

  if ((currtouched4 & _BV(8)) && !(lasttouched4 & _BV(8)) ) {
        play_note(chord[1]);
  }
  if (!(currtouched4 & _BV(8)) && (lasttouched4 & _BV(8)) ) {
      release_note(chord[1]);
  }

  if ((currtouched4 & _BV(9)) && !(lasttouched4 & _BV(9)) ) {
        play_note(chord[0]);
  }
  if (!(currtouched4 & _BV(9)) && (lasttouched4 & _BV(9)) ) {
      release_note(chord[0]);
  }

  if ((currtouched4 & _BV(10)) && !(lasttouched4 & _BV(10)) ) {
    rootC=max(rootC-12,7);
    for(int i = 0; i < 10; i ++){
      chord[i]=chord[i]-12;
    }
  }

  if ((currtouched4 & _BV(11)) && !(lasttouched4 & _BV(11)) ) {
    rootC=min(rootC+12,110);
    for(int i = 0; i < 10; i ++){
      chord[i]=chord[i]+12;
    }
  }


  //////////

  
  lasttouched1 = currtouched1;
  lasttouched2 = currtouched2;
  lasttouched3 = currtouched3;
  lasttouched4 = currtouched4;
}
