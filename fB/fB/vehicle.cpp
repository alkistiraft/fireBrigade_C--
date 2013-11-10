#include "vehicle.h"
#include "land.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>

using namespace std;

int vehicle::vehicles=0;
vector<vehicle*> vehicle::fleet;
terrain *_terrain;

int vehicle::BASE_LAT=0;
int vehicle::BASE_LONG=0;

vehicle::vehicle(void)
{
	//αρχικοποίηση μεταβλητών
	_state=vehicle::DEFAULT_STATE;

	_age=0;
	_ageLimit=vehicle::DEFAULT_AGE_LIMIT;

	_fuelCapacity = vehicle::DEFAULT_FUEL_CAPACITY;
	_fuelConsumption = vehicle::DEFAULT_FUEL_CONSUMPTION;
	_fuelTank = _fuelCapacity;

	_speed = vehicle::DEFAULT_SPEED;

	_waterCapacity = vehicle::DEAFULT_WATER_CAPACITY;
	_waterConsumption = vehicle::DEFAULT_WATER_CONSUMPTION;
	_waterTank = _waterCapacity;

	_posLat = vehicle::DEFAULT_LATITUDE;
	_posLong= vehicle::DEFAULT_LONGITUDE;

	vehicle::vehicles++;
	vehicle::fleet.push_back(this);
}

vehicle::vehicle(int ageLimit,int fuelCapacity, int fuelConsumption,int waterCapacity, int waterConsumption, int speed, int _lat, int _long)
{
	_state=vehicle::DEFAULT_STATE;

	_age=0;
	_ageLimit=ageLimit;

	_fuelCapacity = fuelCapacity;
	_fuelConsumption = fuelConsumption;
	_fuelTank = _fuelCapacity;
	
	_waterCapacity = waterCapacity;
	_waterConsumption = waterConsumption;
	_waterTank = _waterCapacity;

	_speed = speed;

	_posLat = _lat;
	_posLong= _long;

	vehicle::vehicles++;
	vehicle::fleet.push_back(this);
}


vehicle::~vehicle(void)
{
	vehicle::vehicles--;
}

void vehicle::setDest(int _lat, int _long)
{
	this->_destLat = _lat;
	this->_destLong = _long;
	this->_state = vehicle::MOVING_STATE;
}

bool vehicle::destReached()
{
	//ελέγχει αν το όχημα έφτασε στον προορισμό του
	if(_posLat == _destLat && _posLong == _destLong ){
		return true;
	}
	return false;
}

int vehicle::incAge()
{
	//αυξάνει την ηλικία του οχήματος, αν είναι μεγαλύτερη από ένα όρι, το απενεργοποιεί
	this->_age++;
	if( this->_age > this->_ageLimit )
		this->_state = vehicle::DEACTIVATED_STATE;
	return _age;
}

void vehicle::move()
{	
	//μετακινεί το όχημα
	if(this->_state == vehicle::MOVING_STATE){
		if(destReached()==false){
			for(int i=0;i<this->_speed;i++){
				//κάθετος άξονας
				this->moveUpDown();
				//οριζόντιος άξονας
				this->moveLeftRight();
				if(destReached()){
					this->_state = vehicle::ALERT_STATE;
					break;
				}
			}
		}else{
			this->_state = vehicle::ALERT_STATE;
			if (this->_state == vehicle::MALFUNCTION_STATE)
				this->_state = vehicle::BASE_REACHED_STATE;
		}
	}
}

void vehicle::moveUpDown()
{
	if(this->_state == vehicle::MOVING_STATE){
		if(_posLong < _destLong)
			this->_posLong++;
		else if( _posLong > _destLong)
			this->_posLong--;
	}
}

void vehicle::moveLeftRight()
{
	if(this->_state == vehicle::MOVING_STATE){
		if(_posLat < _destLat)
			this->_posLat++;
		else if( _posLat > _destLat)
			this->_posLat--;
	}
}

void vehicle::consumeFuel()
{
	if(this->_state == vehicle::MOVING_STATE){
		if( this->_fuelTank >= this->_fuelConsumption )
			this->_fuelTank-= this->_fuelConsumption;
		else
			this->_state = vehicle::MALFUNCTION_STATE;
	}
}

void vehicle::update()
{
	this->incAge();
	if( this->_state == vehicle::MOVING_STATE ){
		this->move();
		this->consumeFuel();
	}else if( this->_state == vehicle::MALFUNCTION_STATE ){
		this->setDest(vehicle::BASE_LAT, vehicle::BASE_LONG);
		this->_state = vehicle::MALFUNCTION_STATE ;
		this->move();
	}else if( this->_state == vehicle::ALERT_STATE ){

	}else if( this->_state == vehicle::BASE_REACHED_STATE ){
		this->_fuelTank = this->_fuelCapacity;
		this->_waterTank = this->_waterCapacity;
	}
}

void vehicle::alert(land block)
{
	if(block.getState() == land::ON_FIRE && this->_state == vehicle::NORMAL_STATE){
		this->setDest(block._lat(), block._long());
		this->move();
		this->consumeFuel();
	}

}

