// HempSimConsole.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdlib>
#include "HempSimClass.h"
//using namespace hemp_sim;

int main(int argc, char * argv[])
{
    hemp_sim::HempSimParams_t params;
    hemp_sim::hemp_sim* hemp_sim_ptr;

    std::cout << "HEMP Simulation Program, Version : " << VERSION << std::endl;
    if (argc != 15)
    {
        std::cout << "Usage:" << std::endl;
        std::cout << "HempSimConsole x y z hob gamyld bfield bangle ndelr oux iter ap bp rnp top" << std::endl;
        //return 1;
        std::cout << "Setting Defaults " << std::endl;
        params.x = 0.0;
        params.y = 0.0;
        params.z = 0.0;
        params.hob = 100.0;
        params.gamyld = 0.001;
        params.bfield = 0.00002;
        params.bangle = 20.0;
        params.ndelr = 50;
        params.oux = 0;
        params.iter = 20;
        params.ap = 2.2;
        params.bp = 0.25;
        params.rnp = 5.62603;
        params.top = 2.24;

    }
    else
    {
        std::cout << "Simulation Input Parameters: " << std::endl;
        params.x      = std::atof(argv[1]);
        std::cout << "X = " << params.x << std::endl;
        params.y      = std::atof(argv[2]);
        std::cout << "Y = " << params.y << std::endl;
        params.z      = std::atof(argv[3]);
        std::cout << "Z = " << params.z << std::endl;
        params.hob    = std::atof(argv[4]);
        std::cout << "HOB = " << params.hob << std::endl;
        params.gamyld = std::atof(argv[5]);
        std::cout << "GAMYLD = " << params.gamyld << std::endl;
        params.bfield = std::atof(argv[6]);
        std::cout << "BFIELD = " << params.bfield << std::endl;
        params.bangle = std::atof(argv[7]);
        std::cout << "BANGLE = " << params.bangle << std::endl;
        params.ndelr  = std::atoi(argv[8]);
        std::cout << "NDELR = " << params.ndelr << std::endl;
        params.oux    = std::atoi(argv[9]);
        std::cout << "OUX = " << params.oux << std::endl;
        params.iter   = std::atoi(argv[10]);
        std::cout << "ITER = " << params.iter << std::endl;
        params.ap     = std::atof(argv[11]);
        std::cout << "AP = " << params.ap << std::endl;
        params.bp     = std::atof(argv[12]);
        std::cout << "BP = " << params.bp << std::endl;
        params.rnp    = std::atof(argv[13]);
        std::cout << "RNP = " << params.rnp << std::endl;
        params.top    = std::atof(argv[14]);
        std::cout << "TOP = " << params.top << std::endl;
    }

    std::cout << "Creating HEMP Simulation Instance " << std::endl;
    hemp_sim_ptr = new hemp_sim::hemp_sim(&params);

    // Running Simulations
    hemp_sim_ptr->run_sim();

    std::cout << "Simulation Compelete " << std::endl;


}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

