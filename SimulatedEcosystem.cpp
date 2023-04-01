#include "SimulatedEcosystem.h"
#include "Animal.h"

SimulatedEcosystem::SimulatedEcosystem(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    temp->setParent(this);
    temp->show();
    move_of_sidebar = 0;
    ui.scrollAreaWidgetContents->setFixedHeight(475);
    ui.scrollAreaWidgetContents->setFixedWidth(715);

        
    connect(timer, &QTimer::timeout, this, &SimulatedEcosystem::UpdateSurface);
    connect(ui.regame, &QPushButton::clicked, this, &SimulatedEcosystem::ReGame);
    connect(ui.curveFigure, &QPushButton::clicked, this, &SimulatedEcosystem::CurveFigure);
    connect(ui.startButton, &QPushButton::clicked, this, &SimulatedEcosystem::StartButton);
	connect(ui.stopButton, &QPushButton::clicked, this, &SimulatedEcosystem::StopButton);

    connect(ui.pushButton, &QPushButton::clicked, this, &SimulatedEcosystem::AddButton_1);
	connect(ui.pushButton_2, &QPushButton::clicked, this, &SimulatedEcosystem::AddButton_2);
	connect(ui.pushButton_3, &QPushButton::clicked, this, &SimulatedEcosystem::AddButton_3);
	connect(ui.pushButton_4, &QPushButton::clicked, this, &SimulatedEcosystem::AddButton_4);
	connect(ui.pushButton_5, &QPushButton::clicked, this, &SimulatedEcosystem::AddButton_5);

    ui.lineEdit->setText("0");
	ui.lineEdit_2->setText("0");
	ui.lineEdit_3->setText("0");
	ui.lineEdit_4->setText("0");
	ui.lineEdit_5->setText("0");


	test_species[Species::Cow] = 30;
	test_species[Species::Grass] = 60;


    environment = std::make_shared<Environment>(test_species);
    
    shared_ptr<vector<shared_ptr<Animal>>> animals = environment->GetEnvironment();

    for (shared_ptr<Animal>& animal : *animals) {
        AddNewAnimal(animal);
    }

    connect(ui.unfold, &QPushButton::clicked, this, &SimulatedEcosystem::DealUnfold);
    pointlist.clear();
    chart = new MyChart(this, QString::fromLocal8Bit(""));
    ui.line->show();
    ui.line_2->show();
    setWindowFlags(windowFlags() & ~Qt::WindowMinMaxButtonsHint | Qt::WindowMinimizeButtonHint);
    InitChart();
	chart->show();
}

SimulatedEcosystem::~SimulatedEcosystem()
{

}

void SimulatedEcosystem::resizeEvent(QResizeEvent* event) {
    int w = width();
    int h = height();
    
    ui.stackedWidget->setGeometry(w - 20 - move_of_sidebar, 0, 200, 500);
    ui.stackedWidget->hide();
    ui.stackedWidget_2->setGeometry(740, 11, 283, 483);

    ui.time->setGeometry(540, 11, 200, 30);

    ui.scrollArea->setGeometry(11, 11, 724, 483);
    chart->setGeometry(11, 500, 1020, 330);
    ui.line_2->setGeometry(EnvironmentConstants::UPPER_BOUND - 2, 0, 6, 800);
    ui.line->setGeometry(6, EnvironmentConstants::UPPER_BOUND - 2, 1000, 6);
    //chart->setGeometry(0, 0, 800, 600);
    
}

void SimulatedEcosystem::DealUnfold() {
    if (move_of_sidebar == 0) {
        move_of_sidebar = 200 - 20;
        ui.stackedWidget->setGeometry(width() - 20 - move_of_sidebar, 0, 200, 500);
        ui.unfold->setText(">");
    }
    else {
        move_of_sidebar = 0;
        ui.stackedWidget->setGeometry(width() - 20 - move_of_sidebar, 0, 200, 500);
        ui.unfold->setText("<");
    }
}

void SimulatedEcosystem::InitChart()
{
    chart->setAxis(QString::fromLocal8Bit("time"), 0, 100, 10, QString::fromLocal8Bit("The number of animals"), 0, 20, 10);

    QList<QPointF> pointlist_temp = { QPointF(0,1), QPointF(20,2), QPointF(20,4), QPointF(30,8), QPointF(40,16),
                                QPointF(50,16), QPointF(60,8), QPointF(70,4), QPointF(80,2), QPointF(90,1), };
    pointlist.append(pointlist_temp);




    chart->buildChart(pointlist);
}

void SimulatedEcosystem::UpdateSurface() {
    if (is_updating)
        return;
    is_updating = true;
    time++;
    if (time % FPS == 0) {
		ui.time->setText(QString::fromLocal8Bit("ʱ�䣺") + QString::number(time / FPS) + QString::fromLocal8Bit(" ��"));
		environment->Update();
		animals = environment->GetEnvironment();
		vector<int>deadID = environment->GetDeadAnimals();
		for (int id : deadID) {
			DeleteAnimal(id);
		}
		for (shared_ptr<Animal>& animal : *animals) {
			int temp_ID = animal->GetID();
			if (my_animals.find(temp_ID) != my_animals.end()) {
				MoveAnimal(animal);
			}
			else {//new baby animals
				AddNewAnimal(animal);
			}
			AnimalButton* temp = my_animals[animal->GetID()];
		}
    }
    else {
        if (animals != NULL)
        for (shared_ptr<Animal>& animal : *animals) {
            //animal->get
        }
    }
    is_updating = false;
}

void SimulatedEcosystem::DeleteAnimal(int id) {
    AnimalButton* temp = my_animals[id];
	temp->setParent(NULL);
	delete temp;
    my_animals.erase(my_animals.find(id));
}

void SimulatedEcosystem::AddNewAnimal(shared_ptr<Animal> animal) {
	AnimalButton* temp = new AnimalButton(ui.scrollAreaWidgetContents, animal);
	my_animals[animal->GetID()] = temp;
}

void SimulatedEcosystem::MoveAnimal(shared_ptr<Animal> animal) {
    int id = animal->GetID();
    my_animals[id]->SetAnimal(animal);
}

void SimulatedEcosystem::ReGame() {
    timer->start(EnvironmentConstants::UPDATE_FREQUENCY_MS * FPS);
}

void SimulatedEcosystem::CurveFigure() {
    chart->show();
}

void SimulatedEcosystem::StartButton() {
    if (ui.startButton->text() == "Start") {
        ui.startButton->setText("Restart");
		//timer->start(EnvironmentConstants::UPDATE_FREQUENCY_MS * FPS);

    }
    else if (ui.startButton->text() == "Restart") {
		ui.startButton->setText("OK");
		ui.lineEdit->setReadOnly(false);
		ui.lineEdit_2->setReadOnly(false);
		ui.lineEdit_3->setReadOnly(false);
		ui.lineEdit_4->setReadOnly(false);
		ui.lineEdit_5->setReadOnly(false);
        ui.stopButton->hide();
    }
    else if (ui.startButton->text() == "OK") {
		ui.startButton->setText("Restart");
		
		ui.lineEdit->setReadOnly(true);
		ui.lineEdit_2->setReadOnly(true);
		ui.lineEdit_3->setReadOnly(true);
		ui.lineEdit_4->setReadOnly(true);
		ui.lineEdit_5->setReadOnly(true);

		ui.stopButton->show();
    }
}

void SimulatedEcosystem::StopButton() {
	if (ui.stopButton->text() == "Stop") {
		ui.stopButton->setText("Resume");
        timer->stop();
	}
	else if (ui.stopButton->text() == "Resume") {
		ui.stopButton->setText("Stop");

	}
}

void SimulatedEcosystem::AddButton_1() {
    int temp = ui.lineEdit->text().toInt() + 1;
    if (!ui.lineEdit->isReadOnly())
        ui.lineEdit->setText(QString::number(temp));
}

void SimulatedEcosystem::AddButton_2() {
	int temp = ui.lineEdit_2->text().toInt() + 1;
	if (!ui.lineEdit_2->isReadOnly())
	    ui.lineEdit_2->setText(QString::number(temp));
}

void SimulatedEcosystem::AddButton_3() {
	int temp = ui.lineEdit_3->text().toInt() + 1;
	if (!ui.lineEdit_3->isReadOnly())
	    ui.lineEdit_3->setText(QString::number(temp));
}

void SimulatedEcosystem::AddButton_4() {
	int temp = ui.lineEdit_4->text().toInt() + 1;
	if (!ui.lineEdit_4->isReadOnly())
	    ui.lineEdit_4->setText(QString::number(temp));
}

void SimulatedEcosystem::AddButton_5() {
	int temp = ui.lineEdit_5->text().toInt() + 1;
	if (!ui.lineEdit_5->isReadOnly())
	    ui.lineEdit_5->setText(QString::number(temp));
}
