#ifndef REGION_H
#define REGION_H

#include <string>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

class Visitor;

/* very general data type for any kind of regional data*/
class regionData {
  public:
  	regionData(const string n, const string s, const int p) : regionName(n), population(p) {
      stateS.insert(s);
    }

    regionData(const string n, const string s) : regionName(n), population(0) {
      stateS.insert(s);
    }

  	string getRegionName() const { return regionName; }
  	string getState() const { if (stateS.size() == 1) return *(stateS.begin()); else return "many"; }
  	void addState(string inS) { stateS.insert(inS); }
    void addPop(int p) { population += p; }
    string printState() const {
      string s;
      for (std::set<string>::iterator it = stateS.begin(); it != stateS.end(); it++)
        s+=*it+", ";
      s+= "total states: " + std::to_string(stateS.size());
      return s;
    }
    void setName(string inN) { regionName = inN; }
    int getPop() const { return population; }
    void setPop(int inPop) { population = inPop; }

    virtual void toString(ostream& os) const = 0;

    virtual void accept(class Visitor &v) = 0;

  protected:
  	string regionName; // city or county or place name
  	std::set<string> stateS; // region data could be more than one state
  	int population; // region population
    
};
#endif
