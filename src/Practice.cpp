#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <cassert>

using namespace std;



//Ex. Symbol Newtona z Codility
/*
Gdy parametry <0 lub k>n lub rezultat>=1000 000 000 to zwróć błąc -1.


unsigned long iterNewt(int n, int k){
	
	//Obsotrzenie żeby Nie było liczb ujemnych oraz aby k<=n
	if(k<0 && n<k)
		return -1;
	//Marginal constraints
	if(k==0 || k==n)
		return 1;
	
	//Main loop
	unsigned long res=1;
	for(int i=1;i<=k;++i){
		res=res*(n-i+1)/i;
		cout<<res<<endl;
		
		//Prevent from overflow
		if (res>1000000000){
			return -1;
		}
	}
	return res;
}

main(){
	
	long result=iterNewt(41,25);
	cout<<setprecision(30)<<"Result: "<<result;
}
*/\

//Ex.Calculate nr of digits for a number.
/*

int countDigits(long n){
	int counter=0;
	
	while(n!=0){
		n/=10;
		++counter;
	}
	return counter;
}

int main(){

cout<<"Number has "<<countDigits(1234567111849311113)<<" digits."<<endl;
}
*/

//Ex. CODEWARS Convert number to reversed array of digits
/*
Given a random number:
    C++: unsigned long;
You have to return the digits of this number within an array in reverse order.
Example:
348597 => [7,9,5,8,4,3]


std::vector<int> digitize(unsigned long n) 
{  
  unsigned long divider=100000000000;
  vector<int> vec;
  bool first=false;
  
  for(int i=0;i<11;++i){
    int digit= n/divider;
	
	//Look for first digit
	if(digit!=0 || first==true){
		first=true;
		vec.push_back(digit);
		//Odejmij divider*digit od n
		n-=(divider*digit);
		
		//podziel divider przez 10
	}
		divider/=10;
  }
  //reverse
  reverse(vec.begin(),vec.end());
  return vec;
}

//Better solution!
std::vector<int> digitize(unsigned long n) 
{        
  std::vector<int> vec;
  while(n!=0){
    vec.push_back(n%10);
    n/=10;
  }
  return vec;
}

int main(){
vector<int> vec(digitize(345));
for(int el:vec)
	cout<<el;
}
*/