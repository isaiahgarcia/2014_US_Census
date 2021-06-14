#ifndef POLICECOMBODATA_H
#define POLICECOMBODATA_H

#include "raceDemogData.h"
#include "psData.h"
#include "regionData.h"
#include <memory>
#include <cassert>

using namespace std;

class psCombo : public regionData, public std::enable_shared_from_this<psCombo> {
public:
    psCombo(string rN, string s, int m, int f, int c65, int c19, int c18, 
    raceDemogData r, int nm, int nf, int nc) : 
        regionData{rN,s}, mentalIl(m), fleeCount(f), casesOver65(c65), cases19to64(c19), 
        casesUnder18(c18), racialData(r), numMales(nm), numFemales(nf), numOfCases(nc) {}

    psCombo(string rN, string s) : regionData{rN,s}, mentalIl(0), fleeCount(0), casesOver65(0),
        cases19to64(0), casesUnder18(0), racialData(raceDemogData()), numMales(0), numFemales(0),
        numOfCases(0) {}
    
    int getNumMentalI() const { return mentalIl; };
    int getFleeingCount() const { return fleeCount; };
    int getCasesOver65() const { return casesOver65; };
    int getCases19to64() const { return cases19to64; }
    int getCasesUnder18() const { return casesUnder18; };
    raceDemogData getRacialData() const { return racialData; };
    int getnumMales() const { return numMales; };
    int getnumFemales() const { return numFemales; };
    int getNumberOfCases() const { return numOfCases; };

    double getPercentMentalI() const { return 100.0f * ((double)mentalIl/numOfCases); }
    double getPercentFlee() const { return 100.0f * ((double)fleeCount/numOfCases); }

    void updateAgeData(int a);
    void updateGenderData(string g);
    void updateMentalIData(bool m);
    void updateFleeData(string f);
    void updateRacialData(string r);

    //add any others needed
    void addNumberOfCases(int num) { numOfCases += num; };

    friend std::ostream& operator<<(std::ostream &out, const psCombo& PD);

    void toString(ostream& os) const { os << *this; }

    void accept(class Visitor &v) override; 

protected:
    int mentalIl;
    int fleeCount;
    int casesOver65;
    int cases19to64;
    int casesUnder18;
    raceDemogData racialData;
    int numMales;
    int numFemales;
    int numOfCases;
};

#endif