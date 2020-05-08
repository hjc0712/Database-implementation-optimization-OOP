//
//  main.cpp
//  Database1
//
//  Created by rick gessner on 3/17/19.
//  Copyright © 2019 rick gessner. All rights reserved.
//

#include "Assignment2Tests.hpp"
#include "CommandProcessor.hpp"
#include "Tokenizer.hpp"
#include <iostream>
#include <sstream>
#include <bitset>
#include <string>

typedef unsigned char uchar;
//float bytesToFloat(uchar b0, uchar b1, uchar b2, uchar b3){
//    float output;
//    *((uchar*)(&output) + 3) = b0;
//    *((uchar*)(&output) + 2) = b1;
//    *((uchar*)(&output) + 1) = b2;
//    *((uchar*)(&output) + 0) = b3;
//    return output;
//}


int main(int argc, const char * argv[]) {
  ECE141::CommandProcessor  theProcessor;  //only version, help, quit
  ECE141::StatusResult      theResult{};   //
  
  if(argc>1) {
    //in a future assignment, you'll add code to process a script file. Ignore for now...
  }
  else {
    runAssignment2Tests();
    std::string theUserInput;
    bool running=true;
    
    std::cout << std::endl << "> ";
//      std::string s = std::bitset< 16 >( 12345 ).to_string(); // string conversion
//
//      std::cout << std::bitset< 8 >( 231 ) << ' '; // direct output
//      char haha[16];
//      haha[0]=std::bitset< 8 >( 231 );
//      char str[] = "memmove can be very useful......";
//      memmove (str+20,str+15,5);
//      puts (str);
      
//      std::bitset< 64 > input;
//      std::cin >> input;
//      unsigned long ul = input.to_ulong();
      
//      char data[16];
//      int offset = 2;
//      unsigned char bytes[4];
//      float pi = 3.14159;
//      *(float*)(bytes) = pi;  // convert float to bytes
//      printf("bytes = [ 0x%.2x, 0x%.2x, 0x%.2x, 0x%.2x ]\r\n", bytes[0], bytes[1], bytes[2], bytes[3]);
//
//      char sbytes[4];
//      std::memcpy(sbytes,bytes,4);
//      std::strncpy ( data+offset, sbytes, 4);
////      std::cout<<data<<std::endl;
//      printf("[ 0x%.2x, 0x%.2x, 0x%.2x, 0x%.2x ]\r\n", data[0], data[1], data[2], data[3]);
//      unsigned char b[4]={0x3e,0xaa,0xaa,0xab};
////      int curInt = b[0] << 24 | (b[1] & 0xff) << 16 | (b[2] & 0xff) << 8 | (b[3] & 0xff);
////      int slen = b[0] & 0xff;
////      std::cout<<slen;
//       double curFlo = bytesToFloat(b[0],b[1],b[2],b[3]);
//       std::cout<<curFlo;
      
      //      int n=1017;
//      unsigned char bytes[4];
//      bytes[0] = (n >> 24) & 0xFF;
//      bytes[1] = (n >> 16) & 0xFF;
//      bytes[2] = (n >> 8) & 0xFF;
//      bytes[3] = n & 0xFF;
//      printf("bytes = [ 0x%.2x, 0x%.2x, 0x%.2x, 0x%.2x ]\r\n", bytes[0], bytes[1], bytes[2], bytes[3]);

      
    while (running && std::getline(std::cin, theUserInput)) {
      if(theUserInput.length()) {
        std::stringstream theStream(theUserInput); //creates a stingstream type
        ECE141::Tokenizer theTokenizer(theStream); //initializes a Tokenizer with the stream
        theTokenizer.tokenize();                   //should parse the stream into tokens returns StatusResult
        theResult=theProcessor.processInput(theTokenizer);
      }
      if(ECE141::userTerminated==theResult.code)
        running=false;
      else std::cout << std::endl << "> ";
    }
  }
  
  return 0;
}
