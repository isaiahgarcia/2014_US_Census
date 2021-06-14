#ifndef DEMOG_H
#define DEMOG_H

#include "raceDemogData.h"
#include "regionData.h"

#include <string>
#include<iostream>
#include <cmath>
#include <memory>

using namespace std;

/*
  class to represent county demographic data
  from CORGIS - LAB01 starter - replace with your FULL version!
*/
class demogData : public regionData, public std::enable_shared_from_this<demogData> {
  public:
    demogData(string rN, string s, int p, int in65, int in18, int in5, int inBD, 
      int inHS, int inBP, raceDemogData r) :
            regionData{rN,s,p}, popOver65(in65), popUnder18(in18), popUnder5(in5), 
            popWithBachDeg(inBD), popWithHSDeg(inHS), popBelowPovLine(inBP), race(r) {}

    int getpopOver65Count() const { return popOver65; }
    int getpopUnder18Count() const { return popUnder18; }
    int getpopUnder5Count() const { return popUnder5; }
    int getBAupCount() const { return popWithBachDeg; }
    int getHSupCount() const { return popWithHSDeg; }
    int getBelowPovertyCount() const { return popBelowPovLine; }
    raceDemogData getCommunityRaceMix() const { return race; }

    double getpopOver65() const { return 100.0f*((double)(popOver65))/population; }
    double getpopUnder18() const { return 100.0f*((double)(popUnder18))/population; }
    double getpopUnder5() const { return 100.0f*((double)(popUnder5))/population; }
    double getBAup() const { return 100.0f*((double)(popWithBachDeg))/population; }
    double getHSup() const { return 100.0f*((double)(popWithHSDeg))/population; }
    double getpopBelowPovLine() const { return 100.0f*((double)(popBelowPovLine))/population; }
    double getBelowPoverty() const { return 100.0f*((double)(popBelowPovLine))/population; }

    string makeKeyDemog(shared_ptr<demogData> theData);

    friend std::ostream& operator<<(std::ostream &out, const demogData &DD);

    void toString(ostream& os) const { os << *this; }

    void accept(class Visitor &v) override;

protected:
    int popOver65;
    int popUnder18;
    int popUnder5;
    int popWithBachDeg;
    int popWithHSDeg;
    int popBelowPovLine;
    raceDemogData race;

};
#endif
