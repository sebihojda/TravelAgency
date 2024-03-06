#pragma once

#include <string>
#include <iostream>

using std::string;
using std::cout;

class Oferta
{
private:
	int id;
	string denumire;
	string destinatie;
	string tip;
	int pret;

public:
	Oferta(int id, string den, string des, string tip, int p) : id{ id }, denumire{ den }, destinatie{ des }, tip{ tip }, pret{ p } {}

	Oferta(const Oferta& ot) : id{ ot.id }, denumire{ ot.denumire }, destinatie{ ot.destinatie }, tip{ ot.tip }, pret{ ot.pret } {
		//cout << "!!!!!!!!!!!!!!!!!!!!\n";
	}

	Oferta& operator=(const Oferta& o) {
		id = o.id;
		denumire = o.denumire;
		destinatie = o.destinatie;
		tip = o.tip;
		pret = o.pret;
		return *this;
	}

	int getId() const {
		return id;
	}
	string getDenumire() const {
		return denumire;
	}
	string getDestinatie() const {
		return destinatie;
	}
	string getTip() const {
		return tip;
	}
	int getPret() const {
		return pret;
	}

};

void testOferta();
