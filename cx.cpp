//
//  cx.cpp
//  
//
//  Created by Grant Giesbrecht on 5/3/19.
//

#include <stdio.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

int main(int argc, char** argv){
	
	//--------------------- DISPLAY HELP PAGE IF NO INPUTS ---------------
	//
	
	if (argc < 2){
		
		cout << "No input arguments" << endl;
		cout << "Use -h to view help" << endl;
		
		return -1;
	}
	
	string first_arg = argv[1];
	
	if (first_arg == "-h" || first_arg == "-H" || first_arg == "-HELP" || first_arg == "-help" || first_arg == "-Help"){
		cout << "\t************** CX HELP *****************\n" << endl;
		cout << "\tCX automatically compiles and runs C++" << endl;
		cout << "\tprograms.\n" << endl;
		cout << "\tCX works by looking for a compile command" << endl;
		cout << "\twritten in a comment with the first word" << endl;
		cout << "\t'CXCOMPILE'. If multiple such comments exist," << endl;
		cout << "\tthey will be executed in a top to bottom" << endl;
		cout << "\torder. If no such commands exist, CX will try" << endl;
		cout << "\tto automatically determine what compiler flags" << endl;
		cout << "\tare neccesary, but this function is still" << endl;
		cout << "\tbeing developed.\n" << endl;
		cout << "\tThe command 'CXPRINTCOM' can be used to tell CX" << endl;
		cout << "\twhether or not it should print the commands it" << endl;
		cout << "\twill run. CXPRINTCOM must be followed immediately" << endl;
		cout << "\tby a space then 'TRUE' or 'FALSE', all uppercase," << endl;
		cout << "\tno quotes.\n" << endl;
		cout << "\tThe command 'CXVERCOM' can be used to tell CX" << endl;
		cout << "\twhether or not it should verify the commands" << endl;
		cout << "\tit will run with the user before running them." << endl;
		cout << "\tCXVERCOM must be followed immediately by a space" << endl;
		cout << "\tthen 'TRUE' or 'FALSE', all uppercase, no quotes.\n" << endl;
		cout << "\tNOTE: Any and all CX directives (such as CXCOMPILE" << endl;
		cout << "\tand CXVERCOM) must be present before the main" << endl;
		cout << "\tfunction is declared.\n" << endl;
		cout << "\tThe command 'CXGENRUN' can be used to tell CX" << endl;
		cout << "\twhether or not it should generate the command to" << endl;
		cout << "\trun the executable. If the user provides an" << endl;
		cout << "\texecutable run command with a CXCOMPILE directive," << endl;
		cout << "\tCXGENRUN FALSE prevents CX from generating its own" << endl;
		cout << "\trun command. CXGENRUN must be followed immediately" << endl;
		cout << "\tby a space then 'TRUE' or 'FALSE', all uppercase," << endl;
		cout << "\tno quotes.\n" << endl;
		cout << "\tExample usages (to run in command line):" << endl;
		cout << "\t\tcx testprogram    OR    cx testprogram.cpp" << endl;
		cout << "\tExample usage (to appear in testprogram.cpp):" << endl;
		cout << "\t\t//CXCOMPILE clang++ -o output testprogram.cpp" << endl;
		cout << "\t\t// CXPRINTCOM TRUE" << endl;
		cout << "\t\t//CXGENRUN FALSE" << endl;
		
		return 0;
	}
	
	//------------------- DETERMINE FILE NAME -------------------------
	//
	
	string filename = argv[1]; //Filename WTIHOUT extension
	string filename_w_ext = argv[1]; // Filename WITH extension
	
	//Scan for extension in 'argv[1]'
	bool extension_found = false;
	for (size_t i = 0 ; i < filename.length() ;  i++){
		if (filename[i] == '.'){ //If an extension is found...
			filename = filename.substr(0, i); //Cut extension off
			extension_found = true; //Mark that an extension was found
		}
	}
	
	//Add extension to 'filename_w_ext', if neccesary
	if (!extension_found){
		filename_w_ext = filename_w_ext + ".cpp";
	}
	
	ifstream file;
	file.open(filename_w_ext);
	if (!file.is_open()){
		cout << "\tERROR: Failed to open file '" << argv[1] << "'" << endl;
		return -1;
	}
	
	//-------------------- GENERATE COMPILER COMMANDS ------------------
	//
	
	vector<string> compiler_commands;
	bool print_commands = false; //Print commands before running them
	bool verify_commands = false; //Verify commands with user before running them
	bool generate_run_command = true; //CX must generate its own command to run the executable
	
	//Scan through file, look for
	string line;
	size_t line_number = 1;
	while (file.good()){
		
		//Read next line
		getline(file, line);
		
		//Look for compile commands
		if (line.substr(0, 12) == "// CXCOMPILE"){
			compiler_commands.push_back(line.substr(13)); //Add compiler command
			continue;
		}else if( line.substr(0, 11) == "//CXCOMPILE"){
			compiler_commands.push_back(line.substr(12)); //Add compiler command
			continue;
		}
		
		//Look for output filename commands (ie. name of thing to run)
		
		//Look for 'print commands' commands
		if (line.substr(0, 13) == "// CXPRINTCOM"){
			if (line.length() < 18){
				cout << "\tDIRECTIVE SKIPPED: No boolean argument provided after call to 'CXPRINTCOM' on line " << line_number << "." << endl;
			}else if(line.substr(14) == "TRUE"){
				print_commands = true;
			}else if(line.substr(14) == "FALSE"){
				print_commands = false;
			}else{
				cout << "\tDIRECTIVE SKIPPED: Invalid argument provided after call to 'CXPRINTCOM' on line " << line_number << "." << endl;
			}
			continue;
		}else if (line.substr(0, 12) == "//CXPRINTCOM"){
			if (line.length() < 17){
				cout << "\tDIRECTIVE SKIPPED: No boolean argument provided after call to 'CXPRINTCOM' on line " << line_number << "." << endl;
			}else if(line.substr(13) == "TRUE"){
				print_commands = true;
			}else if(line.substr(13) == "FALSE"){
				print_commands = false;
			}else{
				cout << "\tDIRECTIVE SKIPPED: Invalid argument provided after call to 'CXPRINTCOM' on line " << line_number << "." << endl;
			}
			continue;
		}
		
		//Look for 'verify commands' commands
		if (line.substr(0, 11) == "// CXVERCOM"){
			if (line.length() < 16){
				cout << "\tDIRECTIVE SKIPPED: No boolean argument provided after call to 'CXVERCOM' on line " << line_number << "." << endl;
			}else if(line.substr(12) == "TRUE"){
				verify_commands = true;
			}else if(line.substr(12) == "FALSE"){
				verify_commands = false;
			}else{
				cout << "\tDIRECTIVE SKIPPED: Invalid argument provided after call to 'CXVERCOM' on line " << line_number << "." << endl;
			}
			continue;
		}else if (line.substr(0, 10) == "//CXVERCOM"){
			if (line.length() < 15){
				cout << "\tDIRECTIVE SKIPPED: No boolean argument provided after call to 'CXVERCOM' on line " << line_number << "." << endl;
			}else if(line.substr(11) == "TRUE"){
				verify_commands = true;
			}else if(line.substr(11) == "FALSE"){
				verify_commands = false;
			}else{
				cout << "\tDIRECTIVE SKIPPED: Invalid argument provided after call to 'CXVERCOM' on line " << line_number << "." << endl;
			}
			continue;
		}
		
		//Look for 'verify commands' commands
		if (line.substr(0, 11) == "// CXGENRUN"){
			if (line.length() < 16){
				cout << "\tDIRECTIVE SKIPPED: No boolean argument provided after call to 'CXGENRUN' on line " << line_number << "." << endl;
			}else if(line.substr(12) == "TRUE"){
				generate_run_command = true;
			}else if(line.substr(12) == "FALSE"){
				generate_run_command = false;
			}else{
				cout << "\tDIRECTIVE SKIPPED: Invalid argument provided after call to 'CXGENRUN' on line " << line_number << "." << endl;
			}
			continue;
		}else if (line.substr(0, 10) == "//CXGENRUN"){
			if (line.length() < 15){
				cout << "\tDIRECTIVE SKIPPED: No boolean argument provided after call to 'CXGENRUN' on line " << line_number << "." << endl;
			}else if(line.substr(11) == "TRUE"){
				generate_run_command = true;
			}else if(line.substr(11) == "FALSE"){
				generate_run_command = false;
			}else{
				cout << "\tDIRECTIVE SKIPPED: Invalid argument provided after call to 'CXGENRUN' on line " << line_number << "." << endl;
			}
			continue;
		}
		
		//Stop function once main function is declared
		if (line.substr(0, 8) == "int main" || line.substr(0, 4) == "main"){
			break;
		}
		
		//Increment line number
		line_number++;
		
	}
	
	//If no command was specified, generate a command from the filename
	if (compiler_commands.size() < 1){
		compiler_commands.push_back("clang++ -o " + filename + " " + filename_w_ext);
	}
	
	//Add command to run code
	if (generate_run_command){
		compiler_commands.push_back("./" + filename);
	}
	
	//------------------ PRINT AND RUN COMMANDS --------------------------
	
	//Print commands if requested
	if (print_commands){
		cout << "\tWill run: " << endl;
		for (int i = 0 ; i < compiler_commands.size() ; i++){
			cout << "\t\t[" << i+1 << ".] '" << compiler_commands[i] << "'" << endl;
		}
	}
	
	//Verify commands before running if requested
	if (verify_commands){
		string user_input;
		cout << "Proceed? Enter 'Y' to continue: ";
		getline(cin, user_input);
		
		if (user_input != "Y"){
			return -1;
		}
	}

	//Run commands
	for (int i = 0 ; i < compiler_commands.size() ; i++){
		system(compiler_commands[i].c_str());
	}
	
	return 0;
}
