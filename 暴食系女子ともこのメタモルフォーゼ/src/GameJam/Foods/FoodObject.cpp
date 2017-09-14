#include "FoodObject.hpp"

FoodObject::FoodObject(){

}

FoodObject::~FoodObject(){

}

void FoodObject::AddGauge(const int _add, int *_gauge){
	_gauge += _add;
}