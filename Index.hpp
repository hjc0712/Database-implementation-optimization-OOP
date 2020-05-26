#include <iostream>
#include "Value.hpp"
#include "Storage.hpp"

namespace ECE141 {
using IndexType = std::map<Value, uint32_t>; //c++ typedef...
	class Index {
	public:
        Index() {};
        Index(const std::string &aField, uint32_t aTableId, DataType aKeyType): field(aField), tableId(aTableId), keyType(aKeyType) {full = 0; nextBlockNum = 0;}
        Index(Block &aBlock, uint32_t aBlockNum);  //decode
        Index(Index &previousIndex);


        Index&		addKeyValue(const Value &aKey, uint32_t aValue);
        Index&		removeKeyValue(const Value &aKey);
        bool		contains(const Value &aKey);
        uint32_t	getValue(const Value &aKey);
        int         getBlockNum() {return blockNum;}
        void        setBlockNum(int aBlockNum) {blockNum = aBlockNum;}
        int         getNextBlockNum() {return nextBlockNum;}
        void        setNextBlockNum(int aBlockNum) {nextBlockNum = aBlockNum;}
        bool        hasNextBlockNum() {return nextBlockNum>blockNum;}
        bool        isFull() {return full;}
        IndexType   getIndex() {return index;}
        
        
        operator  Block();  //encode
        Index& operator = (Index anIndex);
        Index& operator = (Index* anIndex);
        
    
    protected:
        IndexType	index;
        std::string	field;    //name of the field being indexed
        bool        full;
        DataType	keyType;  //what Valuse datatype are we using for this field?
        uint32_t	tableId; //hash
        uint32_t    blockNum;
        uint32_t    nextBlockNum;
        int         size = 100;
    };
    
}
