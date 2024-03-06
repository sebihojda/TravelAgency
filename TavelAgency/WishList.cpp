#include "WishList.h"
#include <assert.h>

void testADD_DELL() {
	RepoOferte rep;
	WishList wl{ rep };
	Oferta of1{ 1, "OfertaPaste", "Moisei", "AllInclusive", 2000 };
	rep.addRepo(of1);
	Oferta of2{ 2, "OfertaCraciun", "Borsa", "Exclusive", 1700 };
	rep.addRepo(of2);
	Oferta of3{ 3, "Oferta1Mai", "Viseu", "5Stars", 1200 };
	rep.addRepo(of3);
	Oferta of4{ 4, "OfertaAugust", "Maramures", "AllInclusive", 1000 };
	rep.addRepo(of4);
	Oferta of5{ 5, "OfertaVara", "Cluj", "Idk", 9999 };
	rep.addRepo(of5);
	wl.add("Oferta1Mai");
	wl.add("OfertaPaste");
	assert(wl.getAllW().size() == 2);
	try {
		wl.add("OfertaCarnaval");
		assert(false);
	}
	catch (WishListException exw) {
		assert(true);
	}
	try {
		wl.add("OfertaPaste");
		assert(false);
	}
	catch (WishListException exw) {
		assert(true);
	}
	assert(wl.getAllW().size() == 2);
	wl.dell();
	assert(wl.getAllW().size() == 0);
}

void test_genereaza() {
	RepoOferte rep;
	WishList wl{ rep };
	Oferta of1{ 1, "OfertaPaste", "Moisei", "AllInclusive", 2000 };
	rep.addRepo(of1);
	Oferta of2{ 2, "OfertaCraciun", "Borsa", "Exclusive", 1700 };
	rep.addRepo(of2);
	Oferta of3{ 3, "Oferta1Mai", "Viseu", "5Stars", 1200 };
	rep.addRepo(of3);
	Oferta of4{ 4, "OfertaAugust", "Maramures", "AllInclusive", 1000 };
	rep.addRepo(of4);
	Oferta of5{ 5, "OfertaVara", "Cluj", "Idk", 9999 };
	rep.addRepo(of5);
	try {
		wl.genereaza(6);
		assert(false);
	}
	catch (WishListException exw) {
		assert(true);
	}
	wl.genereaza(4);
	assert(wl.getAllW().size() == 4);
	/*for (auto oferta : wl.getAllW()) {
		cout << oferta.getId() << " " << oferta.getDenumire() << " " << oferta.getDestinatie() << " " << oferta.getTip() << " " << oferta.getPret() << "\n";
	}*/
	wl.genereaza(5);
	assert(wl.getAllW().size() == 5);
}

void test_export() {
	RepoOferte rep;
	WishList wl{ rep };
	Oferta of1{ 1, "OfertaPaste", "Moisei", "AllInclusive", 2000 };
	rep.addRepo(of1);
	Oferta of2{ 2, "OfertaCraciun", "Borsa", "Exclusive", 1700 };
	rep.addRepo(of2);
	Oferta of3{ 3, "Oferta1Mai", "Viseu", "5Stars", 1200 };
	rep.addRepo(of3);
	Oferta of4{ 4, "OfertaAugust", "Maramures", "AllInclusive", 1000 };
	rep.addRepo(of4);
	Oferta of5{ 5, "OfertaVara", "Cluj", "Idk", 9999 };
	rep.addRepo(of5);
	wl.genereaza(3);
	wl.exportF("file_test.csv");
	try {
		wl.exportF("");
		assert(false);
	}
	catch (WishListException exw) {
		assert(true);
	}
}

void test_raport() {
	RepoOferte rep;
	WishList wl{ rep };
	Oferta of1{ 1, "OfertaPaste", "Moisei", "AllInclusive", 2000 };
	rep.addRepo(of1);
	Oferta of2{ 2, "OfertaCraciun", "Borsa", "Exclusive", 1700 };
	rep.addRepo(of2);
	Oferta of3{ 3, "Oferta1Mai", "Viseu", "5Stars", 1200 };
	rep.addRepo(of3);
	Oferta of4{ 4, "OfertaAugust", "Maramures", "AllInclusive", 1000 };
	rep.addRepo(of4);
	Oferta of5{ 5, "OfertaVara", "Cluj", "Idk", 9999 };
	rep.addRepo(of5);
	Oferta of6{ 6, "OfertaSeptembrie", "Maramures", "AllInclusive", 1500 };
	rep.addRepo(of6);
	wl.genereaza(6);
	assert(wl.raport("AllInclusive", 1500) == 2);
}