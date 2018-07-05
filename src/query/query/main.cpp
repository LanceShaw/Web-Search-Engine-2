#include<iostream>
#include<locale>

#include "MyInterface.h"
#include "MyInterface2.h"
#include "MyStack.h"
#include "MyString.h"
#include "MyStringLinkedList.h"
#include "MyHashTable.h"
#include "MyAVL.h"
#include "MyDocuList.h"
#include "MyHtmLInfo.h"
#include "ReadFile.h"
#include "WriteFile.h"

using namespace std;

int main()
{
	clock_t start, end;
    start = clock();

	query_to_result();

	end = clock();
    cout<<"Run time: "<<(double)(end - start) / CLOCKS_PER_SEC<<"S"<<endl;
	return 0;
}