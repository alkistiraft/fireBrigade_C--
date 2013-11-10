#include "fbInterface.h"
#include <iostream>
#include <Windows.h>

using namespace std;

fbInterface::fbInterface(int size, int fTrucks, int fPlanes)
{
	trn = terrain(size);
	
	for(int i=0;i<fTrucks;i++)
		new fireTruck();

	for(int i=0;i<fPlanes;i++)
		new firePlane();

	_size = size;
	_endedFires = 0;
}


fbInterface::~fbInterface(void)
{
}

void fbInterface::start()
{
	//Η εξοπείωση διαρκεί μέχρι όλες οι περιοχές να πιάσουν φωτιά
	while( this->trn._onFire < _size*_size ) {
		//ενημερώνει όλες τις περιοχές
		this->trn.update();

		//ενημερώνει ένα ένα τα οχήματα του στόλου
		for(int i=0;i< (int) vehicle::fleet.size(); i++)
			vehicle::fleet[i]->update();

		int _availableVehicles = 0;
		//υπολογίζει πόσα οχήματα είναι διαθέσιμα
		for(int i=0;i< (int) vehicle::fleet.size();i++){
			if( vehicle::fleet[i]->_state == vehicle::NORMAL_STATE){
				_availableVehicles++;
			}
		}
		//Στέλνει κάθε διαθέσιμο όχημα στις περιοχές που έχουν φωτιά
		for(int j=0;j<_availableVehicles;j++){
			if(this->trn.alerts.size() > 0){
				land tmp = this->trn.alerts.front();

				for(int i=0;i<(int)vehicle::fleet.size();i++){
					if( vehicle::fleet[i]->_state == vehicle::NORMAL_STATE){
						vehicle::fleet[i]->setDest(tmp._lat(),tmp._long());
						this->trn.alerts.pop();
						break;
					}

				}
			}
		}

		for(int i=0;i<(int)vehicle::fleet.size();i++){
			if(trn.block[vehicle::fleet[i]->getLat()][vehicle::fleet[i]->getLong()].getState() == land::ON_FIRE ){
				trn.endFire(vehicle::fleet[i]->getLat(),vehicle::fleet[i]->getLong());
				vehicle::fleet[i]->_state=vehicle::NORMAL_STATE;
				_endedFires++;
			}
		}
		//εμφανίζει στατιστικά
		this->displayStatistics();
	}
}

void fbInterface::displayStatistics()
{
	int _movingVehicles=0;
	int _inactiveVehicles=0;
	int _normalVehicles=0;
	int _malfunctionVehicles=0;
	int _alertVehicles=0;
	for(int i=0;i< (int) vehicle::fleet.size();i++)
	{
		switch(vehicle::fleet[i]->_state){
		case vehicle::MOVING_STATE:
			_movingVehicles++;
			break;
		case vehicle::DEACTIVATED_STATE:
			_inactiveVehicles++;
			break;
		case vehicle::NORMAL_STATE:
			_normalVehicles++;
			break;
		case vehicle::MALFUNCTION_STATE:
			_malfunctionVehicles++;
			break;
		case vehicle::ALERT_STATE:
			_alertVehicles++;
			break;
		}
	}

	cout << "\n\n";
	cout << "normal vehicles: \t\t" << _normalVehicles << '\n';
	cout << "moving vehicles: \t\t" << _movingVehicles << '\n';
	cout << "inactive vehicles: \t\t\t" << _inactiveVehicles << '\n';
	cout << "malfunction vehicles: \t\t\t" << _malfunctionVehicles << '\n';
	cout << "alerted vehicles: \t\t\t" << _alertVehicles << '\n';
	cout << "pending alerts: \t\t" << trn.alerts.size() << '\n';
	cout << "blocks on fire: \t\t" << trn._onFire << '\n';
	cout << "extinguished fires: \t\t" << _endedFires <<'\n';



}