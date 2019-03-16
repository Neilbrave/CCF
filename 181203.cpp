#include<algorithm>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include<vector>
using namespace std; 
//这一题的关键在于进行合并时，需要对ip的值进行比较，故需要将字符串转化成数值才醒
//第一种方法是使用：int atoi(const char *nptr);
//就需要先把字符串分割出来，一开始我使用的是字符串数组的逐个赋值，每次都需要加上‘\0’，很是麻烦
//后来我就使用函数basic_string &assign(const basic_string &str, size_type index, size_type len);
//方法二可能更具有普适性：
//将字符串中的“.”和“/”替换成为“ ”再根据不同的信息通过scanf读入！

//重点：结构体的使用；sscanf对字符串进行分割；vector的使用erase和pushback

struct ip {
	int num[4];
	int mask;
	ip(int x1 = 0, int x2 = 0, int x3 = 0, int x4 = 0,int mask = 0)//构造函数中缺省变量默认值在列表最后
	{
		num[0] = x1;
		num[1] = x2;
		num[2] = x3;
		num[3] = x4;
		this->mask = mask;//使用this指针来区别同名
	}
	bool operator <(ip a) {
		if (num[0] != a.num[0])
			return num[0] < a.num[0];
		if (num[1] != a.num[1])
			return num[1] < a.num[1];
		if (num[2] != a.num[2])
			return num[2] < a.num[2];
		if (num[3] != a.num[3])
			return num[3] < a.num[3];
		if (mask != a.mask)
			return mask < a.mask;
	}
	void operator =(ip a) {
		num[0] = a.num[0];
		num[1] = a.num[1];
		num[2] = a.num[2];
		num[3] = a.num[3];
		this->mask = a.mask;
	}
	bool operator ==(ip x) {
		return ((num[0] == x.num[0]) && (num[1] == x.num[1]) && (num[2] == x.num[2]) && (num[3] == x.num[3]));
	}
};


vector <ip> ipn;

void tr(string px)
{
	int t = 0;
	int cnt = 0;
	int flag = 0;
	ip iptmp;
	while (px[t] != '\0')
	{
		if (px[t] == '.')
		{
			px[t] = ' ';
			cnt++;
		}
		if (px[t] == '/')
		{
			px[t] = ' ';
			flag = 1;
		}
		t++;
	}
	iptmp.mask = (cnt+1) * 8;
	if (cnt == 3 && flag == 1)
	{
		sscanf(px.c_str(), "%d %d %d %d %d", &iptmp.num[0], &iptmp.num[1], &iptmp.num[2], &iptmp.num[3], &iptmp.mask);
	}
	if (cnt == 3 && flag == 0)
	{
		sscanf(px.c_str(), "%d %d %d %d", &iptmp.num[0], &iptmp.num[1], &iptmp.num[2], &iptmp.num[3]);
	}
	if (cnt == 2 && flag == 1)
	{
		sscanf(px.c_str(), "%d %d %d %d", &iptmp.num[0], &iptmp.num[1], &iptmp.num[2], &iptmp.mask);
	}
	if (cnt == 2 && flag == 0)
	{
		sscanf(px.c_str(), "%d %d %d", &iptmp.num[0], &iptmp.num[1], &iptmp.num[2]);
	}
	if (cnt == 1 && flag == 1)
	{
		sscanf(px.c_str(), "%d %d %d", &iptmp.num[0], &iptmp.num[1], &iptmp.mask);
	}
	if (cnt == 1 && flag == 0)
	{
		sscanf(px.c_str(), "%d %d", &iptmp.num[0], &iptmp.num[1]);
	}
	if (cnt == 0 && flag == 1)
	{
		sscanf(px.c_str(), "%d %d", &iptmp.num[0], &iptmp.mask);
	}
	if (cnt == 0 && flag == 0)
	{
		sscanf(px.c_str(), "%d", &iptmp.num[0]);
	}
	ipn.push_back(iptmp);
}

void output() {
	vector<ip>::iterator tmpitor;
	for (tmpitor = ipn.begin(); tmpitor < ipn.end(); tmpitor++)
	{
		printf("%d.%d.%d.%d/%d", (*tmpitor).num[0], (*tmpitor).num[1], (*tmpitor).num[2], (*tmpitor).num[3], (*tmpitor).mask);
		if (tmpitor < ipn.end()-1)
		{
			printf("\n");
		}
	}
}
void show(ip ipx) {
	printf("%d.%d.%d.%d/%d\n", ipx.num[0], ipx.num[1], ipx.num[2], ipx.num[3], ipx.mask);
}
//void tr2(string px, int i)
//{
//	int res;
//	res = sscanf(px.c_str(), "%d.%d.%d.%d/%d", &ipn[i].num[0], &ipn[i].num[1], &ipn[i].num[2], &ipn[i].num[3], &ipn[i].mask);
//	printf("%d", res);
//	printf("%d.%d.%d.%d/%d", ipn[i].num[0], ipn[i].num[1], ipn[i].num[2], ipn[i].num[3], ipn[i].mask);
//}

int mas(int x, int mask)//按位与&，按位或|的基本操作
{
	int t = 0xffffff80;
	if (mask == 0)return 0;
	else t = t >> (mask - 1);
	return x&t;
}
//用全局变量不好啊

ip aftermask(ip ipx, int mask)
{
	ip tmpafter;
	//tmpafter.num[0] = 0;
	//tmpafter.num[1] = 0;
	//tmpafter.num[2] = 0;
	//tmpafter.num[3] = 0;
	/*tmpafter.mask = 0;*/
	int j = 0;
	int i = 0;
	if (mask < 8)
	{
		tmpafter.num[0] = mas(ipx.num[0], mask);
		return tmpafter;
	}
	else for (j = 0, i = mask; i >=8; j++, i = i - 8)
	{
		tmpafter.num[j] = ipx.num[j];
	}
	if(j!=4)tmpafter.num[j] = mas(ipx.num[j], i);
	tmpafter.mask = mask;
	return tmpafter;
}
//
//void test() {
//	int i;
//	int num[4];
//	int mask;
//	for (i = 0; i < 4; i++)
//	{
//		scanf("%d", &num[i]);
//	}
//	ip node(num[0], num[1], num[2], num[3]);
//	ip tmp;
//	for (i = 0; i < 10; i++)
//	{
//		scanf("%d",&mask);
//		tmp=aftermask(node, mask);
//		printf("%d.%d.%d.%d/%d", tmp.num[0], tmp.num[1], tmp.num[2], tmp.num[3], tmp.mask);
//	}
//}
bool inclu(ip ipx,ip ipy)
{
	ip afteripx, afteripy;
	afteripx = aftermask(ipx, ipx.mask);
	afteripy = aftermask(ipy, ipx.mask);
	if (afteripx == afteripy)
	{
		return 1;
	}
	else return 0;
}
bool comb(ip ipx, ip ipy)
{
	if (ipx.mask != ipy.mask)return 0;
	ip afteripx, afteripy;
	afteripx = aftermask(ipx, ipx.mask-1);
	afteripy = aftermask(ipy, ipx.mask-1);
	if (afteripx == afteripy)return 1;
	else return 0;
}

int main()
{
	int n;
	int i;
	int j;
	string px;
	char tmp[20];
	//test();
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		scanf("%s",tmp);
		px.assign(tmp);
		tr(px);
	}
	//output(n);
	sort(ipn.begin(), ipn.end());//缺省时默认为<，对于一个类，可以进行重载
	//output();
	//

	for (i = 0; i < ipn.size()-1; i++)
	{
		while(i!= ipn.size()-1)
		{
			if (inclu(ipn[i], ipn[i+1]))
			{
				ipn.erase(ipn.begin() + i + 1);
				//printf(".................\n");
				///*show(ipn[i]);
				//show(ipn[i + 1]);*/
				//output();
				//printf(".................\n");
			}
			else {
				break;
			}
		}
	}
	int fflag=0;
	for (i = 0; i < ipn.size() - 1; i++)
	{
		while (i != ipn.size() - 1)
		{
			if (i != 0&&fflag==1)
			{
				i = i - 1;
			}
			if (comb(ipn[i], ipn[i + 1]))
			{
				ipn[i] = aftermask(ipn[i], ipn[i].mask - 1);
				ipn.erase(ipn.begin() + i + 1);
				fflag = 1;
				//printf(".................\n");
				///*show(ipn[i]);
				//show(ipn[i + 1]);*/
				//output();
				//printf(".................\n");
			}
			else {
				fflag = 0;
				break;
			}
		}
	}
	output();
	return 0;
}


//char* trans(char *px)
//{
//	int i = 0, j;
//	int cnt = 0;
//	int mask = 0;
//	int flag = 0;
//	int flag2 = 0;
//	char tmp[10];
//
//	while (px[i] != '\0')
//	{
//		if (px[i] == '.')
//		{
//			cnt = cnt + 1;
//		}
//		if (px[i] == '/')
//		{
//			flag2 = 1;
//			if (cnt != 3) {
//				flag = 1;
//				break;
//			}
//		}
//		res[i] = px[i];
//		i++;
//	}
//
//	if (flag == 1)//省略后缀
//	{
//		int t = i;
//		for (j = cnt; j<3; j++)
//		{
//			res[t++] = '.';
//			res[t++] = '0';
//		}
//		while (px[i] != '\0')
//		{
//			res[t] = px[i];
//			t++;
//			i++;
//		}
//		res[t] = '\0';
//	}
//	else if (flag2 == 0)//省略长度
//	{
//		mask = 8 * (cnt + 1);
//		for (j = cnt; j<3; j++)
//		{
//			res[i++] = '.';
//			res[i++] = '0';
//		}
//		res[i++] = '/';
//		res[i++] = '\0';
//		itoa(mask, tmp, 10);
//		strcat(res, tmp);
//	}
//	else
//	{
//		res[i] = '\0';
//	}
//
//	return res;
//}
