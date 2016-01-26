/*

DirectoryCopyCat

-1. Get Operating System; ------------------------------------------------------------y
0.Ask for Volume/Season Renaming; ----------------------------------------------------y
1.Get Directory; ---------------------------------------------------------------------WIP till the End
2.Enable Volume 0 Support; -----------------------------------------------------------y
3.Check Child Directorys; ------------------------------------------------------------y
4.Count Child Directorys;-------------------------------------------------------------?
5.Compare Directorys via StringCompare; ----------------------------------------------?
6.Differentiate Directorys via Names and save Names (incremented 2D-Array 0,x);-------y
7.Count Amount of non-equal (neq) Directory changes (incremented 2D-Array x,0);-------y
8.Get Parent Folder Name; ------------------------------------------------------------y
9.Create Volumes/Seasons Folders based on 6 and 7; -----------------------------------y
10.Access Folders;--------------------------------------------------------------------WIP -- Reverse Iter??
11.Copy Files to Created Directory;---------------------------------------------------WIP 
12.Increment Volumes/Seasons Folder based on 7; --------------------------------------y
13.Switch to next Folder; ------------------------------------------------------------y
14.Cycle through 2D-Array; -----------------------------------------------------------y
15.Compare Copyed Files with old Files; ----------------------------------------------WIP
16.Delete old Files; -----------------------------------------------------------------WIP - Optional?
17.Remove old Directorys; ------------------------------------------------------------WIP - Optional
18.Open Parent Directory in File Explorer; -------------------------------------------WIP

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

/*-------------------> ??? <----------------------*/
const int MAX_VOLUMES = 100;
const int MAX_DIRECTORYS = 100;
const int MAX_FILES = 500;
/*-------------------> ??? <----------------------*/

int Type = 0; //Determines type of Media to be focused on
int Vol0; //Initialize only, shows inverted usage if Volume 0 functionallity
int DiffDirs; //Initialize only, Counts the Amount of Chapters
int Fill;
int Clear;
path OriginalPath = current_path(); //Gets The Current Path, which contains the Program
//path Testing = (OriginalPath /= "Example001");
path ReName = OriginalPath.filename(); //Gets the Name of the Parent Folder, idk how but is does instead of parent_name(), but whatever ??? YOLO

typedef vector<path> vec; // store paths, so we can store and sort them later
vec v; //Vector for Source-Directory
vec u; //Vector for Files
vec w; //Vector for Destination-Directory
//string PathTraversal[MAX_VOLUMES][MAX_DIRECTORYS][MAX_FILES]; //Optional

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

void createdir(){
	cout << "DiffDirs equals: " << DiffDirs << endl << endl;
	if(DiffDirs < 10){
		Fill = 0;
		cout << "Fill equals: " << Fill << endl << endl;
	}
	else if(DiffDirs < 100 && DiffDirs >= 10){
		Fill = 1;
		cout << "Fill equals: " << Fill << endl << endl;
	}
	else if(DiffDirs < 1000 && DiffDirs >= 100){
		Fill = 2;
		cout << "Fill equals: " << Fill << endl << endl;
	}
	else{
		Fill = 10; 
		cout << "Fill equals: " << Fill << endl << endl;
	}
	cout << "Pre-if" << endl;
	cout << "Vol0 equals: " << Vol0 << endl << endl;
	int i = Vol0;
	if(i == 1){
		i = 0;
	}
	while (i < DiffDirs){
		cout << "in if" << endl;
		stringstream ss; //Creates a Stringstream for Counter Manipulation and conversion
		ss << setfill('0') << setw(Fill) << Vol0; //Adds the Counter to the Stringstream
		string str = ss.str(); //Converts Stringstream to native String
		string Parent = ReName.string(); //Converts Path to String
		string Conv("Volume " + str); //Converted String Equals renamed Folders
		path Dir;
		Dir = Conv; // Cast String to Path
		cout << "Dir equals: " << Dir << endl << endl;
		cout << "Conv equals: " << Conv << endl << endl;
		if (create_directory(Dir)) { //Checks if creation of Directories Succeeds
			cout << "Success creating Directory called " << Dir << endl; //Outputs Success Message
			i++; //Ganz fcking Wichtig!
			Vol0++;
		}
		else{
			cout << "Breaking!" << endl;
			break;
		}
	}
	cout << "Past IF" << endl;
}
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!HAZARD!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//

void cycletest();

void createtest();


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//
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
			ss4 << setfill('0') << setw(Fill) << Vol0; //Adds the Counter to the Stringstream
			string str = ss4.str(); //Converts Stringstream to native String
			string Prefixint("Volume " + str); //Converted String Equals Volume + Prefix Int
			cout << isdigit(subdir.find(Prefixint)) << endl; //Optional
			cout << Prefixint << "!!!!!!!!!" << endl; //Optional
			ss4 << Prefixint;
			cout << "SS4 equals to " << ss4.str() << endl; //Optional
			DiffDirs++;
			i++;
			cout << DiffDirs << endl;
		}
		/*else{
			cout << (*it).filename().string() << endl;
			cout << Prefixint << endl;
			cout << "Breaking Madness!!" << endl; //Optional
			continue;
		}*/
	}
	cout << "<------------------------------------------------------->" << endl << endl;
	cout << "DiffDirs equals: " << DiffDirs << endl << endl;
	cout << "Vol0 equals: " << Vol0 << endl << endl;
	cout << "Fill equals: " << Fill << endl << endl;
	cout << "<------------------------------------------------------->" << endl << endl;

	//OOOOOOOOOOOOOOOOOOOOOOOExperimentalOOOOOOOOOOOOOOOOOOOOO//

	if (Clear == 1){ //Clears the Vector vec
		for (vec::iterator it (v.begin()); it != v.end(); ++it){ //Iteration cycles through sorted Directory
			it = v.erase(it);
			it--;
		}
	}

	//000000000000000000000000000000000000000000000000000000//

}

void cyclepath(path p);

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
    cycletest();

    //Oppai!!!!
	//getRenameType();
	//cyclepath(Testing);
	//differentiate();
	//createdir();
	//Oppai!!!!
	return 0;
}
//##################################################################################################################################################################//

void cyclepath(path p){
	DiffDirs = 0;
	Fill = 0;
	try{
		if (exists(p)) {   // does p actually exist?
			if (is_regular_file(p)){       // is p a regular file?   
				cout << p << " size is " << file_size(p) << endl; //if it is output the filesize
			}
			else if (is_directory(p)){      // is p a directory?
				cout << p << " is a directory containing:" << endl;
				
				copy(directory_iterator(p), directory_iterator(), back_inserter(v));//I think it iterates through the Directory and saves all "Nodes" in the Vector

				sort(v.begin(), v.end()); // sort, since directory iteration is not ordered on some file systems

				//stringstream ss3; //BackUp String for Path of Files with PrefixZero !Cast to String!
				int count = 0; //Counts Directorys

				for (vec::iterator it (v.begin()); it != v.end(); ++it){ //Iteration cycles through sorted Directory
					if (!is_directory(*it)){
						it = v.erase(it);
						it--;
					}
					else{
						count++;
						cout << "We found " << count << " Directorys so far!" << endl;
						cout << (*it).filename() << " was the latest added Directory!" << endl << endl;
					}
				}
				cout << "The total amount of Directorys is: " << count << endl;
				cout << "Detecting Naming Scheme..." << endl;
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
							cout << "Fill equals: " << Fill << endl;
							Fill++;
							continue;
						}
					}
					break;
				}
				cout << "Fillljnk equals: " << Fill << endl;
				if (Vol0 != 1){
					Fill = 0;
					for (vec::iterator it (v.begin()); it != v.end(); ++it){
						for (int i = 1; i < 16; ++i){
							int zero = 0;
							stringstream ss3; //Creates a Stringstream for Counter Manipulation and conversion
							ss3 << setfill('0') << setw(i) << zero; //Adds the Counter to the Stringstream
							string str = ss3.str(); //Converts Stringstream to native String
							string Prefixint(" Volume " + str); //Converted String Equals Volume + Prefix Int
							string subdir = (*it).filename().string();
							if (subdir.find(Prefixint) == string::npos){
								ss3.str(string()); //Clears the Stringstream
								ss3 << setfill('0') << setw(i-1) << zero; //Adds the Counter to the Stringstream
								string str = ss3.str(); //Converts Stringstream to native String
								string Prefixint(" Volume " + str); //Converted String Equals Volume + Prefix Int
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
								cout << "Fill equals: " << Fill << endl;
								Fill++;
								continue;
							}
						}
						break;
					}
				}
				cout << "<------------------------------------------------------->" << endl << endl;
				cout << "DiffDirs equals: " << DiffDirs << endl << endl;
				cout << "Vol0 equals: " << Vol0 << endl << endl;
				cout << "Fill equals: " << Fill << endl << endl;
				cout << "<------------------------------------------------------->" << endl << endl;		
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

void createtest(){
	cout << "DiffDirs equals: " << DiffDirs << endl << endl;
	if(DiffDirs < 10){
		Fill = 0;
		cout << "Fill equals: " << Fill << endl << endl;
	}
	else if(DiffDirs < 100 && DiffDirs >= 10){
		Fill = 1;
		cout << "Fill equals: " << Fill << endl << endl;
	}
	else if(DiffDirs < 1000 && DiffDirs >= 100){
		Fill = 2;
		cout << "Fill equals: " << Fill << endl << endl;
	}
	else{
		Fill = 10; 
		cout << "Fill equals: " << Fill << endl << endl;
	}
	cout << "Pre-if" << endl;
	cout << "Vol0 equals: " << Vol0 << endl << endl;
	int i = Vol0;
	if(i == 1){
		i = 0;
	}
	while (i < DiffDirs){
		cout << "in if" << endl;
		stringstream ss; //Creates a Stringstream for Counter Manipulation and conversion
		ss << setfill('0') << setw(Fill) << Vol0; //Adds the Counter to the Stringstream
		string str = ss.str(); //Converts Stringstream to native String
		string Parent = ReName.string(); //Converts Path to String
		string Conv("Volume " + str); //Converted String Equals renamed Folders
		path Dir;
		Dir = Conv; // Cast String to Path
		cout << "Dir equals: " << Dir << endl << endl;
		cout << "Conv equals: " << Conv << endl << endl;
		if (create_directory(Dir)) { //Checks if creation of Directories Succeeds
			cout << "Success creating Directory called " << Dir << endl; //Outputs Success Message
			if (remove(Dir)){
				cout << "Delete!" << endl;
			}
			i++; //Ganz fcking Wichtig!
			Vol0++;
		}
		else{
			cout << "Breaking!" << endl;
			break;
		}
	}
	cout << "Past IF" << endl;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

void cycletest(){
	//Gets The Current Path, which contains the Program
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
	for (int i = 0; i < 6; ++i)
	{
		Clear = 1;
		cyclepath(Testing[i]);
		differentiate();
		createtest();
		cout << "<!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!>" << endl << endl;
		cout << "Done with Test Number: " << i << endl << endl;
		cout << "<#######################################################>" << endl << endl;
		Vol0 = 0;
		Fill = 0;
		DiffDirs = 0;
		//Prefixint = 0;	
	}
}

//////////////////////////////////////////////////////////////////////////////////////

/*
if (temp == NULL){
	temp = *it;
	cout << *it << endl;
}
else if(temp != NULL && temp.string().compare((*it).string()) != 0){
	temp = *it;
	cout << *it << endl;
	DiffDirs++;
}
*/