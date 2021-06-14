#include "dataAQ.h"
#include "parse.h"
#include <iostream>
#include <string>   // std::string
#include <iostream> // std::cout
#include <sstream> 
#include <iomanip>
#include "tddFuncs.h"
using namespace std;

int main() {

    dataAQ theAnswers;
    cout << std::setprecision(2) << std::fixed;
    
    std::vector<shared_ptr<regionData> > theDemogData = read_csv(
            "county_demographics.csv", DEMOG);

    std::vector<shared_ptr<regionData> > thePoliceData = read_csv(
            "police_shootings_cleaned.csv", POLICE);


    theAnswers.createComboDemogDataKey((std::vector<shared_ptr<demogData> >&) theDemogData);

    std::stringstream buffer;
    // Redirect std::cout to buffer
    std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());

    //the report code
    cout << *(theAnswers.getComboDemogData("KeyBelowPovLessTenPer")) << endl;
    // Use the string value of buffer to compare against expected output
    std::string theReport = buffer.str();

    // Restore original buffer before exiting
    std::cout.rdbuf(prevcoutbuf);

    // report
    string expectReport1 = "Combo Info: AK, AL, AR, CA, CO, CT, FL, GA, HI, IA, ID, IL, IN, KS, KY, LA, MA, MD, ME, MI, MN, MO, MS, MT, NC, ND, NE, NH, NJ, NM, NV, NY, OH, OK, OR, PA, RI, SD, TN, TX, UT, VA, VT, WA, WI, WY, total states: 46\nNumber of Counties: 431 County Demographics Info: comboData, many\n"; 
    string expectReport2 = "Education info: \n(Bachelor or more): 38.30% and total: 19714949\n(high school or more): 91.51% and total: 47106146\npersons below poverty: 7.55% and total: 3885127\nTotal population: 51476603\n";
    string expectReport3 = "Racial Demographics Info: \n\% American Indian and Alaska Native percent: 0.69 count: 353134\n\% Asian American percent: 7.28 count: 3746101\n\% Black/African American percent: 8.98 count: 4621329\n\% Hispanic or Latinx percent: 10.58 count: 5443695\n\% Native Hawaiian and Other Pacific Islander percent: 0.32 count: 163362\n\% Two or More Races percent: 2.63 count: 1355467\n\% White (inclusive) percent: 80.12 count: 41241007\n\% White (nonHispanic) percent: 71.07 count: 36586915";

    if (theReport.length() > expectReport1.length() + expectReport2.length() + expectReport3.length()) {
        std::string subReport1 = theReport.substr(0, expectReport1.length());
        

        std::size_t found2 = theReport.find("Education");
        std::string subReport2 = theReport.substr(found2, expectReport2.length());
        

        std::size_t found3 = theReport.find("Racial");
        std::string subReport3 = theReport.substr(found3, expectReport3.length());
        
        ASSERT_EQUALS(expectReport1, subReport1);
        ASSERT_EQUALS(expectReport2, subReport2);
        ASSERT_EQUALS(expectReport3, subReport3);
    } else {
        cout << "Failed to create report for BelowPovLessTenPer.  Length of report: " << theReport.length() << endl;
    }

  return 0;
}