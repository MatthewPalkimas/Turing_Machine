#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;


struct table
{
	string current_state, next_state;
	char input, output, direction;
	int transition_num, hmns;
	table(string cs, char i, string ns, char o, char d, int t, int h)
	{
		current_state = cs;
		input = i;
		next_state = ns;
		output = o;
		direction = d;
		transition_num = t;
		hmns = h;
	}
	table(string cs, string i, string ns, string o, string d, int t, int h)
	{
		current_state = cs;
		if(i[1] == '0')
			input = '\0';
		else if(i[1] == '?')
			input = 'Â'; //alt + 168
		else
			input = i[0];
		next_state = ns;
		if(o[1] == '0')
			output = '\0';
		else if(o[1] == '?')
			output = 'Â'; //alt + 168
		else
			output = o[0];
		direction = d[0];
		transition_num = t;
		hmns = h;
	}
	void print() 
	{
		cout << "transistion " << transition_num << ": " << current_state << ", ";
		if(input == '\0')
			cout << "'\\0' -> ";
		else if(input == 'Â') //alt + 168
			cout << "'?' -> "; //deleted the two backslashes to make it look nice
		else if(input == '?') 
			cout << "any -> ";
		else
			cout << "'" << input << "' -> "; 
		cout  << next_state << ", ";
		if(output == '\0')
			cout << "'\\0', ";
		else if(output == 'Â') //alt + 168
			cout << "'?', "; //deleted the two backslashes to make it look nice
		else if(output == '?')
			cout << "same, "; 
		else
			cout << "'" << output << "', ";
		if(direction == 'R')
			cout << "right\n";
		else if(direction == 'L')
			cout << "left\n";
		else
			cout << "stay\n";
	}
};

bool check_valid_input(int argc, char * a[])
{
	if(argc > 4 || argc < 3 || (a[2][0] != '-' && a[2][1] != 'f' && argc == 4))
	{
		cout << "command line be a.out TM-file-name input-string\n";
		cout << "             or a.out TM-file-name -f input-file-name\n";
		exit(1);	
	}
	if(argc == 4)
		return true;
	else
		return false;
}

void removeSpaces(string & str)
{
	int count = 0;
	for (int i = 0; str[i]; i++)
	{
		if (str[i] != ' ')
			if (str[i] != '\t')
				if (str[i] != '\n')
					str[count++] = str[i];
	}
	str[count] = '\0';
	char * y = new char[count+1];
	for (int i = 0; i < count+1; i++)
		y[i] = str[i];
	str = y;
}

void print_vec_l(vector <char> left)
{
	if(left.empty())
		return;
	for(int i = 0; i < left.size(); i++)
		cout << left[i];
}

void print_vec_r(vector <char> right)
{
	if(right.empty())
		return;
	for(int i = 0; i < right.size(); i++)
		cout << right[right.size()-i-1];
}

void print_tape(vector <char> l, char c, vector <char> r)
{
	print_vec_l(l);
	if(c == '\0')
		cout << " \\0 ";
	else if(c == 'Â')
		cout << " ? ";
	else
		cout << " " << c << " ";
	print_vec_r(r);
	cout << endl;
	for(int i = 0; i < l.size(); i++)
		if(l[i] != '\0')
			cout << " ";
	if(c != '\0')
		cout << "*^*\n";
	else
		cout << "*^^*\n";
}

//void print_plane() { cout<<"\n#############################################################"<<endl;sleep(1);cout<<"#                    _                                      #"<<endl;  sleep(1);cout<<"#                  -=\\`\\                                    #"<<endl;  sleep(1);cout<<"#              |\\ ____\\_\\__                                 #"<<endl;  sleep(1);cout<<"#            -=\\c`\"\"\"\"\"\"\" \"`)                               #"<<endl;  sleep(1);cout<<"#               `~~~~~/ /~~`\                WOOHOO!         #"<<endl;  sleep(1);cout<<"#                 -==/ /                                    #"<<endl;  sleep(1);cout<<"#                   '-'                                     #"<<endl;  sleep(1);cout<<"#                  _  _                                     #"<<endl; sleep(1);cout<<"#                 ( `   )_                                  #"<<endl;  sleep(1);cout<<"#                (    )    `)                               #"<<endl;  sleep(1);cout<<"#              (_   (_ .  _) _)                             #"<<endl;  sleep(1);cout<<"#                                             _             #"<<endl;  sleep(1);cout<<"#                                            (  )           #"<<endl;  sleep(1);cout<<"#             _ .                         ( `  ) . )        #"<<endl;  sleep(1);cout<<"#           (  _ )_                      (_, _(  ,_)_)      #"<<endl;  sleep(1);cout<<"#         (_  _(_ ,)                                        #"<<endl;  ;cout<<"#############################################################"<<endl; sleep(1); }

void print_current(string cs, char c)
{
	if(c == '\0')
		cout << "state " << cs << ", input '\\0' - ";
	else if(c == 'Â')
		cout << "state " << cs << ", input '?' - "; //can delete these two backslashes to make it look nice
	else
		cout << "state " << cs << ", input '" << c << "' - ";

}

void print_interval(vector <char> left, char current, vector <char> right, int count)
{
	cout << "After " << count << " steps\n--------- on the tape to the left:\n";
	print_vec_l(left);
	cout << "\n--------- symbol visible now: ";
	if(current == '\0')
		cout << "\\0";
	else if(current == 'Â')
		cout << "?"; //can delete backslashes
	else
		cout << current;
	cout << "\n--------- on the tape to the right:\n";
	print_vec_r(right);
	cout << "\n---------\n";	
}

void palk_end(vector <char> left, char current, vector <char> right)
{
	cout << "\n-----Official Result--------------------------------------------\n";
	cout << "|";
	for(int i = 2; i < 64; i+=1)
		cout << "â†“";
	cout << "|\n|";
	for(int i = 2; i < 64; i+=1)
		cout << " ";
	cout << "|\n| ";
	print_vec_l(left);
	cout << current;
	print_vec_r(right);
	cout << "\n|";
	for(int i = 2; i < 64; i+=1)
		cout << " ";
	cout << "|\n|";
	for(int i = 2; i < 64; i+=1)
		cout << "â†‘";
	cout << "|\n";
	cout << "----------------------------------------------------------------\n\n";
}


/*void print_end(vector <char> l, char c, vector <char> r)
{
	cout << "------------------------------------ Tape Remaining to the left: \n";
	print_vec_l(l);
	cout << "\n------------------------------------ Official result:\n";
	/*if(c == '\0')
		cout << "\\0";		//this one doesn't make sense to print out
	else if(c == 'Â')
		cout << "?";
	else
		cout << c;
	print_vec_r(r);
	cout << "\n-----------------------------------------------------\n";
}*/

void print_tm_table(vector <table> tm_table)
{
	for(int i = 0; i < tm_table.size(); i++)
		tm_table[i].print();
}

void make_tape(string input, vector <char> & right)
{
	for(int i = 0; i < input.length(); i++)
		right.push_back(input[input.length()-i-1]);
}

void make_tape_f(char * tapeName, vector <char> & right)
{
	ifstream tapeFile;
	tapeFile.open(tapeName);
	if(tapeFile.fail())
	{
		cout << "can't read tape input file '" << tapeName << "'\n";
		exit(1);
	}
	string yeet = "";
	while(true)
	{
		string hehexd = "";
		getline(tapeFile, hehexd, '\n');
		if(tapeFile.eof())
			break;
		yeet += hehexd;
	}
	removeSpaces(yeet);
	for(int i = 0; i < yeet.length(); i++)
		right.push_back(yeet[yeet.length()-i-1]);
	tapeFile.close();
}

void adjust_tm_hmns(vector <table> & tm_table)
{
	for(int i = tm_table.size()-1; i > 0; i--)
	{
		if(tm_table[i].hmns > 0)
		{
			int f = tm_table[i].hmns;
			int * temp = new int[f+1];
			for(int j = 0; j < f + 1; j++)
				temp[j] = tm_table[i-j].hmns;
			for(int j = 0; j < f + 1; j++)
				tm_table[i-f+j].hmns = temp[j];
			i -= f;
			delete [] temp;
		}
	}
}

void make_tm_table(char * fn, vector <table> & tm_table)
{
	string f = fn;
	f += ".tm";
	const char * file_name = f.c_str();
    ifstream ifile;
	ifile.open(file_name);
	if(ifile.fail())
	{
		cout << "Can't read TM table from file '" << file_name << "'\n";
		exit(1);
	}
	string yeet = "";
	int y = 0;
	int c = 0;
	while(true)
	{
		string csnum;
		getline(ifile, csnum, ',');
		removeSpaces(csnum);
		if(yeet == csnum)
			c++;	
		else
		{
			c = 0;
			yeet = csnum;
		}
		string i;
		getline(ifile, i, ',');
		removeSpaces(i);
		string nst;
		getline(ifile, nst, ',');
		removeSpaces(nst);
		string o;
		getline(ifile, o, ','); 
		removeSpaces(o);
		string d;
		getline(ifile, d);
		removeSpaces(d);
		if(ifile.eof())
			break;
		y++;
		tm_table.push_back(table(csnum, i, nst, o, d, y, c));
	}
	ifile.close();
	adjust_tm_hmns(tm_table);
	print_tm_table(tm_table);
}

void state_adjust(vector <table> tm_table, vector <char> & left, char & current, vector <char> & right, int i)
{
	if(tm_table[i].direction == 'R')
	{
		left.push_back(tm_table[i].output);
		if(!right.empty())
		{	
			current = right.back();
			right.pop_back();
		}
		else
			current = '\0';
	}
	else if(tm_table[i].direction == 'L')
	{
		right.push_back(tm_table[i].output);
		if(!left.empty())
		{	
			current = left.back();
			left.pop_back();
		}
		else
			current = '\0';
	}
	else if(tm_table[i].direction == '-')
		current = tm_table[i].output;
	else
	{
		cout << "\n\n\nENTERED DIRECTION THAT IS INVALID!\n\n\n";
		exit(1);
	}
}

void state_adjust_q(vector <table> tm_table, vector <char> & left, char & current, vector <char> & right, int i)
{
	if(tm_table[i].direction == 'R')
	{
		if(tm_table[i].output != '?') 
		{
			left.push_back(tm_table[i].output);
			if(!right.empty())
			{		
				current = right.back();
				right.pop_back();
			}
			else
				current = '\0';
		}
	  	else
		{
			left.push_back(current);
			if(!right.empty())
			{	
				current = right.back();
				right.pop_back();
			}
			else
				current = '\0';
		}
	}
	else if(tm_table[i].direction == 'L')
	{
	  	if(tm_table[i].output != '?') 
	  	{
			right.push_back(tm_table[i].output);
			if(!left.empty())
			{	
				current = left.back();
				left.pop_back();
			}
			else
				current = '\0';
		}
	  	else
		{
			right.push_back(current);
			if(!left.empty())
			{	
				current = left.back();
				left.pop_back();
			}
			else
				current = '\0';
		}
	}
	else if(tm_table[i].direction == '-')
	{	
		if(tm_table[i].output != '?')
			current = tm_table[i].output;
	}
	else
	{
		cout << "\n\n\nENTERED DIRECTION THAT IS INVALID!\n\n\n";
		exit(1);
	}
}

void user_input(bool & ask, bool & print_out, bool & until, string & sn, int i, vector <table> tm_table, vector <char> left, char current, vector <char> right, int count)
{
	if(print_out)
		tm_table[i].print();
	if(ask)
	{		
		while(true)
		{	
				cout << "> ";
				string s = "";
				getline(cin, s);
				char * temp = new char[2];
				temp[0] = s[0];
				temp[1] = s[1];
				if((temp[0] == 'r' || temp[0] == 'R') && temp[1] == '\0')
				{	
					ask = false;
					break;	
				}
				else if((temp[0] == 'r' || temp[0] == 'R') && (temp[1] == 'u' || temp[1] == 'U'))
				{	
					removeSpaces(s);
					ask = false; 
					until = true;
					sn = s.substr(2, s.length());		
					break; 
				}
				else if((temp[0] == 'q' || temp[0] == 'Q') && (temp[1] == 'u' || temp[1] == 'U'))
				{	
					removeSpaces(s);
					ask = false; 
					print_out = false;
					until = true;
					sn = s.substr(2, s.length());							
					break; 
				}
				else if((temp[0] == 'q' || temp[0] == 'Q') && temp[1] == '\0')
				{	
					ask = false;
					print_out = false; 
					break;	
				}
				else if((temp[0] == 't' || temp[0] == 'T') && temp[1] == '\0')
				{
					print_interval(left, current, right, count);
				}
				else if((temp[0] == 'h' || temp[0] == 'H') && temp[1] == '\0')
				{
					if(current == tm_table[i].input)
						state_adjust(tm_table, left, current, right, i);
					else if(tm_table[i].input == '?')
						state_adjust_q(tm_table, left, current, right, i);
					cout << "After " << count << " steps\n";
					palk_end(left, current, right);
					exit(1);
				}
				else if(s == "")
					break;
				else
					cout << "'" << s << "' not understood: h, r, q, ru, qu, or t\n";
		}
	}
}

void questions(vector <char> l, char c, vector <char> r)
{
	string t;
	cout << "Would you like to see specifically where the data was on the tape?\n";
	cout << "~y for yes and n for no: ";
	cin >> t;
	if(t == "y")
	{	
		cout << "Alrighty then, the cursor is pointing to what current ended on!\n"
			 << "Left of it was what was left on the left side of the tape!\n"
			 << "Now to the right of it is what was on the right side of the tape!\n"; 
		print_tape(l, c, r); 
	}	
	cout << "\n       Well . . .\n"
	     << "Would you like to see a plane?!\n"
		 << "A word will make the PLANE appear: ";
	cin >> t;
	if (t == "plane")
		cout << "Lucky bugger got it first try...\n"; //print_plane(); 	
	else
	{
		while(true)
		{
			cout << "\nOof, didn't get it did ya . . .\n"
				 << "Don't worry, you get infinite tries!\n"
				 << "     Try again: ";
			cin >> t;
			if (t == "plane")
			{	//print_plane(); 
			break; }
		}
	}
}

void solve_tm(vector <char> & right, vector <char> & left, vector <table> & tm_table)
{
	char current = right.back();
	right.pop_back();
	int current_tm = 0, count = 1;
	string cs = tm_table[current_tm].current_state, sn = "";
	bool ask = true, print_out = true, until = false, bad_char = false;
	while(cs.substr(0,4) != "stop")
	{
		if(print_out)
		{
			print_tape(left, current, right);
			print_current(cs, current);
		}		
		for(int i = 0; i < tm_table.size(); i++)
		{
			if(cs == tm_table[i].current_state)
			{
				if(current == tm_table[i].input)
				{
					user_input(ask, print_out, until, sn, i, tm_table, left, current, right, count);					
					state_adjust(tm_table, left, current, right, i);
					cs = tm_table[i].next_state;
					current_tm = i;
					break;
				}
				else if(tm_table[i].input == '?')
				{	
					if(tm_table[i].hmns > 0)
					{
						int f = tm_table[i].hmns;
						for(int j = i; j < i+f+1; j++)
							if(tm_table[j].input == current)
							{	
								i = j; 
								break;
							}
					}	
					user_input(ask, print_out, until, sn, i, tm_table, left, current, right, count);					
					state_adjust_q(tm_table, left, current, right, i);
					cs = tm_table[i].next_state;
					current_tm = i;
					break;
				}
			}
			if(i == tm_table.size()-1)
				bad_char = true;
		}
		if(bad_char)
		{
			cout << "no transition matching state " << tm_table[current_tm].current_state 
				 << " and input '" << current << "'\n";
			cout << "\n----------------------PLEASE CHECK YOUR TM TABLE FILE!----------------------\n\n";
			exit(1); 
		}
		count++;
		if(until && sn == cs)
		{
			ask = true;
			print_out = true;
			until = false;
		}
	}
	if(print_out)
	{
		print_tape(left, current, right);
		print_current(cs, current);
	}		
	cout << "all finished, After " << count << " steps\n";
	//print_end(left, current, right);
	palk_end(left, current, right);
	//questions(left, current, right);
}

int main(int argc, char * argv[])
{
	bool file = check_valid_input(argc, argv);
	vector <table> tm_table;
	vector <char> right;
	vector <char> left;
	if(file)
		make_tape_f(argv[3], right);
	else
		make_tape(argv[2], right);
	make_tm_table(argv[1], tm_table);
	solve_tm(right, left, tm_table);
	return 0;
}
