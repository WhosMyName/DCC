/*

DirectoryCopyCat

-1. Get Operating System; ------------------------------------------------------------y
0.Ask for Volume/Season Renaming; ----------------------------------------------------y
1.Get Directory; ---------------------------------------------------------------------WIP
2.Enable Volume 0 Support; -----------------------------------------------------------y
3.Check Child Directorys; ?
4.Count Child Directorys;?
5.Compare Directorys via StringCompare; ?
6.Differentiate Directorys via Names and save Names (incremented 2D-Array 0,x);
7.Count Amount of non-equal (neq) Directory changes (incremented 2D-Array x,0);
8.Get Parent Folder Name; ------------------------------------------------------------y
9.Create Volumes/Seasons Folders based on 6 and 7; -----------------------------------y
10.Access Folders;
11.Copy Files to Created Directory;
12.Increment Volumes/Seasons Folder based on 7; --------------------------------------y
13.Switch to next Folder;
14.Cycle through 2D-Array;
15.Compare Copyed Files with old Files;
16.Delete old Files;
17.Remove old Directorys;
18.Open Parent Directory in File Explorer;

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

const int MAX_VOLUMES = 100;
const int MAX_DIRECTORYS = 100;
const int MAX_FILES = 500;

int Type = 0;
int Vol0 = 0;
int DiffDirs = 5; //Initialize only, Counts the Amount of Chapters
path OriginalPath = current_path(); //Gets The Current Path, which contains the Program
path Testing = (OriginalPath /= "Example");
path ReName = OriginalPath.filename(); //Gets the Name of the Parent Folder, idk how but is does instead of parent_name(), but whatever ??? YOLO
//string PathTraversal[MAX_VOLUMES][MAX_DIRECTORYS][MAX_FILES];

void getRenameType(int Type, int Vol0){
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
		if (VOL.compare("Yes") == 0){ //Compares Input with String
			Vol0 = 1;
		}
		if (VOL.compare("No") == 0){ //Compares Input with String
			Vol0 = 0;
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
	for (int i = 0; i < DiffDirs; i++){
		stringstream ss; //Creates a Stringstream for Counter Manipulation and conversion
		ss << i; //Adds the Counter to the Stringstream
		string str = ss.str(); //Converts Stringstream to native String
		string Parent = ReName.string(); //Converts Path to String
		string Conv(Parent + " Volume " + str); //Converted String Equals renamed Folders
		path Dir;
		Dir = Conv; // Cast String to Path
		if (create_directory(Dir)) { //Checks if creation of Directories Succeeds
			cout << "Success creating Directory called " << Dir << endl; //Outputs Success Message
		}
	}
}



void cyclepath(path p);

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

	//getRenameType(Type, Vol0);
	createdir();
	cyclepath(Testing);
	return 0;
}


void cyclepath(path p){
	DiffDirs = 0;
	try{
		if (exists(p)) {   // does p actually exist?
			if (is_regular_file(p)){       // is p a regular file?   
				cout << p << " size is " << file_size(p) << endl; //if it is output the filesize
			}
			else if (is_directory(p)){      // is p a directory?
				cout << p << " is a directory containing:" << endl;
			
				typedef vector<path> vec;             // store paths, so we can sort them later
				vec v;

				copy(directory_iterator(p), directory_iterator(), back_inserter(v));

				sort(v.begin(), v.end());             // sort, since directory iteration is not ordered on some file systems

				path temp;

				for (vec::const_iterator it (v.begin()); it != v.end(); ++it){ //Iteration cycles through sorted Directory
					cout << (*it).filename() << endl;
				}
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

void cyclepath(path p){
	DiffDirs = 0;
	try{
		if (exists(p)) {   // does p actually exist?
			if (is_regular_file(p)){       // is p a regular file?   
				cout << p << " size is " << file_size(p) << endl; //if it is output the filesize
			}
			else if (is_directory(p)){      // is p a directory?
				cout << p << " is a directory containing:" << endl;
				string prev;
				cout << "String!" << endl;
				recursive_directory_iterator dir(p);
				cout << "Iter1" << endl;
				recursive_directory_iterator end;
				cout << "Iter2" << endl;
				while (dir != end){
					if (prev.empty() == true){
						string prev = (*dir).path().string();
						cout << "p p 	" << (*dir).path().string() << endl;
					}
					if ((*dir).path().filename() != prev){
						string prev = dir->path().string();
						cout << "wololololo" << endl;
						DiffDirs++;
						cout << DiffDirs << endl;
					}

					// do other stuff here.            
					cout << "Do Stuff!" << endl;
					++dir;
				}
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
*/