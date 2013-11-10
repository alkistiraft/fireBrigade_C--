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
	//��������� ������� ���� ���������
	void addTruck();
	//��������� ���������
	void addPlane();

	//�������� ��� ���������
	void start();
	//��������� ���������� ��� ������
	void displayStatistics();

	int _size,_endedFires;
};

