#include<iostream>
#include<string>
using namespace std;
struct Birthday{
    int year;
    int month;
    int day;
};
struct Student{
    Birthday birthday;
    char name[20];
    char telephone[20];
    char address[50];
    void print(){
        cout << name << " " << birthday.year << " "<<
         birthday.month << " "<< birthday.day << " "<< telephone << "" << address <<endl;
    }
    bool operator>(Student b){
        Student a = *this;
        if(a.birthday.year > b.birthday.year) return false;
        else if(a.birthday.year < b.birthday.year) return true;
        else{
            if(a.birthday.month > b.birthday.month) return false;
            else if(a.birthday.month < b.birthday.month) return true;
            else{
                if(a.birthday.day > b.birthday.day) return false;
                else return true;
            }
        }
    }
    
};
void swap(Student &a,Student &b){
        Student temp = a;
        a = b;
        b = temp;
    }
int main(){
    int n = 0;
    cin >> n;
    Student *stu = new Student[n];
    for (int i = 0; i < n; ++i){
        cin >> stu[i].name >> stu[i].birthday.year >> stu[i].birthday.month >> stu[i].birthday.day ;
        cin >> stu[i].telephone;
        cin.getline(stu[i].address, 50, '\n');
    }
    for (int i = 0; i < n; ++i){
        stu[i].print();
    }
    for (int i = 0; i < n; ++i){
        for (int j = i; j < n-1; ++j){
            if(stu[i] > stu[j]){
                swap(stu[j], stu[i]);
            }
        }
    }
    for (int i = 0; i < n; ++i){
        stu[i].print();
    }
    return 0;
}
// 本关任务：通信录包含

// “姓名”（最多20个字符）、
// “生日”（包括“年”、“月”、“日”）、
// “电话号码”、
// “家庭地址”（最多50个字符）。
// 定义一个嵌套的结构类型，输入n(n<10)个学生信息，再按照他们的年龄从小到大的顺序输出。

// 编程要求
// 根据提示，在右侧编辑器补充代码，用户先输入正整数n表示学生人数，然后输入这些学生的信息，再按照他们的年龄从小到大的顺序输出。

// 测试说明
// 平台会对你编写的代码进行测试：
// 测试输入：
// 2 
// Wangwu 1990 12 11 13901232222 No. 800 Dongchuan Road
// Zhangsan 1993 1 23 18912337789 No.238 Huasan Road
// 预期输出：
// Zhangsan 1993 1 23 18912337789 No.238 Huasan Road
// Wangwu 1990 12 11 13901232222 No. 800 Dongchuan Road