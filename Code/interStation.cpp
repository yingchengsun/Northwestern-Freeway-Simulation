/**
 * @attention Copyright (C), 2010, Xidian University.
 *
 * @file station.cpp
 * @author 孙颖成
 * @date 2010/11/25
 * @brief 中间站点类
 * @version 1.0
 */
#ifndef INTERSTATION_H_H
#define INTERSTATION_H_H

#include "station.h"
#include <iostream>
#include "vector"
#include <fstream>

using namespace std;

class interStation : public station{

public:	
	int dist2XaNext; //到西安方向邻近的站点的距离
	int dist2BjNext; //到宝鸡方向邻近的站点的距离
	int id;//站点id

	static unsigned count;	// 车站的数目
	const static vector<interStation> X2BArrayInterStop;	//静态变量，西安到宝鸡之间的中间站的车站信息和站间路程信息
	const static vector<interStation> B2XArrayInterStop; //静态变量，宝鸡到西安之间的中间站的车站信息和站间路程信息

public:
	

	/* 初始化中间站信息 */
	static vector<interStation>  initArrayStop(bool x2b)
	{
		ifstream fin("source\\interStation.txt");
		interStation tempStop;
		vector<interStation> tempVector1;
		vector<interStation> tempVector2;	
		fin>>count;
		for(int i=0;i!=count;i++)
		{		
			tempStop.id=i;
			fin>>tempStop.name>>tempStop.dist2BjNext>>tempStop.dist2XaNext;
			tempVector1.push_back(tempStop);
		}
		
		if(x2b)
			/*是西安-宝鸡方向*/
			return tempVector1;
		else
			/*否则对容器重新置反排列返回*/
		{
			for(vector<interStation>::size_type j=0;j!=count;j++)
				tempVector2.push_back(tempVector1[count-j-1]);
			return tempVector2;
		}	
		fin.close();	
	}


	/* 显示中间站点信息 */
	 static void  showInterStopInfo(ostream& out)
	{
		vector<interStation>::const_iterator it;
		out<<"**************************************************************\n"
			<<"                   "<<"西安——宝鸡高速公路路线图"<<endl<<endl;
		it=B2XArrayInterStop.begin();
		out<<"    宝鸡"<<" "<<it->dist2BjNext;//从宝鸡到西安依次列出站名和间隔距离
		for(;it!=B2XArrayInterStop.end();++it)
		{
			out<<" "<<it->name<<" "<<it->dist2XaNext;
		}
		out<<" "<<"西安";
		out<<endl;
		
	}
};
 
#endif
