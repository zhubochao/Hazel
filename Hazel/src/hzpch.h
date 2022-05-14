#pragma once


#include "Hazel/Core/PlatformDetection.h"

#ifdef HZ_PLATFORM_WINDOWS
	#ifndef NOMINMAX
// See github.com/skypjack/entt/wiki/Frequently-Asked-Questions#warning-c4003-the-min-the-max-and-the-macro
		#define NOMINMAX
	#endif
#endif


#include<iostream>
#include<sstream>
#include<memory>
#include<utility>
#include<algorithm>
#include<functional>

#include<vector>
#include<string>
#include <sstream>
#include<map>
#include<set>
#include<unordered_map>
#include<unordered_set>
#include <array>

#include "Hazel/Core/Base.h"
#include"Hazel/Core/Log.h"
#include "Hazel/Debug/Instrumentor.h"


#ifdef HZ_PLATFORM_WINDOWS
#include<Windows.h>
#endif