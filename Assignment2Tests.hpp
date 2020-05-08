//
//  Assignment2Tests.hpp
//  Database2
//
//  Created by rick gessner on 4/7/19.
//  Copyright © 2019 rick gessner. All rights reserved.
//

#ifndef Assignment2Tests_h
#define Assignment2Tests_h

#include "Value.hpp"
#include "Row.hpp"
#include "Storage.hpp"
#include <ctime>
#include <string>
#include <typeinfo> 
#include <iostream>

std::ostream& getOutput() {
	return std::cout;
}

void runConstructorTests(std::ostream &anOutput) {
	//STUDENT: add code here to test that construct your Value class for each type
	bool 			toggle(true);
	int 			integer(-1);
	unsigned int 	tstamp(1);
	float 			decimal(1.11);
	std::string 	theString("one");
	const char *	theCharStar = theString.c_str();

	ECE141::Value theValue5(tstamp);  //build unix_timestamp value
	std::cout << "type: uint, value: " << tstamp << "\t\t";
	theValue5.debugDump(anOutput);
	if (theValue5 == tstamp)				std::cout << "\t\tPassed\n";
	else									std::cout << "\t\tFailed\n";

	ECE141::Value theValue1(theString);  //build varchar from std::string
	std::cout << "type: string, value: " << theString << "\t";
	theValue1.debugDump(anOutput);
	if (theValue1 == theString)				std::cout << "\t\tPassed\n";
	else									std::cout << "\t\tFailed\n";

	ECE141::Value theValue2(theCharStar);  //build varchar from char*
	std::cout << "type: char*, value: " << theCharStar << "\t\t";
	theValue2.debugDump(anOutput);
	if (theValue2 == theCharStar)			std::cout << "\t\tPassed\n";
	else									std::cout << "\t\tFailed\n";

	ECE141::Value theValue6(decimal);  //build float value
	std::cout << "type: float, value: " << decimal << "\t";
	theValue6.debugDump(anOutput);
	if (theValue6 == decimal)				std::cout << "\t\tPassed\n";
	else									std::cout << "\t\tFailed\n";

	ECE141::Value theValue3(toggle);  //build boolean value
	std::cout << "type: bool, value: " << !toggle << "\t\t";
	theValue3.debugDump(anOutput);
	if (theValue3 == toggle)				std::cout << "\t\t\tPassed\n";
	else									std::cout << "\t\t\tFailed\n";

	ECE141::Value theValue4(integer); //build int value
	std::cout << "type: int, value: " << integer << "\t\t";
	theValue4.debugDump(anOutput);
	if (theValue4 == integer)				std::cout << "\t\t\tPassed\n";
	else									std::cout << "\t\t\tFailed\n";


	std::cout << std::endl;
}

void runAssignmentTests(std::ostream &anOutput) {
	// STUDENT: Implement test to validate assignment operators for all your types...
	bool 			toggle(true);
	int 			integer(-2);
	unsigned int 	tstamp(2);
	float 			decimal(2.2);
	std::string 	theString("two");
	const char *	theCharStar = theString.c_str();

	ECE141::Value theValue(toggle); //start with boolean value...

	std::cout << "type: uint, value: " << tstamp << "\t\t";
	//convert to unix_timestamp
	theValue = tstamp;						theValue.debugDump(anOutput);
	if (theValue == tstamp)					std::cout << "\t\tPassed\n";
	else									std::cout << "\t\tFailed\n";

	std::cout << "type: string, value: " << theString << "\t";
	//convert to string
	theValue = theString;					theValue.debugDump(anOutput);
	if (theValue == theString)				std::cout << "\t\tPassed\n";
	else									std::cout << "\t\tFailed\n";

	std::cout << "type: char*, value: " << theCharStar << "\t\t";
	//convert to string (via char*)
	theValue = theCharStar;					theValue.debugDump(anOutput);
	if (theValue == theCharStar)			std::cout << "\t\tPassed\n";
	else									std::cout << "\t\tFailed\n";

	std::cout << "type: float, value: " << decimal << "\t\t";
	//convert to float
	theValue = decimal;  					theValue.debugDump(anOutput);
	if (theValue == decimal)				std::cout << "\t\t\tPassed\n";
	else									std::cout << "\t\t\tFailed\n";

	std::cout << "type: bool, value: " << !toggle << "\t\t";
	//convert to bool
	theValue = !toggle;						theValue.debugDump(anOutput);
	if (theValue == !toggle)				std::cout << "\t\t\tPassed\n";
	else									std::cout << "\t\t\tFailed\n";

	std::cout << "type: int, value: " << integer << "\t\t";
	//convert to int
	theValue = integer;						theValue.debugDump(anOutput);
	if (theValue == integer)				std::cout << "\t\t\tPassed\n";
	else									std::cout << "\t\t\tFailed\n";

	std::cout << std::endl;
}

void runConversionTests(std::ostream &anOutput) {
	//STUDENT: add tests to mutate values between types (from bool to int, or float to varchar)
	//Convert your value object from each type, to each other type... (NxM)
	std::string		theString("three");
	ECE141::Value	timeValue(3);
	ECE141::Value	stringValue(theString);
	ECE141::Value	charValue(theString.c_str());
	ECE141::Value	floatValue(3.33);
	ECE141::Value	boolValue(true);
	ECE141::Value	intValue(-3);

	unsigned int tstamp = timeValue;
	std::cout << "type: uint, value: " << tstamp << "\t\t";
	timeValue.debugDump(anOutput);
	if (timeValue == tstamp)				std::cout << "\t\t\tPassed\n";
	else									std::cout << "\t\t\tFailed\n";

	std::string words = stringValue;
	std::cout << "type: string, value: " << theString << "\t";
	stringValue.debugDump(anOutput);
	if (stringValue == words)				std::cout << "\t\tPassed\n";
	else									std::cout << "\t\tFailed\n";

	const char* character = charValue;
	std::cout << "type: char*, value: " << character << "\t";
	charValue.debugDump(anOutput);
	if (charValue == character)				std::cout << "\t\tPassed\n";
	else									std::cout << "\t\tFailed\n";

	double decimal = floatValue;
	std::cout << "type: float, value: " << decimal << "\t";
	floatValue.debugDump(anOutput);
	if (floatValue == decimal)				std::cout << "\t\tPassed\n";
	else									std::cout << "\t\tFailed\n";

	bool toggle = boolValue;
	std::cout << "type: bool, value: " << !toggle << "\t\t";
	boolValue.debugDump(anOutput);
	if (boolValue == toggle)				std::cout << "\t\t\tPassed\n";
	else									std::cout << "\t\t\tFailed\n";

	int integer = intValue;
	std::cout << "type: int, value: " << integer << "\t\t";
	intValue.debugDump(anOutput);
	if (intValue == integer)				std::cout << "\t\t\tPassed\n";
	else									std::cout << "\t\t\tFailed\n";
	std::cout << std::endl;
}

void runFunctionTests(std::ostream &anOutput) {
	unsigned int 	tstamp(4);
	std::string 	words("4");
	float 			decimal(4.4);
	bool 			toggle(true);
	int 			integer(-4);

	ECE141::Value	timeValue(tstamp);
	ECE141::Value	stringValue(words);
	ECE141::Value	floatValue(decimal);
	ECE141::Value	boolValue(toggle);
	ECE141::Value	intValue(integer);
	std::cout << "Running Become Tests:\n";
	std::cout << "From:\t\tTo:\t\t\t\tResults:\n";
	std::cout << "========================================================\n";
	std::cout << "Time\t\tTime\t\t";
	timeValue.become(ECE141::DataType::timestamp_type);
	if (ECE141::DataType::timestamp_type == timeValue.getType())
											std::cout << "\t\tPassed\n";
	else									std::cout << "\t\tFailed\n";
	std::cout << "Time\t\tString\t\t";
	timeValue.become(ECE141::DataType::varchar_type);
	if (ECE141::DataType::varchar_type == timeValue.getType())
											std::cout << "\t\tPassed\n";
	else									std::cout << "\t\tFailed\n";
	std::cout << "Time\t\tFloat\t\t";
	timeValue.become(ECE141::DataType::float_type);
	if (ECE141::DataType::float_type == timeValue.getType())
											std::cout << "\t\tPassed\n";
	else									std::cout << "\t\tFailed\n";
	std::cout << "Time\t\tBool\t\t";
	timeValue.become(ECE141::DataType::bool_type);
	if (ECE141::DataType::bool_type == timeValue.getType())
											std::cout << "\t\tPassed\n";
	else									std::cout << "\t\tFailed\n";
	std::cout << "Time\t\tInteger\t\t";
	timeValue.become(ECE141::DataType::int_type);
	if (ECE141::DataType::int_type == timeValue.getType())
											std::cout << "\t\tPassed\n";
	else									std::cout << "\t\tFailed\n";
	std::cout << "--------------------------------------------------------\n";
	std::cout << "String\t\tTime\t\t";
	stringValue.become(ECE141::DataType::timestamp_type);
	if (ECE141::DataType::timestamp_type == stringValue.getType())
											std::cout << "\t\tPassed\n";
	else									std::cout << "\t\tFailed\n";
	std::cout << "String\t\tString\t\t";
	stringValue.become(ECE141::DataType::varchar_type);
	if (ECE141::DataType::varchar_type == stringValue.getType())
											std::cout << "\t\tPassed\n";
	else									std::cout << "\t\tFailed\n";
	std::cout << "String\t\tFloat\t\t";
	stringValue.become(ECE141::DataType::float_type);
	if (ECE141::DataType::float_type == stringValue.getType())
											std::cout << "\t\tPassed\n";
	else									std::cout << "\t\tFailed\n";
	std::cout << "String\t\tBool\t\t";
	stringValue.become(ECE141::DataType::bool_type);
	if (ECE141::DataType::bool_type == stringValue.getType())
											std::cout << "\t\tPassed\n";
	else									std::cout << "\t\tFailed\n";
	std::cout << "String\t\tInteger\t\t";
	stringValue.become(ECE141::DataType::int_type);
	if (ECE141::DataType::int_type == stringValue.getType())
											std::cout << "\t\tPassed\n";
	else									std::cout << "\t\tFailed\n";
	std::cout << "--------------------------------------------------------\n";
	std::cout << "Float\t\tTime\t\t";
	floatValue.become(ECE141::DataType::timestamp_type);
	if (ECE141::DataType::timestamp_type == floatValue.getType())
											std::cout << "\t\tPassed\n";
	else									std::cout << "\t\tFailed\n";
	std::cout << "Float\t\tString\t\t";
	floatValue.become(ECE141::DataType::varchar_type);
	if (ECE141::DataType::varchar_type == floatValue.getType())
											std::cout << "\t\tPassed\n";
	else									std::cout << "\t\tFailed\n";
	std::cout << "Float\t\tFloat\t\t";
	floatValue.become(ECE141::DataType::float_type);
	if (ECE141::DataType::float_type == floatValue.getType())
											std::cout << "\t\tPassed\n";
	else									std::cout << "\t\tFailed\n";
	std::cout << "Float\t\tBool\t\t";
	floatValue.become(ECE141::DataType::bool_type);
	if (ECE141::DataType::bool_type == floatValue.getType())
											std::cout << "\t\tPassed\n";
	else									std::cout << "\t\tFailed\n";
	std::cout << "Float\t\tInteger\t\t";
	floatValue.become(ECE141::DataType::int_type);
	if (ECE141::DataType::int_type == floatValue.getType())
											std::cout << "\t\tPassed\n";
	else									std::cout << "\t\tFailed\n";
	std::cout << "--------------------------------------------------------\n";
	std::cout << "Bool\t\tTime\t\t";
	boolValue.become(ECE141::DataType::timestamp_type);
	if (ECE141::DataType::timestamp_type == boolValue.getType())
											std::cout << "\t\tPassed\n";
	else									std::cout << "\t\tFailed\n";
	std::cout << "Bool\t\tString\t\t";
	boolValue.become(ECE141::DataType::varchar_type);
	if (ECE141::DataType::varchar_type == boolValue.getType())
											std::cout << "\t\tPassed\n";
	else									std::cout << "\t\tFailed\n";
	std::cout << "Bool\t\tFloat\t\t";
	boolValue.become(ECE141::DataType::float_type);
	if (ECE141::DataType::float_type == boolValue.getType())
											std::cout << "\t\tPassed\n";
	else									std::cout << "\t\tFailed\n";
	std::cout << "Bool\t\tBool\t\t";
	boolValue.become(ECE141::DataType::bool_type);
	if (ECE141::DataType::bool_type == boolValue.getType())
											std::cout << "\t\tPassed\n";
	else									std::cout << "\t\tFailed\n";
	std::cout << "Bool\t\tInteger\t\t";
	boolValue.become(ECE141::DataType::int_type);
	if (ECE141::DataType::int_type == boolValue.getType())
											std::cout << "\t\tPassed\n";
	else									std::cout << "\t\tFailed\n";
	std::cout << "--------------------------------------------------------\n";
	std::cout << "Integer\t\tTime\t\t";
	intValue.become(ECE141::DataType::timestamp_type);
	if (ECE141::DataType::timestamp_type == intValue.getType())
											std::cout << "\t\tPassed\n";
	else									std::cout << "\t\tFailed\n";
	std::cout << "Integer\t\tString\t\t";
	intValue.become(ECE141::DataType::varchar_type);
	if (ECE141::DataType::varchar_type == intValue.getType())
											std::cout << "\t\tPassed\n";
	else									std::cout << "\t\tFailed\n";
	std::cout << "Integer\t\tFloat\t\t";
	intValue.become(ECE141::DataType::float_type);
	if (ECE141::DataType::float_type == intValue.getType())
											std::cout << "\t\tPassed\n";
	else									std::cout << "\t\tFailed\n";
	std::cout << "Integer\t\tBool\t\t";
	intValue.become(ECE141::DataType::bool_type);
	if (ECE141::DataType::bool_type == intValue.getType())
											std::cout << "\t\tPassed\n";
	else									std::cout << "\t\tFailed\n";
	std::cout << "Integer\t\tInteger\t\t";
	intValue.become(ECE141::DataType::int_type);
	if (ECE141::DataType::int_type == intValue.getType())
											std::cout << "\t\tPassed\n";
	else									std::cout << "\t\tFailed\n";
	std::cout << std::endl;
}
//This is called by testing code to make a Value object for testing...
ECE141::Value createValueObjectForType(ECE141::DataType aType) {
	//create a value object (with random value) of given type
	//return new value object...
	ECE141::Value aValue;
    switch (aType){
        case ECE141::DataType::int_type:{
            aValue = std::rand() % 1000000;
            break;
        }
        case ECE141::DataType::bool_type:{
            aValue = (bool)(rand() % 2);
            break;
        }
		case ECE141::DataType::float_type: {
			aValue = (float)1 / (float)(rand() % 10000);
			break;
		}
		case ECE141::DataType::varchar_type: {
			std::string astring;
			char achar;
			for(int i = 0; i < 8; i++) {
				achar = (char)((rand() % 91) + 32);
				astring += achar;
			}
			aValue = astring;
			break;
		}
		case ECE141::DataType::timestamp_type: {
			aValue = ((unsigned int)std::rand() % (unsigned int)1000000);
			break;
		}
        default:{
            aValue = false;
            break;
        }
    }
	return aValue;
}

//Below we are creating a series of random values for your tests.
//1. N values are stored in the Row
//2. The Row is encoded in to a block
//3. The block is decoded back into a row
//4. The two rows are compared (should be identical)...

void runEncodeDecodeTests(std::ostream &anOutput) {

	// STUDENT: This will only work when:
	// 1. your Value class is working
	// 2. you implemented Block(const KeyValues &aList)  (in storage.cpp)
	// 3. you implemented Row(const Block &aBlock)  (in row.cpp)

	std::srand((unsigned int)std::time(nullptr));//random # seed...

	ECE141::Row theRow;
	ECE141::KeyValues &theColumns = theRow.getColumns();

	//generate 20 values and stuff them into theRow...
	for(int theV = 0; theV < 20; theV++) {
		ECE141::DataType theType = ECE141::DataType::no_type;

		//randomly choose a value type...
		switch((std::rand() % 5)+ 1) {
			case 1 : theType = ECE141::DataType::int_type;			break;
			case 2 : theType = ECE141::DataType::float_type;		break;
			case 3 : theType = ECE141::DataType::bool_type;			break;
			case 4 : theType = ECE141::DataType::timestamp_type;	break;
			case 5 : theType = ECE141::DataType::varchar_type;		break;
			default :												break;
		}

		//now make a value of for type type...
		ECE141::Value theValue=createValueObjectForType(theType);

		char theField[20]{0};
		sprintf(theField, "field_%d", theV);
		theColumns[theField]=theValue;
	}
	ECE141::Block theBlock(theColumns); //Encode your key/values into the block...
	ECE141::Row aDecodedRow(theBlock);	//Going to and fro from Block to Row...
	ECE141::Block aBlock(aDecodedRow);	//Going to and fro form Row to Block...
	ECE141::Row theDecodedRow(aBlock);

	ECE141::KeyValues &theDecodedColumns = theDecodedRow.getColumns();
	std::cout << "Orignal Field:\tOriginal Data:\t\t\t\t";
	std::cout << "Decoded Field:\tDecoded Data:\n";
	std::cout << "========================================================";
	std::cout << "=====================================================\n";
	for(auto it = theColumns.cbegin(), end_theC = theColumns.cend(),
        itd = theDecodedColumns.cbegin(), end_theDC = theDecodedColumns.cend();
        it != end_theC || itd != end_theDC; it++, itd++) {
		std::cout << it->first << " \t";	it->second.debugDump(anOutput);
		if (it->second.getType() == ECE141::DataType::bool_type)
				std::cout << "          \t";
		if (it->second.getType() == ECE141::DataType::int_type)
				std::cout << "        \t";
		else	std::cout << "  \t";
		std::cout << itd->first << "  \t";	itd->second.debugDump(anOutput);
		std::cout << "\n";
	}
	std::cout << "\nResults: ";
	if(theRow==theDecodedRow)	anOutput << "PASSED!" << std::endl;
	else						anOutput << "FAILED!" << std::endl;

}

void runAssignment2Tests() {
	std::ostream &theOutput=getOutput();
	std::cout << "                 |----Running Constructor Tests----|\n";
	std::cout << "Original:\t\t\tDump:\t\t\t\t\tResults:\n";
	std::cout << "============================================================"
			  << "====================\n";
	runConstructorTests(theOutput);
	std::cout << "                 |----Running Assignment Tests-----|\n";
	std::cout << "Original:\t\t\tDump:\t\t\t\t\tResults:\n";
	std::cout << "============================================================"
			  << "====================\n";
	runAssignmentTests(theOutput);
	std::cout << "                 |----Running Conversion Tests-----|\n";
	std::cout << "Original:\t\t\tDump:\t\t\t\t\tResults:\n";
	std::cout << "============================================================"
			  << "====================\n";
	runConversionTests(theOutput);
	std::cout << "          |-----Running Function Tests------|\n";
	runFunctionTests(theOutput);
	std::cout << "\t                    |-Running Encoding/Decoding Tests-|\n";
	runEncodeDecodeTests(theOutput);
	
}
#endif /* Assignment2Tests_h */