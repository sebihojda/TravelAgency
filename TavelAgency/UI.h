#pragma once
#include "ServiceOferte.h"
#include "WishList.h"

class UI
{
private:

	ServiceOferte& serv;

	WishList& wl;

	void addUI();

	void printUI(const vector<Oferta>& oferte);

	void modUI();

	void delUI();

	void filUI();

	void sortUI();

	void addWish();

	void dellWish();

	void genereazaWish();

	void exportWish();

	void printWish();

	void raportWish();

	void undo();
public:

	UI(ServiceOferte& ser, WishList& w) : serv{ ser }, wl{ w } {}

	UI(const ServiceOferte& ot) = delete;

	void startUI();

};

