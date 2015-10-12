
#include "../includes/string.h"
#include <iostream>
#include <cstring>
#include <cassert>
#include <cmath>

// A few freebies to get past the first couple of tests.
// These may need to be modified!
sfw::string::string( void ) {
	m_size = 1;
	m_data = new char[m_size];
	*m_data = '\0';
}

sfw::string::~string() {
	delete m_data;
}

size_t sfw::string::length() const {
	return strlen( m_data );
}

sfw::string::string( size_t size ) {
	m_size = size;
	m_data = new char[m_size];
	*m_data = '\0';
}

sfw::string::string( const char * a, size_t size ) {
	m_size = size;
	m_data = new char[m_size];
	strncpy_s( m_data, m_size, a, m_size - 1 );
}

sfw::string::string( const char * a ) {
	if ( a == nullptr ) {
		m_size = 1;
		m_data = new char[m_size];
		*m_data = '\0';
	} else {
		m_size = strlen( a ) + 1;
		m_data = new char[m_size];
		strcpy_s( m_data, m_size, a );
	}
}

sfw::string::string( const string & a ) {
	if ( this != &a ) {
		m_size = a.m_size;
		m_data = new char[m_size];
		strcpy_s( m_data, m_size, a.m_data );
	} else {
		m_size = 1;
		m_data = new char[m_size];
		*m_data = '\0';
	}
}

sfw::string::string( string && a ) {
	m_size = a.m_size;
	m_data = a.m_data;
	a.m_data = nullptr;
	a = sfw::string();
}

sfw::string & sfw::string::operator=( const string & a ) {
	if ( this != &a ) {
		if ( m_data != nullptr ) {
			delete[] m_data;
		}
		m_size = a.m_size;
		m_data = new char[m_size];
		strncpy_s( m_data, m_size, a.m_data, m_size );
	}
	return *this;
}

sfw::string & sfw::string::operator=( string && a ) {
	if ( this != &a ) {
		if ( m_data != nullptr ) {
			delete[] m_data;
		}
		m_size = a.m_size;
		m_data = a.m_data;
		a.m_data = new char[1];
		a.m_size = 1;
		*a.m_data = '\0';
	}
	return *this;
}

sfw::string & sfw::string::operator=( const char * a ) {
	if ( a == nullptr ) {
		clear();
	} else {
		int len = strlen( a ) + 1;
		if ( m_size < len ) {
			delete[] m_data;
			m_size = len;
			m_data = new char[m_size];
		}
		strcpy_s( m_data, m_size, a );
	}
	return *this;
}

sfw::string & sfw::string::operator+=( const string & a ) {
	int lenNeeded = length() + a.length() + 1;
	if ( m_size < lenNeeded ) {
		resize( lenNeeded );
	}
	strcat_s( m_data, m_size, a.m_data );
	return *this;
}

sfw::string & sfw::string::operator+=( const char * a ) {
	int lenNeeded = length() + strlen( a ) + 1;
	if ( m_size < lenNeeded ) {
		resize( lenNeeded );
	}
	strcat_s( m_data, m_size, a );
	return *this;
}

sfw::string & sfw::string::operator+=( char a ) {
	int lenNeeded = length() + 2;
	if ( m_size < lenNeeded ) {
		resize( lenNeeded );
	}
	m_data[lenNeeded - 2] = a;
	m_data[lenNeeded - 1] = '\0';
	return *this;
}

char & sfw::string::operator[]( size_t index ) {
	return m_data[index];
}

const char & sfw::string::operator[]( size_t index ) const {
	return m_data[index];
}




size_t sfw::string::size() const {
	return m_size;
}

void sfw::string::resize( size_t size ) {
	if ( size == 0 ) {
		size = 1;
	}
	char* tmp = new char[size];
	strncpy_s( tmp, size, m_data, length() + 1 );
	delete m_data;
	m_size = size;
	m_data = tmp;
}

void sfw::string::clear() {
	*m_data = '\0';
}

bool sfw::string::empty() const {
	return !*m_data;
}

const char * sfw::string::cstring() const {
	return m_data;
}

bool sfw::operator<( const string & a, const string & b ) {
	return strcmp( a.cstring(), b.cstring() ) == -1;
}

bool sfw::operator<( const string & a, const char * b ) {
	return strcmp( a.cstring(), b ) == -1;
}

bool sfw::operator<( const char * a, const string & b ) {
	return strcmp( a, b.cstring() ) == -1;
}

bool sfw::operator<=( const string & a, const string & b ) {
	return ( strcmp( a.cstring(), b.cstring() ) == -1 || a == b );
}

bool sfw::operator<=( const string & a, const char * b ) {
	return ( strcmp( a.cstring(), b ) == -1 || a == b );
}

bool sfw::operator<=( const char * a, const string & b ) {
	return ( strcmp( a, b.cstring() ) == -1 || a == b );
}

bool sfw::operator>( const string & a, const string & b ) {
	return strcmp( a.cstring(), b.cstring() ) == 1;
}

bool sfw::operator>( const string & a, const char * b ) {
	return strcmp( a.cstring(), b ) == 1;
}

bool sfw::operator>( const char * a, const string & b ) {
	return strcmp( a, b.cstring() ) == 1;
}

bool sfw::operator>=( const string & a, const string & b ) {
	return ( strcmp( a.cstring(), b.cstring() ) == 1 || a == b );
}

bool sfw::operator>=( const string & a, const char * b ) {
	return ( strcmp( a.cstring(), b ) == 1 || a == b );
}

bool sfw::operator>=( const char * a, const string & b ) {
	return ( strcmp( a, b.cstring() ) == 1 || a == b );
}

bool sfw::operator!=( const string & a, const string & b ) {
	return !( a == b );
}

bool sfw::operator!=( const string & a, const char * b ) {
	return strcmp( a.cstring(), b ) != 0;
}

bool sfw::operator!=( const char * a, const string & b ) {
	return strcmp( a, b.cstring() ) != 0;
}

bool sfw::operator==( const string & a, const string & b ) {
	return strcmp( a.cstring(), b.cstring() ) == 0;
}

bool sfw::operator==( const string & a, const char * b ) {
	return strcmp( a.cstring(), b ) == 0;
}

bool sfw::operator==( const char * a, const string & b ) {
	return strcmp( a, b.cstring() ) == 0;
}

sfw::string sfw::operator+( const string & a, const string & b ) {
	return string( a ) += b;
}

sfw::string sfw::operator+( const string & a, const char * b ) {
	return string( a ) += b;
}

sfw::string sfw::operator+( const char * a, const string & b ) {
	return string( a ) += b;
}

sfw::string sfw::operator+( const string & a, char b ) {
	return string( a ) += b;
}

sfw::string sfw::operator+( char a, const string & b ) {
	string str;
	str += a;
	str += b;
	return str;
}

std::ostream & sfw::operator<<( std::ostream & os, const string & p ) {
	os << p.cstring();
	return os;
}

std::istream & sfw::operator>>( std::istream & is, string & p ) {
	char tmp[256];
	is >> tmp;
	p = tmp;
	return is;
}

const sfw::string sfw::literals::operator""_sfw( const char * a, size_t len ) {
	return string( a, len + 1 );
}
