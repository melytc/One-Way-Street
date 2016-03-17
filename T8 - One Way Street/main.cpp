//
//  main.cpp
//  T8 - One Way Street
//
//  Created by Melissa Trevino on 3/16/16.
//  Copyright © 2016 Melissa Trevino. All rights reserved.
//
//  Objective:
//  - Get to any location starting from the garage, by using the shortest way possible.
//  - Report the total distance
//
//  We decided to use Floyd algorythm to know the shortest way between two locations.


#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Global variables needed.
//int iSIZE;
//
//void floyd (int iMatrix[])
//{
//    for (int iC = 0; iC <)
//}



int main() {
    
    int iLocations, iBCars, iRoads;
    vector <string> vNames;
    string sRoad;
    char cType;
    
    // Number of locations, of broken cars, and roads.
    cin >> iLocations >> iBCars >> iRoads;
    
    // iBCars + 1 names of locations
    for (int iName = 0; iName <= iBCars; iName++)
    {
        string aux;
        cin >> aux;
        vNames.push_back(aux);
    }
    
    // Roads
    int iSpace = 0;
    for (int iRoad = 0; iRoad < iRoads; iRoad++)
    {
        getline(cin, sRoad);
        if (sRoad.find('<') == true && sRoad.find('>') == true)
            cType = 'B';    // Bidirectional
        
        else if (sRoad.find('>') == true)
            cType = 'T';    // To
        
        else if (sRoad.find('<') == true)
            cType = 'F';    // From
        
        
    }
    
    return 0;
}
