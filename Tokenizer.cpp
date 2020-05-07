//
//  Tokenizer.cpp
//  Database1
//
//  Created by rick gessner on 3/19/19.
//  Copyright © 2019 rick gessner. All rights reserved.
//

#include "Tokenizer.hpp"
#include <exception>
#include <cstring>
#include "stdio.h"
#include "ctype.h"
#include <vector>
#include <string>
#include <algorithm>

namespace ECE141 {
  
Tokenizer::Tokenizer(std::istream &anInput) : input(anInput), index(0)  {}

	//convert input given in constructor to collection of tokens---------------
	StatusResult Tokenizer::tokenize() {
		StatusResult theResult;

		std::ostringstream ossInput;
		ossInput << input.rdbuf();  
		std::string stringInput = ossInput.str();
		char *charInput = new char[stringInput.length() + 1];
		strcpy(charInput, stringInput.c_str());
		const char* theDelimiter = " ";
		std::vector<std::string> tokenVector;

		//splits string by spaces----------------------------------------------
		char* charToken = strtok(charInput,theDelimiter);
		while(charToken != NULL) {
			//to lowercase
			int i=0;
			while(charToken[i]) {
				if (charToken[i]>='A' && charToken[i]<='Z') {
					charToken[i]=charToken[i] - ('A'-'a');
				}
				i++;
			}

			tokenVector.push_back(std::string(charToken));
			charToken = strtok(NULL, theDelimiter);
		}

		//splits spaced words by symbols---------------------------------------
		std::vector<std::string> finalToken;
		std::vector<std::string> sTable = {"(",")",",",";",":","[","]",
										   "{","}","=","<",">","!"};
		for(int i=0; i<tokenVector.size(); i++){
			std::string cur = tokenVector[i];
			int head=0;
			for(int j=0; j<cur.size(); j++) {
				std::vector<std::string>::iterator it;
				it = std::find(sTable.begin(), sTable.end(),
					 std::string(1,cur[j]));
				if (it!= sTable.end()) {
					std::string former = cur.substr(head,j-head);
					if(former.length()>0){
						finalToken.push_back(former);
					}
					//distingush between ">" and ">="--------------------------
					if (*it!="<" && *it!=">" && *it!="!")
						finalToken.push_back(*it);
					else{
					  	if (std::string(1,cur[j+1])=="=") {
							std::string aa=*it+"=";
					      	j++;
					      	finalToken.push_back(aa);
					  	}
					  	else
					      	finalToken.push_back(*it);
					}
					head=j+1;
				}
				else if(j==cur.size()-1){
				finalToken.push_back( cur.substr(head,j-head+1));
				}
			}
		}
		//finds what needs to be placed in the token---------------------------
		for(auto i:finalToken){
			Token cur;
			std::map<std::string, TokenType>::iterator itt;
			std::map<std::string, Keywords>::iterator itk;
			itt = tokeDictionary.find(i);
			itk = kDictionary.find(i);
			if (itk != kDictionary.end()) {
				cur.keyword = itk->second;
				cur.data = i;
				if (itk->second > Keywords::where_kw 
					&& itk->second < Keywords::avg_f)
					cur.type = TokenType::operators;
				else if (itk->second > Keywords::or_op 
					&& itk->second < Keywords::column_i)
					cur.type = TokenType::function;
				else if (itk->second > Keywords::max_f)
					cur.type = TokenType::identifier;
				else cur.type = TokenType::keyword;
			}
			else if (itt != tokeDictionary.end()) {
				cur.keyword = Keywords::unknown;
				cur.data = i;
				cur.type = itt->second;
			}
			else {
				cur.keyword = Keywords::unknown;
				cur.data.empty();
				cur.type = TokenType::unknown;
			}
			tokens.push_back(cur);
		}
		return theResult;
	}

	Token& Tokenizer::tokenAt(int anOffset) {
		if(anOffset<size()) return tokens[anOffset];
		throw std::range_error("bad offset");
	}

	bool Tokenizer::next(int anOffset) {
		if(index+anOffset<=size()) {
			index+=anOffset;
			return true;
		}
		return false;
	}

	Token& Tokenizer::current() {
		return tokens[index];
	}

	Token& Tokenizer::peek(int anOffset) {
		return tokenAt(index+anOffset);
	}

}
