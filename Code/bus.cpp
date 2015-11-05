/**
 * @attention Copyright (C), 2010, Xidian University.
 *
 * @file bus.cpp
 * @author ��ӱ��
 * @date 2010/11/25
 * @brief Bus��
 * @version 1.0
 */

#ifndef BUS_H_H
#define BUS_H_H

#include "string"
#include <iostream>
#include <fstream>
#include <list>
#include "vector"

#include "time.cpp"
#include "passenger.cpp"
#include "interStation.cpp"

using namespace std;


class bus{
private:
	int ID; //����
	int limit; //���Ͽ�װ���������
	double speed; //����
	int direction; //������ʻ���� 1:���������� 0:����������
	string type; //���� 
	time startTime;//����ʱ��
	int person[6];//ÿվ�³�����
	time arrayTime[6];//����ÿһվ��ʱ��
	string name;//����

	static unsigned count;	// ��վ����Ŀ
	const static vector<interStation> X2BArrayInterStop;	//��̬����������������֮����м�վ�ĳ�վ��Ϣ��վ��·����Ϣ
	const static vector<interStation> B2XArrayInterStop; //��̬����������������֮����м�վ�ĳ�վ��Ϣ��վ��·����Ϣ

public:
	bus(){
	}
	
	/*���캯��*/
	bus(string type,int ID, int direction)
	{
		ifstream fin;
		this->type=type;
		this->ID=ID;
		this->direction=direction;
		
		for(int i=0;i<6;i++)
			person[i]=0;
		if (type=="volve"){
			fin.open("source\\volve.txt");
			fin>>limit>>speed;
			fin.close();
		}else{
			fin.open("source\\Iveco.txt");
			fin>>limit>>speed;
			fin.close();	
		}

		
	}

	/*�޸ķ���ʱ��*/
	inline void set_startTime(time _t)
	{
		startTime=_t;
	}

	/*��ȡ����ʱ��*/	
	inline time get_startTime(){
		return startTime;
	}
	/*��ȡ�����յ�վ��ʱ��*/
	inline time stopTime()
	{
		return arrayTime[5];
	}

	/*��ȡ������վ���ʱ��*/
	inline void showStopTime()
	{
		
		cout<<ID<<" ";
		for(int i=0;i!=6;++i)
		{
			
			cout<<arrayTime[i].get_TimeStr()<<" ";
		}
		cout<<endl;
	}

	/*��ȡ����ID*/
	int get_id(){
		return this->ID;
	}

	/*��ȡ��������*/
	inline string get_kind()
	{
		return type;
	}

	/*������г˿�*/
	inline void perReset()
	{		
		for(int i=0;i!=interStation::count+1;i++)
		{
			person[i]=0;
		}		
	}



	/*�˿��³�*/
	inline int personAccess(int index,int incre){

		person[index]+=incre;
		return person[index];
	}

	/*���㳵�ڳ˿�����*/
	inline int countPerson()
	{
		return person[0]+person[1]+person[2]+person[3]+person[4]+person[5];		
	}


	/*�жϳ����Ƿ�����*/
	inline bool isFull()
	{
		return (countPerson()==limit);
	}


	/*��������*/
	void start()
	{
		time t=startTime;
		unsigned i;
		if(direction)//����������
		{		
			for(i=0;i!=interStation::count;i++)
			{
				t=t.timePlusMin((interStation::X2BArrayInterStop[i].dist2XaNext)/speed);
				/*��ʼʱ��+ÿһ��·����Ҫ��ʱ����Ϊ����һվ��ʱ��*/
				arrayTime[i]=t;
				
				if(person[i])
				/*����վͣ����ʱ��+2����*/
				{
					t=t.timePlusMin(2);
				}//if
			}//for
			arrayTime[i]=t.timePlusMin((interStation::X2BArrayInterStop[i-1].dist2BjNext)/speed);//count��ֻ�����м�վ��Ŀ
			/*���㵽�յ�վʱ��*/
		}//if
		else//����������
		{
			for(i=0;i!=interStation::count;i++)
			{
				t=t.timePlusMin((interStation::B2XArrayInterStop[i].dist2BjNext/speed));
				arrayTime[i]=t;

				if(person[i])
				{
					t=t.timePlusMin(2);
				}//if
			}//for
			arrayTime[i]=t.timePlusMin((interStation::B2XArrayInterStop[i-1].dist2XaNext)/speed);
		}//else		
	}



	//��ʾ������ǰ״̬��Ϣ
	void showStatic(ostream& out,time _t)
	{
		int i;
		string dir;//���򣺶�����
		double dist;
		time tempT;//��ʱʱ�����

		if(direction)//����������
		{
			dir="��";
			for(i=0;i<interStation::count+1;i++)
			{
				if(i!=interStation::count)//�����յ�վ
				{
					tempT=arrayTime[i].timePlusMin(1);//������վ��Ҫͣ�������ӣ�������һ���ж�����
					if(_t==arrayTime[i]||_t==tempT)//����i��վ
					{
						if(person[i])//�����ڸ�վ�³�
						{
							out<<"ID"<<ID<<" "<<name<<" ���������� �ͳ����� "
								<<interStation::X2BArrayInterStop[i].name<<" վ "
								<<person[i]<<" λ�˿��³�!"
								<<" ���ڳ˿�"<<countPerson()<<"��"<<endl;	
							person[i]=0;//���ϵ���վ�ĳ˿�������0
						}//if
						else/*person[i]==0*/
						{
							out<<"ID"<<ID<<" "<<name<<" ���������� �ͳ����� "
								<<interStation::X2BArrayInterStop[i].name<<" վ. ͣ��������"
								<<" ���ڳ˿�"<<countPerson()<<"��"<<endl;
						}//else
						break;
					}//if
					
					if(_t<arrayTime[i])//û��i��վ
					{
						dist=(arrayTime[i].time2minute()-_t.time2minute())*speed;
						/*���㵱ǰλ�õ���һվ�ľ���*/
						out<<"ID"<<ID<<" "<<name<<" ���������� �ͳ��� "
							<<interStation::X2BArrayInterStop[i].name<<" "<<dir<<" Լ "
							<<dist<<"���ﴦ"
							<<" ���ڳ˿�"<<countPerson()<<"��"<<endl;
						break;
					}//if
				}//if
				
				else/*�յ�վi==count*/
				{
					if(_t==arrayTime[i])//����i��վ
					{
						out<<"ID"<<ID<<" "<<name<<" ���������� �ͳ����ﱦ���յ�վ."<<endl;
						person[i]=0;//���ϵ���վ�ĳ˿�������0
						break;
					}
					if(_t<arrayTime[i])
					{
						dist=(arrayTime[i].time2minute()-_t.time2minute())*speed;
						out<<"ID"<<ID<<" "<<name<<" ���������� �ͳ��� "
							<<"���� "<<dir<<" Լ "<<dist<<"���ﴦ"
							<<" ���ڳ˿�"<<countPerson()<<"��"<<endl;
						break;					
					}
				}//else
			}//for
		}
		else//����������
		{
			dir="��";
			for(i=0;i<interStation::count+1;i++)
			{
				if(i!=interStation::count)//�����յ�վ
				{
					tempT=arrayTime[i].timePlusMin(1);
					if(_t==arrayTime[i]||_t==tempT)
					{
						if(person[i])
						{
							out<<"ID"<<ID<<" "<<name<<" ���������� �ͳ����� "
								<<interStation::B2XArrayInterStop[i].name<<" վ "
								<<person[i]<<" λ�˿��³�!"
								<<" ���ڳ˿�"<<countPerson()<<"��"<<endl;	
							person[i]=0;
						}
						else
						{
							out<<"ID"<<ID<<" "<<name<<" ���������� �ͳ����� "
								<<interStation::B2XArrayInterStop[i].name<<" վ. ͣ��������"
								<<" ���ڳ˿�"<<countPerson()<<"��"<<endl;
						}
						break;
					}
					
					if(_t<arrayTime[i]) 
					{
						dist=(arrayTime[i].time2minute()-_t.time2minute())*speed;
						out<<"ID"<<ID<<" "<<name<<" ���������� �ͳ��� "
							<<interStation::B2XArrayInterStop[i].name<<" "<<dir<<" Լ "<<dist<<"���ﴦ."
							<<" ���ڳ˿�"<<countPerson()<<"��"<<endl;
						break;
					}
				
				}
				else//i==count�յ�վ
				{
					if(_t==arrayTime[i]) 
					{
						out<<"ID"<<ID<<" "<<name<<" ���������� �ͳ����������յ�վ."<<endl;
						person[i]=0;
						break;
					}
					if(_t<arrayTime[i])
					{
						dist=(arrayTime[i].time2minute()-_t.time2minute())*speed;
						out<<"ID"<<ID<<" "<<name<<" ���������� �ͳ��� "
							<<"���� "<<dir<<" Լ "<<dist<<"���ﴦ"
							<<" ���ڳ˿�"<<countPerson()<<"��"<<endl;
						break;					
					}
				}
			}//for
		}//else
		
	}
 

 

};


#endif