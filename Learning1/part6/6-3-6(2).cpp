#include <iostream>
#include <string>

using namespace std;

string s, t;

int main() {
    string ss;
    while(getline(cin, ss)) {
        s += ss;
        s += "\n";
    }
    int ls = s.size();
    t = s;
    for (int i = 0; i < ls; ++i) {
        if (t[i] >= 'a' && t[i] <= 'z') {
            t[i] += 'A' - 'a';
        }
        if (t[i] < 'A' || t[i] > 'Z') {
            t[i] = 0;
        }
    }
    int ans = 0, ansl, ansr;
    for (int i = 0; i < ls; ++i) {
        if (t[i]) {
            int l = i - 1, r = i + 1;
            int len = 1, lastl = i, lastr = i;
            while (true) {
                while (l >= 0 && t[l] == 0) {
                    l--;
                }
                while (r < ls && t[r] == 0) {
                    r++;
                }
                if (l < 0 || r >= ls || t[l] != t[r]) {
                    break;
                } else {
                    len += 2;
                    lastl = l;
                    lastr = r;
                    l--;
                    r++;
                }
            }
            if (len > ans) {
                ans = len;
                ansl = lastl;
                ansr = lastr;
            }
        }
    }
    for (int i = 0; i < ls; ++i) {
        if (t[i]) {
            int r = i + 1;
            while (r < ls && t[r] == 0) {
                r++;
            }
            if (r >= ls || t[r] != t[i]) {
                continue;
            }
            int l = i - 1;
            r++;
            int len = 2, lastl = i, lastr = r - 1;
            while (true) {
                while (l >= 0 && t[l] == 0) {
                    l--;
                }
                while (r < ls && t[r] == 0) {
                    r++;
                }
                if (l < 0 || r >= ls || t[l] != t[r]) {
                    break;
                } else {
                    len += 2;
                    lastl = l;
                    lastr = r;
                    l--;
                    r++;
                }
            }
            if (len > ans) {
                ans = len;
                ansl = lastl;
                ansr = lastr;
            }
        }
    }
    cout << ans << endl;
    for (int i = ansl; i <= ansr; ++i) {
        cout << s[i];
    }
    return 0;
}