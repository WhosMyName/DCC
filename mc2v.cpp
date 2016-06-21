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

int Type = 0; //Determines type of Media to be focused on
int Vol0; //Initialize only, shows inverted usage if Volume 0 functionallity
int DiffDirs; //Initialize only, Counts the Amount of Chapters
int Fill; //Fills with corresponding 0 to match the Source
//int Clear; //Unused Var for Tesing
boost::filesystem::path OriginalPath = boost::filesystem::current_path(); //Gets The Current Path, which contains the Program should be locate in Manga Folder

typedef std::vector<boost::filesystem::path> vec; // store paths, so we can store and sort them later
vec v; //Vector for Source-Directory
vec w; //Vector for Destination-Directory
vec u; //Vector for Files
vec x; //Vector for Source-Directory without Zeros for Comparison

/* Old Function for getting Volume 0 and Media-Type, maybe usefull for later Projects
void getRenameType(){
	std::string Media;
	std::cout << "Would you like to Rename Series or Books?" << std::endl; //Output Self-Explainatory
	std::cout << "Please answer with either \"Series\" or \"Books\" without the Quotes!" << std::endl; //Output Self-Explainatory
	getline (cin, Media); //Save String extraction
	if (Media.compare("Series") == 0){ //Compares Input with String
		int Type = 1;
		return;
	}
	else if (Media.compare("Books") == 0){ //Compares Input with String
		std::string VOL;
		std::cout << "Should the Usage of the Volume 0 be enabled?" << std::endl; //Output Self-Explainatory
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
		std::cout << "Wrong Input!" << std::endl; //Output Self-Explainatory
		exit(EXIT_FAILURE); //Force Exit
	}
}
*/

void showvecs(){ //Optional
	std::cout << "<-----------------------V-------------------------------->" << std::endl << std::endl;
	for (vec::iterator it (v.begin()); it != v.end(); ++it){ //Iteration cycles through Vector V
		std::cout << (*it).filename() << " was the latest added Directory!" << std::endl << std::endl; //Outputs Content of Vector
	}
	std::cout << "<------------------------W------------------------------->" << std::endl << std::endl;
	for (vec::iterator it2 (w.begin()); it2 != w.end(); ++it2){ //Iteration cycles through Vector W
		std::cout << (*it2).filename() << " was the latest added Directory!" << std::endl << std::endl; //Outputs Content of Vector
	}
	std::cout << "<------------------------X------------------------------->" << std::endl << std::endl;
	for (vec::iterator it4 (x.begin()); it4 != x.end(); ++it4){ //Iteration cycles through Vector W
		std::cout << (*it4) << " was the latest added Directory!" << std::endl << std::endl; //Outputs Content of Vector
	}
	std::cout << "<------------------------------------------------------->" << std::endl << std::endl;
}
//................................................................................................\\

void differentiate(){ //Counts the amount of Different Directory aka Chapters

	if (Fill > 0 && Vol0 == 1){
		Fill++;
	}
	std::cout << "<------------------------------------------------------->" << std::endl << std::endl; //Optional
	std::cout << "Fill equals: " << Fill << std::endl << std::endl; //Optional
	std::cout << "<------------------------------------------------------->" << std::endl << std::endl; //Optional
	int i = Vol0;

	for (vec::iterator it (v.begin()); it != v.end(); ++it){
		std::stringstream ss4; //Creates a Stringstream for Counter Manipulation and conversion
		ss4.str(std::string()); //Clears the Stringstream
		ss4 << std::setfill('0') << std::setw(Fill) << i; //Adds the Counter to the Stringstream
		std::string str = ss4.str(); //Converts Stringstream to native String
		std::string Prefixint("Volume " + str); //Converted String Equals Volume + Prefix Int
		std::string subdir = (*it).filename().string(); //Casts Iterator at current Position to the Filename()-String
		std::cout << "Prefixint: " << Prefixint << std::endl; //Optional
		std::cout << "subdir: " << subdir << std::endl; //Optional
		if (subdir.find(Prefixint) != std::string::npos){ //Checks for Content of Prefixint in subdir
			ss4.str(std::string()); //Clears the Stringstream
			ss4 << std::setfill('0') << std::setw(Fill) << i; //Adds the Counter to the Stringstream
			std::string str = ss4.str(); //Converts Stringstream to native String
			std::string Prefixint("Volume " + str); //Converted String Equals Volume + Prefix Int
			std::cout << isdigit(subdir.find(Prefixint)) << std::endl; //Optional
			std::cout << Prefixint << "!!!!!!!!!" << std::endl; //Optional
			std::cout << "SS4 equals to " << ss4.str() << std::endl; //Optional
			DiffDirs++; //Increases Counter
			i++; //Increases Counter
			std::cout << DiffDirs << std::endl; //optional
		}
	}
	std::cout << "<------------------------------------------------------->" << std::endl << std::endl; //Optional
	std::cout << "DiffDirs equals: " << DiffDirs << std::endl << std::endl; //Optional
	std::cout << "Vol0 equals: " << Vol0 << std::endl << std::endl; //Optional
	std::cout << "Fill equals: " << Fill << std::endl << std::endl; //Optional
	std::cout << "<------------------------------------------------------->" << std::endl << std::endl; //Optional
}

void fillx(){
	

	int i = Vol0;
	int j = i;
	if(i == 1){ //Bug Fix for i = 1, dunno why this happens
		i = 0;
	}

	std::cout << "Startin FillX" << std::endl; //Optional

	while (i < DiffDirs){
		vec::iterator it4 (x.begin()); //Creates Iterator it4 on Vec X
		std::stringstream ss5;//Creates Stringstream for Conversion
		ss5.str(std::string()); //Clears the Stringstream
		ss5 << std::setfill('0') << std::setw(Fill) << j; //Adds the Counter to the Stringstream
		std::string str = ss5.str(); //Converts Stringstream to native String
		std::string Prefixint("Volume " + str); //Converted String Equals Volume + Prefix Int
		i++; //Increases Counter
		j++; //Increases Counter
		x.insert(it4,Prefixint); //Inserts Prefixint into Vec X on it4 Position
		std::cout << Prefixint << std::endl; //Optional
	}

	sort(x.begin(), x.end()); //std::sort, since directory iteration is not ordered on some file systems
}

void createdir(){
	std::cout << "DiffDirs equals: " << DiffDirs << std::endl << std::endl; //Optional
	if(DiffDirs < 10){
		Fill = 1;
		std::cout << "Fill equals: " << Fill << std::endl << std::endl; //Optional
	}
	else if(DiffDirs >= 10 && DiffDirs < 100){
		Fill = 2;
		std::cout << "Fill equals: " << Fill << std::endl << std::endl; //Optional
	}
	else if(DiffDirs >= 100 && DiffDirs < 1000){
		Fill = 3;
		std::cout << "Fill equals: " << Fill << std::endl << std::endl; //Optional
	}
	else{
		Fill = 10; 
		std::cout << "Fill equals: " << Fill << std::endl << std::endl; //Optional
	} //Checks for the Amount of Chapters and optionally increases the Fill
	std::cout << "Pre-if" << std::endl; //Optional
	std::cout << "Vol0 equals: " << Vol0 << std::endl << std::endl; //Optional
	std::cout << "Fill equals: " << Fill << std::endl << std::endl; //Optional
	int i = Vol0;
	if(i == 1){ //Same Bug, seee fillx()
		i = 0;
	}
	while (i < DiffDirs){
		std::cout << "in if" << std::endl; //Optional
		std::stringstream ss; //Creates a Stringstream for Counter Manipulation and conversion
		ss << std::setfill('0') << std::setw(Fill) << Vol0; //Adds the Counter to the Stringstream
		std::string str = ss.str(); //Converts Stringstream to native String
		std::string Conv("Volume " + str); //Converted String Equals renamed Folders
		boost::filesystem::path Dir; //Creates temporary Path
		Dir = Conv; // Cast String to Path
		vec::iterator it2 (w.begin()); //Creates Iterator it2 on Vec W
		boost::filesystem::path Dir2 = boost::filesystem::current_path(); //Creates temporary Path
		std::cout << Dir2 << std::endl; //Optional
		std::cout << "Dir equals: " << Dir << std::endl << std::endl; //Optional
		std::cout << "Conv equals: " << Conv << std::endl << std::endl; //Optional
		if (create_directory(Dir)) { //Checks if creation of Directories Succeeds
			std::cout << "Success creating Directory called " << Dir << std::endl; //Outputs Success Message
			i++; //Increases Counter - stops MC2V fron infinetely creating Folders^^
			Vol0++; //Increases Counter
			Dir2 /= Dir; //Full Path in Vec W, Hotfix
			std::cout << Dir2 << std::endl; //Optional
			w.insert(it2,Dir2);//Inserts a Directory Path into the Vector W as single Node
		}
		else{ //Break if something messed up
			std::cout << "Breaking!" << std::endl; //Optional
			break;
		}
	}
	std::cout << "Past IF" << std::endl; //Optional
	sort(w.begin(), w.end()); //std::sort, since directory iteration is not ordered on some file systems
	for (vec::iterator it2 (w.begin()); it2 != w.end(); ++it2){ //Iteration cycles through Vector W
		std::cout << (*it2).filename() << " was the latest added Directory!" << std::endl << std::endl;//Outputs Content of Vector
	}
}


void copyandcheck(){ //This is where the MAGIC happens

	vec::iterator it (v.begin()); //Creates Iterator it on Vec V
	vec::iterator it2 (w.begin()); //Creates Iterator it2 on Vec W
	vec::iterator it3 (u.begin()); //Creates Iterator it3 on Vec U
	vec::iterator it4 (x.begin()); //Creates Iterator it4 on Vec X

	std::cout << "Startin' C'n' C" << std::endl; //Optional

	if(Vol0 != 1){ //Triggers if Volume 0 = 0 

		std::cout << "Vol0 != 1" << std::endl << std::endl; //Optional

		for (vec::iterator it (v.begin()); it != v.end(); ++it){

			std::string Source = (*it4).string(); //Casts Iterator in Source-Directory to std::string 
			std::string Destination = (*it2).filename().string(); //Casts Iterator in Destination-Directory to Filename()-String
			std::string VecV = (*it).filename().string(); //Casts Iterator in Source-Directory to Filename()-String for Comparison
			boost::filesystem::path SourcePath = (*it); //Casts Iterator in Source-Directory to Path
			boost::filesystem::path DestinationPath = (*it2); //Casts Iterator in Destination-Directory to Path



			std::cout << Source << std::endl; //Optional
			std::cout << Destination << std::endl; //Optional

			std::cout << "Inside For" << std::endl; //Optional

			std::cout << "-----------------------------------------" << std::endl; //Optional
							//std::string.find(string2) returns Starting Position of Content of string2 and returns string::npos if string2 was not found in string
			if (VecV.find(Source) == std::string::npos){ //Dertermines Different Chapters by Directory-Name and jumps to next Chapter if string::npos is found
				std::cout << "Unequal, jumping to next Directory!" << std::endl; //Optional
				it2++; //Increases Iterator
				it4++; //Increases Iterator
				it--; //Increases Iterator
			}
			else{ //if Source was found, then the actual Copy Process starts
				
				std::cout << "Started Copy Process!" << std::endl; //Optional
				copy(boost::filesystem::directory_iterator(SourcePath), boost::filesystem::directory_iterator(), std::back_inserter(u)); //std::copy (inputfirst, inputlast, output)

				sort(u.begin(), u.end()); //std::sort, since directory iteration is not ordered on some file systems

				std::cout << Source << std::endl; //Optional
				std::cout << Destination << std::endl; //Optional
				std::cout << SourcePath << std::endl; //Optional
				std::cout << DestinationPath << std::endl; //Optional

				for (vec::iterator it3 (u.begin()); it3 != u.end(); ++it3){ //Iteration cycles through Vector U and removes Folder
					if (is_directory(*it3)){
						it3 = u.erase(it3);
						it3--;
					}
				}

				for (vec::iterator it3 (u.begin()); it3 != u.end(); ++it3){ //Iteration cycles through Vector U
					std::cout << (*it3).filename() << " was the latest added File!" << std::endl << std::endl; //Optional
					boost::filesystem::path Sourcefile = (*it3); //Casts Sourcefile-Name to path
					boost::filesystem::path Destinationfile = DestinationPath/(*it3).filename(); //Creates Full Path with Filename
					std::cout << Destinationfile << std::endl; //Optional
					copy_file(Sourcefile, Destinationfile); //Copys File from Source (Vec U) to Destination (Vec W)
				}

				std::cout << "Finished Copy Process!" << std::endl; //Optional
					
				u.erase(u.begin(), u.end()); //Clears Vec U of all Entrys
			}
		}
	}
	if(Vol0 == 1){ //Literally same just look above, should verify if it is redundant

		std::cout << "Vol0 == 1" << std::endl << std::endl; //Optional

		for (vec::iterator it (v.begin()); it != v.end(); ++it){

		std::string Source = (*it4).string();
		std::string Destination = (*it2).filename().string();
		std::string VecV = (*it).filename().string();
		boost::filesystem::path SourcePath = (*it);
		boost::filesystem::path DestinationPath = (*it2);



		std::cout << Source << std::endl; //Optional
		std::cout << Destination << std::endl; //Optional

		std::cout << "Inside For" << std::endl; //Optional

		std::cout << "-----------------------------------------" << std::endl; //Optional

		if (VecV.find(Source) == std::string::npos){
			std::cout << "Unequal, jumping to next Directory!" << std::endl; //Optional
			it2++;
			it4++;
			it--;
		}
		else{
			
			std::cout << "Started Copy Process!" << std::endl; //Optional
			copy(boost::filesystem::directory_iterator(SourcePath), boost::filesystem::directory_iterator(), std::back_inserter(u)); //std::copy (inputfirst, inputlast, output)

			sort(u.begin(), u.end()); //std::sort, since directory iteration is not ordered on some file systems

			std::cout << Source << std::endl; //Optional
			std::cout << Destination << std::endl; //Optional
			std::cout << SourcePath << std::endl; //Optional
			std::cout << DestinationPath << std::endl; //Optional

			for (vec::iterator it3 (u.begin()); it3 != u.end(); ++it3){ //Iteration cycles through Vector V
				if (is_directory(*it3)){
					it3 = u.erase(it3);
					it3--;
				}
			}

			for (vec::iterator it3 (u.begin()); it3 != u.end(); ++it3){ //Iteration cycles through Vector W
				std::cout << (*it3).filename() << " was the latest added File!" << std::endl << std::endl; //Optional
				boost::filesystem::path Sourcefile = (*it3);
				boost::filesystem::path Destinationfile = DestinationPath/(*it3).filename();
				std::cout << Destinationfile << std::endl; //Optional
				copy_file(Sourcefile, Destinationfile);
			}

			std::cout << "Finished Copy Process!" << std::endl; //Optional
				
			u.erase(u.begin(), u.end());
		}
	}
	}
}

void cyclepath(boost::filesystem::path p);

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!HAZARD!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//
//
//void cycletest(); //Testing Function with CleanUP
//
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//

//##################################################################################################################################################################//
int main(){

	if(BOOST_OS_WINDOWS){ //Checks OS
        std::cout << "Windows" << std::endl;
	}
    else if(BOOST_OS_LINUX){
        std::cout << "Linux" << std::endl;
    }
    else{
        std::cout << "Other" << std::endl;
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

void cyclepath(boost::filesystem::path p){
	DiffDirs = 0;
	Fill = 0;
	try{
		if (exists(p)) {  // does p actually exist?
			if (is_regular_file(p)){  // is p a regular file?   
				std::cout << p << " size is " << file_size(p) << std::endl; //if it is output the filesize
			}
			else if (is_directory(p)){      // is p a directory?
				std::cout << p << " is a directory containing:" << std::endl;
				
				copy(boost::filesystem::directory_iterator(p), boost::filesystem::directory_iterator(), std::back_inserter(v)); //std::copy (inputfirst, inputlast, output)

				sort(v.begin(), v.end()); //std::sort, since directory iteration is not ordered on some file systems

				int count = 0; //Counts Directorys

				for (vec::iterator it (v.begin()); it != v.end(); ++it){ //Iteration cycles through Vector V
					if (!is_directory(*it)){ //Iterates through Vec V and deletes Files
						it = v.erase(it);
						it--;
					}
					else{
						count++; //Increments std::couter for amount of Directorys
						std::cout << "We found " << count << " Directorys so far!" << std::endl; //Optional
						std::cout << (*it).filename() << " was the latest added Directory!" << std::endl << std::endl; //Optional
					}
				}
				std::cout << "The total amount of Directorys is: " << count << std::endl; //Optional
				std::cout << "Detecting Naming Scheme..." << std::endl; //Optional
				for (vec::iterator it (v.begin()); it != v.end(); ++it){
					for (int i = 1; i < 16; ++i){
						int one = 1; //Static Variable for 1 to prevent Errors (yeah actually happened, still dunno why)
						std::stringstream ss2; //Creates a Stringstream for Counter Manipulation and conversion
						ss2 << std::setfill('0') << std::setw(i) << one; //Adds the Counter to the Stringstream
						std::string str = ss2.str(); //Converts Stringstream to native String
						std::string Prefixint(" Volume " + str); //Converted String Equals Volume + Prefix Int
						std::string subdir = (*it).filename().string(); //Assigns Iterator Filename()-String to string
						if (subdir.find(Prefixint) != std::string::npos){ //Searches for the Amount of 0s inside the Directorynames and defines Vol0
							std::cout << isdigit(subdir.find(Prefixint)) << std::endl; //Optional 
							std::cout << Prefixint << "!!!!!!!!!" << std::endl; //Optional 
							std::cout << "SS2 equals to " << ss2.str() << std::endl; //Optional 
							Vol0 = 1; //Sets Vol0 to 1
							break;
						}
						else{
							std::cout << (*it).filename().string() << std::endl; //Optional
							std::cout << Prefixint << std::endl; //Optional
							std::cout << "Breaking Madness!!" << std::endl; //Optional 
							std::cout << "Fill equals: " << Fill << std::endl; //Optional
							Fill++; //Increases Counter
							continue;
						}
					}
					break;
				}
				std::cout << "Fillljnk equals: " << Fill << std::endl; //Optional
				if (Vol0 != 1){ //Same Routine as above, but implying that Vol0 = 0
					Fill = 0;
					for (vec::iterator it (v.begin()); it != v.end(); ++it){
						for (int i = 1; i < 16; ++i){
							int zero = 0;
							std::stringstream ss3; //Creates a Stringstream for Counter Manipulation and conversion
							ss3 << std::setfill('0') << std::setw(i) << zero; //Adds the Counter to the Stringstream
							std::string str = ss3.str(); //Converts Stringstream to native String
							std::string Prefixint("Volume " + str); //Converted String Equals Volume + Prefix Int
							std::string subdir = (*it).filename().string();
							if (subdir.find(Prefixint) == std::string::npos){
								ss3.str(std::string()); //Clears the Stringstream
								ss3 << std::setfill('0') << std::setw(i-1) << zero; //Adds the Counter to the Stringstream
								std::string str = ss3.str(); //Converts Stringstream to native std::string
								std::string Prefixint("Volume " + str); //Converted String Equals Volume + Prefix Int
								std::cout << isdigit(subdir.find(Prefixint)) << std::endl; //Optional
								std::cout << Prefixint << "!!!!!!!!!" << std::endl; //Optional
								ss3 << Prefixint;
								std::cout << "SS3 equals to " << ss3.str() << std::endl; //Optional 
								Vol0 = 0;
								break;
							}
							else{
								std::cout << (*it).filename().string() << std::endl;
								std::cout << Prefixint << std::endl;
								std::cout << "Breaking Madness!!" << std::endl; //Optional
								std::cout << "Fill equals: " << Fill << std::endl; //Optional
								Fill++;
								continue;
							}
						}
						break;
					}
				}
				std::cout << "<------------------------------------------------------->" << std::endl << std::endl; //Optional
				std::cout << "DiffDirs equals: " << DiffDirs << std::endl << std::endl; //Optional
				std::cout << "Vol0 equals: " << Vol0 << std::endl << std::endl; //Optional
				std::cout << "Fill equals: " << Fill << std::endl << std::endl; //Optional
				std::cout << "<------------------------------------------------------->" << std::endl << std::endl; //Optional
			}
			else{
				std::cout << p << " exists, but is neither a regular file nor a directory\n";
			}
		}
		else{
			std::cout << p << " does not exist\n";
		}
	}	
	catch (const boost::filesystem::filesystem_error& ex){ //Error handling!
		std::cout << ex.what() << std::endl;
	}
}

///////////////////////////////////////HAZARD/////////////////////////////////////////
/*
void cycletest(){
	//Gets The Current Path, which contains the Program
	int Multi;
	std::cout << "Single or Auto?" << std::endl;
	cin >> Multi;

	boost::filesystem::path T1 = boost::filesystem::current_path();
	T1 /= "Example0";
	boost::filesystem::path T2 = boost::filesystem::current_path();
	T2 /= "Example00";
	boost::filesystem::path T3 = boost::filesystem::current_path();
	T3 /= "Example000";
	boost::filesystem::path T4 = boost::filesystem::current_path();
	T4 /= "Example1";
	boost::filesystem::path T5 = boost::filesystem::current_path();
	T5 /= "Example01";
	boost::filesystem::path T6 = boost::filesystem::current_path();
	T6 /= "Example001";
	boost::filesystem::path Testing[6] = {T1, T2, T3, T4, T5, T6};

	if (Multi == 0){
		for (int i = 0; i < 1; ++i){
			Clear = 1;
			cyclepath(Testing[3]);
			differentiate();
			fillx();
			createdir();
			showvecs();
			copyandcheck();
			std::cout << "<!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!>" << std::endl << std::endl;
			std::cout << "Done with Test Number: " << i << std::endl << std::endl;
			std::cout << "<#######################################################>" << std::endl << std::endl;
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
					boost::filesystem::path delfolder = (*it);
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
			std::cout << "<!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!>" << std::endl << std::endl;
			std::cout << "Done with Test Number: " << i << std::endl << std::endl;
			std::cout << "<#######################################################>" << std::endl << std::endl;
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
					boost::filesystem::path delfolder = (*it2);
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

