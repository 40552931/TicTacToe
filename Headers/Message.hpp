#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include <string>
#include <iostream>

class Message {
public:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version) {
		ar & contents;
	}
	std::string contents;
	Message(){};
	Message(std::string _contents) : contents(_contents) {}
};
