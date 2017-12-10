#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>

extern bool is_empty(ifstream& Usercsv);

int Rename(string location,string name,int id){
	string temp_location = location, cat_name, subcat_name, event_name,market_name;
	int i,j,k,l,m;
	while(!location.empty()){
		location = location.erase(0,location.find("/")+1);
		i++;
	}
	if(i==2){
		//cout << name << hierarchy_vector[id-1].get_name() << endl;
		hierarchy_vector[id-1].set_name(name);
	}
	else if(i==3){
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		temp_location = temp_location.substr(0,temp_location.find("/"));				//TODO: PUT IN LINE 226-227
		cout << temp_location << endl;
		for(j=0; j<hierarchy_vector.size(); j++){
			if(temp_location == hierarchy_vector[j].get_name()){
				//cout << hierarchy_vector[j].get_sub_vector()[id-1].get_name();
				hierarchy_vector[j].get_sub_vector()[id-1].set_name(name);
			}
		}
	}
	else if(i==4){
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		cat_name = temp_location.substr(0,temp_location.find("/"));
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		subcat_name = temp_location.substr(0,temp_location.find("/"));				//TODO: PUT IN LINE 226-227
		cout << temp_location << endl;
		for(j=0; j<hierarchy_vector.size(); j++){
			if(cat_name == hierarchy_vector[j].get_name()){
				for(int k=0;k<hierarchy_vector[j].get_sub_vector().size();k++){
					if(subcat_name == hierarchy_vector[j].get_sub_vector()[k].get_name())
						hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[id-1].set_name(name);
				}
				//hierarchy_vector[j].print_subcategories();
			}
		}
	}
	else if(i==5){
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		cat_name = temp_location.substr(0,temp_location.find("/"));
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		subcat_name = temp_location.substr(0,temp_location.find("/"));				//TODO: PUT IN LINE 226-227
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
		subcat_name = temp_location.substr(0,temp_location.find("/"));				//TODO: PUT IN LINE 226-227
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
	int i,j,k,l,m;
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
		temp_location = temp_location.substr(0,temp_location.find("/"));				//TODO: PUT IN LINE 226-227
		for(j=0; j<hierarchy_vector.size(); j++){
			if(temp_location == hierarchy_vector[j].get_name()){
				//cout << hierarchy_vector[j].get_sub_vector()[id-1].get_name();
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
		subcat_name = temp_location.substr(0,temp_location.find("/"));				//TODO: PUT IN LINE 226-227
		cout << temp_location << endl;
		for(j=0; j<hierarchy_vector.size(); j++){
			if(cat_name == hierarchy_vector[j].get_name()){
				for(int k=0;k<hierarchy_vector[j].get_sub_vector().size();k++){
					if(subcat_name == hierarchy_vector[j].get_sub_vector()[k].get_name())
						hierarchy_vector[j].get_sub_vector()[k].get_event_vector().push_back(E);
				}
				//hierarchy_vector[j].print_subcategories();
			}
		}
	}
	else if(i==5){
		Market M(name);
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		cat_name = temp_location.substr(0,temp_location.find("/"));
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		subcat_name = temp_location.substr(0,temp_location.find("/"));				//TODO: PUT IN LINE 226-227
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
		subcat_name = temp_location.substr(0,temp_location.find("/"));				//TODO: PUT IN LINE 226-227
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
	cout << "i" << i << endl;
	if(i==2){
		Category C=hierarchy_vector[id-1];
		string name = C.get_name() + " - Copied";
		C.set_name(name);
		hierarchy_vector.push_back(C);
	}
	else if(i==3){
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		temp_location = temp_location.substr(0,temp_location.find("/"));				//TODO: PUT IN LINE 226-227
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
		subcat_name = temp_location.substr(0,temp_location.find("/"));				//TODO: PUT IN LINE 226-227
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
				//hierarchy_vector[j].print_subcategories();
			}
		}
	}
	else if(i==5){
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		cat_name = temp_location.substr(0,temp_location.find("/"));
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		subcat_name = temp_location.substr(0,temp_location.find("/"));				//TODO: PUT IN LINE 226-227
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
		subcat_name = temp_location.substr(0,temp_location.find("/"));				//TODO: PUT IN LINE 226-227
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
		//delete temp;
	}
	else if(i==3){
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		temp_location = temp_location.substr(0,temp_location.find("/"));				//TODO: PUT IN LINE 226-227
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
		subcat_name = temp_location.substr(0,temp_location.find("/"));				//TODO: PUT IN LINE 226-227
		cout << temp_location << endl;
		for(j=0; j<hierarchy_vector.size(); j++){
			if(cat_name == hierarchy_vector[j].get_name()){
				for(int k=0;k<hierarchy_vector[j].get_sub_vector().size();k++){
					if(subcat_name == hierarchy_vector[j].get_sub_vector()[k].get_name())
						hierarchy_vector[j].get_sub_vector()[k].get_event_vector().erase(hierarchy_vector[j].get_sub_vector()[k].get_event_vector().begin() + id - 1);
				}
				//hierarchy_vector[j].print_subcategories();
			}
		}
	}
	else if(i==5){
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		cat_name = temp_location.substr(0,temp_location.find("/"));
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		subcat_name = temp_location.substr(0,temp_location.find("/"));				//TODO: PUT IN LINE 226-227
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
		subcat_name = temp_location.substr(0,temp_location.find("/"));				//TODO: PUT IN LINE 226-227
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

int Log(ofstream &logfile,User _user,string location,char action,string util){
	time_t rawtime;
  	struct tm * timeinfo;
  	char buffer[80];
  	time (&rawtime);
  	timeinfo = localtime(&rawtime);
  	strftime(buffer,80,"%d-%m-%Y %I:%M:%S",timeinfo);
	string str(buffer);
  	//cout << str;
  	
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
}

int Visibility(string location,int id){
	string temp_location = location, cat_name, subcat_name, event_name,market_name;
	int i,j,k,l,m;
	while(!location.empty()){
		location = location.erase(0,location.find("/")+1);
		i++;
	}
	if(i==2){
		//cout << name << hierarchy_vector[id-1].get_name() << endl;
		hierarchy_vector[id-1].toggle_visibility();
	}
	else if(i==3){
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		temp_location = temp_location.substr(0,temp_location.find("/"));				//TODO: PUT IN LINE 226-227
		cout << temp_location << endl;
		for(j=0; j<hierarchy_vector.size(); j++){
			if(temp_location == hierarchy_vector[j].get_name()){
				//cout << hierarchy_vector[j].get_sub_vector()[id-1].get_name();
				hierarchy_vector[j].get_sub_vector()[id-1].toggle_visibility();
			}
		}
	}
	else if(i==4){
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		cat_name = temp_location.substr(0,temp_location.find("/"));
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		subcat_name = temp_location.substr(0,temp_location.find("/"));				//TODO: PUT IN LINE 226-227
		cout << temp_location << endl;
		for(j=0; j<hierarchy_vector.size(); j++){
			if(cat_name == hierarchy_vector[j].get_name()){
				for(int k=0;k<hierarchy_vector[j].get_sub_vector().size();k++){
					if(subcat_name == hierarchy_vector[j].get_sub_vector()[k].get_name())
						hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[id-1].toggle_visibility();
				}
				//hierarchy_vector[j].print_subcategories();
			}
		}
	}
	else if(i==5){
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		cat_name = temp_location.substr(0,temp_location.find("/"));
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		subcat_name = temp_location.substr(0,temp_location.find("/"));				//TODO: PUT IN LINE 226-227
		temp_location = temp_location.erase(0,temp_location.find("/")+1);
		event_name = temp_location.substr(0,temp_location.find("/"));
	
		cout << temp_location << endl;
		for(j=0; j<hierarchy_vector.size(); j++){
			if(cat_name == hierarchy_vector[j].get_name()){
				for(int k=0;k<hierarchy_vector[j].get_sub_vector().size();k++){
					if(subcat_name == hierarchy_vector[j].get_sub_vector()[k].get_name()){
						for(l=0; l<hierarchy_vector[j].get_sub_vector()[k].get_event_vector().size(); l++){
							if(event_name == hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_name())
								hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_market_vector()[id-1].toggle_visibility();
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
		subcat_name = temp_location.substr(0,temp_location.find("/"));				//TODO: PUT IN LINE 226-227
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
										hierarchy_vector[j].get_sub_vector()[k].get_event_vector()[l].get_market_vector()[m].get_sel_vector()[id-1].toggle_visibility();
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

int Print_Log(ifstream &logfile){
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

int Print_Users(){	
	int lines = 0,i,j,k=0;
	vector<string> line;
	string templine,word;
	char vline=186,hline=205,rtcorner=187,rbcorner=188,ltcorner=201,lbcorner=200,hlinedown=203;			//EASCII CHARACTERS TO BE USED LATER.
	//cout << vline << hline << rtcorner << rbcorner << ltcorner << lbcorner << endl;
	ifstream userfile,userfileb;
	userfile.open("Users.csv",fstream::in);
	//userfileb.open("Users.csv",fstream::in);
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
