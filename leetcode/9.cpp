class Solution {
public:
    bool isPalindrome(int x) {
        if(x < 0){
            return false;
        }
        else if(x == 0){
            return true;
        }
        else{
            char ch[32];
            int i = 0, j = 0;
            while(x > 0){
                ch[i++] = x % 10;
                x /= 10;
            }
            i -= 1;
            while(j <= i){
                if(ch[i] != ch[j]){
                    return false;
                    ++j;
                    --i;
                }
            }
            return true;
        }
    }
};