Entry: Source/ComputerPlayer.cpp Source/GameBoard.cpp Source/Entry.cpp Source/GameController.cpp Source/HumanPlayer.cpp Source/Player.cpp 
	g++ Source/ComputerPlayer.cpp Source/GameBoard.cpp Source/Entry.cpp Source/GameController.cpp Source/HumanPlayer.cpp Source/Player.cpp -o Entry
	
SERVERAPP: Source/ServerApp.cpp Source/Server.cpp Source/Client.cpp Source/BasicSocket.cpp Source/ComputerPlayer.cpp Source/GameBoard.cpp Source/GameController.cpp Source/HumanPlayer.cpp Source/Player.cpp 
	g++ Source/ServerApp.cpp Source/Server.cpp Source/Client.cpp Source/BasicSocket.cpp Source/ComputerPlayer.cpp Source/GameBoard.cpp Source/GameController.cpp Source/HumanPlayer.cpp Source/Player.cpp -o SERVERAPP -pthread -L/usr/include/boost -lboost_serialization

CLIENTAPP:Source/ClientApp.cpp Source/Server.cpp Source/Client.cpp Source/BasicSocket.cpp Source/ComputerPlayer.cpp Source/GameBoard.cpp Source/GameController.cpp Source/HumanPlayer.cpp Source/Player.cpp 
	g++ Source/ClientApp.cpp Source/Server.cpp Source/Client.cpp Source/BasicSocket.cpp Source/ComputerPlayer.cpp Source/GameBoard.cpp Source/GameController.cpp Source/HumanPlayer.cpp Source/Player.cpp -o CLIENTAPP -pthread -L/usr/include/boost -lboost_serialization
