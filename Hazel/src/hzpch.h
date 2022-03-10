#pragma once

#include<iostream>
#include<sstream>
#include<memory>
#include<utility>
#include<algorithm>
#include<functional>

#include<vector>
#include<string>
#include<map>
#include<set>
#include<unordered_map>
#include<unordered_set>

#include"Hazel/Log.h"
#include"Hazel/Events/Event.h"
#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/MouseEvent.h"
#include "Hazel/Events/KeyEvent.h"

#ifdef HZ_PLATFORM_WINDOWS
#include<Windows.h>
#endif