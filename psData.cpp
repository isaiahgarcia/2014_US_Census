#include <sstream>
#include "psData.h"
#include "visitor.h"

void psData::accept(class Visitor &v) {
    v.visit(shared_from_this());
}

/* print police data - fill in*/
std::ostream& operator<<(std::ostream &out, const psData &PD) {
     out << "Police Shooting Info: " << PD.getState();
    out << "\nPerson name: " << PD.name;
    out << "\nAge: " << PD.age;
    out << "\nGender: " << PD.gender;
    out << "\nRace: " << PD.race;
    out << "\nMental Illness: " << PD.mentalIllness;
    out << "\nFleeing: " << PD.flee;
    return out;
}
