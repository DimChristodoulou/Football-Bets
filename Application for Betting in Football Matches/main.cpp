#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <fstream>
#include <sstream>
#include "hierarchy.cpp"
#include "users.cpp"
#include "management.cpp"

using namespace std;

extern vector<Category> hierarchy_vector;

typedef vector<User> storage_type;

int Register(storage_type &Users,User new_user){
        int i;
        for(i=0;i< Users.size(); i++){
                if(!new_user.Get_Username().compare( Users[i].Get_Username() )){
                		cout << "Username already exists. Please use another." << endl;
                        return 0;
            	}
        }
        Users.push_back(new_user);
}

bool is_empty(ifstream& Usercsv){
    return Usercsv.peek() == ifstream::traits_type::eof();
}

void New_User(storage_type Users, int userid, ofstream& User_info_file){
	
	User_info_file.close();
	User_info_file.open ("Users.csv" , fstream::out | fstream::app);
	
	string name;
  	string pass;
  	string real_name;
       		
    cout << "To register, please input your full name, a valid username (6-20 characters) and a password (6-20 characters)." << endl;
	cout << "Real name:\n";
    cin >> real_name;
    cout << "Username:\n";
    cin >> name;
    cout << "Password:\n";
    cin >> pass;
    User new_user(name, pass);
    if(Register(Users, new_user)){
			User_info_file << ++userid;
			User_info_file << "|";
			User_info_file << name;
			User_info_file << "|";
			User_info_file << real_name;
			User_info_file << "|";
			User_info_file << pass;
			User_info_file << "|";
			User_info_file << "1";
			User_info_file << "|";
			User_info_file << "Whatever";
			User_info_file << "|";
			User_info_file << 0;
			User_info_file << "|";
			User_info_file << 0;
			User_info_file << "|";
			User_info_file << "\n";
		}
		cout << userid << endl;
		Users[userid-1].User_Info();
}

string Update_Location(string location,int a){
	int i=0,j,k,l;
	string cur_location = location, temp = location , cat_name, sub_name;
	while(!location.empty()){
		location = location.erase(0,location.find("/")+1);
		i++;
	}
	if(i == 2)
		cur_location += hierarchy_vector[a-1].get_name() + "/";
	else if(i==3){
		temp = temp.erase(0,temp.find("/")+1);
		temp = temp.erase(0,temp.find("/")+1);
		temp = temp.substr(0,temp.find("/"));
		cout << temp << endl;
		for(j=0; j<hierarchy_vector.size(); j++){
			if(temp == hierarchy_vector[j].get_name()){
				cur_location += hierarchy_vector[j].get_sub_vector()[a-1].get_name() + "/";
			}
		}
	}
	else if(i==4){
		temp = temp.erase(0,temp.find("/")+1);
		temp = temp.erase(0,temp.find("/")+1);
		cat_name = temp.substr(0,temp.find("/"));
		temp = temp.erase(0,temp.find("/")+1);
		temp = temp.substr(0,temp.find("/"));
		cout << temp << endl;
		for(j=0; j<hierarchy_vector.size(); j++){
			if(cat_name == hierarchy_vector[j].get_name()){
				for(k=0;k<hierarchy_vector[j].get_sub_vector().size();k++){
					if(hierarchy_vector[j].get_sub_vector()[k].get_name()==temp)
						cur_location += hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[a-1].get_name() + "/";
				}
			}
		}
	}
	else if(i==5){
		temp = temp.erase(0,temp.find("/")+1);
		temp = temp.erase(0,temp.find("/")+1);
		cat_name = temp.substr(0,temp.find("/"));
		temp = temp.erase(0,temp.find("/")+1);
		sub_name = temp.substr(0,temp.find("/"));
		temp = temp.erase(0,temp.find("/")+1);
		temp = temp.substr(0,temp.find("/"));
		cout << temp << endl;
		for(j=0; j<hierarchy_vector.size(); j++){
			if(cat_name == hierarchy_vector[j].get_name()){
				for(k=0;k<hierarchy_vector[j].get_sub_vector().size();k++){
					if(hierarchy_vector[j].get_sub_vector()[k].get_name()==sub_name){
						for(l=0; l<hierarchy_vector[j].get_sub_vector()[k].get_event_vector().size(); l++){
							if(hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_name()==temp)
								cur_location += hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_market_vector()[a-1].get_name() + "/";
						}
					}
				}
			}
		}
	}
	cout << cur_location << endl;
	return cur_location;
}

void Print_Available_Nodes(string location, int toggle, int user_type){
	int i=0,j=0,k=0,l=0,m=0;
	string cur_location = location, cat_name, subcat_name, event_name, market_name;
	cout << "----------------------------------" << endl;
	while(!location.empty()){
		location = location.erase(0,location.find("/")+1);
		i++;
	}
	if(i==2){
		for(j=0; j<hierarchy_vector.size(); j++){
			if(hierarchy_vector[j].is_visible()){
				cout << k+1 << ". " << hierarchy_vector[j].get_name() << endl;					//CHECK VISIBILITY
				k++;
			}
		}
	}
	else if(i==3){
		cur_location = cur_location.erase(0,cur_location.find("/")+1);
		cur_location = cur_location.erase(0,cur_location.find("/")+1);
		cur_location = cur_location.substr(0,cur_location.find("/"));
		cout << cur_location << endl;
		for(j=0; j<hierarchy_vector.size(); j++){
			if(cur_location == hierarchy_vector[j].get_name()){
				hierarchy_vector[j].print_subcategories();
			}
		}
	}
	else if(i==4){
		cur_location = cur_location.erase(0,cur_location.find("/")+1);
		cur_location = cur_location.erase(0,cur_location.find("/")+1);
		cat_name = cur_location.substr(0,cur_location.find("/"));
		cur_location = cur_location.erase(0,cur_location.find("/")+1);
		subcat_name = cur_location.substr(0,cur_location.find("/"));
		cout << cur_location << endl;
		for(j=0; j<hierarchy_vector.size(); j++){
			if(cat_name == hierarchy_vector[j].get_name()){
				for(int k=0;k<hierarchy_vector[j].get_sub_vector().size();k++){
					if(subcat_name == hierarchy_vector[j].get_sub_vector()[k].get_name())
						hierarchy_vector[j].get_sub_vector()[k].print_events();
				}
				//hierarchy_vector[j].print_subcategories();
			}
		}
	}
	else if(i==5){
		cur_location = cur_location.erase(0,cur_location.find("/")+1);
		cur_location = cur_location.erase(0,cur_location.find("/")+1);
		cat_name = cur_location.substr(0,cur_location.find("/"));
		cur_location = cur_location.erase(0,cur_location.find("/")+1);
		subcat_name = cur_location.substr(0,cur_location.find("/"));
		cur_location = cur_location.erase(0,cur_location.find("/")+1);
		event_name = cur_location.substr(0,cur_location.find("/"));
	
		cout << cur_location << endl;
		for(j=0; j<hierarchy_vector.size(); j++){
			if(cat_name == hierarchy_vector[j].get_name()){
				for(int k=0;k<hierarchy_vector[j].get_sub_vector().size();k++){
					if(subcat_name == hierarchy_vector[j].get_sub_vector()[k].get_name()){
						for(l=0; l<hierarchy_vector[j].get_sub_vector()[k].get_event_vector().size(); l++){
							if(event_name == hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_name())
								hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].print_markets();
						}
					}
				}
			}
		}
	}
	else if(i==6){
		cur_location = cur_location.erase(0,cur_location.find("/")+1);
		cur_location = cur_location.erase(0,cur_location.find("/")+1);
		cat_name = cur_location.substr(0,cur_location.find("/"));
		cur_location = cur_location.erase(0,cur_location.find("/")+1);
		subcat_name = cur_location.substr(0,cur_location.find("/"));
		cur_location = cur_location.erase(0,cur_location.find("/")+1);
		event_name = cur_location.substr(0,cur_location.find("/"));
		cur_location = cur_location.erase(0,cur_location.find("/")+1);
		market_name = cur_location.substr(0,cur_location.find("/"));
		cout << cur_location << endl;
		for(j=0; j<hierarchy_vector.size(); j++){
			if(cat_name == hierarchy_vector[j].get_name()){
				for(int k=0;k<hierarchy_vector[j].get_sub_vector().size();k++){
					if(subcat_name == hierarchy_vector[j].get_sub_vector()[k].get_name()){
						for(l=0; l<hierarchy_vector[j].get_sub_vector()[k].get_event_vector().size(); l++){
							if(event_name == hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_name()){
								for(m=0; m<hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_market_vector().size(); m++){
									if(market_name == hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_market_vector()[m].get_name()){
										hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_market_vector()[m].print_selections(toggle);
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

void Print_Options(int user_type){
	if(user_type == 1){
		cout << "Logged in as Punter." << endl;
		cout << "A (Account), to manage account information." << endl;
		cout << "P (Place), to place a bet" << endl;
	}
	else if(user_type == 2){
		cout << "Logged in as Trader." << endl;
		cout << "B (Bets), to show last 20 bets." << endl;
		cout << "F (Freebets), to assign coupon to a player." << endl; 
	}
	else if(user_type == 3){
		cout << "Logged in as Director." << endl;
		cout << "B (Bets), to show last 20 bets." << endl;
		cout << "F (Freebets), to assign coupon to a player." << endl; 
		cout << "S (Save), to save current state and synchronize system data files." << endl;
		cout << "L (Logs), to show last 25 system commands." << endl;
		cout << "U (Users), to manage users." << endl;
		cout << "V (Visibility), to change node visibility." << endl;
		cout << "R (Rename), to rename node." << endl;
		cout << "N (New), to add a new node." << endl;
		cout << "C (Copy), to copy a node (as an invisible node)" << endl;
		cout << "D (Delete), to delete a node." << endl;
	}
	cout << "H (Home), to return to home screen." << endl;
	cout << "T (Toggle), to change price preview." << endl;
	cout << "X (Exit), to exit system." << endl;
}

int Login_after_reg(string location){
	char choice;	
	cout << "Welcome to Stoiximania!\n";
	cout << "Successful login.\n";
	cout << location << endl;
	//Do whatever...
	cout << "Please choose:\n";
	for(int i=0; i<hierarchy_vector.size(); i++)
			cout << i+1 << ". " << hierarchy_vector[i].get_name() << endl;
	cin >> choice;
	if (choice == 'X' || choice == 'x')
	{
		cout << "Exiting...";
		return 0;
	}
}

int Toggle_prices(int toggle){
	if (toggle == 0)
	{
		return toggle = 1;
	}
	else if (toggle == 1)
	{
		return toggle = 0;
	}
}

int Login(string location, ofstream& User_info_file, ifstream &Read_User_info_file, storage_type Users, ifstream &hierarchy_file, ofstream &write_hierarchy_file ,int toggle){
	char choice,choice2;
	string username, password,name,line;
	int user_place,id,lines=0;
	ofstream logfile;
	logfile.open("audit.log", fstream::out | fstream::app);
	ifstream read_logfile;
	read_logfile.open("audit.log", fstream::in);
	cout << "Welcome to Stoiximania!\n";
	cout << "Please enter login details or guest:guest to enter as a guest.\n";
	cout << "Username: ";
	cin >> username;
	cout << "Password: ";
	cin >> password;
	cout << "\n";
	//Enter login details check here//
	if (IsUser(username, password, user_place) == 1){
		cout << "Successful login.\n";
		cout << location << endl;
		Print_Options(Users[user_place-1].Get_Type());
		Print_Available_Nodes(location, toggle,Users[user_place-1].Get_Type());
		cin >> choice;
		int a = choice - '0';
		while(choice!='X' && choice!='x'){
			if(Users[user_place-1].Get_Type()==1){
				if  (choice == 'A' || choice == 'a'){
					Change_Name_Password(Users, User_info_file);
				}	
			}
			else if(Users[user_place-1].Get_Type()==3){
				//Rename function call
				if  (choice == 'R' || choice == 'r'){
					Print_Available_Nodes(location,toggle,Users[user_place-1].Get_Type());
					cout << "Enter Node ID. " << endl;
					cin >> id;
					cout << "Enter a new name or 'Cancel/Abort' to cancel the procedure: ";
					cin >> name;
					if(name!="Cancel" && name!="Abort"){
						Rename(location,name,id);
						Log(logfile,Users[user_place-1],location,'R', name);
					}
				}
				//New node function call
				else if(choice == 'N' || choice == 'n'){
					Print_Available_Nodes(location,toggle,Users[user_place-1].Get_Type());
					cout << "Enter a new name or 'Cancel/Abort' to cancel the procedure: ";
					getline(cin,name);
					getline(cin,name);
					if(name!="Cancel" && name!="Abort"){
						New(location,name);
						Log(logfile,Users[user_place-1],location,'N', name);
					}
				}
				//Copy function call
				else if(choice == 'C' || choice == 'c'){
					Print_Available_Nodes(location,toggle,Users[user_place-1].Get_Type());
					cout << "Enter 'Cancel/Abort' to cancel the procedure, else input node ID: ";
					string temp;
					cin >> temp;
					id = atoi(temp.c_str());
					if(temp!="Cancel" && temp!="Abort"){
						Copy(location,id);
						Log(logfile,Users[user_place-1],location,'C', " ");
					}
				}
				//Deletion function call
				else if(choice == 'D' || choice == 'd'){
					Print_Available_Nodes(location,toggle,Users[user_place-1].Get_Type());
					cout << "Enter 'Cancel/Abort' to cancel the procedure, else input node ID: ";
					string temp;
					cin >> temp;
					id = atoi(temp.c_str());
					if(temp!="Cancel" && temp!="Abort"){
						Delete(location,id);
						Log(logfile,Users[user_place-1],location,'D', " ");
					}
				}
				//Visibility function call
				else if(choice == 'V' || choice == 'v'){
					Print_Available_Nodes(location,toggle,Users[user_place-1].Get_Type());
					cout << "Enter 'Cancel/Abort' to cancel the procedure, else input node ID: ";
					string temp;
					cin >> temp;
					id = atoi(temp.c_str());
					if(temp!="Cancel" && temp!="Abort"){
						Visibility(location,id);
						Log(logfile,Users[user_place-1],location,'D', " ");
					}
				}
				//Log Print function call
				else if(choice == 'L' || choice == 'l'){
					Print_Log(read_logfile);
				}
				//Users management
				else if(choice == 'U' || choice == 'u'){
					cout << "V (View), to show user array." << endl;
					cout << "S (Search), to search for a user." << endl;
					cout << "L (Lock), to lock a user account." << endl;
					cin >> choice2;
					if(choice2 == 'V' || choice2 == 'v'){
						Print_Users();
					}
				}
			}
			if (a <= hierarchy_vector.size()){
				//cout << "You've chosen " << a << " " << location << endl;
				location = Update_Location(location,a);
				if(Users[user_place-1].Get_Type()==1){
					Log(logfile,Users[user_place-1],location,'-'," ");
				}
			}
			else if(choice == 'H' || choice == 'h' ){
				location = "Location:/Stoiximania/";
				cout << location << endl;
			}
			else if(choice == 'T' || choice == 't'){
				Toggle_prices(toggle);
			}
			Print_Options(Users[user_place-1].Get_Type());
			Print_Available_Nodes(location,toggle,Users[user_place-1].Get_Type());
			cin >> choice;
			a = choice - '0';
			cout << endl;
		}
	}
	else if (username.compare("guest") == 0 && password.compare("guest") == 0){
		cout << "You logged in as a guest\n";
		cout << location << endl;
//		for(int i=0; i<hierarchy_vector.size(); i++)
//			cout << i+1 << ". " << hierarchy_vector[i].get_name() << endl;
		Print_Options(Users[user_place-1].Get_Type());
		Print_Available_Nodes(location,toggle,Users[user_place-1].Get_Type());
		cin >> choice;
		int a = choice - '0';
//		if (choice == 'X' || choice == 'x'){
//			cout << "Exiting...";
//			return 0;
//		}
		while(choice!='X' && choice!='x'){
			if (a <= hierarchy_vector.size()){
				//cout << "You've chosen " << a << " " << location << endl;
				location = Update_Location(location,a);
			}
			else if(choice == 'H' || choice == 'h' ){
				location = "Location:/Stoiximania/";
				cout << location << endl;
			}
			Print_Options(Users[user_place-1].Get_Type());
			Print_Available_Nodes(location,toggle,Users[user_place-1].Get_Type());
			cin >> choice;
			a = choice - '0';
			cout << endl;
		}
	}
	else{
		cout << "Unrecognizable details!\n\n\n";
	}		
}

int main(int argc, char *argv[]){
	int userid=0;
	int toggle = 0;
	string name,location="Location:/Stoiximania/";
	//string username, password;
	int x, y;
	storage_type Users;
	ofstream User_info_file;
	ifstream Read_User_info_file;
	ifstream hierarchy_file;
	ofstream write_hierarchy_file;
	User_info_file.open ("Users.csv" , fstream::out | fstream::app);
	Read_User_info_file.open ("Users.csv" , fstream::in);
	write_hierarchy_file.open("Hierarchy.dat", fstream::out | fstream::app);
	hierarchy_file.open ("Hierarchy.dat", fstream::in);
	update_hierarchy(hierarchy_file);
	if(is_empty(Read_User_info_file))
	{
		cout << endl;
		Initialize_File(User_info_file);
	}
	userid = Update_User_Vector(Users, Read_User_info_file);
	if(argc>1){
		string a, argv1;
        argv1 += argv[1];
        a += "-R";
		if(argv1.compare(a) == 0){
       		New_User(Users, userid, User_info_file);
       		Login_after_reg(location);
		}
		else
			cout << "Error" << endl;
	}
	else{
		//hierarchy_vector[0].print();
		//cout << "Location:/Stoiximania/" << hierarchy_vector[2].print() << "\n";
		Login(location, User_info_file, Read_User_info_file, Users, hierarchy_file, write_hierarchy_file, toggle);
		//Write_to_users(Users, User_info_file);
		//cout << "Unregistered Access" << endl;
	}
	User_info_file.close();
}



