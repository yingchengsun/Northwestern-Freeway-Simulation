/**
 * @attention Copyright (C), 2010, Xidian University.
 *
 * @file controller.cpp
 * @author ��ӱ��
 * @date 2010/11/25
 * @brief ��������
 * @version 1.0
 */
#ifndef CONTROLLER_H_H
#define CONTROLLER_H_H
#include "iostream"
#include "fstream"
#include "windows.h"
#include <list>

#include "time.cpp"
#include "endStation.cpp"

#include "bus.cpp"
#include "passenger.cpp"

using namespace std;

class controller{

public:

	//����ģ�ⷽ��
	void start(ostream& out)
	{
		
		time currentTime(7,29);// ��ʼ����ǰʱ��07:29
		time upTimeLimit(7,29);// �˿͵�����ʱ������
		time lowTimeLimit(18,0);// �˿͵�����ʱ������

		char choice;//������������

		endStation XN("XN");//�����յ�վ
		endStation BJ("BJ");//�����յ�վ

		list<bus> xnList;//����վ�ڳ��Ķ���
		list<bus> bjList;//����վ�ڳ��Ķ���

		passenger::getPossibility();
	

		/* ���������ʾ����Ϣ  */

		//��ʾ�м�վ����Ϣ
		interStation::showInterStopInfo(out);
		
		out<<"**************************************************************"<<endl;
		out<<"                     "<<"�ͳ�ID��ʽ˵��"<<endl<<endl;

		out<<"    ��������վ�Ŀͳ���1xxx ;"<<"  "<<"��������վ�Ŀͳ���2xxx ;\n"
			<<"    �ֶ��ֿͳ���x1xx ;"<<"         "<<"��ά�¿ͳ���x2xx;"<<endl;

		out<<"**************************************************************"<<endl;

		//���˻�ĵ�ǰʱ��
		out<<"                     ��ǰʱ����"<<currentTime.get_TimeStr()<<endl;
		out<<"**************************************************************"<<endl;


		out<<"                     ��վ��Ϣ"<<endl<<endl;
		//��ʾ����վ�ڿͳ���������ͺͱ�ţ����ȳ��ĳ˿�����
		XN.showStationInfo(out);
		out<<endl<<"*------------------------------------------------------*"<<endl;
		
		//��ʾ����վ�ڿͳ���������ͺͱ�ţ����ȳ��ĳ˿�����
		BJ.showStationInfo(out);

		/*��ʾ·���г���Ϣ*/
		out<<endl<<"**************************************************************"<<endl;
		out<<"                     ·����Ϣ"<<endl<<endl;
		XN.showOnwayInfo(out,currentTime);
		out<<"*------------------------------------------------------*"<<endl;
		BJ.showOnwayInfo(out,currentTime);
	
		/*�����վ����*/	
		XN.getIntoStation(BJ,currentTime);
		BJ.getIntoStation(XN,currentTime);
	
		/*��ǰʱ���1��*/
		currentTime=currentTime.timePlusMin(1);

		out<<"�Ƿ�ʼ���г���?  "<<"y:����  n:�˳�"<<endl;
		cin>>choice;
		if(choice=='n')
			return;

		/* ������ʽ������ʾ����Ϣ  */

		while(true){
		
			out<<"**************************************************************"<<endl;

			//���˻�ĵ�ǰʱ��
			out<<"                     ��ǰʱ����"<<currentTime.get_TimeStr()<<endl;
			out<<"**************************************************************"<<endl;
			
			/*���ڹ涨ʱ���ڣ���˿��ϳ�*/
			if(currentTime>upTimeLimit&&currentTime<lowTimeLimit)
			{
			
				XN.generatePassenger(1);					
				XN.getOn();
				BJ.generatePassenger(0);
				BJ.getOn();
			}

			/*����ǰʱ����volve����ʱ����volve*/
			if(currentTime>=XN.VStartT&&currentTime<=XN.VStopT&&currentTime.getMinute()==30)
			{	
				XN.startVolvo();
				BJ.startVolvo();
			}

			/*����ǰʱ����iveco����ʱ����iveco*/
			if(currentTime>=XN.IStartT&&currentTime<=XN.IStopT&&(currentTime.getMinute()%20)==0)

			{
				XN.startIveco();
				BJ.startIveco();
			}
			
			out<<"                     ��վ��Ϣ"<<endl<<endl;
			//��ʾ����վ�ڿͳ���������ͺͱ�ţ����ȳ��ĳ˿�����
			XN.showStationInfo(out);
			out<<endl<<"*------------------------------------------------------*"<<endl;
			
			//��ʾ����վ�ڿͳ���������ͺͱ�ţ����ȳ��ĳ˿�����
			BJ.showStationInfo(out);

			/*��ʾ·���г���Ϣ*/
			out<<endl<<"**************************************************************"<<endl;
			out<<"                     ·����Ϣ"<<endl<<endl;
			XN.showOnwayInfo(out,currentTime);
			out<<"*------------------------------------------------------*"<<endl;
			BJ.showOnwayInfo(out,currentTime);
		
			/*�����վ����*/	
			XN.getIntoStation(BJ,currentTime);
			BJ.getIntoStation(XN,currentTime);
		
			/*��ǰʱ���1��*/
			currentTime=currentTime.timePlusMin(1);

			/*����ǰʱ��Ϊ18:01,���ɢ�ȳ��˿�*/
			if(currentTime==time(18,1))
			
			{
				XN.lPass.clear();
				BJ.lPass.clear();
				out<<"*---------------------------------------------------------------------*\n"
					<<"��վ����û�пɷ��������˿�ȫ���뿪��"<<endl;
				
			}
		
			/*�������Ѿ����˷���ʱ�䣬����·���Ѿ�û�г����˳�ѭ����ģ�����*/
			if(currentTime>XN.IStopT&&XN.lOnwayBus.empty()&&BJ.lOnwayBus.empty())
					break;
			
			/*�ȴ�1s�����ڹ۲���*/
			Sleep(1000);			
		}//while
		out<<"***************************************************************\n"
					<<"            ��������Ѿ�������лл~~"<<endl;
	}//start

};
	
#endif






















