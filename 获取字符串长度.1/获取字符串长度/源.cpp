

#include<iostream>
using namespace std;

int main()
{
	char str[100] = "0", * p=NULL;
	int count = 0;
	p = str;
	cin.getline(str, sizeof(str));
	while (*p++ != '\0')
		count++;
	cout << count;
	return 0;
}