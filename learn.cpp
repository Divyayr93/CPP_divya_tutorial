///Friend function usage///
#include <iostream>
using namespace std;


class Base{
    int x;
public:
    Base(){}
    Base(int x):x{x} {}
    friend void fun(Base &);
};

void fun(Base &obj)
{
    cout<<obj.x<<endl;
    obj.x = 20;
    cout<<obj.x<<endl;
}
int main()
{
    Base b(10);
    fun(b);
    return 0;
}

///Types of Casting in c++:   const_cast,static_cast, dynamic_cast, reinterpret_cast.
///The expression const_cast<T>(v) can be used to change the const qualifiers of pointers or references.
///T must be pointer, reference.

#include<iostream>
using namespace std;

 void fun(int *x){
        int k = 10;
        cout<<k+(*x)<<endl;
    }

int main()
{
    ///First Case:  trying to change data of non const integer via const address.
    const int a=10;
    const int* b = &a;
    int *d = const_cast<int*> (b);
    *d = 15;/// Invalid or undefined behaviour as a is constant but for const_cast to operate variable should not be const.
    cout<<a<<endl; /// As a is const which is not changed value is not overwritten. so a will hold 10 value.

    int a1 = 20;
    const int* b1 = &a1;
    int *d1 = const_cast<int*>(b1);
    *d1 = 30;  ////valid code as original address is not constant.
    cout<<a1<<endl; 
    /// First case

    ///Second case: trying to pass address/reference to a 3rd party function which should not change the data of that variable and just use it.
    const int x = 5;
    const int*y = &x;
    fun(const_cast<int*> (y)); //without const_cast in this linecompiler will throw error as x and y are constants.
}

///What is the use of decltype in C++:  it checks the type of expression.
///As return type in * T2 add(a,b)* is T2 result always follows T2 type. But truncation happens for 2nd example.
///So, instead if we use decltype(a+b) as return type followed by *->* operator and return type should be auto, final result follows decltype of result.

#include<iostream>
using namespace std;

template<typename T1, typename T2>
T2 add(T1 a, T2 b) // corrected line: auto add(T1 a, T2 b) -> decltype(a+b)
{
    return a+b;
}

int main(){
    cout<<add(1,1.8)<<endl;
    cout<<add(1.8,1)<<endl;
}


/// difference b/w address and pointer
int main(){
    //Memory address will be same incase of reference
    int a =10;
    int c = 20;
    int &b = a; // b has same adress as a.
    int *p = &a; // p has different address , but it holds the address for a;

    //reassignment is not possible incase of reference.
    b = &c; // wrong
    &b = c ; //here value of c is overwritten in memory location of b inturn a.

    ///  Null assignment is not possible incase of reference.

    int *p = NULL;
    int &b = NULL;// Error not possible

    /// Arithematic operationsnot possible incase of reference
    b++; /// not possible.

    ///Indirection
    int **p1 = &p;
    int ***p2 = &p1; // n-dimension indirection possible incase of pointer, but not in reference.
    //max we can do one inderection.
    int &b1 = b;
}


///for loop and for_each difference.
///for loop can iterate through normal arrays, but for_each needs begin and end always to loop inside.

#include <iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main() {
    vector<int> v;
    int ar[10];
    for(int i=0;i<5;i++)
    {
        v.push_back(i);
    }
    for(int i: ar)
        cout<<i<<endl;

    
    for(int i:v) 
    cout<<i<<endl;
    
    for_each(v.begin(),v.end(), [](int i){cout<<i<<endl;} );

}


/// Dynamic Cast: it sole purpose is to downcast properly to correct derived class from base class.
/// For this to happen, base clase shld have atleast one virtual function.
//we shld use only when we are not sure if downcast fails at some point. else we shld avoid using this dynamic_cast as it has runtime overhead.
/// we can use static_cast inplace of dynamic_cast, which does the same job. but only during compile time. so we cannot validate during runtime.

#include <iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Base{
    public:
  virtual void print(){
      cout<<"Base"<<endl;
  }  
};

class Derived1:public Base{
    public:
    Derived1(){
       // cout<<"Derived1"<<endl;
    }
    void print(){
        cout<<"Derived1"<<endl;
    }
};

class Derived2:public Base{
    void print(){
        cout<<"Derived2"<<endl;
    }
};
int main() {
    Derived1 d1;
    Base *bp = dynamic_cast<Base*> (&d1); //typecasting derived class to base pointer.
    bp->print();
    Derived2 *d2p = dynamic_cast<Derived2*>(bp);//error as bp holds Derived1 class..
    //so this can be checked during runtime.
    if(d2p ==nullptr){
        cout<<"NULL"<<endl;
    }
    else{
        cout<<"NOt NULL"<<endl;
    }
    Derived1 *dp = dynamic_cast<Derived1*>(bp);
    if(dp ==nullptr){
        cout<<"NULL"<<endl;
    }
    else{
        cout<<"NOt NULL"<<endl;
    }
}

///Use of explicit Keyworkd in C++
///Ans: It avoids implicit call to constructor.
//Below example fails as b initializes data via constructor which is not called in a way it has to be mentioned explicitly.
#include <iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Base{
    int a;
    public:
  Base(){}
  explicit Base(int b):a(b){}
  void print(){
      cout<<a<<endl;
  }
};

int main() {
    Base b(10);
    Base b1 = 20;
    b.print();
    b1.print
}


///When to use Extern C in C++
///suppose we have some library in c code and trying to call in c++ code.
///name mangling happens in cpp to all functions based on input and output.
///Example add(int a, intb) will have "addi" and   add(floata,floatb) will have "addf" name.
///similarly C functiona as well be mangled to different name. to avoide this explicitly say to cpp compiler that whatever function comes within extern C"  " don't do name mangling.

extern "C"{
#include "header.h
}


///Function chaining: sequence of functions which has to be executed in order else we get error.
///It works correctly while passing by reference.

///function Hiding: Base and Derived function have the functions whose names are similar irrespective of number of arguments or type of argument.
///if we try to call function of base from derived class object, the base function will be hiding and only derived function will be called.
///To explicitly call base function we need to bring base function codes to derived class. To do that we shld define "using Base::fun;" within derived class.
///So that all functions in base will come derived class scope.
#include <iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Base{
public:
   void fun(int i){
       cout<<"BASE"<<endl;
   }
    
};

class Derived: public Base{
public:
    //using Base::fun;  this line shld be present to overcome function hiding.
    void fun(char c){
        cout<< "Derived" <<endl;
    }
};

int main() {
    Derived d;
    d.fun(1);
    d.fun('a');
}

//Functor usage in c++
#include <iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Mul{
    int val;
public:
  Mul(){}
  Mul(int v):val(v){}
  
  int operator () (int var){
      return var*val;
  }
    
};

int main() {
    Mul mul(12);
    cout<<mul(2)<<endl;//operator overloading happens 
    cout<<mul(3)<<endl;
}


