//
//  main.cpp
//  T8 - One Way Street
//
//  Created by Melissa Trevino on 3/16/16.
//  Copyright © 2016 Melissa Trevino. All rights reserved.
//
//  Melissa Treviño         A00816715
//  María Paula Anastás     A00817285


#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Global variables needed.
int iMatrix[100][100];      // Adjacency matrix.
int iSIZE;                  // Size of the matrix.

// Function that returns the minimum between two paths.
int minimum (int A, int B)
{
    return (A < B)? A : B;
}


// Floyd algorithm that constructs the shortest path from an original matrix.
void floyd()
{
    for (int k = 0; k < iSIZE; k++)
    {
        for (int i = 0; i < iSIZE; i++)
        {
            for (int j = 0; j < iSIZE; j++)
                iMatrix[i][j] = minimum (iMatrix[i][j], iMatrix[i][k] + iMatrix[k][i]);
        }
    }
}


int main() {
    // Variables used for the input.
    int iLocations, iBCars, iRoads;
    vector <string> vNames;
    string sRoad;
    char cType;
    
    // Number of locations, of broken cars, and roads.
    cin >> iLocations >> iBCars >> iRoads;
    iSIZE = iLocations;
    
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
