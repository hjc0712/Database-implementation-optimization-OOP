//
//  Row.cpp
//  Database3
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
    //STUDENT: Implement this method...
  }
  
  Row::Row(KeyValues &aKeyValueList) : blockNumber(0), columns(aKeyValueList) {    
  }

  Row::~Row() {
  }
  
  bool Row::operator==(const Row &aCopy) {
    return false; //STUDENT: implement this too
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


