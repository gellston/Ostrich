#pragma once

#ifndef OSTRICH_BINDING
#define OSTRICH_BINDING


#include "icontext.h"
#include "addon.h"

#define OSTRICH_ADDON_EXPORT __declspec(dllexport)

#define OSTRICH_ADDON_INIT(context) extern "C" OSTRICH_ADDON_EXPORT bool ostrich_addon_init(hv::v2::icontext * context)

#define OSTRICH_VERSION(version)\
extern "C" OSTRICH_ADDON_EXPORT const char * ostrich_addon_version(){\
	return #version;\
}\

#define OSTRICH_NAME(name_arg)\
extern "C" OSTRICH_ADDON_EXPORT const char * ostrich_addon_name() { return #name_arg;}

#define OSTRICH_MODULE()\
extern "C" OSTRICH_ADDON_EXPORT bool ostrich_addon_module_enable(){\
	return true;\
}\



#ifdef _DEBUG

#define OSTRICH_SANITY_CHECK()\
extern "C" OSTRICH_ADDON_EXPORT bool ostrich_sanity_check(){\
	return false;\
}\

#endif

#ifndef _DEBUG

#define OSTRICH_SANITY_CHECK()\
extern "C" OSTRICH_ADDON_EXPORT bool ostrich_sanity_check(){\
	return true;\
}\

#endif


#endif