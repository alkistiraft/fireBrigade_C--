#pragma once
#include "land.h"
#include "consts.h"

#include <stdlib.h>
#include <queue>

using namespace std;

class terrain
{
public:
	terrain(void);
	terrain(int);
	~terrain(void);
	//Χρησιμοποιούμε vector<vector> για να δημιουργήσουμε δυσδιάστατο πίνακα
	//που αναπαριστά την γη στην οποία κινούνται τα οχήματα
	vector<vector<land>> block;

	int getSize(){return size;};
	int onFire(){return _onFire;};
	//πραγματοποεί αλλαγές στην κατάσταση των περιοχων, ξεκινάει φωτιές, εξαπλώνει φωτιές κτλ.
	void update();
	void spreadFire(land);
	land alert();
	//ουρά με τα τμήματα που έχουν πιάσει φωτιά και δεν έχει αποσταλεί πυροσβεστικό
	//για την κατάσβεση της.
	queue<land> alerts;
	//τμήματα με φωτιά
	int _onFire;
	//σβησμένες φωτιές
	int _endedFires;
	//κατάσβεση φωτιάς σε μια περιοχή
	void endFire(int _lat, int _long);

private:
	int size;

	
};

