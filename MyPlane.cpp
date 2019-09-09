#include "MyPlane.h"

/**
 * constructor
 * @param modelNumber - the model number of the plane
 * @param crewNeeded - the crew that the plane needed
 * @param max_passengers - the max passengers that the plane could have
 * @param id - the id of the plane
 */
MyPlane::MyPlane(int modelNumber, map<Jobs, int> crewNeeded,
                 map<Classes,int> max_passengers, string id) {
    this->id = id;
    this->modelNumber = modelNumber;
    this->crewNeeded = crewNeeded;
    this->maxFirstClass = max_passengers.at(FIRST_CLASS);
    this->maxEconomyClass = max_passengers.at(SECOND_CLASS);
}

/**
 * return the model number of the plane
 * @return the model number of the plane
 */
int MyPlane:: getModelNumber() {
    return this->modelNumber;
}
/**
 * return the crew needed of the plane
 * @return the crew needed of the plane
 */
map<Jobs, int> MyPlane:: getCrewNeeded(){
    return this->crewNeeded;
}
/**
 * return the max people that could be in the first class
 * @return the max people that could be in the first class
 */
int MyPlane:: getMaxFirstClass() {
    return this->maxFirstClass;
}
/**
 * return the max people that could be in the economy class
 * @return the max people that could be in the economy class
 */
int MyPlane:: getMaxEconomyClass() {
    return this->maxEconomyClass;
}
/**
 * return the id of the plane
 * @return the id of the plane
 */
string MyPlane:: getID() {
    return this->id;
}