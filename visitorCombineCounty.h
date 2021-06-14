#ifndef VCOMBOC_H
#define VCOMBOC_H

#include "psData.h"
#include "psCombo.h"
#include "demogData.h"
#include "demogCombo.h"
#include "visitorCombine.h"
#include "parse.h"
#include <memory>
#include <fstream>
#include <cassert>
#include <string>

class visitorCombineCounty : public visitorCombine {
public:
    visitorCombineCounty() {}

    //store demographic data by county name
	void visit(shared_ptr<demogData> obj) {
        std::string county = obj->getRegionName().substr(0, obj->getRegionName().find("County")-1) + " " + obj->getState();
        if (theComboDemogData[county] == NULL) {
            theComboDemogData[county] = make_shared<demogCombo>(obj->getRegionName(), 
                obj->getState(), obj->getPop(), obj->getpopOver65Count(), obj->getpopUnder18Count(), 
                obj->getpopUnder5Count(), obj->getBAupCount(), obj->getHSupCount(), 
                obj->getBelowPovertyCount(), obj->getCommunityRaceMix(), 1);
        } else {
            theComboDemogData[county]->addNumberOfCounties(1);
            theComboDemogData[county]->addpopOver65Count(obj->getpopOver65Count());
            theComboDemogData[county]->addpopUnder18Count(obj->getpopUnder18Count());
            theComboDemogData[county]->addpopUnder5Count(obj->getpopUnder5Count());
            theComboDemogData[county]->addBAupCount(obj->getBAupCount());
            theComboDemogData[county]->addHSupCount(obj->getHSupCount());
            theComboDemogData[county]->addBelowPovertyCount(obj->getBelowPovertyCount());
            theComboDemogData[county]->addCommunityRaceMix(obj->getCommunityRaceMix());
            theComboDemogData[county]->addPop(obj->getPop());
        }
        return;
    }
    
    //aggregate police shooting data by county
    void visit(shared_ptr<psData> obj) {
        std::string county = obj->getRegionName().substr(0, obj->getRegionName().find("County")-1) + " " + obj->getState();
        if (theComboPoliceData[county] == NULL) {
            theComboPoliceData[county] = make_shared<psCombo>(obj->getRegionName(), obj->getState());
        } 

        theComboPoliceData[county]->addNumberOfCases(1);
        theComboPoliceData[county]->updateAgeData(obj->getAge());
        theComboPoliceData[county]->updateGenderData(obj->getGender());
        theComboPoliceData[county]->updateMentalIData(obj->getMentalIllness());
        theComboPoliceData[county]->updateFleeData(obj->getFlee());
        theComboPoliceData[county]->updateRacialData(obj->getRace());
        return;
    }

    void visit(shared_ptr<psCombo> obj) {
      return;
    }

  private:
    //only inherited data at this point
};

#endif
