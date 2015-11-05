/**
 * @attention Copyright (C), 2010, Xidian University.
 *
 * @file main.cpp
 * @author ��ӱ��
 * @date 2010/11/25
 * @brief main����
 * @version 1.0
 */
#include "controller.cpp"
#include <iostream>
#include <fstream>
using namespace std;

unsigned interStation::count=1;	// ��վ����Ŀ
const vector<interStation> interStation::X2BArrayInterStop=initArrayStop(true);	//��̬����������������֮����м�վ�ĳ�վ��Ϣ��վ��·����Ϣ
const vector<interStation> interStation::B2XArrayInterStop=initArrayStop(false);//��̬����������������֮����м�վ�ĳ�վ��Ϣ��վ��·����Ϣ
static void getPossibility();

int passenger::possibilityXB[6]={0,0,0,0,0,0};//{5,10,15,17,23,30};

int passenger::possibilityBX[6]={0,0,0,0,0,0};//{11,4,17,15,24,29};

void  passenger::getPossibility()
	{
		ifstream fin;
		fin.open("source\\possXB.txt");	
		int i;
		
		for(i=0;i!=6;++i)
		{
			fin>>possibilityXB[i];
	
			if(i>0)
			{
				possibilityXB[i]+=possibilityXB[i-1];
				/*�Զ�ȡ�ĸ�����ֵ�����������������ʽ*/
			}		
		}
		fin.clear();
		fin.close();
		/*�ļ��رղ���*/
		fin.open("source\\possBX.txt");
		for(i=0;i!=6;++i)
		{	
			
			fin>>possibilityBX[i];

			if(i>0)
			{
				possibilityBX[i]+=possibilityBX[i-1];
			}		
		}
		fin.clear();
		fin.close();	
	}
int main(){

	ofstream fout;
	controller C;
	
	C.start(cout);
	/*����Ļ��������ͬʱҲ��������浽result.txt�ļ�����Ϊ����*/
	//fout.open("result\\result.txt");
	//C.start(fout);
	//fout.close();

	return 0;
}