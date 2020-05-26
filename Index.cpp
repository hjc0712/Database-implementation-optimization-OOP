//
//  index.cpp
//  ece141_pro8
//
//  Created by 洪吉宸 on 6/2/19.
//  Copyright © 2019 洪吉宸. All rights reserved.
//

#include "Index.hpp"

namespace ECE141 {
	//decode block to index
	Index::Index(Block &aBlock, uint32_t  aBlockNum) {
		//STUDENT: construct an index (decode) from the given block...
		BufferReader theReader(aBlock.data, kPayloadSize, kPayloadSize);
		std::string dt;
		theReader >> full;
		theReader >> field;
		theReader >> dt;
		
		if (dt == "I")      { keyType = DataType::int_type; }
		else if (dt == "F") { keyType=DataType::float_type; }
		else if (dt == "V") { keyType=DataType::varchar_type; }
		else if (dt == "B") { keyType=DataType::bool_type; }
		else if (dt == "T") { keyType=DataType::timestamp_type;}
		
		theReader >> tableId;
		
		for (int i = 0; i < size; i++) {
			Value aValue;
			uint32_t aInt = NULL;
			theReader >> aValue;
			if(aValue.getType() == DataType::no_type)
                break;
			theReader >> aInt;
			
			index[aValue] = aInt;
		}
		theReader >> nextBlockNum;
		blockNum = aBlockNum;
	}

	Index::Index(Index& previousIndex) {
		full = false;
		blockNum = previousIndex.nextBlockNum;
		field = previousIndex.field;
		keyType = previousIndex.keyType;
		tableId = previousIndex.tableId;
	}

	// encode index to block
	Index::operator Block() {
		Block theBlock(kIndexBlockType);
		//STUDENT: Decode your index into a block, and return it...
		std::string dt="N";
		switch (keyType) {
			case DataType::int_type: {dt="I"; break;}
			case DataType::float_type: {dt="F"; break;}
			case DataType::varchar_type: {dt="V"; break;}
			case DataType::bool_type: {dt="B"; break;}
			case DataType::timestamp_type: {dt="T";break;}
			default: break;
		}
		
		BufferWriter theWriter(theBlock.data, sizeof theBlock.data);
		theWriter << full << field << dt << tableId;
		for (auto thePair : index){
			theWriter << thePair.first << thePair.second;
		}
		if (index.size()==size) {
			theWriter << nextBlockNum;
		}
		//        std::cout << theWriter.getBuffer() << std::endl;
		return theBlock;
	}
	Index& Index::operator=(Index theIndex) {
		index = theIndex.index;
		field = theIndex.field;
		full = theIndex.full;
		keyType = theIndex.keyType;
		tableId = theIndex.tableId;
		blockNum = theIndex.blockNum;
		nextBlockNum = theIndex.nextBlockNum;
		return *this;
	}

	Index& Index::operator=(Index* theIndex) {
		index = theIndex->index;
		field = theIndex->field;
		full = theIndex->full;
		keyType = theIndex->keyType;
		tableId = theIndex->tableId;
		blockNum = theIndex->blockNum;
		nextBlockNum = theIndex->nextBlockNum;
		return *this;
	}

	Index& Index::addKeyValue(const Value &theKey, uint32_t theValue) {
		index[theKey] = theValue;
		if(index.size() == size) {
			full = true;
		}
		return *this;
	}
	
	Index&   Index::removeKeyValue(const Value &aKey){
        index.erase(aKey);
        return *this;
    }
}