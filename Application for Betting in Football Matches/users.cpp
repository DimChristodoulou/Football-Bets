#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <fstream>
#include <sstream>


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
			cout << user_id << endl;
			cout << username << endl;
			cout << full_name << endl;
			cout << password << endl;
			cout << type << endl;
			cout << status << endl;
			cout << balance << endl;
			cout << freebets << endl;
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
		
		void Change_Status(string new_status)
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
		
		void Change_Freebets(int new_freebets)
		{
			this->freebets = new_freebets;
		}
};

typedef vector<User> storage_type;

int Update_User_Vector(storage_type &Users,ifstream &Read_User_info_file){
	string userline;
	
	string username,password,status,fullname,suser_id;
	int user_id,balance,freebets,type;
	getline(Read_User_info_file,userline);
	while(getline(Read_User_info_file,userline)){
		suser_id = userline.substr(0,userline.find("|"));
		user_id = atoi(suser_id.c_str());
//		cout << "UserID " << user_id << endl;
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
//		newUser.extendedPrint();
		Users.push_back(newUser);
//		cout << user_id << username << fullname << password << type << status << balance << freebets << endl;
//		cout << userline << endl;
	}
	return user_id;
	
}


bool IsUser(string username_cmp, string password_cmp, int &user_place){
	//Search for a user in the file.
	ifstream User_info_file("Users.csv");
	string line;
	int has_username = 0, has_password = 0, i = 1, in_line = 1, my_line = 1, fu = 0, fp = 0, um = 2, up = 4;
	
	//while (getline(User_info_file, line)) 
	{
		getline(User_info_file, line);
	    istringstream myline(line);
	    string word;
	    //cout << line << "\n";
	    has_username = 0;
	    has_password = 0;
//	    cout << line << endl;
	    while (getline(User_info_file, word, '|') && (has_username == 0 || has_password == 0))
	    {
	    	fu++;
	    	fp++;
//	    	cout << um << up << fu << fp << endl;
//			word = line.substr(8,line.find(",")+1);
//			cout << "Word is: " << word << endl;
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
	}
	return 0;
}


void Initialize_File(ofstream& Usercsv){
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


int Search_User_ID(string username_cmp, string password_cmp){
	//Search for a user in the file.
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

void Write_to_users(storage_type Users, ofstream& User_info_file){
	User_info_file.close();
	User_info_file.open ("Users.csv" , fstream::out | fstream::trunc);
	
	Initialize_File(User_info_file);
	
	int i = 0;
	for (i = 0; i < Users.size(); i++)
	{
		cout << Users[i].Get_Username() << endl;
		cout << Users[i].Get_Password() << endl;
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

void Change_Name_Password(storage_type Users, ofstream& User_info_file){
	string username, password, new_username, new_password;
	int id,user_place;
	
	cout << "Please enter login details again." << endl;
	cout << "Username: ";
	cin >> username;
	cout << "Password: ";
	cin >> password;
	cout << "\n";
	//Enter login details check here//
	if (IsUser(username, password,user_place) == 1)
	{
		id = Search_User_ID(username, password);
		cout << "ID: " << id << endl;
		
		cout << "Successful login.\n";
		cout << "Enter new username: ";
		cin >> new_username;
		cout << "Enter new password: ";
		cin >> new_password;
		
		if (id <= Users.size())
		{
			Users[id].Change_Username(new_username);
			Users[id].Change_Password(new_password);
			
			cout << Users[id].Get_Username() << endl;
			cout << Users[id].Get_Password() << endl;
			
			Write_to_users(Users, User_info_file);
		}
	}
	else
	{
		cout << "Error." << endl;
	}
}

