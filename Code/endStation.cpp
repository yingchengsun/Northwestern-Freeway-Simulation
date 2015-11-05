/**
 * @attention Copyright (C), 2010, Xidian University.
 *
 * @file station.cpp
 * @author ��ӱ��
 * @date 2010/11/25
 * @brief �յ�վ��
 * @version 1.0
 */

#ifndef ENDSTATION_H_H
#define ENDSTATION_H_H

#include <iostream>
#include <fstream>
#include <list>
#include "string"

#include "passenger.cpp"
#include "bus.cpp"
#include "time.cpp"
#include "station.h"

using namespace std;

class endStation : public station{

private:
	int numVolvo;//����Volvo������
	int numIveco;//����Iveco������
	int numPassPerMin;//ÿ���Ӳ��������˿���

	list<bus>::iterator it_V;//volve�����еĵ�����
	list<bus>::iterator it_I;//iveco�����еĵ�����

	list<bus> lvBus;
	list<bus> liBus;
	

	time lvtLastBus;//volve�������е����һ�������ĳ���ʱ��
	time litLastBus;//iveco�������е����һ�������ĳ���ʱ��
public:
	 time VStartT;//volve����ʱ��
	 time VStopT;//volveͣ��ʱ��
	 time IStartT;//iveco����ʱ��
	 time IStopT;//ivecoͣ��ʱ��

	list<passenger> lPass;//�˿Ͷ���
	list<bus> lOnwayBus;
public:


	//���캯��
	endStation(string name):VStartT(8,30),VStopT(17,30),IStartT(8,0),IStopT(18,00){
		ifstream fin;
		/*���ļ����뵱ǰ��վ���е�Volvo��Iveco���˿͵���Ŀ*/	
		if (name=="XN"){
			fin.open("source\\stationXA.txt");
			fin>>numVolvo>>numIveco>>numPassPerMin;
		}else
		{
			fin.open("source\\stationBJ.txt");
			fin>>numVolvo>>numIveco>>numPassPerMin;
		}
		this->name=name;
		fin.close();
		generateBus();
	
		
	}

	void generateBus()
	{
		int i;
		int tempId=2000;
		int temp_b=0;//0��ʾ������1��ʾ����
		/*��ʼ���ĸ�վ���ɵ������ı�־λ��false������վ*/

		time tv(8,30);//volve����ʱ��
		time ti(8,0);//iveco����ʱ��

		for(i=0;i<numVolvo;++i)
		{/*����Volvo*/
			if(tv>VStopT)
			{	//��ʱ�����ͣ��ʱ����������
				break;
			}
			temp_b=0;
			if("XN"==name)
			{
				tempId=1000;//���ڳ�ʼ������id����ʱ������
				temp_b=1;
			}
			bus temVolvo("volve",(i+100+tempId),temp_b);//��������
			temVolvo.set_startTime(tv);
			lvBus.push_back(temVolvo);//�������ɵ�����������������	
		
			lvtLastBus=tv;//�����������е����һ�������ĳ���ʱ��
			
			tv=tv.timePlusMin(60);//ʱ������60���� 
		}

		for(i=0;i<numIveco;++i)
		{
			/*����Iveco*/
			if(ti>IStopT)
			{	//��ʱ�����ͣ��ʱ����������
				break;
			}
			tempId=2000;
			temp_b=0;
			if("XN"==name)
			{
				tempId=1000;//���ڳ�ʼ������id����ʱ������
				temp_b=1;

			}
			bus temIveco("iveco",(i+200+tempId),temp_b);//��������

			temIveco.set_startTime(ti);
			liBus.push_back(temIveco);//�������ɵ�����������������
			litLastBus=ti;//�����������е����һ�������ĳ���ʱ��

			ti=ti.timePlusMin(20);//ʱ������20���� 
		}

		it_V=lvBus.begin();//��ʼ��Volvo�����б�ĵ�������ָ���б������һ��δ��������
		it_I=liBus.begin();//��ʼ��Iveco�����б�ĵ�������ָ���б������һ��δ��������
	} 


	/*�������0-numPassPerMin����Ŀ�ĳ˿�*/
	void generatePassenger(int direct){		
		for(int i=0; i<((unsigned)rand())%numPassPerMin+1; i++){
			if(direct==1){
				passenger temPass(1);	
				lPass.push_back(temPass);//�����³˿�
			}else
			{
				passenger temPass(0);
				lPass.push_back(temPass);//�����³˿�
			}
			
		}	
	}

	void regeditPass(bus& _b){	
		_b.personAccess(lPass.front().get_SN(),1);
		/*�˿��ϳ�*/
		lPass.pop_front();
		/*�˿ͳ��ȳ�����*/
		
	}

    inline void refreshIter(list<bus>::iterator& _it)
	{
		if(_it->isFull())
		/*����ǰ���������������ָ����һ����*/
			++_it;		
	}

	void getOn(){

		while(!lPass.empty()){	//���зǿ�
			
		 	if(it_V==lvBus.end()&&it_I==liBus.end()){//���Ӷ������ˣ��˳�ѭ��
				break;
			}

			if(it_V!=lvBus.end()&&it_I==liBus.end()){//volvoδ������Volvo
				regeditPass(*it_V);	//�˿��б�ĵ�һ�����ϳ������ҳ���
				refreshIter(it_V);//����Volvo���ӵ�ָ�����һ��δ�����ĵ�����
				continue;
			}

			if(it_V==lvBus.end()&&it_I!=liBus.end()){//Ivecoδ������Iveco
				regeditPass(*it_I);//�˿��б�ĵ�һ�����ϳ������ҳ���
				refreshIter(it_I);//����Iveco���ӵ�ָ�����һ��δ�����ĵ�����
				continue;
			}
		
			if(it_V->get_startTime()<it_I->get_startTime()){//ȫδ��
				//��Volvo�ķ���ʱ���Iveco�ķ���ʱ���磬��Volvo	
				regeditPass(*it_V);	//�˿��б�ĵ�һ�����ϳ������ҳ���
				refreshIter(it_V);//����Iveco���ӵ�ָ�����һ��δ�����ĵ�����
				continue;			
			}
		
			if(it_I->get_startTime()<it_V->get_startTime()){//ȫδ��
				//��Iveco�ķ���ʱ���Volvo�ķ���ʱ���磬��Iveco
				regeditPass(*it_I);	//�˿��б�ĵ�һ�����ϳ������ҳ���
				refreshIter(it_I); //����Iveco���ӵ�ָ�����һ��δ�����ĵ�����
				continue;
			} 
			 
		}//while
	}//getOn

	
	/*����Volvo����*/
	void  startVolvo()
	{
		if(!lvBus.empty())
		{
			/*�������зǿ�*/
			if(it_V==lvBus.begin())
			{
				++it_V;//�����ߵ������һ��δ�����������򽫵�����ָ����һ������
			}
			lvBus.front().start();//��ͷ��������
			lOnwayBus.push_back(lvBus.front());//����������˳�վ����·���е������ĳ���
			lvBus.pop_front();//���������ӳ�����վ�Ķ���ɾ��*/
		}
	}


		
	/*����Volvo����*/
	void startIveco()
	{
		if(!liBus.empty())
		{
			/*�������зǿ�*/
			if(it_I==liBus.begin())
			{				
				++it_I;//�����ߵ������һ��δ�����������򽫵�����ָ����һ������
			}
				
			liBus.front().start();//��ͷ��������
			lOnwayBus.push_back(liBus.front());//����������˳�վ����·���е������ĳ���
			liBus.pop_front();//���������ӳ�����վ�Ķ���ɾ��*/
		}
	}
	
	/*��ʾ�����򱦼���վ�ڵ���Ϣ*/
	void showStationInfo(ostream& out)
	{
		int tempBN,tempPN=0;
		list<bus>::iterator it;
		
		if (name=="XN")
			name="����";
		if (name=="BJ")
			name="����";

		//���Volvo������Ϣ�����Ҽ���Volvo���ϵĳ˿���Ŀ
		if((tempBN=lvBus.size())>=1)		
		{
			out<<name<<" ��վ�� "<<tempBN<<" ���ֶ��ֳ�."<<endl;
		}
		else
		{	
			out<<name<<"��վû���ֶ��ֳ�. "<<endl;
		}
		/*���Volvo������Ϣ*/
		for(it=lvBus.begin();it!=lvBus.end();++it)
		{
			out<<"  �ֶ��� ID:"<<it->get_id()<<"..���ڳ˿�����:"<<it->countPerson()<<" ����ʱ��:"<<it->get_startTime().get_TimeStr()<<endl;
			tempPN+=it->countPerson();
		}
		
		out<<endl;
		
		//���Iveco������Ϣ�����Ҽ���Iveco���ϵĳ˿���Ŀ
		if((tempBN=liBus.size())>=1)		
		{
			out<<name<<" ��վ�� "<<tempBN<<" ����ά�³�."<<endl;
		}
		else
		{	
			out<<name<<" ��վû����ά�³�. "<<endl;
		}
		
		
		for(it=liBus.begin();it!=liBus.end();++it)
		{
			out<<"  ��ά�� ID:"<<it->get_id()<<"..���ڳ˿�����:"<<it->countPerson()<<" ����ʱ��:"<<it->get_startTime().get_TimeStr()<<endl;
			tempPN+=it->countPerson();
		}	
		
		out<<endl;

		//����˿���Ϣ
		if((tempPN+=lPass.size())>=1)	
		{
			out<<name<<" ��վ�� "<<tempPN<<" λ�˿�."<<endl;
		}
		else
		{	
			out<<name<<"��վû�г˿�. "<<endl;
		}
		
	}


	/*��ʾ·���г���Ϣ*/
	void showOnwayInfo(ostream& out,time _t)
	{
		list<bus>::iterator it;

		if(lOnwayBus.empty())
		{
			/*���г�����Ϊ�գ���������*/
			if(name=="����") 
				out<<"����������·��û������!"<<endl;
			if(name=="����") 
				out<<"����������·��û������!"<<endl;	
			return;
			/*����*/
		}

		for(it=lOnwayBus.begin();it!=lOnwayBus.end();++it)
		{
			it->showStatic(out,_t);
			/*����ÿһ������������ĵ�ǰ��Ϣ*/
		}	
	}



	void getIntoStation(endStation& _ss,time _t)
	{
		time tempT;
		list<bus>::iterator it;

		for(it=lOnwayBus.begin();it!=lOnwayBus.end();)//����·��ÿһ����������
		{			
			if(it->stopTime()==_t)//����ǰʱ��Ϊ���ͣ��ʱ��
			{
				it->perReset();//���ĳ˿�������
				if(it->get_kind()=="volve") 
				{
						//Volvo
						tempT=_ss.lvtLastBus;
						/*����������е����һ��������ʱ��*/
						do
						{	
							tempT=tempT.timePlusMin(60);//volveÿ��һСʱ��һ�೵
						}while(tempT<=it->stopTime());
						
						if(tempT>VStopT)
						{		
							/*������ķ���ʱ�����������ʱ����ʲô������*/
						}
						else
						{	/*������ķ���ʱ��С��������ʱ���������´���*/		
							it->set_startTime(tempT);//�����ٴη���ʱ��
							_ss.lvBus.push_back(*it);//������복վ�Ķ�Ӧ��������������
							_ss.lvtLastBus=tempT;//���øö��е����һ�����ķ���ʱ��

							if(it_V==lvBus.end())
							{
								it_V==endLast(lvBus);//���µ���������it_v����Ϊ���һ����ЧԪ�صĵ�����
							}
						}			
						break;
				}
				if(it->get_kind()=="iveco") 
				{		
						//Iveco
						tempT=_ss.litLastBus;
						/*����������е����һ��������ʱ��*/
						do
						{								
							tempT=tempT.timePlusMin(20);//ivecoÿ��20���ӷ�һ�೵
						}while(tempT<=it->stopTime());
						
						if(tempT>IStopT)
						{	
							/*������ķ���ʱ�����������ʱ����ʲô������*/
						}
						else
						{		
							/*������ķ���ʱ��С��������ʱ���������´���*/	
							it->set_startTime(tempT);//�����ٴη���ʱ��
							_ss.liBus.push_back(*it);//������복վ�Ķ�Ӧ��������������
							_ss.litLastBus=tempT;//���øö��е����һ�����ķ���ʱ��*/

							if(it_I==liBus.end())
							{							
								it_I==endLast(liBus);//���µ���������it_v����Ϊ���һ����ЧԪ�صĵ�����
							}
						}				
						break;				
				}

				it=lOnwayBus.erase(it);//���˳����г�������ɾ��*/
				continue;
			}//if
			++it;
		}//for
	}

	/*���µ�����*/
	list<bus>::iterator endLast(list<bus> li){	
		list<bus>::iterator it;
		list<bus>::iterator itLast;
		
		for(it=li.begin();it!=li.end();it++)
		{
			itLast=it;
		}
		return itLast;
	}


};
#endif