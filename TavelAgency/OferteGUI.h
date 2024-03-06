#pragma once

#include "ServiceOferte.h"
#include "WishList.h"
#include "WishListGUI.h"
#include "observer.h"

#include <QtWidgets/qwidget.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlistwidget.h>
#include <qdebug.h>
#include <qmessagebox.h>

#include <vector>
#include <string>

using std::vector;
using std::string;

class OferteGUI: public QWidget{
private:
    ServiceOferte& serv;
    WishList& wl;

    QListWidget* lst = new QListWidget;

    QPushButton* btnExit = new QPushButton{ "&Exit" };
    QPushButton* btnAdd = new QPushButton{ "&Adauga" };
    QPushButton* btnDell = new QPushButton{ "&Sterge" };
    QPushButton* btnMod = new QPushButton{ "&Modifica" };
    QPushButton* btnFDes = new QPushButton{ "&FiltruDestinatie" };
    QPushButton* btnFPret1 = new QPushButton{ "&FiltruPret<=" };
    QPushButton* btnFPret2 = new QPushButton{ "&FiltruPret>=" };
    QPushButton* btnSDes = new QPushButton{ "&SortDestinatie" };
    QPushButton* btnSDen = new QPushButton{ "&SortDenumire" };
    QPushButton* btnSTipPret = new QPushButton{ "&SortTip&Pret" };
    QPushButton* cmdSupriza = new QPushButton{ "&777" };
    QPushButton* wlist = new QPushButton{ "&WishList" };
    QPushButton* readOnly = new QPushButton{ "&ReadOnly" };
    QPushButton* undo = new QPushButton{ "&Undo" };
    QPushButton* btnAddW = new QPushButton{ "&AdaugaWish" }; 
    QPushButton* btnDellW = new QPushButton{ "&GolesteWish" }; 
    QPushButton* btnGenW = new QPushButton{ "&GenereazaWish" }; 
    QVBoxLayout* lyBtnDy = new QVBoxLayout;
    QWidget* btnDyn = new QWidget;

    QList< QPushButton* > lstDyn;

    QLineEdit* txtId = new QLineEdit;
    QLineEdit* txtDen = new QLineEdit;
    QLineEdit* txtDes = new QLineEdit;
    QLineEdit* txtTip = new QLineEdit;
    QLineEdit* txtPret = new QLineEdit;
    void initGUI();
    void connectSignalsSlots();
    void loadData(const vector<Oferta>& oferte);
    void golesteListaButoane();
    void adaugaButoane(const vector<Oferta>& oferte);
public:
    OferteGUI(ServiceOferte& ser, WishList& w) : serv{ ser }, wl{ w } {
        initGUI();
        connectSignalsSlots();
        loadData(serv.getAll());
        adaugaButoane(serv.getAll());
    }
};

