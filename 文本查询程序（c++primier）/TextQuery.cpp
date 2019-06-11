#include "TextQuery.h"

#include <cstddef>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>
#include <utility>

using namespace std;

typedef map<string, shared_ptr<set<TextQuery::line_no> > > wmType;
typedef wmType::const_iterator wmIter;
typedef shared_ptr<set<TextQuery::line_no> > lineType;
typedef set<TextQuery::line_no>::const_iterator lineIter;

// 构造函数，读取输入文件
TextQuery::TextQuery(ifstream &is): file(new vector<string>) {
    string text;
    while(getline(is, text)) {
        file -> push_back(text);
        int n = file -> size() - 1;
        istringstream line(text);
        string word;
        while(line >> word) { // 遍历每行的每个单词
            word = cleanup_str(word);
            lineType &lines = wm[word];
            if(!lines) // 该单词第一次出现
                lines.reset(new set<line_no>);
            lines -> insert(n);
        }
    }
}

string TextQuery::cleanup_str(const string &word) {
    string ret;
    for(string::const_iterator it = word.begin(); it != word.end(); ++it) {
        if(!ispunct(*it)) // 检查是否是标点符号
            ret += tolower(*it);
    }
    return ret;
}

QueryResult TextQuery::query(const string &sought) const {
    static lineType nodata(new set<line_no>);

    wmIter loc = wm.find(cleanup_str(sought));

    if(loc == wm.end()) 
        return QueryResult(sought, nodata, file); // not found
    else 
        return QueryResult(sought, loc -> second, file);
}

ostream &print(ostream &os, const QueryResult &qr) {
    os << qr.sought << "occurs" << qr.lines -> size() << " "
       << make_plural(qr.lines -> size(), "time", "s") << endl;

    for(lineIter num = qr.lines -> begin(); num != qr.lines -> end(); ++num) 
        os << "\t(lint " << *num + 1 << ") " << *(qr.file -> begin() + *num) << endl;

    return os;
}

void TextQuery::display_map() {
    wmIter iter = wm.begin(), iter_end = wm.end();

    for(; iter != iter_end; ++iter) {
        cout << "word: " << iter -> first << " {";

        lineType text_locs = iter -> second;
        lineIter loc_iter = text_locs -> begin(), loc_iter_end = text_locs -> end();

        while(loc_iter != loc_iter_end) {
            cout << *loc_iter;

            if(++loc_iter != loc_iter_end)
                cout << ", ";
        }
        cout << "}\n";
    }
    cout << endl;
}


