SRC_DIR :=./Source
SRC_FILES := $(filter-out ./Source/Entry.cpp, $(wildcard $(SRC_DIR)/*.cpp))
SVR_ENTRY :=./Source/ServerApp.cpp
CLT_ENTRY :=./Source/ClientApp.cpp

default: Server Client
all: Server Client

Server: $(SVR_ENTRY)
	g++ $(filter-out ./Source/ClientApp.cpp, $(SRC_FILES)) -o Server -pthread -L/usr/include/boost -lboost_serialization

Client: $(CLT_ENTRY)
	g++ $(filter-out ./Source/ServerApp.cpp, $(SRC_FILES)) -o Client -pthread -L/usr/include/boost -lboost_serialization

Clean:
	rm -f Server Client