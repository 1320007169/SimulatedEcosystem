#include "SimulatedEcosystem.h"
#include <QtWidgets/QApplication>
#include "Log.h"
#include "Vector2D.h"
#include <iostream>
#include <string>
#include "Environment.h"
#include "Grass.h"
#include <memory>

/*
* 
�ڹ��캯�����棬������ʹ��һ���»��߿�ͷ������_n���������Ա������n=n�Ĵ���
һ��ʹ��shared_ptf,��ֹʹ��C++ԭ��ָ�룬�����ڴ����
���ԵĴ���д��DEBUG���棬��ʽ�Ĵ���д��else���棬��main��������ĺ궨��
��ֹʹ��std::cout��һ��ʹ��LogMessage�����������Ҫ��ע������ĵȼ�
������ʹ�ô�д��ͷ������GetNumber();
������ʹ��Сд��ͷ���»������ӣ�����number_hello;
*/
#define DEBUG

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SimulatedEcosystem w;
    w.show();
 
#ifdef DEBUG
    /*
    Log::LogMessage("HelloWorld", LogLevel::Info);
	Log::LogMessage("HelloWorld", LogLevel::Warning);
	Log::LogMessage("HelloWorld", LogLevel::Error);*/
    
    map<Species, int> test_species;
    test_species[Species::Grass] = 100;
    
    Environment environment(test_species);

   /* std::shared_ptr<Grass> it = std::dynamic_pointer_cast<Grass>(*environment.GetEnvironment()->begin());
	Log::LogMessage(std::to_string(it->GetPosition().GetX()) +"  " + std::to_string(it->GetPosition().GetY()), LogLevel::Info);
    Log::LogMessage("HelloWorld", LogLevel::Info);
    shared_ptr<Grass> aim = std::dynamic_pointer_cast<Grass>(environment.GetClosetPair(*it,it->GetSpecies()));
    if(aim!=NULL) Log::LogMessage(std::to_string(aim->GetPosition().GetX()) + "  "+ std::to_string(aim->GetPosition().GetY()), LogLevel::Info);
    Log::LogMessage("HelloWorld", LogLevel::Info);
    PrintAnimals(environment);*/

#else

#endif


    return a.exec();
}
