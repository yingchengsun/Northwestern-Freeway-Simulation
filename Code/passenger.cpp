/**
 * @attention Copyright (C), 2010, Xidian University.
 *
 * @file passenger.cpp
 * @author 孙颖成
 * @date 2010/11/25
 * @brief passenger类
 * @version 1.0
 */
#ifndef PASSENGER_H_H
#define PASSENGER_H_H

#include<iostream>
#include<fstream>

using namespace std;

class passenger{

private:
	int direction;//乘客的出行方向 1:西安到宝鸡 0:宝鸡到西安
public:
	static 	int possibilityXB[6];
	static  int possibilityBX[6];
	unsigned SN;//乘客到站的车站编号
public:
	passenger(){}


	static void getPossibility();

	

	passenger(int _b):direction(_b)
	{
		int i;	
		unsigned ranNum=ranWithin100();//利用小于100的随机数初始化
		for(i=0;i!=6;i++)
		{
			if(direction)//西安-宝鸡
			{	
				if(i==0&&ranNum<possibilityXB[i])//判断成立的条件：第一次循环并且生成的随机数轮询到第1站的概率区间
												   //到第一站，SN=0
						break;
				if(ranNum>=possibilityXB[i-1]&&ranNum<possibilityXB[i])//判断成立的条件：第一次循环并且生成的随机数轮询到第i站的概率区间
																		//到第i站，SN=i	
						break;
			}//if
			else
			{
				if(i==0&&ranNum<possibilityBX[i])//到第一站，SN=0
					break;
				if(ranNum>=possibilityBX[i-1]&&ranNum<possibilityBX[i])//到第i站，SN=i
					break;
			}//else
		}//for
		SN=i;
	}

	/* 生成100以内的随机数*/
	unsigned ranWithin100()
	{		
		return ((unsigned)rand())%100;
	}


    /*停车站点编号的访问器*/
	inline unsigned get_SN()
	{
		return SN;
	}


};

#endif