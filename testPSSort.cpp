
#include "dataAQ.h"
#include "parse.h"
#include <iostream>
#include "tddFuncs.h"
using namespace std;

int main() {
  cout << "Testing PS sort..." << endl;

    dataAQ theAnswers;

    //read in a csv file and create a vector of objects representing each counties data
    std::vector<shared_ptr<regionData>> theDemogData = read_csv(
            "county_demographics.csv", DEMOG);

    std::vector<shared_ptr<regionData>> thePoliceData = read_csv(
            "police_shootings_cleaned.csv", POLICE);

    theAnswers.createComboDemogData((std::vector<shared_ptr<demogData> >&)theDemogData);
    theAnswers.createComboPoliceData((std::vector<shared_ptr<psData> >&)thePoliceData);

    theAnswers.reportTopTenStatesPS();

  return 0;
}
