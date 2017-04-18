#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
using namespace std;


class account
{
	int acno;
	char name[90];
	int deposit;
	char type;
public:
	void create_account();
	void show_account() const;
	void modify();
	void dep(int);
	void draw(int);
	void report() const;
	int retacno() const;
	int retdeposit() const;
	char rettype() const;
};

void account::create_account()
{
	cout<<"Enter The account No. :"<<endl;
	cin>>acno;
	cout<<Enter The Name of The account Holder : "<<endl;
	cin.ignore();
	cin.getline(name,90);
	cout<<"Enter Type of The account (C/S) : "<<endl;
	cin>>type;
	type=toupper(type);
	cout<<"Enter The Initial amount(>=500 for Saving and >=1000 for current ) : "<<endl;
	cin>>deposit;
	cout<<"Account Created.."<<endl;
}

void account::show_account() const
{
	cout<<"\nAccount No. : "<<acno<<endl;
	cout<<"\nAccount Holder Name : ";
	cout<<name;
	cout<<"Type of Account : "<<type<<endl;
	cout<<"Balance amount : "<<deposit<<endl;
}


void account::modify()
{
	cout<<Account No. : "<<acno<<endl;
	cout<<Modify Account Holder Name : "<<endl;
	cin.ignore();
	cin.getline(name,50);
	cout<<Modify Type of Account : "<<endl;
	cin>>type;
	type=toupper(type);
	cout<<Modify Balance amount : "<<endl;
	cin>>deposit;
}


void account::dep(int x)
{
	deposit+=x;
}

void account::draw(int x)
{
	deposit-=x;
}

void account::report() const
{
	cout<<acno<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(6)<<deposit<<endl;
}


int account::retacno() const
{
	return acno;
}

int account::retdeposit() const
{
	return deposit;
}

char account::rettype() const
{
	return type;
}

void write_account();
void display_sp(int);
void modify_account(int);
void delete_account(int);
void display_all();
void deposit_withdraw(int, int);
void intro();

int main()
{
	char ch;
	int num;
	intro();
	do
	{
		system("cls");
		cout<<"MAIN MENU"<<endl;
		cout<<" NEW ACCOUNT"<<endl;
		cout<<" DEPOSIT AMOUNT"<<endl;
		cout<<" WITHDRAW AMOUNT"<<endl;
		cout<<" BALANCE ENQUIRY"<<endl;
		cout<<" ALL ACCOUNT HOLDER LIST"<<endl;
		cout<<" CLOSE AN ACCOUNT"<<endl;
		cout<<" MODIFY AN ACCOUNT"<<endl;
		cout<<" EXIT"<<endl;
		cout<<"Select Your Option (1-8) "<<endl;
		cin>>ch;
		system("cls");
		switch(ch)
		{
		case '1':
			write_account();
			break;
		case '2':
			cout<<"Enter The account No. : "<<endl;
            cin>>num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			cout<<"Enter The account No. : "<<endl;
             cin>>num;
			deposit_withdraw(num, 2);
			break;
		case '4':
			cout<<"Enter The account No. : "<<endl;
            cin>>num;
			display_sp(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			cout<<"\n\n\tEnter The account No. : "<<endl;
            cin>>num;
			delete_account(num);
			break;
		 case '7':
			cout<<"\n\n\tEnter The account No. : "<<endl;
             cin>>num;
			modify_account(num);
			break;
		 case '8':
			cout<<"\n\n\tThanks for using bank managemnt system"<<endl;
			break;
		 default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
	}while(ch!='8');
	return 0;
}


void write_account()
{
	account ac;
	ofstream outFile;
	outFile.open("account.dat",ios::binary,ios::app);
	ac.create_account();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
	outFile.close();
}
void display_sp(int n)
{
	account ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open. Press any Key...";
		return;
	}
	cout<<"BALANCE DETAILS"<<endl;

    	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"Account number does not exist"<<endl;
}

void modify_account(int n)
{
	bool found=false;
	account ac;
	fstream File;
	File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()==n)
		{
			ac.show_account();
			cout<<"Enter The New Details of account"<<endl;
			ac.modify();
			int pos=(-1)*static_cast<int>(sizeof(account));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<"\n\n\t Record Updated";
			found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<" Record Not Found "<<endl;
}
void delete_account(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File can not be open. Press any Key...";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
	cout<<"Record Deleted ..";
}


void display_all()
{
	account ac;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"ACCOUNT HOLDER LIST"<<endl;
	cout<<"===================================================="<<endl;
	cout<<"A/c no.      NAME           Type  Balance"<<endl;
	cout<<"===================================================="<<endl;
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		ac.report();
	}
	inFile.close();
}



void deposit_withdraw(int n, int option)
{
	int amt;
	bool found=false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key..."<<endl;
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()==n)
		{
			ac.show_account();
			if(option==1)
			{
				cout<<"TO DEPOSITE AMOUNT "<<endl;
				cout<<"Enter The amount to be deposited"<<endl;
				cin>>amt;
				ac.dep(amt);
			}
			if(option==2)
			{
				cout<<"TO WITHDRAW AMOUNT"<<endl;
				cout<<"Enter The amount to be withdraw"<<endl;
				cin>>amt;
				int bal=ac.retdeposit()-amt;
				if((bal<500 && ac.rettype()=='S') || (bal<1000 && ac.rettype()=='C'))
					cout<<"Insufficience balance";
				else
					ac.draw(amt);
			}
			int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<"Record Updated"<<endl;
			found=true;
	       }
         }
	File.close();
	if(found==false)
		cout<<"Record Not Found "<<endl;
}


void intro()
{
	cout<<" BANK MANAGEMENT SYSTEM";

	cin.get();
}
