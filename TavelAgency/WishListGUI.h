#pragma once
#include <qwidget.h>
#include <qtimer.h>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <qpushbutton.h>
#include <qlistwidget.h>
#include <qtablewidget.h>
#include <qstring.h>
#include <qlabel.h>

#include "Oferta.h"
#include "WishList.h"
#include "observer.h"

#include <vector>
#include <random>

class WishListGUITable: public QWidget, public Observer{
private:
	WishList& wish;

	QTableWidget* lst = new QTableWidget;
	QPushButton* btnAdd = new QPushButton{ "&AdaugaWish" };
	QPushButton* btnDell = new QPushButton{ "&GolesteWish" };
	QPushButton* btnGen = new QPushButton{ "&GenereazaWish" };
	QPushButton* btnExp = new QPushButton{ "&ExportWish" };
	QPushButton* btnRap = new QPushButton{ "&RaportWish" };
	QLineEdit* txtDen = new QLineEdit;
	QLineEdit* txtNr = new QLineEdit;
	QLineEdit* txtNm = new QLineEdit;
	QLineEdit* txtTip = new QLineEdit;
	QLineEdit* txtPret = new QLineEdit;
	void initGUIWishList();
	void connectSignalsWishList();
	void loadTableWishList(const std::vector<Oferta>& oferte);
public:
	WishListGUITable(WishList& w) : wish{ w } {
		initGUIWishList();
		connectSignalsWishList();
		loadTableWishList(wish.getAllW());
	}

	void update() override {
		loadTableWishList(wish.getAllW());
	}

	~WishListGUITable() {
		wish.removeObserver(this);
	}

};

class WishListGUILabel :public QLabel, public Observer {
	WishList& wish;
public:
	WishListGUILabel(WishList& w) :wish{ w } {
		setFont(QFont{ "arial", 24 });
		setAttribute(Qt::WA_DeleteOnClose); //daca vreau sa se distruga fereastra imediat dupa inchidere
		wish.addObserver(this);
		update();
	}

	void update() override {
		setText("WishList-ul contine:" + QString::number(wish.getAllW().size()));
	}
	~WishListGUILabel() {
		wish.removeObserver(this);
	}
};

#include <qpainter.h>

class WishListReadOnlyGUI : public QWidget, public Observer {
private:
	WishList& wl;
public:
	WishListReadOnlyGUI(WishList& w) : wl{ w } {
		wl.addObserver(this);
	}

	void update() override {
		repaint();
	}

	void paintEvent(QPaintEvent* ev) override {
		QPainter p{ this };
		for (auto& x : wl.getAllW()) {
			std::mt19937 mt{ std::random_device{}() }; 
			std::uniform_int_distribution<> dist(0, 200); 
			int rndX = dist(mt);// numar aleator intre [0,size-1]
			std::mt19937 mt1{ std::random_device{}() }; 
			std::uniform_int_distribution<> dist1(0, 200); 
			int rndY = dist1(mt1);// numar aleator intre [0,size-1] 
			p.drawImage(rndX, rndY, QImage("first.png"));
		}
	}

};

class MyTableModel : public QAbstractTableModel {
public:
	vector<Oferta> oferte;
	MyTableModel(const vector<Oferta> of) : oferte{ of } {};
	/**
	* number of rows
	*/
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	/**
	* number of columns
	*/
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	/**
	* Value at a given position
	*/
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
};

