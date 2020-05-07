//
//  Tokenizer.hpp
//  Database
//
//  Created by rick gessner on 3/19/19.
//  Copyright © 2019 rick gessner. All rights reserved.
//

#ifndef Tokenizer_hpp
#define Tokenizer_hpp

#include <stdio.h>
#include <sstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "keywords.hpp"


namespace ECE141 {
  
  using callback = bool(char aChar);
  
  //Delineates different types of tokens our system will encounter. You may need to add more...
  enum class TokenType {
    apostrophe=1, colon, comma, equal, function, identifier, keyword, lbrace,
    lbracket, lparen, minus, number, operators, plus, rbrace, rbracket, rparen,
    semicolon, slash, star, string, unknown
  };
  static std::map<std::string, TokenType> tokeDictionary = {
    std::make_pair(",", TokenType::colon),
    std::make_pair(":", TokenType::comma),
    std::make_pair("=", TokenType::equal),
    std::make_pair("[", TokenType::lbrace),
    std::make_pair("]", TokenType::rbrace),
    std::make_pair("(", TokenType::lparen),
    std::make_pair(")", TokenType::rparen),
    std::make_pair("{", TokenType::lbracket),
    std::make_pair("}", TokenType::rbracket),
    std::make_pair(";", TokenType::semicolon),
    std::make_pair("*", TokenType::star),
    std::make_pair("/", TokenType::slash),
    std::make_pair("-", TokenType::minus),
    std::make_pair("+", TokenType::plus)
  };
  //Holds a given token, created when input (command line or script) is tokenized...
  struct Token {
    Token(TokenType aType=TokenType::unknown,std::string aString="",Keywords aKW=Keywords::unknown) :
    type(aType), keyword(aKW), data(aString) {}
    
    TokenType   type;       // This should catagorize infomation from smaller dictionaries.
    Keywords    keyword;    // This should be from a dictionary that holds all possible inputs.
    std::string data;
  };
  
  
  // USE: This class performs tokenizing for the sytsem --------------------
  
  class Tokenizer {
  public:
    Tokenizer(std::istream &anInputStream);
    
    virtual StatusResult  tokenize();
    virtual Token&        tokenAt(int anOffset);
    size_t                size() {return tokens.size();}
    
    virtual void          restart() {index=0;}
    virtual bool          more() {return index<size();}
    virtual bool          next(int anOffset=1);
    virtual Token&        peek(int anOffset=1);
    virtual Token&        current();
    
  protected:
    
    std::vector<Token>    tokens;
    std::istream          &input;
    int                   index;
  };
  
}

#endif /* Tokenizer_hpp */
