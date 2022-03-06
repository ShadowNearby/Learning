#include<iostream>
#include<string>
using namespace std;
bool judge(char a){
    if(a<='z'&&a>='a') return true;
    else if(a<='Z'&&a>='A') return true;
    else if(a<='9'&&a>='0') return true;
    else if(a==','||a=='.'||a=='"'||a==' '||a=='@'||a=='#'||a=='$') return true;
    else return false;
}
bool judge2(char a){
    if(a==' '||a=='@'||a=='#'||a=='$'||a==0) return true;
    else return false;
}
int main(void){
    string str,str2,str3;
    getline(cin,str);
    str3 = str;
    int len=int(str.size()),i=0;
    if(len>20) {
        cout << "输入不符合要求";
        return 0;
    }
    while(i<len){
        if(!judge(str[i])) {
            cout << "输入不符合要求" ;
            return 0;
        }
        if(str[i]<='Z'&&str[i]>='A') str2+=char(str[i]-'A'+'a');
        else str2+=str[i];
        i++;
    }
    for(int i = 0;i < len ;i++){
        if(str[i]=='#'||str[i]=='$'||str[i]=='@') {
            str2[i]=0;
        }
    }
    for(int j = 0; j < 10 ;j++){
        int temi=0;
        for(int i = 0;i < len ;i++){
            if(str2[i]=='l') {
                temi = i;
                for(int ti = temi + 1 ; ti < len ;ti++){
                    if(judge2(str2[ti])) continue;
                    if(str2[ti]=='4'){
                        for(int k = ti;k>=temi;k--){
                            str2[k]=0;
                            str3[k]=0;
                        }
                        i=ti;
                        break;
                    }
                    else if(str2[ti]!='4') {
                        i = ti;
                        break;
                    }
                }
            }
        }    
            for(int i = 0;i < len ;i++){
                if(str2[i]=='f') {
                    temi = i;
                    for(int ti = temi + 1 ; ti < len ;ti++){
                        if(judge2(str2[ti])) continue;
                        if(str2[ti]=='d'){
                            for(int k = ti;k>=temi;k--){
                            str2[k]=0;
                            str3[k]=0;
                        }
                            i=ti;
                            break;
                        }
                        else if(str2[ti]!='d') {
                            i = ti;
                            break;
                        }
                    }
                }
            }
            for(int i = 0;i < len ;i++){
                if(str2[i]=='d') {
                    temi = i;
                    for(int ti = temi + 1 ; ti < len ;ti++){
                        if(judge2(str2[ti])) continue;
                        if(str2[ti]=='2'){
                            int tem = ti;
                            for(int t = tem + 1; t < len ;t++){
                                if(judge2(str2[t])) continue;
                                if(str2[t]=='6'){
                                    for(int k = t;k>=temi;k--){
                                    str2[k]=0;
                                    str3[k]=0;
                                    }
                                    ti=t;
                                    break;
                                }
                                else if(str[t]!='6'){
                                    ti=t;
                                    break;
                                }
                            }
                        }
                        else if(str2[ti]!='2') {
                            i = ti;
                            break;
                        }
                    }
                }
            }
    }
    for(int i = 0; i<str3.size() ;i++){
        
        if(str3[i]!=0){
            cout << str3[i];
        }
    }
    //cout << str2 <<endl <<str3 <<endl;
}
/*input:L^67d*
output:输入不符合要求

样例2
input:@#$,."
output:@#$,."

样例3
input:# f@#$$#d #
output:#  #
请注意样例3中的空格，在过滤掉fd之后空格应该还有两个。

样例4
input:f$#d26
output:26

样例5
input:Ld264
output:
样例5应该没有任何输出

样例6
input:12345678901234567890123
output:输入不符合要求

样例7
input:f @#$,d
output:f @#$,d*/