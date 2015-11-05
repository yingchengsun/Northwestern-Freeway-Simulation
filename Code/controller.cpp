/**
 * @attention Copyright (C), 2010, Xidian University.
 *
 * @file controller.cpp
 * @author 孙颖成
 * @date 2010/11/25
 * @brief 控制器类
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

	//流程模拟方法
	void start(ostream& out)
	{
		
		time currentTime(7,29);// 初始化当前时间07:29
		time upTimeLimit(7,29);// 乘客到来的时间上限
		time lowTimeLimit(18,0);// 乘客到来的时间下限

		char choice;//程序启动开关

		endStation XN("XN");//西安终点站
		endStation BJ("BJ");//宝鸡终点站

		list<bus> xnList;//西安站内车的队列
		list<bus> bjList;//宝鸡站内车的队列

		passenger::getPossibility();
	

		/* 程序界面显示的信息  */

		//显示中间站点信息
		interStation::showInterStopInfo(out);
		
		out<<"**************************************************************"<<endl;
		out<<"                     "<<"客车ID形式说明"<<endl<<endl;

		out<<"    西安客运站的客车：1xxx ;"<<"  "<<"宝鸡客运站的客车：2xxx ;\n"
			<<"    沃尔沃客车：x1xx ;"<<"         "<<"依维柯客车：x2xx;"<<endl;

		out<<"**************************************************************"<<endl;

		//客运活动的当前时刻
		out<<"                     当前时间是"<<currentTime.get_TimeStr()<<endl;
		out<<"**************************************************************"<<endl;


		out<<"                     车站信息"<<endl<<endl;
		//显示西安站内客车情况（车型和编号）、等车的乘客人数
		XN.showStationInfo(out);
		out<<endl<<"*------------------------------------------------------*"<<endl;
		
		//显示宝鸡站内客车情况（车型和编号）、等车的乘客人数
		BJ.showStationInfo(out);

		/*显示路上行车信息*/
		out<<endl<<"**************************************************************"<<endl;
		out<<"                     路上信息"<<endl<<endl;
		XN.showOnwayInfo(out,currentTime);
		out<<"*------------------------------------------------------*"<<endl;
		BJ.showOnwayInfo(out,currentTime);
	
		/*处理进站车辆*/	
		XN.getIntoStation(BJ,currentTime);
		BJ.getIntoStation(XN,currentTime);
	
		/*当前时间加1分*/
		currentTime=currentTime.timePlusMin(1);

		out<<"是否开始运行程序?  "<<"y:运行  n:退出"<<endl;
		cin>>choice;
		if(choice=='n')
			return;

		/* 程序正式运行显示的信息  */

		while(true){
		
			out<<"**************************************************************"<<endl;

			//客运活动的当前时刻
			out<<"                     当前时间是"<<currentTime.get_TimeStr()<<endl;
			out<<"**************************************************************"<<endl;
			
			/*若在规定时间内，则乘客上车*/
			if(currentTime>upTimeLimit&&currentTime<lowTimeLimit)
			{
			
				XN.generatePassenger(1);					
				XN.getOn();
				BJ.generatePassenger(0);
				BJ.getOn();
			}

			/*若当前时间是volve发车时间则发volve*/
			if(currentTime>=XN.VStartT&&currentTime<=XN.VStopT&&currentTime.getMinute()==30)
			{	
				XN.startVolvo();
				BJ.startVolvo();
			}

			/*若当前时间是iveco发车时间则发iveco*/
			if(currentTime>=XN.IStartT&&currentTime<=XN.IStopT&&(currentTime.getMinute()%20)==0)

			{
				XN.startIveco();
				BJ.startIveco();
			}
			
			out<<"                     车站信息"<<endl<<endl;
			//显示西安站内客车情况（车型和编号）、等车的乘客人数
			XN.showStationInfo(out);
			out<<endl<<"*------------------------------------------------------*"<<endl;
			
			//显示宝鸡站内客车情况（车型和编号）、等车的乘客人数
			BJ.showStationInfo(out);

			/*显示路上行车信息*/
			out<<endl<<"**************************************************************"<<endl;
			out<<"                     路上信息"<<endl<<endl;
			XN.showOnwayInfo(out,currentTime);
			out<<"*------------------------------------------------------*"<<endl;
			BJ.showOnwayInfo(out,currentTime);
		
			/*处理进站车辆*/	
			XN.getIntoStation(BJ,currentTime);
			BJ.getIntoStation(XN,currentTime);
		
			/*当前时间加1分*/
			currentTime=currentTime.timePlusMin(1);

			/*若当前时间为18:01,则解散等车乘客*/
			if(currentTime==time(18,1))
			
			{
				XN.lPass.clear();
				BJ.lPass.clear();
				out<<"*---------------------------------------------------------------------*\n"
					<<"车站内已没有可发车辆，乘客全部离开。"<<endl;
				
			}
		
			/*若现在已经过了发成时间，并且路上已经没有车则退出循环，模拟结束*/
			if(currentTime>XN.IStopT&&XN.lOnwayBus.empty()&&BJ.lOnwayBus.empty())
					break;
			
			/*等待1s，便于观察结果*/
			Sleep(1000);			
		}//while
		out<<"***************************************************************\n"
					<<"            当天客运已经结束，谢谢~~"<<endl;
	}//start

};
	
#endif






















