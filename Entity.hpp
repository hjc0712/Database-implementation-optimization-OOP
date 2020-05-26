//
//  Entity.hpp
//  ECEDatabase
//
//  Created by rick gessner on 4/19/18.
//  Copyright © 2018 rick gessner. All rights reserved.
//

#ifndef Entity_hpp
#define Entity_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <functional>
#include "Attribute.hpp"
#include "Value.hpp"
#include "Row.hpp"
#include "View.hpp"

namespace ECE141 {

	struct Block;
	struct Expression;
	class  Database;
	class  Tokenizer;

	using StringList = std::vector<std::string>;

	using attribute_callback = std::function<bool(const Attribute &anAttribute)>;
	using AttributeList = std::vector<Attribute>;

	class Entity {
	public:
								Entity();
								Entity(std::string aName);
								Entity(Block &aBlock , uint32_t aBlockId=0);
								Entity(const Entity &aCopy);

		operator				Block();

		std::string&			getName() {return name;}

		const AttributeList&	getAttributes() const {return attributes;}

		Entity&					markDirty(bool aState);
		bool					isDirty() {return dirty;}

		Entity&					addAttribute(std::string aName, DataType aType, uint8_t aSize=0, bool autoIncr=false);
		Entity&					addAttribute(const Attribute &anAttribute);

		Attribute&				getAttribute(const std::string &aName);
		Value					getDefaultValue(const Attribute &anAttribute);
        uint32_t                getHash() const {return hash;}

		StatusResult			validate(KeyValues &aList);

		StatusResult			encodeData(KeyValues &aValuesList, Block &aBlock);
		StatusResult			decodeData(const Block &aBlock, KeyValues &aValuesList,
								const StringList *aFields=nullptr) const;

		std::string				getPrimaryKey();
		uint32_t				getNextAutoIncrementValue();

		virtual void			each(attribute_callback aCallback) const;

		static  uint32_t		hashString(const char *aString);

		friend class Database;

	protected:

		AttributeList	attributes;
		std::string		name;
		uint16_t		count;     //number of records
		uint32_t		autoincr;  //current auto_increment value (# of records created)...
		uint32_t		blockNum;  //storage location.
		uint32_t		hash;      //int hash of schema name
		bool			dirty;
		uint32_t		index;
	};


}

#endif /* Entity_hpp */
