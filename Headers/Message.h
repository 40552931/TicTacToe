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

class ServerResponse {
public:
	friend class boost::serialization::access;

	std::string message; // Sent with all responses
	std::string printableGameBoard;  // Sent with marker choice, move ok, begin game responses
	int responseCode; // Sent with all responses
	int winner; // Sent with check for winner request
	int currentTurnPlayerMarker; // Sent with move ok responses
	template<class Archive>
	void serialize(Archive& serializationArchive, const unsigned int version) {
		serializationArchive & message;
		serializationArchive & printableGameBoard;
		serializationArchive & responseCode;
		serializationArchive & winner;
		serializationArchive & currentTurnPlayerMarker;
	}

	// Empty constructor
	ServerResponse() { };

	// Marker choice & move response overload
	ServerResponse(int responseCode, std::string message, std::string printableGameBoard, int currentTurnPlayerMarker) {
		this->responseCode = responseCode;
		this->message = message;
		this->printableGameBoard = printableGameBoard;
		this->currentTurnPlayerMarker = currentTurnPlayerMarker;
	}

	// Begin game overload
	ServerResponse(int responseCode, std::string message) {
		this->responseCode = responseCode;
		this->message = message;
		this->printableGameBoard = printableGameBoard;
	}

	// Check for winner response overload
	ServerResponse(int responseCode, std::string message, int winner, std::string printableGameBoard) {
		this->responseCode = responseCode;
		this->message = message;
		this->winner = winner;
		this->printableGameBoard = printableGameBoard;
	}
};