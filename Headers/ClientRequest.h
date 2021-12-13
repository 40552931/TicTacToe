#pragma once

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include "../Headers/SerializeTuple.h"

#include <string>
#include <iostream>
#include <tuple>


class ClientRequest {
public:
	friend class boost::serialization::access;

	int markerChoice; // for marker selection
	std::string message; // Sent with all requests
	std::tuple<int, int> position; // Move request
	template<class Archive>
	void serialize(Archive& serializationArchive, const unsigned int version) {
		serializationArchive & markerChoice;
		serializationArchive & message;
		serializationArchive & position;
	}

	ClientRequest() { };

	// Move request overload
	ClientRequest(std::string message, std::tuple<int, int> position) {
		this->message = message;
		this->position = position;
	}

	// Begin game request & check for winner overload
	ClientRequest(std::string message) {
		this->message = message;
	}

	// Marker choice request overload
	ClientRequest(std::string message, int markerChoice) {
		this->message = message;
		this->markerChoice = markerChoice;
	}
};