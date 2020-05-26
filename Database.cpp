//
//  Database.cpp
//  Database1
//
//  Created by rick gessner on 4/12/19.
//  Copyright © 2019 rick gessner. All rights reserved.
//

#include "Database.hpp"
#include "View.hpp"
#include "BlockVisitor.hpp"
#include "RecordsView.hpp"
//#include "Storage.hpp"
//#include "Index.hpp"

namespace ECE141 {

	bool describeBlock(const Block &aBlock, uint32_t aBlockNum) {
		//This was blank probably will need to implement something here.
		return true;
	}

	//==================================================================

	// USE: This view is used to do a debug dump of db/storage container...
	class DescribeDatabaseView : public View {
	public:
		DescribeDatabaseView(Storage &aStorage) : storage{aStorage}, stream(nullptr) {}

        StatusResult operator()(Storage &aStorage, const Block &aBlock, uint32_t aBlockNum) {
            //STUDENT: Write code here to display information about the given block to your output stream.
            //         Make this as informative as you can.
			std::cout << aBlockNum << ". block ";
            switch(aBlock.header.type) {
                case 'T': std::cout << "TOC\n"; break;
                case 'D': std::cout << "Data\n"; break;
                case 'E': std::cout << "Entity\n"; break;
                case 'F': std::cout << "Free\n"; break;
                case 'I': std::cout << "Index\n"; break;
                default:
					break;
			}
            return StatusResult();
        }
        
		bool show(std::ostream &anOutput) {
			//STUDENT: Implement this method...
            stream = &anOutput;
			storage.eachBlock(*this);
			return true;
		}

	protected:
		Storage       &storage;
		std::ostream  *stream;
	};

	//==================================================================

	// USE: This view is used to show list of entities in TOC....
	class ShowTablesView : public View {
	public:
		ShowTablesView(Block &aTOC) : toc{aTOC} {}

		bool show(std::ostream &anOutput) {
			for(int i=0;i<toc.entities.header.count;i++) {
				anOutput << toc.entities.items[i].name << std::endl;
			}
			return true;
		}

	protected:
		Block         &toc;
	};

	//==================================================================

	Database::Database(const std::string aName, CreateNewStorage)
	: name(aName), storage(aName, CreateNewStorage{}) {
		//we've created storage, but haven't loaded any entities yet...
		
	}

	Database::Database(const std::string aName, OpenExistingStorage)
	: name(aName), storage(aName, OpenExistingStorage{}) {
		//we've opened storage, but haven't loaded any entities yet...

	}

	Database::~Database() {
        saveEntities();
        saveIndexs();
	}

	// USE: a child object needs a named entity for processing...
	Entity* Database::getEntity(const std::string &aName) {
		//STUDENT: implement this method to retrieve entity from storage...
		if(entities.count(aName)) {
			return entities[aName];
		}
		else {
			//check unloaded schema from storage...
			PersistEntity *thePE = storage.findEntityInTOC(aName);
			if(thePE && thePE->blocknum>0) {
				Block theBlock;
				StatusResult theResult=storage.readBlock(thePE->blocknum, theBlock, sizeof(theBlock));
				if(theResult) {
					Entity *theEntity=new Entity(theBlock,thePE->blocknum);
					entities[aName]=theEntity;
					return theEntity;
				}
			}
		}
		return nullptr;
	}

	Index* Database::getIndex(const std::string &aName, Entity* theEntity) {
		//If more grab more from next index block.
		if(theIndexes.count(aName)) {
			return theIndexes[aName];
		}
		else {
			if(theEntity->index) {
				Block theBlock;
				StatusResult theResult = storage.readBlock(theEntity->index, theBlock, sizeof(theBlock));
				if(theResult) {
					Index *theIndex = new Index(theBlock, theEntity->index);
					theIndexes[aName] = theIndex;
					Index* curIndex;
					curIndex = theIndex;
					while(curIndex->hasNextBlockNum()) {
						Block theBlock;
						StatusResult theResult = storage.readBlock(curIndex->getNextBlockNum(), theBlock, sizeof(theBlock));
						if(theResult) {
						Index *theIndex = new Index(theBlock, curIndex->getNextBlockNum());
						theNext[curIndex->getNextBlockNum()] = theIndex;
						curIndex = theIndex;
						}
					}
					return theIndex;
				}
			}
		}
		return nullptr;
	}

	// USE:   Add a new table (entity);
	// NOTE:  The DB assumes ownership of the entity object...
	StatusResult Database::createTable(Entity *anEntity) {
		std::string &theName=anEntity->getName();
		entities[theName]=anEntity;

		Block theBlock;
		theBlock = (*anEntity); //convert from entity...

		StatusResult theResult= storage.addEntity(theName, theBlock);
		Entity *theEntity=entities[theName];
		theEntity->blockNum=theResult.value; //hang on to the blocknum...
        
        //for index
        const AttributeList& theList = anEntity->getAttributes();
        for(auto attr: theList) {
            if (attr.isPrimaryKey()) {
                Index* curTableIndex = new Index(attr.getName(), anEntity->getHash(), attr.getType());
                //construct the new I block
                Block theBlock=(*curTableIndex);
                StatusResult theResult2 = storage.addBlock(theBlock);
                if(theResult2){
                    curTableIndex->setBlockNum(theResult2.value);
					theEntity->index = theResult2.value;
                }
                theIndexes[theName] = curTableIndex;  //pushback an empty Tableindex
                break;
            }
        }

		return theResult;
	}

	// USE: called to actually delete rows from storage for table (via entity) with matching filters...
	StatusResult Database::deleteRows(const Entity &anEntity, const Filters &aFilters) {
		// STUDENT: impelement this
//        StatusResult theResult{unknownDatabase};
//        if(Entity *theEntity = getEntity(aName)) {
//            RowCollection theCollection;
//            if(theResult = selectRows(theCollection, *theEntity, aFilters)) {
//                RowList& theRows=theCollection.getRows();
//                for(auto *theRow : theRows) {
//                    int32_t  blockID = theRow->getBlockNumber();
//                    storage.releaseBlock(blockID);
////                    std::cout<<"Delete Row Successfully!"<<std::endl;
//                }
//            }
//            else{
//                return StatusResult{unexpectedValue};
//            }
//        }
        RowCollection* aCollection = new RowCollection;
        Entity &nonConstEntity = const_cast<Entity&> (anEntity);
        selectRows(*aCollection, nonConstEntity, aFilters);
        if (aCollection->getRows().empty()) {
            return StatusResult{unknownData};
        }
        for (auto aRow : aCollection->getRows()) {
            storage.releaseBlock(aRow->getBlockNumber());
            Value theIndexKey = aRow->getColumns()[nonConstEntity.getPrimaryKey()];
            theIndexes[nonConstEntity.getName()]->removeKeyValue(theIndexKey);
        }
        delete aCollection;
		return StatusResult{noError};
	}

	// USE: Call this to dump the db for debug purposes...
	StatusResult Database::describe(std::ostream &anOutput) {
		if(View *theView = new DescribeDatabaseView(storage)) {
			theView->show(anOutput);  //STUDENT you need to implement the view...
			delete theView;
		}
		return StatusResult{noError};
	}

	// USE: call this to actually remove a table from the DB...
	StatusResult Database::dropTable(const std::string &aName) {
		//STUDENT: Implement this method:
		//         1. find the Entity in storage TOC
		//         2  if found, ask storage to drop it
		//         3. if you cache entities on DB, remove it there too...
        
        PersistEntity* curEntity = storage.findEntityInTOC(aName);
        if(curEntity){
            storage.dropEntity(aName);
            std::map<std::string, Entity*>::iterator it;
            if( it == entities.find(aName))
                entities.erase(it);
            return StatusResult{noError};
        }
        return StatusResult{unknownTable};
	}

	// USE: call this to add a row into the given database...
	StatusResult Database::insertRow(const Row &aRow, const std::string &aTableName) {
		if(Entity *theEntity=getEntity(aTableName)) {
			if(Index *theIndex =getIndex(aTableName, theEntity)) {
			}
			//STUDENT: Add code here to store the row:
			//   1. encode row into a block
			//   2. add block to storage
			//   3. maybe in the future add it to an index
			//   4. get the next auto_incr value from entity (if you need it for id field)...
            
            // get the keyvalue map of aRow
            Row &curRow = const_cast<Row&> (aRow);
            KeyValues curKeyValue = curRow.getColumns();
            
            // add auto_incr key
            Value index_Key;
            std::string thePK = theEntity->getPrimaryKey();  //the primary key
            if(theEntity->getAttribute(thePK).isAutoIncrement()) { // if the primary key is auto_incr
                Value *curValue = new Value(int(theEntity->getNextAutoIncrementValue()));
                curKeyValue[theEntity->getPrimaryKey()] = *curValue;
                curRow.addColumn(thePK, *curValue);
                index_Key = *curValue;
            }
            
            
            //validate the data in aRow (whether matching the format in entity)
            for(auto curAttr:theEntity->attributes){
                std::string curKey = curAttr.getName();
                ////no user imput value for curAttr
                if(!curKeyValue.count(curKey)){
                    if(!curAttr.isNullable())
					{
                        return StatusResult{invalidArguments};
					}
					else
                        curKeyValue[curKey] = "NULL";
                }
                
                Value curValue = curKeyValue[curKey];
                //valid type
                if(curAttr.getType() != curValue.getType()){
                    return StatusResult{invalidArguments};
				}
					
                //valid size
				
                if(curAttr.getSize() < curValue.getSize()-2) {
                    return StatusResult{invalidArguments};
				}
				
            }
            // construct new block and add it to storage
            Block curBlock = Block(curKeyValue);
            curBlock.header.extra = theEntity->getHash();
            StatusResult theResult2 = storage.addBlock(curBlock);
            
            // for index if more add new index block;
            if(theIndexes.count(aTableName)){
				Index* curIndex;
				curIndex = theIndexes[aTableName];
				if (!theIndexes[aTableName]->isFull()) {
					theIndexes[aTableName]->addKeyValue(index_Key, theResult2.value);
				}
				else{
					while(curIndex->isFull()) {
						if (!curIndex->hasNextBlockNum()) {
							//created new index block when full
							Index* nextIndex =  new Index(*curIndex);
							Block theBlock=(*nextIndex);
							StatusResult theResult2 = storage.addBlock(theBlock);
							if(theResult2){
								nextIndex->setBlockNum(theResult2.value);
								curIndex->setNextBlockNum(theResult2.value);
							}
							nextIndex->addKeyValue(index_Key, theResult2.value);
							theNext[nextIndex->getBlockNum()] = nextIndex;
							curIndex = nextIndex;
							return StatusResult{noError};
						}
						if (curIndex->hasNextBlockNum()) {
							curIndex = theNext[curIndex->getNextBlockNum()];
						}
					}
					if (theNext.count(curIndex->getBlockNum())){
							theNext[curIndex->getBlockNum()]->addKeyValue(index_Key, theResult2.value);
							return StatusResult{noError};
					}
				}

			}
            
            std::cout<<"Insert Successfully!!"<<std::endl;
            return StatusResult{noError};
		}
		return StatusResult{unknownTable};
	}

	// USE: select a set of rows that match given filters (or all rows if filters are empty)...
	StatusResult Database::selectRows(RowCollection &aCollection, Entity &anEntity,
						const Filters &aFilters, const StringList *aFields) {
		//STUDENT: Get blocks for this entity from storage, decode into rows, and add to collection
		//         NOTE:  aFields (if not empty) tells you which fields to load per row;
		//                otherwise load all fields (*)
        RowCollector aRC(anEntity, aFilters, aCollection, aFields);
        storage.eachBlock(aRC);
		return StatusResult{noError};
	}

	StatusResult Database::selectRows(RowCollection &theRowCollection, Entity &theEntity, Index &theIndex, const Filters &theFilters) {
		StatusResult theResult;
		std::cout << "Number of values stores is " << theIndex.getIndex().size() << '\n';
		for(auto &theValue: theIndex.getIndex()) {
			Block tempBlock;
            KeyValues aList;
            if(storage.readBlock(theValue.second, tempBlock)) {
				KeyValues theValues;
				theResult = theEntity.decodeData(tempBlock, aList);;
				if(theFilters.getCount() == 0 || theFilters.matches(aList)) {
					Row *aRow = new Row(theValue.second);
					for (auto &thePair: aList) {
						aRow->addColumn(thePair.first, thePair.second);
					}
					theRowCollection.add(aRow);
				}
				
			}
		}
		if (theIndex.hasNextBlockNum()) {
			Index *curIndex;
			curIndex = &theIndex;
			while (curIndex->hasNextBlockNum()) {
				curIndex = theNext[theIndex.getNextBlockNum()];
				for(auto &theValue: curIndex->getIndex()) {
					Block tempBlock;
					KeyValues aList;
					if(storage.readBlock(theValue.second, tempBlock)) {
						KeyValues theValues;
						theResult = theEntity.decodeData(tempBlock, aList);;
						if(theFilters.getCount() == 0 || theFilters.matches(aList)) {
							Row *aRow = new Row(theValue.second);
							for (auto &thePair: aList) {
								aRow->addColumn(thePair.first, thePair.second);
							}
							theRowCollection.add(aRow);
						}
						
					}
				}
				if(curIndex->hasNextBlockNum()) {
					curIndex = theNext[curIndex->getNextBlockNum()];
				}
			}
		}

		// else {
		// 	for(auto& expression:theFilters.get()) {
		// 		if (storage.readBlock(theIndex.getValue(expression->rhs.value), tempBlock)) {
		// 			KeyValues theValues;
		// 				theResult = theEntity.decodeData(tempBlock, aList);;

		// 				Row *aRow = new Row(theIndex.getValue(expression->rhs.value));
		// 				for (auto &thePair: aList) {
		// 					aRow->addColumn(thePair.first, thePair.second);
		// 				}
		// 				theRowCollection.add(aRow);
		// 		}
				
		// 	}
		// }
		return theResult;
	}

	//USE: resave entities that were in memory and changed...
	StatusResult Database::saveEntities() {
		StatusResult theResult{noError};
		for (auto thePair : entities) {
			if(thePair.second->isDirty()) {
				Block theBlock=(*thePair.second);
				theResult=storage.writeBlock(thePair.second->blockNum, theBlock);
			}
		}
		return theResult;
	}
    
    StatusResult Database::saveIndexs() {
        StatusResult theResult{noError};
        for (auto aTableIndex : theIndexes) {
            Block theBlock=(*aTableIndex.second);
            theResult = storage.writeBlock(aTableIndex.second->getBlockNum(), theBlock);
//            if(thePair.second->isDirty()) {
//                Block theBlock=(*thePair.second);
//                theResult=storage.writeBlock(thePair.second->blockNum, theBlock);
//            }
        }
		for (auto aTableIndex : theNext) {
            Block theBlock=(*aTableIndex.second);
            theResult = storage.writeBlock(aTableIndex.second->getBlockNum(), theBlock);
//            if(thePair.second->isDirty()) {
//                Block theBlock=(*thePair.second);
//                theResult=storage.writeBlock(thePair.second->blockNum, theBlock);
//            }
        }
        return theResult;
    }

	//USE: show the list of tables in this db...
	StatusResult Database::showTables(std::ostream &anOutput) {
		//STUDENT: create a ShowTablesView object, and call the show() method...
		//         That view is declared at the top of this file.
		ShowTablesView* theTablesView = new ShowTablesView(storage.toc);
		theTablesView->show(anOutput);
		delete theTablesView;
		return StatusResult{noError};
	}

	// USE: called to update records already in db (future assignment)...
	StatusResult Database::updateRow(Row &aRow, const KeyValues &aKVList, const Entity &anEntity){
		//STUDENT: Implement this...
        //update row
//        Row &bRow = const_cast<Row&>(aRow);
        for(std::map<std::string, Value>::const_iterator it = aKVList.begin(); it!=aKVList.end(); it++){
            aRow.getColumns()[it->first] = it->second;
        }
        //find the certain block and delete
        int32_t  blockID = aRow.getBlockNumber();
        storage.releaseBlock(blockID);
        //construt a new block data and store it to the old block#
        Block curBlock = Block(aRow.getColumns()); //use bRow's column, cause 'aKVList' only has partial data
        curBlock.header.extra = anEntity.getHash();
        storage.writeBlock(blockID, curBlock);
        std::cout<<"Update Successfully!"<<std::endl;
        
		return StatusResult{noError};
	}

	// USE: asks the DB if a table exists in storage...
	bool Database::tableExists(const std::string aName) {
		//STUDENT: implement this if you need it...
		return false;
	}

}

