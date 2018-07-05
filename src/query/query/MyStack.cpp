#include "MyStack.h"

void MyStack_test()
{

	MyStack<int> s;

	for (int i = 0; i < 10; ++i)
	{
		s.push(i);
	}
	for (int j = s.size() - 1; j >= 0; --j)
	{
		cout << "node: " << s.Top() << endl;
		s.pop();
	}

	s.clear();

}
