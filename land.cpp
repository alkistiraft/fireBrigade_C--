#include "land.h"

#include <stdlib.h>
#include <iostream>

land::land(void)
{
	state = land::NORMAL;
	timeOnFire = 0;
	_latitude = land::DEFAULT_LAT;
	_longitude = land::DEFAULT_LONG;
}

land::land(int x, int y)
{
	state = land::NORMAL;
	_latitude = x;
	_longitude = y;
}


land::~land(void)
{
}

int land::getState()
{
	return state;
}

int land::endFire()
{
	state = land::NORMAL;
	timeOnFire = 0;
	return state;
}

int land::startFire()
{
	if(state == land::NORMAL){
		state = land::ON_FIRE;
	}
	return state;
}

int land::update(){
	if( rand()%land::FIRE_SPAWN_PROB_MAX < land::FIRE_SPAWN_PROB){
		startFire();
	}

	if( state == land::ON_FIRE )
		timeOnFire++;

	return state;
}

