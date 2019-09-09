#include "MyReservation.h"
#include "Reader.h"
/**
 * constructor
 * @param customerId - the id of the customer
 * @param flightId - the id of the flight
 * @param cls - the class
 * @param maxBaggage - the max baggage
 * @param id - the id of the reservation
 * @param reader - a Reader*
 */
MyReservation::MyReservation(string customerId, string flightId, Classes cls, int maxBaggage,
                             string id, Reader* reader) {
    this->id = id;
    this->customerId = customerId;
    this->flightId = flightId;
    this->cls = cls;
    this->maxBaggage = maxBaggage;
    this->r = reader;
}

/**
 * return the customer of the reservation
 * @return the customer of the reservation
 */
Customer* MyReservation:: getCustomer() {
    return r->getCustomer(this->customerId);
}
/**
 * return the flight of the reservation
 * @return the flight of the reservation
 */
Flight* MyReservation:: getFlight() {
    return r->getFlight(this->flightId);
}
/**
 * return the class of the reservation
 * @return the class of the reservation
 */
Classes MyReservation:: getClass() {
    return this->cls;
}
/**
 * return the max baggage of the reservation
 * @return the max baggage of the reservation
 */
int MyReservation:: getMaxBaggage() {
    return this->maxBaggage;
}
/**
 * return the id of the customer
 * @return the id of the customer
 */
const string &MyReservation::getCustomerId() const {
    return this->customerId;
}
/**
 * return the id of the flight
 * @return the id of the flight
 */
const string &MyReservation::getFlightId() const {
    return this->flightId;
}
/**
 * return the id of the reservation
 * @return the id of the reservation
 */
string MyReservation:: getID() {
    return this->id;
}