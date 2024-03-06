#include "WishListGUI.h"

#include <qwidget.h>
#include <qtimer.h>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QFormLayout>
#include <qpushbutton.h>
#include <qlistwidget.h>
#include <qtablewidget.h>
#include <qstring.h>
#include <qlabel.h>
#include <qmessagebox.h>

#include "Oferta.h"
#include <vector>
#include <string>

void WishListGUITable::initGUIWishList() {
	QVBoxLayout* l = new QVBoxLayout;

	QHBoxLayout* ly = new QHBoxLayout;
	ly->addWidget(lst);
	
	QVBoxLayout* vly = new QVBoxLayout;

	auto formLy = new QFormLayout;
	formLy->addRow("Denumire:", txtDen);
	formLy->addRow("Numar oferte:", txtNr);
	formLy->addRow("Nume fisier:", txtNm);
	formLy->addRow("Tip:", txtTip);
	formLy->addRow("Pret:", txtPret);
	vly->addLayout(formLy);

	ly->addLayout(vly);

	QHBoxLayout* btnLy = new QHBoxLayout;
	btnLy->addWidget(btnAdd);
	btnLy->addWidget(btnDell);
	btnLy->addWidget(btnGen);
	btnLy->addWidget(btnExp);
	btnLy->addWidget(btnRap);

	l->addLayout(ly);
	l->addLayout(btnLy);

	setLayout(l);
}

void WishListGUITable::connectSignalsWishList() {
	wish.addObserver(this);
	QObject::connect(btnAdd, &QPushButton::clicked, [&]() {
		try {
			wish.add(txtDen->text().toStdString());
		}
		catch (WishListException& exw) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(exw.getMesaj()));
		}
		//loadTableWishList(wish.getAllW());
		});

	QObject::connect(btnDell, &QPushButton::clicked, [&]() {
		wish.dell();
		//loadTableWishList(wish.getAllW());
		});

	QObject::connect(btnGen, &QPushButton::clicked, [&]() {
		try {
			wish.genereaza(txtNr->text().toInt());
		}
		catch (WishListException& exw) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(exw.getMesaj()));
		}
		//loadTableWishList(wish.getAllW());
		});

	QObject::connect(btnExp, &QPushButton::clicked, [&]() {
		try {

			wish.exportF(txtNm->text().toStdString());
			QMessageBox::information(nullptr, "InfoExport", "WishList exportat cu succes!"); 
		}
		catch (WishListException& exw) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(exw.getMesaj()));
		}
		loadTableWishList(wish.getAllW());
		});

	QObject::connect(btnRap, &QPushButton::clicked, [&]() {
		double nr = wish.raport(txtTip->text().toStdString(), txtPret->text().toInt());
		double procent = nr * 100 / wish.getAllW().size();
		string s = "Procentul ofertelor de tipul " + txtTip->text().toStdString()+ " care costa mai putin de "
			+ txtPret->text().toStdString() + " lei, este " + std::to_string(procent) + "%.\n";
		QMessageBox::information(nullptr, "InfoRaport", QString::fromStdString(s));
		loadTableWishList(wish.getAllW());
		});
}

void WishListGUITable::loadTableWishList(const std::vector<Oferta>& oferte) {
	lst->clear();
	lst->setRowCount(oferte.size());
	lst->setColumnCount(5);
	for (int i = 0; i < oferte.size(); i++) {
		lst->setItem(i, 0, new QTableWidgetItem(QString::number(oferte[i].getId())));
		lst->setItem(i, 1, new QTableWidgetItem(oferte[i].getDenumire().c_str()));
		lst->setItem(i, 2, new QTableWidgetItem(oferte[i].getDestinatie().c_str())); 
		lst->setItem(i, 3, new QTableWidgetItem(oferte[i].getTip().c_str()));
		lst->setItem(i, 4, new QTableWidgetItem(QString::number(oferte[i].getPret())));
	}
}

//MyTableModel::MyTableModel(QObject* parent) :
//	QAbstractTableModel(parent) {
//}
int MyTableModel::rowCount(const QModelIndex& ) const{
	return oferte.size();
}
int MyTableModel::columnCount(const QModelIndex& ) const{
	return 5;
}
QVariant MyTableModel::data(const QModelIndex& index, int role) const {
	if (role == Qt::DisplayRole) {
		qDebug() << "row:" << index.row() << "col:" << index.column();
		Oferta of = oferte[index.row()];
		if (index.column() == 0)
			return QString::number(of.getId());
		else if(index.column() == 1)
			return QString::fromStdString(of.getDenumire());
		else if (index.column() == 2)
			return QString::fromStdString(of.getDestinatie());
		else if (index.column() == 3)
			return QString::fromStdString(of.getTip());
		else if (index.column() == 4)
			return QString::number(of.getPret());
	} 
	return QVariant(); 
}

