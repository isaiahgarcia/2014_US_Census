#include "demogData.h"
#include "visitor.h"
#include <sstream>
#include <iomanip>

void demogData::accept(class Visitor &v) {
    v.visit(shared_from_this());
}

/* print county demographic data */
std::ostream& operator<<(std::ostream &out, const demogData &DD) {
    out << "County Demographics Info: " << DD.getRegionName() << ", " << DD.getState();
    out << std::setprecision(2) << std::fixed;
    out << " total population: " << DD.population;
    //consider re-writing with getters....
    out << "\nPopulation info: \n(\% over 65): " << DD.getpopOver65();
    out <<  " Count: " << DD.getpopOver65Count();
    out << "\n(\% under 18): " << DD.getpopUnder18();
    out <<  " Count: " << DD.getpopUnder18Count();
    out << "\n(\% under 5): " << DD.getpopUnder5();
    out <<  " Count: " << DD.getpopUnder5Count();
    out << "\nEducation info: \n(\% Bachelor degree or more): " << DD.getBAup();
    out <<  " Count: " << DD.getBAupCount();
    out << "\n(\% high school or more): " << DD.getHSup();
    out <<  " Count: " << DD.getHSupCount();
    out << "\npersons below poverty: " << DD.getBelowPoverty();
    out <<  " Count: " << DD.getBelowPovertyCount();
    return out;
}
