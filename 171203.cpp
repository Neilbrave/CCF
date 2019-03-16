#include<iostream>
#include<vector>
#include<string.h> 
#include<stdlib.h>
using namespace std;

struct timeinfo {
	int year;
	int month;
	int day;
	int hour;
	int min;
	int date;
	void ass(int y, int m, int d, int h, int M,int dat)
	{
		year = y;
		month = m;
		day = d;
		hour = h;
		min = M;
		date = dat;
	}
	void output() {
		
		printf("%d", year);
		if (month >= 10)
			printf("%d", month);
		else
			printf("0%d", month);
		if (day >= 10)
			printf("%d", day);
		else
			printf("0%d", day);
		if (hour >= 10)
			printf("%d", hour);
		else
			printf("0%d", hour);
		if (min >= 10)
			printf("%d", min);
		else
			printf("0%d", min);
	}
	bool operator ==(timeinfo ipx) {
		return (year == ipx.year) && (month == ipx.month) && (day == ipx.day) && (hour == ipx.hour) && (min == ipx.min);
	}
};
struct cron {
	int min;
	int hour;
	int day;
	int mon;
	int date;
	char name[100];
	void output() {
		printf("CRON:%d %d %d %d %d %s\n", mon, day, hour, min, date,name);
	}
};
vector <cron> cronary;

int isruny(int y)
{
	if (y % 4 == 0)
		return 1;
	else return 0;
}
void time2info(timeinfo &tnod,int y, int m, int d, int h, int M) {
	int dayadd=0;
	int runy = 0;
	runy = isruny(y);
	if (m == 1)dayadd = d - 1;
	else if (m == 2)dayadd = d - 1 + 31;
	else if (m == 3)dayadd = d - 1 + 31 + 28 + runy;
	else if (m == 4)dayadd = d - 1 + 31 + 28 + runy+31;
	else if (m == 5)dayadd = d - 1 + 31 + 28 + runy+31+30;
	else if (m == 6)dayadd = d - 1 + 31 + 28 + runy+31+30+31;
	else if (m == 7)dayadd = d - 1 + 31 + 28 + runy+31+30+31+30;
	else if (m == 8)dayadd = d - 1 + 31 + 28 + runy+31+30+31+30+31;
	else if (m == 9)dayadd = d - 1 + 31 + 28 + runy + 31 + 30 + 31 + 30 + 31+31;
	else if (m == 10)dayadd = d - 1 + 31 + 28 + runy + 31 + 30 + 31 + 30 + 31+31+30;
	else if (m == 11)dayadd = d - 1 + 31 + 28 + runy + 31 + 30 + 31 + 30 + 31+31+30+31;
	else if (m == 12)dayadd = d - 1 + 31 + 28 + runy + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31+30;
	int yearadd;
	int runadd;
	if (y <= 1972)runadd = 0;
	else runadd = (y - 1972 - 1)/ 4 + 1;
	yearadd = (y - 1970) * 365 + runadd;
	int date;
	date = (4 + yearadd + dayadd) % 7;
	tnod.ass(y, m, d, h, M, date);
}
int datetrans(const	char *date) {
	string dates = date;
	if (dates == "Sun")return 0;
	if (dates == "Mon")return 1;
	if (dates == "Tue")return 2;
	if (dates == "Wed")return 3;
	if (dates == "Thu")return 4;
	if (dates == "Fri")return 5;
	if (dates == "Sat")return 6;
	else return -1;
}
int monthtrans(const char *mon) {
	string mons = mon;
	if (mons == "Jan")return 1;
	if (mons == "Feb")return 2;
	if (mons == "Mar")return 3;
	if (mons == "Apr")return 4;
	if (mons == "May")return 5;
	if (mons == "Jun")return 6;
	if (mons == "Jul")return 7;
	if (mons == "Aug")return 8;
	if (mons == "Sep")return 9;
	if (mons == "Oct")return 10;
	if (mons == "Nov")return 11;
	if (mons == "Dec")return 12;
	else return -1;
}
void clock_add(timeinfo &c) {
	c.min++;
	if (c.min == 60)
	{
		c.min = 0;
		c.hour++;
		if (c.hour == 24)
		{
			c.hour = 0;
			c.day++;
			c.date = (c.date + 1) % 7;
			if ((c.day == 32 && (c.month == 1 || c.month == 3 || c.month == 5 || c.month == 7 || c.month == 8 || c.month == 10 || c.month == 12))
				|| (c.day == 31 && (c.month == 4 || c.month == 6 || c.month == 9 || c.month == 11))
				|| (c.day == 29 && c.month == 2 && (!isruny(c.year)))
				|| (c.day == 30 && c.month == 2 && (isruny(c.year)))
				) {
				c.day = 1;
				c.month++;
				if (c.month == 13) {
					c.month = 1;
					c.year++;
				}
			}	
		}
	}
}
void add(vector <cron> &cronary, const char *min, const char *hour, const char *day, const char *month, const char *date,const char *name) {
	cron tmp;
	if (!strcmp(min, "*"))
		tmp.min = -1;
	else tmp.min = atoi(min);

	if (!strcmp(hour, "*"))
		tmp.hour = -1;
	else tmp.hour = atoi(hour);

	if (!strcmp(day, "*"))
		tmp.day = -1;
	else tmp.day = atoi(day);

	if (!strcmp(date, "*"))
		tmp.date = -1;
	else {
		if (date[0] >= '0'&&date[0] <= '6')
			tmp.date = atoi(date);
		else
			tmp.date = datetrans(date);
	}

	if (!strcmp(month, "*"))
		tmp.mon = -1;
	else{
		if (month[0] <= '9'&&month[0] >= '0')
			tmp.mon = atoi(month);
		else
			tmp.mon = monthtrans(month);
	}
		
	strcpy(tmp.name, name);
	//tmp.output();
	cronary.push_back(tmp);
}
void split(string s, string c, vector<string> &res) {//注意此处的传参方式 
	int pos1, pos2;
	pos1 = 0;
	pos2 = s.find(c, 0);
	while (pos2 != string::npos) {
		res.push_back(s.substr(pos1, pos2 - pos1));
		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.size())
	{
		res.push_back(s.substr(pos1));
	}
}

void split(string s, vector<string> &res) {//注意此处的传参方式 
	int pos,pos1, pos2;
	int flag = 0;
	pos = 0;
	pos1 = s.find(",", 0);
	pos2 = s.find("-",0);
	while (pos1 != string::npos||pos2 != string::npos) {
		if (pos1<pos2&&pos1!=string::npos)
		{
			res.push_back(s.substr(pos, pos1 - pos));
			pos = pos1 + 1;
			pos1 = s.find(",", pos);			
		}
		else{
			s 
		}

	}
	if (pos1 != s.size())
	{
		res.push_back(s.substr(pos1));
	}
}
void insert_cron(vector <cron> &cronary, char *min, char *hour,char *day,char *month,char *date,char *name) {
	vector<string> nmin;
	vector<string> nhour;
	vector<string> nday;
	vector<string> nmonth;
	vector<string> ndata;
	int  mini=0, houri=0, dayi=0, monthi=0, datei=0;
	split(min, ",", nmin);
	split(hour, ",", nhour);
	split(day, ",", nday);
	split(month, ",", nmonth);
	split(date, ",", ndata);
	for (mini = 0; mini < nmin.size(); mini++)
	{
		for (houri = 0; houri < nhour.size(); houri++)
		{
			for (dayi = 0; dayi < nday.size(); dayi++)
			{
				for (monthi = 0; monthi < nmonth.size(); monthi++)
				{
					for (datei = 0; datei < ndata.size(); datei++)
					{
					add(cronary, nmin[mini].c_str(), nhour[houri].c_str(), nday[dayi].c_str(), nmonth[monthi].c_str(), ndata[datei].c_str(), name);
					}
				}
			}
		}
	}
	
}

//void split(string s, vector<string>&res, int beg, int end) {
//	int pos, pos1, pos2;
//	pos = 0;
//	pos1 = s.find(",", 0);
//	pos2 = s.find("-", 0);
//	while ((pos1 != string::npos) || (pos2 != s.find("-", 0)))
//	{
//		if ((pos1 != string::npos) && (pos2 != s.find("-", 0)))
//		{
//			if (pos1 < pos2) {
//				res.push_back(s.substr(pos, pos1 - pos));
//				pos = pos1 + 1;
//				pos1 = s.find(",", pos);
//			}
//			else
//			{
//				
//			}
//				
//		}
//	}
//}



void crotest(timeinfo &clock,cron &cnod)
{
	if ((cnod.mon == -1 || clock.month == cnod.mon) && (cnod.day == -1 || clock.day == cnod.day)
		&& (cnod.hour == -1 || clock.hour == cnod.hour) && (cnod.min == -1 || clock.min == cnod.min)
		&& (cnod.date == -1 || clock.date == cnod.date))
	{
		clock.output();
		printf(" %s\n", cnod.name);
	}
}
int main()
{
	int i;
	int n, s, t;
	int yyyy, mm, dd, hh, MM;
	timeinfo ttmp;
	timeinfo sta;
	timeinfo endt;
	scanf("%d", &n);
	scanf("%4d%2d%2d%2d%2d", &yyyy, &mm, &dd, &hh, &MM);
	time2info(sta, yyyy, mm, dd, hh, MM);
	scanf("%4d%2d%2d%2d%2d", &yyyy, &mm, &dd, &hh, &MM);
	time2info(endt, yyyy, mm, dd, hh, MM);
	//sta.output();
	//endt.output();
	char min[100];
	char hour[100];
	char day[100];
	char mon[100];
	char date[100];
	char name[100];
	for (i = 0; i < n; i++)
	{
		scanf("%s %s %s %s %s %s", min, hour, day, mon, date,name);
		insert_cron(cronary, min, hour, day, mon, date,name);
	}
	for (; !(sta == endt); clock_add(sta))
	{
		for (i = 0; i < cronary.size(); i++) {
			crotest(sta, cronary[i]);
		}
	}
	return 0;
}
