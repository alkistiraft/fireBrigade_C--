#include <iostream>

#include "land.h"
#include "terrain.h"
#include "vehicle.h"
#include "fireTruck.h"
#include "firePlane.h"
#include "fbInterface.h"

using namespace std;

int main()
{
	fbInterface fbI = fbInterface(50,20,25);

	fbI.start();
	system("pause");
}