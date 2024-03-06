#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_AgentieDeTurismGUI.h"

class AgentieDeTurismGUI : public QMainWindow
{
    Q_OBJECT

public:
    AgentieDeTurismGUI(QWidget *parent = nullptr);
    ~AgentieDeTurismGUI();

private:
    Ui::AgentieDeTurismGUIClass ui;
};
