#include <iostream>
#include <string>
#include <cstdio>
#include <set>
using namespace std;

bool graph[10][7] = {1, 1, 1, 1, 1, 1, 0,//0
					 0, 1, 1, 0, 0, 0, 0,//1
					 1, 1, 0, 1, 1, 0, 1,//2
					 1, 1, 1, 1, 0, 0, 1,//3
					 0, 1, 1, 0, 0, 1, 1,//4
					 1, 0, 1, 1, 0, 1, 1,//5
					 1, 0, 1, 1, 1, 1, 1,//6
					 1, 1, 1, 0, 0, 0, 0,//7
					 1, 1, 1, 1, 1, 1, 1,//8
					 1, 1, 1, 1, 0, 1, 1};//9
					 

int f(bool* a, bool* b)	{
	int sum = 0, n = 0;
	for(int i = 0; i < 7; i++)	{
		if(a[i] == 0 && b[i] == 1)	{
			n++;
			sum--;
		}
		else if(a[i] == 1 && b[i] == 0)	{
			sum++;
			n++;
		}
	}
	if(n == 2 && sum == 0)			return 1;
	else if(n == 1 && sum == 1)		return 2;
	else if(n == 1 && sum == -1)	return -2;
	else 					return 0;
}

//0表示无法转换
//1表示不需要添加或减少火柴，只移动一根火柴即可转换
//-2表示需要添加1根火柴 
//2表示需要减少一根火柴 
int d[10][10];
void cpt()	{
	int i, j;
	for(i = 0; i < 10; i++)	{
		d[i][i] = 0;
		for(j = i+1; j < 10; j++)	{
			int ans = f(graph[i], graph[j]);
			d[i][j] = ans;
			if(ans == 1)	d[j][i] = 1;
			else			d[j][i] = -ans;
		}
	}
}

bool judge(string equation, int pos1, int pos2)	{
	string a, b, c;
	if(equation[pos1] == '+')	{
		a = equation.substr(0, pos1);
		b = equation.substr(pos1+1, pos2-pos1-1);
		c = equation.substr(pos2+1, equation.size()-pos2-1);
	}
	else if(equation[pos1] == '-')	{
		c = equation.substr(0, pos1);
		b = equation.substr(pos1+1, pos2-pos1-1);
		a = equation.substr(pos2+1, equation.size()-pos2-1);
	}
	
	if((a[0]=='0'&&a.size() >1) || (b[0]=='0'&&b.size()>1) || (c[0]=='0'&&c.size()> 1))
	return 0;
	int p, p1 = a.size(), p2 = b.size(), p3 = c.size();
	p = (p1 > p2)?p1:p2;
	p = (p > p3)?p:p3;
	a.insert(0, p-p1, '0');
	b.insert(0, p-p2, '0');
	c.insert(0, p-p3, '0');
	
	int inc, sum;
	for(inc = 0, p--; p >= 0; p--)	{
		sum = a[p]-48 + b[p]-48 + inc;
		inc = sum / 10;
		sum %= 10;
		if(sum != c[p]-48)	break;
	}
	if(p < 0 && inc == 0)	return 1;
	else					return 0;
}	
		
	
			
	
int main()
{
	int i, j, k, l;
	
	int pos1, pos2;
	cpt();
	
	char op1, op2;
	string equation, a, b, c;
	while(getline(cin, equation))   {
	
	for(i = 0; i < equation.size(); i++)	{
		if(equation[i] == '-' || equation[i] == '+')	{
			pos1 = i;
			op1 = equation[i];
		}
		if(equation[i] == '=')	{
			pos2 = i;
			op2 = equation[i];
		}
	}
	
	set<string> s;
	s.clear();
	for(i = 0; i < equation.size(); i++)	{
		if(equation[i] != '+' && equation[i] != '-' && equation[i] != '=')	{
			for(j = 0; j < 10; j++)	{
				if(d[equation[i]-48][j] == 1)	{
					string temp = equation;
					temp[i] = j+48;
					if(judge(temp, pos1, pos2))	s.insert(temp);
				}
			}
		}
	}
	
	int r1, r2;
	for(i = 0; i < equation.size(); i++)
	for(j = i+1; j <  equation.size(); j++)	{
		if(i == pos2 || j == pos2)	continue;
		if(i == pos1)	{
			r1 = (op1 == '+')?2:-2;
			for(l = 0; l < 10; l++)	{
				r2 = d[equation[j]-48][l];
				if(r2+r1 == 0)	{
					string temp = equation;
					if(op1 == '+')	temp[pos1] = '-';
					else			temp[pos1] = '+';
					temp[j] = l+48;
					if(judge(temp, pos1, pos2))	s.insert(temp);
				}
			}
		}
		else {	
			for(k = 0; k < 10; k++)	{
				r1 = d[equation[i]-48][k];
				if(r1 == 0 || r1 == 1)	continue;
				if(j == pos1)	{
					r2 = (op1 == '+')?2:-2;
					if(r1+r2 == 0)	{
						string temp = equation;
						if(op1 == '+')	temp[pos1] = '-';
						else			temp[pos1] = '+';
						temp[i] = k+48;
						if(judge(temp, pos1, pos2))	s.insert(temp);
					}
				}
				else	{
					for(l = 0; l < 10; l++)	{
						r2 = d[equation[j]-48][l];
						if(r1+r2 == 0)	{
							string temp = equation;
							temp[j] = l+48;
							temp[i] = k+48;
							if(judge(temp, pos1, pos2))	s.insert(temp);
						}
					}
				}
			}
		}
	}
	
	set<string>::iterator cnt;
	if(s.empty()) cout << -1 << endl;
	else	{
		for(cnt = s.begin(); cnt != s.end(); cnt++)
		cout << *cnt << endl;
	}
	}
	return 0;
}
		
							
							
				
				
						
					
		
	
	
