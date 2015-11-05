/**
 * @attention Copyright (C), 2010, Xidian University.
 *
 * @file station.cpp
 * @author ��ӱ��
 * @date 2010/11/25
 * @brief �м�վ����
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
	int dist2XaNext; //�����������ڽ���վ��ľ���
	int dist2BjNext; //�����������ڽ���վ��ľ���
	int id;//վ��id

	static unsigned count;	// ��վ����Ŀ
	const static vector<interStation> X2BArrayInterStop;	//��̬����������������֮����м�վ�ĳ�վ��Ϣ��վ��·����Ϣ
	const static vector<interStation> B2XArrayInterStop; //��̬����������������֮����м�վ�ĳ�վ��Ϣ��վ��·����Ϣ

public:
	

	/* ��ʼ���м�վ��Ϣ */
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
			/*������-��������*/
			return tempVector1;
		else
			/*��������������÷����з���*/
		{
			for(vector<interStation>::size_type j=0;j!=count;j++)
				tempVector2.push_back(tempVector1[count-j-1]);
			return tempVector2;
		}	
		fin.close();	
	}


	/* ��ʾ�м�վ����Ϣ */
	 static void  showInterStopInfo(ostream& out)
	{
		vector<interStation>::const_iterator it;
		out<<"**************************************************************\n"
			<<"                   "<<"���������������ٹ�··��ͼ"<<endl<<endl;
		it=B2XArrayInterStop.begin();
		out<<"    ����"<<" "<<it->dist2BjNext;//�ӱ��������������г�վ���ͼ������
		for(;it!=B2XArrayInterStop.end();++it)
		{
			out<<" "<<it->name<<" "<<it->dist2XaNext;
		}
		out<<" "<<"����";
		out<<endl;
		
	}
};
 
#endif
