#include <string>
#include <map>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;



int pos,len,beg,ed;
string str,str_var;
map<string, double> dict;
map<string, string> fs;
double d,ans;


void init()
{
  fs["mile"] = "miles";
	fs["yard"] = "yards";
	fs["inch"] = "inches";
	fs["foot"] = "feet";
	fs["fath"] = "faths";
	fs["furlong"] = "furlongs";
}

void parse_string(string &str)
{
	
	vector<string> fh,num,_dw;
	ans = 0;

	str.push_back(' ');
	len = str.size();
	for(beg = ed = 0; ed < len; ed++)
	{
		if(str[ed] == ' ')
		{
			if(str[ed-1] == '+' || str[ed-1] == '-')
			{
				if(str[ed-1] == '+')
					fh.push_back("+");
				else
					fh.push_back("-");
			}else
			{
				if(str[ed-1] >= 'a' && str[ed-1] <= 'z')
				{
						_dw.push_back(str.substr(beg, ed-beg));
				}else
				{
					num.push_back(str.substr(beg, ed-beg));
				}
			}
			beg = ed+1;
		}
		
	}


	d = atof(&num[0][0]);
	d = d*dict[_dw[0]];
	ans += d;

	for(beg = 1; beg < num.size(); beg++)
	{
		d = atof(&num[beg][0]);
		d = d*dict[_dw[beg]];
		if(fh[beg-1][0] == '+')
			ans += d;
		else
			ans -= d;
	}
}





int main()
{	
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);

	init();
	while(1)
	{	
		getline(cin, str);
		if(!str.size())
			break;
		len = str.size();
		pos = str.find('=');
		str_var = str.substr(pos+2, len-2-(pos+2)+1);
		d = atof(&str_var[0]);
		 str_var = str.substr(2, pos-2-2+1);
		dict[str_var] = d;
		dict[fs[str_var]] = d;
		str.clear();
	}

	printf("175119606@qq.com\n");
	while(1)
	{
		getline(cin, str);
		if(!str.size())
			break;
		printf("\n");
		parse_string(str);
		printf("%.2lf m",ans);
		str.clear();
	}
	return 0;
}
