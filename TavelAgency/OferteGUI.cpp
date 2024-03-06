#include "OferteGUI.h"
#include "Oferta.h"
#include "WishListGUI.h"

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>
#include <qpalette.h>
#include <qbrush.h>
#include<qdebug.h>
#include <string>
#include <algorithm>

#include <unordered_map>

void OferteGUI::initGUI() {
	QHBoxLayout* lyMain = new QHBoxLayout{};
	setLayout(lyMain);

	//QWidget* widDreapta = new QWidget; 
	QVBoxLayout* vl = new QVBoxLayout; 
	//widDreapta->setLayout(vl);
	vl->addWidget(lst);

	//QWidget* widBtnDreapta = new QWidget;
	QHBoxLayout* lyBtnF = new QHBoxLayout;
	//widBtnDreapta->setLayout(lyBtnF);
	lyBtnF->addWidget(btnFDes);
	lyBtnF->addWidget(btnFPret1);
	lyBtnF->addWidget(btnFPret2);


	QHBoxLayout* lyBtnS = new QHBoxLayout;
	lyBtnS->addWidget(btnSDen);
	lyBtnS->addWidget(btnSDes);
	lyBtnS->addWidget(btnSTipPret);

	vl->addLayout(lyBtnF);
	vl->addLayout(lyBtnS);
	lyMain->addLayout(vl);
	/*vl->addWidget(widBtnDreapta);
	lyMain->addWidget(widDreapta);*/

	auto stgLy = new QVBoxLayout;

	auto formLy = new QFormLayout;
	formLy->addRow("Id:", txtId);
	formLy->addRow("Denumire:", txtDen);
	formLy->addRow("Destinatie:", txtDes);
	formLy->addRow("Tip:", txtTip);
	formLy->addRow("Pret:", txtPret);
	stgLy->addLayout(formLy);

	QHBoxLayout* lyBtn = new QHBoxLayout{};
	lyBtn->addWidget(btnAdd); 
	lyBtn->addWidget(btnDell);
	lyBtn->addWidget(btnMod); 
	lyBtn->addWidget(btnExit);
	stgLy->addLayout(lyBtn); 
	
	QHBoxLayout* lyBtn2 = new QHBoxLayout{};
	lyBtn2->addWidget(cmdSupriza);
	lyBtn2->addWidget(wlist);
	lyBtn2->addWidget(readOnly);
	lyBtn2->addWidget(undo);
	stgLy->addLayout(lyBtn2);

	QHBoxLayout* lyBtn3 = new QHBoxLayout{};
	lyBtn3->addWidget(btnAddW);
	lyBtn3->addWidget(btnDellW);
	lyBtn3->addWidget(btnGenW);
	stgLy->addLayout(lyBtn3);

	btnDyn->setLayout(lyBtnDy);
	lyMain->addWidget(btnDyn);

	lyMain->addLayout(stgLy);
}

void OferteGUI::connectSignalsSlots() {
	QObject::connect(lst, &QListWidget::itemSelectionChanged, [&]() {
		auto sel = lst->selectedItems();
		if (sel.isEmpty()) {
			txtId->setText("");
			txtDen->setText("");
			txtDes->setText("");
			txtTip->setText("");
			txtPret->setText("");
			//btnAddToCos->setDisabled(true);
		}
		else {
			auto selItem = sel.at(0);
			auto den = selItem->text();
			txtDen->setText(den);
			auto id = selItem->data(Qt::UserRole).toString();
			txtId->setText(id);
			auto rez = std::find_if(serv.getAll().begin(), serv.getAll().end(), [id](const Oferta& of) {
				return of.getId() == id.toInt();
				});
			if (rez != serv.getAll().end()) {
				txtDes->setText(QString::fromStdString((*rez).getDestinatie()));
				txtTip->setText(QString::fromStdString((*rez).getTip()));
				txtPret->setText(QString::number((*rez).getPret()));
			}
			//btnAddToCos->setEnabled(true);
		}
		});

	QObject::connect(btnExit, &QPushButton::clicked, [&]() {
		qDebug() << "Exit button apasat!";
		QMessageBox::information(nullptr, "Info", "Exit button apasat!");
		close();
		});

	QObject::connect(btnAdd, &QPushButton::clicked, [&]() {
		try {
			serv.addService(txtId->text().toInt(), txtDen->text().toStdString(),
				txtDes->text().toStdString(), txtTip->text().toStdString(),
				txtPret->text().toInt());
			golesteListaButoane();
			adaugaButoane(serv.getAll());
		}
		catch (ValidateException& e) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(e.getMesaj()));
		}
		catch (RepoException& r) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(r.getMesaj())); 
		}
		loadData(serv.getAll());
		qDebug() << txtId->text() << " " << txtDen->text() << " " << txtDes->text()
			<< " " << txtTip->text() << " " << txtPret->text();
		});

	QObject::connect(btnDell, &QPushButton::clicked, [&]() {
		try {
			serv.dellService(txtId->text().toInt());
			golesteListaButoane();
			adaugaButoane(serv.getAll());
		}
		catch (RepoException& r) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(r.getMesaj()));
		}
		loadData(serv.getAll());
		qDebug() << txtId->text();
		});

	QObject::connect(btnMod, &QPushButton::clicked, [&]() {
		try {
			serv.modService(txtId->text().toInt(), txtDen->text().toStdString(),
				txtDes->text().toStdString(), txtTip->text().toStdString(),
				txtPret->text().toInt());
			golesteListaButoane();
			adaugaButoane(serv.getAll());
		}
		catch (ValidateException& e) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(e.getMesaj()));
		}
		catch (RepoException& r) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(r.getMesaj()));
		}
		loadData(serv.getAll());
		qDebug() << txtId->text() << " " << txtDen->text() << " " << txtDes->text()
			<< " " << txtTip->text() << " " << txtPret->text();
		});

	QObject::connect(btnFDes, &QPushButton::clicked, [&]() {
		qDebug() << "filtru DESTINATIE";
		loadData(serv.filtrare_destinatie(txtDes->text().toStdString()));
		});

	QObject::connect(btnFPret1, &QPushButton::clicked, [&]() {
		qDebug() << "filtru PRET<=";
		loadData(serv.filtrare_pret1(txtPret->text().toInt()));
		});

	QObject::connect(btnFPret2, &QPushButton::clicked, [&]() {
		qDebug() << "filtru PRET>=";
		loadData(serv.filtrare_pret2(txtPret->text().toInt()));
		});

	QObject::connect(btnSDen, &QPushButton::clicked, [&]() {
		qDebug() << "sort DENUMIRE";
		loadData(serv.sortareDen());
		});

	QObject::connect(btnSDes, &QPushButton::clicked, [&]() {
		qDebug() << "sort DESTINATIE";
		loadData(serv.sortareDes());
		});

	QObject::connect(btnSTipPret, &QPushButton::clicked, [&]() {
		qDebug() << "sort TIP&PRET";
		loadData(serv.sortareTipPret());
		});

	QObject::connect(cmdSupriza, &QPushButton::clicked, [&]() {
		try {
			serv.addService(1, "OfertaPaste", "Moisei", "AllInclusive", 2000);
			serv.addService(2, "OfertaCraciun", "Borsa", "Exclusive", 1700);
			serv.addService(3, "Oferta1Mai", "Viseu", "5Stars", 1200);
			serv.addService(4, "OfertaAugust", "Maramures", "AllInclusive", 1000);
			serv.addService(5, "OfertaVara", "Cluj", "Idk", 9999);
		}
		catch (RepoException& r) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(r.getMesaj()));
		}
		qDebug() << "cmdSupriza";
		loadData(serv.getAll());
		golesteListaButoane();
		adaugaButoane(serv.getAll());
		QTableView* tV = new QTableView();
		MyTableModel* model = new MyTableModel(serv.getAll());
		tV->setModel(model);
		tV->show();
		});

	QObject::connect(undo, &QPushButton::clicked, [&]() {
		qDebug() << "undo";
		try {
			serv.undo();
			loadData(serv.getAll());
			golesteListaButoane();
			adaugaButoane(serv.getAll());
		}
		catch (ServiceException& s) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(s.getMesaj()));
		}
		});

	QObject::connect(wlist, &QPushButton::clicked, [&]() {
		/*qDebug() << "WishList";
		QMessageBox::warning(this, "Warning", QString::fromStdString("Folositi fereastra specifica WishList-ului!"));*/
		auto fereastra = new WishListGUITable{this->wl};
		fereastra->show();
		});

	QObject::connect(readOnly, &QPushButton::clicked, [&]() {
		auto fereastra = new WishListReadOnlyGUI{ this->wl };
		fereastra->show();
		});

	//wl.addObserver(this);
	QObject::connect(btnAddW, &QPushButton::clicked, [&]() {
		try {
			wl.add(txtDen->text().toStdString());
		}
		catch (WishListException& exw) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(exw.getMesaj()));
		}
		//loadTableWishList(wish.getAllW());
		});

	QObject::connect(btnDellW, &QPushButton::clicked, [&]() {
		wl.dell();
		//loadTableWishList(wish.getAllW());
		});

	QObject::connect(btnGenW, &QPushButton::clicked, [&]() { 
		try {
			wl.genereaza(txtPret->text().toInt()); 
		}
		catch (WishListException& exw) { 
			QMessageBox::warning(this, "Warning", QString::fromStdString(exw.getMesaj()));
		}
		//loadTableWishList(wish.getAllW());
		});
}

void OferteGUI::golesteListaButoane() {
	for (auto btn : lstDyn) {
		delete btn;
	}
	lstDyn.clear();
}

void OferteGUI::adaugaButoane(const vector<Oferta>& oferte) {
	std::unordered_map<string, int> mp;
	for (auto& oferta : oferte) {
		mp[oferta.getTip()]++;
	}
	for (auto& tip : mp) {
		auto btn = new QPushButton{ QString::fromStdString(tip.first) };
		lstDyn.append(btn);
		lyBtnDy->addWidget(btn);
		QObject::connect(btn, &QPushButton::clicked, [this, tip]() {
			QMessageBox::information(nullptr, "Info", QString::number(tip.second));
			});
	}
}

void OferteGUI::loadData(const vector<Oferta>& oferte) {
	lst->clear();

	for (const auto& of : oferte) {
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(of.getDenumire()));
		//lst->addItem(QString::fromStdString(of.getDenumire()));
		lst->addItem(item);
		item->setData(Qt::UserRole, QString::number(of.getId()));

		qDebug() << of.getId() << " " << of.getDenumire() << of.getDestinatie()
			<< " " << of.getTip() << " " << of.getPret();
	}
	qDebug() << "Numar oferte service:" << oferte.size();
}