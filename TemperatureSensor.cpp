/**
*               __
*    _________ / /_  ____  ________  ____________  _____
*   /___/ __ \/ __ \/ __ \/ ___/ _ \/ ___/ ___/ / / / _ \
*  / / / /_/ / /_/ / /_/ / /  /  __(__  ) /__/ /_/ /  __/
* /_/  \____/_.___/\____/_/   \___/____/\___/\__,_/\___/
*
*
* @file TemperatureSensor.cpp
* @date Created: 25-4-2015
* @version 1.3
*
* @author Edwin Koek
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

#include "TemperatureSensor.h"

const static float Kelvin = 273.15;

TemperatureSensor::TemperatureSensor(){}

float TemperatureSensor::getTemperatureC(
      float ADCReading,
      float ADCMaxValue, 
      float ADCMinValue){
  if(0 > (ADCReading - ADCMinValue) || ADCReading > ADCMaxValue){
   return -1; 
  } 
  ADCReading -= ADCMinValue;
  ADCMaxValue -= ADCMinValue;   
  return ((((ADCReading - ADCMinValue) / (ADCMaxValue - ADCMinValue)) * 3300) / 10) - Kelvin;
}        

float TemperatureSensor::getTemperatureC(float volt){
  if(0 > volt || volt > 3.3){
    return -1;
  }   
  return ((volt * 1000) / 10) - Kelvin;
}  

float TemperatureSensor::getTemperatureK(
      float ADCReading,
      float ADCMaxValue, 
      float ADCMinValue){
  if(0 > (ADCReading - ADCMinValue) || ADCReading > ADCMaxValue){
   return -1; 
  }    
  ADCReading -= ADCMinValue;
  ADCMaxValue -= ADCMinValue;
  return (((ADCReading - ADCMinValue) / (ADCMaxValue - ADCMinValue)) * 3300) / 10;    
}        

float TemperatureSensor::getTemperatureK(float volt){
  if(0 > volt || volt > 3.3){
    return -1;
  }    
  return (volt * 1000) / 10;
}  

