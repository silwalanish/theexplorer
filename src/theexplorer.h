#pragma once

#ifdef _WIN32
#define THEEXPLORER_EXPORT __declspec(dllexport)
#else
#define THEEXPLORER_EXPORT
#endif

THEEXPLORER_EXPORT void theexplorer();
