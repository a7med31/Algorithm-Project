#include <iostream>
#include <cmath>
using namespace std;

int count;

     void hanoi(int n, int k, string from, string temp, string to) {
        if (n == 0) {
             cout<<"";
             return;
        }
        hanoi(n - 1, k, from, to, temp);
        cout<<"Move disc "<< (n + k) << " from " << from << " to " <<to<<"\n";
        count++;
        hanoi(n - 1, k, temp, from, to);

    }
     void rev(int n, string from, string temp, string to, string temp2) {
         //k is random no, 1<=k<=n
        int k = (int) (n + 1 - round(sqrt(2 * n + 1)));
        if (k == 0){
            cout<<"Move disc " << 1  << " from " << from << " to " << to<<"\n";
            count++;
            return;
        }
        rev(k, from , to, temp , temp2);
        hanoi(n-k,k, from, temp2, to);
        rev(k,temp,from,to,temp2);
    }

    int main(){
    int n = 8;
    rev(n, "A", "B", "D", "C");
    cout<<count;
     }


     //frame stewart

