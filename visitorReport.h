#ifndef VISITREP_H
#define VISITREP_H

#include "psData.h"
#include "demogData.h"
#include "visitor.h"
#include <iomanip>

class visitorReport : public Visitor {
	public:
		void visit(shared_ptr<demogData> obj) {
			cout << "print summary demog Data:";
			cout << "\nRegion info: comboData, " << obj->getState();
			cout << std::setprecision(2) << std::fixed;
			cout << "\nEducation info:\n(Bachelor or more): " << obj->getBAup() << "%";
		    cout <<  " and total: " << obj->getBAupCount();
		    cout << "\n(high school or more): " << obj->getHSup() << "%";
		    cout <<  " and total: " << obj->getHSupCount();
		    cout << "\nTotal population: " << obj->getPop() << endl;
		    cout << obj->getCommunityRaceMix() << endl;
		}

		void visit(shared_ptr<psData> obj) {
			cout << "print aggregate police shooting data:";
			// call visit for psCombo
		}

		void visit(shared_ptr<psCombo> obj) {
			cout << "State Info: " << obj->printState();
		    cout << "\nNumber of incidents: " << obj->getNumberOfCases();
		    cout << std::setprecision(2) << std::fixed;
		    cout << "\nRacial demographics of state incidents: " << obj->getRacialData() << endl;
		}
};

#endif
