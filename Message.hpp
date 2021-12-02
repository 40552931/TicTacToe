#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>


class Message {
public:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version) {
		ar & contents;
	}
	string contents;
	Message(){};
	Message(string _contents) : contents(_contents) {}
};