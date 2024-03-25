#include <iostream>
#include <iomanip>
#include <cstring>
#include <vector>
#include <unistd.h>
#include <fcntl.h>
#include "libasm.h"

#define FUNC "write"

bool KO = false;

int	cmp(const char *s1, int test)
{
	int len = strlen(s1);
	int fd = open("out.txt", O_RDWR | O_CREAT);
	if (fd == -1)
	{
		std::cerr << "Failed to open file for writing." << std::endl;
		return 1;
	}
	unlink("out.txt");

	ssize_t	b1 = ft_write(fd, s1, len);
	ssize_t	b2 = write(fd, s1, len);

	if (b1 == -1 || b2 == -1)
	{
		std::cerr << "Failed to write to file." << std::endl;
		return 1;
	}

	char buf1[len + 1];
	char buf2[len + 1];
	bzero(buf1, len + 1);
	bzero(buf2, len + 1);

	lseek(fd, 0, SEEK_SET);
	if (read(fd, buf1, len) == -1 || read(fd, buf2, len) == -1)
	{
		std::cerr << "Failed to read from file." << std::endl;
		return 1;
	}
	close(fd);

	int res = (b1 == b2) && (strcmp(buf1, buf2) == 0);

	if (!res)
	{
		if (!KO)
		{
			std::cerr << "------- " << FUNC << " -------" << std::endl;
			KO = true;
		}
		std::cerr << "Test " << test << ": expected '" << buf2 << "' , bytes: " << b2;
		std::cerr << " got '" << buf1 << "' , bytes: " << b1 << std::endl;
	}

	return (res);
}

int printRes(std::vector<int> v)
{
	int res = 0;

	std::cout << std::left << std::setw(20) << FUNC << " : ";
	for (size_t i = 0; i < v.size(); i++)
	{
		std::cout << i + 1 << ".";
		if (v[i])
			std::cout << "\033[1;32mOK\033[0m ";
		else
		{
			std::cout << "\033[1;31mKO\033[0m ";
			res = 1;
		}
	}
	std::cout << std::endl;

	return res;
}

int main(void)
{
	std::vector<int>	v;
	int					res;
	int					i = 1;

	// Test 1
	res = cmp("", i++);
	v.push_back(res);

	// Test 2
	res = cmp("a", i++);
	v.push_back(res);

	// Test 3
	res = cmp("ab", i++);
	v.push_back(res);

	// Test 4
	res = cmp("lol", i++);
	v.push_back(res);

	// Test 5
	res = cmp("this is a test!", i++);
	v.push_back(res);

	// Test 6
	res = cmp("1234", i++);
	v.push_back(res);

	// Test 7
	res = cmp("12", i++);
	v.push_back(res);

	return printRes(v);
}

