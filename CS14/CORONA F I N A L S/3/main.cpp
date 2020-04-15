#include "Patient.h"

#include <iostream>
#include <utility>

#include <queue>
#include <stack>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>

using namespace std;

// Describe any additional functions that are needed for part III

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Proper usage: " << argv[0] << " <patients_file>." << endl;
        return 1;
    }

    ifstream ifs(argv[1]);
    if (!ifs.is_open()) {
        cerr << "Error: Unable to open " << argv[1] << endl;
        return 1;
    }

    //??? intake_times;  // Part I, what data structure should be used here and why? (implement)
    // using set because we want the structure to have ability to quick access by intake time
    // set inserts in position as close as possible
    set<pair<int, int>> intake_times; // O(1)
    //??? patients; // Part II, what data structure should be used here and why? (implement)
    // using unodered_map because we want the structure to have quick access to the id
    unordered_map<int, Patient*> patients; // O(1)
    //??? patient_urgencies; // Part III, what data structure should be used here and why? (comments only)
    // use a vector because all we want to do is insert in the patients, while also having urgency
    // urgency of patient is set during the while loop later
    // vector<unordered_set<Patient*>> patient_urgencies; // O(1)
    // parameters should just be patient, it would insert all the patients in the same set 
    // as other orders
    // we use unordered_set because we want to have constant access 


    string first_name, last_name;
    int intake_time, urgency, id;

    // Overall runtime complexity: O(nlogn) where n is number of patients, worst case O(n^2)
    // Overall space complexity: O(n)
    while (ifs >> id) { // O(n)
        ifs >> first_name >> last_name >> intake_time >> urgency; // O(1)
        Patient* patient_record = new Patient(id, first_name + " "s + last_name); // O(1)
        patient_record->urgency(urgency); // O(1)

        intake_times.insert(make_pair(intake_time, id)); // O(logN)
        patients.insert(make_pair(id, patient_record)); // O(1) or O(n) worst case
        // if (urgency == 0)
        // patient_urgencies.at(0).push_back(patient_record) // o(1) worst case O(n)
        // else if (urgerncy == 1){
        // patient_urgencies.at(1).push_back(patient_record) // o(1) worst case O(n)
        //}
        // else
        //patient_urgencies.at(2).push_back(patient_record); // O(1) worst case O(n)
    }

    // Output Patients sorted by oldest intake_time (smallest) to newest intake_time (largest) (Implement)
    // Runtime: O(n) n is number of ids/patients
    // Space: O(1)
    cout << "Sorted by intake times: " << endl;
    set<pair<int, int>>::iterator it = intake_times.begin();
    while (it != intake_times.end()) {
        cout << *patients.at(it->second) << endl;
        it++;
    }

    // Output Patients ID's sorted by most urgent to least urgent
    // In comments describe how this would work. 
    // for (int i = 2; i > 0; i--){
    // unordered_set<Patient*>::iterator it = ...
    //}
    // iterate through starting from patient_urgencies.at(i).begin();
    // print out all the data within
    // decrease i to move to new priority
   
    return 0;
}
