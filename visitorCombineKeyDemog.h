#ifndef VCOMBOKD_H
#define VCOMBOKD_H

#include "psData.h"
#include "psCombo.h"
#include "demogData.h"
#include "demogCombo.h"
#include "visitorCombine.h"
#include <memory>
#include <map>


class visitorCombineKeyDemog : public visitorCombine {
public:
    visitorCombineKeyDemog(string (*df)(shared_ptr<demogData>), std::map<string, string>& mapDemogToKey) {
      demogFunc = df;
      //probably want to assert the map is legit and store it
      assert(mapDemogToKey.size() > 0);
      mapComboDemogToKey = mapDemogToKey;
   }


  //just store based on function
	void visit(shared_ptr<demogData> obj) {
    string key = (*demogFunc)(obj);
    if (theComboDemogData[key] == NULL) {
      theComboDemogData[key] = make_shared<demogCombo>(obj->getRegionName(), 
      obj->getState(), obj->getPop(), obj->getpopOver65Count(), obj->getpopUnder18Count(), 
      obj->getpopUnder5Count(), obj->getBAupCount(), obj->getHSupCount(), 
      obj->getBelowPovertyCount(), obj->getCommunityRaceMix(), 1);
    } else {
      theComboDemogData[key]->addState(obj->getState());
      theComboDemogData[key]->addNumberOfCounties(1);
      theComboDemogData[key]->addpopOver65Count(obj->getpopOver65Count());
      theComboDemogData[key]->addpopUnder18Count(obj->getpopUnder18Count());
      theComboDemogData[key]->addpopUnder5Count(obj->getpopUnder5Count());
      theComboDemogData[key]->addBAupCount(obj->getBAupCount());
      theComboDemogData[key]->addHSupCount(obj->getHSupCount());
      theComboDemogData[key]->addBelowPovertyCount(obj->getBelowPovertyCount());
      theComboDemogData[key]->addCommunityRaceMix(obj->getCommunityRaceMix());
      theComboDemogData[key]->addPop(obj->getPop());
    }
    return;
  }
  
  //store based on demog key
  void visit(shared_ptr<psData> obj) {
    std::string county = obj->getRegionName().substr(0, obj->getRegionName().find("County")-1) + " " + obj->getState();
    std::string key = mapComboDemogToKey[county];
    // std::cout << county << std::endl;
    // std::cout << key << std::endl;
    // std::cout << mapComboDemogToKey["Jefferson LA"] << std::endl;
    if (theComboPoliceData[key] == NULL) {
        theComboPoliceData[key] = make_shared<psCombo>(obj->getRegionName(), obj->getState());
    } 

    theComboPoliceData[key]->addNumberOfCases(1);
    theComboPoliceData[key]->addState(obj->getState());
    theComboPoliceData[key]->updateAgeData(obj->getAge());
    theComboPoliceData[key]->updateGenderData(obj->getGender());
    theComboPoliceData[key]->updateMentalIData(obj->getMentalIllness());
    theComboPoliceData[key]->updateFleeData(obj->getFlee());
    theComboPoliceData[key]->updateRacialData(obj->getRace());
    return;
  }

  void visit(shared_ptr<psCombo> obj) {
    return;
  }

  private:
    //the function pointers to the key functions
    string (*demogFunc)(shared_ptr<demogData>);

    //want a way to keep region to key for mapping between the two dataTypes
    std::map<std::string, std::string> mapComboDemogToKey;

};

#endif
