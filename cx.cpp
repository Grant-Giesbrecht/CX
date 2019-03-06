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
		cout << "************** CX HELP *****************\n" << endl;
		cout << "CX automatically compiles and runs C++" << endl;
		cout << "programs.\n" << endl;
		cout << "CX works by looking for a compile command" << endl;
		cout << "written in a comment with the first word" << endl;
		cout << "'CXCOMPILE'. If multiple such comments exist," << endl;
		cout << "they will be executed in a top to bottom" << endl;
		cout << "order. If no such commands exist, CX will try" << endl;
		cout << "to automatically determine what compiler flags" << endl;
		cout << "are neccesary, but this function is still" << endl;
		cout << "being developed.\n" << endl;
		cout << "The command 'CXPRINTCOM' can be used to tell CX" << endl;
		cout << "whether or not it should print the commands it" << endl;
		cout << "will run. CXPRINTCOM must be followed immediately" << endl;
		cout << "by a space then 'TRUE' or 'FALSE', all uppercase," << endl;
		cout << "no quotes. Defaults to off.\n" << endl;
		cout << "The command 'CXVERCOM' can be used to tell CX" << endl;
		cout << "whether or not it should verify the commands" << endl;
		cout << "it will run with the user before running them." << endl;
		cout << "CXVERCOM must be followed immediately by a space" << endl;
		cout << "then 'TRUE' or 'FALSE', all uppercase, no quotes." << endl;
		cout << "Defaults to off.\n" << endl;
		cout << "The command 'CXGENRUN' can be used to tell CX" << endl;
		cout << "whether or not it should generate the command to" << endl;
		cout << "run the executable. If the user provides an" << endl;
		cout << "executable run command with a CXCOMPILE directive," << endl;
		cout << "CXGENRUN FALSE prevents CX from generating its own" << endl;
		cout << "run command. CXGENRUN must be followed immediately" << endl;
		cout << "by a space then 'TRUE' or 'FALSE', all uppercase," << endl;
		cout << "no quotes. Defaults to on.\n" << endl;
		cout << "The command 'CXPERSIST' can be used to tell CX" << endl;
		cout << "whether or not it should continue executing " << endl;
		cout << "commands in the event of one command resulting in" << endl;
		cout << "and error. CXPERSIST must be followed immediately" << endl;
		cout << "by a space then 'TRUE' or 'FALSE', all uppercase," << endl;
		cout << "no quotes. Defaults to off.\n" << endl;
		cout << "NOTE: Any and all CX directives (such as CXCOMPILE" << endl;
		cout << "and CXVERCOM) must be present before the main" << endl;
		cout << "function is declared.\n" << endl;
		cout << "Example usages (to run in command line):" << endl;
		cout << "\tcx testprogram    OR    cx testprogram.cpp" << endl;
		cout << "Example usage (to appear in testprogram.cpp):" << endl;
		cout << "\t//CXCOMPILE clang++ -o output testprogram.cpp" << endl;
		cout << "\t// CXPRINTCOM TRUE" << endl;
		cout << "\t//CXGENRUN FALSE" << endl;
		
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
		cout << "ERROR: Failed to open file '" << argv[1] << "'" << endl;
		return -1;
	}
	
	//-------------------- GENERATE COMPILER COMMANDS ------------------
	//
	
	vector<string> compiler_commands;
	bool print_commands = false; //Print commands before running them
	bool verify_commands = false; //Verify commands with user before running them
	bool generate_run_command = true; //CX must generate its own command to run the executable
	bool persist_on_error = false; //If true, CX will continue executing commands even if one returns and error
	
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
				cout << "DIRECTIVE SKIPPED: No boolean argument provided after call to 'CXPRINTCOM' on line " << line_number << "." << endl;
			}else if(line.substr(14) == "TRUE"){
				print_commands = true;
			}else if(line.substr(14) == "FALSE"){
				print_commands = false;
			}else{
				cout << "DIRECTIVE SKIPPED: Invalid argument provided after call to 'CXPRINTCOM' on line " << line_number << "." << endl;
			}
			continue;
		}else if (line.substr(0, 12) == "//CXPRINTCOM"){
			if (line.length() < 17){
				cout << "DIRECTIVE SKIPPED: No boolean argument provided after call to 'CXPRINTCOM' on line " << line_number << "." << endl;
			}else if(line.substr(13) == "TRUE"){
				print_commands = true;
			}else if(line.substr(13) == "FALSE"){
				print_commands = false;
			}else{
				cout << "DIRECTIVE SKIPPED: Invalid argument provided after call to 'CXPRINTCOM' on line " << line_number << "." << endl;
			}
			continue;
		}
		
		//Look for 'verify commands' commands
		if (line.substr(0, 11) == "// CXVERCOM"){
			if (line.length() < 16){
				cout << "DIRECTIVE SKIPPED: No boolean argument provided after call to 'CXVERCOM' on line " << line_number << "." << endl;
			}else if(line.substr(12) == "TRUE"){
				verify_commands = true;
			}else if(line.substr(12) == "FALSE"){
				verify_commands = false;
			}else{
				cout << "DIRECTIVE SKIPPED: Invalid argument provided after call to 'CXVERCOM' on line " << line_number << "." << endl;
			}
			continue;
		}else if (line.substr(0, 10) == "//CXVERCOM"){
			if (line.length() < 15){
				cout << "DIRECTIVE SKIPPED: No boolean argument provided after call to 'CXVERCOM' on line " << line_number << "." << endl;
			}else if(line.substr(11) == "TRUE"){
				verify_commands = true;
			}else if(line.substr(11) == "FALSE"){
				verify_commands = false;
			}else{
				cout << "DIRECTIVE SKIPPED: Invalid argument provided after call to 'CXVERCOM' on line " << line_number << "." << endl;
			}
			continue;
		}
		
		//Look for 'verify commands' commands
		if (line.substr(0, 11) == "// CXGENRUN"){
			if (line.length() < 16){
				cout << "DIRECTIVE SKIPPED: No boolean argument provided after call to 'CXGENRUN' on line " << line_number << "." << endl;
			}else if(line.substr(12) == "TRUE"){
				generate_run_command = true;
			}else if(line.substr(12) == "FALSE"){
				generate_run_command = false;
			}else{
				cout << "DIRECTIVE SKIPPED: Invalid argument provided after call to 'CXGENRUN' on line " << line_number << "." << endl;
			}
			continue;
		}else if (line.substr(0, 10) == "//CXGENRUN"){
			if (line.length() < 15){
				cout << "DIRECTIVE SKIPPED: No boolean argument provided after call to 'CXGENRUN' on line " << line_number << "." << endl;
			}else if(line.substr(11) == "TRUE"){
				generate_run_command = true;
			}else if(line.substr(11) == "FALSE"){
				generate_run_command = false;
			}else{
				cout << "DIRECTIVE SKIPPED: Invalid argument provided after call to 'CXGENRUN' on line " << line_number << "." << endl;
			}
			continue;
		}
		
		//Look for 'print commands' commands
		if (line.substr(0, 12) == "// CXPERSIST"){
			if (line.length() < 17){
				cout << "DIRECTIVE SKIPPED: No boolean argument provided after call to 'CXPERSIST' on line " << line_number << "." << endl;
			}else if(line.substr(13) == "TRUE"){
				persist_on_error = true;
			}else if(line.substr(13) == "FALSE"){
				persist_on_error = false;
			}else{
				cout << "DIRECTIVE SKIPPED: Invalid argument provided after call to 'CXPERSIST' on line " << line_number << "." << endl;
			}
			continue;
		}else if (line.substr(0, 11) == "//CXPERSIST"){
			if (line.length() < 16){
				cout << "DIRECTIVE SKIPPED: No boolean argument provided after call to 'CXPERSIST' on line " << line_number << "." << endl;
			}else if(line.substr(12) == "TRUE"){
				persist_on_error = true;
			}else if(line.substr(12) == "FALSE"){
				persist_on_error = false;
			}else{
				cout << "DIRECTIVE SKIPPED: Invalid argument provided after call to 'CXPERSIST' on line " << line_number << "." << endl;
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
		cout << "Will run: " << endl;
		for (int i = 0 ; i < compiler_commands.size() ; i++){
			cout << "\t[" << i+1 << ".] '" << compiler_commands[i] << "'" << endl;
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
		int error_code = system(compiler_commands[i].c_str());
		if (error_code != 0){
			cout << "\nERROR ENCOUNTERED: The previous CX command triggered and error." << endl;
			cout << "\tcommand: '" << compiler_commands[i] << "', error code: " << error_code << endl;
			if (!persist_on_error){
				cout << "CX ABORT" << endl;
				return -1;
			}
		}
	}
	
	return 0;
}
