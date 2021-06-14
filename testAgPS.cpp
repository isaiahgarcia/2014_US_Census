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
    
    std::vector<shared_ptr<regionData> > thePoliceData = read_csv(
            "police_shootings_cleaned.csv", POLICE);

    theAnswers.createComboPoliceDataKey((std::vector<shared_ptr<psData> >&) thePoliceData);

    std::stringstream buffer;
    // Redirect std::cout to buffer
    std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());

    //the report code
    cout << *(theAnswers.getComboPoliceData("KeyNativeAmericanVictim")) << endl;
    // Use the string value of buffer to compare against expected output
    std::string theReport = buffer.str();

    // Restore original buffer before exiting
    std::cout.rdbuf(prevcoutbuf);

    // report
    string expectReport1 = "State Info: AK, AZ, CA, CO, ID, KS, KY, MN, MT, ND, NE, NM, NV, OK, SD, TX, UT, VA, VT, WA, WI, WY, total states: 22\nNumber of incidents: 87\n"; 
    string expectReport2 = "Incidents involving fleeing: 28 %: 32.18\nIncidents involving mental illness: 15 %: 17.24\nMale incidents: 82 female incidents: 5\n";

    if (theReport.length() > expectReport1.length() + expectReport2.length()) {
        std::string subReport1 = theReport.substr(0, expectReport1.length());

        std::size_t found2 = theReport.find("Incidents involving");
        std::string subReport2 = theReport.substr(found2, expectReport2.length());

        ASSERT_EQUALS(expectReport1, subReport1);
        ASSERT_EQUALS(expectReport2, subReport2);
    } else {
        cout << "Failed to create report for NativeAmericanVictim.  Length of report: " << theReport.length() << endl;
    }

  return 0;
}