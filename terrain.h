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
	//�������������� vector<vector> ��� �� �������������� ����������� ������
	//��� ���������� ��� �� ���� ����� ��������� �� �������
	vector<vector<land>> block;

	int getSize(){return size;};
	int onFire(){return _onFire;};
	//������������ ������� ���� ��������� ��� ��������, �������� ������, ��������� ������ ���.
	void update();
	void spreadFire(land);
	land alert();
	//���� �� �� ������� ��� ����� ������ ����� ��� ��� ���� ��������� ������������
	//��� ��� ��������� ���.
	queue<land> alerts;
	//������� �� �����
	int _onFire;
	//��������� ������
	int _endedFires;
	//��������� ������ �� ��� �������
	void endFire(int _lat, int _long);

private:
	int size;

	
};

