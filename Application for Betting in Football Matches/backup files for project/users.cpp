#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>

extern int cur_location_size(string location);
extern string cur_location_name(string location, int bet_loc);
extern bool is_empty(ifstream& bets_history);

using namespace std;

class User{
	private:
		string username,password,status,full_name;
		int user_id, balance, type, freebets;
	public:
		User(string name, string pass){
			username=name;
			password=pass;
		}
		
		User(string username_c, string password_c, int type_c, string status_c, int user_id_c, int balance_c, int freebets_c, string full_name_c){
			username=username_c;
			password=password_c;
			full_name=full_name_c;
			type = type_c;
			status = status_c;
			user_id = user_id_c;
			balance = balance_c;
			freebets = freebets_c;
		}

		void User_Info(){
			cout << "Name:" << username <<endl;
			cout << "Pass:" << password <<endl;
		}
		
		void extendedPrint(){
			cout << user_id << "|";
			cout << username << "|";
			cout << full_name << "|";
			cout << password << "|";
			cout << type << "|";
			cout << status << "|";
			cout << balance << "|";
			cout << freebets << "|" << endl;
		}

		string Get_Username(){
			return this->username;
		}
		
		void Change_Username(string new_username)
		{
			this->username = new_username;
		}
		
		string Get_Fullname(){
			return this->full_name;
		}
		
		void Change_Fullname(string new_fullname)
		{
			this->full_name = new_fullname;
		}
		
		int Get_Type()
		{
			return this->type;
		}
		
		void Change_Type(int new_type)
		{
			this->type = new_type;
		}
		
		string Get_Password(){
			return this->password;
		}
		
		void Change_Password(string new_password)
		{
			this->password = new_password;
		}
		
		string Get_Status(){
			return this->status;
		}
		
		void Set_Status(string &new_status)
		{
			this->status = new_status;
		}
		
		int Get_User_Id(){
			return this->user_id;
		}
		
		void Change_User_Id(int new_user_id)
		{
			this->user_id = new_user_id;
		}
		
		int Get_Balance(){
			return this->balance;
		}
		
		void Change_Balance(int new_balance)
		{
			this->balance = new_balance;
		}
		
		int Get_Freebets(){
			return this->freebets;
		}
		
		void Add_Freebets(int new_freebets)
		{
			this->freebets += new_freebets;
		}
};

typedef vector<User> storage_type;

int Update_User_Vector(storage_type &Users,ifstream &Read_User_info_file){					//Sets the current user id for a new player to register.
	string userline;
	
	string username,password,status,fullname,suser_id;
	int user_id,balance,freebets,type;
	getline(Read_User_info_file,userline);
	while(getline(Read_User_info_file,userline)){
		suser_id = userline.substr(0,userline.find("|"));
		user_id = atoi(suser_id.c_str());
		userline.erase(0,userline.find("|")+1);
		username = userline.substr(0,userline.find("|"));
		userline.erase(0,userline.find("|")+1);
		fullname = userline.substr(0,userline.find("|"));
		userline.erase(0,userline.find("|")+1);
		password = userline.substr(0,userline.find("|"));
		userline.erase(0,userline.find("|")+1);
		type = atoi(userline.substr(0,userline.find("|")).c_str());
		userline.erase(0,userline.find("|")+1);
		status = userline.substr(0,userline.find("|"));
		userline.erase(0,userline.find("|")+1);
		balance = atoi(userline.substr(0,userline.find("|")).c_str());
		userline.erase(0,userline.find("|")+1);
		freebets = atoi(userline.substr(0,userline.find("|")).c_str());
		User newUser(username,password,type,status,user_id,balance,freebets,fullname);
		Users.push_back(newUser);
	}
	return user_id;
	
}

bool IsUser(string username_cmp, string password_cmp, int &user_place){													//Checks to see if there is indeed such a user trying to log in.
	ifstream User_info_file("Users.csv");
	string line;
	int has_username = 0, has_password = 0, i = 1, in_line = 1, my_line = 1, fu = 0, fp = 0, um = 2, up = 4;

	getline(User_info_file, line);
    istringstream myline(line);
    string word;
    has_username = 0;
    has_password = 0;
    while (getline(User_info_file, word, '|') && (has_username == 0 || has_password == 0))
    {
    	//Searches the users file and if a userame and a passwod are on the same line, then that user exists and has entered the correct details.
    	fu++;
    	fp++;
        if (word.compare(username_cmp) == 0 && fu == um)
        {
        	has_username = 1;
        	my_line = in_line;
        }
    	if (word.compare(password_cmp) == 0 && has_username == 1 && in_line == my_line && fp == up)
        {
        	has_password = 1;
        }
        i++;
		if (i >= 8 * in_line)
		{
			in_line++;
			um+=8;
			up+=8;
		}
	}
	
	if (has_username == 1 && has_password == 1)
	{
		user_place = in_line;
		return 1;
	}
	return 0;
}

void Initialize_File(ofstream& Usercsv){				//Initializes the Users.csv file with the generic fields.
	Usercsv << "User Id";
	Usercsv << "|";
	Usercsv << "Username";
	Usercsv << "|";
	Usercsv << "Full name";
	Usercsv << "|";
	Usercsv << "Password";
	Usercsv << "|";
	Usercsv << "Type";
	Usercsv << "|";
	Usercsv << "Status";
	Usercsv << "|";
	Usercsv << "Balance";
	Usercsv << "|";
	Usercsv << "Freebets";
	Usercsv << "|";
	Usercsv << "\n";
}

int Search_User_ID(string username_cmp, string password_cmp){						//Searches for a user id thought theiru sername and password.
	ifstream User_info_file("Users.csv");
	string line;
	int has_username = 0, has_password = 0, i = 1, in_line = 1, my_line = 1, fu = 0, fp = 0, um = 2, up = 4;

	{
		getline(User_info_file, line);
	    istringstream myline(line);
	    string word;

	    has_username = 0;
	    has_password = 0;

	    while (getline(User_info_file, word, '|'))
	    {
	    	fu++;
	    	fp++;
	    	
	        if (word.compare(username_cmp) == 0 && fu == um)
	        {
	        	has_username = 1;
	        	my_line = in_line;
	        }
	    	if (word.compare(password_cmp) == 0 && has_username == 1 && in_line == my_line && fp == up)
	        {
	        	has_password = 1;
	        	return (in_line - 1);
	        }
	        i++;
			if (i >= 8 * in_line)
			{
				in_line++;
				um+=8;
				up+=8;
			}
		}
	}
	return 0;
}

void Write_to_users(storage_type &Users, ofstream& User_info_file){				//Writes any changes to the users file.
	User_info_file.close();
	User_info_file.open ("Users.csv" , fstream::out | fstream::trunc);
	
	Initialize_File(User_info_file);
	
	int i = 0;
	for (i = 0; i < Users.size(); i++)
	{
		User_info_file << Users[i].Get_User_Id();
		User_info_file << "|";
		User_info_file << Users[i].Get_Username();
		User_info_file << "|";
		User_info_file << Users[i].Get_Fullname();
		User_info_file << "|";
		User_info_file << Users[i].Get_Password();
		User_info_file << "|";
		User_info_file << Users[i].Get_Type();
		User_info_file << "|";
		User_info_file << Users[i].Get_Status();
		User_info_file << "|";
		User_info_file << Users[i].Get_Balance();
		User_info_file << "|";
		User_info_file << Users[i].Get_Freebets();
		User_info_file << "|";
		User_info_file << "\n";
	}
	
	User_info_file.close();
}

bool Change_Username(storage_type Users, ofstream& User_info_file){			//Changes the username of a user.
	string username, password, new_username, new_password;
	int id,user_place;
	
	cout << "Please enter login details again." << endl;
	cout << "Username: ";
	cin >> username;
	cout << "Password: ";
	cin >> password;
	cout << "\n";
	//Login details check again to determine user id.
	if (IsUser(username, password,user_place) == 1)
	{
		id = Search_User_ID(username, password);
		cout << "ID: " << id << endl;
		
		cout << "Successful login.\n";
		cout << "Enter new username: ";
		cin >> new_username;
		
		if (id <= Users.size())
		{
			Users[id].Change_Username(new_username);
			
			cout << Users[id].Get_Username() << endl;
			
			Write_to_users(Users, User_info_file);
			
			return 1;
		}
	}
	else
	{
		cout << "Error." << endl;
		
		return 0;
	}
}

bool Change_Password(storage_type Users, ofstream& User_info_file){			//Changes the password of a user.
	string username, password, new_username, new_password;
	int id,user_place;
	
	cout << "Please enter login details again." << endl;
	cout << "Username: ";
	cin >> username;
	cout << "Password: ";
	cin >> password;
	cout << "\n";
	//Login details check again to determine user id.
	if (IsUser(username, password,user_place) == 1)
	{
		id = Search_User_ID(username, password);
		cout << "ID: " << id << endl;
		
		cout << "Successful login.\n";
		cout << "Enter new password: ";
		cin >> new_password;
		
		if (id <= Users.size())
		{
			Users[id].Change_Password(new_password);

			cout << Users[id].Get_Password() << endl;
			
			Write_to_users(Users, User_info_file);
			
			return 1;
		}
	}
	else
	{
		cout << "Error." << endl;
		
		return 0;
	}
}

int Bets(ofstream &bets_history, User _user, int bet, int bet_loc, string location){				//Writes to the bets history file.
	time_t rawtime;
  	struct tm * timeinfo;
  	char buffer[80];
  	time (&rawtime);
  	timeinfo = localtime(&rawtime);
  	strftime(buffer,80,"%d-%m-%Y %I:%M:%S",timeinfo);
	string str(buffer);
  	
	bets_history << _user.Get_Username() << "# on " << str << " bet #" << bet << "$ on #" << cur_location_name(location, bet_loc) << "," << "\n";
}

int Print_Bets(ifstream &bets_history, int user_place, storage_type Users){						//Prints a user's bet history.

	bets_history.close();
	bets_history.open ("Bets.csv" , fstream::in);
	
	int i=0;
	string action, temp;

	while(getline(bets_history, action, '\n'))
	{
		temp = action;
		temp = action.substr(0,action.find("#"));
		//Searches throught the bet history file to find matches between the username and the user who has placed the bet.
		if (Users[user_place].Get_Username().compare(temp) == 0)
		{
			cout << action.substr(0,action.find(",")) << endl;
		}
	}
}

void Show_bets_history(ifstream &bets_history){													//Prints the last 20 bets.

	bets_history.close();
	bets_history.open ("Bets.csv" , fstream::in);
	
	int i=0;
	string action;
	while(getline(bets_history, action, '\n') && i < 20)
	{
		cout << action.substr(0,action.find(",")) << endl;
		i++;
	}
}

bool Assign_Freebet(storage_type Users, ofstream& User_info_file)								//Assigns a freebet coupon to a player.
{
	int id, i = 0;
	
	for (i = 0; i < Users.size(); i++)
	{
		cout << i+1 << ": " << Users[i].Get_Username() << endl;
	}
	
	cout << "Enter player id to assign freebet coupon to: ";
	cin >> id;
	
	if (id <= Users.size())
	{
		Users[id-1].Add_Freebets(1);
		Write_to_users(Users, User_info_file);
		return 1;
	}
	else
	{
		return 0;
	}
}

int Place_bet(storage_type Users, ofstream& User_info_file, int user_place, int total_bets, ofstream& bets_history, string location)		//Places a user bet.
{
	int bet, bet_loc, new_bal;
	int j, k, l, m;
	
	cout << "Available balance: " << Users[user_place].Get_Balance() - total_bets << endl;
	cout << "Available freebet coupons: " << Users[user_place].Get_Freebets() << endl;
	
	cout << "Enter 'Cancel/Abort' to cancel the procedure, else input node ID: ";
	string temp;
	cin >> temp;
	bet_loc = atoi(temp.c_str());
	if(temp=="Cancel" || temp=="Abort"){
		return total_bets;
	}
	
	do
	{
		//A freebet coupon is considered equal to a betting amount of 30$.
		cout << "How much to bet? Press -1 to play a freebet: ";
		cin >> bet;
		
		if (bet == -1 && Users[user_place].Get_Freebets() > 0)
		{
			cout << "Played a freebet coupon, which equals a betting amount of 30$." << endl;
		}
		else if ((Users[user_place].Get_Balance() - total_bets) < bet)
		{
			cout << "Not enough funds." << endl;
		}
	}
	while (((Users[user_place].Get_Balance() - total_bets) < bet));
	
	if ((bet > 0 && (Users[user_place].Get_Balance() - total_bets) >= bet && bet_loc <= cur_location_size(location)))
	{
		total_bets += bet;
		new_bal = Users[user_place].Get_Balance() - total_bets;
		Users[user_place].Change_Balance(new_bal);
		Write_to_users(Users, User_info_file);
		cout << "You bet " << bet << " on " << bet_loc << endl << "Good luck!" << endl;
		Bets(bets_history,Users[user_place],bet, bet_loc, location);		

		return total_bets;
	}
	else if (bet == -1 && Users[user_place].Get_Freebets() > 0)
	{
		bet = 30;
		Users[user_place].Add_Freebets(-1);
		Write_to_users(Users, User_info_file);
		cout << "You bet " << bet << " on " << bet_loc << " using a freebet coupon." << endl << "Good luck!" << endl;
		Bets(bets_history,Users[user_place],bet, bet_loc, location);		

		return total_bets;
	}
	else
	{
		cout << "Error." << endl;
		return total_bets;
	}
}

int Add_Credits(storage_type Users, ofstream& User_info_file, int total_credits)			//Users Add funds to their account.
{
	string username, password;
	int credit, new_balance, id, user_place;
	
	cout << "Please enter login details again." << endl;
	cout << "Username: ";
	cin >> username;
	cout << "Password: ";
	cin >> password;
	cout << "\n";
	if (IsUser(username, password, user_place) == 1)
	{
		id = Search_User_ID(username, password);
		cout << "ID: " << id << endl;
		
		cout << "Successful login.\n";
		cout << "How much credit to add?" << endl;
		cin >> credit;
		
		if (credit > 0)
		{
			total_credits += credit;
			new_balance = Users[id].Get_Balance() + total_credits;
			Users[id].Change_Balance(new_balance);
			
			Write_to_users(Users, User_info_file);
			
			return total_credits;
		}
		else
		{
			cout << "Error!" << endl;
			
			return total_credits;
		}
	}
	else
	{
		cout << "Error." << endl;
		
		return total_credits;
	}
}
