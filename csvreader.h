#ifndef CSVREADER_H_INCLUDED
#define CSVREADER_H_INCLUDED
#include<string>
#include<vector>

#define C_COMMA ','
#define C_EQUAL '='
#define C_PLUS '+'
#define C_MINUS '-'
#define C_MULT '*'
#define C_DIV '/'
using namespace std;
typedef struct {
    string value;
    unsigned int pos_x;
    unsigned int pos_y;
} csv_s;
typedef struct {
    string pos_x;
    string pos_y;
    string value;
} new_csv_s;
string calcul(const char& operation, const string& val1,const string& val2);
string calcValInTabl(const vector<new_csv_s>& arr, const string& findVal);

#endif // CSVREADER_H_INCLUDED
