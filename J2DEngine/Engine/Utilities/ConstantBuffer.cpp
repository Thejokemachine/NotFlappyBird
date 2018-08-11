#include "ConstantBuffer.h"

CDirectXFramework* CConstantBuffer::ourFramework;

CConstantBuffer::CConstantBuffer()
{
}


CConstantBuffer::~CConstantBuffer()
{
}

void CConstantBuffer::SetFramework(CDirectXFramework * aFramework)
{
	ourFramework = aFramework;
}
