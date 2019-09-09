#include "ValidCheck.h"
#include "Writer.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

#define EMPLOYEES_FILE "employees.txt"
#define CUSTOMERS_FILE "customers.txt"
#define PLANES_FILE "planes.txt"
#define FLIGHTS_FILE "flights.txt"
#define RESERVATIONS_FILE "reservation.txt"
#define EMPLOYEE_FLIGHT_FILE "employee-flight.txt"

using namespace std;

/**
 * checks if the customer with this id is exist
 * @param id - the id of the customer we search
 * @param r - a Reader*
 * @return true if the customer with this id is exist, else return false
 */
bool ValidCheck:: customerExist(string id, Reader* r) {
    string info = r->findLineById(CUSTOMERS_FILE, id, 0);
    // if we get empty line it is means that customer with the id we
    // want doesn't exist
    if (info == "") {
        return false;
    }
    return true;
}
/**
 * checks if the flight with this id is exist
 * @param id - the id of the flight we search
 * @param r - a Reader*
 * @return true if the flight with this id is exist, else return false
 */
bool ValidCheck:: flightExist(string id, Reader* r) {
    string info = r->findLineById(FLIGHTS_FILE, id, 0);
    // if we get empty line it is means that flight with the id we
    // want doesn't exist
    if (info == "") {
        return false;
    }
    return true;
}
/**
 * check if the plane with this model number is available in this date
 * @param modelNumber - the model number of the plane
 * @param date - a Date
 * @param r - a Reader*
 * @return true if the plane is available, else return false
 */
bool ValidCheck:: planeAvailable(string modelNumber, Date date, Reader* r) {
    int count = 0;
    // get all the lines of the planes that have this model number
    vector<string> planesExist = r->findLinesById(PLANES_FILE, modelNumber, 1);

    if (planesExist .empty()) {
        __throw_invalid_argument("There is no plane of this type of model");
    }

    ifstream readFile;
    readFile.open(FLIGHTS_FILE);
    string line;
    if(!readFile.is_open()) {
        throw "can't create the file";
    }
    vector<string> f;
    while (getline(readFile, line)) {
        if (line.find(modelNumber, 0) != string::npos) {
            f = r->split(line, ',');
            // if the plane isn't available
            if (f[1] == modelNumber && f[2] == date.getDate()) {
                count++;
            }
        }
    }
    readFile.close();

    // if there is no planes with this model number that are available in this date
    if (count >= planesExist.size()) {
        return false;
    }
    return true;
}
/**
 * check if there is a crew that is available for the flight with the 'idFlight'
 * @param modelNumber - the model number of the plane of the flight
 * @param date - the date of the flight
 * @param idFlight - the id of the flight
 * @param r - a Reader*
 * @return true if there is a crew that is available for the flight with the 'idFlight'
 */
bool ValidCheck:: crewNeededAvailable(string modelNumber, Date date, string idFlight,
                                      Reader* r) {
    // find the information about the model number plane the flight needs
    string planeInfo = r->findLineById(PLANES_FILE, modelNumber, 1);
    if (planeInfo == "") {
        __throw_invalid_argument("There is no plane of this type of model");
    }
    vector<string> v = r->split(planeInfo, ',');
    map<Jobs, int> crewNeeded;
    // put the crew the flight needs on a map
    for (int i = 0; i <= OTHER; ++i) {
        crewNeeded.insert(pair<Jobs,int>((Jobs)i, stoi(v[5+i])));
    }
    list<string> manager, navigator, flyAttendant, pilot, other;

    ifstream readFile;
    readFile.open(EMPLOYEES_FILE);
    string line;
    if(!readFile.is_open()) {
        throw "can't create the file";
    }
    vector<string> e;
    // put the id of every employee in the right list according to his job
    while (getline(readFile, line)) {
        e = r->split(line, ',');

        if (e[1] == "MANAGER") {
            manager.push_back(e[0]);
        } else if (e[1] == "NAVIGATOR") {
            navigator.push_back(e[0]);
        } else if (e[1] == "FLY_ATTENDANT") {
            flyAttendant.push_back(e[0]);
        } else if (e[1] == "PILOT") {
            pilot.push_back(e[0]);
        } else {
            other.push_back(e[0]);
        }
    }
    readFile.close();

    map<string, MyFlight*> flights;
    MyFlight* fl;
    readFile.open(FLIGHTS_FILE);
    if(!readFile.is_open()) {
        throw "can't create the file";
    }

    // loading all the flights
    while (getline(readFile, line)) {
        e = r->split(line, ',');
        Date date = Date(e[2]);
        fl = new MyFlight(stoi(e[1]), date, e[3], e[4], e[0], r);
        flights.insert(pair<string, MyFlight*>(e[0], fl));
    }
    readFile.close();

    // if there is already flights that exist
    if (!flights.empty()) {
        readFile.open(EMPLOYEE_FLIGHT_FILE);
        if(!readFile.is_open()) {
            throw "can't create the file";
        }
        // check which employee is not available
        while (getline(readFile, line)) {
            e = r->split(line, ',');

            // if we find a flight with a date as our flight
            if (flights.find(e[1])->second->getDate() == date) {

                // if the employee is manager delete him from the list of the available managers
                if (find(manager.begin(), manager.end(), e[0]) != manager.end()) {
                    manager.remove(e[0]);
                    // if the employee is navigator delete him from the list of the available
                    // navigators
                } else if (find(navigator.begin(), navigator.end(), e[0]) != navigator.end()) {
                    navigator.remove(e[0]);
                    // if the employee is fly attendant delete him from the list of the available
                    // fly attendants
                } else if (find(flyAttendant.begin(), flyAttendant.end(), e[0])
                           != flyAttendant.end()) {
                    flyAttendant.remove(e[0]);
                    // if the employee is pilot delete him from the list of the available pilots
                } else if (find(pilot.begin(), pilot.end(), e[0]) != pilot.end()) {
                    pilot.remove(e[0]);
                    // if the employee is other delete him from the list of the available others
                } else if (find(other.begin(), other.end(), e[0]) != other.end()){
                    other.remove(e[0]);
                }
            }
        }
        readFile.close();
    }

    Writer w;
    bool availableCrew = true;
    int m, n, f, p, o;
    m = crewNeeded.find(MANAGER)->second;
    n = crewNeeded.find(NAVIGATOR)->second;
    f = crewNeeded.find(FLY_ATTENDANT)->second;
    p = crewNeeded.find(PILOT)->second;
    o = crewNeeded.find(OTHER)->second;

    // if there is not enough crew that is available
    if (m > manager.size() || n > navigator.size() || f > flyAttendant.size() ||
        p > pilot.size() || o > other.size()) {
        availableCrew = false;
        // add the right crew to the flight, and write it to the file
    } else {
        w.writeEmployeeFlight(m, manager, idFlight);
        w.writeEmployeeFlight(n, navigator, idFlight);
        w.writeEmployeeFlight(f, flyAttendant, idFlight);
        w.writeEmployeeFlight(p, pilot, idFlight);
        w.writeEmployeeFlight(o, other, idFlight);
    }
    // delete all the flights pointers we create
    for (const auto& flight: flights) {
        delete (flight.second);
    }

    return availableCrew;
}
/**
 * check if the flight with this id is available - i.e. if there is a place
 * in the class 'cls' in this flight
 * @param id - the id of the flight
 * @param cls - a class (FIRST_CLASS or SECOND_CLASS)
 * @param r - a Reader*
 * @return true if there is a place in the class 'cls' in this flight, else return false
 */
bool ValidCheck:: flightAvailable(string id, Classes cls, Reader* r) {
    int maxPlace;
    // get the information about the flight
    string flightInfo = r->findLineById(FLIGHTS_FILE, id, 0);
    if (flightInfo == "") {
        __throw_invalid_argument("There is no flight with this id");
    }
    // get the information about a plane with a model number that the flight has
    string planeInfo = r->findLineById(PLANES_FILE, r->split(flightInfo, ',')[1], 1);
    // check how much places there is in the flight in the 'cls'
    if (cls == FIRST_CLASS) {
        maxPlace = stoi(r->split(planeInfo, ',')[2]);
    } else {
        maxPlace = stoi(r->split(planeInfo, ',')[3]);
    }

    ofstream write;
    write.open (RESERVATIONS_FILE, ios::out | ios::app | ios::ate);
    // if a file stream wasn't successful opening a file
    if (!write.is_open()) {
        __throw_bad_exception();
    }
    write.close();

    ifstream readFile;
    string line;
    readFile.open(RESERVATIONS_FILE);

    if(!readFile.is_open()) {
        __throw_invalid_argument("can't create the file");
    }
    vector<string> e;
    Classes c;

    // go over all the reservation and check how much reservation the flight have
    while (getline(readFile, line)) {
        e = r->split(line, ',');
        if (e[3] == "FIRST CLASS") {
            c = FIRST_CLASS;
        } else {
            c = SECOND_CLASS;
        }

        if (e[2] == id && c == cls) {
            maxPlace--;
        }
    }

    // there is no place in this flight in this class
    if (maxPlace <= 0) {
        return false;
    }
    return true;
}