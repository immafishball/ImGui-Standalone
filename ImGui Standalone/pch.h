#ifndef PCH_H
#define PCH_H

#include <Windows.h>

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <d3d11.h>
#include <tchar.h>

#include "IconsFontAwesome6.h"

// For more info creating and using the compressed font follow:
// TTF TO COMPRESSED: https://github.com/ocornut/imgui/blob/master/misc/fonts/binary_to_compressed_c.cpp
// USE COMPRESSED FONT: https://github.com/ocornut/imgui/blob/master/docs/FONTS.md#loading-font-data-embedded-in-source-code
#include "fa-solid-900.h"

#include "ImGuiNotify.hpp"

#ifdef _DEBUG
#define DX12_ENABLE_DEBUG_LAYER
#endif

#ifdef DX12_ENABLE_DEBUG_LAYER
#include <dxgidebug.h>
#pragma comment(lib, "dxguid.lib")
#endif

#include "imgui_internal.h"


#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

#endif