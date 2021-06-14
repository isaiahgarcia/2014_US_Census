#ifndef VCOMBOS_H
#define VCOMBOS_H


#include "visitorCombine.h"
#include <memory>

class visitorCombineState : public visitorCombine {
public:
    visitorCombineState() {}

	void visit(shared_ptr<demogData> obj) {
		  if (theComboDemogData[obj->getState()] == NULL) {
			  theComboDemogData[obj->getState()] = make_shared<demogCombo>(obj->getRegionName(), 
				obj->getState(), obj->getPop(), obj->getpopOver65Count(), obj->getpopUnder18Count(), 
				obj->getpopUnder5Count(), obj->getBAupCount(), obj->getHSupCount(), 
				obj->getBelowPovertyCount(), obj->getCommunityRaceMix(), 1);
  		} else {
  			theComboDemogData[obj->getState()]->addNumberOfCounties(1);
  			theComboDemogData[obj->getState()]->addpopOver65Count(obj->getpopOver65Count());
  			theComboDemogData[obj->getState()]->addpopUnder18Count(obj->getpopUnder18Count());
  			theComboDemogData[obj->getState()]->addpopUnder5Count(obj->getpopUnder5Count());
  			theComboDemogData[obj->getState()]->addBAupCount(obj->getBAupCount());
  			theComboDemogData[obj->getState()]->addHSupCount(obj->getHSupCount());
  			theComboDemogData[obj->getState()]->addBelowPovertyCount(obj->getBelowPovertyCount());
  			theComboDemogData[obj->getState()]->addCommunityRaceMix(obj->getCommunityRaceMix());
        theComboDemogData[obj->getState()]->addPop(obj->getPop());
  		}

  		return;
    }
    
    void visit(shared_ptr<psData> obj) {
        if (theComboPoliceData[obj->getState()] == NULL) {
            theComboPoliceData[obj->getState()] = make_shared<psCombo>(obj->getRegionName(), obj->getState());
        }

        theComboPoliceData[obj->getState()]->addNumberOfCases(1);
        theComboPoliceData[obj->getState()]->updateAgeData(obj->getAge());
        theComboPoliceData[obj->getState()]->updateGenderData(obj->getGender());
        theComboPoliceData[obj->getState()]->updateMentalIData(obj->getMentalIllness());
        theComboPoliceData[obj->getState()]->updateFleeData(obj->getFlee());
        theComboPoliceData[obj->getState()]->updateRacialData(obj->getRace());
        return;
    }

    void visit(shared_ptr<psCombo> obj) {
      return;
    }

  private:
     //inherited
};

#endif
