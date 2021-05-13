#include "hw2_test.h"
#include <stdio.h>
#include <iostream>
#include <cassert>

using namespace std;

int main() {
    int x = get_weight();
	cout << "weight: " << x << endl;
	assert(x == 0);
    x = set_weight(5);
	cout << "set_weight returns: " << x << endl;
	assert(x == 0);
    x = get_weight();
	cout << "new weight: " << x << endl;
	assert(x == 5);
    cout << "===== SUCCESS =====" << endl;
     cout <<"main pid is :" <<getpid()<<std::endl;
	 cout << " main weight is : " <<get_weight()<<std::endl;

	pid_t pid = fork ();

	if (pid > 0)
	{
		sleep (5);
	}
	else
	{
		set_weight(4);
		std::cout<< " son pid is :" << getpid()<<std::endl;
		std::cout<< " son weight is :" << get_weight() << std::endl;
		x=get_heaviest_ancestor();
		std::cout<< " heaviest _ ancestor is :" << x << std::endl;
	}
    return 0;
}

