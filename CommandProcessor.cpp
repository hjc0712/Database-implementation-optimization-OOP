//
//  CommandProcessor.cpp
//  ECEDatabase
//
//  Created by rick gessner on 3/30/18.
//  Copyright © 2018 rick gessner. All rights reserved.
//

#include <iostream>
#include "CommandProcessor.hpp"
#include "Tokenizer.hpp"
#include "Statement.hpp"

namespace ECE141 {

	CommandProcessor::CommandProcessor() {}

	CommandProcessor::~CommandProcessor() {}


	// USE: ---------------------------------------------
	void showError(StatusResult &aResult) {
		switch(aResult.code) {
			case ECE141::unknownCommand: std::cout << "Unknown command: "; break;
			case ECE141::userTerminated: break; //ignore this...
			default: std::cout << "Unknown error"; break;
		}
		std::cout << std::endl;
	}

	//executes the commands based off of the vector of tokens made---------------
	StatusResult CommandProcessor::interpret(const Statement &aStatement) {
		switch(aStatement.getType()) {
			case Keywords::version_kw:
				std::cout << "T12 Database Version: 0.1" << std::endl;
				break;
			case Keywords::help_kw:
				std::cout << "The left column describes what needs to be typed"
						  << " in to the command line." 	<< std::endl;
				std::cout << "Where ever a series of \"...\" this is where"
						  << " your information should be " << std::endl;
				std::cout << "inserted without the quotations or periods. This"
						  << " information may be a "		<< std::endl;
				std::cout << "name of a table, database, or actual data." 
															<< std::endl;
				std::cout << "The right column is the description of what the"
						  << " command will do.\n"			<< std::endl;
				std::cout << "--Commands--    --Description--"
															<< std::endl;
				std::cout << "_______________________________________________"
						  << "_________________________"	<< std::endl;
				std::cout << " version         This shows what version of our"
						  << " Database you are using." 	<< std::endl;
				std::cout << " help            This does what you are looking"
						  << " at right now dummy."			<< std::endl;
				std::cout << " quit            The program will find it's"
						  << " bugout bag and skip town."   << std::endl;
				break;
			case Keywords::quit_kw:
				std::cout << "Program terminating..." << std::endl;
				return StatusResult(Errors::userTerminated,
									Errors::userTerminated);
			default:
				break;
		}
		return StatusResult();
	}

	//retrieve a statement based on given text input---------------------------
	Statement* CommandProcessor::getStatement(Tokenizer &aTokenizer) {    
		if (aTokenizer.size()) {
			Token& theToken = aTokenizer.current();
			if (theToken.type == TokenType::keyword) {
				aTokenizer.next();
				return new Statement(aTokenizer, theToken.keyword);
			}
		}
		return nullptr;
	}

	//sends input to different functions for processing------------------------
	StatusResult CommandProcessor::processInput(Tokenizer &aTokenizer,
												IInterpreter *another) {
		StatusResult theResult;
	
		while(theResult && aTokenizer.more()) {
			if (Statement *theStatement=getStatement(aTokenizer)) {
				theResult=interpret(*theStatement);
			}
			else if(another) {
				if(Statement *theStatement=another->getStatement(aTokenizer)) {
					theResult=another->interpret(*theStatement);
				}
			}
			else return StatusResult{ECE141::unknownCommand};
	
			if(!theResult) showError(theResult);
		}
		return theResult;
	}
}
