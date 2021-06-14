#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include "demogData.h"
#include "psData.h"
#include "parse.h"
#include "regionData.h"
#include "visitorCombineState.h"
#include "visitorCombineCounty.h"
#include "visitorCreateKey.h"
#include "visitorCombineKeyDemog.h"
#include "visitorCombineKeyPS.h"
#include "stats.h"
#include "statTool.h"
#include "tddFuncs.h"

using namespace std;

string makeKeyDemog(shared_ptr<demogData> theData) {
    string theKey = "Key";

    if (theData->getCommunityRaceMix().getBlackPercent() >= 20) {
        theKey += "AfriAmerTwentyPer";
    } else if (theData->getCommunityRaceMix().getLatinxPercent() >= 20) {
        theKey += "LatinxPerTwentyPer";
    } else if (theData->getCommunityRaceMix().getFirstNationPercent() >= 20) {
        theKey += "FirstNationTwentyPer";
    } else if (theData->getCommunityRaceMix().getAsianPercent() >= 20) {
        theKey += "AsianTwentyPer";
    } else {
        theKey += "Other";
    }

    return theKey;
}

string makeKeyPS(shared_ptr<psData> theData) {
    string theKey = "Key";
    if (theData->getRace() == "W") {
        theKey += "WhiteVictim";
    } else if (theData->getRace() == "A") {
        theKey += "AsianVictim";
    } else if (theData->getRace() == "H") {
        theKey += "HispanicVictim";
    } else if (theData->getRace() == "N") {
        theKey += "NativeAmericanVictim";
    } else if (theData->getRace() == "B") {
        theKey += "AfricanAmericanVictim";
    } else if (theData->getRace() == "O") {
        theKey += "OtherRace";
    } else {
        theKey += "RaceUnspecified";
    }
    return theKey;
}

int main() {
    //read in a csv file and create a vector of objects representing each counties data
    std::vector<shared_ptr<regionData>> pileOfData;

    // read in the police data
    read_csv(pileOfData, "police_shootings_cleaned.csv", POLICE);

    // read in the demographic data
    read_csv(pileOfData, "county_demographics.csv", DEMOG);

    //create a visitor to combine the state data
    visitorCombineState theStates;
    statTool::createStateData(pileOfData, theStates);
    // theStates.printAllCombo(&demogData::getBelowPovertyCount, &psCombo::getNumberOfCases);

    //create a visitor to combine the county data
    visitorCombineCounty theCounties;
    statTool::createCountyData(pileOfData, theCounties);
    // theCounties.printAllCombo(&demogData::getBelowPovertyCount, &psCombo::getNumberOfCases);

    //Do stats work here
    // cout << "State data Pop under 18 and below poverty: " << endl;
    // statTool::computeStatsDemogRegionData(&theStates, &demogData::getpopUnder18, &demogData::getBelowPoverty,
    //     &demogData::getpopUnde185Count, &demogData::getBelowPovertyCount);
    // cout << "County data Pop under 18 and below poverty: " << endl;
    // statTool::computeStatsDemogRegionData(&theCounties, &demogData::getpopUnder18, &demogData::getBelowPoverty,
    //     &demogData::getpopUnder18Count, &demogData::getBelowPovertyCount);
    // cout << "State data Pop below poverty and HS up: " << endl;
    // statTool::computeStatsDemogRegionData(&theStates, &demogData::getBelowPoverty, &demogData::getHSup,
    //     &demogData::getBelowPovertyCount, &demogData::getHSupCount);
    // cout << "County data Pop below poverty and HS up: " << endl;
    // statTool::computeStatsDemogRegionData(&theCounties, &demogData::getBelowPoverty, &demogData::getHSup,
    //     &demogData::getBelowPovertyCount, &demogData::getHSupCount);
    // cout << "County data PS mental health and white victims: " << endl;
    // statTool::computeStatsPSData(&theCounties, &psCombo::getNumMentalI, &psCombo::getWhiteCountPS);
    // cout << "County data PS mental health and african american victims: " << endl;
    // statTool::computeStatsPSData(&theCounties, &psCombo::getNumMentalI, &psCombo::getBlackCountPS);
    // cout << "County data population and number of incidents: " << endl;
    // statTool::computeStatsMixRegionData(&theCounties, &demogCombo::getPop, &psCombo::getNumberOfCases);
    // cout << "County data pop under 18 and incidents under 18: " << endl;
    // statTool::computeStatsMixRegionData(&theCounties, &demogCombo::getpopUnder18Count, &psCombo::getCasesUnder18);
    // cout << "County data proportion whiteNH general vs whiteNH PS" << endl;
    // statTool::computeStatsRaceProportion(/* fill in */);


    /*
    //create a visitor to combine the state data
    visitorCombineState theStates;
    //create the state demographic data
    statTool::createStateData(pileOfData, theStates);

    //create a visitor to combine the county data (need aux map city-> county)
    visitorCombineCounty theCounties;
    statTool::createCountyData(pileOfData, theCounties);
    */

    // for (const auto &obj : theCounties.getComboPolice()) {
    //     std::cout << obj.first << std::endl;
    // }

    visitorCreateKey theKeys(&makeKeyDemog, &makeKeyPS);
    statTool::createKeys(pileOfData, theKeys);

    // visitorCombineKeyDemog theKeyedDemog(&makeKeyDemog, theKeys.getDemogRegionToKey());
    // statTool::createKeyedDataDemog(pileOfData, theKeyedDemog);
    // theKeyedDemog.printAllCombo();

    visitorCombineKeyPS theKeyedPS(&makeKeyPS, theKeys.getPsRegionToKey());
    statTool::createKeyedDataPS(pileOfData, theKeyedPS);
    theKeyedPS.printAllCombo();

    // for (const auto &obj : theKeys.getDemogRegionToKey()) {
    //     std::cout << obj.first << std::endl;
    //     std::cout << obj.second << std::endl;
    // }
    

    // cout << "No errors" << endl;


    // std::vector<shared_ptr<regionData>> theDemogData = read_csv(
    //         "county_demographics.csv", DEMOG);

    // std::vector<shared_ptr<regionData>> thePoliceData = read_csv(
    //         "police_shootings_cleaned.csv", POLICE);

    // theAnswers.createComboDemogData((std::vector<shared_ptr<demogData> >&) theDemogData);
    // theAnswers.createComboPoliceData((std::vector<shared_ptr<psData> >&) thePoliceData);

    // theAnswers.comboReport(92);

    // theAnswers.createComboDemogData((std::vector<shared_ptr<demogData> >&)theDemogData);
    // theAnswers.createComboPoliceData((std::vector<shared_ptr<psData> >&)thePoliceData);

    // theAnswers.reportTopTenStatesBP();

     //debug print out
    // for (const auto &obj : thePoliceData) {
    //     std::cout << *obj << std::endl;
    // }
    
    
    // theAnswers.createComboDemogData(theDemogData);
    // theAnswers.createComboPoliceData(thePoliceData);
    // cout << theAnswers << endl;


    /*
    cout << "*** the state that needs the most pre-schools**" << endl;
    string needPK = theAnswers.youngestPop();
    cout << *(theAnswers.getStateData(needPK)) << endl;
    cout << "*** the state that needs the most high schools**" << endl;
    string needHS = theAnswers.teenPop();
    cout << *(theAnswers.getStateData(needHS)) << endl;
    cout << "*** the state that needs the most vaccines**" << endl;
    string needV = theAnswers.wisePop();
    cout << *(theAnswers.getStateData(needV)) << endl;

    cout << "*** the state that needs the most help with education**" << endl;
    string noHS = theAnswers.underServeHS();
    cout << *(theAnswers.getStateData(noHS)) << endl;
    cout << "*** the state with most college grads**" << endl;
    string grads = theAnswers.collegeGrads();
    cout << *(theAnswers.getStateData(grads)) << endl;

    cout << "*** the state with most population below the poverty line**" << endl;
    string belowPov = theAnswers.belowPoverty();
    cout << *(theAnswers.getStateData(belowPov)) << endl;
    */
    
    return 0;
}

