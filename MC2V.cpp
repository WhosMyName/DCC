/*

DirectoryCopyCat

-1. Get Operating System; ------------------------------------------------------------y
0.Ask for Volume/Season Renaming; ----------------------------------------------------y
1.Get Directory; ---------------------------------------------------------------------y Insert into Dir
2.Enable Volume 0 Support; -----------------------------------------------------------y
3.Check Child Directorys; ------------------------------------------------------------y
4.Count Child Directorys;-------------------------------------------------------------?
5.Compare Directorys via StringCompare; ----------------------------------------------?
6.Differentiate Directorys via Names and save Names (incremented 2D-Array 0,x);-------y
7.Count Amount of non-equal (neq) Directory changes (incremented 2D-Array x,0);-------y
8.Get Parent Folder Name; ------------------------------------------------------------y
9.Create Volumes/Seasons Folders based on 6 and 7; -----------------------------------y
10.Access Folders;--------------------------------------------------------------------y
11.Copy Files to Created Directory;---------------------------------------------------y
12.Increment Volumes/Seasons Folder based on 7; --------------------------------------y
13.Switch to next Folder; ------------------------------------------------------------y
14.Cycle through 2D-Array; -----------------------------------------------------------y
15.Compare Copyed Files with old Files; ----------------------------------------------WIP - ???
16.Delete old Files; -----------------------------------------------------------------WIP - Optional?
17.Remove old Directorys; ------------------------------------------------------------WIP - Optional
18.Open Parent Directory in File Explorer; -------------------------------------------WIP - Optional since it's executed inParent Directory

*/

#include <stdio.h> 
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <iterator>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/predef.h>

using namespace std;
using namespace boost::filesystem;

int Type = 0; //Determines type of Media to be focused on
int Vol0; //Initialize only, shows inverted usage if Volume 0 functionallity
int DiffDirs; //Initialize only, Counts the Amount of Chapters
int Fill;
int Clear;
path OriginalPath = current_path(); //Gets The Current Path, which contains the Program

typedef vector<path> vec; // store paths, so we can store and sort them later
vec v; //Vector for Source-Directory
vec x; //Vector for Source-Directory without Zeros for Comparison
vec u; //Vector for Files
vec w; //Vector for Destination-Directory

/*
void getRenameType(){
	string Media;
	cout << "Would you like to Rename Series or Books?" << endl; //Output Self-Explainatory
	cout << "Please answer with either \"Series\" or \"Books\" without the Quotes!" << endl; //Output Self-Explainatory
	getline (cin, Media); //Save String extraction
	if (Media.compare("Series") == 0){ //Compares Input with String
		int Type = 1;
		return;
	}
	else if (Media.compare("Books") == 0){ //Compares Input with String
		string VOL;
		cout << "Should the Usage of the Volume 0 be enabled?" << endl; //Output Self-Explainatory
		getline(cin, VOL); //Save String extraction
		if (VOL.compare("Yes") == 0){ //Compares Input with String inverted for compatibillity see cyclepath
			Vol0 = 0;
		}
		if (VOL.compare("No") == 0){ //Compares Input with String
			Vol0 = 1;
		}
		int Type = 2;
		return;
	}
	else { //If no Input equals to above Cases then Exit
		cout << "Wrong Input!" << endl; //Output Self-Explainatory
		exit(EXIT_FAILURE); //Force Exit
	}
}
*/

void showvecs(){ //Optional
	cout << "<-----------------------V-------------------------------->" << endl << endl;
	for (vec::iterator it (v.begin()); it != v.end(); ++it){ //Iteration cycles through Vector V
		cout << (*it).filename() << " was the latest added Directory!" << endl << endl;
	}
	cout << "<------------------------W------------------------------->" << endl << endl;
	for (vec::iterator it2 (w.begin()); it2 != w.end(); ++it2){ //Iteration cycles through Vector W
		cout << (*it2).filename() << " was the latest added Directory!" << endl << endl;
	}
	cout << "<------------------------X------------------------------->" << endl << endl;
	for (vec::iterator it4 (x.begin()); it4 != x.end(); ++it4){ //Iteration cycles through Vector W
		cout << (*it4) << " was the latest added Directory!" << endl << endl;
	}
	cout << "<------------------------------------------------------->" << endl << endl;
}
//................................................................................................\\

void differentiate(){

	if (Fill > 0 && Vol0 == 1){
		Fill++;
	}
	cout << "<------------------------------------------------------->" << endl << endl;
	cout << "Fill equals: " << Fill << endl << endl;
	cout << "<------------------------------------------------------->" << endl << endl;
	int i = Vol0;

	for (vec::iterator it (v.begin()); it != v.end(); ++it){
		stringstream ss4; //Creates a Stringstream for Counter Manipulation and conversion
		ss4.str(string()); //Clears the Stringstream
		ss4 << setfill('0') << setw(Fill) << i; //Adds the Counter to the Stringstream
		string str = ss4.str(); //Converts Stringstream to native String
		string Prefixint("Volume " + str); //Converted String Equals Volume + Prefix Int
		string subdir = (*it).filename().string();
		cout << "Prefixint: " << Prefixint << endl;
		cout << "subdir: " << subdir << endl;
		if (subdir.find(Prefixint) != string::npos){
			ss4.str(string()); //Clears the Stringstream
			ss4 << setfill('0') << setw(Fill) << i; //Adds the Counter to the Stringstream
			string str = ss4.str(); //Converts Stringstream to native String
			string Prefixint("Volume " + str); //Converted String Equals Volume + Prefix Int
			cout << isdigit(subdir.find(Prefixint)) << endl; //Optional
			cout << Prefixint << "!!!!!!!!!" << endl; //Optional
			cout << "SS4 equals to " << ss4.str() << endl; //Optional
			DiffDirs++;
			i++;
			cout << DiffDirs << endl;
		}
	}
	cout << "<------------------------------------------------------->" << endl << endl; //Optional
	cout << "DiffDirs equals: " << DiffDirs << endl << endl; //Optional
	cout << "Vol0 equals: " << Vol0 << endl << endl; //Optional
	cout << "Fill equals: " << Fill << endl << endl; //Optional
	cout << "<------------------------------------------------------->" << endl << endl; //Optional
}

void fillx(){
	

	int i = Vol0;
	int j = i;
	if(i == 1){
		i = 0;
	}

	cout << "Startin FillX" << endl; //Optional

	while (i < DiffDirs){
		vec::iterator it4 (x.begin());
		stringstream ss5;
		ss5.str(string()); //Clears the Stringstream
		ss5 << setfill('0') << setw(Fill) << j; //Adds the Counter to the Stringstream
		string str = ss5.str(); //Converts Stringstream to native String
		string Prefixint("Volume " + str); //Converted String Equals Volume + Prefix Int
		i++;
		j++;
		x.insert(it4,Prefixint);
		cout << Prefixint << endl; //Optional
	}

	sort(x.begin(), x.end()); //std::sort, since directory iteration is not ordered on some file systems
}

void createdir(){
	cout << "DiffDirs equals: " << DiffDirs << endl << endl; //Optional
	if(DiffDirs < 10){
		Fill = 1;
		cout << "Fill equals: " << Fill << endl << endl; //Optional
	}
	else if(DiffDirs >= 10 && DiffDirs < 100){
		Fill = 2;
		cout << "Fill equals: " << Fill << endl << endl; //Optional
	}
	else if(DiffDirs >= 100 && DiffDirs < 1000){
		Fill = 3;
		cout << "Fill equals: " << Fill << endl << endl; //Optional
	}
	else{
		Fill = 10; 
		cout << "Fill equals: " << Fill << endl << endl; //Optional
	}
	cout << "Pre-if" << endl; //Optional
	cout << "Vol0 equals: " << Vol0 << endl << endl; //Optional
	cout << "Fill equals: " << Fill << endl << endl; //Optional
	int i = Vol0;
	if(i == 1){
		i = 0;
	}
	while (i < DiffDirs){
		cout << "in if" << endl; //Optional
		stringstream ss; //Creates a Stringstream for Counter Manipulation and conversion
		ss << setfill('0') << setw(Fill) << Vol0; //Adds the Counter to the Stringstream
		string str = ss.str(); //Converts Stringstream to native String
		string Conv("Volume " + str); //Converted String Equals renamed Folders
		path Dir;
		Dir = Conv; // Cast String to Path
		vec::iterator it2 (w.begin());
		path Dir2 = current_path();
		cout << Dir2 << endl;
		cout << "Dir equals: " << Dir << endl << endl; //Optional
		cout << "Conv equals: " << Conv << endl << endl; //Optional
		if (create_directory(Dir)) { //Checks if creation of Directories Succeeds
			cout << "Success creating Directory called " << Dir << endl; //Outputs Success Message
			i++; //Ganz fcking Wichtig!
			Vol0++;
			Dir2 /= Dir; //Full Path in Vec W
			cout << Dir2 << endl; //Optional
			w.insert(it2,Dir2);//Inserts a Directory Path into the Vector W as single Node
			//it2++;
		}
		else{
			cout << "Breaking!" << endl; //Optional
			break;
		}
	}
	cout << "Past IF" << endl; //Optional
	sort(w.begin(), w.end()); //std::sort, since directory iteration is not ordered on some file systems
	for (vec::iterator it2 (w.begin()); it2 != w.end(); ++it2){ //Iteration cycles through Vector W
		cout << (*it2).filename() << " was the latest added Directory!" << endl << endl;
	}
}


void copyandcheck(){

	vec::iterator it (v.begin());
	vec::iterator it2 (w.begin());
	vec::iterator it3 (u.begin());
	vec::iterator it4 (x.begin());

	cout << "Startin' C'n' C" << endl; //Optional

	if(Vol0 != 1){

		cout << "Vol0 != 1" << endl << endl; //Optional

		for (vec::iterator it (v.begin()); it != v.end(); ++it){

			string Source = (*it4).string();
			string Destination = (*it2).filename().string();
			string VecV = (*it).filename().string();
			path SourcePath = (*it);
			path DestinationPath = (*it2);



			cout << Source << endl; //Optional
			cout << Destination << endl; //Optional

			cout << "Inside For" << endl; //Optional

			cout << "-----------------------------------------" << endl; //Optional

			if (VecV.find(Source) == string::npos){
				cout << "Unequal, jumping to next Directory!" << endl; //Optional
				it2++;
				it4++;
				it--;
			}
			else{
				
				cout << "Started Copy Process!" << endl; //Optional
				copy(directory_iterator(SourcePath), directory_iterator(), back_inserter(u)); //std::copy (inputfirst, inputlast, output)

				sort(u.begin(), u.end()); //std::sort, since directory iteration is not ordered on some file systems

				cout << Source << endl; //Optional
				cout << Destination << endl; //Optional
				cout << SourcePath << endl; //Optional
				cout << DestinationPath << endl; //Optional

				for (vec::iterator it3 (u.begin()); it3 != u.end(); ++it3){ //Iteration cycles through Vector V
					if (is_directory(*it3)){
						it3 = u.erase(it3);
						it3--;
					}
				}

				for (vec::iterator it3 (u.begin()); it3 != u.end(); ++it3){ //Iteration cycles through Vector W
					cout << (*it3).filename() << " was the latest added File!" << endl << endl;
					path Sourcefile = (*it3);
					path Destinationfile = DestinationPath/(*it3).filename();
					cout << Destinationfile << endl; //Optional
					copy_file(Sourcefile, Destinationfile);
				}

				cout << "Finished Copy Process!" << endl; //Optional
					
				u.erase(u.begin(), u.end());
			}
		}
	}
	if(Vol0 == 1){

		cout << "Vol0 == 1" << endl << endl; //Optional

		for (vec::iterator it (v.begin()); it != v.end(); ++it){

		string Source = (*it4).string();
		string Destination = (*it2).filename().string();
		string VecV = (*it).filename().string();
		path SourcePath = (*it);
		path DestinationPath = (*it2);



		cout << Source << endl; //Optional
		cout << Destination << endl; //Optional

		cout << "Inside For" << endl; //Optional

		cout << "-----------------------------------------" << endl; //Optional

		if (VecV.find(Source) == string::npos){
			cout << "Unequal, jumping to next Directory!" << endl; //Optional
			it2++;
			it4++;
			it--;
		}
		else{
			
			cout << "Started Copy Process!" << endl; //Optional
			copy(directory_iterator(SourcePath), directory_iterator(), back_inserter(u)); //std::copy (inputfirst, inputlast, output)

			sort(u.begin(), u.end()); //std::sort, since directory iteration is not ordered on some file systems

			cout << Source << endl; //Optional
			cout << Destination << endl; //Optional
			cout << SourcePath << endl; //Optional
			cout << DestinationPath << endl; //Optional

			for (vec::iterator it3 (u.begin()); it3 != u.end(); ++it3){ //Iteration cycles through Vector V
				if (is_directory(*it3)){
					it3 = u.erase(it3);
					it3--;
				}
			}

			for (vec::iterator it3 (u.begin()); it3 != u.end(); ++it3){ //Iteration cycles through Vector W
				cout << (*it3).filename() << " was the latest added File!" << endl << endl; //Optional
				path Sourcefile = (*it3);
				path Destinationfile = DestinationPath/(*it3).filename();
				cout << Destinationfile << endl; //Optional
				copy_file(Sourcefile, Destinationfile);
			}

			cout << "Finished Copy Process!" << endl; //Optional
				
			u.erase(u.begin(), u.end());
		}
	}
	}
}

void cyclepath(path p);

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!HAZARD!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//

void cycletest();

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//

//##################################################################################################################################################################//
int main(){

	if(BOOST_OS_WINDOWS){
        cout << "Windows" << endl;
	}
    else if(BOOST_OS_LINUX){
        cout << "Linux" << endl;
    }
    else{
        cout << "Other" << endl;
    }
    //cycletest();


	//getRenameType();
	cyclepath(OriginalPath);
	differentiate();
	fillx();
	createdir();
	showvecs();
	copyandcheck();

	return 0;
}
//##################################################################################################################################################################//

void cyclepath(path p){
	DiffDirs = 0;
	Fill = 0;
	try{
		if (exists(p)) {  // does p actually exist?
			if (is_regular_file(p)){  // is p a regular file?   
				cout << p << " size is " << file_size(p) << endl; //if it is output the filesize
			}
			else if (is_directory(p)){      // is p a directory?
				cout << p << " is a directory containing:" << endl;
				
				copy(directory_iterator(p), directory_iterator(), back_inserter(v)); //std::copy (inputfirst, inputlast, output)

				sort(v.begin(), v.end()); //std::sort, since directory iteration is not ordered on some file systems

				int count = 0; //Counts Directorys

				for (vec::iterator it (v.begin()); it != v.end(); ++it){ //Iteration cycles through Vector V
					if (!is_directory(*it)){
						it = v.erase(it);
						it--;
					}
					else{
						count++;
						cout << "We found " << count << " Directorys so far!" << endl; //Optional
						cout << (*it).filename() << " was the latest added Directory!" << endl << endl; //Optional
					}
				}
				cout << "The total amount of Directorys is: " << count << endl; //Optional
				cout << "Detecting Naming Scheme..." << endl; //Optional
				for (vec::iterator it (v.begin()); it != v.end(); ++it){
					for (int i = 1; i < 16; ++i){
						int one = 1;
						stringstream ss2; //Creates a Stringstream for Counter Manipulation and conversion
						ss2 << setfill('0') << setw(i) << one; //Adds the Counter to the Stringstream
						string str = ss2.str(); //Converts Stringstream to native String
						string Prefixint(" Volume " + str); //Converted String Equals Volume + Prefix Int
						string subdir = (*it).filename().string();
						if (subdir.find(Prefixint) != string::npos){
							cout << isdigit(subdir.find(Prefixint)) << endl; //Optional 
							cout << Prefixint << "!!!!!!!!!" << endl; //Optional 
							cout << "SS2 equals to " << ss2.str() << endl; //Optional 
							Vol0 = 1;
							break;
						}
						else{
							cout << (*it).filename().string() << endl;
							cout << Prefixint << endl;
							cout << "Breaking Madness!!" << endl; //Optional 
							cout << "Fill equals: " << Fill << endl; //Optional
							Fill++;
							continue;
						}
					}
					break;
				}
				cout << "Fillljnk equals: " << Fill << endl;//Optional
				if (Vol0 != 1){
					Fill = 0;
					for (vec::iterator it (v.begin()); it != v.end(); ++it){
						for (int i = 1; i < 16; ++i){
							int zero = 0;
							stringstream ss3; //Creates a Stringstream for Counter Manipulation and conversion
							ss3 << setfill('0') << setw(i) << zero; //Adds the Counter to the Stringstream
							string str = ss3.str(); //Converts Stringstream to native String
							string Prefixint("Volume " + str); //Converted String Equals Volume + Prefix Int
							string subdir = (*it).filename().string();
							if (subdir.find(Prefixint) == string::npos){
								ss3.str(string()); //Clears the Stringstream
								ss3 << setfill('0') << setw(i-1) << zero; //Adds the Counter to the Stringstream
								string str = ss3.str(); //Converts Stringstream to native String
								string Prefixint("Volume " + str); //Converted String Equals Volume + Prefix Int
								cout << isdigit(subdir.find(Prefixint)) << endl; //Optional
								cout << Prefixint << "!!!!!!!!!" << endl; //Optional
								ss3 << Prefixint;
								cout << "SS3 equals to " << ss3.str() << endl; //Optional 
								Vol0 = 0;
								break;
							}
							else{
								cout << (*it).filename().string() << endl;
								cout << Prefixint << endl;
								cout << "Breaking Madness!!" << endl; //Optional
								cout << "Fill equals: " << Fill << endl; //Optional
								Fill++;
								continue;
							}
						}
						break;
					}
				}
				cout << "<------------------------------------------------------->" << endl << endl; //Optional
				cout << "DiffDirs equals: " << DiffDirs << endl << endl; //Optional
				cout << "Vol0 equals: " << Vol0 << endl << endl; //Optional
				cout << "Fill equals: " << Fill << endl << endl; //Optional
				cout << "<------------------------------------------------------->" << endl << endl; //Optional
			}
			else{
				cout << p << " exists, but is neither a regular file nor a directory\n";
			}
		}
		else{
			cout << p << " does not exist\n";
		}
	}	
	catch (const filesystem_error& ex){
		cout << ex.what() << endl;
	}
}

///////////////////////////////////////HAZARD/////////////////////////////////////////
/*
void cycletest(){
	//Gets The Current Path, which contains the Program
	int Multi;
	cout << "Single or Auto?" << endl;
	cin >> Multi;

	path T1 = current_path();
	T1 /= "Example0";
	path T2 = current_path();
	T2 /= "Example00";
	path T3 = current_path();
	T3 /= "Example000";
	path T4 = current_path();
	T4 /= "Example1";
	path T5 = current_path();
	T5 /= "Example01";
	path T6 = current_path();
	T6 /= "Example001";
	path Testing[6] = {T1, T2, T3, T4, T5, T6};

	if (Multi == 0){
		for (int i = 0; i < 1; ++i){
			Clear = 1;
			cyclepath(Testing[3]);
			differentiate();
			fillx();
			createdir();
			showvecs();
			copyandcheck();
			cout << "<!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!>" << endl << endl;
			cout << "Done with Test Number: " << i << endl << endl;
			cout << "<#######################################################>" << endl << endl;
			Vol0 = 0;
			Fill = 0;
			DiffDirs = 0;

			if (Clear == 1){ //Clears the Vector v
				for (vec::iterator it (v.begin()); it != v.end(); ++it){ //Iteration cycles through sorted Directory
					it = v.erase(it);
					it--;
				}
			}

			if (Clear == 1){ //Clears the Vector v
				for (vec::iterator it (x.begin()); it != x.end(); ++it){ //Iteration cycles through sorted Directory
					it = x.erase(it);
					it--;
				}
			}

			cin.ignore().get();

			if (Clear == 1){ //Clears the Vector w
				for (vec::iterator it (w.begin()); it != w.end(); ++it){ //Iteration cycles through sorted Directory
					path delfolder = (*it);
					remove_all(delfolder);
					it = w.erase(it);
					it--;
				}
			}	
		}
	}
	if (Multi == 1){//FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF------AUTOTESTING------FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
		for (int i = 0; i < 6; ++i){
			Clear = 1;
			cyclepath(Testing[i]);
			differentiate();
			fillx();
			createdir();
			showvecs();
			copyandcheck();
			cout << "<!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!>" << endl << endl;
			cout << "Done with Test Number: " << i << endl << endl;
			cout << "<#######################################################>" << endl << endl;
			Vol0 = 0;
			Fill = 0;
			DiffDirs = 0;

			if (Clear == 1){ //Clears the Vector v
				for (vec::iterator it (v.begin()); it != v.end(); ++it){ //Iteration cycles through sorted Directory
					it = v.erase(it);
					it--;
				}
			}

			if (Clear == 1){ //Clears the Vector v
				for (vec::iterator it (x.begin()); it != x.end(); ++it){ //Iteration cycles through sorted Directory
					it = x.erase(it);
					it--;
				}
			}

			cin.ignore().get();

			if (Clear == 1){ //Clears the Vector w
				for (vec::iterator it2 (w.begin()); it2 != w.end(); ++it2){ //Iteration cycles through sorted Directory
					path delfolder = (*it2);
					remove_all(delfolder);
					it2 = w.erase(it2);
					it2--;
				}
			}

			if (Clear == 1){ //Clears the Vector u
				for (vec::iterator it3 (u.begin()); it3 != u.end(); ++it3){ //Iteration cycles through sorted Directory
					it3 = u.erase(it3);
					it3--;
				}
			}

			cin.ignore().get();	
		}
	}
}
*/