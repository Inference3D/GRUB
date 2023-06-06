//--------------------------------------------------
// Defines a simple helper for generating sequence numbers
//
// @author: Wild Boar
//
// @date: 2023-06-06
//--------------------------------------------------

#pragma once

#include <iostream>
using namespace std;

namespace NVL_App
{
	class Indexer
	{
	private:
		int _index;
	public:
		Indexer(int start = 0) : _index(start) {}
		inline int Next() { return _index++; }
	};
}
