
#include "string.h"
#include <iostream>
#include <cstring>
#include <cassert>
#include <cmath>

// A few freebies to get past the first couple of tests.
// These may need to be modified!
sfw::string::string(void)
{
	// TODO: is this finished?
	m_data = new char[m_size = 1]{ '\0' };
}

sfw::string::~string()
{
	// TODO: is this finished?
	if (m_data != nullptr) {
		delete[]m_data;
	}
}

size_t sfw::string::length() const
{
	// TODO: is this finished?
	return m_data == nullptr ? 0 : strlen(m_data);
}





sfw::string::string(size_t size)
{
	// TODO:
	m_size = size;
	m_data = new char[m_size];
	*m_data = '\0';
}

sfw::string::string(const char * a, size_t size)
{
	// TODO:
	m_size = size;
	m_data = new  char[m_size];
	memcpy(m_data, a, m_size);
	m_data[m_size-1] = '\0';
}

sfw::string::string(const char * a)
{
	// TODO:
	//assert(a != nullptr);
	if (a == nullptr) {
		m_data = new char[m_size = 1]{ '\0' };
	}
	else {
		m_size = strlen(a) + 1;
		m_data = new char[m_size];
		memcpy(m_data, a, m_size);
		m_data[m_size - 1] = '\0';
	}
}

sfw::string::string(const string & a)
{
	// TODO:
	m_size = a.length() + 1;
	m_data = new char[m_size];
	memcpy(m_data, a.m_data, m_size);
	m_data[m_size - 1] = '\0';
}

sfw::string::string(string && a)
{
	// TODO:
	m_size = a.m_size;
	m_data = a.m_data;
	a.m_data = nullptr;
	a.m_size = 0;
}

sfw::string & sfw::string::operator=(const string & a)
{
	// TODO:
	if (this != &a) {
		int length = a.length();
		if (length + 1 > m_size) {
			resize(length + 1);
		}
		memcpy(m_data, a.m_data, m_size);
		m_data[m_size - 1] = '\0';
	}
	return *this;
}

sfw::string & sfw::string::operator=(string && a)
{
	// TODO:
	if (this != &a) {
		delete m_data;
		m_size = a.m_size;
		m_data = a.m_data;
		a.m_data = nullptr;
		a.m_size = 0;
	}
	return *this;
}

sfw::string & sfw::string::operator=(const char * a)
{
	// TODO:
	if (a == nullptr) {
		m_data = new char[m_size = 1]{ '\0' };
	}
	else {
		int length = strlen(a);
		if (m_size < length + 1) {
			resize(length + 1);
		}
		memcpy(m_data, a, m_size);
		m_data[m_size - 1] = '\0';
	}
	return *this;
}

sfw::string & sfw::string::operator+=(const string & a)
{
	// TODO:
	return *this = *this + a;
}

sfw::string & sfw::string::operator+=(const char * a)
{
	// TODO:
	return *this = *this + a;
}

sfw::string & sfw::string::operator+=(char a)
{
	// TODO:
	return *this = *this + a;
}

char & sfw::string::operator[](size_t index)
{
	// TODO: Is this finished?
	return this->m_data[index];
}

const char & sfw::string::operator[](size_t index) const
{
	// TODO: Is this finished?
	return this->m_data[index];
}




size_t sfw::string::size() const
{
	// TODO:
	return m_size;
}

void sfw::string::resize(size_t size)
{
	// handle case where input is not positive
	if (size <= 0) {
		if (m_data != nullptr) {
			m_size = 0;
			delete m_data;
			m_data = nullptr;
		}
	}
	else {
		m_size = size;
		int oldLen = length();
		char* tmp = new(std::nothrow) char[m_size];
		if (tmp == nullptr) {
			resize(1);
			return;
		}
		memcpy(tmp, m_data, oldLen);
		int min = oldLen < m_size - 1 ? oldLen : m_size - 1;
		tmp[min] = '\0';
		if (m_data != nullptr) {
			delete m_data;
		}
		m_data = tmp;
	}
}

void sfw::string::clear()
{
	// TODO:
	if (m_data != nullptr) {
		*m_data = '\0';
	}
}

bool sfw::string::empty() const
{
	// TODO:
	return !(*m_data);
}

const char * sfw::string::cstring() const
{
	// TODO:
	return m_data;
}

bool sfw::operator<(const string & a, const string & b)
{
	// TODO:
	return strcmp(a.cstring(), b.cstring()) == -1;
}

bool sfw::operator<(const string & a, const char * b)
{
	// TODO:
	return strcmp(a.cstring(), b) == -1;
}

bool sfw::operator<(const char * a, const string & b)
{
	// TODO:
	return strcmp(a, b.cstring()) == -1;
}

bool sfw::operator<=(const string & a, const string & b)
{
	// TODO:
	int val = strcmp(a.cstring(), b.cstring());
	return val == -1 || val == 0;
}

bool sfw::operator<=(const string & a, const char * b)
{
	// TODO:
	int val = strcmp(a.cstring(), b);
	return val == -1 || val == 0;
}

bool sfw::operator<=(const char * a, const string & b)
{
	// TODO:
	int val = strcmp(a, b.cstring());
	return val == -1 || val == 0;
}

bool sfw::operator>(const string & a, const string & b)
{
	// TODO:
	return strcmp(a.cstring(), b.cstring()) == 1;
}

bool sfw::operator>(const string & a, const char * b)
{
	// TODO:
	return strcmp(a.cstring(), b) == 1;
}

bool sfw::operator>(const char * a, const string & b)
{
	// TODO:
	return strcmp(a, b.cstring()) == 1;
}

bool sfw::operator>=(const string & a, const string & b)
{
	// TODO:
	int val = strcmp(a.cstring(), b.cstring());
	return val == 1 || val == 0;
}

bool sfw::operator>=(const string & a, const char * b)
{
	// TODO:
	int val = strcmp(a.cstring(), b);
	return val == 1 || val == 0;
}

bool sfw::operator>=(const char * a, const string & b)
{
	// TODO:
	int val = strcmp(a, b.cstring());
	return val == 1 || val == 0;
}

bool sfw::operator!=(const string & a, const string & b)
{
	// TODO:
	return strcmp(a.cstring(), b.cstring()) != 0;
}

bool sfw::operator!=(const string & a, const char * b)
{
	// TODO:
	return strcmp(a.cstring(), b) != 0;
}

bool sfw::operator!=(const char * a, const string & b)
{
	// TODO:
	return strcmp(a, b.cstring()) != 0;
}

bool sfw::operator==(const string & a, const string & b)
{
	// TODO:
	return strcmp(a.cstring(), b.cstring()) == 0;
}

bool sfw::operator==(const string & a, const char * b)
{
	// TODO:
	return strcmp(a.cstring(), b) == 0;
}

bool sfw::operator==(const char * a, const string & b)
{
	// TODO:
	return strcmp(a, b.cstring()) == 0;
}

sfw::string sfw::operator+(const string & a, const string & b)
{
	// TODO:
	int len = a.length() + b.length() + 1;
	char* tmp = new char[len];
	memcpy(tmp, a.cstring(), a.length());
	tmp[a.length()] = '\0';
	strcat_s(tmp, len, b.cstring());
	string str(tmp);
	delete tmp;
	return str;
}

sfw::string sfw::operator+(const string & a, const char * b)
{
	// TODO:
	int len = a.length() + strlen(b) + 1;
	char* tmp = new char[len];
	memcpy(tmp, a.cstring(), a.length());
	tmp[a.length()] = '\0';
	strcat_s(tmp, len, b);
	string str(tmp);
	delete tmp;
	return str;
}

sfw::string sfw::operator+(const char * a, const string & b)
{
	// TODO:
	int len = strlen(a) + b.length() + 1;
	char* tmp = new char[len];
	memcpy(tmp, a, strlen(a));
	tmp[strlen(a)] = '\0';
	strcat_s(tmp, len, b.cstring());
	string str(tmp);
	delete tmp;
	return str;
}

sfw::string sfw::operator+(const string & a, char b)
{
	// TODO:
	int len = a.length() + 2;
	char* tmp = new char[len];
	strcat_s(tmp, len, a.cstring());
	tmp[a.length()] = '\0';
	tmp[len - 2] = b;
	tmp[len - 1] = '\0';
	string str(tmp);
	delete tmp;
	return str;
}

sfw::string sfw::operator+(char a, const string & b)
{
	// TODO:
	int len = b.length() + 2;
	char* tmp = new char[len];
	tmp[0] = a;
	tmp[1] = '\0';
	strcat_s(tmp, len, b.cstring());
	string str(tmp);
	delete tmp;
	return str;
}

std::ostream & sfw::operator<<(std::ostream & os, const string & p)
{
	// TODO:
	os << p.cstring();
	return os;
}

std::istream & sfw::operator>>(std::istream & is, string & p)
{
	// TODO:
	char tmp[128];
	is >> tmp;
	p = tmp;
	return is;
}

const sfw::string sfw::literals::operator""_sfw(const char * a, size_t len)
{
	// TODO:
	return string(a);
}
