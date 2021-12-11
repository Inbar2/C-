#include <cstdio>
#include <vector>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;
using std::string;

int main(){
    vector<string> elements;

    elements.push_back("type");
    elements.push_back("floor");
    elements.push_back("room");

    //  1<<n is essentially pow(2, n), but much faster and only for integers
    //  the iterator i will be our mask i.e. its binary form will tell us which elements to use and which not
    std::cout << (1<<elements.size()) << std::endl;
	std::cout << pow(2, elements.size()) << std::endl;
    for (int i=0;i<(1<<elements.size());++i)
    {
        printf("Combination #%d: ", i+1);
        string key;
        //size_t temp = 1;
        for (int j=0;j<elements.size();++j)
        {
            //  1<<j shifts the 1 for j places and then we check j-th binary digit of i
            if (i & (1<<j )/*temp*/)
            {
                key += elements[j];
            }
            else
            {
            	key+= "X"; //any
			}
			if(j!=2)
			{
				key+='|';
			}
            //temp<<=1;
        }
        std::cout << key << std::endl;
    }

    return 0;
}

//source https://stackoverflow.com/questions/23516696/recursion-vs-bitmasking-for-getting-all-combinations-of-vector-elements result:
/*
Combination #1:
Combination #2: 1
Combination #3: 2
Combination #4: 1 2
Combination #5: 3
Combination #6: 1 3
Combination #7: 2 3
Combination #8: 1 2 3
*/

//Result after modification, got the keys:
/*
Combination #1: X|X|X
Combination #2: type|X|X
Combination #3: X|floor|X
Combination #4: type|floor|X
Combination #5: X|X|room
Combination #6: type|X|room
Combination #7: X|floor|room
Combination #8: type|floor|room
*/
