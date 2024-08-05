#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>
#include <fstream>
#include <string>
#define ll long long

using namespace std;
class Icart;
class User;
vector<User>user_save;
vector<Icart*>cart_save;
class System;

class User {
public:
	string User_name;
	string Password;
	string Phone;
	friend class System;
	friend class Visacart;
	User() {

	}
	User(string user_name, string passw, string phon) {
		User_name = user_name;
		Password = passw;
		Phone = phon;
	}

};


class Icart {
public:
	ll  Amount;
	string User_vname;
	string Phone_number;
	string Password;
	int type;

	virtual void send_money(long long money, string phone_num) = 0;   //  cheak on the datatype
	virtual void send_money(string user_vname, long long money) = 0;
	virtual void addmoney() = 0;
	virtual void show_money() = 0;  //  cheak on the datatype



};
class Visacart :public Icart {
public:
	friend class User;
	void send_money(string uservname, long long money) {
		bool flag = 0;
		if (Amount < money) {
			cout << "not have this money \n";
		}
		else {
			//found the user name
			for (int i = 0; i < user_save.size(); i++) {
				if (uservname == user_save[i].User_name) {
					flag = 1; break;
				}
			}

			if (flag) {
				Amount -= (money - (money / 100) * 1);
				int count = 0;
				for (int i = 0; i < cart_save.size(); i++) {
					if (cart_save[i]->User_vname == User_vname) {
						cart_save[i]->Amount += (money - (money / 100) * 1); break;
					}
				}
				cout << "Successful operation \n";
			}
			else {
				cout << "not found the user \n";
			}

		}

	}
	void send_money(long long money, string phone_num) {
		bool flag = 0;
		if (Amount < money) {
			cout << "not have this money \n";
		}
		else {
			//found the user name
			for (int i = 0; i < user_save.size(); i++) {
				if (phone_num == user_save[i].Phone) {
					flag = 1;
				}
			}

			if (flag) {
				Amount -= money;
				int count = 0;
				for (int i = 0; i < cart_save.size(); i++) {
					if (cart_save[i]->Phone_number == phone_num) {
						cart_save[i]->Amount += (money - (money / 100) * 1); break;
					}
				}
				cout << "Successful operation \n";
			}
			else {
				cout << "not found the user \n";
			}

		}
	}
	void addmoney() {
		cout << "enter the money :";
		int mn; cin >> mn;
		if (mn > 10000) {
			cout << "Exceeded the maximum\n";
			addmoney();
		}
		Amount += mn - ((mn / 100) * 1);
		cout << "Successful operation \n";
	}
	void show_money() {
		cout << "your money is :" << Amount << endl;
	}
};
class Mastercard :public Icart {
public:
	void send_money(string user_vname, ll money) {
		bool flag = 0;
		if (Amount < money) {
			cout << "not have this money \n";
		}
		else {
			//found the user name
			for (int i = 0; i < user_save.size(); i++) {
				if (user_vname == user_save[i].User_name) {
					flag = 1;
				}
			}

			if (flag) {
				Amount -= money;
				int count = 0;
				for (int i = 0; i < cart_save.size(); i++) {
					if (cart_save[i]->User_vname == User_vname) {
						cart_save[i]->Amount += (money - (money / 100) * 2); break;
					}
				}
				cout << "Successful operation \n";
			}
			else {
				cout << "not found the user \n";
			}

		}

	}
	void send_money(long long money, string phone_num) {
		bool flag = 0;
		if (Amount < money) {
			cout << "not have this money \n";
		}
		else {
			//found the user name
			for (int i = 0; i < user_save.size(); i++) {
				if (phone_num == user_save[i].Phone) {
					flag = 1;
				}
			}

			if (flag) {
				Amount -= money;
				int count = 0;
				for (int i = 0; i < cart_save.size(); i++) {
					if (cart_save[i]->Phone_number == phone_num) {
						cart_save[i]->Amount += (money - (money / 100) * 2); break;
					}
				}
				cout << "Successful operation \n";
			}
			else {
				cout << "not found the user \n";
			}

		}
	}
	void addmoney() {
		cout << "enter the money :";
		int mn; cin >> mn;
		if (mn > 10000) {
			cout << "Exceeded the maximum\n";
			addmoney();
		}
		Amount += mn - ((mn / 100) * 2);
		cout << "Successful operation \n";
	}
	void show_money() {
		cout << "your money is :" << Amount << endl;
	}
};
class System {
public:
	friend class User;
	User login() {
		string nmnm, passworde;
		cout << "Enter your user name:\n";
		cin >> nmnm;
		cout << "Enter your password : \n";
		cin >> passworde;
		bool flag = 0;
		for (int i = 0; i < user_save.size(); i++) {
			if (nmnm == user_save[i].User_name && passworde == user_save[i].Password) {
				flag = 1;
				return user_save[i];

			}
		}
		if (!flag) {
			cout << "Invaled user name ,plesse try again\n";
			cout << "Enter 1 to login or any button to exit\n";
			string op; cin >> op; if (op == "1") { return login(); }
		}
		User Invaled = { "-1","-1","-1" };
		return Invaled;
	}
	User sign_up() {
		string user, ph;
		string passwo;
		cout << "Enter user name. (No spaces) : \n";
		cin >> user;
		cout << "Enter password : \n";
		cin >> passwo;
		cout << "Enter your phone number : \n";
		cin >> ph;


		for (int i = 0; i < user_save.size(); i++) {
			if (user == user_save[i].User_name) {
				cout << "This user is already used\n";
				return sign_up();
			}
		}

		cout << "choise type the visa \n"
			<< "1- visa_cart \n"
			<< "2- master_cart \n";

		int cou; cin >> cou;
		if (cou == 1) {
			Icart* ptr = new Visacart;
			ptr->Amount = 0;
			ptr->Password = passwo;
			ptr->Phone_number = ph;
			ptr->User_vname = user;
			ptr->type = 1;
			cart_save.push_back(ptr);
		}
		else {
			Icart* ptr = new Mastercard;
			ptr->Amount = 0;
			ptr->Password = passwo;
			ptr->Phone_number = ph;
			ptr->User_vname = user;
			ptr->type = 2;
			cart_save.push_back(ptr);
		}

		User users = { user ,passwo,ph };
		user_save.push_back(users);
		return users;
	}

	int menu() {
		cout << "menu:\n";
		cout << "			1:Login" << endl;
		cout << "			2:Sign Up" << endl;
		int op;
		cout << "Enter number in range 1 - 2: " << endl;
		cin >> op;
		if (op < 1 || op>2) {
			cout << "Invaled number";
			return menu();
		}
		return op;
	}
	int menu2() {
		cout << "Menu:\n";
		cout << "			1: send money" << endl; //done
		cout << "			2: show your money in visa" << endl;
		cout << "			3: add visa " << endl;
		cout << "			4: add money " << endl; // done
		cout << "			5: Logout" << endl;//done
		int operation;
		cout << "Enter number in range 1 - 5: ";
		cin >> operation;
		if (operation < 1 || operation >5) {
			cout << "Invaled Nember\n";
			return menu2();
		}
		return operation;
	}

	void add_visa(User nw) {
		cout << "1- visacart \n";
		cout << "2- mastercart \n";
		int num; cin >> num;
		if (num == 1) {
			bool flag = 0;
			for (int i = 0; i < cart_save.size(); i++) {
				if (nw.User_name == cart_save[i]->User_vname and cart_save[i]->type == 1) {
					cout << "you have already this visa \n"; flag = 1;
				}
			}
			if (!flag) {
				Icart* ptr;
				ptr = new Visacart;
				ptr->Password = nw.Password;
				ptr->Phone_number = nw.Phone;
				ptr->User_vname = nw.User_name;
				ptr->Amount = 0;
				ptr->type = 1;
				cart_save.push_back(ptr);
			}

		}
		else {
			bool flag = 0;
			for (int i = 0; i < cart_save.size(); i++) {
				if (nw.User_name == cart_save[i]->User_vname and cart_save[i]->type == 2) {
					cout << "you have already this visa \n"; flag = 1;
				}
			}
			if (!flag) {
				Icart* ptr;
				ptr = new Mastercard;
				ptr->Password = nw.Password;
				ptr->Phone_number = nw.Phone;
				ptr->User_vname = nw.User_name;
				ptr->Amount = 0;
				ptr->type = 2;
				cart_save.push_back(ptr);
			}
		}
		cout << "Successful operation \n";
	}

	System() {

		ifstream file("user list.txt", ios::in);
		if (file.fail()) {
			cout << "faild download users data" << endl;
			return;
		}
		user_save.clear();
		if (!file.fail()) {
			User odj;
			while (file >> odj.User_name >> odj.Password >> odj.Phone) {
				user_save.push_back(odj);
			}
			file.close();
		}


		ifstream file1("Icart list.txt", ios::in);
		if (file1.fail()) {
			cout << "faild download Icart data" << endl;
			return;
		}
		cart_save.clear();
		if (!file1.fail()) {
			Icart* asd{};
			string User_vname, Phone_number, Password;
			long long Amount;
			int type;
			while (file1 >> Amount >> User_vname >> Phone_number >> Password >> type) {
				if (type == 1) {
					Visacart temp;
					temp.Amount = Amount;
					temp.User_vname = User_vname;
					temp.Password = Password;
					temp.Phone_number = Phone_number;
					temp.type = type;
					asd = new Visacart(temp);
				}
				else {
					Mastercard temp;
					temp.Amount = Amount;
					temp.User_vname = User_vname;
					temp.Password = Password;
					temp.Phone_number = Phone_number;
					temp.type = type;
					asd = new Mastercard(temp);
				}
				cart_save.push_back(asd);
			}
			file1.close();
		}
	}
	~System() {

		ofstream file("user list.txt", ios::out);
		if (file.fail()) {
			cout << "faild download users data" << endl;
			return;
		}
		for (int i = 0; i < user_save.size(); i++) {
			User odj = user_save[i];
			file << odj.User_name + '\n' << odj.Password + '\n' << odj.Phone + '\n';
		}
		file.close();


		ofstream file1("Icart list.txt", ios::out);
		if (file1.fail()) {
			cout << "faild download Icart data" << endl;
			return;
		}
		for (int i = 0; i < cart_save.size(); i++) {
			Icart* asd = cart_save[i];
			file1 << asd->Amount << '\n' << asd->User_vname << '\n' << asd->Phone_number << '\n' << asd->Password << '\n' << asd->type << '\n';
		}
		file1.close();
	}


};

int main() {
	User user_new;
	int op;
restart:
	System sys;
	op = sys.menu();


	if (op == 1) {
		user_new = sys.login();
		if (user_new.User_name == "-1") { return 0; }
	}
	if (op == 2) {
		user_new = sys.sign_up();
	}

	cout << "Hello " << user_new.User_name << endl;
start:
	op = sys.menu2();
	// 1 ----> send money
	if (op == 1) {

		cout << "enter amount the money you want to send : ";
		int money; cin >> money;
		cout << "enter 1 to send by user name , 2 to send by phone number \n";
		int ch; cin >> ch;
		string nmnm; string fon;
		if (ch == 1) {
			cout << "enter the name :";
			cin >> nmnm;
		}
		else {
			cin >> fon;
		}

		int cc = 0;

		for (int i = 0; i < cart_save.size(); i++) {
			if (user_new.User_name == cart_save[i]->User_vname)cc++;
		}

		if (cc == 1) {
			for (int i = 0; i < cart_save.size(); i++) {
				if (user_new.User_name == cart_save[i]->User_vname && ch == 1) {
					cart_save[i]->send_money(nmnm, money);
				}
				else if (user_new.User_name == cart_save[i]->User_vname && ch == 2) {
					cart_save[i]->send_money(money, fon);
				}
			}
		}
		else {
			cout << "1- visacart \n";
			cout << "2- mastercart \n";
			int num; cin >> num;
			Icart* ptr{};

			if (num == 1) {
				for (int i = 0; i < cart_save.size(); i++) {
					if (user_new.User_name == cart_save[i]->User_vname and cart_save[i]->type == 1) {
						ptr = cart_save[i];
					}
				}
			}

			else {
				for (int i = 0; i < cart_save.size(); i++) {
					if (user_new.User_name == cart_save[i]->User_vname and cart_save[i]->type == 2) {
						ptr = cart_save[i];
					}
				}
			}

			if (ch == 1) {
				ptr->send_money(nmnm, money);
			}
			else {
				ptr->send_money(money, fon);
			}

		}

		goto start;
	}
	if (op == 2) {

		int cc = 0;
		for (int i = 0; i < cart_save.size(); i++) {
			if (user_new.User_name == cart_save[i]->User_vname)cc++;
		}
		if (cc == 1) {
			for (int i = 0; i < cart_save.size(); i++) {
				if (user_new.User_name == cart_save[i]->User_vname) {
					cart_save[i]->show_money();
				}
			}
		}
		else {

			cout << "1- visacart \n";
			cout << "2- mastercart \n";
			int num; cin >> num;
			Icart* asd{};
			if (num == 1) {
				for (int i = 0; i < cart_save.size(); i++) {
					if (user_new.User_name == cart_save[i]->User_vname && cart_save[i]->type == 1) {
						asd = cart_save[i];
					}
				}
			}

			else {
				for (int i = 0; i < cart_save.size(); i++) {
					if (user_new.User_name == cart_save[i]->User_vname && cart_save[i]->type == 2) {
						asd = cart_save[i];
					}
				}
			}

			asd->show_money();
		}
		goto start;
	}
	if (op == 3) {
		sys.add_visa(user_new);
		goto start;
	}
	if (op == 4) {
		int cc = 0;
		for (int i = 0; i < cart_save.size(); i++) {
			if (user_new.User_name == cart_save[i]->User_vname)cc++;
		}
		if (cc == 1) {
			for (int i = 0; i < cart_save.size(); i++) {
				if (user_new.User_name == cart_save[i]->User_vname) {
					cart_save[i]->addmoney();
				}
			}
		}
		else {

			cout << "1- visacart \n";
			cout << "2- mastercart \n";
			int num; cin >> num;
			Icart* asd{};
			if (num == 1) {
				for (int i = 0; i < cart_save.size(); i++) {
					if (user_new.User_name == cart_save[i]->User_vname && cart_save[i]->type == 1) {

						asd = cart_save[i];

					}
				}
			}

			else {
				for (int i = 0; i < cart_save.size(); i++) {
					if (user_new.User_name == cart_save[i]->User_vname && cart_save[i]->type == 2) {

						asd = cart_save[i];

					}
				}
			}

			asd->addmoney();
		}
		goto start;
	}
	if (op == 5) {

		int ope;
		cout << "Enter 1 to end programme or 2 to enter another user\n";
		cin >> ope;
		if (ope == 1) { return 0; }
		if (ope == 2) { goto restart; }

	}
}