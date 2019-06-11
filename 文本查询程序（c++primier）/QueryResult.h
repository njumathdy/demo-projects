#ifndef QUERYRESULT_H
#define QUERYRESULT_H

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <set>

using namespace std;

class QueryResult {
friend ostream& print(ostream&, const QueryResult&);

public: 
    typedef vector<string>::size_type line_no;
	typedef set<line_no>::const_iterator line_it;
    QueryResult(string s, shared_ptr<set<line_no> > p, shared_ptr<vector<string> > f):
        sought(s), lines(p), file(f) {}

private: 
    string sought;
    shared_ptr<set<line_no> > lines;
    shared_ptr<vector<string> > file;
};

ostream &print(std::ostream&, const QueryResult&);
inline string make_plural(size_t ctr, const string &word, const string &ending) {
	return (ctr > 1) ? word + ending : word;
}

#endif