#pragma once

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include "../Headers/SerializeTuple.h"

#include <string>
#include <iostream>
#include <tuple>

struct Move {
	Move() {}
	Move(int moveRating) : moveRating(moveRating) {}
	Move(int x, int y) : position(x, y) {}
	std::tuple<int, int> position;
	int moveRating;
};

class SendableObject {
public:
	std::tuple<int, int> position;
	std::string indicator;
	int markerChoice;
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar & position;
		ar & markerChoice;
		ar & indicator;
	}
	SendableObject() {}; // empty constructor
	SendableObject(std::string _indicator, int x, int y) { 
		position = std::make_tuple(x, y); 
		indicator = _indicator;
	}
	SendableObject(std::string _indicator, int _markerChoice) { 
		markerChoice = _markerChoice; 
		indicator = _indicator;
	}
	SendableObject(int x, int y) {position = std::make_tuple(x,y);}
};