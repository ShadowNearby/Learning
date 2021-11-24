#include<iostream>
#include<string>
#include<iomanip>
#include<sstream>
using namespace std;
int main(){
    string text;
    getline(cin,text);
    for(int i=0;i<int(text.size());i++){
        if(text[i]>='A'&&text[i]<='Z') {
            text[i]=text[i]-'A'+'a';}
        if(!(text[i]>='A'&&text[i]<='Z'||text[i]>='a'&&text[i]<='z')) text[i]=' ';
    }
    stringstream ss(text);
    string word[1000];
    int time[1000],i=0;
    while(ss >> word[i]){
        time[i]=1;
        for(int j=0;j<i;j++){
            if (word[i]==word[j]) {
                time[j]++;
                time[i]=0;
                break;
        }
        }
        i++;
    }
    for(int j=0;j<i;j++){
        if(time[j]==0) continue;
        cout << word[j] << "\t" << time[j]<< endl;
    }
    return 0;
}