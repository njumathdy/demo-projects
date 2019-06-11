#ifndef TEXTQUERY_H
#define TEXTQUERY_H

#include <vector>
#include <memory>
#include <set>
#include <map>
#include <string>
#include <fstream>

#include "QueryResult.h"

using namespace std;

class QueryResult;
class TextQuery {
public: 
    using line_no = vector<string>::size_type;
    TextQuery(ifstream&);
    QueryResult query(const string&) const;
    void display_map();

private: 
    shared_ptr<vector<string> > file;
    map<string, shared_ptr<set<line_no> > > wm;

    static string cleanup_str(const std::string&);
};

#endif