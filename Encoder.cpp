/**
*               __
*    _________ / /_  ____  ________  ____________  _____
*   /___/ __ \/ __ \/ __ \/ ___/ _ \/ ___/ ___/ / / / _ \
*  / / / /_/ / /_/ / /_/ / /  /  __(__  ) /__/ /_/ /  __/
* /_/  \____/_.___/\____/_/   \___/____/\___/\__,_/\___/
*
*
* @file Encoder.cpp
* @date Created: 1-5-2015
* @version 1.0
*
* @author Nathan Schaaphuizen
*
* @section LICENSE
* License: newBSD
*
* Copyright © 2015, HU University of Applied Sciences Utrecht.
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
* - Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
* - Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
* - Neither the name of the HU University of Applied Sciences Utrecht nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE HU UNIVERSITY OF APPLIED SCIENCES UTRECHT
* BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
* GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
* OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**/

#include "Encoder.h"
#include <simpletools.h>

Encoder::Encoder(int newPin):
pin{newPin}
{
  //Start execution of code on a new cog.
  //We can not directly call a member function.
  //So we pass the pointer of this object as the parameter to atchineve the same.
  cogId = cogstart(&Encoder::run, this, stack,  sizeof(stack)); 
}

Encoder::~Encoder(){
  //Stop the cog execution and free it for other purposes.
  cogstop(cogId); 
}   
 
unsigned int Encoder::getEncoderCount(){
  //Return the amount of counted pulses.
  return encoderCount; 
}
 
int Encoder::getSpeed(){
  //Return the amount of counted pulses per second.
  return speed;  
}

unsigned int Encoder::getLoops() {
  return loops; 
}  

void Encoder::run(void* obj){
  //Since we are sure the object is of type Encoder we can safely cast it back to a Encoder pointer. 
  Encoder* enc = reinterpret_cast<Encoder*>(obj);
  //Var we are using to hold the read dta.
  int read;
  //Var containt the data form last reading.
  //We use this to make a comparison the the new reading.
  //To make sure we have the correct start value we already make a reading here. 
  int last = input(enc->pin);
  //Var we use the count time.
  int count = 0;
  //Var we use the calculate the speed.
  int lastSpeed = 0;
  //Start the reading, this will never end.
  enc->loops = 0;
  
  while(true){
    enc->loops++;
    //Read the state of the pin.
    //1 = endocer blocked
    //0 = encoder can see the led
    read = input(enc->pin);
    //Read a downwards pulse.
    //Check if the encoder was blocked the last time we read.
    //Check if the encoder is not blocked now.
    //If so the motor has rotated and moved the encoder disk along with it.
    if(last != read){
      //Add a pulse to the counter.
      enc->encoderCount++;
    }
    
    last = read;
          
  }   
} 