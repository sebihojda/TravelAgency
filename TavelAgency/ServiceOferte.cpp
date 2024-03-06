#include "ServiceOferte.h"

#include <assert.h>
#include <iostream>

using std::cout;

void testAdd() {
	RepoOferte rep;
	Validator val;
	ServiceOferte serv{ rep , val };
	serv.addService(1, "OfertaPaste", "Moisei", "AllInclusive", 400);
	const auto& oferte = serv.getAll();
	assert(oferte.size() == 1);
	//cout << "succes!\n";
}

void testDell() {
	RepoOferte rep;
	Validator val;
	ServiceOferte serv{ rep , val };
	serv.addService(1, "OfertaPaste", "Moisei", "AllInclusive", 400);
	const auto& oferte = serv.getAll();
	assert(oferte.size() == 1);
	serv.dellService(1);
	assert(oferte.size() == 0);
	try {
		serv.dellService(1);
		assert(false);
	}
	catch (RepoException r) {
		assert(true);
	}
}

void testMod() {
	RepoOferte rep;
	Validator val;
	ServiceOferte serv{ rep , val };
	serv.addService(1, "OfertaPaste", "Moisei", "AllInclusive", 400);
	const auto& oferte = serv.getAll();
	assert(oferte.size() == 1);
	serv.modService(1, "den", "des", "tip", 1000);
	assert(oferte[0].getDenumire() == "den");
	assert(oferte[0].getDestinatie() == "des");
	assert(oferte[0].getTip() == "tip");
	assert(oferte[0].getPret() == 1000);
	try {
		serv.modService(2, "den", "des", "tip", 1000);
		assert(false);
	}
	catch (RepoException r) {
		assert(true);
	}
}

void testFil() {
	RepoOferte rep;
	Validator val;
	ServiceOferte serv{ rep , val };
	serv.addService(1, "OfertaPaste", "Moisei", "AllInclusive", 400);
	serv.addService(2, "OfertaPaste", "Viseu", "AllInclusive", 1000);
	serv.addService(3, "OfertaPaste", "Moisei", "Inclusive", 1000);
	serv.addService(4, "OfertaPaste", "Borsa", "AllInclusive", 400);
	const auto& oferte_filtrate1 = serv.filtrare_destinatie("Moisei");
	assert(oferte_filtrate1.size() == 2);
	const auto& oferte_filtrate2 = serv.filtrare_pret1(500);
	assert(oferte_filtrate2.size() == 2);
	const auto& oferte_filtrate3 = serv.filtrare_pret2(500);
	assert(oferte_filtrate3.size() == 2);
	//cout << "Succes!";
}

void testSort() {
	RepoOferte rep;
	Validator val;
	ServiceOferte serv{ rep , val };
	serv.addService(1, "OfertaPaste", "Moisei", "AllInclusive", 2000);
	serv.addService(2, "OfertaCraciun", "Borsa", "Exclusive", 1700);
	serv.addService(3, "Oferta1Mai", "Viseu", "5Stars", 1200);
	serv.addService(4, "OfertaAugust", "Maramures", "AllInclusive", 1000);
	serv.addService(5, "OfertaVara", "Cluj", "Idk", 9999);
	const auto oferte_sortate1 = serv.sortareDen();
	assert(oferte_sortate1[0].getDenumire() == "Oferta1Mai");
	const auto oferte_sortate2 = serv.sortareDes();
	assert(oferte_sortate2[0].getDestinatie() == "Borsa");
	const auto oferte_sortate3 = serv.sortareTipPret();
	assert(oferte_sortate3[0].getTip() == "5Stars");
	assert(oferte_sortate3[0].getPret() == 1200);
	//cout << "Succes!";
}


void testUndo() {
	RepoOferte rep;
	Validator val;
	ServiceOferte serv{ rep , val };
	serv.addService(1, "OfertaPaste", "Moisei", "AllInclusive", 2000);
	serv.addService(2, "OfertaCraciun", "Borsa", "Exclusive", 1700);
	serv.addService(3, "Oferta1Mai", "Viseu", "5Stars", 1200);
	serv.addService(4, "OfertaAugust", "Maramures", "AllInclusive", 1000);
	serv.addService(5, "OfertaVara", "Cluj", "Idk", 9999);
	serv.undo();
	assert(serv.getAll().size() == 4);
	serv.dellService(4);
	serv.undo();
	assert(serv.getAll().size() == 4);
	serv.modService(2, "OfertaCraciun_mod", "Borsa_mod", "Exclusive_mod", 1701);
	serv.undo();
	assert(serv.getAll()[1].getPret() == 1700);
}