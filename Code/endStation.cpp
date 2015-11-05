/**
 * @attention Copyright (C), 2010, Xidian University.
 *
 * @file station.cpp
 * @author 孙颖成
 * @date 2010/11/25
 * @brief 终点站类
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
	int numVolvo;//最大的Volvo车辆数
	int numIveco;//最大的Iveco车辆数
	int numPassPerMin;//每分钟产生的最多乘客数

	list<bus>::iterator it_V;//volve车队列的迭代器
	list<bus>::iterator it_I;//iveco车队列的迭代器

	list<bus> lvBus;
	list<bus> liBus;
	

	time lvtLastBus;//volve汽车队列的最后一个汽车的出发时间
	time litLastBus;//iveco汽车队列的最后一个汽车的出发时间
public:
	 time VStartT;//volve发车时间
	 time VStopT;//volve停车时间
	 time IStartT;//iveco发车时间
	 time IStopT;//iveco停车时间

	list<passenger> lPass;//乘客队列
	list<bus> lOnwayBus;
public:


	//构造函数
	endStation(string name):VStartT(8,30),VStopT(17,30),IStartT(8,0),IStopT(18,00){
		ifstream fin;
		/*从文件读入当前车站具有的Volvo，Iveco，乘客的数目*/	
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
		int temp_b=0;//0表示宝鸡，1表示西安
		/*初始化哪个站生成的汽车的标志位，false代表宝鸡站*/

		time tv(8,30);//volve发车时间
		time ti(8,0);//iveco发车时间

		for(i=0;i<numVolvo;++i)
		{/*生成Volvo*/
			if(tv>VStopT)
			{	//若时间大于停车时间则不再生成
				break;
			}
			temp_b=0;
			if("XN"==name)
			{
				tempId=1000;//用于初始化汽车id的临时整形数
				temp_b=1;
			}
			bus temVolvo("volve",(i+100+tempId),temp_b);//生成汽车
			temVolvo.set_startTime(tv);
			lvBus.push_back(temVolvo);//将新生成的汽车加入汽车队列	
		
			lvtLastBus=tv;//设置汽车队列的最后一个汽车的出发时间
			
			tv=tv.timePlusMin(60);//时间增加60分钟 
		}

		for(i=0;i<numIveco;++i)
		{
			/*生成Iveco*/
			if(ti>IStopT)
			{	//若时间大于停车时间则不再生成
				break;
			}
			tempId=2000;
			temp_b=0;
			if("XN"==name)
			{
				tempId=1000;//用于初始化汽车id的临时整形数
				temp_b=1;

			}
			bus temIveco("iveco",(i+200+tempId),temp_b);//生成汽车

			temIveco.set_startTime(ti);
			liBus.push_back(temIveco);//将新生成的汽车加入汽车队列
			litLastBus=ti;//设置汽车队列的最后一个汽车的出发时间

			ti=ti.timePlusMin(20);//时间增加20分钟 
		}

		it_V=lvBus.begin();//初始化Volvo汽车列表的迭代器，指向列表中最后一个未满的汽车
		it_I=liBus.begin();//初始化Iveco汽车列表的迭代器，指向列表中最后一个未满的汽车
	} 


	/*随机生成0-numPassPerMin间数目的乘客*/
	void generatePassenger(int direct){		
		for(int i=0; i<((unsigned)rand())%numPassPerMin+1; i++){
			if(direct==1){
				passenger temPass(1);	
				lPass.push_back(temPass);//加入新乘客
			}else
			{
				passenger temPass(0);
				lPass.push_back(temPass);//加入新乘客
			}
			
		}	
	}

	void regeditPass(bus& _b){	
		_b.personAccess(lPass.front().get_SN(),1);
		/*乘客上车*/
		lPass.pop_front();
		/*乘客出等车队列*/
		
	}

    inline void refreshIter(list<bus>::iterator& _it)
	{
		if(_it->isFull())
		/*若当前汽车满，则迭代器指向下一汽车*/
			++_it;		
	}

	void getOn(){

		while(!lPass.empty()){	//队列非空
			
		 	if(it_V==lvBus.end()&&it_I==liBus.end()){//车队都上满了，退出循环
				break;
			}

			if(it_V!=lvBus.end()&&it_I==liBus.end()){//volvo未满，上Volvo
				regeditPass(*it_V);	//乘客列表的第一个人上车，并且出队
				refreshIter(it_V);//更新Volvo车队的指向最后一个未满车的迭代器
				continue;
			}

			if(it_V==lvBus.end()&&it_I!=liBus.end()){//Iveco未满，上Iveco
				regeditPass(*it_I);//乘客列表的第一个人上车，并且出队
				refreshIter(it_I);//更新Iveco车队的指向最后一个未满车的迭代器
				continue;
			}
		
			if(it_V->get_startTime()<it_I->get_startTime()){//全未满
				//若Volvo的发车时间比Iveco的发车时间早，上Volvo	
				regeditPass(*it_V);	//乘客列表的第一个人上车，并且出队
				refreshIter(it_V);//更新Iveco车队的指向最后一个未满车的迭代器
				continue;			
			}
		
			if(it_I->get_startTime()<it_V->get_startTime()){//全未满
				//若Iveco的发车时间比Volvo的发车时间早，上Iveco
				regeditPass(*it_I);	//乘客列表的第一个人上车，并且出队
				refreshIter(it_I); //更新Iveco车队的指向最后一个未满车的迭代器
				continue;
			} 
			 
		}//while
	}//getOn

	
	/*启动Volvo汽车*/
	void  startVolvo()
	{
		if(!lvBus.empty())
		{
			/*汽车队列非空*/
			if(it_V==lvBus.begin())
			{
				++it_V;//若开走的是最后一个未满的汽车，则将迭代器指向下一个汽车
			}
			lvBus.front().start();//队头汽车开车
			lOnwayBus.push_back(lvBus.front());//此汽车加入此车站正在路上行的汽车的车队
			lvBus.pop_front();//将此汽车从出发车站的队列删除*/
		}
	}


		
	/*启动Volvo汽车*/
	void startIveco()
	{
		if(!liBus.empty())
		{
			/*汽车队列非空*/
			if(it_I==liBus.begin())
			{				
				++it_I;//若开走的是最后一个未满的汽车，则将迭代器指向下一个汽车
			}
				
			liBus.front().start();//队头汽车开车
			lOnwayBus.push_back(liBus.front());//此汽车加入此车站正在路上行的汽车的车队
			liBus.pop_front();//将此汽车从出发车站的队列删除*/
		}
	}
	
	/*显示西安或宝鸡车站内的信息*/
	void showStationInfo(ostream& out)
	{
		int tempBN,tempPN=0;
		list<bus>::iterator it;
		
		if (name=="XN")
			name="西安";
		if (name=="BJ")
			name="宝鸡";

		//输出Volvo车辆信息，并且计算Volvo车上的乘客数目
		if((tempBN=lvBus.size())>=1)		
		{
			out<<name<<" 车站有 "<<tempBN<<" 辆沃尔沃车."<<endl;
		}
		else
		{	
			out<<name<<"车站没有沃尔沃车. "<<endl;
		}
		/*输出Volvo车辆信息*/
		for(it=lvBus.begin();it!=lvBus.end();++it)
		{
			out<<"  沃尔沃 ID:"<<it->get_id()<<"..车内乘客人数:"<<it->countPerson()<<" 发车时间:"<<it->get_startTime().get_TimeStr()<<endl;
			tempPN+=it->countPerson();
		}
		
		out<<endl;
		
		//输出Iveco车辆信息，并且计算Iveco车上的乘客数目
		if((tempBN=liBus.size())>=1)		
		{
			out<<name<<" 车站有 "<<tempBN<<" 辆依维柯车."<<endl;
		}
		else
		{	
			out<<name<<" 车站没有依维柯车. "<<endl;
		}
		
		
		for(it=liBus.begin();it!=liBus.end();++it)
		{
			out<<"  依维柯 ID:"<<it->get_id()<<"..车内乘客人数:"<<it->countPerson()<<" 发车时间:"<<it->get_startTime().get_TimeStr()<<endl;
			tempPN+=it->countPerson();
		}	
		
		out<<endl;

		//输出乘客信息
		if((tempPN+=lPass.size())>=1)	
		{
			out<<name<<" 车站有 "<<tempPN<<" 位乘客."<<endl;
		}
		else
		{	
			out<<name<<"车站没有乘客. "<<endl;
		}
		
	}


	/*显示路上行车信息*/
	void showOnwayInfo(ostream& out,time _t)
	{
		list<bus>::iterator it;

		if(lOnwayBus.empty())
		{
			/*若行车队列为空，则无汽车*/
			if(name=="西安") 
				out<<"西安—宝鸡路上没有汽车!"<<endl;
			if(name=="宝鸡") 
				out<<"宝鸡—西安路上没有汽车!"<<endl;	
			return;
			/*返回*/
		}

		for(it=lOnwayBus.begin();it!=lOnwayBus.end();++it)
		{
			it->showStatic(out,_t);
			/*对于每一辆车，输出车的当前信息*/
		}	
	}



	void getIntoStation(endStation& _ss,time _t)
	{
		time tempT;
		list<bus>::iterator it;

		for(it=lOnwayBus.begin();it!=lOnwayBus.end();)//对于路上每一辆车做处理
		{			
			if(it->stopTime()==_t)//若当前时间为最后停车时间
			{
				it->perReset();//车的乘客数清零
				if(it->get_kind()=="volve") 
				{
						//Volvo
						tempT=_ss.lvtLastBus;
						/*计算欲入队列的最后一个车发车时间*/
						do
						{	
							tempT=tempT.timePlusMin(60);//volve每隔一小时发一班车
						}while(tempT<=it->stopTime());
						
						if(tempT>VStopT)
						{		
							/*若求出的发车时间大于最晚发车时间则，什么都不做*/
						}
						else
						{	/*若求出的发车时间小于最晚发车时间则，做如下处理*/		
							it->set_startTime(tempT);//设置再次发车时间
							_ss.lvBus.push_back(*it);//加入进入车站的对应的汽车发车队列
							_ss.lvtLastBus=tempT;//设置该队列的最后一辆车的发车时间

							if(it_V==lvBus.end())
							{
								it_V==endLast(lvBus);//更新迭代器，将it_v设置为最后一个有效元素的迭代器
							}
						}			
						break;
				}
				if(it->get_kind()=="iveco") 
				{		
						//Iveco
						tempT=_ss.litLastBus;
						/*计算欲入队列的最后一个车发车时间*/
						do
						{								
							tempT=tempT.timePlusMin(20);//iveco每隔20分钟发一班车
						}while(tempT<=it->stopTime());
						
						if(tempT>IStopT)
						{	
							/*若求出的发车时间大于最晚发车时间则，什么都不做*/
						}
						else
						{		
							/*若求出的发车时间小于最晚发车时间则，做如下处理*/	
							it->set_startTime(tempT);//设置再次发车时间
							_ss.liBus.push_back(*it);//加入进入车站的对应的汽车发车队列
							_ss.litLastBus=tempT;//设置该队列的最后一辆车的发车时间*/

							if(it_I==liBus.end())
							{							
								it_I==endLast(liBus);//更新迭代器，将it_v设置为最后一个有效元素的迭代器
							}
						}				
						break;				
				}

				it=lOnwayBus.erase(it);//将此车从行车队列中删除*/
				continue;
			}//if
			++it;
		}//for
	}

	/*更新迭代器*/
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