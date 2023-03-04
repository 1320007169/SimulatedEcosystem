#include "SimulatedEcosystem.h"
#include <QtWidgets/QApplication>
#include "Log.h"
#include "Vector2D.h"
#include <iostream>

/*
�ڹ��캯�����棬������ʹ��һ���»��߿�ͷ������_n���������Ա������n=n�Ĵ���
һ��ʹ��shared_ptf,��ֹʹ��C++ԭ��ָ�룬�����ڴ����
���ԵĴ���д��DEBUG���棬��ʽ�Ĵ���д��else���棬��main��������ĺ궨��
��ֹʹ��std::cout��һ��ʹ��LogMessage�����������Ҫ��ע������ĵȼ�
*/
#define DEBUG

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SimulatedEcosystem w;
    w.show();
 
#ifdef DEBUG
    
    Log::LogMessage("HelloWorld", LogLevel::Info);
    Log::LogMessage("HelloWorld", LogLevel::Warning);
    Log::LogMessage("HelloWorld", LogLevel::Error);

#else

#endif

	Log::LogMessage("HelloWorld", LogLevel::Info);
	Log::LogMessage("HelloWorld", LogLevel::Warning);
	Log::LogMessage("HelloWorld", LogLevel::Error);
    Vector2D::GetDirectionVector(Direction(5));

    //?????????????????


    return a.exec();
}
