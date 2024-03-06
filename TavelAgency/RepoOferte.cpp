#include "RepoOferte.h"

#include <assert.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <sstream>

using std::vector;
using std::string;

void FileRepoOferte::loadFromFile() {
	std::ifstream fin(file_name);

	if (!fin.is_open())
		throw RepoException("FileRepoException: Fisierul nu poate fi deschis!\n");

	while (!fin.eof()) {
		string line;
		fin >> line;

		if (fin.eof()) break;

		vector<string> atribute;
		std::stringstream ss(line);

		while (ss.good()) {
			string substr;
			std::getline(ss, substr, ',');
			atribute.push_back(substr);
		}
		Oferta of{ stoi(atribute[0]), atribute[1], atribute[2], atribute[3], stoi(atribute[4]) };
		RepoOferte::addRepo(of);

		atribute.clear();
		line.clear();
	}
	fin.close();
}

void FileRepoOferte::writeToFile() {
	std::ofstream fout(file_name);

	if (!fout.is_open())
		throw RepoException("FileRepoException: Fisierul nu poate fi deschis!\n");

	for (auto& of : getAll())
		fout << of.getId() << "," << of.getDenumire() << "," << of.getDestinatie() << "," << of.getTip() << "," << of.getPret() << "\n";
	fout.close();
}

void test_load_and_write() {
	//RepoOferte rep;
	FileRepoOferte frepo{ "file_repo_test.txt" };
	Oferta of1{ 1,"Paste","Moisei","AllInclusive",400 };
	Oferta of2{ 2,"Paste","Moisei","AllInclusive",400 };
	Oferta of3{ 3,"Paste","Moisei","AllInclusive",400 };
	Oferta of4{ 4,"Paste","Moisei","AllInclusive",400 };
	frepo.addRepo(of1);
	frepo.addRepo(of2);
	frepo.addRepo(of3);
	frepo.addRepo(of4);
	assert(frepo.getAll().size() == 4);
	Oferta of11{ 1,"Paste_mod","Moisei_mod","AllInclusive_mod",400 };
	frepo.modRepo(of11);
	assert(frepo.getAll()[0].getDenumire() == "Paste_mod");
	frepo.dellRepo(1);
	frepo.dellRepo(2);
	frepo.dellRepo(3);
	frepo.dellRepo(4);
	assert(frepo.getAll().size() == 0);
}

void testRepo() {
	RepoOferte rep;
	Oferta of{ 1,"Paste","Moisei","AllInclusive",400 };
	rep.addRepo(of);
	Oferta of1{ 2,"Paste","Moisei","AllInclusive",400 };
	Oferta of2{ 3,"Paste","Moisei","AllInclusive",400 };
	Oferta of3{ 4,"Paste","Moisei","AllInclusive",400 };
	rep.addRepo(of1);
	rep.addRepo(of2);
	rep.addRepo(of3);
	const vector<Oferta>& oferte = rep.getAll();
	//const auto& oferte = rep.getAll();
	assert(oferte.size() == 4);

	try {
		rep.addRepo(of);
		assert(false);
	}
	catch (RepoException& r) {
		assert(true);
		assert(r.getMesaj() == (string)"Oferta existenta!\n");
		//std::cout << r.getMesaj();
	}
	//std::cout << "succes!\n";
}