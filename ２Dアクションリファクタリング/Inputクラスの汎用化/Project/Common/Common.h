#pragma once

#define _CRT_SECURE_NO_WARNINGS

//C++標準
#include	<iostream>
#include	<iomanip>
#include	<string>
#include	<random>
#include	<vector>
#include	<queue>
#include	<list>
#include	<map>
#include	<unordered_map>
#include	<tuple>
#include	<type_traits>
#include	<memory>
#include	<fstream>
#include	<sstream>
#include	<cmath>
#include	<cassert>
#include	<cstdarg>
#include	<algorithm>
#include	<functional>
#include	<utility>
#include	<thread>
#include	<mutex>

//SAFEDELETE
#define		SAFE_DELETE(x)		{if(x){ delete x; x = nullptr;} }
#define		SAFE_DELETE_ARRAY(x){if(x){ delete[] x; x = nullptr;} }

//C++17以降の場合はあり
#if _HAS_CXX17
#include	<filesystem>
namespace filesystem = std::filesystem;
#include	<any>
using anytype = std::any;
#else
namespace filesystem = std::experimental::filesystem;
using anytype = void*;
#endif /* _HAS_CXX17 */

//MOFライブラリの利用
#define		__MOFLIB
#ifdef 		__MOFLIB
#include	<Mof.h>
#endif		//__MOFLIB