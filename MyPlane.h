//
// Created by adi on 26/11/18.
//

#ifndef Ex2_MYPLANE_H
#define Ex2_MYPLANE_H

#include "interface.h"

class MyPlane : public Plane{
    string id;
    int modelNumber;
    map<Jobs, int> crewNeeded;
    int maxFirstClass;
    int maxEconomyClass;

public:
    MyPlane(int modelNumber, map<Jobs, int> crewNeeded,
            map<Classes, int> max_passengers, string id);
    int getModelNumber();
    map<Jobs, int> getCrewNeeded();
    int getMaxFirstClass();
    int getMaxEconomyClass();
    string getID();
};


#endif //Ex2_MYPLANE_H