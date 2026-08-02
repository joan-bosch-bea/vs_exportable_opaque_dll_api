#pragma once

#if defined(_WIN32)
	#ifdef OPAQUELIB_EXPORTS
		#define OPAQUELIB_API __declspec(dllexport)
	#else
		#define OPAQUELIB_API __declspec(dllimport)
	#endif
#else
	#define OPAQUELIB_API
#endif

#ifdef __cplusplus
extern "C" {
#endif
	typedef struct OpaqueHandle OpaqueHandle;

	OPAQUELIB_API OpaqueHandle *Opaque_Create();
	OPAQUELIB_API void Opaque_Destroy(OpaqueHandle *);
	OPAQUELIB_API int Opaque_Suma(OpaqueHandle *, int, int);

#ifdef __cplusplus
}
#endif