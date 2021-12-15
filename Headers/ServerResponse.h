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
	friend class boost::serialization::access;

	std::string message; // Sent with all responses
	std::string printableGameBoard;  // Sent with marker choice, move ok, begin game responses
	int responseCode; // Sent with all responses
	int winner; // Sent with check for winner request
	int currentTurnPlayerMarker; // Sent with move ok responses
	int tossWin;
	template<class Archive>
	void serialize(Archive& serializationArchive, const unsigned int version) {
		serializationArchive & message;
		serializationArchive & printableGameBoard;
		serializationArchive & responseCode;
		serializationArchive & winner;
		serializationArchive & currentTurnPlayerMarker;
		serializationArchive & tossWin;
	}

	// Empty constructor
	ServerResponse() { };

	// Marker choice response overload
	ServerResponse(int responseCode, std::string message, std::string printableGameBoard, int currentTurnPlayerMarker, int tossWin) {
		this->responseCode = responseCode;
		this->message = message;
		this->printableGameBoard = printableGameBoard;
		this->currentTurnPlayerMarker = currentTurnPlayerMarker;
		this->tossWin = tossWin;
	}

	// Move response overload
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