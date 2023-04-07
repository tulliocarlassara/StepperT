/*
 * Stepper3T.h - Libreria per gestire tre driver per motori passo-passo.
 * Realizza movimenti con rampe di accelerazione e decelerazione.
 * I movimenti contemporanei sono interpolati linearmente.
 *
 * by Tullio Carlassara - 2016
 *
 * This library is distributed in the hope that it will be useful but WITHOUT ANY WARRANTY.
 */

#ifndef Stepper3T_h
#define Stepper3T_h

#define k 1000000.0

class Stepper3T{
  public:
    Stepper3T(int stepXPin, int stepYPin, int stepZPin, int dirXPin, int dirYPin, int dirZPin);
    void setParametri(double vMax, double acc);
    void start(unsigned long PassiX, unsigned long PassiY, unsigned long PassiZ, int dirX, int dirY, int dirZ);

  private:
    double vMax,acc;
    unsigned long T, oldMicros;
    unsigned long passiRampa,stopAcc,startDec;
    unsigned long i, pmX, pmY, pmZ, mezzeria, maxPassi;
    int stepXPin, stepYPin, stepZPin;
    int dirXPin, dirYPin, dirZPin;
    bool passoX, passoY, passoZ;
};

#endif
