/**
 * @attention Copyright (C), 2010, Xidian University.
 *
 * @file main.cpp
 * @author 孙颖成
 * @date 2010/11/25
 * @brief main函数
 * @version 1.0
 */
#include "controller.cpp"
#include <iostream>
#include <fstream>
using namespace std;

unsigned interStation::count=1;	// 车站的数目
const vector<interStation> interStation::X2BArrayInterStop=initArrayStop(true);	//静态变量，西安到宝鸡之间的中间站的车站信息和站间路程信息
const vector<interStation> interStation::B2XArrayInterStop=initArrayStop(false);//静态变量，宝鸡到西安之间的中间站的车站信息和站间路程信息
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
				/*对读取的概率数值做处理，区成区间的形式*/
			}		
		}
		fin.clear();
		fin.close();
		/*文件关闭操作*/
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
	/*在屏幕输出结果的同时也将结果保存到result.txt文件中作为备份*/
	//fout.open("result\\result.txt");
	//C.start(fout);
	//fout.close();

	return 0;
}