#ifndef POLICE_H
#define POLICE_H

#include "regionData.h"

#include <string>
#include <iostream>
#include <utility>
#include <memory>

using namespace std;

/*
  class to represent police shooting data
  from CORGIS
*/
class psData : public regionData, public std::enable_shared_from_this<psData> {
  public:
    //add appropriate function paramaters to constructor once you add data
    psData(string rN, string s, string inN, int a, string g, string r, 
      bool MI, string f) : 
          regionData{rN,s}, name(inN), age(a), gender(g), race(r), 
          mentalIllness(MI), flee(f) {}

    string getName() const { return name; }
    int getAge() const { return age; }
    string getGender() const { return gender; }
    string getRace() const { return race; }
    bool getMentalIllness() const { return mentalIllness; }
    string getFlee() const { return flee; }

    string makeKeyPS(shared_ptr<psData> theData);

    friend std::ostream& operator<<(std::ostream &out, const psData &PD);

    void toString(ostream& os) const { os << *this; }

    void accept(class Visitor &v) override;

protected:
    const string name;
    const int age;
    const string gender;
    const string race;
    const bool mentalIllness;
    const string flee;


};

#endif
