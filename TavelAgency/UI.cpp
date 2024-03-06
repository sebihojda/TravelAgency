#include "UI.h"

#include <iostream>
using std::cin;
using std::cout;


void UI::addUI() {
	int id;
	cout << "Id:";
	cin >> id;
	string den;
	cout << "Denumire:";
	cin >> den;
	string des;
	cout << "Destinatie:";
	cin >> des;
	string tip;
	cout << "Tip:";
	cin >> tip;
	int p;
	cout << "Pret:";
	cin >> p;
	serv.addService(id, den, des, tip, p);
	cout << "Oferta adaugata!\n";
}

void UI::printUI(const vector<Oferta>& oferte) {
	if (oferte.size() == 0) {
		cout << "Nu exista oferte in aplicatie!\n";
	}
	else {
		cout << "---------------------------------------\n";
		cout << "Ofertele sunt:\n";
		for (const auto& oferta : oferte) {
			cout << oferta.getId() << " " << oferta.getDenumire() << " " << oferta.getDestinatie() << " " << oferta.getTip() << " " << oferta.getPret() << "\n";
		}
		cout << "---------------------------------------\n";
	}
}

void UI::delUI() {
	int id;
	cout << "Id:";
	cin >> id;
	serv.dellService(id);
	cout << "Oferta stearsa!\n";
}

void UI::modUI() {
	cout << "Alegeti oferta:\n";
	int id;
	cout << "Id:";
	cin >> id;
	cout << "Alegeti campurile:\n";
	string den;
	cout << "Denumire:";
	cin >> den;
	string des;
	cout << "Destinatie:";
	cin >> des;
	string tip;
	cout << "Tip:";
	cin >> tip;
	int p;
	cout << "Pret:";
	cin >> p;
	serv.modService(id, den, des, tip, p);
	cout << "Oferta modificata!\n";
}

void UI::filUI() {
	cout << "Alegeti filtrul:\n";
	int x;
	cout << "1. Destinatie;\n";
	cout << "2. Pret\n";
	cin >> x;
	if (x == 1) {
		cout << "Introduceti destinatia dorita:\n";
		string den;
		cin >> den;
		printUI(serv.filtrare_destinatie(den));
	}
	else if (x == 2) {
		cout << "Introduceti pretul dorit:\n";
		int pret;
		cin >> pret;
		cout << "Introduceti modul dorit:(<=/>=)\n";
		string s;
		cin >> s;
		if (s == "<=")
			printUI(serv.filtrare_pret1(pret));
		else if (s == ">=")
			printUI(serv.filtrare_pret2(pret));
		else
			cout << "Mod filtrare pret invalid!\n";
	}
	else {
		cout << "Optiune filtrare invalida!\n";
	}
}

void UI::sortUI() {
	cout << "Alegeti sortarea:\n";
	int x;
	cout << "1. Destinatie\n";
	cout << "2. Denumire\n";
	cout << "3. Tip&Pret\n";
	cin >> x;
	if (x == 1)
		printUI(serv.sortareDes());
	else if (x == 2)
		printUI(serv.sortareDen());
	else if (x == 3)
		printUI(serv.sortareTipPret());
	else
		cout << "Optiune sortare invalida!\n";
}

void UI::addWish() {
	cout << "Introduceti denumirea ofertei:\n";
	string den;
	cin >> den;
	wl.add(den);
	printWish();
}

void UI::dellWish() {
	wl.dell();
	printWish();
}

void UI::genereazaWish() {
	cout << "Introduceti numarul de oferte dorite:\n";
	int nr;
	cin >> nr;
	wl.genereaza(nr);
	printWish();
}

void UI::exportWish() {
	cout << "Introduceti numele fisierului exportat:\n";
	string nume_fisier;
	cin >> nume_fisier;
	wl.exportF(nume_fisier);
}

void UI::printWish() {
	if (wl.getAllW().size() == 0)
		cout << "Nu exista oferte in WishList!\n";
	else {
		cout << "WishListul contine:\n";
		printUI(wl.getAllW());
	}
}

void UI::raportWish() {
	cout << "Alegeti tipul ofertei:\n";
	string tip;
	cin >> tip;
	cout << "Alegeti pretul ofertei:\n";
	int pret;
	cin >> pret;
	double nr = wl.raport(tip, pret);
	double procent = nr * 100 / wl.getAllW().size();
	cout << "Procentul ofertelor de tipul " << tip << " care costa mai putin de " << pret << " lei, este " << procent << "%.\n";
}

void UI::undo() {
	serv.undo();
}

void UI::startUI() {
	while (true) {
		cout << "1. Add\n2. Modifica\n3. Sterge\n4. Print\n5. Filtrare\n6. Sortare\n7. WishList\n8. Undo\n0. Exit\nComanda:";
		int cmd = 0;
		cin >> cmd;
		try {
			if (cmd == 0) {
				break;
			}
			else if (cmd == 1) {
				addUI();
			}
			else if (cmd == 2) {
				modUI();
			}
			else if (cmd == 3) {
				delUI();
			}
			else if (cmd == 4) {
				printUI(serv.getAll());
			}
			else if (cmd == 5) {
				filUI();
			}
			else if (cmd == 6) {
				sortUI();
			}
			else if (cmd == 777) {
				serv.addService(1, "OfertaPaste", "Moisei", "AllInclusive", 2000);
				serv.addService(2, "OfertaCraciun", "Borsa", "Exclusive", 1700);
				serv.addService(3, "Oferta1Mai", "Viseu", "5Stars", 1200);
				serv.addService(4, "OfertaAugust", "Maramures", "AllInclusive", 1000);
				serv.addService(5, "OfertaVara", "Cluj", "Idk", 9999);
			}
			else if (cmd == 7) {
				cout << "1. Adauga WishList\n2. Goleste WishList\n3. Genereaza WishList\n4. Exporta WishList\n5. Print\n6. Raport\n";
				int cmd_w;
				cin >> cmd_w;
				try {
					if (cmd_w == 1)
						addWish();
					else if (cmd_w == 2)
						dellWish();
					else if (cmd_w == 3)
						genereazaWish();
					else if (cmd_w == 4)
						exportWish();
					else if (cmd_w == 5)
						printWish();
					else if (cmd_w == 6)
						raportWish();
					else
						cout << "Comanda inexistenta!\n";
				}
				catch (WishListException& w) {
					cout << w.getMesaj();
				}
			}
			else if (cmd == 8) {
				undo();
			}
			else {
				cout << "Comanda inexistenta!\n";
			}
		}
		catch (RepoException& r) {
			cout << r.getMesaj();
		}
		catch (const ValidateException& e) {
			cout << e << "\n";
		}
		catch (ServiceException& s) {
			cout << s.getMesaj();
		}
		cout << "Numarul ofertelor din WishList este: " << wl.getAllW().size() << "\n";
	}
}