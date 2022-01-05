SRC_DIR :=./Source
SRC_FILES :=$(filter-out ./Source/Entry.cpp, $(wildcard $(SRC_DIR)/*.cpp))
SVR_ENTRY :=./Source/ServerApp.cpp
CLT_ENTRY :=./Source/ClientApp.cpp
VIC_TEST :=./Tests/CheckVictory_Test.cpp

default: packages Server Client
all: packages Server Client VictoryTest

packages:
		[ -d "`/usr/include/boost/ 2>/dev/null`"] && sudo apt install libboost-serialization-dev || echo "Required packages found"
.PHONY: packages

Server: $(SVR_ENTRY)
	g++ $(filter-out ./Source/ClientApp.cpp, $(SRC_FILES)) -o Server -pthread -L/usr/include/boost -lboost_serialization

Client: $(CLT_ENTRY)
	g++ $(filter-out ./Source/ServerApp.cpp, $(SRC_FILES)) -o Client -pthread -L/usr/include/boost -lboost_serialization

VictoryTest: $(VIC_TEST)
	g++ $(filter-out ./Source/ServerApp.cpp ./Source/ClientApp.cpp, $(SRC_FILES) $(VIC_TEST)) -o VictoryTest -pthread -L/usr/include/boost -lboost_serialization

Clean:
	rm -f Server Client
