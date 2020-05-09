//
//  Row.hpp
//  Database3
//
//  Created by rick gessner on 3/22/19.
//  Copyright © 2019 rick gessner. All rights reserved.
//

#ifndef Row_h
#define Row_h

#include <stdio.h>
#include <vector>
#include "Value.hpp"

namespace ECE141 {
  
  class Block;
  
  class Row {
  public:
    Row(int32_t aBlockNumber=0);
    Row(const Row &aRow);
    Row(const Block &aBlock); //decode from raw storage...
    Row(KeyValues &aKeyValueList); //build a row
    ~Row();
    
    int32_t             getBlockNumber() {return blockNumber;}
    const KeyValues&    getColumns() const {return columns;}
    
    bool                operator==(const Row &aCopy);
    
    friend class  RowCollection;
    
  protected:
    int32_t       blockNumber;
    std::map<std::string, Value> columns;
  };
  
  //-------------------------------------------
  
  using RowList = std::vector<Row*>;
  
  class RowCollection {
  public:
    RowCollection();
    RowCollection(const RowCollection &aCopy);
    ~RowCollection();
    
    RowList&          getRows() {return rows;}
    RowCollection&    add(Row* aRow);
    
  protected:
    RowList rows;
  };
  
}
#endif /* Row_h */
