#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <cctype>

using namespace std;

// struct containing three elements: courseId, title, and a vector of prerequisites
struct Course {
    string courseId;
    string title;
    vector<string> prerequisites;
};

// hash table data structure to hold courses
unordered_map<string, Course> courseTable;

// read and store data in hash table
void loadData() {

    string fileName;
    string line;

    cout << "\nEnter name of file.\n";
    cin.ignore();
    getline(cin, fileName); // file name is stored

    ifstream file;
    file.open(fileName);

    // error handling if file is not opened
    if (!file.is_open()) {
        cout << "\nError opening file.\n";
        return;
    }

    else {

        // read every line in file
        while (getline(file, line)) {

            stringstream ss(line);
            string word;
            Course course;
            
            // parse line and store courseId, title, and prerequisite in Course object
            if (getline(ss, word, ',')) {
                course.courseId = word;
            }

            if (getline(ss, word, ',')) {
                course.title = word;
            }

            while (getline(ss, word, ',')) {
                course.prerequisites.push_back(word);
            }

            courseTable[course.courseId] = course;
        }

        cout << "\nData loaded successfully!\n";
        }
    }

// sort and print courses
void printCourseList() {
    
    // error handling if courses have not been loaded
    if (courseTable.empty()) {
        cout << "\nNo courses available. Please load data first.\n";
        return;
    }

    cout << "\nHere is the course list:\n";

    vector<string> courseIds;

    // loop through hash table, accessing the key-value pair by reference and automatically detecting the data type
    for (const auto& pair : courseTable) {
        courseIds.push_back(pair.first); // the courseId is appended to the local vector
    }

    // local vector is sorted
    sort(courseIds.begin(), courseIds.end());

    cout << "\nCourse List:\n" << endl;

    // loop through vector, accessing the id strings by reference
    for (const string& id : courseIds) {
        cout << id << ", " << courseTable[id].title << endl; // print course id and corresponding title
    }
}

// search for course and associated prerequisites
void searchCourse() {

    string id;
    
    cout << "\nWhich course do you want to search for?\n";
    cin >> id;   

    transform(id.begin(), id.end(), id.begin(), toupper); // convert string to uppercase to match IDs

    // search hash table for key; return if not found
    if (courseTable.find(id) == courseTable.end()) {

        cout << "\nCourse not found.\n";
        return;
    }

    cout << endl << courseTable[id].courseId << ", " << courseTable[id].title << endl << "Prerequisites: ";
    
    // loop through and print the course prerequisites vector 
    for (unsigned i = 0; i < courseTable[id].prerequisites.size(); ++i) {

        cout << courseTable[id].prerequisites[i];
        if (i < courseTable[id].prerequisites.size() - 1) {

            cout << ", ";
        }
    }
    cout << endl;
}

int main() {

    int choice = 0;

    cout << "Welcome to the course planner.\n";

    // menu loop
    while (choice != 9) {

        cout << "\n   1. Load Data Structure\n";
        cout << "   2. Print Course List\n";
        cout << "   3. Print Course\n";
        cout << "   9. Exit\n";

        cout << "\nWhat would you like to do?\n";
        
        cin >> choice;

        // error handling if input fails
        if (cin.fail()) {
            
            cout << "\nIvalid Option.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {

        case 1:

            loadData();
            break;

        case 2:

            printCourseList();
            break;

        case 3:

            searchCourse();
            break;

        case 9:

            cout << "\nThank you for using the course planner!\n";
            break;

        default:

            cout << "\nInvalid option.\n";
        }       
    }
    return 0;
}