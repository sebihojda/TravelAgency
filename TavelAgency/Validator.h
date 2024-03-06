#pragma once

#include "Oferta.h"

#include <vector>
#include <string>

using std::vector;
using std::string;
using std::ostream;

class ValidateException {

	vector<string> msgs;

public:
	ValidateException(const vector<string>& errors) : msgs{ errors } {}
	//functie friend (vreau sa folosesc membru privat msg)
	friend ostream& operator<<(ostream& out, const ValidateException& ex);

	string getMesaj() {
		string result;
		for (const auto& msg : msgs) {
			result += msg;
		}
		return result;
	}
};

ostream& operator<<(ostream& out, const ValidateException& ex);

class Validator {
public:
	void validate(const Oferta& of);
};

void testValidator();