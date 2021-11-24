#include<iostream>
#include<string>
using namespace std;
bool ischar(char cha){
    if(cha>='a'&&cha<='z'||cha>='A'&&cha<='Z') return true;
    else return false;
}
int main(){
    int max=0,ansl,ansh,templow,temphigh;
    string b="",c="",d="",a="";    
    while(getline(cin,d)){
        c+=d;
        c+='\n';
    }
    for(int i=0;i<int(c.size());i++){
        if(c[i]<='Z'&&c[i]>='A') {
            a+=char(c[i]+'a'-'A');
            continue;
        }
        if(!(c[i]>='a'&&c[i]<='z')) a += char(0);
        else a+=c[i];
    }
    int low,high,len=int(a.size());
    for(int i=1;i<len;i++){
        if(!c[i]) continue;
        int ans=-1;
        low=i;
        high=i;
        while(1){
            while(!a[low]&&low>0) low--;
            if(low<0) break;
            while(!a[high]&&high<len) high++; 
            if(high>=len) break;
            if(a[low]!=a[high]) {
                break;
            }
            ans+=2;
            templow=low;temphigh=high;
            low--;
            high++;
        } 
        if(max<ans){
            max=ans;
            ansl=templow;
            ansh=temphigh;          
        }
    }
        for(int i=1;i<len;i++){
        if(!c[i]) continue;
        int ans=0;
        low=i;
        high=i+1;
        while(1){
            while(!a[low]&&low>0) low--;
            if(low<0) break;
            while(!a[high]&&high<len-1) high++; 
            if(high>=len) break;
            if(a[low]!=a[high]) {
                break;
            }
            ans+=2;
            templow=low;
            temphigh=high;
            low--;
            high++;
        } 
        if(max<ans){
            max=ans;
            ansl=templow;
            ansh=temphigh;        
        }
    }
    for(int j=ansl;j<=ansh;j++){
        b+=c[j];
    }
    cout << max << endl << b << endl;
    return 0;
}