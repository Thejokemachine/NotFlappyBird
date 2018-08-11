#pragma once
#include "Base.h"

#define SMALLSTRING_SIZE 16

class CSmallString : public CBase
{
public:
	CSmallString();
	~CSmallString();

	bool operator==(const CSmallString& aCompare);
	bool operator!=(const CSmallString& aCompare);

	void operator=(const CSmallString& aSmallString);

	bool operator==(char aCharArray[]);
	bool operator!=(char aCharArray[]);

	void operator=(char aCharArray[]);

	CSmallString operator+(const CSmallString& aStringToAdd);
	void operator+=(const CSmallString& aStringToAdd);

	CSmallString operator+(char aCharArray[]);
	void operator+=(char aCharArray[]);

	std::string ToString() override;

private:
	char myData[SMALLSTRING_SIZE];
	unsigned int myUsedSize;
};

