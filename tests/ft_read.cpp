#include <iostream>
#include <iomanip>
#include <cstring>
#include <vector>
#include <unistd.h>
#include <fcntl.h>
#include "libasm.h"

#define FUNC "ft_read"

bool KO = false;

int	cmp(const char *s1, int test, int mode)
{
	int len = strlen(s1);
	int fd = open("out.txt", O_RDWR | O_CREAT);
	if (fd == -1)
	{
		std::cerr << "Failed to open file for writing." << std::endl;
		return 1;
	}
	unlink("out.txt");

	if (write(fd, s1, len) == -1)
	{
		std::cerr << "Failed to write to file." << std::endl;
		close(fd);
		return 1;
	}

	char buf1[len + 1];
	char buf2[len + 1];
	bzero(buf1, len + 1);
	bzero(buf2, len + 1);

	if (mode)
	{
		close(fd);
		fd = -1;
	}

	char *err1 = (char*)"";
	char *err2 = (char*)"";
	ssize_t b1 = 0;
	ssize_t b2 = 0;

	if (mode == 0)
	{
		lseek(fd, 0, SEEK_SET);
		b1 = ft_read(fd, buf1, len);
		if (mode && errno)
			err1 = strerror(errno);

		lseek(fd, 0, SEEK_SET);
		b2 = read(fd, buf2, len);
		if (mode && errno)
			err2 = strerror(errno);

		if (b1 == -1 || b2 == -1)
		{
			std::cerr << "Failed to read from file." << std::endl;
			close(fd);
			return 1;
		}
		close(fd);
	}

	int res = (b1 == b2) && (strcmp(buf1, buf2) == 0);
	if (mode)
		res += strcmp(err1, err2) == 0;

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

int printRes(const std::vector<int>& v)
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
	res = cmp("", i++, 0);
	v.push_back(res);

	// Test 2
	res = cmp("a", i++, 0);
	v.push_back(res);

	// Test 3
	res = cmp("ab", i++, 0);
	v.push_back(res);

	// Test 4
	res = cmp("lol", i++, 0);
	v.push_back(res);

	// Test 5
	res = cmp("this is a test!", i++, 0);
	v.push_back(res);

	// Test 6
	res = cmp("1234", i++, 0);
	v.push_back(res);

	// Test 7
	res = cmp("12", i++, 1);
	v.push_back(res);

	res = printRes(v);

	std::exit(res);
}

