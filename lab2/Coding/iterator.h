#pragma once
class Iterator
{
public:
	virtual int freq() = 0;
	virtual char symbol() = 0;
	virtual std::string code() = 0;
	virtual bool has_cur() = 0;
	virtual void next() = 0;
};