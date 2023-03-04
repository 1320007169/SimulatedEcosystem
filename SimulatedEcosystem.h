#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SimulatedEcosystem.h"
#include "AnimalButton.h"
#include <memory>

using std::shared_ptr;

class SimulatedEcosystem : public QMainWindow
{
    Q_OBJECT

public:
    SimulatedEcosystem(QWidget *parent = nullptr);
    ~SimulatedEcosystem();

    void resizeEvent(QResizeEvent* event);//�����ڴ�С����
    void dealUnfold();//��������


private:
    Ui::SimulatedEcosystemClass ui;
    AnimalButton* temp = new AnimalButton(this);
    int move_of_window = 0;//�����
};
