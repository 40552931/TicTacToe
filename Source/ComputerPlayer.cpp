#include "../Headers/ComputerPlayer.h"

#include <iostream>

using namespace std;

Move ComputerPlayer::getMove(GameBoard& board, int player, int depth) {
	/**
	 * minimax algorithm implementation to find the best move
	 *
	 * creates a tree of all possible moves the computer can take
	 * from a given position. It does this by calling itself 
	 * recursively until there are no more possible
	 * moves to make. The best move to take is calculated
	 * based on a "rating" given to each move.
	*/
	int previousGameWinner = board.checkVictory();
	if (previousGameWinner == getMarker()) // is this computerplayer.marker?
		return Move(10 - depth); // return good score, AI won
	else if (previousGameWinner == getOtherPlayerMarker())
		return Move(depth - 10); // return bad score, AI lost
	else if (previousGameWinner == TIE_INDICATOR)
		return Move(0);
	depth++;
	std::vector<Move> takenMoves;
	for (int y = 0; y < BOARD_SIZE; y++)
	{
		for (int x = 0; x < BOARD_SIZE; x++)
		{
			if (board.getValueAtPosition(x, y) == BLANK) {
				Move move(x, y);
				board.setValueAtPosition(x, y, player);
				// player = otherplayer (human) if player is ai, otherwise ai player
				move.moveRating = getMove(board, player == getMarker() ? getOtherPlayerMarker() : getMarker(), depth).moveRating;
				takenMoves.push_back(move);
				board.setValueAtPosition(x, y, BLANK); // remove the marker from pos
			}
		}
	}

	int bestMoveIndex = 0; // index of the best move in takenMoves vector
	if (player == getMarker()) { // player is ai
		int bestScore = -1000; // low value, easily beatable
		for (int i = 0; i < takenMoves.size(); i++)
		{
			// If the move in question is better than the current best, update
			// bestMove and bestScore variables.
			if (takenMoves[i].moveRating > bestScore) {
				bestMoveIndex = i;
				bestScore = takenMoves[i].moveRating;
			}
		}
	}
	else { // human player
		int bestScore = 1000; // make hardest for the player
		for (int i = 0; i < takenMoves.size(); i++)
		{
			if (takenMoves[i].moveRating < bestScore) {
				bestMoveIndex = i;
				bestScore = takenMoves[i].moveRating;
			}
		}
	}
	return takenMoves[bestMoveIndex];
}

void ComputerPlayer::performMove(GameBoard& board) {
	Move bestPossibleMove = getMove(board, getMarker());
	board.computerMoves.push_back(bestPossibleMove);
	int x, y;
	std::tie(x, y) = bestPossibleMove.position;
	board.setValueAtPosition(x, y, getMarker());
}

void ComputerPlayer::initialize(int aiPlayerMarker) {
	setMarkers(aiPlayerMarker);
	setName("Computer");
}
