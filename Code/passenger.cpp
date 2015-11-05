/**
 * @attention Copyright (C), 2010, Xidian University.
 *
 * @file passenger.cpp
 * @author ��ӱ��
 * @date 2010/11/25
 * @brief passenger��
 * @version 1.0
 */
#ifndef PASSENGER_H_H
#define PASSENGER_H_H

#include<iostream>
#include<fstream>

using namespace std;

class passenger{

private:
	int direction;//�˿͵ĳ��з��� 1:���������� 0:����������
public:
	static 	int possibilityXB[6];
	static  int possibilityBX[6];
	unsigned SN;//�˿͵�վ�ĳ�վ���
public:
	passenger(){}


	static void getPossibility();

	

	passenger(int _b):direction(_b)
	{
		int i;	
		unsigned ranNum=ranWithin100();//����С��100���������ʼ��
		for(i=0;i!=6;i++)
		{
			if(direction)//����-����
			{	
				if(i==0&&ranNum<possibilityXB[i])//�жϳ�������������һ��ѭ���������ɵ��������ѯ����1վ�ĸ�������
												   //����һվ��SN=0
						break;
				if(ranNum>=possibilityXB[i-1]&&ranNum<possibilityXB[i])//�жϳ�������������һ��ѭ���������ɵ��������ѯ����iվ�ĸ�������
																		//����iվ��SN=i	
						break;
			}//if
			else
			{
				if(i==0&&ranNum<possibilityBX[i])//����һվ��SN=0
					break;
				if(ranNum>=possibilityBX[i-1]&&ranNum<possibilityBX[i])//����iվ��SN=i
					break;
			}//else
		}//for
		SN=i;
	}

	/* ����100���ڵ������*/
	unsigned ranWithin100()
	{		
		return ((unsigned)rand())%100;
	}


    /*ͣ��վ���ŵķ�����*/
	inline unsigned get_SN()
	{
		return SN;
	}


};

#endif