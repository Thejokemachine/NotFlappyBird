#include "SmallString.h"



CSmallString::CSmallString()
{
	myUsedSize = 0;
}


CSmallString::~CSmallString()
{
}

bool CSmallString::operator==(const CSmallString & aCompare)
{
	for (int i = 0; i < SMALLSTRING_SIZE; ++i)
	{
		if (myData[i] ^ aCompare.myData[i] == 1)
		{
			return false;
		}
	}

	return true;
}

bool CSmallString::operator!=(const CSmallString & aCompare)
{
	return (*this == aCompare) == false;
}

void CSmallString::operator=(const CSmallString & aSmallString)
{
	for (int i = 0; i < SMALLSTRING_SIZE; ++i)
	{
		myData[i] = aSmallString.myData[i];
	}
	myUsedSize = aSmallString.myUsedSize;
}

bool CSmallString::operator==(char aCharArray[])
{
	unsigned size = strlen(aCharArray);

	if (size > SMALLSTRING_SIZE)
	{
		return false;
	}

	for (int i = 0; i < size; ++i)
	{
		int what = myData[i] ^ aCharArray[i];
		if ((myData[i] ^ aCharArray[i]) == 1)
		{
			return false;
		}
	}

	return true;
}

bool CSmallString::operator!=(char aCharArray[])
{
	return (*this == aCharArray) == false;
}

void CSmallString::operator=(char aCharArray[])
{
	unsigned newSize = strlen(aCharArray);

	if (newSize > SMALLSTRING_SIZE)
	{
		// Too big for SmallString, use MediumString or LargeString instead
		return;
	}

	for (int i = 0; i < newSize; ++i)
	{
		myData[i] = aCharArray[i];
	}
	myData[newSize] = '\0';
	myUsedSize = newSize;
}

CSmallString CSmallString::operator+(const CSmallString & aStringToAdd)
{
	CSmallString rv = *this;

	if (rv.myUsedSize + aStringToAdd.myUsedSize > SMALLSTRING_SIZE)
	{
		// Tried to add a too long string, use MediumString or LargeString instead
		return rv;
	}

	for (int i = rv.myUsedSize; i < aStringToAdd.myUsedSize; ++i)
	{
		rv.myData[i] = aStringToAdd.myData[i - rv.myUsedSize];
	}

	rv.myUsedSize += aStringToAdd.myUsedSize;

	rv.myData[rv.myUsedSize] = '\0';

	return rv;
}

void CSmallString::operator+=(const CSmallString & aStringToAdd)
{
	*this = *this + aStringToAdd;
}

CSmallString CSmallString::operator+(char aCharArray[])
{
	CSmallString rv = *this;

	unsigned size = strlen(aCharArray);

	if (rv.myUsedSize + size > SMALLSTRING_SIZE)
	{
		return rv;
	}

	rv.myData[rv.myUsedSize] = '@';

	for (int i = rv.myUsedSize; i < rv.myUsedSize + size; ++i)
	{
		rv.myData[i] = aCharArray[i - rv.myUsedSize];
	}


	rv.myUsedSize += size;

	rv.myData[rv.myUsedSize] = '\0';

	return rv;
}

void CSmallString::operator+=(char aCharArray[])
{
	*this = *this + aCharArray;
}

std::string CSmallString::ToString()
{
	return std::string(myData);
}
