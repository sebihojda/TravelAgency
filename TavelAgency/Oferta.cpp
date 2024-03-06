#include "Oferta.h"

#include <assert.h>

#include <iostream>
using std::cout;

void testOferta() {
	Oferta of{ 1,"Paste","Moisei","AllInclusive",400 };
	assert(of.getId() == 1);
	assert(of.getDenumire() == "Paste");
	assert(of.getDestinatie() == "Moisei");
	assert(of.getTip() == "AllInclusive");
	assert(of.getPret() == 400);
	Oferta of2{ 1,"Craciun","Borsa","AllInclusive",1000 };
	of = of2;
	Oferta o3 = of;
	assert(of.getId() == 1);
	assert(of.getDenumire() == "Craciun");
	assert(of.getDestinatie() == "Borsa");
	assert(of.getTip() == "AllInclusive");
	assert(of.getPret() == 1000);
	//cout << "succes!\n";
}
