#pragma once
class land
{
public:public:
	land(void);
	land(int,int);
	~land(void);

	int getState();
	int _lat(){return _latitude;};
	int _long(){return _longitude;};

	void _setLat(int x){_latitude = x;};
	void _setLong(int y){_longitude = y;};
	
	//'εναρξη φωτιάς
	int startFire();
	//σβήσιμο φωτιάς
	int endFire();
	//επιστρέφει τον χρόνο που καίγεται ένα σημείο, χρησιμοποιείται για την 
	//επέκταση της φωτιάς
	int getTimeOnFire(){return timeOnFire;};

	//ενημερώνει την κατάσταση του σημείου. Η ενημέρωση γίνεται με πιθανότητες που ορίζονται
	//static και είναι κοινές για όλα τα σημεία.
	int update();

	static const int NORMAL=0, ON_FIRE=1;
	static const int DEFAULT_LAT=-1, DEFAULT_LONG=-1;
	static const int FIRE_SPAWN_PROB=2;
	static const int FIRE_SPAWN_PROB_MAX=100000;
	static const int PROPAGATE_FIRE_TIME = 1000;

private:

	int state;
	int timeOnFire;
	int _latitude, _longitude;

};

