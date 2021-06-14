/* aggregate data */
#include "dataAQ.h"
#include "demogData.h"
#include "psData.h"
#include <iostream>
#include <algorithm>
#include <iomanip>

dataAQ::dataAQ() {}

string makeKeyExample(shared_ptr<demogData> theData) {
  string theKey = "Key";

  if (theData->getpopBelowPovLine() < 10) {
    theKey += "BelowPovLessTenPer";
  } else if (theData->getpopBelowPovLine() < 20) {
    theKey += "BelowPovLessTwentyPer";
  } else if (theData->getpopBelowPovLine() < 30) {
    theKey += "BelowPovLessThirtyPer";
  } else {
    theKey += "BelowPovAboveThirtyPer";
  }

  return theKey;
}


string makeKeyExample(shared_ptr<psData> theData) {
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
    theKey += "OtherRaceVictim";
  } else {
    theKey += "RaceUnspecifiedVictim";
  }
  return theKey;
}


//swtich to a function parameter
void dataAQ::createComboDemogDataKey(std::vector<shared_ptr<demogData> >& theData) {
  // make a pair of a hashmap based on key from makeKeyExample function
  string key;
  for (auto& c : theData) {
    key = makeKeyExample(c);

    if (allComboDemogData[key] == NULL) {
      // construct new object
      allComboDemogData[key] = make_shared<demogCombo>(c->getRegionName(), c->getState(), 
        c->getPop(), c->getpopOver65Count(), c->getpopUnder18Count(), c->getpopUnder5Count(), 
        c->getBAupCount(), c->getHSupCount(), c->getpopBelowPovLineCount(), c->getRace(), 1);
    } else {
      // same state but different county
      allComboDemogData[key]->addState(c->getState());
      allComboDemogData[key]->addNumberOfCounties(1);
      allComboDemogData[key]->addpopOver65Count(c->getpopOver65Count());
      allComboDemogData[key]->addpopUnder18Count(c->getpopUnder18Count());
      allComboDemogData[key]->addpopUnder5Count(c->getpopUnder5Count());
      allComboDemogData[key]->addBAupCount(c->getBAupCount());
      allComboDemogData[key]->addHSupCount(c->getHSupCount());
      allComboDemogData[key]->addpopBelowPovLineCount(c->getpopBelowPovLineCount());
      allComboDemogData[key]->addRace(c->getRace());
      allComboDemogData[key]->addPop(c->getPop());
    }
  }

  return;
}

void dataAQ::createComboPoliceDataKey(std::vector<shared_ptr<psData> >& theData) {
  // make a pair of a hashmap based on key from makeKeyExample function
  int age = 0, count65 = 0, count19to64 = 0, count18 = 0, countM = 0, countF = 0, 
    countMI = 0, countFlee = 0, countCases = 0;
  string key;
  for (auto& c : theData) {
    key = makeKeyExample(c);
    countCases++;
    raceDemogData race;

    // assess which age group to increment
    if (c->getAge() <= 18) {
      count18++;
    } else if (c->getAge() > 18 && c->getAge() < 65) {
      count19to64++;
    } else {
      count65++;
    }

    // assess which gender to increment
    if (c->getGender() == "M") {
      countM++;
    }
    else if (c->getGender() == "F") {
      countF++;
    }

    // assess if mental illness
    if (c->getMentalIllness()) {
      countMI++;
    }

    // assess if flee
    if (c->getFlee() != "Not fleeing" && c->getFlee() != "") {
      countFlee++;
    }

    // assess race
    if (c->getRace() == "W") {
      race.addWhiteNHCount(1);
    } else if (c->getRace() == "B") {
      race.addBlackCount(1);
    } else if (c->getRace() == "A") {
      race.addAsianCount(1);
    } else if (c->getRace() == "N") {
      race.addFirstNationCount(1);
    } else if (c->getRace() == "H") {
      race.addLatinxCount(1);
    } else if (c->getRace() == "O") {
      race.addOtherCount(1);
    }

    if (allComboPoliceData[key] == NULL) {
      // construct new object
      allComboPoliceData[key] = make_shared<psCombo>(c->getRegionName(), c->getState(), 
        countMI, countFlee, count65, count19to64, count18, race, countM, countF, countCases);
    } else {
      // same state but different county
      allComboPoliceData[key]->addState(c->getState());
      allComboPoliceData[key]->addNumMentalI(countMI);
      allComboPoliceData[key]->addFleeingCount(countFlee);
      allComboPoliceData[key]->addCasesOver65(count65);
      allComboPoliceData[key]->addCases19to64(count19to64);
      allComboPoliceData[key]->addCasesUnder18(count18);
      allComboPoliceData[key]->addRacialData(race);
      allComboPoliceData[key]->addNumMales(countM);
      allComboPoliceData[key]->addNumFemales(countF);
      allComboPoliceData[key]->addNumberOfCases(countCases);
    }

    age = 0, count65 = 0, count19to64 = 0, count18 = 0, countM = 0, countF = 0, 
    countMI = 0, countFlee = 0, countCases = 0;
  }

  return;

}

/******************************************/
/* state examples */
void dataAQ::createComboDemogData(std::vector<shared_ptr<demogData> >&  theData) {
  // initialize variables
  string state, region;
  int counties = 0, statePop = 0, NFpop = 0, Apop = 0, Bpop = 0, Lpop = 0, 
    HIpop = 0, MRpop = 0, Wpop = 0, WHpop = 0, pop65 = 0, pop18 = 0, pop5 = 0, 
    popBDG = 0, popHSDG = 0, popBPL = 0;

  for (int i = 0; i < theData.size(); i++) {
    // aggregate data
    counties++;
    pop65 += theData[i]->getpopOver65Count();
    pop18 += theData[i]->getpopUnder18Count();
    pop5 += theData[i]->getpopUnder5Count();
    popBDG += theData[i]->getBAupCount();
    popHSDG += theData[i]->getHSupCount();
    popBPL += theData[i]->getpopBelowPovLineCount();
    NFpop += theData[i]->getRace().getFirstNationCount();
    Apop += theData[i]->getRace().getAsianCount();
    Bpop += theData[i]->getRace().getBlackCount();
    Lpop += theData[i]->getRace().getLatinxCount();
    HIpop += theData[i]->getRace().getHIPacificIsleCount();
    MRpop += theData[i]->getRace().getMultiRaceCount();
    Wpop += theData[i]->getRace().getWhiteCount();
    WHpop += theData[i]->getRace().getWhiteNHCount();
    statePop += theData[i]->getPop();

    // assess csv file and group data by state name
    if (i == theData.size()-1 || theData[i]->getState() != theData[i+1]->getState()) {
      // attain state name
      state = theData[i]->getState();
      region = theData[i]->getRegionName();

      // call raceDemogData constructor
      raceDemogData race(NFpop, Apop, Bpop, Lpop, HIpop, MRpop, Wpop, WHpop, statePop);

      // call state constructor
      allComboDemogData[state] = make_shared<demogCombo>(region, state, statePop, 
        pop65, pop18, pop5, popBDG, popHSDG, popBPL, race, counties);

      // reinitialize variables
      counties = 0, statePop = 0, NFpop = 0, Apop = 0, Bpop = 0, Lpop = 0, 
        HIpop = 0, MRpop = 0, Wpop = 0, WHpop = 0, pop65 = 0, pop18 = 0, 
        pop5 = 0, popBDG = 0, popHSDG = 0, popBPL = 0;
    }
  }

  return;
}


void dataAQ::createComboPoliceData(std::vector<shared_ptr<psData> >& theData) {
  // initialize variables
  int age = 0, count65 = 0, count19to64 = 0, count18 = 0, countM = 0, countF = 0, 
    countMI = 0, countFlee = 0, countCases = 0;
  string state, region;

  for (int i = 0; i < theData.size(); i++) {
    // attain state name and region name
    state = theData[i]->getState();
    region = theData[i]->getRegionName();
    countCases++;
    raceDemogData race;

    // assess which age group to increment
    if (theData[i]->getAge() <= 18) {
      count18++;
    } else if (theData[i]->getAge() > 18 && theData[i]->getAge() < 65) {
      count19to64++;
    } else {
      count65++;
    }

    // assess which gender to increment
    if (theData[i]->getGender() == "M") {
      countM++;
    }
    else if (theData[i]->getGender() == "F") {
      countF++;
    }

    // assess if mental illness
    if (theData[i]->getMentalIllness()) {
      countMI++;
    }

    // assess if flee
    if (theData[i]->getFlee() != "Not fleeing" && theData[i]->getFlee() != "") {
      countFlee++;
    }

    // assess race
    if (theData[i]->getRace() == "W") {
      race.addWhiteNHCount(1);
    } else if (theData[i]->getRace() == "B") {
      race.addBlackCount(1);
    } else if (theData[i]->getRace() == "A") {
      race.addAsianCount(1);
    } else if (theData[i]->getRace() == "N") {
      race.addFirstNationCount(1);
    } else if (theData[i]->getRace() == "H") {
      race.addLatinxCount(1);
    } else if (theData[i]->getRace() == "O") {
      race.addOtherCount(1);
    }

    if (allComboPoliceData[state] == NULL) {
      // construct new object
      allComboPoliceData[state] = make_shared<psCombo>(region, state, countMI, 
        countFlee, count65, count19to64, count18, race, countM, countF, countCases);
    }
    else {
      // add elements to exiting object
      allComboPoliceData[state]->addNumMentalI(countMI);
      allComboPoliceData[state]->addFleeingCount(countFlee);
      allComboPoliceData[state]->addCasesOver65(count65);
      allComboPoliceData[state]->addCases19to64(count19to64);
      allComboPoliceData[state]->addCasesUnder18(count18);
      allComboPoliceData[state]->addRacialData(race);
      allComboPoliceData[state]->addNumMales(countM);
      allComboPoliceData[state]->addNumFemales(countF);
      allComboPoliceData[state]->addNumberOfCases(countCases);
    }

    age = 0, count65 = 0, count19to64 = 0, count18 = 0, countM = 0, countF = 0, 
    countMI = 0, countFlee = 0, countCases = 0;
  }

  return;
}

bool compareBPLPop(std::pair<string,shared_ptr<demogCombo>> left, std::pair<string,shared_ptr<demogCombo>> right) {
  return left.second->getpopBelowPovLine() > right.second->getpopBelowPovLine();
}

bool comparePS(std::pair<string, shared_ptr<psCombo>> left, std::pair<string, shared_ptr<psCombo>> right) {
  return left.second->getNumberOfCases() > right.second->getNumberOfCases();
}


//sort and report the top ten states in terms of number of police shootings 
void dataAQ::reportTopTenStatesPS() {
  std::vector<std::pair<string, shared_ptr<psCombo>>> v;
   
  // set precision to 2 decimal places
  cout.setf(ios::fixed);
  cout.setf(ios::showpoint);
  cout.precision(2);

  // create vector of police states hashmap
  for (auto& it : allComboPoliceData) {
    v.push_back(it);
  }

  // sort and print
  sort(v.begin(), v.end(), comparePS);
  cout << "Top ten states sorted on Police Shootings data & the associated below poverty data:" << endl;
  for (int i = 0; i < 10; i++) {
    cout << v[i].first << endl;
    cout << "Total population: " << allComboDemogData[v[i].first]->getPop() << endl;
    cout << "Police shooting incidents: " << v[i].second->getNumberOfCases() << endl;
    cout << "Percent below poverty: " << allComboDemogData[v[i].first]->getpopBelowPovLine() << endl;
  }

  cout << "**Full listings for top 3 Police Shooting data & the associated below poverty data for top 3:" << endl;

  for (int i = 0; i < 3; i++) {
    cout << *(allComboDemogData[v[i].first]) << endl;
    cout << *(v[i].second) << endl;
  }

  return;
}


    //sort and report the top ten states with largest population below poverty 
void dataAQ::reportTopTenStatesBP() {
  std::vector<std::pair<string, shared_ptr<demogCombo>>> v;
   
  // set precision to 2 decimal places
  cout.setf(ios::fixed);
  cout.setf(ios::showpoint);
  cout.precision(2);

  // create vector of police states hashmap
  for (auto& it : allComboDemogData) {
    v.push_back(it);
  }

  // sort and print
  sort(v.begin(), v.end(), compareBPLPop);
  cout << "Top ten states sorted on Below Poverty data & the associated police shooting data:" << endl;
  for (int i = 0; i < 10; i++) {
    cout << v[i].first << endl;
    cout << "Total population: " << v[i].second->getPop() << endl;
    cout << "Percent below poverty: " << v[i].second->getpopBelowPovLine() << endl;
    cout << "Police shooting incidents: " << allComboPoliceData[v[i].first]->getNumberOfCases() << endl;
  }

  cout << "**Full listings for top 3 Below Poverty data & the associated police shooting data for top 3:" << endl;

  for (int i = 0; i < 3; i++) {
    cout << *(v[i].second) << endl;
    cout << *(allComboPoliceData[v[i].first]) << endl;
  }

  return;
}

void dataAQ::comboReport(double thresh) {
  visitorReport report;
  std::vector<shared_ptr<regionData>> pileData;

  for (const auto &obj : allComboDemogData) {
    if (obj.second->getHSup() > thresh) {
      pileData.push_back(obj.second);
      pileData.push_back(allComboPoliceData[obj.first]);
    }
  }

  for (const auto &obj : pileData) {
      obj->accept(report);
  }
  return;
}

/* print all combo data */
std::ostream& operator<<(std::ostream &out, const dataAQ &theAnswers) {
  out << "Combo Demographic Info: ";
  for (auto const& entry : theAnswers.allComboDemogData) {
      out << "key: " << entry.first << endl;
      out << *(entry.second) << "\n";

  }

  for (auto const& entry : theAnswers.allComboPoliceData) {
      out << "key: " << entry.first << endl;
      out << *(entry.second) << "\n";

  }

  return out;
}