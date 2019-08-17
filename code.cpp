#include <iostream>
#include <string>
#include <conio.h>
#include <fstream>
#include <vector>
#include <ctime>
#include <sstream>
using std::vector;
using namespace std;
class type_code
{
	string name,code;
public:
	string& retname(){return name;}
	string& retcode(){return code;}
};
class type_message
{
public:
	string name;
	int time,pretime;
};
class password
{
	string name,code;
	vector<type_code> store;
	vector<type_message> store_message;
public:
	int flag;//�����Ƿ���ϱ�׼
	int times;//����������
	password(){code="";flag=0;}
	void input_information();
	void check_information();
	void add_information();
	void solve_code(string &code);//�����˸�
	string add_dele_code(string temcode);//����
	void change_code();//�޸�����
	void dele_code();//ע���˺�
	void load_log_in();//��ȡ��¼��Ϣ
	void refresh_log_in();//ˢ�µ�¼��Ϣ
	void add_log_in(const string &temname);//���ӵ�¼��Ϣ
	void dele_log_in();//ɾ����¼��Ϣ
};
int main()
{
	password test;
	test.input_information();
	test.check_information();
	test.add_information();
	test.change_code();
	test.dele_code();
}
void password::input_information()
{
	cout<<"�������˺�\n";
	cin>>name;
	cout<<"\n����������\n";
	solve_code(code);
}
void password::check_information()
{
	string add_code=add_dele_code(code);
	string mid;
	ifstream in("user.txt",ios::in);
	int flag=0;
	while(getline(in,mid))
	{
		if(!flag)
		{
			flag=1;
			if(mid==name)
				break;
		}
		else
		{
			flag=0;
			continue;
		}
	}
	if(in.eof())
		cout<<"\n�˺Ż������������";
	else
	{
		load_log_in();
		getline(in,mid);
		if(mid==add_code)
		{
			cout<<"\n��¼�ɹ���\n";
			times=0;
			refresh_log_in();
		}
		else
		{
			times++;
			cout<<"\n�˺Ż������������\n";
			if(times>3&&times<8)
			{
				cout<<"�������������������࣬���˺Ž�������"<<(times-3)*5<<"����";
			}
			else if(times>=8)
			{
				cout<<"�������������������࣬���˺Ž�������"<<120<<"����";
			}
			refresh_log_in();
		}
	}
	in.close();
}
void password::add_information()
{
	cout<<"������ע���˺�\n";
	string temname,temcodeFirst="",temcodeSecond="";
	cin>>temname;
	cout<<"Ϊ�����������밲ȫ�������÷�������Ҫ������룺"<<endl;
	cout<<"���Ȳ�����7λ�Ҳ�����15λ�����ٰ���һλ���ֻ���ĸ�������֧����������ĸ�����"<<endl;
	cout<<"\n������ע������\n";
	solve_code(temcodeFirst);
	while(!(temcodeFirst.length()>=7&&temcodeFirst.length()<=15&&flag))
	{
		cout<<"\n���벻���Ϲ淶������������\n";
		solve_code(temcodeFirst);
	}
	cout<<"\n���ٴ���������\n";
	solve_code(temcodeSecond);
	while(temcodeFirst!=temcodeSecond)
	{
		temcodeSecond=temcodeFirst="";
		cout<<("�����������벻һ�£����ٴ�����");
		cout<<"\n������ע������\n";
		solve_code(temcodeFirst);
		cout<<"\n���ٴ���������\n";
		solve_code(temcodeSecond);
	}
	string temp;
	ifstream solve("user.txt",ios::in);
	int flag=0;
	while(getline(solve,temp))
	{
		if(!flag)
		{
			flag=1;
			if(temp==temname)
			{
				cout<<"\n���˺��ѱ�ע��\n";
				break;
			}
		}
		else
		{
			flag=0;
			continue;
		}
	}
	if(solve.eof())
	{
		solve.close();
		ofstream solve("user.txt",ios::app);
		temcodeFirst=add_dele_code(temcodeSecond);//����
		solve<<temname<<endl<<temcodeFirst<<endl;
		add_log_in(temname);
		cout<<"\nע����ɣ�\n";
	}
	solve.close();
}
void password::solve_code(string &code)
{
	code="";
	flag=0;
	char temp;
	int flag_num,flag_alp;
	flag_alp=flag_num=0;
	while((temp=getch())!='\r')
	{
		if(temp==8)
		{
			if(code=="")
				continue;
			cout<<"\b \b";
			code.erase(code.end()-1);
			continue;
		}
		if(temp>='0'&&temp<='9')
			flag_num=1;
		else if((temp>='a'&&temp<='z')||(temp>='A'&&temp<='Z'))
			flag_alp=1;
		code+=temp;
		cout<<"*";
	}
	if(flag_alp&&flag_num)
		flag=1;
}
string password::add_dele_code(string temcode)
{
	int n=0;
	string midtemp="";
	while(temcode[n])
	{
		midtemp+=temcode[n]*2+1;
		n++;
	}
	return midtemp;
}
void password::change_code()
{
	cout<<"������ԭ����\n";
	string precode,newcode_fir,newcode_sec;
	solve_code(precode);
	if(precode!=code)
	{
		cout<<"�����������\n";
		return;
	}
	cout<<"\n������������\n";
	solve_code(newcode_fir);
	cout<<"\n���ٴ���������\n";
	solve_code(newcode_sec);
	while(newcode_fir!=newcode_sec)
	{
		cout<<"\n�����������벻һ�£����ٴ�����\n";
		cout<<"������������\n";
		solve_code(newcode_fir);
		cout<<"\n���ٴ���������\n";
		solve_code(newcode_sec);
	}
	code=newcode_sec;
	string add_code=add_dele_code(code);//����
	ifstream in("user.txt",ios::in);
	type_code temp;
	string mid;
	while(getline(in,mid))
	{
		temp.retname()=mid;
		if(mid==name)
		{
			temp.retcode()=add_code;
			getline(in,mid);
		}
		else
		{
		getline(in,mid);
		temp.retcode()=mid;
		}
		store.push_back(temp);
	}
	in.close();
	ofstream out("user.txt",ios::out);
	for(int n=0;n<store.size();n++)
	{
		out<<store[n].retname()<<endl<<store[n].retcode()<<endl;
	}
	out.close();
	cout<<"\n�����޸����\n";
	store.clear();
}
void password::dele_code()
{
	cout<<"\n������ԭ����\n";
	string precode;
	solve_code(precode);
	if(precode!=code)
	{
		cout<<"\n�����������\n";
		return;
	}
	type_code temp;
	ifstream in("user.txt",ios::in);
	string mid;
	while(getline(in,mid))
	{
		if(mid==name)
		{
			getline(in,mid);
			continue;
		}
		temp.retname()=mid;
		getline(in,mid);
		temp.retcode()=mid;
		store.push_back(temp);
	}
	in.close();
	ofstream out("user.txt",ios::out);
	for(int n=0;n<store.size();n++)
	{
		out<<store[n].retname()<<endl<<store[n].retcode()<<endl;
	}
	out.close();
	dele_log_in();
	cout<<"\n������Ϣ��ɾ��\n";
	store.clear();
}
void password::load_log_in()
{
	ifstream in("user_message.txt",ios::in);
	string temp;
	int limit_time=0;//��λ������
	int pre;
	time_t now;
	while(getline(in,temp))
	{
		if(temp==name)
		{
			getline(in,temp);
			times=temp[0]-'0';
			if(times>3&&times<8)
			{
				limit_time=(times-3)*5;
			}
			else if(times>=8)
			{
				limit_time=120;
			}
			getline(in,temp);
			istringstream iss(temp);
			iss>>pre;
			now=time(0);
			if(now-pre<60*limit_time)
			{
				cout<<"\n���˺Ŵ��ڶ���״̬��ʣ�ඳ��ʱ�䣺"<<60*limit_time-(now-pre)<<"s"<<endl;
				getch();
				exit(0);
			}
			else
			{
				return;
			}
		}
		else
		{
			getline(in,temp);
			getline(in,temp);
		}
	}
	in.close();
}
void password::refresh_log_in()
{
	ifstream in("user_message.txt",ios::in);
	string temp;
	type_message temmessage;
	time_t second=time(0);//��ȡ��ǰʱ��
	while(getline(in,temp))
	{
		temmessage.name=temp;
		if(temp==name)
		{
			temmessage.time=times;
			temmessage.pretime=second;
			getline(in,temp);
			getline(in,temp);
		}
		else
		{
			getline(in,temp);
			istringstream iss(temp);
			iss>>temmessage.time;
			getline(in,temp);
			istringstream oss(temp);
			oss>>temmessage.pretime;
		}
		store_message.push_back(temmessage);
	}
	in.close();
	ofstream out("user_message.txt",ios::out);
	for(int n=0;n<store_message.size();n++)
	{
		out<<store_message[n].name<<endl<<store_message[n].time<<endl<<store_message[n].pretime<<endl;
	}
	store_message.clear();
	out.close();
}
void password::add_log_in(const string &temname)
{
	ofstream out("user_message.txt",ios::app);
	out.seekp(0,ios::end);
	time_t second=time(0);
	out<<temname<<endl<<"0"<<endl<<second<<endl;
	out.close();
}
void password::dele_log_in()
{
	string temp;
	type_message temmessage;
	ifstream in("user_message.txt",ios::in);
	while(getline(in,temp))
	{
		if(temp==name)
		{
			getline(in,temp);
			getline(in,temp);
		}
		else
		{
			temmessage.name=temp;
			getline(in,temp);
			istringstream iss(temp);
			iss>>temmessage.time;
			getline(in,temp);
			istringstream oss(temp);
			oss>>temmessage.pretime;
			store_message.push_back(temmessage);
		}
	}
	in.close();
	ofstream out("user_message.txt",ios::out);
	for(int n=0;n<store_message.size();n++)
	{
		out<<store_message[n].name<<endl<<store_message[n].time<<endl<<store_message[n].pretime<<endl;
	}
	store_message.clear();
	out.close();
}