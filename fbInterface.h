#pragma once
#include "land.h"
#include "terrain.h"
#include "firePlane.h"
#include "fireTruck.h"

class fbInterface
{
public:
	fbInterface(int size, int fTrucks, int fPlanes);
	~fbInterface(void);

	terrain trn;
	//προσθέτει φορτηγό στην εξομείωση
	void addTruck();
	//προσθέτει αεροπλάνο
	void addPlane();

	//ξεκινάει την εξομείωση
	void start();
	//εμφανίζει στατιστικά στο χρήστη
	void displayStatistics();

	int _size,_endedFires;
};

