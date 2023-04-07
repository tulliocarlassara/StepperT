/*
 * StepperT.h - Libreria per gestire un driver per motori passo-passo.
 * Realizza movimenti con rampe di accelerazione e decelerazione.
 *
 * by Tullio Carlassara - 2016
 *
 * This library is distributed in the hope that it will be useful but WITHOUT ANY WARRANTY.
 */

#ifndef StepperT_h
#define StepperT_h

#define k 1000000.0

class StepperT{
  public:
    StepperT(int stepPin, int dirPin);
    void setParametri(double vMax, double acc);
    void start(unsigned long numeroPassi, int dir);

  private:
    int stepPin,dirPin;
    double vMax,acc;
    unsigned long passiRampa,stopAcc, startDec;
    unsigned long T, oldMicros;
};

#endif
