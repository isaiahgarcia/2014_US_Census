
#include "dataAQ.h"
#include "psData.h"
#include "parse.h"
#include <iostream>
#include "tddFuncs.h"
using namespace std;

int main() {
  cout << "Testing state data police shooting..." << endl;

	dataAQ theAnswers;

    //read in a csv file and create a vector of objects representing each counties data
    std::vector<shared_ptr<regionData>> thePoliceData = read_csv(
            "police_shootings_cleaned.csv", POLICE);

    theAnswers.createComboPoliceData((std::vector<shared_ptr<psData> >&)thePoliceData);

    shared_ptr<psCombo> CA_PSData = theAnswers.getComboPoliceData("CA");
    
  	ASSERT_EQUALS(211, CA_PSData->getNumMentalI() );
    ASSERT_EQUALS(303, CA_PSData->getFleeingCount() );
    ASSERT_EQUALS(878, CA_PSData->getnumMales() );
    ASSERT_EQUALS(46, CA_PSData->getnumFemales() );
    ASSERT_EQUALS(924, CA_PSData->getNumberOfCases() );

  return 0;
}
