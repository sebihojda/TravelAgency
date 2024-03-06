#include <QtWidgets/QApplication>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlistwidget.h>

#include <iostream>
#include "Oferta.h"
#include "Validator.h"
#include "RepoOferte.h"
#include "ServiceOferte.h"
#include "WishList.h"
#include "UI.h"
#include "OferteGUI.h"
#include "WishListGUI.h"

void allTests() {
    testOferta();
    testValidator();
    testRepo();
    testAdd();
    testDell();
    testMod();
    testFil();
    testSort();
    testADD_DELL();
    test_genereaza();
    test_export();
    test_raport();
    test_load_and_write();
    testUndo();
}



int main(int argc, char *argv[])
{
    allTests();
    //RepoOferte rep;
    FileRepoOferte rep{ "main_file.txt" };
    Validator val;
    ServiceOferte serv{ rep , val };
    WishList wl{ rep };
    //UI ui{ serv, wl };
    //ui.startUI();
    
    QApplication a(argc, argv); 
    OferteGUI gui{serv, wl};
    gui.move(640,316);
    gui.show();

    WishListGUITable wish{ wl };
    wish.move(142, 249);
    wish.show();

    WishListGUILabel* wish2 = new WishListGUILabel{ wl };
    wish2->show();



    /*WishListReadOnlyGUI wish3{ wl };
    wish3.show();*/

    return a.exec();
}
