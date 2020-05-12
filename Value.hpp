//
//  Value.hpp
//  Database1
//
//  Created by rick gessner on 3/20/19.
//  Copyright © 2019 rick gessner. All rights reserved.
//

#ifndef Value_hpp
#define Value_hpp

#include <string>
#include <cstring>
#include <map>
#include <iostream>
#include "Errors.hpp"
#include "MemoryStream.hpp"

namespace ECE141 {

  	//NOTE: integer is a SIGNED value
  	//NOTE: timestamp is an UNSIGNED value!!!!!

  	enum class DataType {
    	no_type='N',		int_type='I',		float_type='F',	bool_type='B',
		timestamp_type='T', varchar_type='V',
    	//our enums are associated w/chars to be readable in encoded storage blocks...
  	};
  
  	//USE: define a dynamic type that allows us to hold field data in rows...k
  	class Value {
	public:
/*/--------------------------------------------------------------------------/^/
	Value needs multiple constructors for each type of data. Currently
	Value supports:

		1.	unsigned int	[Representing a Timestamp in MySQL]
		2.	string			[Representing a Char in MySQL]
		3.	const char *	[^ same]
		4.	double			[Representing a Float in MySQL]
			- Currently stores as a float, but should store as a double
			  in the future. (This is temporary.)
		5.	float			[^ same, but here to stay]
		6.	bool			[Representing a Bool in MySQL]
	
	The Value class needs a const version of each operator due to the
	possibilty of Value being a const object.

	Will need to make versions of Value's members that can handle const
	values as input.
/^/--------------------------------------------------------------------------/*/

		//Default Constructor Declaration
		Value();

		//Conversion Constructor Declarations
		Value(unsigned int						aTime);
		Value(std::string						aString);
		Value(const char*						aCharStar);
		Value(double 							aDouble);
		Value(float								aFloat);
		Value(bool 								aBool);
		Value(int 								anInt);

    	//Assignment Operator Declarations
		Value operator=(unsigned int			aTime);
		Value operator=(std::string				aString);
		Value operator=(const char* 			aCharStar);
		Value operator=(double					aDouble);
		Value operator=(float					aFloat);
		Value operator=(bool					aBool);
		Value operator=(int						anInt);

    	//Conversion Operator Declarations
		//Constant Value
		operator		unsigned int()							const;
		operator		std::string()							const;
		operator		const char*()							const;
		operator		double()								const;
		operator		float()									const;
		operator		bool()									const;
		operator		int()									const;
		//None Constant Value
		operator		unsigned int();
		operator		std::string();
		operator		const char*();
		operator		double();
		operator		float();
		operator		bool();
		operator		int();

		//Boolean Operator Declarations
		//Equals
		bool operator==(const Value				&aValue)		const;
		bool operator==(Value					&aValue);
		bool operator==(unsigned int			aTime);
		bool operator==(std::string				aString);
		bool operator==(const char*				aCharStar);
		bool operator==(double					aDouble);
		bool operator==(float					aFloat);
		bool operator==(bool					aBool);
		bool operator==(int						anInteger);
		//Not Equals
		bool operator!=(const Value				&aValue)		const;
		bool operator!=(Value					&aValue);
		bool operator!=(unsigned int			aTime);
		bool operator!=(std::string				aString);
		bool operator!=(const char*				aCharStar);
		bool operator!=(double					aDouble);
		bool operator!=(float					aFloat);
		bool operator!=(bool					aBool);
		bool operator!=(int						anInteger);
		//Less Than Or Equals
		bool operator<=(const Value				&aValue)		const;
		bool operator<=(Value					&aValue);
		bool operator<=(unsigned int			aTime);
		bool operator<=(std::string				aString);
		bool operator<=(const char*				aCharStar);
		bool operator<=(double					aDouble);
		bool operator<=(float					aFloat);
		bool operator<=(bool					aBool);
		bool operator<=(int						anInteger);
		//Greater Than Or Equals
		bool operator>=(const Value				&aValue)		const;
		bool operator>=(Value					&aValue);
		bool operator>=(unsigned int			aTime);
		bool operator>=(std::string				aString);
		bool operator>=(const char*				aCharStar);
		bool operator>=(double					aDouble);
		bool operator>=(float					aFloat);
		bool operator>=(bool					aBool);
		bool operator>=(int						anInteger);
		//Less Than
		bool operator<(const Value				&aValue)		const;
		bool operator<(Value					&aValue);
		bool operator<(unsigned int				aTime);
		bool operator<(std::string				aString);
		bool operator<(const char*				aCharStar);
		bool operator<(double					aDouble);
		bool operator<(float					aFloat);
		bool operator<(bool						aBool);
		bool operator<(int						anInteger);
        //Greater Than
		bool operator>(const Value				&aValue)		const;
		bool operator>(Value					&aValue);
		bool operator>(unsigned int				aTime);
		bool operator>(std::string				aString);
		bool operator>(const char*				aCharStar);
		bool operator>(double					aDouble);
		bool operator>(float					aFloat);
		bool operator>(bool						aBool);
		bool operator>(int						anInteger);
	
		//This finds the size of the Value.
		size_t  		getSize()								const;
    	size_t  		getSize();

		//This finds the type assigned to the Value.
		DataType		getType()								const;
    	DataType		getType();

		//This causes the value to assume given type.
    	StatusResult	become(DataType aType);

		//This describes (emit) this object onto given stream.
		void			debugDump(std::ostream &anOutput)		const;
    	void			debugDump(std::ostream &anOutput);

		//Deconstructor Declaration
		~Value();

		//Friends to allow for using Value's privates.
		friend BufferReader& operator >> (BufferReader& istm, Value &aValue);
		friend BufferWriter& operator << (BufferWriter& ostm, const Value &aValue);

	protected:
		//The Value's Type.
		DataType 			type;
		//The String had issues being part of the union.
		std::string			vstring;
		//This union will be 4 bytes big.
		union {
			bool			vbool;
			int				vint;
			float			vfloat;
			unsigned int	vuint;
		};
  	};
  
  	//for holding a collection of key/values...
  	using KeyValues = std::map<std::string, Value>;
}

#endif /* Value_h */
