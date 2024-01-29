// ***********************************************************************
//
//								 ZPG
// 
//						JAN KARKOŠKA - (KAR0229)
//
// ***********************************************************************

#include "Subject.h"

void Subject::attach(Observer* observer)
{
	this->vector_observers.push_back(observer);
}

void Subject::dettach(Observer* observer)
{
	std::remove(vector_observers.begin(), vector_observers.end(), observer);
}

void Subject::notifyObservers(void* camera, std::string choose)
{
	for (Observer* observer : vector_observers) {
		observer->notify(camera, choose);
	}
}

