//
//  Row.cpp
//  ECEDatabase
//
//  Created by rick gessner on 4/29/18.
//  Copyright © 2018 rick gessner. All rights reserved.
//

#include "Row.hpp"
#include "Storage.hpp"

namespace ECE141 {

	Row::Row(int32_t aBlockNumber) : blockNumber(aBlockNumber), columns() {
	}

	Row::Row(const Row &aCopy) : blockNumber(aCopy.blockNumber), columns(aCopy.columns) {
	}

	Row::Row(const Block &aBlock) {
		std::cout << "There is stuff here"<<std::endl;
		// //STUDENT: Implmenent this method...
		// Row::blockNumber = aBlock.header.id;

		// int offset=0;
		// int round=0;
		// //      for(int i=0;i<1000;i++){
		// //          std::cout<<aBlock.data[i];
		// //      }
		// // std::cout<<aBlock.data<<'\n';
		// while(round<20) {//aBlock.data[offset]!=NULL){
		// 	round++;
		// 	char curChar = aBlock.data[offset];
			
		// 	// std::cout << "Current Type:\t" << curChar <<'\t';
		// 	offset++;
		// 	switch (curChar) {
		// 		case 'V':{
		// 			// decode the 'string'
		// 				int slen = (int) (aBlock.data[offset] & 0xff);
		// 				offset++;
		// 				std::string curStr;
		// 				for(int i = 0; i < slen; i++)
		// 					curStr += aBlock.data[offset + i];
		// 				offset += slen;
		// 			//decode the data in vachar
		// 			int vlen = aBlock.data[offset] & 0xff;
		// 			offset++;
		// 			char *tmpVar = new char[vlen];
		// 			for(int i = 0; i < vlen; i++)
		// 				tmpVar[i] = aBlock.data[offset+i];
		// 			std::string resStr(tmpVar);
		// 			// std::cout << curStr << ": \t" << resStr << '\n';
		// 			this->columns[curStr] = resStr;
		// 			offset+=vlen;
		// 			delete []tmpVar;
		// 			break;
		// 		}
		// 		case 'I':{
		// 			// decode the 'string'
		// 				int slen = (int) (aBlock.data[offset] & 0xff);
		// 				offset++;
		// 				std::string curStr;
		// 				for(int i = 0; i < slen; i++)
		// 					curStr += aBlock.data[offset + i];
		// 				offset += slen;
		// 			//decode the int data
		// 			unsigned char b[4];
		// 			for(int i = 0; i < 4; i++)
		// 				b[i] = aBlock.data[offset + i];
		// 			int curInt = b[0] << 24 | (b[1] & 0xff) << 16 | (b[2] & 0xff) << 8 | (b[3] & 0xff);
		// 			// std::cout << curStr << ": \t" << curInt << '\n';
		// 			this->columns[curStr] = curInt;
		// 			offset+=4;
		// 			break;
		// 		}
		// 		case 'F':{
		// 			// decode the 'string'
		// 				int slen = (int) (aBlock.data[offset] & 0xff);
		// 				offset++;
		// 				std::string curStr;
		// 				for(int i = 0; i < slen; i++)
		// 					curStr += aBlock.data[offset + i];
		// 				offset += slen;
		// 			//decode the int data
		// 			float curFlo;
		// 			unsigned char b[sizeof(float)];
		// 			for(int i = 0; i < sizeof(float); i++)
		// 				b[i] = aBlock.data[offset + i];
		// 			memcpy(&curFlo, b, sizeof(float));
		// 			// std::cout << curStr << ": \t" << curFlo << std::endl;
		// 			this->columns[curStr] = curFlo;
		// 			offset+=sizeof(float);
		// 			break;
		// 		}
		// 		case 'B':{
		// 			// decode the 'string'
		// 				int slen = (int) (aBlock.data[offset] & 0xff);
		// 				offset++;
		// 				std::string curStr;
		// 				for(int i = 0; i < slen; i++)
		// 					curStr += aBlock.data[offset + i];
		// 				offset += slen;
		// 			//decode the int data
		// 			bool curBool;
		// 			if(aBlock.data[offset]=='1')
		// 			curBool=true;
		// 			else
		// 			curBool=false;
		// 			// std::cout << curStr << ": \t" << curBool << '\n';
		// 			this->columns[curStr] = curBool;
		// 			offset++;
		// 			break;
		// 		}
		// 		case 'T':{
		// 			// decode the 'string'
		// 				int slen = (int) (aBlock.data[offset] & 0xff);
		// 				offset++;
		// 				std::string curStr;
		// 				for(int i = 0; i < slen; i++)
		// 					curStr += aBlock.data[offset + i];
		// 				offset += slen;
		// 			//decode the int data
		// 			unsigned char b[4];
		// 			for(int i = 0; i < 4; i++)
		// 				b[i] = aBlock.data[offset + i];
		// 			unsigned int curUInt = b[0] << 24 | (b[1] & 0xff) << 16 | (b[2] & 0xff) << 8 | (b[3] & 0xff);
		// 			// std::cout << curStr << ": \t" << curUInt << '\n';
		// 			this->columns[curStr] = curUInt;
		// 			offset+=4;
		// 			break;
		// 		}
		// 		default:
		// 		break;
		// 	}
		// }


	}

    Row::Row(KeyValues &aKeyValueList) : blockNumber(0), columns(aKeyValueList) {
    }
    
	Row::~Row() {
		//STUDENT: implement this too
	}

	bool Row::operator==(const Row &aCopy) {
		if(columns == aCopy.columns)
			return true; //STUDENT: implement this too
		else
			return false;
	}
    
    Row&  Row::addColumn(const std::string &aString, const Value &aValue){
        columns.insert( std::pair<std::string, Value>(aString,aValue));
        return *this;
    }

	//---------------------------------------------------

	RowCollection::RowCollection() : rows() {}

	RowCollection::RowCollection(const RowCollection &aCopy) : rows(aCopy.rows) {}

	RowCollection::~RowCollection() {
		for(auto theRow : rows) {
			delete theRow;
		}
	}

	RowCollection& RowCollection::add(Row* aRow) {
		rows.push_back(aRow);
		return *this;
	}
}


