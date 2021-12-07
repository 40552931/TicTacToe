#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

struct Move {
	int x;
	int y;

	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar & x;
		ar & y;
	}
};