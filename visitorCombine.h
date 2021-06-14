#ifndef VCOMBO_H
#define VCOMBO_H

#include "psData.h"
#include "psCombo.h"
#include "demogData.h"
#include "demogCombo.h"
#include "visitor.h"
#include <memory>
#include <map>

using namespace std;

//The shared combo data
class visitorCombine : public Visitor {
public:
    visitorCombine() {}

    //hust a helper to print out various fields
    void printAllCombo(int (demogData::*f1)() const, int (psCombo::*f2)() const) {
        //stay tuned may be provided
        // demogData: getBelowPovertyCount
        // psCombo: getNumberOfCases
        return;
    }

    void printAllCombo() {
        for (const auto& entry : theComboDemogData) {
            cout << "name: " << entry.first << endl;
            cout << *(theComboDemogData[entry.first]) << endl;
            if (theComboPoliceData[entry.first] != NULL) {
                cout << *(theComboPoliceData[entry.first]) << endl;
            }
        }
        // cout << *(theComboDemogData[key]) << endl;
        // cout << *(theComboPoliceData[key]) << endl;
        //stay tuned may be provided
        // demogData: getBelowPovertyCount
        // psCombo: getNumberOfCases
        return;
    }

    shared_ptr<demogCombo> getComboDemogData(string regionName) { return theComboDemogData[regionName]; }
    shared_ptr<psCombo> getComboPoliceData(string regionName) { return theComboPoliceData[regionName]; }

	std::map<string, shared_ptr<demogCombo> >& getComboDemog()  { return theComboDemogData; }
    std::map<string, shared_ptr<psCombo> > & getComboPolice() { return theComboPoliceData; }

    protected:
    	//combo maps
        std::map<string, shared_ptr<demogCombo>> theComboDemogData;
        std::map<string, shared_ptr<psCombo>> theComboPoliceData;
};

#endif
