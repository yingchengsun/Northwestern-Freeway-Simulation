/**
 * @attention Copyright (C), 2010, Xidian University.
 *
 * @file time.cpp
 * @author ��ӱ��
 * @date 2010/11/25
 * @brief time��
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
	/*���캯��*/
	time(){
		this->hour=0;
		this->minute=0;
	}
	/*���캯��*/
	time(int hour,int minute){
		this->hour=hour;
		this->minute=minute;
	}

	/*�鿴Сʱ*/
	int getHour(){
		return this->hour;
	}
	
	/*�鿴����*/
	int getMinute(){
		return this->minute;
	}

	/*ʱ�����*/
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


	/*ʱ��ӷ�*/
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

	/*ʱ��+=����*/
	time operator+=(const time& _t)
	{
		(*this)=(*this)+_t;
		return *this;
	}

	/*ʱ��<�Ƚ�*/
	bool operator<(const time& _t) const
	{
		if(this->time2minute()<_t.time2minute())
			return true;
		else return false;
	}

	/*ʱ��>�Ƚ�*/
	bool operator>(const time& _t) const
	{
		if(this->time2minute()>_t.time2minute())
			return true;
		else return false;
	}

	/*ʱ��>=�Ƚ�*/
	bool operator>=(const time& _t) const
	{
		if((*this)>_t||(*this)==_t)
			return true;
		else return false;
	}

	/*ʱ��<=�Ƚ�*/
	bool operator<=(const time& _t) const
	{
		if((*this)<_t||(*this)==_t)
			return true;
		else return false;
	}

	/*ʱ��==�Ƚ�*/
	bool operator==(const time& _t) const
	{
		if(this->time2minute()==_t.time2minute())
			return true;
		else 
			return false;
	}

    /*ʱ��ת���ɷ��ӵ�����*/
	int time2minute() const
	{
		return hour*60+minute;
	}

	/*ʱ��ӷ���*/
	time timePlusMin(int minute) const
	{
		time t=*this;
		t.hour+=((t.minute+minute)/60)%24;		
		t.minute=(t.minute+minute)%60;		
		return t;	
	}

	/*����ʱ������Ӧ���ַ���*/
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
