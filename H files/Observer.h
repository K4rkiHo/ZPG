// ***********************************************************************
//
//								 ZPG
// 
//						JAN KARKOŠKA - (KAR0229)
//
// ***********************************************************************

#pragma once

#include <iostream>

class Observer {
public:
	//virtual void notify(void * camera) = 0;
	virtual void notify(void* camera, std::string choose) = 0;
};