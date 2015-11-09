//============================================================================
// Name        : pso_ga.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "psoga.h"
using namespace std;

int main() {
	pso_ga* pso_ga_opt = new pso_ga();
	pso_ga_opt->run();
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
