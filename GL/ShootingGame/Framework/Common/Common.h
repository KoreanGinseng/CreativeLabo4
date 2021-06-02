#pragma once

#define        _CRT_SECURE_NO_WARNINGS

//C++標準
#include    <iostream>
#include    <istream>
#include    <fstream>
#include    <sstream>
#include    <iomanip>
#include    <string>
#include    <regex>
#include    <random>
#include    <vector>
#include    <queue>
#include    <list>
#include    <map>
#include    <set>
#include    <unordered_map>
#include    <unordered_set>
#include    <tuple>
#include    <type_traits>
#include    <memory>
#include    <filesystem>
#include    <cstdlib>
#include    <cmath>
#include    <cassert>
#include    <cstdarg>
#include    <algorithm>
#include    <iterator>
#include    <functional>
#include    <utility>
#include    <thread>
#include    <mutex>

//OpenGL関連
#pragma comment (lib, "Library/lib32/GL/OpenGL32.lib")
#pragma comment (lib, "Library/lib32/GLEW/glew32.lib")
#pragma comment (lib, "Library/lib32/GLUT/glut32.lib")
#pragma comment (lib, "Library/lib32/GLFW/glfw3.lib")

#include    "../../Library/include/GLEW/glew.h"
#include    "../../Library/include/GLFW/glfw3.h"
#include    "../../Library/include/GLM/glm.hpp"
#include    "../../Library/include/GLM/mat4x4.hpp"
#include    "../../Library/include/GLM/gtc/matrix_transform.hpp"

//PNG関連
#ifdef _DEBUG
#pragma comment (lib, "Library/lib32/libpng/libpng16d.lib")
#else
#pragma comment (lib, "Library/lib32/libpng/libpng16.lib")
#endif // DEBUG

#include    "../../Library/include/libpng/png.h"

//OpenAL関連
#pragma comment (lib, "Library/lib32/AL/OpenAL32.lib")

#include    "../../Library/include/AL/al.h"
#include    "../../Library/include/AL/alc.h"

//WINDOWS用
#include    <windows.h>
#include    <ks.h>
#include    <ksmedia.h>

//SAFEDELETE
#define        SAFE_DELETE(x)        {if(x){ delete x; x = nullptr;} }
#define        SAFE_DELETE_ARRAY(x){if(x){ delete[] x; x = nullptr;} }

//ログ関連
#if _DEBUG
//Releaseモードでの出力が必要な場合は別途プロジェクトの設定で追加してください
#define        OUTPUTLOG
#endif

#ifdef OUTPUTLOG
#define        INFO_LOG(log)            std::cout << log << std::endl;
#define        ERROR_LOG(log)            std::cerr << log << std::endl;
#define        GL_ERROR_RETURN( estr, ret )    \
    {\
        const GLenum error = glGetError();\
        if (error != GL_NO_ERROR)\
        {\
            ERROR_LOG(estr)\
            return ret;\
        }\
    }
#else
#define        INFO_LOG(log)
#define        ERROR_LOG(log)
#define        GL_ERROR_RETURN( func_name, ret )
#endif

//C++17以降の場合はあり
#if _HAS_CXX17
namespace filesystem = std::filesystem;
#include	<any>
using anytype = std::any;
#else
namespace filesystem = std::experimental::filesystem;
using anytype = void*;
#endif /* _HAS_CXX17 */

#define        __GLLIB