#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include "../Headers/SerializeTuple.h"

#include <string>
#include <iostream>
#include <tuple>

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
		std::make_tuple(x, y); 
		indicator = _indicator;
	}
	SendableObject(std::string _indicator, int _markerChoice) { 
		markerChoice = _markerChoice; 
		indicator = _indicator;
	}
};