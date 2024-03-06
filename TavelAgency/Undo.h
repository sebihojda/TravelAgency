#pragma once
#include "Oferta.h"
#include "RepoOferte.h"

class ActiuneUndo
{
public:
	virtual void doUndo() = 0;
	virtual ~ActiuneUndo() = default;

};

class UndoAdauga : public ActiuneUndo {
	Oferta OfertaAdaugata;
	RepoOferte& repo;
public:
	UndoAdauga(const Oferta& of, RepoOferte& rep) : repo{ rep }, OfertaAdaugata{ of } {};

	void doUndo() override {
		repo.dellRepo(OfertaAdaugata.getId());
	}
};

class UndoSterge : public ActiuneUndo {
	Oferta OfertaStearsa;
	RepoOferte& repo;
public:
	UndoSterge(const Oferta& of, RepoOferte& rep) : repo{ rep }, OfertaStearsa{ of } {};

	void doUndo() override {
		repo.addRepo(OfertaStearsa);
	}
};

class UndoModifica : public ActiuneUndo {
	Oferta OfertaModificata;
	RepoOferte& repo;
public:
	UndoModifica(const Oferta& of, RepoOferte& rep) : repo{ rep }, OfertaModificata{ of } {};

	void doUndo() override {
		repo.modRepo(OfertaModificata);
	}
};