//
//  BlockVisitor_h
//  Datatabase4
//
//  Created by rick gessner on 4/25/19.
//  Copyright © 2019 rick gessner. All rights reserved.
//

#ifndef BlockVisitor_h
#define BlockVisitor_h

#include "Storage.hpp"
#include "Entity.hpp"
#include "Filters.hpp"
#include "Row.hpp"

namespace ECE141 {
  
  class BlockVisitor {
  public:
    BlockVisitor(Entity &anEntity, const Filters &aFilters)
      : entity(anEntity), filters(aFilters) {}

    StatusResult operator()(Storage &aStorage, const Block &aBlock, uint32_t aBlockNum) {
      if('D'==aBlock.header.type) {
        if(0 == aBlock.header.extra) {
        }
      }
      return StatusResult{noError};
    }

    Entity      &entity;
    const Filters     &filters;
  };
    
    
    class RowCollector : public BlockVisitor{
      public:
        RowCollector(Entity &anEntity, const Filters &aFilters, RowCollection &aCollection, const StringList *aField)
            : BlockVisitor(anEntity, aFilters),  collection(aCollection), fields(aField){
            }
        
        StatusResult operator() (Storage &aStorage, const Block &aBlock, uint32_t aBlockNum){
            if('D'==aBlock.header.type) {
              //uint32_t hash = Entity::hashString(entity.getName().c_str());
                // std::cout << "Entity: " << entity.getHash() << "Block: " << aBlock.header.extra << "\n"; //=========================================================
                if(entity.getHash()== aBlock.header.extra) {
                    KeyValues curKeyValue;
                    // Row *aRow = new Row(aBlock);
                    // collection.add(aRow);
                    StatusResult theResult = entity.decodeData(aBlock, curKeyValue, fields);
                    // for(auto curKV : aRow->getColumns()) {
                    //   std::string str = curKV.second;
                    //   std::cout << "In: " << str << std::endl;
                    // }
                    if(theResult){
                        if(filters.getCount()==0 || filters.matches(curKeyValue)){
                            Row *curRow = new Row(aBlockNum);
                            for(auto curKV : curKeyValue) {
                                curRow->addColumn(curKV.first, curKV.second);
                            }
                            collection.add(curRow);
                        }
                        return theResult;
                    }
                    else
                  return StatusResult{noError};
                }
            }
            return StatusResult{noError};
        }
        
        
        RowCollection         &collection;
        const StringList*     fields;
        
        };
    
    
}




#endif /* BlockVisitor_h */
