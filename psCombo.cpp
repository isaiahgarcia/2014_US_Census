#include <iomanip>
#include "psCombo.h"
#include "visitor.h"

void psCombo::accept(class Visitor &v) {
  v.visit(shared_from_this());
}

void psCombo::updateAgeData(int a) {
    if (a <= 18) {
      casesUnder18++;
    } else if (a > 18 && a < 65) {
      cases19to64++;
    } else {
      casesOver65++;
    }
    return;
}

void psCombo::updateGenderData(string g) {
    if (g == "M") {
      numMales++;
    }
    else if (g == "F") {
      numFemales++;
    }
    return;
}

void psCombo::updateMentalIData(bool m) {
    if (m) {
      mentalIl++;
    }
    return;
}

void psCombo::updateFleeData(string f) {
    if (f != "Not fleeing" && f != "") {
      fleeCount++;
    }
    return;
}

void psCombo::updateRacialData(string r) {
    if (r == "W") {
      racialData.addWhiteNHCount(1);
      racialData.addWhiteCount(1);
    } else if (r == "B") {
      racialData.addBlackCount(1);
    } else if (r == "A") {
      racialData.addAsianCount(1);
    } else if (r == "N") {
      racialData.addFirstNationCount(1);
    } else if (r == "H") {
      racialData.addLatinxCount(1);
    } else {
      racialData.addOtherCount(1);
    }

    racialData.setCommunityCount(numOfCases);
}

/* print state data - as aggregate of all incidents in this state */
std::ostream& operator<<(std::ostream &out, const psCombo& PD) {
    out << "State Info: " << PD.printState();
    out << "\nNumber of incidents: " << PD.numOfCases;
    out << std::setprecision(2) << std::fixed;
    out << "\nIncidents with age \n(over 65): " << PD.casesOver65;
    out << "\n(19 to 64): " << PD.cases19to64;
    out << "\n(under 18): " << PD.casesUnder18;
    out << "\nIncidents involving fleeing: " << PD.fleeCount << " %: " << PD.getPercentFlee();
    out << "\nIncidents involving mental illness: " << PD.mentalIl << " %: " << PD.getPercentMentalI();
    out << "\nMale incidents: " << PD.numMales << " female incidents: " << PD.numFemales;
    out << "\nRacial demographics of state incidents: " << PD.racialData;
    return out;
}