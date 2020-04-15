#include <iostream>
#include <string>
#include <stack>
using namespace std;

bool isOp(char x)
{
	if(x=='+'||x=='-'||x=='*'||x=='/'||x=='(')
		return true;
	else
		return false;
}

int prior(char x)
{
	if(x=='#')
		return -1;
	else if(x=='(')
		return 0;
	else if(x=='+'||x=='-')
		return 1;
	else if(x=='*'||x=='/')
		return 2;
	else
		return -1;
}

string convert(string str,string &rsp,bool &hasError) //�Ȱ���׺���ʽת��׺���ʽ
{
	stack<char> op; //������ջ
	op.push('#'); //ĩβ���
	int len = (int)str.length(); //������unsigned
	for(int i=0;i<len;i++)
	{
		if(str[i]==' ')
			continue;
		if(str[i]>='0' && str[i]<='9') //����ֱ���������׺
			rsp += str[i];
		else if(str[i]=='(') //������(ֱ����ջ
			op.push(str[i]);
        else if(str[i]==')')
        {
        	while(op.top()!='(')
        	{
        		rsp += op.top();
        		op.pop();
			}
			op.pop(); //�����ţ���ջ
		}
		else if(isOp(str[i]))
		{
			rsp += ' '; //�ÿո�����ֺ�������������������λ����
			while(prior(str[i])<=prior(op.top())) //���ȼ�С�ڵ���ջ��������ջ����rsp
			{
				rsp += op.top();
				op.pop();
			}
			op.push(str[i]); //���ȼ�����ջ������ջ
		}
		else
		{
			cout << "ERROR: ��������ȷ���ʽ��\n";
			hasError = true;
			break;
		}
	}
	while(!op.empty())
	{
		rsp += op.top();
		op.pop();
	}
	
	return rsp;
}

double readNum(string exp,int &i)
{
	double result = 0;
	while(exp[i]>='0' && exp[i]<='9')
	{
		result = result * 10 + (exp[i] - '0');
		i++;
	}
	return result;
}

double calculate(string rsp,bool &hasError)
{
	int i = 0;
	stack<double> num;
	double x1,x2;
	
	while(rsp[i]!='#')
	{
		if(rsp[i]>='0' && rsp[i]<='9')
			num.push(readNum(rsp,i));
		else if(rsp[i]==' ')
			i++;
		else if(rsp[i]=='+')
		{
			x1 = num.top();
			num.pop();
			x2 = num.top();
			num.pop();
			num.push(x1 + x2);
			i++;
		}
		else if(rsp[i]=='-')
		{
			x1 = num.top();
			num.pop();
			x2 = num.top();
			num.pop();
			num.push(x2 - x1);
			i++;
		}
		else if(rsp[i]=='*')
		{
			x1 = num.top();
			num.pop();
			x2 = num.top();
			num.pop();
			num.push(x1 * x2);
			i++;
		}
		else if(rsp[i]=='/')
		{
			x1 = num.top();
			{
				if(x1==0)
				{
					cout << "ERROR: ��������Ϊ0��\n";
					hasError = true;
					break;
				}
			}
			num.pop();
			x2 = num.top();
			num.pop();
			num.push(x2 / x1);
			i++;
		}
	}
	return num.top(); //���ļ�����
}

int main()
{
	string str = "";

	while(getline(cin,str)) //ע��cin>>str�����ո����
	{
		string s = "";
		bool hasError = false;
		double result = 0;
		string rsp = convert(str,s,hasError);
//		cout << "rsp: " << rsp << endl;
		if(!hasError)
			result = calculate(rsp,hasError);
		if(!hasError)
			cout << result << endl;
	}
	
	return 0;
}
