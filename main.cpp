#include "SimulatedEcosystem.h"
#include <QtWidgets/QApplication>
#include "Log.h"
#include "Vector2D.h"
#include <iostream>

/*
�ڹ��캯�����棬������ʹ��һ���»��߿�ͷ������_n���������Ա������n=n�Ĵ���
һ��ʹ��shared_ptf,��ֹʹ��C++ԭ��ָ�룬�����ڴ����
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SimulatedEcosystem w;
    w.show();
    
    //std::cout << "hello";

	/*Log::LogMessage("HelloWorld", LogLevel::Info);
	Log::LogMessage("HelloWorld", LogLevel::Warning);
	Log::LogMessage("HelloWorld", LogLevel::Error);
    Vector2D::GetDirectionVector(Direction(5));*/

    return a.exec();
}
