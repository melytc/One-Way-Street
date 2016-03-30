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
#include <sstream>
#include <queue>
using namespace std;

// Global variables needed.
int iMatrix[100][100];      // Adjacency matrix.
int iSIZE;                  // Size of the matrix.

int iRightSide;             // Counter for road cicles.
int iLeftSide;

string sRoadValue;          // This will contain the numeric value, but in a string.
int iRoadValue;             // The value of the road.

string sCityName1;          // Two strings for each road input.
string sCityName2;

queue <int> qBrokenCars;        // Queue with cities.
vector <int> vTotal;        // Vector with the total road value for each case.
vector <string> vCities;

// Function that creates a road based on the string from the input.
void createRoad (string sRoad)
{
    int iActual = 0;
    iRightSide = 0;
    iLeftSide = 0;
    
    sRoadValue.clear();
    
    // Cicle for checking the left side of the road input.
    // This will know if the road goes from the right city to the left city.
    while (sRoad[iActual] == '<' || sRoad[iActual] == '-' || sRoad[iActual] == ' ')
    {
        if (sRoad[iActual] == '<')
            iLeftSide = 1;
        
        sRoad[iActual] = ' ';
        iActual++;
    }
    
    // Cicle for checking the path value, eliminating the character that are not numbers.
    while (sRoad[iActual] != '-' && sRoad[iActual] != ' ')
    {
        sRoadValue += sRoad[iActual];
        iActual++;
    }
    
    // Cicle for checking the right side of the road input.
    // This will know if the road goes from the left city to the right city.
    while (iActual != sRoad.length())
    {
        if (sRoad[iActual] == '>')
            iRightSide = 1;
        
        sRoad[iActual] = ' ';
        iActual++;
    }
    
    // Convertion from string to integer.
    istringstream ss(sRoadValue);
    ss >> iRoadValue;
    
    // Delete the past value.
    sRoadValue = "";
}

// Function that checks in the vector of city names, and adds it up if needed.
void checkCities (bool bCity1, bool bCity2, int &iSize)
{
    // Cicle that checks if the cities are in the array of names.
    for (int i = 0; i < iSize; i++)
    {
        if (vCities[i] == sCityName1)
            bCity1 = true;
        
        if (vCities[i] == sCityName2)
            bCity2 = true;
    }
    
    if (!bCity1)
        vCities.push_back(sCityName1);
    if (!bCity2)
        vCities.push_back(sCityName2);
}


// Function that adds the road value to the matrix.
void setRoadValue (int iCity1, int iCity2, int &iSize)
{
    // Cicle that gets the position of the city in the array of names.
    for (int i = 0; i < iSize; i++)
    {
        if (vCities[i] == sCityName1)
            iCity1 = i;
        
        if (vCities[i] == sCityName2)
            iCity2 = i;
    }
    
    // Checks for the road value between both cities.
    if (iCity1 != iCity2)
    {
        if (iRightSide)
            iMatrix[iCity1][iCity2] = iRoadValue;
        
        if (iLeftSide)
            iMatrix[iCity2][iCity1] = iRoadValue;
    }
}

// Function that gets the total road value to get to a broken car, passing through the cities.
int getRoadValue (int iSize, int iRoadValue)
{
    string sBrokenCar;
    int iBCPos;
    
    while (!qBrokenCars.empty())
    {
        iBCPos = qBrokenCars.front();
        for (int i = 0; i < iSize; i++)
        {
            if (vCities[i] == sBrokenCar)
                iBCPos = i;
        }
        
        iRoadValue += iMatrix[0][iBCPos] + iMatrix[iBCPos][0];
        qBrokenCars.pop();
    }
    
    vTotal.push_back(iRoadValue);
    return iRoadValue;
}


// Function that constructs the matrix for Floyd algorithm, having the diagonal
// in 0s (no road from the same city) and infinite lengths for the others (represented in 999s).
void contruct (int iSize)
{
    for (int i = 0; i < iSize; i++)
    {
        for (int j = 0; j < iSize; j++)
        {
            if (i == j)
                iMatrix[i][j] = 0;
            else
                iMatrix[i][j] = 999;
        }
    }
}

// Function that returns the minimum between two paths.
int minimum (int A, int B)
{
    return (A < B)? A : B;
}

// Floyd algorithm that constructs the shortest path from an original matrix.
void floyd(int iCities)
{
    for (int k = 0; k < iCities; k++)
    {
        for (int i = 0; i < iCities; i++)
        {
            for (int j = 0; j < iCities; j++)
                iMatrix[i][j] = minimum(iMatrix[i][j], iMatrix[i][k] + iMatrix[k][j]);
        }
    }
}


int main() {
    
    // Variables used for the input.
    int iCities, iBCars, iRoads, iSpace;
    
    // Number of cities, of broken cars, and roads.
    cin >> iCities >> iBCars >> iRoads;
    iSIZE = iCities;
    
    // Cicle to add iBCars + 1 names of cities to go to a vector.
    for (int iName = 0; iName <= iBCars; iName++)
    {
        string aux;
        cin >> aux;
        vCities.push_back(aux);
        if (iName != 0)
            qBrokenCars.push(iName);
    }
    
    // Create the matrix of adyacencies.
    contruct(iCities);
    
    // Cicle to read roads.
    cin.ignore();
    for (int iRoad = 0; iRoad < iRoads; iRoad++)
    {
        // Read from input.
        getline(cin, sRoadValue);
        
        // Extract the name of the first city.
        sCityName1 = sRoadValue;
        iSpace = sCityName1.find(" ");
        sCityName1 = sCityName1.substr(0, iSpace);
        sRoadValue = sRoadValue.substr(iSpace, sRoadValue.length());
        
        // Extract the name of the second city.
        sCityName2 = sRoadValue;
        iSpace = sCityName2.find(" ");
        while (iSpace == 0)
        {
            sCityName2 = sCityName2.substr(iSpace + 1, sCityName2.length());
            iSpace = sCityName2.find(" ");
        }
        
        sRoadValue = sCityName2;
        sCityName2 = sCityName2.substr(iSpace + 1, sCityName2.length());
        sRoadValue = sRoadValue.substr(0, iSpace);
        
        // Read and add the road to the matrix.
        createRoad(sRoadValue);
        checkCities(false, false, iCities);
        setRoadValue(-1, -1, iCities);
    }
    
    floyd(iCities);
    cout << getRoadValue(iSIZE, 0) << endl;
    
    return 0;
}