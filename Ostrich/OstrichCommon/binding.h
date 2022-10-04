#pragma once

#ifndef OSTRICH_BINDING
#define OSTRICH_BINDING


#include "icontext.h"

#define OSTRICH_ADDON_EXPORT __declspec(dllexport)

#define OSTRICH_ADDON_INIT(context) extern "C" OSTRICH_ADDON_EXPORT void ostrich_init(hv::v2::iconext * context)

#define OSTRICH_VERSION(version)\
extern "C" OSTRICH_ADDON_EXPORT const char * ostrich_version(){\
	return version;\
}\

#define OSTRICH_NAME(name_arg)\
extern "C" OSTRICH_ADDON_EXPORT const char * ostrich_name() { return #name_arg;}

#define OSTRICH_MODULE\
extern "C" OSTRICH_ADDON_EXPORT const char * ostrich_module(){\
	return true;\
}\





#endif