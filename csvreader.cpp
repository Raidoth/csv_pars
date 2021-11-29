#include"csvreader.h"
#include<string>
#include<iostream>
#include<vector>
#include<fstream>

//#define TEST


using namespace std;


int main(int argc, char **argv){
    string name_file;
    string file_line;
    string file_tmp;
    vector<string> colomn_name;
    vector<string> row_name;

    vector<csv_s> vec_table;
    if(argc == 2) {
        csv_s tmp_csv;
        name_file = argv[1];
        ifstream file(name_file);
        if(!file) {
            cout << name_file << ": open error\n";
        } else {
            #ifdef TEST
            cout << name_file << ": file open\n";
            #endif // TEST

        }
        int count_all_comma=0;
        unsigned int row=0; //y
        while(file >> file_tmp) {
            int size_line = file_tmp.size();
            unsigned int count_comma = 0;//x
            for(int i = 0;i<size_line;i++) {
                if(count_comma==0&&row==0&&file_tmp[0]!=',') {
                    cout<<"Error. Wrong input\n";
                    return -5;
                }
                if(file_tmp[i]!=C_COMMA) {
                    file_line+=file_tmp[i];
                }
                if(file_tmp[i]==C_COMMA) {
                    if(row==0) {
                        colomn_name.push_back(file_line);
                    }
                    if(count_comma==0) {
                        row_name.push_back(file_line);
                    }
                    tmp_csv= {file_line,row,count_comma};
                    vec_table.push_back(tmp_csv);
#ifdef TEST
                    cout<<file_line << " ";
#endif // TEST
                    count_comma++;
                    count_all_comma++;
                    file_line.clear();
                }
                if(i == size_line-1) {
                    if(row==0) {
                        colomn_name.push_back(file_line);
                    }
                    tmp_csv= {file_line,row,count_comma};
                    vec_table.push_back(tmp_csv);
#ifdef TEST
                    cout<<file_line << " ";
#endif // TEST
                    file_line.clear();
                }
            }
            row++;
#ifdef TEST
            cout << endl;
#endif // TEST

        }
        for(unsigned int i = 0; i<colomn_name.size(); i++) {
            for(unsigned int j = i+1; j<colomn_name.size(); j++) {
            if(colomn_name[i]==colomn_name[j]){
            cout<<"Error. Duplicate name colomn\n";
            return 10;
            }
        }
        }

         for(unsigned int i = 0; i<row_name.size(); i++) {
            for(unsigned int j = i+1; j<row_name.size(); j++) {
            if(row_name[i]==row_name[j]){
            cout<<"Error. Duplicate number row\n";
            return 10;
            }
        }
        }
#ifdef TEST
        cout<<"NAME COLOMN\n";

        for(int i = 0; i<colomn_name.size(); i++) {

            cout<<colomn_name.at(i)<<endl;
        }
        cout<<"NAME ROWS\n";

        for(int i = 0; i<row_name.size(); i++) {

            cout<<row_name.at(i)<<endl;
        }
#endif // TEST


//cout<<m.at(10).pos_x<<" "<<m.at(3).pos_y<<endl;
        /*
        for(int i = 0;i<m.size();i++){
        int s=1;
        string first_val;
        string second_val;
        string tmp;
        if(m.at(i).value[0]=='='){
            while(s<m.at(i).value.size()){

            if(m.at(i).value[s]=='+'){
                first_val=tmp;
                tmp.clear();
                s++;
                continue;
            }

            tmp+=m.at(i).value[s];
            s++;
            }
            second_val=tmp;
            tmp.clear();
            cout<<"FIRST VAL "<< first_val <<" SECOND VAL "<<second_val<<endl;
            findValCsv(m,first_val,colomn);
        }

        cout<<"x: "<<m.at(i).pos_x << " y: "<< m.at(i).pos_y<<" value: "<<m.at(i).value <<endl;



        }
        */
#ifdef TEST
        cout<<"\n++++++++++++++++++++CHANGE STRUCT++++++++++++++++++++++\n"<<endl;
#endif // TEST
        vector<new_csv_s> new_vec_table;

        new_csv_s new_vec_tmp;
        for(unsigned int i = 0;i<vec_table.size();i++) {
            if(vec_table.at(i).pos_y!=0&&vec_table.at(i).pos_x!=0) {
                string pos_x;
                string pos_y;
                for(unsigned int j = 0;j<vec_table.size();j++) {
                    if(vec_table.at(j).pos_y==0&&vec_table.at(j).pos_x==vec_table.at(i).pos_x) {
                        pos_x=vec_table.at(j).value;
                    }
                    if(vec_table.at(j).pos_x==0&&vec_table.at(j).pos_y==vec_table.at(i).pos_y) {
                        pos_y=vec_table.at(j).value;
                    }
                }

                new_vec_tmp= {pos_x,pos_y,vec_table.at(i).value};
                new_vec_table.push_back(new_vec_tmp);
#ifdef TEST
                cout<<pos_y<<" "<<pos_x<<" "<<vec_table.at(i).value<<endl;
#endif // TEST
            }
        }
#ifdef TEST
        int g = 0;
        while(g<new_vec_table.size()) {
            cout<<new_vec_table.at(g).pos_y<<new_vec_table.at(g).pos_x<<" "<<new_vec_table.at(g).value<<endl;
            g++;
        }
#endif // TEST
        char operations;
        for(unsigned int i = 0; i<new_vec_table.size(); i++) {
            string first_val;
            string tmp_val;
            string second_val;
            unsigned int s = 1;
            if(new_vec_table[i].value[0]==C_EQUAL) {
                while(s<new_vec_table[i].value.size()) {

                    if(new_vec_table[i].value[s]==C_PLUS) {
                        operations=C_PLUS;
                        first_val=tmp_val;
                        tmp_val.clear();
                        #ifdef TEST
                        cout<<first_val;
                        #endif // TEST
                        s++;
                        continue;
                    } else if(new_vec_table[i].value[s]==C_MINUS) {
                        operations=C_MINUS;
                        first_val=tmp_val;
                        tmp_val.clear();
                        #ifdef TEST
                        cout<<first_val;
                        #endif // TEST
                        s++;
                        continue;
                    } else if(new_vec_table[i].value[s]==C_MULT) {
                        operations=C_MULT;
                        first_val=tmp_val;
                        tmp_val.clear();
                        #ifdef TEST
                        cout<<first_val;
                        #endif // TEST
                        s++;
                        continue;
                    } else if(new_vec_table[i].value[s]==C_DIV) {
                        operations=C_DIV;
                        first_val=tmp_val;
                        tmp_val.clear();
                        #ifdef TEST
                        cout<<first_val;
                        #endif // TEST
                        s++;
                        continue;
                    }
                    tmp_val+=new_vec_table[i].value[s];
                    s++;
                }
                second_val=tmp_val;
                if(!isdigit(first_val[0])) {
                    string num1 = calcValInTabl(new_vec_table,first_val);
                    string num2 = calcValInTabl(new_vec_table,second_val);
                    new_vec_table[i].value=calcul(operations,num1,num2);
                    unsigned int row;
                    unsigned int colomn;
                    for(unsigned int j = 0; j<row_name.size(); j++) {
                        if(new_vec_table[i].pos_x==row_name[j]) {
                            row=j;
                            break;
                        }
                    }
                    for(unsigned int j = 0; j<colomn_name.size(); j++) {
                        if(new_vec_table[i].pos_y==colomn_name[j]) {
                            colomn=j;
                            break;
                        }
                    }
                    for(unsigned int j = 0;j<vec_table.size();j++) {
                        if(vec_table[j].pos_x==row&&vec_table[j].pos_y==colomn) {
                            vec_table[j].value=new_vec_table[i].value;
                            break;
                        }
                    }

                } else {
                    new_vec_table[i].value=calcul(operations,first_val,second_val);
                    unsigned int row;
                    unsigned int colomn;
                    for(unsigned int j = 0; j<row_name.size(); j++) {
                        if(new_vec_table[i].pos_x==row_name[j]) {
                            row=j;
                            break;
                        }
                    }
                    for(unsigned int j = 0; j<colomn_name.size(); j++) {
                        if(new_vec_table[i].pos_y==colomn_name[j]) {
                            colomn=j;
                            break;
                        }
                    }
                    for(unsigned int j = 0;j<vec_table.size();j++) {
                        if(vec_table[j].pos_x==row&&vec_table[j].pos_y==colomn) {
                            vec_table[j].value=new_vec_table[i].value;
                            break;
                        }
                    }
                }
            }

        }
#ifdef TEST
        g = 0;
        cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
        while(g<new_vec_table.size()) {
            cout<<new_vec_table.at(g).pos_y<<new_vec_table.at(g).pos_x<<" "<<new_vec_table.at(g).value<<endl;
            g++;
        }
#endif // TEST
        for(unsigned int i = 0; i<row_name.size(); i++) {
            for(unsigned int j = 0; j<colomn_name.size(); j++) {
                for(unsigned int k = 0;k<vec_table.size();k++) {
                    if(vec_table[k].pos_y==j&&vec_table[k].pos_x==i) {
                        cout<<vec_table[k].value<<"\t";
                        break;
                    }
                }
            }
            cout<<endl;
        }
        #ifdef TEST
        for(int i = 0; i<vec_table.size(); i++) {
            cout<<"colomn " <<vec_table[i].pos_y <<" row "<<vec_table[i].pos_x<<" value "<<vec_table[i].value<<endl;
        }
        #endif // TEST
        /*
        int pp=0;
        for(int i = 0;i<ssS.size();i++){
        int s=1;
        string first_val;
        string second_val;
        string tmp;
        char operation;
        if(ssS[i].value[0]=='='){
        while(s<ssS[i].value.size()){
            if(ssS[i].value[s]=='+'){
                    operation='+';
                    first_val=tmp;
                    tmp.clear();
                    s++;
                    continue;
                }else if(ssS[i].value[s]=='-'){
                    operation='-';
                    first_val=tmp;
                    tmp.clear();
                    s++;
                    continue;
                }else if(ssS[i].value[s]=='*'){
                    operation='*';
                    first_val=tmp;
                    tmp.clear();
                    s++;
                    continue;
                }else if(ssS[i].value[s]=='/'){
                    operation='/';
                    first_val=tmp;
                    tmp.clear();
                    s++;
                    continue;
                }else{
                    return WRONG_INPUT;
                }

                tmp+=ssS[i].value[s];
                    s++;
        }
            second_val=tmp;
            tmp.clear();
            cout<<"DIGIT "<<isdigit(first_val[0])<<endl;
            if(0){
                ssS[i].value=calcul(operation,first_val,second_val);

            }else{
                ssS[i].value=findValCsv(ssS,first_val,colomn);

            }
        cout<<"HERE\n";
        }

        //cout<<ssS.at(i).pos_y<<" "<<ssS.at(i).pos_x<<" "<<ssS.at(i).value<<endl;

        }
        */
    }




}


string calcValInTabl(const vector<new_csv_s>& arr, const string& findVal){
    string first_search;
    string second_search;
    int size_val = findVal.size();
    string result;
    for(int i = 0;i<size_val;i++) {
        if(!isdigit(findVal[i])) {
            first_search+=findVal[i];
        } else {
            second_search+=findVal[i];
        }
    }

    int size_array = arr.size();

    for(int i = 0; i<size_array; i++) {
        if(arr[i].pos_y==first_search&&arr[i].pos_x==second_search) {
            result=arr[i].value;
        }

    }
    //cout<<"\nRESULT"<<result<<endl;
//cout<<"FIRST SEARCH "<<first_search<<" SECOND SEARCH " << second_search<<endl;

    return result;
}

string calcul(const char& operation, const string& val1,const string& val2){
    int value1 = atoi(val1.c_str());
    int value2 = atoi(val2.c_str());
    int result = 0;
    switch(operation) {
    case C_PLUS:
        result=value1+value2;
        break;
    case C_MINUS:
        result=value1-value2;
        break;
    case C_MULT:
        result = value1 * value2;
        break;
    case C_DIV:
        if(value2!=0) {
            result = value1/value2;
        } else {
            return "-5325";
        }
        break;
    }

    return to_string(result);
}
