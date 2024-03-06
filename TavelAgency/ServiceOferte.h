#pragma once
#include "Oferta.h"
#include "Validator.h"
#include "RepoOferte.h"
#include "Undo.h"

#include <algorithm>
#include <functional>
#include <string>
#include <vector>

using std::function;
using std::string;
using std::vector;

using namespace std;

class ServiceException {
	string msg;

public:
	ServiceException(string m) : msg{ m } {}

	string getMesaj() {
		return msg;
	}
};

class ServiceOferte
{
private:
	RepoOferte& repo;
	Validator& val;

	std::vector<unique_ptr<ActiuneUndo>> undoActions;

public:
	ServiceOferte(RepoOferte& rep, Validator& val) : repo{ rep }, val{ val } {}

	ServiceOferte(const ServiceOferte& ot) = delete;

	ServiceOferte() = default;

	void addService(int id, string den, string des, string tip, int p) {
		Oferta of{ id, den, des, tip, p };
		val.validate(of);
		repo.addRepo(of);
		undoActions.push_back(std::make_unique<UndoAdauga>(of, repo));
	}

	void dellService(int id) {
		auto rez = std::find_if(getAll().begin(), getAll().end(), [id](const Oferta& oferta) {
			return oferta.getId() == id;
			});
		if (rez != getAll().end()) {
			Oferta of_undo{ (*rez).getId(), (*rez).getDenumire(), (*rez).getDestinatie(), (*rez).getTip(), (*rez).getPret() };
			undoActions.push_back(std::make_unique<UndoSterge>(of_undo, repo));
		}
		repo.dellRepo(id);
	}

	void modService(int id, string den, string des, string tip, int p) {
		Oferta of{ id, den, des, tip, p };
		val.validate(of);
		auto rez = std::find_if(getAll().begin(), getAll().end(), [id](const Oferta& oferta) {
			return oferta.getId() == id;
			});
		if (rez != getAll().end())
		{
			Oferta of_undo{ (*rez).getId(), (*rez).getDenumire(), (*rez).getDestinatie(), (*rez).getTip(), (*rez).getPret() };
			undoActions.push_back(std::make_unique<UndoModifica>(of_undo, repo));
		}
		repo.modRepo(of);
	}

	void undo() {
		if (undoActions.empty())
			throw ServiceException("Nu mai exista operatii!\n");

		undoActions.back()->doUndo();
		undoActions.pop_back();
	}

	const vector<Oferta>& getAll() {
		return repo.getAll();
	}

	const vector<Oferta> filtrare_destinatie(string den) {
		vector<Oferta> rezultat;
		auto rez = std::copy_if(repo.getAll().begin(), repo.getAll().end(), std::back_inserter(rezultat), [den](const Oferta& of) {return of.getDestinatie() == den;});
		return rezultat;
	}

	const vector<Oferta> filtrare_pret1(int pret) {
		vector<Oferta> rezultat;
		auto rez = std::copy_if(repo.getAll().begin(), repo.getAll().end(), std::back_inserter(rezultat), [pret](const Oferta& of) {return of.getPret() <= pret;});
		return rezultat;
	}

	const vector<Oferta> filtrare_pret2(int pret) {
		vector<Oferta> rezultat;
		auto rez = std::copy_if(repo.getAll().begin(), repo.getAll().end(), std::back_inserter(rezultat), [pret](const Oferta& of) {return of.getPret() >= pret;});
		return rezultat;
	}

	vector<Oferta> sortareDes() {
		vector<Oferta> rezultat = repo.getAll();
		std::sort(rezultat.begin(), rezultat.end(), [](const Oferta& of1, const Oferta& of2) {
			return of1.getDestinatie() < of2.getDestinatie();
			});
		return rezultat;
	}

	vector<Oferta> sortareDen() {
		vector<Oferta> rezultat = repo.getAll();
		std::sort(rezultat.begin(), rezultat.end(), [](const Oferta& of1, const Oferta& of2) {
			return of1.getDenumire() < of2.getDenumire();
			});
		return rezultat;
	}

	vector<Oferta> sortareTipPret() {
		vector<Oferta> rezultat = repo.getAll();
		std::sort(rezultat.begin(), rezultat.end(), [](const Oferta& of1, const Oferta& of2) {
			return (of1.getTip() == of2.getTip() ? of1.getPret() < of2.getPret() : of1.getTip() < of2.getTip());
			});
		return rezultat;
	}

};

void testAdd();

void testDell();

void testMod();

void testFil();

void testSort();

void testUndo();