//
//  Storage.cpp
//  ECEDatabase
//
//  Created by rick gessner on 4/1/18.
//  Copyright © 2018 rick gessner. All rights reserved.
//

#include <iostream>
#include "Storage.hpp"

namespace ECE141 {
  Block::Block(const KeyValues &theKVList) {
    construct(theKVList);
  }
  void Block::construct(const KeyValues &theKVList) {
    int offset = 0;
        this->header = BlockHeader('N', 0); //hpp l28

    for(std::map<std::string, Value>::const_iterator it = theKVList.begin();
      it != theKVList.end(); ++it) {  //use const_iterater instead
      // data type: 'I' 3 a g e [] [] [] [](4 bytes int data) 'V' 4 n a m e 12 [] [] ...(12 byte vachar data)
      size_t curSize = it->second.getSize();
      DataType curType = it->second.getType();
      switch (curType) {
        case DataType::varchar_type: {
                    this->data[offset] = 'V';
          offset++;
          //store the 'string' of keValues map
            int len = it->first.size();
                        data[offset] = (unsigned char)(len & 0xFF);;
            offset++;
            unsigned char *strChar = new unsigned char[len];
            std::strcpy((char *)strChar, it->first.c_str());
            for(int i = 0; i < len; i++)
              data[offset + i] = strChar[i];
            offset += len;
          //store the data
          data[offset]= curSize & 0xff; //store the length of data
          offset++;
          std::string curStr = it->second;
          unsigned char *curChar = new unsigned char[curSize];
          std::strcpy((char *)curChar, curStr.c_str());
          for(int i = 0; i < curSize; i++)
            data[offset+i] = curChar[i];
          offset += curSize;
          delete []curChar;
          break;
        }

        case DataType::int_type: {
          //store datatype
          Block::data[offset] = 'I';
          offset++;
            //store the 'string' of keValues map
            int len = it->first.size();
                        data[offset] = (unsigned char)(len & 0xFF);;
            offset++;
            unsigned char *strChar = new unsigned char[len];
            std::strcpy((char *)strChar, it->first.c_str());
            for(int i = 0; i < len; i++)
              data[offset + i] = strChar[i];
            offset += len;
          //transform int into 4 bytes unsigned char
          int n = it->second;
          unsigned char bytes[4];
          bytes[0] = (unsigned char)((n >> 24) & 0xFF);
          bytes[1] = (unsigned char)((n >> 16) & 0xFF);
          bytes[2] = (unsigned char)((n >> 8) & 0xFF);
          bytes[3] = (unsigned char)(n & 0xFF);
                    for(int i = 0; i < 4; i++)
                        data[offset + i] = bytes[i];
          offset += 4;
          break;
        }

        case DataType::float_type: {
          Block::data[offset]='F';
          offset++;
            //store the 'string' of keValues map
            int len = it->first.size();
                        data[offset] = (unsigned char)(len & 0xFF);;
            offset++;
            unsigned char *strChar = new unsigned char[len];
            std::strcpy((char *)strChar, it->first.c_str());
            for(int i = 0; i < len; i++)
              data[offset + i] = strChar[i];
            offset += len;
          //transform int into 4 bytes binary data
          float curFlo = it->second;
          unsigned char b[sizeof(float)];
          memcpy(b, &curFlo, sizeof(curFlo));
          for(int i = 0; i < sizeof(curFlo); i++)
                        data[offset + i] = b[i];
          offset += sizeof(curFlo);
          break;
        }

        case DataType::bool_type:{
          Block::data[offset]='B';
          offset++;
            int len = it->first.size();
                        data[offset] = (unsigned char)(len & 0xFF);;
            offset++;
            unsigned char *strChar = new unsigned char[len];
            std::strcpy((char *)strChar, it->first.c_str());
            for(int i = 0; i < len; i++)
              data[offset + i] = strChar[i];
            offset += len;
          bool curbool = it->second;
          data[offset]=(curbool)?'1':'0';
          offset++;
          break;
        }

        case DataType::timestamp_type: {
          Block::data[offset]='T';
          offset++;
            //store the 'string' of keValues map
            int len = it->first.size();
                        data[offset] = (unsigned char)(len & 0xFF);;
            offset++;
            unsigned char *strChar = new unsigned char[len];
            std::strcpy((char *)strChar, it->first.c_str());
            for(int i = 0; i < len; i++)
              data[offset + i] = strChar[i];
            offset += len;
          //convert uint to uchar
          unsigned int n = it->second;
          unsigned char bytes[4];
          bytes[0] = (unsigned char)((n >> 24) & 0xFF);
          bytes[1] = (unsigned char)((n >> 16) & 0xFF);
          bytes[2] = (unsigned char)((n >> 8) & 0xFF);
          bytes[3] = (unsigned char)(n & 0xFF);
                    for(int i = 0; i < 4; i++)
                        data[offset + i] = bytes[i];
          offset += 4;
          break;
        }

        case DataType::no_type: {

        }
      }
    }
  }
  Block::Block(const Row& theRow) {
    Row aRow = theRow;
    KeyValues &theColumns = aRow.getColumns();
    construct(theColumns);
  }

  //path to the folder where you want to store your DB's...
  const char* Storage::getDefaultStoragePath() {
    return "/tmp";
  }

  // USE: ctor ---------------------------------------
  Storage::Storage(const std::string aName) : toc('T',0), name(aName) {
    char thePath[128];
    sprintf(thePath,"%s/%s.%s", getDefaultStoragePath(), aName.c_str(),"db");
    stream.open (thePath, std::fstream::binary | std::fstream::in | std::fstream::out);

    toc.header.count=0; //init for new db...
    memset(toc.data,0,sizeof(toc.data));
  }

  // USE: dtor ---------------------------------------
  Storage::~Storage() {
    toc.header.dirty=false;
    writeBlock(0,toc);
    stream.close();
  }

  // USE: retrieve toc (block=0) from storage -------------------------------
  StatusResult Storage::loadTOC() {
    stream.seekg(stream.tellg(), std::ios::beg); //C++ trick to sync stream buffers...
    return Storage::readBlock(0, toc);
  }

  // USE: create a new storage file -----------------------------------------
  StatusResult Storage::makeEmpty() {
    char thePath[128];
    sprintf(thePath,"%s/%s.%s", getDefaultStoragePath(), name.c_str(),"db");
    stream.clear(); // Clear Flag, then create file...
    stream.open(thePath, std::fstream::in | std::fstream::out | std::fstream::trunc);
    stream.close();
    stream.open(thePath, std::fstream::binary | std::fstream::in | std::fstream::out);
    return addBlock(toc);
  }

  // USE: validate we're open and ready -------------------------------------
  bool Storage::isReady() {
    return stream.is_open();
  }

  // USE: count blocks in file ----------------------------------------------
  uint32_t Storage::getTotalBlockCount() {
    stream.seekg(stream.tellg(), std::ios::beg); //force read mode; dumb c++ issue...
    stream.seekg(0, std::ios::end);
    int thePos = (int)stream.tellg();
    return thePos / kBlockSize;
  }

  // USE: scan free blocks. if not found, add a new block -------------------
  uint32_t Storage::findFreeBlockId() {
    if(toc.header.id) {
      //we have a free block...
    }
    return 0;
  }

  // USE: read data a given block # -----------------------------------------
  StatusResult Storage::readBlock(int aBlockNumber, Block &aBlock, std::size_t aBlockSize) {
    stream.seekg(aBlockNumber * kBlockSize);
    if(stream.read ((char*)&aBlock, aBlockSize)) {
      return StatusResult{};
    }
    return StatusResult(ECE141::readError);
  }

  // USE: low-level write data to given block (assumes seekp is set) --------
  StatusResult write(Block &aBlock, std::fstream &aStream) {
    if(aStream.write ((char*)&aBlock, kBlockSize)) {
      aStream.flush();
      return StatusResult{};
    }
    return StatusResult{ECE141::writeError};
  }

  // USE: write data a given block (after seek) -----------------------------
  StatusResult Storage::writeBlock(int aBlockNumber, Block &aBlock) {
    stream.seekg(stream.tellg(), std::ios::beg); //attemp to sync stream buffers...
    stream.seekp(aBlockNumber * kBlockSize);
    return write(aBlock, stream);
  }

  // USE: save block (in free block, or appended bloc -----------------------
  StatusResult Storage::addBlock(Block &aBlock) {
    if(int theBlockNum = findFreeBlockId()) {
      return writeBlock(theBlockNum, aBlock);
    }

    stream.seekg(stream.tellg(), std::ios::beg); //attemp to sync stream buffers...
    stream.seekp(0, std::ios::end); //append...

    toc.header.dirty=true; //TEST ONLY

    return write(aBlock, stream);
  }

  // USE: mark block as free ------------------------------------------------
  StatusResult Storage::releaseBlock(int aBlockNumber) {
    return StatusResult{ECE141::notImplemented};
  }

  // USE: add schema to TOC, and store properties in block ------------------
  StatusResult Storage::addSchema(const std::string &aName, Block &aBlock) {
    return StatusResult{ECE141::storageFull};
  }

  // USE: remove schema from TOC and mark schema-block free -----------------
  StatusResult Storage::dropSchema(const std::string &aName) {
    return StatusResult{ECE141::noError};
  }
  
}
