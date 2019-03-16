#include<iostream> 
#include<vector>
using namespace std;
struct ru {
	string name;
	vector <string> type; 
	void operator = (ru rux) {
		this->name = rux.name;
		this->type.clear();
		int i = 0;
		for (i = 0; i < rux.type.size(); i++)
		{
			this->type.push_back(rux.type[i]);
		}
	}
	 ru() {
		name = "";
		this->type.clear();
	}
};

vector <ru> rls;

void split(string s, string c, vector<string> &res) {//注意此处的传参方式 
	int pos1, pos2;
	pos1 = 1;
	pos2 = s.find(c,1);
	while (pos2 != string::npos) {
		res.push_back(s.substr(pos1, pos2 - pos1));
		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.size())
	{
		res.push_back(s.substr(pos1));
	}
	else {
		res.push_back("/");
	}
}

ru torule(string rule,string name)
{
	ru res;
	res.name =name;
	vector<string> aftersplit;
	string c = "/";
	split(rule, c, aftersplit);
	res.type.clear();
	int i = 0;
	for (i = 0; i < aftersplit.size(); i++)
	{
		res.type.push_back(aftersplit[i]);
	}
	return res;
}
void printvec(vector<string> s) {
	int i = 0;
	for (i = 0; i < s.size(); i++) {
		printf("%s\n", s[i].c_str());
	}
}
bool test_int(string s, vector<string> &par) {
	string tmp;
	int i = 0;
	int flag = 0;
	int pos;
	for (i = 0; i < s.size(); i++) {
	 if ('0' <= s[i] &&s[i]<= '9') {
		 if (flag == 0 && s[i] != '0') {
			 pos = i;
			 flag = 1;
		 }
	}
	else return 1;
	}
	tmp.assign(s, pos, s.size() - pos);
	par.push_back(tmp);
	return 0;
}
bool test_str(string s, vector<string> &par) {
	string tmp;
	int i = 0;
	par.push_back(s);
	return 0;
}
bool test_path(string s, vector<string> &par) {
	string tmp;	
	tmp.append(s);
	par.push_back(tmp);
	return 0;
}
void notmatch() {
	printf("404\n");
}
bool match(vector <string> adds, ru rux) {
	int i;
	vector<string> par;
	if (rux.type[rux.type.size()-1]!="<path>"&&adds.size() != rux.type.size()) {
		return 1;
	}
	for (i = 0; i < adds.size(); i++)
	{
		if (rux.type[i] == "<int>") {
			if(test_int(adds[i], par)==1)//该函数仅处理par，不输出
				{return 1;}
		}
		else if (rux.type[i] == "<str>") {
			if (test_str(adds[i], par) == 1)
				{return 1;}
		}
		else if(rux.type[i] == "<path>") {
			string tmp;
			if (adds[i] == "/")return 1;
			while (i < adds.size()) {
				tmp.append(adds[i]);
				if (i != adds.size() - 1&&adds[i+1]!="/")
					tmp.append("/");
				i++;
			}
			par.push_back(tmp);
		}
		else if (adds[i] == rux.type[i]) {
			//par.push_back(adds[i]);
		}
		else {return 1;}
	}
	printf("%s ", rux.name.c_str());
	for (i = 0; i < par.size(); i++)
	{
		printf("%s ", par[i].c_str());
	}
	printf("\n");
	return 0;
}
int main(){
	int n,m;
	int i;
	char tmp[100];
	ru rlstmp;
	string rule;
	string rname;
	string tmpadd;
	string c = "/";
	vector <string> adds;
	int j;
	scanf("%d %d",&n,&m);
	for(i=0;i<n;i++)
	{
		scanf("%s",tmp);
		rule.assign(tmp);
		scanf("%s",tmp);
		rname.assign(tmp);
		//printf("%s %s",rule.c_str(),rname.c_str());
		rlstmp=torule(rule,rname);
		rls.push_back(rlstmp);
	 } 
	//printf("\n[after_split]\n");
	/*for (i = 0; i < n; i++) {
		printf("%s\n", rls[i].name.c_str());
		printvec(rls[i].type);
		printf("\n");
	}*/
	 for(i=0;i<m;i++)
	 {
	 	scanf("%s",tmp);
		tmpadd.assign(tmp);
		split(tmpadd, c, adds);
		/*printf("\n[after_split]\n");
		printvec(adds);
		printf("\n");*/
		int m_flag = 0;
		for (j = 0; j < n; j++)
		{
			if (match(adds, rls[j]) == 0)//匹配
			{
				m_flag = 1;
				break;
			}
		}
		if (m_flag == 0) {
			notmatch();
		}
		adds.clear();
	 }
} 

//对于vector一开始不能直接使用[i]进行操作 
