#include<iostream>
#include<vector>
//#include<cstdio>

using namespace std;
struct node {
	int depth;
	string label;
	string id;
	void show() {
		printf("%d %s %s\n", depth, label.c_str(), id.c_str());
	}
};
vector<node> nlist;
vector<int> res_num;
void printvec(vector<int> res) {
	int i;
	for (i = 0; i < res.size(); i++)
	{
		printf("%d ", res[i] + 1);
	}
	printf("\n");
}
void tras(string stmp, node &nox) {
	char tmp[80];
	int depth = 0;
	int i;
	for (i = 0; stmp[i] == '.'; i = i + 2) {
		depth++;
	}
	nox.depth = depth;
	string inf;
	inf.assign(stmp.substr(i));
	nox.label = inf;
	/*char* keyw = " #";
	int pos1;
	pos1 = inf.find(keyw);
	if (pos1 != string::npos) {
	nox.label.assign(inf, 0, pos1);
	nox.id.assign(inf.substr(pos1+2));
	}
	else {
	nox.label.assign(inf);
	nox.id.assign("");
	}*/
}
bool nob_check(string s, string x) {
	int i = 0;
	if (s.size() != x.size())return 0;
	for (i = 0; i < s.size(); i++) {
		if (('a' <= s[i] && s[i] <= 'z' && (s[i] == x[i] || s[i] == x[i] - ('A' - 'a'))) || ('A' <= s[i] && s[i] <= 'Z' && (s[i] == x[i] || s[i] == x[i] - ('a' - 'A'))) || (s[i] == x[i]))
			;
		else return 0;
	}
	return 1;
}
void id_ser(string s) {
	int i;
	for (i = 0; i < nlist.size(); i++)
	{
		if (s == nlist[i].id)
			res_num.push_back(i);
	}
}
void label_ser(string s) {
	int i;
	for (i = 0; i < nlist.size(); i++)
	{
		if (nob_check(s, nlist[i].label) == 1)
			res_num.push_back(i);
	}
}
void child_ser(vector<string> demand) {
	int i;
	int j;
	int dep;
	int index = 1;
	for (i = 0; i < nlist.size(); i++)
	{
		index = 1;
		if (nob_check(demand[demand.size() - 1], nlist[i].label) == 1)
		{
			dep = nlist[i].depth;
			for (j = i; j >= 0; j--)
			{
				if (nlist[j].depth < dep) {
					dep = nlist[j].depth;
					if (nob_check(demand[demand.size() - index - 1], nlist[j].label) == 1) {
						index++;
						if (demand.size() == index) {
							res_num.push_back(i);
							break;
						}
					}
				}
			}
		}
	}
}
void split(string s, string c, vector<string>&v) {
	int pos1 = 0;
	int pos2;
	pos2 = s.find(c);
	while (pos2 != string::npos) {
		v.push_back(s.substr(pos1, pos2 - pos1));
		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length()) {
		v.push_back(s.substr(pos1));
	}
}
int main() {
	int n, m;
	int res;
	int char_flag=0;
	node nodetmp;
	char tmp[80];
	char tmp2[80];
	string stmp;
	string ser;
	scanf("%d %d\n", &n, &m);
	int i;
	for (i = 0; i < n; i++) {
		res = scanf("%s #%s", tmp, tmp2);
		stmp.assign(tmp);
		if (res == 1) {
			tras(stmp, nodetmp);
			nlist.push_back(nodetmp);
		}
		else {
			tras(stmp, nodetmp);
			nlist.push_back(nodetmp);
			nlist[nlist.size() - 1].id = tmp2;
		}
		if (i == n - 1 && res == 2) { char_flag = 1; }
	}

	/*char c = getchar();
	while(c != '\n')c = getchar();*/

	if(char_flag==1) getchar();//(前一行是scanf，后一行为gets_s)
	for (i = 0; i < m; i++)
	{
		char d[100];
		vector<string> demand;
		cin.getline(d, 100);//
							//gets(d);
		stmp.assign(d);
		split(d, " ", demand);
		if (demand.size() == 1) {
			if (stmp[0] == '#')
			{
				ser = stmp.substr(1);
				id_ser(ser);
			}
			else
			{
				ser = stmp;
				label_ser(ser);
			}
		}
		else {
			/*int j;
			printf("demand: ");
			for (j = 0; j < demand.size(); j++){
			printf("%s ",demand[j].c_str());
			}
			printf("\n");*/
			child_ser(demand);
		}
		printf("%d ", res_num.size());
		printvec(res_num);
		res_num.clear();
	}
	return 0;
}