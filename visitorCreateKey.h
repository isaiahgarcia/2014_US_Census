#ifndef VCOMBOK_H
#define VCOMBOK_H

#include "psData.h"
#include "psCombo.h"
#include "demogData.h"
#include "demogCombo.h"
#include "visitorCombine.h"
#include <memory>
#include <map>


class visitorCreateKey : public Visitor {
public:
  visitorCreateKey(string (*df)(shared_ptr<demogData>), string (*psf)(shared_ptr<psData>)) {
      demogFunc = df;
      psFunc =psf; 
   }

	void visit(shared_ptr<demogData> obj) {
    std::string county = obj->getRegionName().substr(0, obj->getRegionName().find("County")-1) + " " + obj->getState();
    // std::cout << county << std::endl;
    mapDemogToKey[county] = (*demogFunc)(obj);
  }
    
  void visit(shared_ptr<psData> obj) {
    std::string county = obj->getRegionName().substr(0, obj->getRegionName().find("County")-1) + " " + obj->getState();
    // std::cout << county << std::endl;
    mapPSToKey[county] = (*psFunc)(obj);
  }

  void visit(shared_ptr<psCombo> obj) {
    return;
  }

  //add getters as needed
  std::map<std::string, std::string>& getDemogRegionToKey() { return mapDemogToKey; }
  std::map<std::string, std::string>& getPsRegionToKey() { return mapPSToKey; }

    private:
      //the function pointers to the key functions
      string (*demogFunc)(shared_ptr<demogData>);
      string (*psFunc)(shared_ptr<psData>);

      //ADD data to map between location and key
      std::map<std::string, std::string> mapDemogToKey;
      std::map<std::string, std::string> mapPSToKey;

};

#endif
