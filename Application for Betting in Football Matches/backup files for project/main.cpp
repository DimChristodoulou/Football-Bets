#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "hierarchy.cpp"
#include "users.cpp"
#include "management.cpp"

using namespace std;

extern vector<Category> hierarchy_vector;																									//Global vector in order to use in every .cpp file

typedef vector<User> storage_type;

int Register(storage_type &Users,User new_user){																							//Register function is used to check if user is already registered in the users file.
        int i;
        for(i=0;i< Users.size(); i++){
                if(!new_user.Get_Username().compare( Users[i].Get_Username() )){
                		cout << "Username already exists. Please use another." << endl;
                        return 0;
            	}
        }
        Users.push_back(new_user);
}

bool is_empty(ifstream& Usercsv){																											//Check if a file is empty by looking at the first character of the file.
    return Usercsv.peek() == ifstream::traits_type::eof();
}

void New_User(storage_type Users, int userid, ofstream& User_info_file){																	//Register new user in the Users.csv file.
	
	User_info_file.close();
	User_info_file.open ("Users.csv" , fstream::out | fstream::app);																		//Opening the Users.csv file with append mode.
	
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
    User new_user(name, pass);																												//Calling User constructor, then adding user to file.
    if(Register(Users, new_user)){
			User_info_file << ++userid;																										//In this case, "|" is used as a delimiter.
			User_info_file << "|";
			User_info_file << name;
			User_info_file << "|";
			User_info_file << real_name;
			User_info_file << "|";
			User_info_file << pass;
			User_info_file << "|";
			User_info_file << "1";																											//Default user type after registering is punter. To change user type, please enter the desired user type in the appropriate field of the Users.csv file.
			User_info_file << "|";
			User_info_file << "A";																											//Default user status is active.
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

string Update_Location(string location,int a, int user_type){																								//This function is called after every navigation attempt and updates the location string to hold the current location.
	int i=0,j,k,l;
	string cur_location = location, temp = location , cat_name, sub_name;
	while(!location.empty()){																												//For each "/" found in the location string, i is incremented. According to the location, i(continued)
																																			//can be either 2(category), 3(subcategory), 4(event), etc.
		location = location.erase(0,location.find("/")+1);
		i++;
	}
	if(i == 2){																																//If current location is a category node, just append the name of the category to the location string.
		if(user_type >= 2)
			cur_location += hierarchy_vector[a-1].get_name() + "/";
		else{
			int j, q = 0;
			for(j = 0; j < hierarchy_vector.size(); j++){
				if (hierarchy_vector[j].is_visible()){
					q++;
					if (q == a)
						cur_location += hierarchy_vector[j].get_name() + "/";
				}
			}
		}
	}
	else if(i==3){																															//If current location is a subcategory node, find which category contains the current node and append the name of the subcategory to the location string.
		temp = temp.erase(0,temp.find("/")+1);
		temp = temp.erase(0,temp.find("/")+1);
		temp = temp.substr(0,temp.find("/"));
		cout << temp << endl;
		for(j=0; j<hierarchy_vector.size(); j++){
			if(temp == hierarchy_vector[j].get_name()){
				if(user_type >= 2)
					cur_location += hierarchy_vector[j].get_sub_vector()[a-1].get_name() + "/";
				else{
					int p, q = 0;
					for(p = 0; p < hierarchy_vector[j].get_sub_vector().size(); p++){
						if (hierarchy_vector[j].get_sub_vector()[p].is_visible()){
						q++;
						if (q == a)
							cur_location += hierarchy_vector[j].get_sub_vector()[p].get_name() + "/";
						}
					}
				}
			}
		}
	}
	else if(i==4){																															//If current location is an event node, find which subcategory contains the current node and append the name of the event to the location string.
		temp = temp.erase(0,temp.find("/")+1);
		temp = temp.erase(0,temp.find("/")+1);
		cat_name = temp.substr(0,temp.find("/"));
		temp = temp.erase(0,temp.find("/")+1);
		temp = temp.substr(0,temp.find("/"));
		cout << temp << endl;
		for(j=0; j<hierarchy_vector.size(); j++){
			if(cat_name == hierarchy_vector[j].get_name()){
				for(k=0;k<hierarchy_vector[j].get_sub_vector().size();k++){
					if(hierarchy_vector[j].get_sub_vector()[k].get_name()==temp){
						if(user_type >= 2)
							cur_location += hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[a-1].get_name() + "/";
						else{
							int p, q = 0;
							for(p = 0; p < hierarchy_vector[j].get_sub_vector()[k].get_event_vector().size(); p++){
								if (hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[p].is_visible()){
								q++;
								if (q == a)
									cur_location += hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[p].get_name() + "/";
								}
							}
						}
					}
				}
			}
		}
	}
	else if(i==5){																															//If current location is a market node, find which event contains the current node and append the name of the market to the location string.
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
							if(hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_name()==temp){
								if(user_type >= 2)
									cur_location += hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_market_vector()[a-1].get_name() + "/";
								else{
									int p, q = 0;
									for(p = 0; p < hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_market_vector().size(); p++){
										if (hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_market_vector()[p].is_visible()){
										q++;
										if (q == a)
											cur_location += hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_market_vector()[p].get_name() + "/";
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
	//There is no need to write a block for the selections, because the user cannot go below the selections level.
	cout << cur_location << endl;
	return cur_location;
}

void Print_Available_Nodes(string location, int toggle, int user_type){ 									//Prints the nodes that each user can see (hidden and non-hidden).
	int i=0,j=0,k=0,l=0,m=0;
	string cur_location = location, cat_name, subcat_name, event_name, market_name;
	cout << "----------------------------------" << endl;
	while(!location.empty()){
		location = location.erase(0,location.find("/")+1);
		i++;
	}
	if(i==2){
		for(j=0; j<hierarchy_vector.size(); j++){
			if(user_type==1){
				if(hierarchy_vector[j].is_visible()){
					cout << k+1 << ". " << hierarchy_vector[j].get_name() << endl;
					k++;
				}
			}
			else{
				cout << k+1 << ". " << hierarchy_vector[j].get_name() << endl;					
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
				if(user_type==1){
					hierarchy_vector[j].print_visible_subcategories();
				}
				else
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
					if(subcat_name == hierarchy_vector[j].get_sub_vector()[k].get_name()){
						if(user_type==1)
							hierarchy_vector[j].get_sub_vector()[k].print_visible_events();
						else
							hierarchy_vector[j].get_sub_vector()[k].print_events();
					}
				}
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
							if(event_name == hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_name()){
								if(user_type==1)
									hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].print_visible_markets();
								else
									hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].print_markets();
							}
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
										if(user_type==1)
											hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_market_vector()[m].print_visible_selections(toggle);
										else
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

void Print_Options(int user_type){																			//Prints the options each user has, based on their type.
	if(user_type == 1){
		cout << "Logged in as Punter." << endl;
		cout << "A (Account), to manage account information." << endl;
		cout << "P (Place), to place a bet" << endl;
	}
	else if(user_type == 2){
		cout << "Logged in as Trader." << endl;
		cout << "B (Bets), to show last 20 bets." << endl;
		cout << "F (Freebets), to assign coupon to a player." << endl;
		cout << "V (Void) to cancel a selection." << endl;
		cout << "S (Settle) to settle the market." << endl;
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
	cout << "Please choose:\n";
	for(int i=0; i<hierarchy_vector.size(); i++)
			cout << i+1 << ". " << hierarchy_vector[i].get_name() << endl;
	cin >> choice;
	if (choice == 'X' || choice == 'x'){
		cout << "Exiting...";
		return 0;
	}
}

int Toggle_prices(int toggle){																		//Toggles the price viewing.
	if (toggle == 0)
		return toggle = 1;
	else if (toggle == 1)
		return toggle = 0;
}

int Login(string location, ofstream& User_info_file, ifstream &Read_User_info_file, storage_type Users, ifstream &hierarchy_file, ofstream &write_hierarchy_file){		//Basic function after a user logs in.
	string choice,choice2, choice3;
	string username, password,name,line;
	int user_place,id,lines=0;
	int total_bets = 0, total_credits = 0;
	int toggle = 0;
	
	ofstream logfile;
	logfile.open("audit.log", fstream::out | fstream::app);
	ifstream read_logfile;
	read_logfile.open("audit.log", fstream::in);
	
	ofstream bets_history;
	bets_history.open("Bets.csv", fstream::out | fstream::app);
	ifstream read_bets_history;
	read_bets_history.open("Bets.csv", fstream::in);
	
	cout << "Welcome to Stoiximania!\n";
	cout << "Please enter login details or guest:guest to enter as a guest.\n";
	cout << "Username: ";
	cin >> username;
	cout << "Password: ";
	cin >> password;
	cout << "\n";
	if ((IsUser(username, password, user_place) == 1) && Users[user_place-1].Get_Status().at(0)!='L' ){
		cout << "Successful login.\n";
		cout << location << endl;
		Print_Options(Users[user_place-1].Get_Type());
		Print_Available_Nodes(location, toggle,Users[user_place-1].Get_Type());
		cin >> choice;
		int a = atoi(choice.c_str());
		transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
		while(choice!="X" && choice!="x"){
			if(Users[user_place-1].Get_Type()==1){
				if  (choice == "a" || choice == "account"){
					cout << "Punter: " << Users[user_place-1].Get_Username() << endl;
					cout << "Available Balance: " << Users[user_place-1].Get_Balance() << endl;
					cout << "Available Freebets: " << Users[user_place-1].Get_Freebets() << endl << endl;
					cout << "Options: " << endl;
					cout << "R (Rename), to change username." << endl;
					cout << "P (Password), to change password." << endl;
					cout << "B (Bets), to show bet history." << endl;
					cout << "D (Deposit), to to fill account and increase balance." << endl;
					cin >> choice3;
					transform(choice3.begin(), choice3.end(), choice3.begin(), ::tolower);
					if (choice3 == "r" || choice3 == "rename")
					{
						if (Change_Username(Users, User_info_file) == 1)
						{
							cout << "Username changed successfully." << endl;
							cout << "Exiting system, please log in again." << endl;
							User_info_file.close();
							Read_User_info_file.close();
							write_hierarchy_file.close();
							write_hierarchy_file.close();
							
							return 0;
						}
					}
					else if (choice3 == "p" || choice3 == "password")
					{
						if (Change_Password(Users, User_info_file) == 1);
						{
							cout << "Password changed successfully." << endl;
							cout << "Exiting system, please log in again." << endl;
							User_info_file.close();
							Read_User_info_file.close();
							write_hierarchy_file.close();
							write_hierarchy_file.close();
							
							return 0;
						}
						
					}
					else if (choice3 == "b" || choice3 == "bets")
					{
						Print_Bets(read_bets_history, user_place-1, Users);
					}
					else if (choice3 == "d" || choice3 == "deposit")
					{
						total_credits = Add_Credits(Users, User_info_file, total_credits);
						cout << "Total deposits for this session: " << total_credits << endl;
					}
				}
				else if (choice == "p" || choice == "place")
				{
					int i = 0;
					string temp_loc = location;
					
					while(!temp_loc.empty()){
						temp_loc = temp_loc.erase(0,temp_loc.find("/")+1);
						i++;
					}

					if (i == 6)
					{
						total_bets = Place_bet(Users, User_info_file, user_place-1, total_bets, bets_history, location);
						cout << "Total betting for this session: " << total_bets << endl;
					}
				}	
			}
			else if(Users[user_place-1].Get_Type()==2){
				//Last 20 bets.
				if  (choice == "b" || choice == "bets"){
					Show_bets_history(read_bets_history);
				}
				//Freebets.
				else if(choice == "f" || choice == "freebets"){
					if (Assign_Freebet(Users, User_info_file) == 1)
					{
						cout << "Freebet assigned." << endl;
						cout << "Exiting system for security purposes." << endl;
						User_info_file.close();
						Read_User_info_file.close();
						write_hierarchy_file.close();
						write_hierarchy_file.close();
							
						return 0;
					}
				}
				//Voiding.
				else if(choice == "v" || choice == "void")
				{
					if (Selection_void(Users, read_bets_history, location, user_place, logfile, User_info_file) == 1)
					{
						cout << "Voided successfully, exiting system." << endl;
						
						User_info_file.close();
						Read_User_info_file.close();
						write_hierarchy_file.close();
						write_hierarchy_file.close();
							
						return 0;
					}
				}
				//Settling
				else if(choice == "s" || choice == "settle")
				{
					if (Selection_settle(Users, read_bets_history, location, user_place, logfile, User_info_file) == 1)
					{
						cout << "Settled successfully, exiting system." << endl;
						
						User_info_file.close();
						Read_User_info_file.close();
						write_hierarchy_file.close();
						write_hierarchy_file.close();
							
						return 0;
					}
				}
			}
			else if(Users[user_place-1].Get_Type()==3){
				//Rename function call
				if  (choice == "r" || choice == "rename"){
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
				else if(choice == "n" || choice == "new"){
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
				else if(choice == "c" || choice == "copy"){
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
				else if(choice == "d" || choice == "delete"){
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
				else if(choice == "v" || choice == "visibility"){
					Print_Available_Nodes(location,toggle,Users[user_place-1].Get_Type());
					cout << "Enter 'Cancel/Abort' to cancel the procedure, else input node ID: ";
					string temp;
					cin >> temp;
					id = atoi(temp.c_str());
					if(temp!="Cancel" && temp!="Abort"){
						Visibility(location,id);
						Log(logfile,Users[user_place-1],location,'V', " ");
					}
				}
				//Log Print function call
				else if(choice == "l" || choice == "logs"){
					Print_Log(read_logfile);
				}
				//Save function call
				else if(choice == "s" || choice == "save")
					Save();
				//Users management
				else if(choice == "u" || choice == "users"){
					cout << "V (View), to show user array." << endl;
					cout << "S (Search), to search for a user." << endl;
					cout << "L (Lock), to lock a user account." << endl;
					cin >> choice2;
					transform(choice2.begin(), choice2.end(), choice2.begin(), ::tolower);
					if(choice2 == "v" || choice2 == "view")
						Print_Users();
					if(choice2 == "s" || choice2 == "search")
						Search(Users);
					if(choice2 == "l" || choice2 == "lock")
						Lock_User(Users);
				}
				//Bets.
				else if  (choice == "b" || choice == "bets"){
					Show_bets_history(read_bets_history);
				}
				//Freebets.
				else if(choice == "f" || choice == "freebets"){
					if (Assign_Freebet(Users, User_info_file) == 1)
					{
						cout << "Freebet assigned." << endl;
						cout << "Exiting system for security purposes." << endl;
						User_info_file.close();
						Read_User_info_file.close();
						write_hierarchy_file.close();
						write_hierarchy_file.close();
							
						return 0;
					}
				}
			}
			while(a>cur_location_size(location)){
				cout << "Please input a correct node id." << endl;
				cin >> a;
			}
			cout << cur_location_size(location) << endl;
			if (a <= cur_location_size(location) && is_cur_location_visible(location, a) && a!=0){
				location = Update_Location(location,a,Users[user_place-1].Get_Type());
				if(Users[user_place-1].Get_Type()==1){
					Log(logfile,Users[user_place-1],location,'-'," ");
				}
			}
			if(choice == "h" || choice == "home"){
				location = "Location:/Stoiximania/";
				cout << location << endl;
			}
			else if(choice == "t" || choice == "toggle"){
				cout << "Toggling..." << endl;
				toggle = Toggle_prices(toggle);
			}
			Print_Options(Users[user_place-1].Get_Type());
			Print_Available_Nodes(location,toggle,Users[user_place-1].Get_Type());
			cin >> choice;
			a = atoi(choice.c_str());
			transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
			cout << endl;
		}
	}
	else if (username.compare("guest") == 0 && password.compare("guest") == 0){
		cout << "You logged in as a guest\n";
		cout << location << endl;
		Print_Options(Users[user_place-1].Get_Type());
		Print_Available_Nodes(location,toggle,Users[user_place-1].Get_Type());
		cin >> choice;
		int a = atoi(choice.c_str());
		transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
		while(choice!="x" && choice!="exit"){
			if (a <= hierarchy_vector.size()){
				location = Update_Location(location,a,1);
			}
			else if(choice == "h" || choice == "home"){
				location = "Location:/Stoiximania/";
				cout << location << endl;
			}
			Print_Options(Users[user_place-1].Get_Type());
			Print_Available_Nodes(location,toggle,Users[user_place-1].Get_Type());
			cin >> choice;
			transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
			int a = atoi(choice.c_str());
			cout << endl;
		}
	}
	else
		cout << "Unrecognizable details!\n\n\n";	
}

int main(int argc, char *argv[]){															//Main used to enter the Login function, and to register new players (through New_User).
	int userid=0;
	string name,location="Location:/Stoiximania/";
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
       		Login_after_reg(location, User_info_file, Read_User_info_file, Users, hierarchy_file, write_hierarchy_file);
		}
		else
			cout << "Error" << endl;
	}
	else
		Login(location, User_info_file, Read_User_info_file, Users, hierarchy_file, write_hierarchy_file);
	User_info_file.close();
	Read_User_info_file.close();
	write_hierarchy_file.close();
	write_hierarchy_file.close();
}
