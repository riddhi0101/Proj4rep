
//
// Created by Dev Patel on 2019-04-13.
//
#include <iostream>
#include "StringUtils.h"
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <string>

namespace StringUtils{

    std::string Slice(const std::string &str, ssize_t start, ssize_t end){
        // Your code goes here
        int sli_start,sli_stop;
        sli_start = int(start);
        sli_stop = int(end);
        int slice_stride;
        if (sli_start > str.length() && sli_start> 0){
            return "";

        }
        else {
            if (sli_start < 0) {
                sli_start = (int) str.length() + sli_start;
            }
            if (sli_stop < 0) {
                sli_stop = (int) str.length() + sli_stop;
            }
            slice_stride = sli_stop - sli_start;
            return str.substr(sli_start, slice_stride);
        }

    }

    std::string Capitalize(const std::string &str){
        // Your code goes here
        std::string Ret;
        for(auto Ch : str){
            Ret += tolower(Ch);
        }
        Ret[0] = toupper(Ret[0]);
        return Ret;
    }

    std::string Title(const std::string &str){
        // Your code goes here
        std::string Ret;
        for(auto Ch : str){
            Ret += tolower(Ch);
        }
        for (int i = 0; i < (int)Ret.size();i++) {

            if (i==0 || !isalpha(Ret[i-1])) {
                Ret[i]= toupper(Ret[i]);

            }
        }
        return Ret;
    }

    std::string LStrip(const std::string &str){
        // Your code goes here
        std::string Ret;
        Ret = str;
        for (int i=0; i < (int)str.size();i++){
            if (Ret[i] == ' '){
                continue;

            }
            else{
                //Ret = StringUtils::Slice(Ret,i,(int)Ret.length());
                Ret = Ret.substr(i,(int)Ret.length());
                break;
            }
        }
        return Ret;
    }

    std::string RStrip(const std::string &str){
        // Your code goes here
        std::string Ret;
        Ret = str;
        for (int i=((int)str.length()-1); i >=0;i--) {
            if (!isalpha(Ret[i])) {
                continue;
            }
            else {
                Ret = Ret.substr(0,i+1);
                return Ret;
            }

        }


    }

    std::string Strip(const std::string &str){
        // Your code goes here
        std::string Ret;
        Ret = str;
        Ret = StringUtils::RStrip(Ret);
        Ret = StringUtils::LStrip(Ret);
        //Ret = StringUtils::RStrip(StringUtils::LStrip(Ret));
        return Ret;
    }

    std::string Center(const std::string &str, int width, char fill){
        // Your code goes here
        std::string Ret;
        Ret = str;
        int remain_space;
        remain_space = width - (int)Ret.length();
        std::string stuff1(remain_space/2, fill);

        if (remain_space %2 == 0) {
            //std::string stuff2(int(Ret.length())-int(stuff1.length()),fill);
            Ret = stuff1 + Ret + stuff1;
        }
        else {
            std::string stuff2((int)stuff1.length()+1,fill);
            Ret = ((stuff1) + Ret + stuff2);
        }
        return Ret;
    }

    std::string LJust(const std::string &str, int width, char fill){
        // Your code goes here
        std::string Ret;
        int remain_space;
        Ret = str;
        remain_space = width - (int)Ret.length();
        std::string stuff1(remain_space, fill);
        Ret = Ret + stuff1;
        return Ret;
    }

    std::string RJust(const std::string &str, int width, char fill){
        // Your code goes here
        std::string Ret;
        int remain_space;
        Ret = str;
        remain_space = width - (int)Ret.length();
        std::string stuff1(remain_space, fill);
        Ret = stuff1 + Ret;
        return Ret;
    }

    std::string Replace(const std::string &str, const std::string &old, const std::string &rep) {
        // Your code goes here
        std::string Ret;
        Ret = str;
        size_t pos = Ret.find(old);

        while( pos <= Ret.length()){
            Ret.replace(pos, old.size(), rep);
            pos =Ret.find(old, pos + rep.size());
        }
        return Ret;
    }


    std::vector< std::string > Split(const std::string &work, const std::string & delim) {
        // Your code goes here
        std::vector<std::string> flds;

        //if (!flds.empty()) flds.clear();  // empty vector if necessary
        //string work = data();
        std::string buf = "";
        int i = 0;
        if (work[0] == delim[0]) {
            flds.push_back("");
            i++;
        }
        if (i>=0){

            while (i < work.length()) {
                if (work[i] == '!'){
                    buf += work[i];
                    break;

                }
                else if (work[i] != delim[0] && (isalpha(work[i]))) {
                    buf += work[i];
                    //else if (rep == 1) {
                    //flds.push_back(buf);
                    //buf = "";
                }
                else if (buf.length() > 0) {
                    flds.push_back(buf);
                    buf = "";
                }
                i++;
            }
            if (!buf.empty()) {
                flds.push_back(buf);
            }
        }


        return flds;
    }


    std::string Join(const std::string &str, const std::vector< std::string > &vect) {
        // Your code goes here
        std::string Ret;
        Ret = "";
        for (auto Ch : vect) {
            if (Ch == "") {
                continue;
            } else if (Ret == "") {
                Ret = str + Ch;
            } else {
                Ret = Ret + str + Ch;
            }
        }
        if (Ret[0] == ' ') {
            Ret = Ret.substr(1, Ret.length());
        }
        return Ret;
    }

    std::string ExpandTabs(const std::string &str, int tabsize) {
        // Your code goes here
        std::string Ret;
        Ret = str;
        //int pos = 0;
        std::string result;
        std::string stuff1;
        std::string sto;
        sto = '\t';
        int w;
        int pos = 0;
        result = "";
        int flag = 1;
        for (int i = 0; i < Ret.length(); i++) {
            if (Ret[i]== sto[0]) {
                if(flag==1) {
                    w = tabsize - (pos % tabsize);
                    w = w+1;
                    std::string stuff1(w, ' ');
                    result += stuff1;
                    pos = 0;
                    flag+=1;
                }
                else {
                    w = tabsize - (pos % tabsize);
                    std::string stuff1(w, ' ');
                    result += stuff1;
                    pos = 0;
                }
                //i++;
            }
            else {
                pos += 1;
                result += Ret[i];
            }

        }
        return result;
    }



    int EditDistance(const std::string &s1, const std::string &s2, bool ignorecase){
        // Your code goes here
        if (ignorecase == true){
            return 0;
        }
        else{

            const size_t m(s1.size());
            const size_t n(s2.size());

            if( m==0 ) return n;
            if( n==0 ) return m;

            size_t *costs = new size_t[n + 1];

            for( size_t k=0; k<=n; k++ ) costs[k] = k;

            size_t i = 0;
            for ( std::string::const_iterator it1 = s1.begin(); it1 != s1.end(); ++it1, ++i ){
                costs[0] = i+1;
                size_t corner = i;

                size_t j = 0;
                for ( std::string::const_iterator it2 = s2.begin(); it2 != s2.end(); ++it2, ++j ){
                    size_t upper = costs[j+1];
                    if( *it1 == *it2 ){
                        costs[j+1] = corner;
                    }
                    else{
                        size_t t(upper<corner?upper:corner);
                        costs[j+1] = (costs[j]<t?costs[j]:t)+1;
                    }
                    corner = upper;
                }
            }

            size_t result = costs[n];
            delete [] costs;

            return result;
        }


    }
}


