#include "demogCombo.h"
#include "demogData.h"
#include <sstream>
#include <string>
#include <assert.h>
#include <iomanip>

//add member functions here

/* print state data - as aggregate of all the county data */
std::ostream& operator<<(std::ostream &out, const demogCombo& ComboD) {
	out.setf(ios::fixed);
    out.setf(ios::showpoint);
    out.precision(2);

	out << "Combo Info: " << ComboD.printState() << endl;
    out << "Number of Counties: " << ComboD.getNumberOfCounties() << " County Demographics Info: comboData, " << ComboD.getState() << endl;
    out << "Population info: \n(over 65): " << ComboD.getpopOver65() << "%";
    out <<  " and total: " << ComboD.getpopOver65Count();
    out << "\n(under 18): " << ComboD.getpopUnder18() << "%";
    out <<  " and total: " << ComboD.getpopUnder18Count();
    out << "\n(under 5): " << ComboD.getpopUnder5() << "%";
    out <<  " and total: " << ComboD.getpopUnder5Count();
    out << "\nEducation info: \n(Bachelor or more): " << ComboD.getBAup() << "%";
    out <<  " and total: " << ComboD.getBAupCount();
    out << "\n(high school or more): " << ComboD.getHSup() << "%";
    out <<  " and total: " << ComboD.getHSupCount();
    out << "\npersons below poverty: " << ComboD.getBelowPoverty() << "%";
    out <<  " and total: " << ComboD.getBelowPovertyCount();
    out << "\nTotal population: " << ComboD.getPop() << endl;
    out << ComboD.race;
    return out;
}
