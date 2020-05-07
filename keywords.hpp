//
//  keywords.hpp
//  Database
//
//  Created by rick gessner on 3/21/19.
//  Copyright © 2019 rick gessner. All rights reserved.
//

#ifndef keywords_h
#define keywords_h

#include <string>
#include <map>
#include "Errors.hpp"
//#include "Tokenizer.hpp"

namespace ECE141 {
  //This enum defines each of the keywords we need to handle across our multiple languages...
  enum class Keywords {
    //Keywords
    add_kw=1, all_kw, alter_kw, auto_increment_kw,
    by_kw, char_kw, create_kw,
    database_kw, databases_kw, datetime_kw, decimal_kw, delete_kw,
    describe_kw, distinct_kw, double_kw, drop_kw, explain_kw,
    float_kw, foreign_kw, from_kw, group_kw, help_kw,
    in_kw, insert_kw, integer_kw, into_kw, key_kw,
    null_kw, order_kw, primary_kw, quit_kw,
    references_kw, select_kw, set_kw, show_kw, sum_kw,
    unique_kw, update_kw, use_kw,
    values_kw, varchar_kw, version_kw, where_kw,
    //Operators
    and_op, between_op, equal_op, gt_op, gte_op, lt_op, lte_op,
    nor_op, not_op, notequal_op, or_op,
    //Functions
    avg_f, count_f, max_f, min_f,
    //Identifires
    table_i, tables_i, row_i, rows_i, column_i, columns_i,
    //Unknown
    unknown
  };

  //This map binds a keyword string with a Keyword (token)...
  static std::map<std::string,  Keywords> kDictionary = {
    std::make_pair("add",            Keywords::add_kw),
    std::make_pair("all",            Keywords::all_kw),
    std::make_pair("alter",          Keywords::alter_kw),
    std::make_pair("auto_increment", Keywords::auto_increment_kw),
    std::make_pair("by",             Keywords::by_kw),
    std::make_pair("char",           Keywords::char_kw),
    std::make_pair("create",         Keywords::create_kw),
    std::make_pair("database",       Keywords::database_kw),
    std::make_pair("databases",      Keywords::databases_kw),
    std::make_pair("datetime",       Keywords::datetime_kw),
    std::make_pair("decimal",        Keywords::decimal_kw),
    std::make_pair("delete",         Keywords::delete_kw),
    std::make_pair("describe",       Keywords::describe_kw),
    std::make_pair("distinct",       Keywords::distinct_kw),
    std::make_pair("double",         Keywords::double_kw),
    std::make_pair("drop",           Keywords::drop_kw),
    std::make_pair("explain",        Keywords::explain_kw),
    std::make_pair("float",          Keywords::float_kw),
    std::make_pair("foreign",        Keywords::foreign_kw),
    std::make_pair("from",           Keywords::from_kw),
    std::make_pair("group",          Keywords::group_kw),
    std::make_pair("help",           Keywords::help_kw),
    std::make_pair("in",             Keywords::in_kw),
    std::make_pair("insert",         Keywords::insert_kw),
    std::make_pair("integer",        Keywords::integer_kw),
    std::make_pair("into",           Keywords::into_kw),
    std::make_pair("key",            Keywords::key_kw),
    std::make_pair("null",           Keywords::null_kw),
    std::make_pair("order",          Keywords::order_kw),
    std::make_pair("primary",        Keywords::primary_kw),
    std::make_pair("quit",           Keywords::quit_kw),
    std::make_pair("references",     Keywords::references_kw),
    std::make_pair("select",         Keywords::select_kw),
    std::make_pair("set",            Keywords::set_kw),
    std::make_pair("show",           Keywords::show_kw),
    std::make_pair("sum",            Keywords::sum_kw),
    std::make_pair("unique",         Keywords::unique_kw),
    std::make_pair("update",         Keywords::update_kw),
    std::make_pair("use",            Keywords::use_kw),
    std::make_pair("values",         Keywords::values_kw),
    std::make_pair("varchar",        Keywords::varchar_kw),
    std::make_pair("version",        Keywords::version_kw),
    std::make_pair("where",          Keywords::where_kw),

    std::make_pair("and",            Keywords::and_op),
    std::make_pair("between",        Keywords::between_op),
    std::make_pair("not",            Keywords::not_op),
    std::make_pair("or",             Keywords::or_op),

    std::make_pair("avg",            Keywords::avg_f),
    std::make_pair("count",          Keywords::count_f),
    std::make_pair("max",            Keywords::max_f),
    std::make_pair("min",            Keywords::min_f),

    std::make_pair("column",         Keywords::column_i),
    std::make_pair("table",          Keywords::table_i),
  };


  //a list of known functions...
  static std::map<std::string,int> gFunctions = {
    std::make_pair("avg", 10),
    std::make_pair("count", 20),
    std::make_pair("max", 30),
    std::make_pair("min", 40)
  };
    
}
 
#endif /* keywords_h */
