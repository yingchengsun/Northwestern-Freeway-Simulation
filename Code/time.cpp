/**
 * @attention Copyright (C), 2010, Xidian University.
 *
 * @file time.cpp
 * @author 孙颖成
 * @date 2010/11/25
 * @brief time类
 * @version 1.0
 */
#ifndef time_H_H
#define time_H_H

#include "sstream"
#include <iostream>
#include <string>
using namespace std;

class time{
private:
	int hour;
	int minute;

public:
	/*构造函数*/
	time(){
		this->hour=0;
		this->minute=0;
	}
	/*构造函数*/
	time(int hour,int minute){
		this->hour=hour;
		this->minute=minute;
	}

	/*查看小时*/
	int getHour(){
		return this->hour;
	}
	
	/*查看分钟*/
	int getMinute(){
		return this->minute;
	}

	/*时间减法*/
	time operator-(const time& _t) const
	{
		time t;
		if(this->minute<_t.minute)
		{
			t.hour=this->hour-_t.hour-1;
			t.minute=this->minute+60-_t.minute;

		}
		else
		{
			t.hour=this->hour-_t.hour;
			t.minute=this->minute-_t.minute;
		}	
		return t;
	}


	/*时间加法*/
	time operator+(const time& _t) const
	{
		time t;
		if(this->minute+_t.minute<60)
		{
			t.hour=this->hour+_t.hour;
			t.minute=this->minute+_t.minute;
				
		}
		else
		{
			t.hour=this->hour+_t.hour-1;
			t.minute=this->minute+_t.minute-60;
		}	
		return t;
	}

	/*时间+=操作*/
	time operator+=(const time& _t)
	{
		(*this)=(*this)+_t;
		return *this;
	}

	/*时间<比较*/
	bool operator<(const time& _t) const
	{
		if(this->time2minute()<_t.time2minute())
			return true;
		else return false;
	}

	/*时间>比较*/
	bool operator>(const time& _t) const
	{
		if(this->time2minute()>_t.time2minute())
			return true;
		else return false;
	}

	/*时间>=比较*/
	bool operator>=(const time& _t) const
	{
		if((*this)>_t||(*this)==_t)
			return true;
		else return false;
	}

	/*时间<=比较*/
	bool operator<=(const time& _t) const
	{
		if((*this)<_t||(*this)==_t)
			return true;
		else return false;
	}

	/*时间==比较*/
	bool operator==(const time& _t) const
	{
		if(this->time2minute()==_t.time2minute())
			return true;
		else 
			return false;
	}

    /*时间转化成分钟的整形*/
	int time2minute() const
	{
		return hour*60+minute;
	}

	/*时间加分钟*/
	time timePlusMin(int minute) const
	{
		time t=*this;
		t.hour+=((t.minute+minute)/60)%24;		
		t.minute=(t.minute+minute)%60;		
		return t;	
	}

	/*返回时间所对应的字符串*/
	string get_TimeStr() const 
	{
		ostringstream format_temStr;
		if(hour<10)
		{
			if(minute<10)
				format_temStr<<"0"<<hour<<":"<<"0"<<minute;
			else
				format_temStr<<"0"<<hour<<":"<<minute;
		}
		else
		{
			if(minute<10)
				format_temStr<<hour<<":"<<"0"<<minute;
			else
				format_temStr<<hour<<":"<<minute;
		}

		return format_temStr.str();
	}

};
#endif
