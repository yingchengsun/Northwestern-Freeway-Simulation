/**
 * @attention Copyright (C), 2010, Xidian University.
 *
 * @file bus.cpp
 * @author 孙颖成
 * @date 2010/11/25
 * @brief Bus类
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
	int ID; //车号
	int limit; //车上可装的最大人数
	double speed; //车速
	int direction; //车的行驶方向 1:西安到宝鸡 0:宝鸡到西安
	string type; //车型 
	time startTime;//发车时间
	int person[6];//每站下车人数
	time arrayTime[6];//车到每一站的时间
	string name;//车名

	static unsigned count;	// 车站的数目
	const static vector<interStation> X2BArrayInterStop;	//静态变量，西安到宝鸡之间的中间站的车站信息和站间路程信息
	const static vector<interStation> B2XArrayInterStop; //静态变量，宝鸡到西安之间的中间站的车站信息和站间路程信息

public:
	bus(){
	}
	
	/*构造函数*/
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

	/*修改发车时间*/
	inline void set_startTime(time _t)
	{
		startTime=_t;
	}

	/*读取发车时间*/	
	inline time get_startTime(){
		return startTime;
	}
	/*读取车到终点站的时间*/
	inline time stopTime()
	{
		return arrayTime[5];
	}

	/*读取车到各站点的时间*/
	inline void showStopTime()
	{
		
		cout<<ID<<" ";
		for(int i=0;i!=6;++i)
		{
			
			cout<<arrayTime[i].get_TimeStr()<<" ";
		}
		cout<<endl;
	}

	/*读取车的ID*/
	int get_id(){
		return this->ID;
	}

	/*读取车的类型*/
	inline string get_kind()
	{
		return type;
	}

	/*清空所有乘客*/
	inline void perReset()
	{		
		for(int i=0;i!=interStation::count+1;i++)
		{
			person[i]=0;
		}		
	}



	/*乘客下车*/
	inline int personAccess(int index,int incre){

		person[index]+=incre;
		return person[index];
	}

	/*计算车内乘客人数*/
	inline int countPerson()
	{
		return person[0]+person[1]+person[2]+person[3]+person[4]+person[5];		
	}


	/*判断车内是否已满*/
	inline bool isFull()
	{
		return (countPerson()==limit);
	}


	/*汽车发车*/
	void start()
	{
		time t=startTime;
		unsigned i;
		if(direction)//西安—宝鸡
		{		
			for(i=0;i!=interStation::count;i++)
			{
				t=t.timePlusMin((interStation::X2BArrayInterStop[i].dist2XaNext)/speed);
				/*起始时间+每一段路程需要的时间作为到下一站的时间*/
				arrayTime[i]=t;
				
				if(person[i])
				/*若到站停车则时间+2分钟*/
				{
					t=t.timePlusMin(2);
				}//if
			}//for
			arrayTime[i]=t.timePlusMin((interStation::X2BArrayInterStop[i-1].dist2BjNext)/speed);//count中只存了中间站数目
			/*计算到终点站时间*/
		}//if
		else//宝鸡—西安
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



	//显示汽车当前状态信息
	void showStatic(ostream& out,time _t)
	{
		int i;
		string dir;//方向：东；西
		double dist;
		time tempT;//临时时间变量

		if(direction)//西安—宝鸡
		{
			dir="东";
			for(i=0;i<interStation::count+1;i++)
			{
				if(i!=interStation::count)//不到终点站
				{
					tempT=arrayTime[i].timePlusMin(1);//若到车站需要停车两分钟，故增加一个判断条件
					if(_t==arrayTime[i]||_t==tempT)//就在i车站
					{
						if(person[i])//有人在该站下车
						{
							out<<"ID"<<ID<<" "<<name<<" 西安—宝鸡 客车到达 "
								<<interStation::X2BArrayInterStop[i].name<<" 站 "
								<<person[i]<<" 位乘客下车!"
								<<" 车内乘客"<<countPerson()<<"人"<<endl;	
							person[i]=0;//车上到该站的乘客人数清0
						}//if
						else/*person[i]==0*/
						{
							out<<"ID"<<ID<<" "<<name<<" 西安—宝鸡 客车到达 "
								<<interStation::X2BArrayInterStop[i].name<<" 站. 停车两分钟"
								<<" 车内乘客"<<countPerson()<<"人"<<endl;
						}//else
						break;
					}//if
					
					if(_t<arrayTime[i])//没到i车站
					{
						dist=(arrayTime[i].time2minute()-_t.time2minute())*speed;
						/*计算当前位置到下一站的距离*/
						out<<"ID"<<ID<<" "<<name<<" 西安—宝鸡 客车在 "
							<<interStation::X2BArrayInterStop[i].name<<" "<<dir<<" 约 "
							<<dist<<"公里处"
							<<" 车内乘客"<<countPerson()<<"人"<<endl;
						break;
					}//if
				}//if
				
				else/*终点站i==count*/
				{
					if(_t==arrayTime[i])//就在i车站
					{
						out<<"ID"<<ID<<" "<<name<<" 西安—宝鸡 客车到达宝鸡终点站."<<endl;
						person[i]=0;//车上到该站的乘客人数清0
						break;
					}
					if(_t<arrayTime[i])
					{
						dist=(arrayTime[i].time2minute()-_t.time2minute())*speed;
						out<<"ID"<<ID<<" "<<name<<" 西安—宝鸡 客车在 "
							<<"宝鸡 "<<dir<<" 约 "<<dist<<"公里处"
							<<" 车内乘客"<<countPerson()<<"人"<<endl;
						break;					
					}
				}//else
			}//for
		}
		else//宝鸡—西安
		{
			dir="西";
			for(i=0;i<interStation::count+1;i++)
			{
				if(i!=interStation::count)//不到终点站
				{
					tempT=arrayTime[i].timePlusMin(1);
					if(_t==arrayTime[i]||_t==tempT)
					{
						if(person[i])
						{
							out<<"ID"<<ID<<" "<<name<<" 宝鸡—西安 客车到达 "
								<<interStation::B2XArrayInterStop[i].name<<" 站 "
								<<person[i]<<" 位乘客下车!"
								<<" 车内乘客"<<countPerson()<<"人"<<endl;	
							person[i]=0;
						}
						else
						{
							out<<"ID"<<ID<<" "<<name<<" 宝鸡—西安 客车到达 "
								<<interStation::B2XArrayInterStop[i].name<<" 站. 停车两分钟"
								<<" 车内乘客"<<countPerson()<<"人"<<endl;
						}
						break;
					}
					
					if(_t<arrayTime[i]) 
					{
						dist=(arrayTime[i].time2minute()-_t.time2minute())*speed;
						out<<"ID"<<ID<<" "<<name<<" 宝鸡—西安 客车在 "
							<<interStation::B2XArrayInterStop[i].name<<" "<<dir<<" 约 "<<dist<<"公里处."
							<<" 车内乘客"<<countPerson()<<"人"<<endl;
						break;
					}
				
				}
				else//i==count终点站
				{
					if(_t==arrayTime[i]) 
					{
						out<<"ID"<<ID<<" "<<name<<" 宝鸡—西安 客车到达西安终点站."<<endl;
						person[i]=0;
						break;
					}
					if(_t<arrayTime[i])
					{
						dist=(arrayTime[i].time2minute()-_t.time2minute())*speed;
						out<<"ID"<<ID<<" "<<name<<" 宝鸡—西安 客车在 "
							<<"西安 "<<dir<<" 约 "<<dist<<"公里处"
							<<" 车内乘客"<<countPerson()<<"人"<<endl;
						break;					
					}
				}
			}//for
		}//else
		
	}
 

 

};


#endif