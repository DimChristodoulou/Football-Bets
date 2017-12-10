#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class Selection{
	
	private:
		string name, yield, yield_frac;
		bool visibility;
		float yield_dec;
		
	public:
		
		Selection(string nametoassign){
			name = nametoassign;
			visibility = 1;
		}
		
		int print(){
			int i;
			cout << "\t\t\t\t" << name << endl;
		}
		
		bool toggle_visibility(){
			if(this->visibility==1)
				this->visibility=0;
			else if(this->visibility==0)
				this->visibility=1;
		}
		
		bool is_visible(){
			return this->visibility;
		}
		
		string get_name(){
			return this->name;
		}
		
		void set_name()
		{
			name = name.substr(0,name.find("#"));
		}
		
		void set_name(string &name_to_give){
			this->name = name_to_give;
		}
		
		string get_yield_fractional()
		{
			return this->yield_frac;
		}
		
		void set_yield_fractional()
		{
			yield = name;
			yield_frac = yield.erase(0,yield.find("#") + 1);
		}
		
		float get_yield_decimal()
		{
			return this->yield_dec;
		}
		
		void set_yield_decimal()
		{
			string d1, d2;
			float d11, d22;
			yield = name;
			yield = yield.erase(0,yield.find("#") + 1);
			d1 = yield.substr(0,yield.find("/"));
			yield = yield.erase(0,yield.find("/") + 1);
			d2 = yield;
			
			d11 = atoi(d1.c_str());
			d22 = atoi(d2.c_str());
			
			yield_dec = (d11/d22) + 1;
		}
};

class Market{
	
	private:
		string name;
		bool visibility;
		vector<Selection> sel_vector;
	
	public:
		
		Market(string nametoassign){
			name = nametoassign;
			visibility = 1;
		}
		
		int print(){
			int i;
			cout << "\t\t\t" << name << endl;
			for(i=0;i<sel_vector.size();i++){
				//cout << "\t\t\t" << name << endl;
				sel_vector[i].print();
			}	
		}
		
		bool toggle_visibility(){
			if(this->visibility==1)
				this->visibility=0;
			else if(this->visibility==0)
				this->visibility=1;
		}
		
		bool is_visible(){
			return this->visibility;
		}
		
		vector<Selection> &get_sel_vector(){
			return this->sel_vector;	
		}
		
		void print_selections(int toggle){
//			for(int i=0; i<sel_vector.size();i++)
//			{
//				sel_vector[i].set_yield_fractional();
//				sel_vector[i].set_yield_decimal();
//				sel_vector[i].set_name();
//				
//				if (toggle == 0)
//				{
//					cout << i+1 << ". " << sel_vector[i].get_name() << "#";
//					cout << sel_vector[i].get_yield_fractional() << endl;
//				}
//				else if (toggle == 1)
//				{
//					cout << i+1 << ". " << sel_vector[i].get_name() << "#";
//					cout << sel_vector[i].get_yield_decimal() << endl;
//				}
//			}	
			int j=0;
			for(int i=0; i<sel_vector.size();i++){
				if(sel_vector[i].is_visible()){
					cout << j+1 << ". " << sel_vector[i].get_name() << endl;
					j++;
				}
			}
		}
		
		string get_name(){
			return this->name;
		}
		
		void set_name(string &name_to_give){
			this->name = name_to_give;
		}		
		
		int new_selection(Selection s){
			sel_vector.push_back(s);
		}
};

class Event{
	private:
		string name,date,announce_time;
		bool visibility;
		vector<Market> market_vector;
		
	public:
		
		Event(string nametoassign){
			name = nametoassign;
			visibility = 1;
		}
		
		int print(){
			int i;
			cout << "\t\t" << name << endl;
			for(i=0;i<market_vector.size();i++){
				//cout << "\t\t" << name << endl;
				market_vector[i].print();
			}
		}
		
		bool toggle_visibility(){
			if(this->visibility==1)
				this->visibility=0;
			else if(this->visibility==0)
				this->visibility=1;
		}
		
		bool is_visible(){
			return this->visibility;
		}
		
		void set_name(string &name_to_give){
			this->name = name_to_give;
		}
		
		void print_markets(){
			int j=0;
			for(int i=0; i<market_vector.size();i++){
				if(market_vector[i].is_visible()){
					cout << j+1 << ". " << market_vector[i].get_name() << endl;
					j++;
				}
			}
		}
		
		vector<Market> &get_market_vector(){
			return this->market_vector;	
		}
		
		int new_market(Market m){
			market_vector.push_back(m);
		}
		
		int new_selection(Selection s,int market_place){
			market_vector[market_place].new_selection(s);
		}
		
		string get_name(){
			return this->name;
		}
		
};

class Subcategory{
	private:
		vector<Event> event_vector;
		bool visibility;
		string name;
	
	public:
		
		Subcategory(string nametoassign){
			name = nametoassign;
			visibility = 1;
		}
		
		int print(){
			int i;
			cout << "\t" << name << endl;
			for(i=0;i<event_vector.size();i++){
				//cout << "\t" << name << endl;
				event_vector[i].print();
			}
		}
		
		bool toggle_visibility(){
			if(this->visibility==1)
				this->visibility=0;
			else if(this->visibility==0)
				this->visibility=1;
		}
		
		bool is_visible(){
			return this->visibility;
		}
		
		void set_name(string &name_to_give){
			this->name = name_to_give;
		}
		
		void print_events(){
			int j=0;
			for(int i=0; i<event_vector.size();i++){
				if(event_vector[i].is_visible()){
					cout << j+1 << ". " << event_vector[i].get_name() << endl;
					j++;
				}
			}
		}
		
		vector<Event> &get_event_vector(){
			return this->event_vector;
		}
		
		string get_name(){
			return this->name;
		}
		
		int new_event(Event e){
			event_vector.push_back(e);
		}
		
		int new_market(Market m, int ev_place){
			event_vector[ev_place].new_market(m);
		}
		
		int new_selection(Selection s, int ev_place, int market_place){
			event_vector[ev_place].new_selection(s,market_place);
		}
			
};

class Category{
	private:
		vector<Subcategory> sub_vector;
		bool visibility;
		string name;
		
	public:
		
		Category(string nametoassign){
			name = nametoassign;
			visibility = 1;
		}
		
		int print(){
			int i;
			cout << name << endl;
			for(i=0;i<sub_vector.size();i++){
				//cout << name << endl;
				sub_vector[i].print();
			}
		}
		
		void print_subcategories(){
			int j=0;
			for(int i=0; i<sub_vector.size();i++){
				if(sub_vector[i].is_visible()){
					cout << j+1 << ". " << sub_vector[i].get_name() << endl;
					j++;
				}
			}
		}
		
		bool toggle_visibility(){
			if(this->visibility==1)
				this->visibility=0;
			else if(this->visibility==0)
				this->visibility=1;
		}
		
		bool is_visible(){
			return this->visibility;
		}

		string get_name(){
			return this->name;
		}
		
		void set_name(string &name_to_give){
			this->name = name_to_give;
		}
		
		vector<Subcategory> &get_sub_vector(){
			return this->sub_vector;
		}
		
		int new_subcategory(Subcategory s){
			sub_vector.push_back(s);
		}
		
		int new_event(Event e, int subcat_place){
			sub_vector[subcat_place].new_event(e);
		}
		
		int new_market(Market m, int subcat_place, int ev_place){
			sub_vector[subcat_place].new_market(m,ev_place);
		}
		
		int new_selection(Selection s, int subcat_place, int ev_place, int market_place){
			sub_vector[subcat_place].new_selection(s,ev_place,market_place);
		}
				
};

vector<Category> hierarchy_vector;

int update_hierarchy(ifstream &Read_hierarchy){
	//ifstream Read_hierarchy;
	string line,cat,cat_nums,subcat_nums;
	//Read_hierarchy.open("Hierarchy.dat" , fstream::in);
	string a;
	while(!Read_hierarchy.eof()){
		getline(Read_hierarchy,line);
		cat = line.substr(0,line.find(" "));
		cat_nums = line.substr(0,1);
		int cat_num = atoi(cat_nums.c_str());
		subcat_nums = line.substr(2,1);
		int subcat_num = atoi(subcat_nums.c_str());
		int ev_num=atoi(line.substr(4,1).c_str());
		int market_num = atoi(line.substr(6,1).c_str());
		//cout << "EVNUM" << ev_num << endl;
		line = line.erase(0,line.find(" ")+1);
		//cout << cat << cat.size() <<endl;
		if(cat.size()==2){
			Category c(line);
			hierarchy_vector.push_back(c);
		}
		else if(cat.size()==3){										//WARNING: Does not handle X.X. format. Only handles X.X format. Hierarchy file has been changed accordingly.
			Subcategory s(line);
			hierarchy_vector[cat_num-1].new_subcategory(s);
		}
		else if(cat.size()==5){
			Event e(line);
			hierarchy_vector[cat_num-1].new_event(e,subcat_num-1);
		}
		else if(cat.size()==7){
			Market m(line);
			hierarchy_vector[cat_num-1].new_market(m,subcat_num-1,ev_num-1);
		}
		else if(cat.size()>=9){
			Selection s(line);
			hierarchy_vector[cat_num-1].new_selection(s,subcat_num-1,ev_num-1,market_num-1);
		}
	}
//	for(int i=0;i<hierarchy_vector.size();i++)
//		hierarchy_vector[i].print();
//	getline(Read_hierarchy,a);
//	cout << a << endl;
}

