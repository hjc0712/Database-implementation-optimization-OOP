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
			case ECE141::keywordExpected: 
			default: std::cout << "Unknown error"; break;
		}
		std::cout << std::endl;
	}

	//executes the commands based off of the vector of tokens made---------------
	StatusResult CommandProcessor::interpret(const Statement &aStatement) {
		switch(aStatement.getType()) {
			case Keywords::version_kw:
				std::cout << "Team11 Database Version: 0.2.14" << std::endl;
				break;
			case Keywords::help_kw:
				std::cout << "\nThe left column describes what needs to be" 
						  << " typed in to the command line.\n";
				std::cout << "Where ever a series of \"...\" this is where"
						  << " your information should be \n";
				std::cout << "inserted without the quotations or periods. This"
						  << " information may be a \n";
				std::cout << "name of a table, database, or actual data.\n";
				std::cout << "The right column is the description of what the"
						  << " command will do.\n";
				std::cout << "|-Commands-|    |-Description-|\n";
				std::cout << "_______________________________________________"
						  << "_________________________\n";
				std::cout << " version         This shows what version of our"
						  << " Database you are using.\n";
				std::cout << " help            This does what you are looking"
						  << " at right now dummy.\n";
				std::cout << " quit            The program will find its"
						  << " bugout bag and skip town.\n";
				break;
			case Keywords::quit_kw:
				std::cout << "Goodbye My Dear..." << std::endl;
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
