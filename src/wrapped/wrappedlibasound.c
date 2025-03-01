#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <stdarg.h>

#include "wrappedlibs.h"

#include "debug.h"
#include "wrapper.h"
#include "bridge.h"
#include "librarian/library_private.h"
#include "x86emu.h"
#include "emu/x86emu_private.h"
#include "callback.h"
#include "librarian.h"
#include "box86context.h"
#include "emu/x86emu_private.h"
#include "bridge.h"

#define LIBNAME libasound
const char* libasoundName = "libasound.so.2";

typedef void*   (*pFp_t)        (void*);

EXPORT uintptr_t my_snd_lib_error = 0;

static void default_error_handler(const char *file, int line, const char *function, int err, const char *fmt, va_list ap)
{
    vprintf(fmt, ap);
}
    // setup custom error handler
#define ADDED_INIT()\
    my_snd_lib_error = AddCheckBridge(my_context->system, vFpipipV, default_error_handler, 0, "(ASoundCustomErrorHandler)");
#define ADDED_FINI()\
    my_snd_lib_error = 0;   // no removing of bridge

#define ADDED_FUNCTIONS()           \

#include "generated/wrappedlibasoundtypes.h"

#include "wrappercallback.h"

#define SUPER() \
GO(0)   \
GO(1)   \
GO(2)   \
GO(3)

// snd_async_callback_t
#define GO(A)   \
static uintptr_t my_async_fct_##A = 0;   \
static void* my_async_##A(void* handler)     \
{                                       \
    return (void*)RunFunction(my_context, my_async_fct_##A, 1, handler);\
}
SUPER()
#undef GO
static void* findAsyncFct(void* fct)
{
    if(!fct) return fct;
    if(GetNativeFnc((uintptr_t)fct))  return GetNativeFnc((uintptr_t)fct);
    #define GO(A) if(my_async_fct_##A == (uintptr_t)fct) return my_async_##A;
    SUPER()
    #undef GO
    #define GO(A) if(my_async_fct_##A == 0) {my_async_fct_##A = (uintptr_t)fct; return my_async_##A; }
    SUPER()
    #undef GO
    printf_log(LOG_NONE, "Warning, no more slot for Asound Async callback\n");
    return NULL;
}


EXPORT int my_snd_async_add_handler(x86emu_t *emu, void *handler, int fd, void* callback, void *private_data)
{
    return my->snd_async_add_handler(handler, fd, findAsyncFct(callback), private_data);
}

EXPORT int my_snd_async_add_pcm_handler(x86emu_t *emu, void *handler, void* pcm,  void* callback, void *private_data)
{
    return my->snd_async_add_pcm_handler(handler, pcm, findAsyncFct(callback), private_data);
}

static void* current_error_handler = NULL;
static void dummy_error_handler(const char *file, int line, const char *function, int err, const char *fmt, ...)
{
    va_list ap;

    fprintf(ftrace, "Warning: this is a dummy snd_lib error handler\n");
    fprintf(ftrace, "Error in file %s on line %i: ", file, line);
    va_start(ap, fmt);
    vfprintf(ftrace, fmt, ap);
    va_end(ap);
    fflush(ftrace);
}

static void empty_error_handler(const char *file, int line, const char *function, int err, const char *fmt, ...)
{
    // do nothing
}

EXPORT int my_snd_lib_error_set_handler(x86emu_t* emu, void* handler)
{
    current_error_handler = handler;
    void *error_handler;
    uint8_t *code = (uint8_t *)handler;
    if (code) {
        if (code && ((code[0] == 0xC3) || ((code[0] == 0xF3) && (code[1] == 0xC3)))) {
            error_handler = &empty_error_handler;
        } else {
            error_handler = &dummy_error_handler;
            printf_log(LOG_NONE, "Warning: snd_lib_error_set_handler: using dummy error handler\n");
        }
    } else error_handler = NULL;

    return my->snd_lib_error_set_handler(error_handler);
}

void* my_dlopen(x86emu_t* emu, void *filename, int flag);   // defined in wrappedlibdl.c
char* my_dlerror(x86emu_t* emu);
int my_dlclose(x86emu_t* emu, void *handle);
void* my_dlvsym(x86emu_t* emu, void *handle, void *symbol, void *version);
EXPORT void * my_snd_dlopen(x86emu_t* emu, void* name, int mode, void* errbuf, size_t errbuflen)
{
    void* ret = my_dlopen(emu, name, mode);  // Does NULL name (so dlopen libasound) need special treatment?
    if(!ret && errbuf) {
        strncpy(errbuf, my_dlerror(emu), errbuflen);
    }
    return ret;
}
EXPORT int my_snd_dlclose(x86emu_t* emu, void* handle)
{
    return my_dlclose(emu, handle);
}
EXPORT void* my_snd_dlsym(x86emu_t* emu, void* handle, void* name, void* version)
{
    return my_dlvsym(emu, handle, name, version);
}

#define CUSTOM_INIT                     \
    getMy(lib);

#define CUSTOM_FINI                     \
    freeMy();

#include "wrappedlib_init.h"

