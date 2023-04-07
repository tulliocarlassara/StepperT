/*
 * Stepper3T.cpp - Libreria per gestire tre driver per motori passo-passo.
 * Realizza movimenti con rampe di accelerazione e decelerazione.
 * I movimenti contemporanei sono interpolati linearmente.
 *
 * by Tullio Carlassara - 2016
 *
 * This library is distributed in the hope that it will be useful but WITHOUT ANY WARRANTY.
 */

#include "Stepper3T.h"
#include "Arduino.h"

Stepper3T::Stepper3T(int stepXPin, int stepYPin, int stepZPin, int dirXPin, int dirYPin, int dirZPin){
  
  this->stepXPin=stepXPin;
  this->stepYPin=stepYPin;
  this->stepZPin=stepZPin;
  this->dirXPin=dirXPin;
  this->dirYPin=dirYPin;
  this->dirZPin=dirZPin;
  
  pinMode(stepXPin,OUTPUT);
  pinMode(stepYPin,OUTPUT);
  pinMode(stepZPin,OUTPUT);
  pinMode(dirXPin,OUTPUT);
  pinMode(dirYPin,OUTPUT);
  pinMode(dirZPin,OUTPUT);
}

void Stepper3T::setParametri(double vMax, double acc){
  this->vMax=vMax;
  this->acc=acc;
}

void Stepper3T::start(unsigned long passiX, unsigned long passiY, unsigned long passiZ, int dirX, int dirY, int dirZ){

  digitalWrite(dirXPin,dirX);
  digitalWrite(dirYPin,dirY);
  digitalWrite(dirZPin,dirZ);

  maxPassi = passiX;
  if(passiY>maxPassi) maxPassi = passiY;
  if(passiZ>maxPassi) maxPassi = passiZ;
  
  if(acc!=0)
  {
      passiRampa=vMax*vMax/(2*acc);    
        
      if(passiRampa>maxPassi/2L)
      {
        passiRampa=maxPassi/2L;
      }

      stopAcc=passiRampa;
      startDec=maxPassi+1-passiRampa;
   }
   else
   {
      stopAcc=0;
      startDec=maxPassi;  
      T=k/vMax;
   }
    
    mezzeria=maxPassi/2L;
    pmX=maxPassi;
    pmY=maxPassi;
    pmZ=maxPassi;
    
    passoX=false;
    passoY=false;
    passoZ=false;

    oldMicros=micros();
    
    for(i=1; i<=maxPassi; i++)
    {
        if((pmX-=passiX)<=mezzeria)
        {
          pmX+=maxPassi;
          passoX=true;
        }
        if((pmY-=passiY)<=mezzeria)
        {
          pmY+=maxPassi;
          passoY=true;
        }
        if((pmZ-=passiZ)<=mezzeria)
        {
          pmZ+=maxPassi;
          passoZ=true;
        }
        
        if(i<=stopAcc)
        {
           T=(unsigned long)k/sqrt(2*acc*i);
        }
        if(i>=startDec)
        {
           T=(unsigned long)k/sqrt(2*acc*(maxPassi-i+1));
        }
        
        while(micros()-oldMicros<T);
        oldMicros=micros();

        if(passoX)digitalWrite(stepXPin,HIGH);
        if(passoY)digitalWrite(stepYPin,HIGH);
        if(passoZ)digitalWrite(stepZPin,HIGH);
        
        delayMicroseconds(3);    //da modificare a seconda dell'hardware
        
        passoX=false;
        passoY=false;
        passoZ=false;
        
        digitalWrite(stepXPin,LOW);
        digitalWrite(stepYPin,LOW);
        digitalWrite(stepZPin,LOW);
    }  
}

