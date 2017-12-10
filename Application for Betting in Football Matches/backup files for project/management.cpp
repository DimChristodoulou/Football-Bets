#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cmath>

extern bool is_empty(ifstream& Usercsv);

using namespace std;

int Rename(string location,string name,int id){												//All functions that run thought the entire hierarchy to find/print the appropriate selections/markets/etc use the same motif of finding where a user is currently (location) and then printing the options available to that location.
	string temp_location = location, cat_name, subcat_name, event_name,market_name;
	int i=0,j,k,l,m;
	while(!location.empty()){
		location = location.erase(0,location.find("/")+1);
		i++;
	}
	if(i==2){
		hierarchy_vector[id-1].set_name(name);
	}
	else if(i==3){
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		temp_location = temp_location.substr(0,temp_location.find("/"));
		cout << temp_location << endl;
		for(j=0; j<hierarchy_vector.size(); j++){
			if(temp_location == hierarchy_vector[j].get_name()){
				hierarchy_vector[j].get_sub_vector()[id-1].set_name(name);
			}
		}
	}
	else if(i==4){
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		cat_name = temp_location.substr(0,temp_location.find("/"));
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		subcat_name = temp_location.substr(0,temp_location.find("/"));
		cout << temp_location << endl;
		for(j=0; j<hierarchy_vector.size(); j++){
			if(cat_name == hierarchy_vector[j].get_name()){
				for(int k=0;k<hierarchy_vector[j].get_sub_vector().size();k++){
					if(subcat_name == hierarchy_vector[j].get_sub_vector()[k].get_name())
						hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[id-1].set_name(name);
				}
			}
		}
	}
	else if(i==5){
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		cat_name = temp_location.substr(0,temp_location.find("/"));
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		subcat_name = temp_location.substr(0,temp_location.find("/"));
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		event_name = temp_location.substr(0,temp_location.find("/"));
		cout << temp_location << endl;
		for(j=0; j<hierarchy_vector.size(); j++){
			if(cat_name == hierarchy_vector[j].get_name()){
				for(int k=0;k<hierarchy_vector[j].get_sub_vector().size();k++){
					if(subcat_name == hierarchy_vector[j].get_sub_vector()[k].get_name()){
						for(l=0; l<hierarchy_vector[j].get_sub_vector()[k].get_event_vector().size(); l++){
							if(event_name == hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_name())
								hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_market_vector()[id-1].set_name(name);
						}
					}
				}
			}
		}
	}
	else if(i==6){
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		cat_name = temp_location.substr(0,temp_location.find("/"));
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		subcat_name = temp_location.substr(0,temp_location.find("/"));
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		event_name = temp_location.substr(0,temp_location.find("/"));
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		market_name = temp_location.substr(0,temp_location.find("/"));
		cout << temp_location << endl;
		for(j=0; j<hierarchy_vector.size(); j++){
			if(cat_name == hierarchy_vector[j].get_name()){
				for(int k=0;k<hierarchy_vector[j].get_sub_vector().size();k++){
					if(subcat_name == hierarchy_vector[j].get_sub_vector()[k].get_name()){
						for(l=0; l<hierarchy_vector[j].get_sub_vector()[k].get_event_vector().size(); l++){
							if(event_name == hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_name()){
								for(m=0; m<hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_market_vector().size(); m++){
									if(market_name == hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_market_vector()[m].get_name()){
										hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_market_vector()[m].get_sel_vector()[id-1].set_name(name);
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

int New(string location,string name){
	int i=0,j,k,l,m;
	string temp_location = location, cat_name, subcat_name, event_name,market_name;
	while(!location.empty()){
		location = location.erase(0,location.find("/")+1);
		i++;
	}
	if(i==2){
		Category C(name);
		hierarchy_vector.push_back(C);
	}
	else if(i==3){
		Subcategory S(name);
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		temp_location = temp_location.substr(0,temp_location.find("/"));
		for(j=0; j<hierarchy_vector.size(); j++){
			if(temp_location == hierarchy_vector[j].get_name()){
				hierarchy_vector[j].get_sub_vector().push_back(S);
			}
		}
	}
	else if(i==4){
		Event E(name);
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		cat_name = temp_location.substr(0,temp_location.find("/"));
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		subcat_name = temp_location.substr(0,temp_location.find("/"));
		cout << temp_location << endl;
		for(j=0; j<hierarchy_vector.size(); j++){
			if(cat_name == hierarchy_vector[j].get_name()){
				for(int k=0;k<hierarchy_vector[j].get_sub_vector().size();k++){
					if(subcat_name == hierarchy_vector[j].get_sub_vector()[k].get_name())
						hierarchy_vector[j].get_sub_vector()[k].get_event_vector().push_back(E);
				}
			}
		}
	}
	else if(i==5){
		Market M(name);
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		cat_name = temp_location.substr(0,temp_location.find("/"));
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		subcat_name = temp_location.substr(0,temp_location.find("/"));
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		event_name = temp_location.substr(0,temp_location.find("/"));
	
		cout << temp_location << endl;
		for(j=0; j<hierarchy_vector.size(); j++){
			if(cat_name == hierarchy_vector[j].get_name()){
				for(int k=0;k<hierarchy_vector[j].get_sub_vector().size();k++){
					if(subcat_name == hierarchy_vector[j].get_sub_vector()[k].get_name()){
						for(l=0; l<hierarchy_vector[j].get_sub_vector()[k].get_event_vector().size(); l++){
							if(event_name == hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_name())
								hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_market_vector().push_back(M);
						}
					}
				}
			}
		}
	}
	else if(i==6){
		Selection S(name);
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		cat_name = temp_location.substr(0,temp_location.find("/"));
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		subcat_name = temp_location.substr(0,temp_location.find("/"));
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		event_name = temp_location.substr(0,temp_location.find("/"));
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		market_name = temp_location.substr(0,temp_location.find("/"));
		cout << temp_location << endl;
		for(j=0; j<hierarchy_vector.size(); j++){
			if(cat_name == hierarchy_vector[j].get_name()){
				for(int k=0;k<hierarchy_vector[j].get_sub_vector().size();k++){
					if(subcat_name == hierarchy_vector[j].get_sub_vector()[k].get_name()){
						for(l=0; l<hierarchy_vector[j].get_sub_vector()[k].get_event_vector().size(); l++){
							if(event_name == hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_name()){
								for(m=0; m<hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_market_vector().size(); m++){
									if(market_name == hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_market_vector()[m].get_name()){
										hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_market_vector()[m].get_sel_vector().push_back(S);
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

int Copy(string location,int id){
	string temp_location = location, cat_name, subcat_name, event_name,market_name;
	int i=0,j,k,l,m;
	cout << location << endl;
	while(!location.empty()){
		location = location.erase(0,location.find("/")+1);
		i++;
		cout << location << endl;
	}
	if(i==2){
		Category C=hierarchy_vector[id-1];
		string name = C.get_name();
		name.append(" - Copied");
		C.set_name(name);
		hierarchy_vector.push_back(C);
	}
	else if(i==3){
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		temp_location = temp_location.substr(0,temp_location.find("/"));
		cout << temp_location << endl;
		for(j=0; j<hierarchy_vector.size(); j++){
			if(temp_location == hierarchy_vector[j].get_name()){
				Subcategory S = hierarchy_vector[j].get_sub_vector()[id-1];
				string name = S.get_name() + " - Copied";
				S.set_name(name);
				hierarchy_vector[j].get_sub_vector().push_back(S);
			}
		}
	}
	else if(i==4){
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		cat_name = temp_location.substr(0,temp_location.find("/"));
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		subcat_name = temp_location.substr(0,temp_location.find("/"));
		cout << temp_location << endl;
		for(j=0; j<hierarchy_vector.size(); j++){
			if(cat_name == hierarchy_vector[j].get_name()){
				for(int k=0;k<hierarchy_vector[j].get_sub_vector().size();k++){
					if(subcat_name == hierarchy_vector[j].get_sub_vector()[k].get_name()){
						Event E = hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[id-1];
						string name = E.get_name() + " - Copied";
						E.set_name(name);
						hierarchy_vector[j].get_sub_vector()[k].get_event_vector().push_back(E);
					}
				}
			}
		}
	}
	else if(i==5){
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		cat_name = temp_location.substr(0,temp_location.find("/"));
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		subcat_name = temp_location.substr(0,temp_location.find("/"));
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		event_name = temp_location.substr(0,temp_location.find("/"));
	
		cout << temp_location << endl;
		for(j=0; j<hierarchy_vector.size(); j++){
			if(cat_name == hierarchy_vector[j].get_name()){
				for(int k=0;k<hierarchy_vector[j].get_sub_vector().size();k++){
					if(subcat_name == hierarchy_vector[j].get_sub_vector()[k].get_name()){
						for(l=0; l<hierarchy_vector[j].get_sub_vector()[k].get_event_vector().size(); l++){
							if(event_name == hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_name()){
								Market M = hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_market_vector()[id-1];
								string name = M.get_name() + " - Copied";
								M.set_name(name);
								hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_market_vector().push_back(M);
							}
						}
					}
				}
			}
		}
	}
	else if(i==6){
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		cat_name = temp_location.substr(0,temp_location.find("/"));
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		subcat_name = temp_location.substr(0,temp_location.find("/"));
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		event_name = temp_location.substr(0,temp_location.find("/"));
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		market_name = temp_location.substr(0,temp_location.find("/"));
		cout << temp_location << endl;
		for(j=0; j<hierarchy_vector.size(); j++){
			if(cat_name == hierarchy_vector[j].get_name()){
				for(int k=0;k<hierarchy_vector[j].get_sub_vector().size();k++){
					if(subcat_name == hierarchy_vector[j].get_sub_vector()[k].get_name()){
						for(l=0; l<hierarchy_vector[j].get_sub_vector()[k].get_event_vector().size(); l++){
							if(event_name == hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_name()){
								for(m=0; m<hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_market_vector().size(); m++){
									if(market_name == hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_market_vector()[m].get_name()){
										Selection S = hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_market_vector()[m].get_sel_vector()[id-1];
										string name = S.get_name() + " - Copied";
										S.set_name(name);
										hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_market_vector()[m].get_sel_vector().push_back(S);
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

int Delete(string location,int id){
	string temp_location = location, cat_name, subcat_name, event_name,market_name;
	int i=0,j,k,l,m;
	while(!location.empty()){
		location = location.erase(0,location.find("/")+1);
		i++;
	}
	if(i==2){
		Category *temp = &hierarchy_vector[id-1];
		hierarchy_vector.erase(hierarchy_vector.begin() + id - 1);
	}
	else if(i==3){
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		temp_location = temp_location.substr(0,temp_location.find("/"));
		cout << temp_location << endl;
		for(j=0; j<hierarchy_vector.size(); j++){
			if(temp_location == hierarchy_vector[j].get_name()){
				hierarchy_vector[j].get_sub_vector().erase(hierarchy_vector[j].get_sub_vector().begin() + id - 1);
			}
		}
	}
	else if(i==4){
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		cat_name = temp_location.substr(0,temp_location.find("/"));
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		subcat_name = temp_location.substr(0,temp_location.find("/"));
		cout << temp_location << endl;
		for(j=0; j<hierarchy_vector.size(); j++){
			if(cat_name == hierarchy_vector[j].get_name()){
				for(int k=0;k<hierarchy_vector[j].get_sub_vector().size();k++){
					if(subcat_name == hierarchy_vector[j].get_sub_vector()[k].get_name())
						hierarchy_vector[j].get_sub_vector()[k].get_event_vector().erase(hierarchy_vector[j].get_sub_vector()[k].get_event_vector().begin() + id - 1);
				}
			}
		}
	}
	else if(i==5){
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		cat_name = temp_location.substr(0,temp_location.find("/"));
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		subcat_name = temp_location.substr(0,temp_location.find("/"));
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		event_name = temp_location.substr(0,temp_location.find("/"));
	
		cout << temp_location << endl;
		for(j=0; j<hierarchy_vector.size(); j++){
			if(cat_name == hierarchy_vector[j].get_name()){
				for(int k=0;k<hierarchy_vector[j].get_sub_vector().size();k++){
					if(subcat_name == hierarchy_vector[j].get_sub_vector()[k].get_name()){
						for(l=0; l<hierarchy_vector[j].get_sub_vector()[k].get_event_vector().size(); l++){
							if(event_name == hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_name())
								hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_market_vector().erase(hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_market_vector().begin() + id - 1);
						}
					}
				}
			}
		}
	}
	else if(i==6){
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		cat_name = temp_location.substr(0,temp_location.find("/"));
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		subcat_name = temp_location.substr(0,temp_location.find("/"));
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		event_name = temp_location.substr(0,temp_location.find("/"));
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		market_name = temp_location.substr(0,temp_location.find("/"));
		cout << temp_location << endl;
		for(j=0; j<hierarchy_vector.size(); j++){
			if(cat_name == hierarchy_vector[j].get_name()){
				for(int k=0;k<hierarchy_vector[j].get_sub_vector().size();k++){
					if(subcat_name == hierarchy_vector[j].get_sub_vector()[k].get_name()){
						for(l=0; l<hierarchy_vector[j].get_sub_vector()[k].get_event_vector().size(); l++){
							if(event_name == hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_name()){
								for(m=0; m<hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_market_vector().size(); m++){
									if(market_name == hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_market_vector()[m].get_name()){
										hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_market_vector()[m].get_sel_vector().erase(hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_market_vector()[m].get_sel_vector().begin() + id - 1);
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

int Log(ofstream &logfile,User _user,string location,char action,string util){														//Log for the audit file.
	time_t rawtime;
  	struct tm * timeinfo;
  	char buffer[80];
  	time (&rawtime);
  	timeinfo = localtime(&rawtime);
  	strftime(buffer,80,"%d-%m-%Y %I:%M:%S",timeinfo);
	string str(buffer);
  	
  	if(action=='-'){
		logfile << "N " << str << " : User " << _user.Get_Username() << " navigated to " << location << endl;
	}
	else if(action == 'R'){
		logfile << "A " << str << " : Admin " << _user.Get_Username() << " renamed a node in " << location << " to " << util << endl;
	}
	else if(action == 'N'){
		logfile << "A " << str << " : Admin " << _user.Get_Username() << " created a new node in " << location << " by the name of " << util << endl;
	}
	else if(action == 'C'){
		logfile << "A " << str << " : Admin " << _user.Get_Username() << " copied a node in " << location << endl;
	}
	else if(action == 'D'){
		logfile << "A " << str << " : Admin " << _user.Get_Username() << " deleted a node in " << location << endl;
	}
	else if(action == 'V'){
		logfile << "A " << str << " : Admin " << _user.Get_Username() << " changed the visibility of a node in " << location << endl;
	}
	else if(action == 'W'){
		logfile << "A " << str << " : Trader " << _user.Get_Username() << " set " << location << "as winning" << endl;
	}
}

int Visibility(string location,int id){
	string temp_location = location, cat_name, subcat_name, event_name,market_name;
	int i,j,k,l,m;
	while(!location.empty()){
		location = location.erase(0,location.find("/")+1);
		i++;
	}
	if(i==2){
		if(hierarchy_vector[id-1].is_visible()){
			string newname = hierarchy_vector[id-1].get_name() + "$hidden";
			hierarchy_vector[id-1].set_name(newname);
		}
		else{
			string newname = hierarchy_vector[id-1].get_name().erase(hierarchy_vector[id-1].get_name().find("$"),hierarchy_vector[id-1].get_name().find('\n'));
			hierarchy_vector[id-1].set_name(newname);
		}
	}
	else if(i==3){
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		temp_location = temp_location.substr(0,temp_location.find("/"));
		cout << temp_location << endl;
		for(j=0; j<hierarchy_vector.size(); j++){
			if(temp_location == hierarchy_vector[j].get_name()){
				if(hierarchy_vector[j].get_sub_vector()[id-1].is_visible()){
					string newname = hierarchy_vector[j].get_sub_vector()[id-1].get_name() + "$hidden";
					hierarchy_vector[j].get_sub_vector()[id-1].set_name(newname);
				}
				else{
					string newname = hierarchy_vector[j].get_sub_vector()[id-1].get_name().erase(hierarchy_vector[j].get_sub_vector()[id-1].get_name().find("$"),hierarchy_vector[j].get_sub_vector()[id-1].get_name().find('\n'));
					hierarchy_vector[j].get_sub_vector()[id-1].set_name(newname);
				}
			}
		}
	}
	else if(i==4){
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		cat_name = temp_location.substr(0,temp_location.find("/"));
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		subcat_name = temp_location.substr(0,temp_location.find("/"));			
		cout << temp_location << endl;
		for(j=0; j<hierarchy_vector.size(); j++){
			if(cat_name == hierarchy_vector[j].get_name()){
				for(int k=0;k<hierarchy_vector[j].get_sub_vector().size();k++){
					if(subcat_name == hierarchy_vector[j].get_sub_vector()[k].get_name()){
						if(hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[id-1].is_visible()){
							string newname = hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[id-1].get_name() + "$hidden";
							hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[id-1].set_name(newname);
						}
						else{
							string newname = hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[id-1].get_name().erase(hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[id-1].get_name().find("$"),hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[id-1].get_name().find('\n'));
							hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[id-1].set_name(newname);
						}
					}
				}
			}
		}
	}
	else if(i==5){
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		cat_name = temp_location.substr(0,temp_location.find("/"));
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		subcat_name = temp_location.substr(0,temp_location.find("/"));			
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		event_name = temp_location.substr(0,temp_location.find("/"));
	
		cout << temp_location << endl;
		for(j=0; j<hierarchy_vector.size(); j++){
			if(cat_name == hierarchy_vector[j].get_name()){
				for(int k=0;k<hierarchy_vector[j].get_sub_vector().size();k++){
					if(subcat_name == hierarchy_vector[j].get_sub_vector()[k].get_name()){
						for(l=0; l<hierarchy_vector[j].get_sub_vector()[k].get_event_vector().size(); l++){
							if(event_name == hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_name()){
								if(hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_market_vector()[id-1].is_visible()){
									string newname = hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_market_vector()[id-1].get_name() + "$hidden";
									hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_market_vector()[id-1].set_name(newname);
								}
								else{
									string newname = hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_market_vector()[id-1].get_name().erase(hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_market_vector()[id-1].get_name().find("$"),hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_market_vector()[id-1].get_name().find('\n'));
									hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_market_vector()[id-1].set_name(newname);
								}
							}
						}
					}
				}
			}
		}
	}
	else if(i==6){
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		cat_name = temp_location.substr(0,temp_location.find("/"));
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		subcat_name = temp_location.substr(0,temp_location.find("/"));	
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		event_name = temp_location.substr(0,temp_location.find("/"));
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		market_name = temp_location.substr(0,temp_location.find("/"));
		cout << temp_location << endl;
		for(j=0; j<hierarchy_vector.size(); j++){
			if(cat_name == hierarchy_vector[j].get_name()){
				for(int k=0;k<hierarchy_vector[j].get_sub_vector().size();k++){
					if(subcat_name == hierarchy_vector[j].get_sub_vector()[k].get_name()){
						for(l=0; l<hierarchy_vector[j].get_sub_vector()[k].get_event_vector().size(); l++){
							if(event_name == hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_name()){
								for(m=0; m<hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_market_vector().size(); m++){
									if(market_name == hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_market_vector()[m].get_name()){
										if(hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_market_vector()[m].get_sel_vector()[id-1].is_visible()){
											string newname = hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_market_vector()[m].get_sel_vector()[id-1].get_name() + "$hidden";
											hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_market_vector()[m].get_sel_vector()[id-1].set_name(newname);
										}
										else{
											string newname = hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_market_vector()[m].get_sel_vector()[id-1].get_name().erase(hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_market_vector()[m].get_sel_vector()[id-1].get_name().find("$"),hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_market_vector()[m].get_sel_vector()[id-1].get_name().find('\n'));
											hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_market_vector()[m].get_sel_vector()[id-1].set_name(newname);
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
}

int cur_location_size(string location){
	string temp_location = location, cat_name, subcat_name, event_name,market_name;
	int i=0,j,k,l,m;
	while(!location.empty()){
		location = location.erase(0,location.find("/")+1);
		i++;
	}
	if(i==2)
		return hierarchy_vector.size();
	else if(i==3){
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		temp_location = temp_location.substr(0,temp_location.find("/"));
		for(j=0; j<hierarchy_vector.size(); j++){
			if(temp_location == hierarchy_vector[j].get_name())
				return hierarchy_vector[j].get_sub_vector().size();
		}
	}
	else if(i==4){
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		cat_name = temp_location.substr(0,temp_location.find("/"));
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		subcat_name = temp_location.substr(0,temp_location.find("/"));
		for(j=0; j<hierarchy_vector.size(); j++){
			if(cat_name == hierarchy_vector[j].get_name()){
				for(int k=0;k<hierarchy_vector[j].get_sub_vector().size();k++){
					if(subcat_name == hierarchy_vector[j].get_sub_vector()[k].get_name())
						return hierarchy_vector[j].get_sub_vector()[k].get_event_vector().size();
				}
			}
		}
	}
	else if(i==5){
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		cat_name = temp_location.substr(0,temp_location.find("/"));
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		subcat_name = temp_location.substr(0,temp_location.find("/"));
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		event_name = temp_location.substr(0,temp_location.find("/"));	
		for(j=0; j<hierarchy_vector.size(); j++){
			if(cat_name == hierarchy_vector[j].get_name()){
				for(int k=0;k<hierarchy_vector[j].get_sub_vector().size();k++){
					if(subcat_name == hierarchy_vector[j].get_sub_vector()[k].get_name()){
						for(l=0; l<hierarchy_vector[j].get_sub_vector()[k].get_event_vector().size(); l++){
							if(event_name == hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_name())
								return hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_market_vector().size();
						}
					}
				}
			}
		}
	}
	else if(i==6){
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		cat_name = temp_location.substr(0,temp_location.find("/"));
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		subcat_name = temp_location.substr(0,temp_location.find("/"));
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		event_name = temp_location.substr(0,temp_location.find("/"));
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		market_name = temp_location.substr(0,temp_location.find("/"));
		for(j=0; j<hierarchy_vector.size(); j++){
			if(cat_name == hierarchy_vector[j].get_name()){
				for(int k=0;k<hierarchy_vector[j].get_sub_vector().size();k++){
					if(subcat_name == hierarchy_vector[j].get_sub_vector()[k].get_name()){
						for(l=0; l<hierarchy_vector[j].get_sub_vector()[k].get_event_vector().size(); l++){
							if(event_name == hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_name()){
								for(m=0; m<hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_market_vector().size(); m++){
									if(market_name == hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_market_vector()[m].get_name())
										return (hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_market_vector()[m].get_sel_vector().size());
								}
							}
						}
					}
				}
			}
		}
	}
	
}

string cur_location_name(string location,int id){
	string temp_location = location, cat_name, subcat_name, event_name,market_name;
	int i=0,j,k,l,m;
	while(!location.empty()){
		location = location.erase(0,location.find("/")+1);
		i++;
	}
	if(i==2)
		return hierarchy_vector[id-1].get_name();
	else if(i==3){
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		temp_location = temp_location.substr(0,temp_location.find("/"));
		for(j=0; j<hierarchy_vector.size(); j++){
			if(temp_location == hierarchy_vector[j].get_name()){
				return hierarchy_vector[j].get_sub_vector()[id-1].get_name();
			}
		}
	}
	else if(i==4){
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		cat_name = temp_location.substr(0,temp_location.find("/"));
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		subcat_name = temp_location.substr(0,temp_location.find("/"));
		for(j=0; j<hierarchy_vector.size(); j++){
			if(cat_name == hierarchy_vector[j].get_name()){
				for(int k=0;k<hierarchy_vector[j].get_sub_vector().size();k++){
					if(subcat_name == hierarchy_vector[j].get_sub_vector()[k].get_name())
						return hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[id-1].get_name();
				}
			}
		}
	}
	else if(i==5){
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		cat_name = temp_location.substr(0,temp_location.find("/"));
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		subcat_name = temp_location.substr(0,temp_location.find("/"));
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		event_name = temp_location.substr(0,temp_location.find("/"));
		for(j=0; j<hierarchy_vector.size(); j++){
			if(cat_name == hierarchy_vector[j].get_name()){
				for(int k=0;k<hierarchy_vector[j].get_sub_vector().size();k++){
					if(subcat_name == hierarchy_vector[j].get_sub_vector()[k].get_name()){
						for(l=0; l<hierarchy_vector[j].get_sub_vector()[k].get_event_vector().size(); l++){
							if(event_name == hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_name())
								return hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_market_vector()[id-1].get_name();
						}
					}
				}
			}
		}
	}
	else if(i==6){
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		cat_name = temp_location.substr(0,temp_location.find("/"));
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		subcat_name = temp_location.substr(0,temp_location.find("/"));
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		event_name = temp_location.substr(0,temp_location.find("/"));
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		market_name = temp_location.substr(0,temp_location.find("/"));
		for(j=0; j<hierarchy_vector.size(); j++){
			if(cat_name == hierarchy_vector[j].get_name()){
				for(int k=0;k<hierarchy_vector[j].get_sub_vector().size();k++){
					if(subcat_name == hierarchy_vector[j].get_sub_vector()[k].get_name()){
						for(l=0; l<hierarchy_vector[j].get_sub_vector()[k].get_event_vector().size(); l++){
							if(event_name == hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_name()){
								for(m=0; m<hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_market_vector().size(); m++){
									if(market_name == hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_market_vector()[m].get_name()){
										return (hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_market_vector()[m].get_sel_vector()[id-1].get_name());
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

bool is_cur_location_visible(string location, int id){
	string temp_location = location, cat_name, subcat_name, event_name,market_name;
	int i=0,j,k,l,m;
	while(!location.empty()){
		location = location.erase(0,location.find("/")+1);
		i++;
	}
	if(i==2)
		return hierarchy_vector[id-1].is_visible();
	else if(i==3){
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		temp_location = temp_location.substr(0,temp_location.find("/"));
		for(j=0; j<hierarchy_vector.size(); j++){
			if(temp_location == hierarchy_vector[j].get_name()){
				return hierarchy_vector[j].get_sub_vector()[id-1].is_visible();
			}
		}
	}
	else if(i==4){
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		cat_name = temp_location.substr(0,temp_location.find("/"));
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		subcat_name = temp_location.substr(0,temp_location.find("/"));
		for(j=0; j<hierarchy_vector.size(); j++){
			if(cat_name == hierarchy_vector[j].get_name()){
				for(int k=0;k<hierarchy_vector[j].get_sub_vector().size();k++){
					if(subcat_name == hierarchy_vector[j].get_sub_vector()[k].get_name())
						return hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[id-1].is_visible();
				}
			}
		}
	}
	else if(i==5){
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		cat_name = temp_location.substr(0,temp_location.find("/"));
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		subcat_name = temp_location.substr(0,temp_location.find("/"));
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		event_name = temp_location.substr(0,temp_location.find("/"));
		for(j=0; j<hierarchy_vector.size(); j++){
			if(cat_name == hierarchy_vector[j].get_name()){
				for(int k=0;k<hierarchy_vector[j].get_sub_vector().size();k++){
					if(subcat_name == hierarchy_vector[j].get_sub_vector()[k].get_name()){
						for(l=0; l<hierarchy_vector[j].get_sub_vector()[k].get_event_vector().size(); l++){
							if(event_name == hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_name())
								return hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_market_vector()[id-1].is_visible();
						}
					}
				}
			}
		}
	}
	else if(i==6){
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		cat_name = temp_location.substr(0,temp_location.find("/"));
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		subcat_name = temp_location.substr(0,temp_location.find("/"));
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		event_name = temp_location.substr(0,temp_location.find("/"));
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		market_name = temp_location.substr(0,temp_location.find("/"));
		for(j=0; j<hierarchy_vector.size(); j++){
			if(cat_name == hierarchy_vector[j].get_name()){
				for(int k=0;k<hierarchy_vector[j].get_sub_vector().size();k++){
					if(subcat_name == hierarchy_vector[j].get_sub_vector()[k].get_name()){
						for(l=0; l<hierarchy_vector[j].get_sub_vector()[k].get_event_vector().size(); l++){
							if(event_name == hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_name()){
								for(m=0; m<hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_market_vector().size(); m++){
									if(market_name == hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_market_vector()[m].get_name()){
										return (hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_market_vector()[m].get_sel_vector()[id-1].is_visible());
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

int Print_Log(ifstream &logfile){							//Prints the log.
	int i=0;
	string action;
	if(is_empty(logfile)){
		cout << "Log file is empty!" << endl;
		return 0;
	}
	while(i<25 && getline(logfile,action)){
		if(action.at(0)=='A'){
			i++;
			cout << action << endl;
		}
	}
}

int Print_Users(){												//Prints users.
	int lines = 0,i,j,k=0;
	vector<string> line;
	string templine,word;
	ifstream userfile,userfileb;
	userfile.open("Users.csv",fstream::in);
	while(!userfile.eof()){
		lines++;
		getline(userfile,templine);
		line.push_back(templine);
	}
	for(i=0;i<2*lines+1;i++){
                if(i%2==0){
                        for(j=0;j<122;j++){
                                int mod = j%122;
                                if(mod == 0 || mod == 11 || mod == 32 || mod == 53 || mod == 74 || mod == 79 || mod == 100 || mod == 111 || mod == 121)
                                        cout << "+";
                                else
                                        cout << "-";
                        }
                }
                else{
                        j = 0;
                        while(j<122){
                                int mod = j%122;
                                if(mod == 0 || mod == 11 || mod == 32 || mod == 53 || mod == 74 || mod == 79 || mod == 100 || mod == 111 || mod == 121){
                                        cout << "|";
                                        word = line[k].substr(0,line[k].find("|"));
                                        line[k].erase(0,line[k].find("|")+1);
                                        j+=word.length();
                                        cout << word;
                                }
                                else
                                        cout << " ";
                                j++;
                        }
                        k++;
                }
                cout << endl;
	}
}

int Save(){																						//Saves the current state.
	ofstream savefile;
	int i,j,k,l,m;
	savefile.open("Hierarchy.dat");
	for(i=0; i<hierarchy_vector.size(); i++){
		savefile << i+1 << ". " << hierarchy_vector[i].get_name() << endl;
		for(int j=0;j<hierarchy_vector[i].get_sub_vector().size();j++){
			savefile << i+1 << "." << j+1 << " " << hierarchy_vector[i].get_sub_vector()[j].get_name() << endl;
			for(k=0; k<hierarchy_vector[i].get_sub_vector()[j].get_event_vector().size(); k++){
				savefile << i+1 << "." << j+1 << "." << k+1 << " " << hierarchy_vector[i].get_sub_vector()[j].get_event_vector()[k].get_name() << endl;
				for(l=0; l<hierarchy_vector[i].get_sub_vector()[j].get_event_vector()[k].get_market_vector().size(); l++){
					savefile << i+1 << "." << j+1 << "." << k+1 << "." << l+1 << " " << hierarchy_vector[i].get_sub_vector()[j].get_event_vector()[k].get_market_vector()[l].get_name() << endl;
					for(m=0; m<hierarchy_vector[i].get_sub_vector()[j].get_event_vector()[k].get_market_vector()[l].get_sel_vector().size();m++){
						savefile << i+1 << "." << j+1 << "." << k+1 << "." << l+1 << "." << m+1 << " " << hierarchy_vector[i].get_sub_vector()[j].get_event_vector()[k].get_market_vector()[l].get_sel_vector()[m].get_name() << endl;
					}
				}
			}
		}
	}
	savefile.close();
}

int Search(storage_type &Users){																	//Search user.
	int i;
	string name;
	cout << "Enter part of the username to search for it: " << endl;
	cin >> name;
	for(i=0; i<Users.size(); i++){
		if(Users[i].Get_Username().find(name)!=string::npos)
			Users[i].extendedPrint();
	}
}

int Lock_User(storage_type &Users){																	//Lock user.
	string user_name,comment;
	ofstream Userfile;
	int i;
	cout << "Please enter username of the account you wish to lock." << endl;
	cin >> user_name;
	cout << Users.size();
	for(i=0; i<Users.size();i++){
		cout << Users[i].Get_Username() << " " << Users[i].Get_Status() << " " << Users[i].Get_Type() << endl;
		if(user_name == Users[i].Get_Username() && Users[i].Get_Status().at(0)=='A' && Users[i].Get_Type()!=3){
			cout << "Please enter lock comment." << endl;
			cin >> comment;
			comment = "L," + comment;
			Users[i].Set_Status(comment);
			Write_to_users(Users,Userfile);
			return 1;
		}
		else if(user_name == Users[i].Get_Username() && Users[i].Get_Status().at(0)=='L' && Users[i].Get_Type()!=3){
			cout << "User is already locked. Enter a new lock comment, or space to unlock user." << endl;
			getchar();
			getline(cin,comment);
			if(comment==" "){
				comment = "A";
				Users[i].Set_Status(comment);
				Write_to_users(Users,Userfile);
				return 1;
			}
			else{
				comment = "L," + comment;
				Users[i].Set_Status(comment);
				Write_to_users(Users,Userfile);
				return 1;
			}
		}
	}
	cout << "Username could not be found or account cannot be locked." << endl;
}

bool Selection_void(storage_type Users, ifstream& bets_history, string location, int user_place, ofstream &logfile, ofstream& User_info_file)		//Voiding a selection.
{
	bets_history.close();
	bets_history.open ("Bets.csv" , fstream::out);

	int id = 0, i = 0;
	string temp;
	int j = 0;
	string action, username, bet, selection, name_check;
	int bet_int = 0;
	
	temp = location;
	
	while(!temp.empty()){
		temp = temp.erase(0,temp.find("/")+1);
		i++;
	}
	
	if (i == 6)
	{
		cout << "Choose selection id to void: ";
		cin >> id;
		
		if (id <= cur_location_size(location))
		{
			while(getline(bets_history, action, '\n'))
			{
				//Uses the bet history to find which players have placed bets on the voided selection.
				username = bet = selection = action;
				username = username.substr(0,username.find("#"));
				
				bet = bet.erase(0,bet.find("#")+1);
				bet = bet.erase(0,bet.find("#")+1);
				bet = bet.substr(0, bet.find("$"));

				selection = selection.erase(0,selection.find("#")+1);
				selection = selection.erase(0,selection.find("#")+1);
				selection = selection.erase(0,selection.find("#")+1);
				selection = selection.substr(0, selection.find("#"));

				cout << endl;
				for (j = 0; j < Users.size(); j++)
				{
					name_check = cur_location_name(location,id).substr(0, cur_location_name(location,id).find("#"));
					if (name_check == selection)
					{
						if (Users[j].Get_Username().compare(username) == 0) 
						{
							bet_int = atoi(bet.c_str());
							int bal = Users[j].Get_Balance() + bet_int;
							Users[j].Change_Balance(bal);
							Write_to_users(Users, User_info_file);
							
							Delete(location,id);
							Log(logfile,Users[user_place-1],location,'V', " ");
							Save();
							
							return 1;
						}
					}
				}
			}
			Delete(location,id);
			Log(logfile,Users[user_place-1],location,'V', " ");
			Save();
		}
	}
	
	return 0;
}

bool Selection_settle(storage_type Users, ifstream& bets_history, string location, int user_place, ofstream &logfile, ofstream& User_info_file)		//Settles a selection.
{
	bets_history.close();
	bets_history.open ("Bets.csv" , fstream::out);

	int id = 0, i = 0;
	string temp;
	int j = 0;
	string action, username, bet, selection, fd, sd, name_check;
	int bet_int = 0;
	float fd_float = 0.0, sd_float = 0.0, win = 0.0;
	
	temp = location;
	
	while(!temp.empty()){
		temp = temp.erase(0,temp.find("/")+1);
		i++;
	}
	
	if (i == 6)
	{
		cout << "Choose selection id to settle: ";
		cin >> id;
		
		if (id <= cur_location_size(location))
		{
			while(getline(bets_history, action, '\n'))
			{
				//Like voiding, uses the bet history to find which players have placed bets on the settled selection.
				username = bet = selection = fd = sd = action;
				username = action.substr(0,action.find("#"));
				
				bet = bet.erase(0,bet.find("#")+1);
				bet = bet.erase(0,bet.find("#")+1);
				bet = bet.substr(0, bet.find("$"));
				
				selection = selection.erase(0,selection.find("#")+1);
				selection = selection.erase(0,selection.find("#")+1);
				selection = selection.erase(0,selection.find("#")+1);
				selection = selection.substr(0, selection.find("#"));
				
				fd = fd.erase(0,fd.find("#")+1);
				fd = fd.erase(0,fd.find("#")+1);
				fd = fd.erase(0,fd.find("#")+1);
				fd = fd.erase(0,fd.find("#")+1);
				fd = fd.substr(0, fd.find("/"));
				
				sd = sd.erase(0,sd.find("#")+1);
				sd = sd.erase(0,sd.find("#")+1);
				sd = sd.erase(0,sd.find("#")+1);
				sd = sd.erase(0,sd.find("#")+1);
				sd = sd.erase(0,sd.find("/")+1);
				sd = sd.substr(0, sd.find(","));
				
				fd_float = atoi(fd.c_str());
				sd_float = atoi(sd.c_str());
				
				win = (fd_float/sd_float) + 1;
				
				cout << endl; 

				for (j = 0; j < Users.size(); j++)
				{
					name_check = cur_location_name(location,id).substr(0, cur_location_name(location,id).find("#"));
					if (name_check == selection)
					{
						if (Users[j].Get_Username().compare(username) == 0)
						{
							bet_int = atoi(bet.c_str());
							int bal = Users[j].Get_Balance() + (bet_int*((int)win + 1));
							Users[j].Change_Balance(bal);
							Write_to_users(Users, User_info_file);
							
							Log(logfile,Users[user_place-1],location,'W', " ");
							Save();
							
							return 1;
						}
					}
				}
			}
			Log(logfile,Users[user_place-1],location,'W', " ");
			Save();
		}
	}
	
	return 0;
}
