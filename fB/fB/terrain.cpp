#include "terrain.h"
#include "land.h"

#include <stdlib.h>
#include <iostream>

terrain::terrain(void)
{
}

terrain::terrain(int size)
{
	this->size = size;
	this->_onFire = 0;
	this->_endedFires = 0;

	block.resize(size);
	for(int i=0; i<size;i++)
		block[i].resize(size);

	for(int i=0; i<size; i++){
		for(int j=0;j<size;j++){
			block[i][j] = land(i,j);
		}
	}
}


terrain::~terrain(void)
{
}

void terrain::update()
{	
	for(int i=0; i<size; i++){
		for(int j=0;j<size;j++){
			int prvStatus = block[i][j].getState();
			int crnStatus = block[i][j].update();
			if( prvStatus != crnStatus && crnStatus == land::ON_FIRE ){
				alerts.push(block[i][j]);
				_onFire++;
			}
		}
	}
}

void terrain::endFire(int _lat, int _long)
{
	this->block[_lat][_long].endFire();
	this->_endedFires++;
	this->_onFire--;
}
