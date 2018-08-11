#include "Base.h"



CBase::CBase()
{
}


CBase::~CBase()
{
}

std::string CBase::ToString()
{
	return "This class has not overridden the ToString method.";
}

SColor SColor::operator*(float aScalar)
{
	SColor rv = *this;
	rv.a *= aScalar;
	return rv;
}

void SColor::operator*=(float aScalar)
{
	*this = *this * aScalar;
}
