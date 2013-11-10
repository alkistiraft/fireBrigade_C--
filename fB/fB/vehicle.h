#pragma once
#include "land.h"
#include "terrain.h"
#include <stdlib.h>
#include <vector>

using namespace std;

class vehicle
{
public:
	vehicle(void);
	vehicle(int ageLimit,int fuelCapacity, int fuelConsumption, int waterCapacity, int waterConsumption, int speed, int _lat, int _long);
	~vehicle(void);

	int _state;

	int getAge(){return _age;};
	int getFuelCapacity(){return _fuelCapacity;};
	int getSpeed(){return _speed;};

	int getLat(){return _posLat;};
	int getLong(){return _posLong;};

	//������� �� ����� �� ��� ���������
	void setDest(int _lat, int _long);
	bool destReached();

	//������� ��� ������
	int incAge();

	//����� �� ����� ���� ��������� ��� ������ �����
	void move();
	//���������� ��� ��������� ��� ��������, �� ����� �� ����� �� ���������� �������, ������� ��� ������
	//����������� ������� ���
	void update();
	//���������� �� ����� ��� ����� �� ��� ���������
	void alert(land block);

	//������� ������ ��������
	static int vehicles;
	//� ������ ��� ��������, ����������� �� vector ��� ������� ����������� �� �������� ���������� ������
	static vector<vehicle*> fleet;
	//� ���� ��� ����� ��� �����
	static int BASE_LAT, BASE_LONG;
	//�������� �������� ��� ������� �� �������
	static const int NORMAL_STATE=0, MOVING_STATE=1, MALFUNCTION_STATE=2, DEACTIVATED_STATE=3;
	static const int ALERT_STATE=4, BASE_REACHED_STATE=5, FIRE_OUT_STATE=0;

	static const int DEFAULT_STATE=0;
	static const int DEFAULT_AGE_LIMIT=150;

	static const int DEFAULT_FUEL_CAPACITY=1000;
	static const int DEFAULT_FUEL_CONSUMPTION=1;

	static const int DEAFULT_WATER_CAPACITY=4000;
	static const int DEFAULT_WATER_CONSUMPTION=1;

	static const int DEFAULT_SPEED=1;
	static const int DEFAULT_LATITUDE=0, DEFAULT_LONGITUDE=0;
private:
	int _age;
	int _ageLimit;

	int _fuelCapacity;
	int _fuelConsumption;
	int _fuelTank;

	int _waterCapacity;
	int _waterConsumption;
	int _waterTank;

	int _speed;

	int _posLat, _posLong;
	int _destLat, _destLong;

	void moveUpDown();
	void moveLeftRight();
	//����������� �������
	void consumeFuel();

};

