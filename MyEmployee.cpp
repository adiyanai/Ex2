#include "MyEmployee.h"
#include "Reader.h"

/**
 * constructor
 * @param seniority - the seniority of the employee
 * @param birthYear - the birth year of the employee
 * @param employer_id - the id of the employer of the employee
 * @param title - the title job of the employee
 * @param id - the id of the employee
 * @param reader - a Reader*
 */
MyEmployee:: MyEmployee(int seniority, int birthYear, string employer_id, Jobs title,
                        string id, Reader* reader) {
    this->id = id;
    this->seniority = seniority;
    this->birthYear = birthYear;
    this->employerId = employer_id;
    this->title = title;
    this->r = reader;
}

/**
 * return the seniority of the employee
 * @return the seniority of the employee
 */
int MyEmployee:: getSeniority() {
    return  this->seniority;
}
/**
 * return the birth year of the employee
 * @return the birth year of the employee
 */
int MyEmployee:: getBirthYear() {
    return this->birthYear;
}
/**
 * return the employer of the employee
 * @return the employer of the employee
 */
Employee* MyEmployee:: getEmployer() {
    return r->getEmployee(this->employerId);
}
/**
 * return the title of the job of the employee
 * @return the title of the job of the employee
 */
Jobs MyEmployee:: getTitle() {
    return this->title;
}
/**
 * return the id of the employer
 * @return the id of the employer
 */
const string &MyEmployee:: getEmployerId() const {
    return this->employerId;
}
/**
 * return the id of the employee
 * @return the id of the employee
 */
string MyEmployee::getID() {
    return this->id;
}

