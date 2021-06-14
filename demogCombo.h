#ifndef COMBODEMOG_H
#define COMBODEMOG_H

#include <memory>
#include <string>
#include <iostream>
#include "demogData.h"
#include "raceDemogData.h"
#include "regionData.h"

/*
  class to represent combined demographic data 
*/
class demogCombo : public demogData {
  public:
   	demogCombo(string rN, string s, int pop, int in65, int in18, int in5, 
   		int inBD, int inHS, int inBP, raceDemogData r, int nC) :
            demogData{rN, s, pop, in65, in18, in5, inBD, inHS, inBP, r}, 
            numOfCounties(nC) {}

    int getNumberOfCounties() const { return numOfCounties; }

    void addNumberOfCounties(int p) { numOfCounties += p; }

    void addpopOver65Count(int p) { popOver65 += p; }
    void addpopUnder18Count(int p) { popUnder18 += p; }
    void addpopUnder5Count(int p) { popUnder5 += p; }
    void addBAupCount(int p) { popWithBachDeg += p; }
    void addHSupCount(int p) { popWithHSDeg += p; }
    void addBelowPovertyCount(int p) { popBelowPovLine += p; }
    void addCommunityRaceMix(raceDemogData r) { race += r; }

  	friend std::ostream& operator<<(std::ostream &out, const demogCombo &SD);

	private:
    int numOfCounties;
};
#endif
