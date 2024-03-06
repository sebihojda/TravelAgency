#pragma once

#include "Oferta.h"

#include <algorithm>
#include <vector>
#include <string>

using std::vector;
using std::string;

class RepoException {

	string msg;

public:
	RepoException(string m) : msg{ m } {}

	string getMesaj() {
		return msg;
	}
};

class RepoOferte
{
private:

	vector<Oferta> oferte;

public:

	RepoOferte() = default;

	RepoOferte(const RepoOferte& ot) = delete;

	virtual ~RepoOferte() = default;

	virtual void addRepo(const Oferta& of) {
		auto rez = std::find_if(oferte.begin(), oferte.end(), [&](const Oferta& oferta) {
			return of.getId() == oferta.getId();
			});
		if (rez != oferte.end())
			throw RepoException("Oferta existenta!\n");
		else
			oferte.push_back(of);
	}

	virtual void dellRepo(int id) {
		auto rez = std::find_if(oferte.begin(), oferte.end(), [id](const Oferta& oferta) {
			return oferta.getId() == id;
			});
		if (rez != oferte.end())
			oferte.erase(rez);
		else
			throw RepoException("Oferta inexistenta!\n");
	}

	virtual void modRepo(const Oferta& of) {
		auto rez = std::find_if(oferte.begin(), oferte.end(), [&](const Oferta& oferta) {
			return of.getId() == oferta.getId();
			});
		if (rez != oferte.end())
			std::replace_if(oferte.begin(), oferte.end(), [&](const Oferta& oferta) {
			return of.getId() == oferta.getId();
				}, of);
		else
			throw RepoException("Oferta inexistenta!\n");
	}

	const vector<Oferta>& getAll() {
		return oferte;
	}

};

void testRepo();

#include <fstream>

class FileRepoOferte : public RepoOferte {
private:
	string file_name;
	void loadFromFile();
	void writeToFile();
public:
	FileRepoOferte(const string fn) : RepoOferte(), file_name{ fn } {
		loadFromFile();
	}

	void addRepo(const Oferta& of) override {
		RepoOferte::addRepo(of);
		writeToFile();
	}

	void dellRepo(int id) override {
		RepoOferte::dellRepo(id);
		writeToFile();
	}

	void modRepo(const Oferta& of) override {
		RepoOferte::modRepo(of);
		writeToFile();
	}

};

void test_load_and_write();