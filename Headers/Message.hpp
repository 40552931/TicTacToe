#pragma once

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include "../Headers/SerializeTuple.h"

#include <string>
#include <iostream>
#include <tuple>
#include <vector>

struct Move {
	Move() {}
	Move(int moveRating) : moveRating(moveRating) {}
	Move(int x, int y) : position(x, y) {}
	std::tuple<int, int> position;
	int moveRating;
};

class ServerResponse {
public:
	std::vector<int> board;
	std::string message;
	int winner;
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar & board;
		ar & message;
	}
	ServerResponse() {};
	ServerResponse(std::string _message) { message = _message; }
	ServerResponse(std::string _message, std::vector<int> _board) {
		board = _board;
		message = _message;
	}
	ServerResponse(std::string _message, int _winner) {
		winner = _winner;
		message = _message;
	}
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