//
//  Database.hpp
//  Database3
//
//  Created by rick gessner on 3/30/18.
//  Copyright © 2018 rick gessner. All rights reserved.
//

#ifndef Database_hpp
#define Database_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include <map>
#include "Storage.hpp"
#include "Row.hpp"
#include "Entity.hpp"
#include "Filters.hpp"
#include "Index.hpp"

namespace ECE141 {

	class Statement;

	class Database {
	public:

		Database(const std::string aPath, CreateNewStorage);
		Database(const std::string aPath, OpenExistingStorage);

		//Database(const Database &aDatabase);

		~Database();

		std::string&    getName() {return name;}
		Entity*         getEntity(const std::string &aName);
		Index*			getIndex(const std::string &aName, Entity* anEntity);
		StatusResult    describe(std::ostream &anOutput); //dump the DB (storage) for debug purpose
		StatusResult    saveEntities();
        StatusResult    saveIndexs();

		//Row related...
		StatusResult    deleteRows(const Entity &anEntity, const Filters &aFilters);
		StatusResult    insertRow(const Row &aRow, const std::string &aTableName);
		StatusResult    updateRow(Row &aRow, const KeyValues &aKVList, const Entity &anEntity);
		StatusResult    selectRows(RowCollection &aColl,    Entity &anEntity,
		                        const Filters &aFilters,	const StringList *aList=nullptr);
		StatusResult	selectRows(RowCollection &aRowCollection, Entity &anEntity,	Index &anIndex,	const Filters &aFilters);
		//Table related...
		StatusResult    createTable(Entity *anEntity);
		StatusResult    dropTable(const std::string &aName);
		StatusResult    showTables(std::ostream &anOutput);
		bool            tableExists(const std::string aName);


	protected:
		std::string                     name;
		Storage                         storage;
		std::map<std::string, Entity*>  entities;  // an entity correspondding to a table. it's a tablename--entity map
//        std::map<std::string, uint32_t> theTableIndex;
        std::map<std::string, Index*>	theIndexes;
		std::map<uint32_t, Index*>		theNext;
	};

}

#endif /* Database_hpp */
