//
//  Value.cpp
//  Database1
//
//  Created by rick gessner on 4/8/19.
//  Copyright © 2019 rick gessner. All rights reserved.
//

#include "Value.hpp"
#include <sstream>

namespace ECE141 {
//--------WELCOME TO SWITCH CASE CENTRAL HOME OF THE BINTENDO SWITCH----------//
/*/--------------------------------------------------------------------------/^/
	The Implementation has a few problems currently. It isn't elegant.
	Some overloaded members should be able to just pass it's operations to
	another member, but ther were some run time errors where it would loop.
	Need to find a better way of implementation.
/^/--------------------------------------------------------------------------/*/

	//Conversion Constructor Implementations------------------------------------
	Value::Value() {
		type =					DataType::no_type;
	}
	Value::Value(unsigned int	theTime) {
		vuint =					theTime;
		type =					DataType::timestamp_type;
	}
	Value::Value(std::string	theString) {
		vstring = 				theString;
		type =					DataType::varchar_type;
	}
	Value::Value(const char*	theCharStar) {
		vstring =				theCharStar;
		type =					DataType::varchar_type;
	}
	Value::Value(double			theDouble) {
		vfloat = 				(float)theDouble;
		type =					DataType::float_type;
	}
	Value::Value(float			theFloat) {
		vfloat = 				theFloat;
		type =					DataType::float_type;
	}
	Value::Value(bool 			theBool) {
		vbool =					theBool;
		type =					DataType::bool_type;
	}
	Value::Value(int 			theInt) {
		vint =					theInt;
		type =					DataType::int_type;
	}

	//Assignment Operators Implementations--------------------------------------
	Value Value::operator=(unsigned int	theTime) {
		vuint =							theTime;
		type =							DataType::timestamp_type;
        return *this;
    }
	Value Value::operator=(std::string	theString) {
		vstring = 						theString;
		type =							DataType::varchar_type;
		return *this;
	}
	Value Value::operator=(const char*	theCharStar) {
		vstring = 						theCharStar;
		type =							DataType::varchar_type;
		return *this;
	}
	Value Value::operator=(double		theDouble) {
		vfloat = 						(float)theDouble;
		type =							DataType::float_type;
        return *this;
    }
	Value Value::operator=(float		theFloat) {
		vfloat = 						(float)theFloat;
		type =							DataType::float_type;
        return *this;
    }
	Value Value::operator=(bool			theBool) {
		vbool =							theBool;
		type =							DataType::bool_type;
        return *this;
    }
	Value Value::operator=(int			theInt) {
		vint =							theInt;
		type =							DataType::int_type;
        return *this;
    }

	//Conversion Operator Implementations---------------------------------------
	//Constant Value
	Value::operator unsigned int() const {
		switch(type) {
			case DataType::timestamp_type:
				return vuint;
			case DataType::varchar_type:
				return std::stol(vstring, nullptr, 0);
			case DataType::float_type:
				return (unsigned int)vfloat;
			case DataType::bool_type:
				return (unsigned int)vbool;
			case DataType::int_type:
				return (int)vint;
			case DataType::no_type:
				return 0;
		}
	}
	Value::operator std::string() const {
		switch(type) {
			case DataType::timestamp_type:
				return std::to_string(vuint);
			case DataType::varchar_type:
				return vstring;
			case DataType::float_type:
				return std::to_string(vfloat);
			case DataType::bool_type:
				return std::to_string(vbool);
			case DataType::int_type:
				return std::to_string(vint);
			case DataType::no_type:
				return 0;
		}
	}
	Value::operator const char*() const {
		switch(type) {
			case DataType::timestamp_type:
				return std::to_string(vuint).c_str();
			case DataType::varchar_type:
				return vstring.c_str();
			case DataType::float_type:
				return std::to_string(vfloat).c_str();
			case DataType::bool_type:
				return std::to_string(vbool).c_str();
			case DataType::int_type:
				return std::to_string(vint).c_str();
			case DataType::no_type:
				return 0;
		}
	}
	Value::operator double() const {
		switch(type) {
			case DataType::timestamp_type:
				return (double)vuint;
			case DataType::varchar_type:
				return std::stod(vstring, nullptr);
			case DataType::float_type:
				return (double)vfloat;
			case DataType::bool_type:
				return (double)vbool;
			case DataType::int_type:
				return (double)vint;
			case DataType::no_type:
				return 0;
		}
	}
	Value::operator float() const {
		switch(type) {
			case DataType::timestamp_type:
				return (float)vuint;
			case DataType::varchar_type:
				return std::stod(vstring, nullptr);
			case DataType::float_type:
				return (float)vfloat;
			case DataType::bool_type:
				return (float)vbool;
			case DataType::int_type:
				return (float)vint;
			case DataType::no_type:
				return 0;
		}
	}
	Value::operator bool() const {
		switch(type) {
			case DataType::timestamp_type:
				return (bool)vuint;
			case DataType::varchar_type:
				if (vstring.empty())	return false;
				else					return true;	
			case DataType::float_type:
				return vfloat;
			case DataType::bool_type:
				return vbool;
			case DataType::int_type:
				return vint;
			case DataType::no_type:
				return 0;
		}
	}
	Value::operator int() const {
		switch(type) {
			case DataType::timestamp_type:
				return (int)vuint;
			case DataType::varchar_type:
				return std::stoi(vstring, nullptr);
			case DataType::float_type:
				return (int)vfloat;
			case DataType::bool_type:
				return (int)vbool;
			case DataType::int_type:
				return vint;
			case DataType::no_type:
				return 0;
		}
	}

	//None Constant Value
	Value::operator unsigned int() {
		switch(type) {
			case DataType::timestamp_type:
				return vuint;
			case DataType::varchar_type:
				return std::stol(vstring, nullptr, 0);
			case DataType::float_type:
				return (unsigned int)vfloat;
			case DataType::bool_type:
				return (unsigned int)vbool;
			case DataType::int_type:
				return (int)vint;
			case DataType::no_type:
				return 0;
		}
	}
	Value::operator std::string() {
		switch(type) {
			case DataType::timestamp_type:
				return std::to_string(vuint);
			case DataType::varchar_type:
				return vstring;
			case DataType::float_type:
				return std::to_string(vfloat);
			case DataType::bool_type:
				return std::to_string(vbool);
			case DataType::int_type:
				return std::to_string(vint);
			case DataType::no_type:
				return 0;
		}
	}
	Value::operator const char*() {
		switch(type) {
			case DataType::timestamp_type:
				return std::to_string(vuint).c_str();
			case DataType::varchar_type:
				return vstring.c_str();
			case DataType::float_type:
				return std::to_string(vfloat).c_str();
			case DataType::bool_type:
				return std::to_string(vbool).c_str();
			case DataType::int_type:
				return std::to_string(vint).c_str();
			case DataType::no_type:
				return 0;
		}
	}
	Value::operator double() {
		switch(type) {
			case DataType::timestamp_type:
				return (double)vuint;
			case DataType::varchar_type:
				return std::stod(vstring, nullptr);
			case DataType::float_type:
				return vfloat;
			case DataType::bool_type:
				return (double)vbool;
			case DataType::int_type:
				return (double)vint;
			case DataType::no_type:
				return 0;
		}
	}
	Value::operator float() {
		switch(type) {
			case DataType::timestamp_type:
				return (float)vuint;
			case DataType::varchar_type:
				return std::stod(vstring, nullptr);
			case DataType::float_type:
				return vfloat;
			case DataType::bool_type:
				return (float)vbool;
			case DataType::int_type:
				return (float)vint;
			case DataType::no_type:
				return 0;
		}
	}
	Value::operator bool() {
		switch(type) {
			case DataType::timestamp_type:
				return (bool)vuint;
			case DataType::varchar_type:
				if (vstring.empty())	return false;
				else					return true;	
			case DataType::float_type:
				return vfloat;
			case DataType::bool_type:
				return vbool;
			case DataType::int_type:
				return vint;
			case DataType::no_type:
				return 0;
		}
	}

	Value::operator int() {
		switch(type) {
			case DataType::timestamp_type:
				return (int)vuint;
			case DataType::varchar_type:
				return std::stoi(vstring, nullptr);
			case DataType::float_type:
				return (int)vfloat;
			case DataType::bool_type:
				return (int)vbool;
			case DataType::int_type:
				return vint;
			case DataType::no_type:
				return 0;
		}
	}

	//Boolean Operator Implementations------------------------------------------
	//Equals
	bool Value::operator==(const Value &theValue) const {
		if(type == theValue.type) {
			switch(type) {
				case DataType::timestamp_type:
					if (vuint == theValue.vuint)		return true;	break;
				case DataType::varchar_type:
					if (vstring == theValue.vstring)	return true;	break;
				case DataType::float_type:
					if (vfloat == theValue.vfloat)		return true;	break;
				case DataType::bool_type:
					if (vbool == theValue.vbool)		return true;	break;
				case DataType::int_type:
					if (vint == theValue.vint)			return true;	break;
				case DataType::no_type:					return true;	break;
			}
		}
		return false;
	}
	bool Value::operator==(Value &theValue) {
		if(type == theValue.type) {
			switch(type) {
				case DataType::timestamp_type:
					if (vuint == theValue.vuint)		return true;	break;
				case DataType::varchar_type:
					if (vstring == theValue.vstring)	return true;	break;
				case DataType::float_type:
					if (vfloat == theValue.vfloat)		return true;	break;
				case DataType::bool_type:
					if (vbool == theValue.vbool)		return true;	break;
				case DataType::int_type:
					if (vint == theValue.vint)			return true;	break;
				case DataType::no_type:					return true;	break;
			}
		}
		return false;
	}
	bool Value::operator==(unsigned int theTime) {
		return vuint == theTime;
	}
	bool Value::operator==(std::string	theString) {
		if (theString.compare(vstring) == 0)					return true;
		else													return false;
	}
	bool Value::operator==(const char* theCharStar) {
		if (std::strcmp(theCharStar, vstring.c_str()) == 0)		return true;
		else													return false;
	}
	bool Value::operator==(double theDouble) {
		return vfloat == (float)theDouble;
	}
	bool Value::operator==(float theFloat) {
		return vfloat == theFloat;
	}
	bool Value::operator==(bool theBool) {
		return vbool == theBool;
	}
	bool Value::operator==(int theInteger) {
		return vint == theInteger;
	}
	//Not Equals
	bool Value::operator!=(const Value &theValue) const {
		if(type == theValue.type) {
			switch(type) {
				case DataType::timestamp_type:
					if (vuint != theValue.vuint)		return true;	break;
				case DataType::varchar_type:
					if (vstring != theValue.vstring)	return true;	break;
				case DataType::float_type:
					if (vfloat != theValue.vfloat)		return true;	break;
				case DataType::bool_type:
					if (vbool != theValue.vbool)		return true;	break;
				case DataType::int_type:
					if (vint != theValue.vint)			return true;	break;
				case DataType::no_type:					return true;	break;
			}
		}
		return false;
	}
	bool Value::operator!=(Value &theValue) {
		if(type == theValue.type) {
			switch(type) {
				case DataType::timestamp_type:
					if (vuint != theValue.vuint)		return true;	break;
				case DataType::varchar_type:
					if (vstring != theValue.vstring)	return true;	break;
				case DataType::float_type:
					if (vfloat != theValue.vfloat)		return true;	break;
				case DataType::bool_type:
					if (vbool != theValue.vbool)		return true;	break;
				case DataType::int_type:
					if (vint != theValue.vint)			return true;	break;
				case DataType::no_type:					return true;	break;
			}
		}
		return false;
	}
	bool Value::operator!=(unsigned int theTime) {
		return vuint != theTime;
	}
	bool Value::operator!=(std::string	theString) {
		if (theString.compare(vstring) != 0)					return true;
		else													return false;
	}
	bool Value::operator!=(const char* theCharStar) {
		if (std::strcmp(theCharStar, vstring.c_str()) != 0)		return true;
		else													return false;
	}
	bool Value::operator!=(double theDouble) {
		return vfloat != (float)theDouble;
	}
	bool Value::operator!=(float theFloat) {
		return vfloat != theFloat;
	}
	bool Value::operator!=(bool theBool) {
		return vbool != theBool;
	}
	bool Value::operator!=(int theInteger) {
		return vint != theInteger;
	}
	//Less Than Or Equal
	bool Value::operator<=(const Value &theValue) const {
		if(type == theValue.type) {
			switch(type) {
				case DataType::timestamp_type:
					if (vuint <= theValue.vuint)		return true;	break;
				case DataType::varchar_type:
					if (vstring <= theValue.vstring)	return true;	break;
				case DataType::float_type:
					if (vfloat <= theValue.vfloat)		return true;	break;
				case DataType::bool_type:
					if (vbool <= theValue.vbool)		return true;	break;
				case DataType::int_type:
					if (vint <= theValue.vint)			return true;	break;
				case DataType::no_type:					return true;	break;
			}
		}
		return false;
	}
	bool Value::operator<=(Value &theValue) {
		if(type == theValue.type) {
			switch(type) {
				case DataType::timestamp_type:
					if (vuint <= theValue.vuint)		return true;	break;
				case DataType::varchar_type:
					if (vstring <= theValue.vstring)	return true;	break;
				case DataType::float_type:
					if (vfloat <= theValue.vfloat)		return true;	break;
				case DataType::bool_type:
					if (vbool <= theValue.vbool)		return true;	break;
				case DataType::int_type:
					if (vint <= theValue.vint)			return true;	break;
				case DataType::no_type:					return true;	break;
			}
		}
		return false;
	}
	bool Value::operator<=(unsigned int theTime) {
		return vuint <= theTime;
	}
	bool Value::operator<=(std::string	theString) {
		if (theString.compare(vstring) <= 0)					return true;
		else													return false;
	}
	bool Value::operator<=(const char* theCharStar) {
		if (std::strcmp(theCharStar, vstring.c_str()) <= 0)		return true;
		else													return false;
	}
	bool Value::operator<=(double theDouble) {
		return vfloat <= (float)theDouble;
	}
	bool Value::operator<=(float theFloat) {
		return vfloat <= theFloat;
	}
	bool Value::operator<=(bool theBool) {
		return vbool <= theBool;
	}
	bool Value::operator<=(int theInteger) {
		return vint <= theInteger;
	}
	//Greater Than Or Equal
	bool Value::operator>=(const Value &theValue) const {
		if(type == theValue.type) {
			switch(type) {
				case DataType::timestamp_type:
					if (vuint >= theValue.vuint)		return true;	break;
				case DataType::varchar_type:
					if (vstring >= theValue.vstring)	return true;	break;
				case DataType::float_type:
					if (vfloat >= theValue.vfloat)		return true;	break;
				case DataType::bool_type:
					if (vbool >= theValue.vbool)		return true;	break;
				case DataType::int_type:
					if (vint >= theValue.vint)			return true;	break;
				case DataType::no_type:					return true;	break;
			}
		}
		return false;
	}
	bool Value::operator>=(Value &theValue) {
		if(type == theValue.type) {
			switch(type) {
				case DataType::timestamp_type:
					if (vuint >= theValue.vuint)		return true;	break;
				case DataType::varchar_type:
					if (vstring >= theValue.vstring)	return true;	break;
				case DataType::float_type:
					if (vfloat >= theValue.vfloat)		return true;	break;
				case DataType::bool_type:
					if (vbool >= theValue.vbool)		return true;	break;
				case DataType::int_type:
					if (vint >= theValue.vint)			return true;	break;
				case DataType::no_type:					return true;	break;
			}
		}
		return false;
	}
	bool Value::operator>=(unsigned int theTime) {
		return vuint >= theTime;
	}
	bool Value::operator>=(std::string	theString) {
		if (theString.compare(vstring) >= 0)					return true;
		else													return false;
	}
	bool Value::operator>=(const char* theCharStar) {
		if (std::strcmp(theCharStar, vstring.c_str()) >= 0)		return true;
		else													return false;
	}
	bool Value::operator>=(double theDouble) {
		return vfloat >= (float)theDouble;
	}
	bool Value::operator>=(float theFloat) {
		return vfloat >= theFloat;
	}
	bool Value::operator>=(bool theBool) {
		return vbool >= theBool;
	}
	bool Value::operator>=(int theInteger) {
		return vint >= theInteger;
	}
	//Less Than
	bool Value::operator<(const Value &theValue) const {
		if(type == theValue.type) {
			switch(type) {
				case DataType::timestamp_type:
					if (vuint < theValue.vuint)			return true;	break;
				case DataType::varchar_type:
					if (vstring < theValue.vstring)		return true;	break;
				case DataType::float_type:
					if (vfloat < theValue.vfloat)		return true;	break;
				case DataType::bool_type:
					if (vbool < theValue.vbool)			return true;	break;
				case DataType::int_type:
					if (vint < theValue.vint)			return true;	break;
				case DataType::no_type:					return true;	break;
			}
		}
		return false;
	}
	bool Value::operator<(Value &theValue) {
		if(type == theValue.type) {
			switch(type) {
				case DataType::timestamp_type:
					if (vuint < theValue.vuint)			return true;	break;
				case DataType::varchar_type:
					if (vstring < theValue.vstring)		return true;	break;
				case DataType::float_type:
					if (vfloat < theValue.vfloat)		return true;	break;
				case DataType::bool_type:
					if (vbool < theValue.vbool)			return true;	break;
				case DataType::int_type:
					if (vint < theValue.vint)			return true;	break;
				case DataType::no_type:					return true;	break;
			}
		}
		return false;
	}
	bool Value::operator<(unsigned int theTime) {
		return vuint < theTime;
	}
	bool Value::operator<(std::string	theString) {
		if (theString.compare(vstring) < 0)						return true;
		else													return false;
	}
	bool Value::operator<(const char* theCharStar) {
		if (std::strcmp(theCharStar, vstring.c_str()) < 0)		return true;
		else													return false;
	}
	bool Value::operator<(double theDouble) {
		return vfloat < (float)theDouble;
	}
	bool Value::operator<(float theFloat) {
		return vfloat < theFloat;
	}
	bool Value::operator<(bool theBool) {
		return vbool < theBool;
	}
	bool Value::operator<(int theInteger) {
		return vint < theInteger;
	}
	//Greater Than
	bool Value::operator>(const Value &theValue) const {
		if(type == theValue.type) {
			switch(type) {
				case DataType::timestamp_type:
					if (vuint > theValue.vuint)			return true;	break;
				case DataType::varchar_type:
					if (vstring > theValue.vstring)		return true;	break;
				case DataType::float_type:
					if (vfloat > theValue.vfloat)		return true;	break;
				case DataType::bool_type:
					if (vbool > theValue.vbool)			return true;	break;
				case DataType::int_type:
					if (vint > theValue.vint)			return true;	break;
				case DataType::no_type:					return true;	break;
			}
		}
		return false;
	}
	bool Value::operator>(Value &theValue) {
		if(type == theValue.type) {
			switch(type) {
				case DataType::timestamp_type:
					if (vuint > theValue.vuint)			return true;	break;
				case DataType::varchar_type:
					if (vstring > theValue.vstring)		return true;	break;
				case DataType::float_type:
					if (vfloat > theValue.vfloat)		return true;	break;
				case DataType::bool_type:
					if (vbool > theValue.vbool)			return true;	break;
				case DataType::int_type:
					if (vint > theValue.vint)			return true;	break;
				case DataType::no_type:					return true;	break;
			}
		}
		return false;
	}
	bool Value::operator>(unsigned int theTime) {
		return vuint > theTime;
	}
	bool Value::operator>(std::string	theString) {
		if (theString.compare(vstring) > 0)						return true;
		else													return false;
	}
	bool Value::operator>(const char* theCharStar) {
		if (std::strcmp(theCharStar, vstring.c_str()) > 0)		return true;
		else													return false;
	}
	bool Value::operator>(double theDouble) {
		return vfloat > (float)theDouble;
	}
	bool Value::operator>(float theFloat) {
		return vfloat > theFloat;
	}
	bool Value::operator>(bool theBool) {
		return vbool > theBool;
	}
	bool Value::operator>(int theInteger) {
		return vint > theInteger;
	}
	
	//Functions-----------------------------------------------------------------
	size_t Value::getSize() {
		switch(type) {
			case DataType::timestamp_type:	return sizeof(vuint);		break;
			case DataType::varchar_type:	return sizeof(vstring);		break;
			case DataType::float_type:		return sizeof(vfloat);		break;
			case DataType::bool_type:		return sizeof(vbool);		break;
			case DataType::int_type:		return sizeof(vint);		break;
			case DataType::no_type:			return 0;					break;
		}
	}
	size_t Value::getSize() const {
        switch(type) {
            case DataType::timestamp_type:	return sizeof(vuint);		break;
            case DataType::varchar_type:	return sizeof(vstring);		break;
            case DataType::float_type:		return sizeof(vfloat);		break;
            case DataType::bool_type:		return sizeof(vbool);		break;
            case DataType::int_type:		return sizeof(vint);		break;
            case DataType::no_type:			return 0;					break;
        }
	}

	DataType Value::getType() {				return type;}
	DataType Value::getType() const {		return type;}

	StatusResult Value::become(DataType theType) {
		//Going to need these variables later.
		std::istringstream iss(vstring);
		std::stringstream ss;
		StatusResult theResult;

		switch(theType) {
			case DataType::timestamp_type:	vuint = *this;				break;
			case DataType::varchar_type:
				switch(type) {
					case DataType::timestamp_type:
						ss << vuint;		vstring = ss.str();			break;
					case DataType::float_type:
						ss << vfloat;		vstring = ss.str();			break;
					case DataType::bool_type:
						ss << vbool;		vstring = ss.str();			break;
					case DataType::int_type:
						ss << vint;		vstring = ss.str();				break;
					default:											break;
				}														break;	
			case DataType::float_type:		vfloat = *this;				break;
			case DataType::bool_type:		vbool = *this;				break;
			case DataType::int_type:		vint = *this;				break;
			case DataType::no_type:			vint = 0;					break;
		}
		type = theType;
		return theResult;
	}

	void Value::debugDump(std::ostream &theOutput) {
		theOutput << "type: ";
		switch(type) {
			case DataType::timestamp_type:
				theOutput << "unix_timestamp, value: " << vuint;		break;
			case DataType::varchar_type:
				theOutput << "varchar, value: " << vstring;				break;
			case DataType::float_type:
				theOutput << "float, value: " << vfloat;				break;
			case DataType::bool_type:
				theOutput << "bool, value: " << vbool;					break;
			case DataType::int_type:
				theOutput << "int, value: " << vint;					break;
			case DataType::no_type:										break;
		}
	}
	void Value::debugDump(std::ostream &theOutput) const {
		theOutput << "type: ";
		switch(type) {
			case DataType::timestamp_type:
				theOutput << "unix_timestamp, value: " << vuint;		break;
			case DataType::varchar_type:
				theOutput << "varchar, value: " << vstring;				break;
			case DataType::float_type:
				theOutput << "float, value: " << vfloat;				break;
			case DataType::bool_type:
				theOutput << "bool, value: " << vbool;					break;
			case DataType::int_type:
				theOutput << "int, value: " << vint;					break;
			case DataType::no_type:										break;
		}
	}

	Value::~Value() {}


	//What my friends can do----------------------------------------------------
	BufferReader& operator >> (BufferReader& aReader, Value &aValue) {
		uint32_t readInt;
		switch (aValue.type) {
		case DataType::timestamp_type:
			aReader >> aValue.vuint;		break;
		case DataType::varchar_type:
			aReader >> aValue.vstring;		break;
		case DataType::float_type:
			aReader >> aValue.vfloat;		break;
		case DataType::bool_type:
			aReader >> aValue.vbool;		break;
		case DataType::int_type:
			readInt = (uint32_t)aValue.vint;
			aReader >> readInt;				break;
		default:							break;
		}
		return aReader;
	}

	BufferWriter& operator << (BufferWriter& aWriter, const Value &aValue) {
		uint32_t writeInt;
		switch (aValue.type) {
		case DataType::timestamp_type:
			aWriter << aValue.vuint;		break;
		case DataType::varchar_type:
			aWriter << aValue.vstring;		break;
		case DataType::float_type:
			aWriter << aValue.vfloat;		break;
		case DataType::bool_type:
			aWriter << aValue.vbool;		break;
		case DataType::int_type:
			writeInt = (uint32_t)aValue.vint;
			aWriter << writeInt;			break;
		default:							break;
		}
		return aWriter;
	}
}

