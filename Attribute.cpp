//
//  Attribute.cpp
//  Datatabase4
//
//  Created by rick gessner on 4/12/19.
//  Copyright © 2019 rick gessner. All rights reserved.
//

#include "Attribute.hpp"
#include "Storage.hpp"
#include "MemoryStream.hpp"

namespace ECE141 {
    
  Attribute::Attribute(std::string aName, DataType aType, uint8_t aSize, bool autoIncr, bool aPrimary) :
  name(aName), type(aType), size(aSize) {
    autoIncrement=autoIncr;
    primary=aPrimary;
    nullable=true;
  }
  
  Attribute::Attribute(DataType aType) : type(aType) {
    autoIncrement=primary=false;
    nullable=true;
  }
  
  Attribute::Attribute(const Attribute &aCopy) : name(aCopy.name), type(aCopy.type), size(aCopy.size) {
    autoIncrement=aCopy.autoIncrement;
    nullable=aCopy.nullable;
    primary=aCopy.primary;
  }
  
  Attribute::~Attribute() {
  }
  
  Attribute& Attribute::setName(std::string &aName) {name=aName; return *this;}
  Attribute& Attribute::setType(DataType aType) {type=aType; return *this;}
  Attribute& Attribute::setSize(int aSize) {size=aSize; return *this;}
  Attribute& Attribute::setAutoIncrement(bool anAuto) {autoIncrement=anAuto; return *this;}
  Attribute& Attribute::setPrimaryKey(bool aPrimary) {primary=aPrimary; return *this;}
  Attribute& Attribute::setNullable(bool aNullable) {nullable=aNullable; return *this;}
  
  bool Attribute::isValid() {
    return true;
  }
    
  bool Attribute::isCompatible(DataType aType) const {
    return false;
/*
    switch(aType) {
      case TokenType::number:
        return isNumericKeyword(type);
      case TokenType::identifier:
      case TokenType::string:
        return Keywords::varchar_kw==type;
      default: return false;
    }
*/
    return false;
  }
    
  //how big a given attribute...
  size_t Attribute::getSize() const {
    switch(type) {
      case DataType::timestamp_type:
      case DataType::int_type:
        return sizeof(int32_t);
      case DataType::float_type:
        return sizeof(float);
      case DataType::varchar_type:
        return size;
      default: break;
    }
    return 0;
  }
  
  std::string Attribute::describeTabular(std::string curType) {
    std::string theResult;
    char theBuffer[100];
    std::sprintf(theBuffer, "| %-17s |",name.c_str()); theResult+=theBuffer;
    
    std::sprintf(theBuffer," %-12s |", curType.c_str()); theResult+=theBuffer;
    
    static const char* Nu[]={"N","Y"};
    const char *temp = Nu[(nullable && (!primary))];
    std::sprintf(theBuffer," %-4s |", temp); theResult+=theBuffer; //nullable...
    
    static const char* keys[]={" ","PRI"};
    const char *temp2 = keys[primary];
    
    std::sprintf(theBuffer," %-4s |", temp2); theResult+=theBuffer; //key...
    std::sprintf(theBuffer," %-14s |", "   "); theResult+=theBuffer;
    
    static const char* extra[]={" ","auto"};
    const char *temp3 = extra[autoIncrement];
    std::sprintf(theBuffer," %-16s |", temp3); theResult+=theBuffer;
    
    return theResult;
  }
  
  // USE: read attribute properties from memory stream...
  BufferReader& operator >> (BufferReader& aReader, Attribute &aValue) {
    char theCharType;
    bool theIncr, thePrimary, theNull;
    uint8_t theSize;

    aReader >> aValue.name;
    aReader >> theCharType;
    aValue.type=static_cast<DataType>(theCharType);
    aReader >> theSize >> theIncr >> thePrimary >> theNull;
    aValue.size=theSize;
    aValue.autoIncrement=theIncr;
    aValue.primary=thePrimary;
    aValue.nullable=theNull;
    return aReader;
  }
  
  // USE: Write attribute properties into a memory stream...
  BufferWriter& operator << (BufferWriter& aWriter, const Attribute &aValue) {
    char theBuffer[17];
    std::sprintf(theBuffer, "%-17s",aValue.name.c_str());
      aWriter << theBuffer
      << static_cast<char>(aValue.type)
      << static_cast<uint8_t>(aValue.size)
      << static_cast<bool>(aValue.autoIncrement)
      << static_cast<bool>(aValue.primary)
      << static_cast<bool>(aValue.nullable);
    return aWriter;
  }
  
}
