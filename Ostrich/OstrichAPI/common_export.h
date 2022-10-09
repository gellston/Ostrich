#pragma once

#ifndef OSTRICH_COMMON_API_MACRO
#define OSTRICH_COMMON_API_MACRO


#ifndef OSTRICH_COMMON_EXPORT
#define OSTRICH_COMMON_API __declspec(dllimport)
#else
#define OSTRICH_COMMON_API __declspec(dllexport)
#endif



#endif