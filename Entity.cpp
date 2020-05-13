//
//  Schema.cpp
//  ECEDatabase
//
//  Created by rick gessner on 4/19/18.
//  Copyright © 2018 rick gessner. All rights reserved.
//

#include "Entity.hpp"
#include "Storage.hpp"
#include "Row.hpp"
#include "Tokenizer.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <streambuf>
#include <algorithm>
#include <sys/stat.h>
#include "Helpers.hpp"
#include "MemoryStream.hpp"
#include "View.hpp"
#include "Filters.hpp"

const int gMultiplier = 37;

namespace ECE141 {

	//utility...

	uint32_t Entity::hashString(const char *str) {
		uint32_t h{0};
		unsigned char *p;
		for (p = (unsigned char*)str; *p != '\0'; p++)
			h = gMultiplier * h + *p;
		return h;
	}

	//----------------------------------------------------

	Entity::Entity(std::string aName)
	: name(aName), attributes(), dirty(false), count(0), blockNum(0), autoincr(0) {
		hash = hashString(aName.c_str());
	}

	Entity::Entity(const Entity &aCopy) :
	name(aCopy.name), attributes(aCopy.attributes), dirty(aCopy.dirty), autoincr(aCopy.autoincr),
	count(aCopy.count), blockNum(aCopy.blockNum), hash(aCopy.hash)  {
	}

	Entity::Entity(Block &aBlock, uint32_t aBlockNum) {
		//STUDENT: construct an entity (decode) from the given block...
        BufferReader theReader(aBlock.data, sizeof(aBlock.data), aBlockNum * sizeof(aBlock.data));
        while(1){
            Attribute theAttr;
            theReader >> theAttr;
            if(theAttr.getName().size()==0)
                break;
            attributes.push_back(theAttr);
        }
        hash = aBlock.header.extra;
	}

	Entity::Entity() {}

	// USE: ask the entity for name of primary key (may not have one...)
	std::string Entity::getPrimaryKey() {
		return std::string("id"); //XXX-HACK wrong
	}

	// USE: ask entity for next auto-incr value  (for a new record)....
	uint32_t Entity::getNextAutoIncrementValue() {
		dirty=true; //so we resave when DB is released...
		return ++autoincr;
	}

	void Entity::each(attribute_callback aCallback) const {
		for(auto theAttr : attributes) {
			aCallback(theAttr);
		}
	}


	Entity& Entity::markDirty(bool aState) {
		dirty=aState;
		return *this;
	}

	Entity& Entity::addAttribute(std::string aName, DataType aType, uint8_t aSize, bool autoIncr) {
		attributes.push_back(Attribute(aName, aType, aSize));
		return *this;
	}

	Entity& Entity::addAttribute(const Attribute &anAttribute) {
		attributes.push_back(anAttribute);
		return *this;
	}

	Attribute& Entity::getAttribute(const std::string &aName)  {
		for(auto theIter = attributes.begin(); theIter != attributes.end(); theIter++) {
			if(theIter->getName()==aName) {
				return *theIter;
			}
		}
		throw std::runtime_error("Attribute not found");
	}

	Value Entity::getDefaultValue(const Attribute &anAttribute) {
		Value theResult;
		return theResult;
	}

	//Encode (pack) this entity into a storage block...
	Entity::operator Block() {
		Block theBlock(kEntityBlockType);
		BufferWriter theWriter(theBlock.data, sizeof theBlock.data);
		//STUDENT: Decode your entity into a block, and return it...
		for(int i = 0; i < attributes.size(); i++) {
			Attribute currAtt = attributes[i];
			//Didn't realize how easy it is to use the BufferWriter.
			theWriter << currAtt;
		}
//        std::cout << theWriter.getBuffer() << std::endl;
		return theBlock;
	}

	//** USE:
	StatusResult Entity::validate(KeyValues &aList) {
		for (auto theKV : aList) {
			/*
			if(!hasCompatibleAttribute(theKV.first, theKV.second)) {
			return StatusResult{invalidAttribute};
			}
			*/
		}
		return StatusResult{noError};
	}

	// USE: write given row into given block (using entity as guide...)
	StatusResult Entity::encodeData(KeyValues &aDataList, Block &aBlock) {
		StatusResult theResult{noError};
		aBlock = aDataList;
		// STUDENT: Encode your entity data into the given block...

		return theResult;
	}

	bool inGivenFields(const std::string &aFieldName, const StringList &aFields) {
		auto theEnd = aFields.end();
		return std::find(aFields.begin(), theEnd, aFieldName) != theEnd;
	}

	// USE: read data from block into given keyvalue list (for row?)...
	StatusResult Entity::decodeData(const Block &aBlock, KeyValues &aValuesList,
						const StringList *aFields) const {
		StatusResult theResult{noError};
		Block &ablk = const_cast<Block&> (aBlock);
		BufferReader theReader(ablk.data, kPayloadSize, kPayloadSize);
		uint8_t size;
		theReader >> size;
        while(1){
			std::string astr;
            theReader >> astr;
			Value aval;
			theReader >> aval;
            if(astr.empty())
                break;
			aValuesList.insert(std::pair<std::string, Value>(astr, aval));
        }
		// STUDENT: Decode your entity from the given block...
		return theResult;
	}


}
