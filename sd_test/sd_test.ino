#include "SD.h"
#define SD_ChipSelectPin 10 //chose any available PWM pin 44, 45, and 46 should work
#include "TMRpcm.h"
#include "SPI.h"
//need these libraries to work, TMRpcm is responsible for playing the music
TMRpcm music; //create global music object

void setup(){ //sets up the sd card connection, no music yet
  music.speakerPin = 9; //Also chose any availabe PWM pin
  Serial.begin(9600);
  if (!SD.begin(SD_ChipSelectPin)) {
    Serial.println("SD fail");
    return;
  }
}

void loop(){  
  //in the main function after everyone is ready and the game is about to begin play the countdown using these lines:
  music.setVolume(5);
  music.play("countdown.wav");
  music.loop(0); //only plays once
  //Countdown takes 4 seconds so add 4 seconds delay and then signal controller arduinos to begin
  //after that add these lines for the main soundtrack
  music.play("main_track.wav");
  music.loop(1); //will make the track loop
  //For the end of the game play a cheer track
  music.play("main_track.wav");
  music.loop(0); //will make the track play once
}
