#include "Validator.h"

#include <assert.h>
#include <sstream>

void Validator::validate(const Oferta& of) {
	vector<string> msgs;
	if (of.getId() <= 0) msgs.push_back("Id negativ sau nul!\n");
	if (of.getDenumire() == "") msgs.push_back("Denumire vida!\n");
	if (of.getDestinatie() == "") msgs.push_back("Destinatie vida!\n");
	if (of.getTip() == "") msgs.push_back("Tip vid!\n");
	if (of.getPret() <= 0) msgs.push_back("Pret negativ sau nul!\n");
	if (msgs.size() > 0) {
		throw ValidateException(msgs);
	}
}

ostream& operator<<(ostream& out, const ValidateException& ex) {
	for (const auto& msg : ex.msgs) {
		out << msg << " ";
	}
	return out;
}

void testValidator() {
	Validator v;
	Oferta of{ 0,"","","",-100 };
	try {
		v.validate(of);
	}
	catch (const ValidateException& ex) {
		std::stringstream sout;
		sout << ex;
		const auto mesaj = sout.str();
		assert(mesaj.find("negativ") >= 0);
		assert(mesaj.find("vid") >= 0);
	}
}
