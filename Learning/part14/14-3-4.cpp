#include <iostream>
using namespace std;
int getlen(const char *string);
int compare(char a, char b);
class String{
private:
    char *str;
    int capicity = 0;
    int length = 0;
    void doublespace();
    void append(const char ch);
public:
    String(){
        str = new char[1];
        *(str) = '\0';
    }
    friend istream &operator>>(istream &is, String &a);
    friend ostream &operator<<(ostream &os, const String &a);
    void operator=(const char *s);
    void operator=(const String &string);
    String operator+(const String &string);
    void operator+=(const String &string);
    bool operator==(const String &string);
    bool operator>=(const String &string);
    bool operator<=(const String &string);
    bool operator>(const String &string);
    bool operator<(const String &string);
};
int getlen(const char *string){
    int i = 0;
    while(true){
        if(*(string + i) == '\0'){
            break;
        }
        ++i;
    }
    return i;
}
void String::doublespace(){
    char *tem = new char[capicity * 2 + 1];
    for (int i = 0; i < capicity; ++i){
        *(tem + i) = *(str + i);
    }
    str[capicity] = '\0';
    capicity *= 2;
    delete[] tem;
    tem = NULL;
}
void String::append(const char ch){
    if(capicity == 0){
        str = new char[2];
        str[0] = ch;
        str[1] = '\0';
        ++capicity;
        ++length;
        return;
    }
    if(length == capicity){
        doublespace();
    }
    *(str + length) = ch;
    *(str + length + 1) = '\0';
    ++length;
}
istream &operator>>(istream &is, String &a){
    char k[100];
    is >> k;
    a.length = a.capicity = getlen(k);
    a.str = new char[a.capicity+1];
    int i = 0;
    for (i = 0; i < a.length; ++i){
        a.str[i] = k[i];
    }
    a.str[a.capicity] = '\0';
    return is;
}
ostream &operator<<(ostream &os, const String &a){
    os << a.str;
    return os;
}
void String::operator=(const char *s){
    capicity = length = getlen(s);
    str = new char[capicity + 1];
    for (int i = 0; i < capicity; ++i){
        str[i] = s[i];
    }
    str[length] = '\0';
}
void String::operator=(const String &string){
    capicity = string.capicity;
    length = string.length;
    str = new char[capicity + 1];
    for (int i = 0; i < capicity; ++i){
        str[i] = string.str[i];
    }
    str[length] = '\0';
}
String String::operator+(const String &string){
    String ans;
    ans = *this;
    int i = 0;
    for (i = 0; i < string.length; ++i){
        ans.append(string.str[i]);
    }
    return ans;
}
void String::operator+=(const String &string){
    int i = 0;
    for (i = 0; i < string.length; ++i){
        append(string.str[i]);
    }
}
bool String::operator==(const String &string){
    if(this->length != string.length){
        return false;
    }
    else{
        for (int i = 0; i < this->length; ++i){
            if(this->str[i] != string.str[i]){
                return false;
            }
        }
    }
    return true;
}
int compare(char a,char b){
    if(a == b){
        return 0;
    }
    if(a <= '9' && a >= '0' && b <= '9' && b >= '0'){
        if(a > b) 
            return 1;
        else
            return -1;
    }
    else if(a <= 'z' && a >= 'a' && b <= 'z' && b >= 'a'){
        if(a > b) 
            return 1;
        else
            return -1;
    }
    else if(a <= 'Z' && a >= 'A' && b <= 'Z' && b >= 'A'){
        if(a > b) 
            return 1;
        else
            return -1;
    }
    else if(a <= 'z' && a >= 'a' && b <= 'Z' && b >= 'A'){
        a = a + 'A' - 'a';
        if(a >= b) 
            return 1;
        else
            return -1;
    }
    else if(a <= 'Z' && a >= 'A' && b <= 'z' && b >= 'a'){
        b = b + 'A' - 'a';
        if(a > b) 
            return 1;
        else
            return -1;
    }
    else {
        if(a > b){
            return 1;
        }
        else
            return -1;
    }
}
bool String::operator>(const String &string){
    if(*this == string){
        return false;
    }
    int len = min(this->length, string.length);
    for (int i = 0; i < len; ++i){
        if (compare(this->str[i], string.str[i]) == 0){
            continue;
        }
        else if(compare(this->str[i], string.str[i]) == 1){
            return true;
        }
        else
            return false;
    }
    if(len == string.length){
        return true;
    }
    else
        return false;
}
bool String::operator<(const String &string){
    if(*this > string || *this == string){
        return false;
    }
    else
        return true;
}
bool String::operator>=(const String &string){
    if(*this < string){
        return false;
    }
    else
        return true;
}
bool String::operator<=(const String &string){
    if(*this > string){
        return false;
    }
    else
        return true;
}

int main(){
    String str, str1;
    str = "abcd";
    str1 = "bed";
    cout << str << endl;
    cout << str1 << endl;
    cout << (str > str1) << endl;
}