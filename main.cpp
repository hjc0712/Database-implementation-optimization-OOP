//
//  main.cpp
//  Database1
//
//  Created by rick gessner on 3/17/19.
//  Copyright © 2019 rick gessner. All rights reserved.
//

#include "CommandProcessor.hpp"
#include "DBManager.hpp"
#include "SQLInterpreter.hpp"
#include "RGTokenizer.hpp"
#include "Tokenizer.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdio>
#include <ctime>
#include <functional>
#include <iomanip>
#include "Entity.hpp"
#include "Errors.hpp"
#include "Storage.hpp"

// USE: ---------------------------------------------
void showError(ECE141::StatusResult &aResult) {
	switch(aResult.code) {
		case ECE141::unknownCommand: std::cout << "Unknown command "; break;
		case ECE141::unknownDatabase: std::cout << "Unknown database "; break;
		case ECE141::unknownTable: std::cout << "Unknown table "; break;
		case ECE141::tableExists: std::cout << "Table exists "; break;
		case ECE141::invalidArguments: std::cout << "Invalid Arguments "; break;
		case ECE141::userTerminated: break; //ignore this...
		default: std::cout << "Unknown error"; break;
	}
	std::cout << std::endl;
}

//build a tokenizer, tokenize input, ask processors to handle...
ECE141::StatusResult handleInput(std::istream &aStream, ECE141::IInterpreter &aProcessor) {
	ECE141::RGTokenizer theTokenizer(aStream); //USE RGTokenizer if you prefer...
	// ECE141::Tokenizer theTokenizer(aStream); // USE Your tokenizer if you prefer...
	ECE141::StatusResult theResult=theTokenizer.tokenize();
	while(theResult && theTokenizer.more()) {
		if(";"==theTokenizer.current().data) {
		theTokenizer.next();  //skip the ";"...
		}
		else theResult=aProcessor.processInput(theTokenizer);
	}
	return theResult;
}

int main(int argc, const char * argv[]) {

	ECE141::DBManager         theManager;
	ECE141::SQLInterpreter    theSQLInterpreter(&theManager);
	ECE141::CommandProcessor  theProcessor(&theSQLInterpreter);
	ECE141::StatusResult      theResult{};

	if(argc>1) {
		 std::clock_t start;
    	double duration;

    	start = std::clock();

		std::ifstream theStream(argv[1]);
		ECE141::StatusResult theResult = handleInput(theStream, theProcessor);
		
		duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
		std::cout<<"Perfomance: "<< duration <<'\n';	
		return theResult;
	}
	else {
		std::string theUserInput;
		bool running=true;
		do {
			std::cout << std::endl << "> ";
			if(std::getline(std::cin, theUserInput)) {
				if(theUserInput.length()) {
					std::stringstream theStream(theUserInput);
					theResult=handleInput(theStream, theProcessor);
					if(!theResult) showError(theResult);
				}
				if(ECE141::userTerminated==theResult.code)
				running=false;
			}
		}
		while (running);
	}
	return 0;
}

