//
//  RecordsView.hpp
//  Datatabase4
//
//  Created by rick gessner on 4/26/19.
//  Copyright © 2019 rick gessner. All rights reserved.
//

#ifndef RecordsView_h
#define RecordsView_h

#include <iostream>
#include <iomanip>
#include "View.hpp"
#include "Entity.hpp"
#include "Storage.hpp"

namespace ECE141 {

  // USE: This view is used to show a record set in tabular format...
  class RecordsView : public View {
  public:
    
    RecordsView(const Entity &anEntity, RowCollection &aCollection)
      : collection{aCollection}, entity(anEntity) {}
    
    // USE: this is the main show() for the view, where it presents all the rows...
    bool show(std::ostream &anOutput) {
      //STUDENT: Implement this, to show each row (from aCollection) like this example:
      std::string sep = "+-";
      std::string theResult = "|";
        int i = 0;
        int r[100];
        for(auto curAtt : entity.getAttributes()) {
        sep.append(curAtt.getSize()+1 ,'-'); 
        sep += '+';
        char theBuffer[100];
            r[i] = curAtt.getSize();
        std::sprintf(theBuffer, " %-*s |", r[i], curAtt.getName().c_str());
        theResult += theBuffer;
            i++;
      }
      anOutput << sep << std::endl;
      anOutput << theResult << std::endl;
      anOutput << sep << std::endl;
      int j=i;

      for(auto curRow : collection.getRows()) {
        KeyValues aKV = curRow->getColumns();
        std::string aResult = "|";
          i=j;
        for(KeyValues::iterator itr = aKV.begin(); itr != aKV.end(); itr++) {
          char theBuffer[100];
          itr->second.become(DataType::varchar_type);
          std::string astr = itr->second;
          if(astr.empty())
              continue;
          std::sprintf(theBuffer, "| %-*s ", r[i-1] ,astr.c_str());
          aResult = theBuffer + aResult;
            i--;
        }
        anOutput << aResult << std::endl;
        anOutput << sep << std::endl;
      }
      return true; //or false ,if your view fails...
    }
    
  protected:
    RowCollection  &collection;
    const Entity   &entity;
  };

}

#endif /* RecordsView_h */
