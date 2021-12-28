#include "BackBuffer.h"

bool BackBuffer::Initialize()
{
	
	return false;
}

bool BackBuffer::Release()
{
	this->m_pBackBuffer->Release();
	return false;
}
