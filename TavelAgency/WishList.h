#pragma once

#include "Oferta.h"
#include "RepoOferte.h"

#include <algorithm>
#include <string>
#include <random>

#include <iostream>
#include <fstream>

#include "observer.h"

class WishListException {
	string msg;

public:
	WishListException(string m) : msg{ m } {};

	string getMesaj() {
		return msg;
	}
};


class WishList: public Observable{
private:
	vector<Oferta> wishlist;
	RepoOferte& repo;

public:
	WishList(RepoOferte& rep) : repo{ rep } {}

	WishList(const WishList& ot) = delete;

	void add(string den) {
		auto& all = repo.getAll();
		auto rez = std::find_if(all.begin(), all.end(), [den](const Oferta& of) {
			return of.getDenumire() == den;
			});
		if (rez != all.end()) {
			auto& allW = getAllW();
			auto rezW = std::find_if(allW.begin(), allW.end(), [den](const Oferta& of) {
				return of.getDenumire() == den;
				});
			if (rezW == allW.end()) {
				wishlist.push_back(*rez);
			}
			else
				throw WishListException("Denumire existenta in WishList\n");
		}
		else
			throw WishListException("Denumire inexistenta in Repo!\n");
		notify();
	}

	void dell() {
		wishlist.clear();
		notify();
	}

	void genereaza(int total) {
		auto nr = repo.getAll().size();
		if (nr < total)
			throw WishListException("Numar oferte insuficient!\n");
		else if (nr == total) {
			wishlist.clear();
			for (auto& oferta : repo.getAll())
				add(oferta.getDenumire());
		}
		else {
			wishlist.clear();
			auto& allr = repo.getAll();
			while (total) {
				std::mt19937 mt{ std::random_device{}() };
				std::uniform_int_distribution<> dist(0, allr.size() - 1);
				int rndNr = dist(mt);// numar aleator intre [0,size-1] 
				try {
					add(allr[rndNr].getDenumire());
					total--;
				}
				catch (WishListException exw) {
					continue;
				}
			}
		}
		notify();
	}

	void exportF(string nume) {
		std::ofstream fout(nume);
		if (!fout.is_open())
			throw WishListException("The file could not be opened!\n");

		for (auto& oferta : getAllW())
			fout << oferta.getId() << "," << oferta.getDenumire() << "," << oferta.getDestinatie() << "," << oferta.getTip() << "," << oferta.getPret() << "\n";

		fout.close();

	}

	auto raport(string tip, int pret) {
		//cat la suta din oferte sunt de un anumit tip (de ex.: AllInclusive)
		//si au pretul mai mic de un anumit pret (de ex.: 1500 lei)
		auto rez = std::count_if(getAllW().begin(), getAllW().end(), [tip, pret](const Oferta& of) {
			return of.getTip() == tip && of.getPret() <= pret;
			});
		return rez;
	}

	const vector<Oferta>& getAllW() {
		return wishlist;
	}

};


void testADD_DELL();

void test_genereaza();

void test_export();

void test_raport();