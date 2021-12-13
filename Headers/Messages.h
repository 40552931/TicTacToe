#pragma once

namespace Response {
	const std::string BEGIN_GAME = "BEGIN_GAME_RESPONSE";
	const std::string MARKER_CHOICE = "MARKER_CHOICE_RESPONSE";
	const std::string MOVE = "MOVE_RESPONSE";
	const std::string WINNER_DETECTED = "WINNER_DETECTED";
}

namespace Request {
	const std::string BEGIN_GAME = "BEGIN_GAME_REQUEST";
	const std::string MARKER_CHOICE = "MARKER_CHOICE_REQUEST";
	const std::string MOVE = "MOVE_REQUEST";
}