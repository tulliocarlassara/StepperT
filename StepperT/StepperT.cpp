/*
 * StepperT.cpp - Libreria per gestire un driver per motori passo-passo.
 * Realizza movimenti con rampe di accelerazione e decelerazione.
 *
 * by Tullio Carlassara - 2016
 *
 * This library is distributed in the hope that it will be useful but WITHOUT ANY WARRANTY.
 */

#include "StepperT.h"
#include "Arduino.h"

StepperT::StepperT(int stepPin, int dirPin){
  this->stepPin=stepPin;
  this->dirPin=dirPin;
  
  pinMode(this->stepPin,OUTPUT);
  pinMode(this->dirPin,OUTPUT);
}

void StepperT::setParametri(double vMax, double acc){
  this->vMax=vMax;
  this->acc=acc;
}

void StepperT::start(unsigned long numeroPassi, int dir){

  digitalWrite(dirPin,dir);
  
  passiRampa=vMax*vMax/(2*acc);   
  if(passiRampa>numeroPassi/2)
  {
     passiRampa=numeroPassi/2;
  }
  stopAcc=passiRampa;
  startDec=numeroPassi+1-passiRampa;
    
  oldMicros=micros();
    
  for(unsigned long j=1; j<=numeroPassi; j++){
    if(j<=stopAcc)
      {
         T=(unsigned long)k/sqrt(2*acc*j);
      }
      if(j>=startDec)
      {
         T=(unsigned long)k/sqrt(2*acc*(numeroPassi-j+1));
      }
   
      while(micros()-oldMicros<T);
      oldMicros=micros();
      digitalWrite(stepPin,HIGH);
      delayMicroseconds(3);	//da modificare a seconda dell'hardware
      digitalWrite(stepPin,LOW);
  }
}

