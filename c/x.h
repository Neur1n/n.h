/******************************************************************************
Copyright (c) 2022 Jihang Li
x.h is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan
PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details.


Last update: 2024-05-26 11:43
Version: v0.7.0
******************************************************************************/
#ifndef X_H
#define X_H x_ver(0, 7, 0)


/** Table of Contents
 * Headers
 *                     IMPL_Compat
 * DECL_Gadget         IMPL_Gadget
 * DECL_x_log          IMPL_x_log
 * DECL_x_err          IMPL_x_err
 * DECL_x_cnd          IMPL_x_cnd
 * DECL_x_mtx          IMPL_x_mtx
 * DECL_x_sem          IMPL_x_sem
 * DECL_x_thd          IMPL_x_thd
 * DECL_x_atomic       IMPL_x_atomic
 * DECL_x_cks          IMPL_x_cks
 * DECL_x_pkt
 * DECL_x_iov
 * DECL_x_skt          IMPL_x_skt
 * DECL_x_node         IMPL_x_node
 * DECL_x_deque        IMPL_x_deque
 * DECL_x_nbque        IMPL_x_nbque
 * DECL_x_tlque        IMPL_x_tlque
 * DECL_x_stopwatch    IMPL_x_stopwatch
 * DECL_x_stopwatch_cu IMPL_x_stopwatch_cu
 */

#define X_EMPTINESS

#ifndef X_ENABLE_CUDA
#define X_ENABLE_CUDA (0)
#endif

#ifndef X_ENABLE_SOCKET
#define X_ENABLE_SOCKET (0)
#endif

//************************************************* Version Number Generator{{{
/**
 * major: [0, 99]
 * minor: [0, 99]
 * patch: [0, 99999], to work with _MSC_FULL_VER
 */
#define x_ver(major, minor, patch) \
  (((major) % 100) * 10000000 + ((minor) % 100) * 100000 + ((patch) % 100000))
// Version Number Generator}}}

//*************************************************** Architecture Detection{{{
#if INTPTR_MAX == INT64_MAX
#define X_32BIT (0)
#define X_64BIT (1)
#elif INTPTR_MAX == INT32_MAX
#define X_32BIT (1)
#define X_64BIT (0)
#else
#error "Only 32-bit or 64-bit architecture is supported."
#endif

#if defined(__arm__) || defined(__thumb__) || defined(_M_ARM)
#define X_ARM (1)
#else
#define X_ARM (0)
#endif

#if defined(__aarch64__)
#define X_ARM64 (1)
#else
#define X_ARM64 (0)
#endif

#if defined(i386) || defined(__i386) || defined(__i386__) \
  || defined(__i486__) || defined(__i586__) || defined(__i686__) \
  || defined(_M_IX86_) || defined(_X86_)
#define X_X86 (1)
#else
#define X_X86 (0)
#endif

#if defined(__amd64) || defined(__amd64__) || defined(__x86_64) \
  || defined(__x86_64__) || defined(_M_AMD64) || defined(_M_X64)
#define X_X64 (1)
#else
#define X_X64 (0)
#endif
// Architecture Detection}}}

//******************************************************* Compiler Detection{{{
#if defined(__clang__)
#define X_CLANG x_ver(__clang_major__, __clang_minor__, __clang_patchlevel__)
#else
#define X_CLANG (0)
#endif

#if defined(__GNUC__)
#define X_GCC x_ver(__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__)
#else
#define X_GCC (0)
#endif

#if defined(_MSC_VER)
#define X_MSVC _MSC_FULL_VER
#else
#define X_MSVC (0)
#endif

#if defined(__NVCC__)
#define X_NVCC x_ver(__CUDACC_VER_MAJOR__, __CUDACC_VER_MINOR__, __CUDACC_VER_BUILD__)

#ifndef X_ENABLE_CUDA
#define X_ENABLE_CUDA (1)
#endif
#else
#define X_NVCC (0)
#endif
// Compiler Detection}}}

//*********************************************** Operating System Detection{{{
#if defined(__CYGWIX__)
#define X_CYGWIN x_ver(CYGWIN_VERSION_API_MAJOR, CYGWIN_VERSION_API_MINOR, 0)
#else
#define X_CYGWIN (0)
#endif

#if defined(__gnu_linux__) || defined(__linux__)
#define X_LINUX (1)
#else
#define X_LINUX (0)
#endif

#if defined(Macintosh) || defined(macintosh)
#define X_MACOS x_ver(9, 0, 0)
#elif defined(__APPLE__) && defined(__MACH__)
#define X_MACOS x_ver(10, 0, 0)
#else
#define X_MACOS (0)
#endif

#if defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) \
  || defined(__TOS_WIX__) || defined(__WINDOWS__)
#define X_WINDOWS (1)
#else
#define X_WINDOWS (0)
#endif
// Operating System Detection}}}

//******************************************************* Platform Detection{{{
#if defined(__ANDROID__)
#define X_ANDROID (1)
#else
#define X_ANDROID (0)
#endif

#if defined(__MINGW32__) || defined(__MINGW64__)
#include <_mingw.h>
#define X_MINGW (1)
#else
#define X_MINGW (0)
#endif

#if defined(__MINGW32__)
#define X_MINGW32 x_ver(__MINGW32_VERSION_MAJOR, __MINGW32_VERSION_MINOR, 0)
#else
#define X_MINGW32 (0)
#endif

#if defined(__MINGW64__)
#define X_MINGW64 x_ver(__MINGW64_VERSION_MAJOR, __MINGW64_VERSION_MINOR, 0)
#else
#define X_MINGW64 (0)
#endif
// Platform Detection}}}

//****************************************************************** Headers{{{
#if X_CLANG || X_GCC
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#endif

#include <assert.h>
#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include <fcntl.h>
#include <sys/stat.h>

#if X_ENABLE_CUDA
#include <cuda_runtime.h>
#endif

#if X_WINDOWS && X_MSVC
#if X_ENABLE_SOCKET
#pragma comment(lib, "Ws2_32")
#include <winsock2.h>
#include <ws2tcpip.h>
#endif

#include <windows.h>
#include <conio.h>
#include <intrin.h>
#include <process.h>
#include <processthreadsapi.h>
#include <synchapi.h>
#elif X_GCC || (!X_MINGW && X_CLANG)
#if X_ENABLE_SOCKET
#include <arpa/inet.h>
#include <sys/socket.h>
#endif

#include <ctype.h>
#include <limits.h>
#include <stdlib.h>

#include <pthread.h>
#include <semaphore.h>
#include <sys/ioctl.h>
#include <sys/sysinfo.h>
#include <termios.h>
#include <unistd.h>
#else
#error "Unsupported build environment."
#endif
// Headers}}}

//************************************************************* Env Specific{{{
// X_EXP, X_IMP
#if X_WINDOWS
#define X_EXP __declspec(dllexport)
#else
#define X_EXP __attribute__ ((visibility("default")))
#endif

#if X_WINDOWS
#define X_IMP __declspec(dllimport)
#else
#define X_IMP __attribute__ ((visibility("hidden")))
#endif

// X_KEY
#define X_KEY_ESC   (0x1B)
#define X_KEY_A     (0x41)
#define X_KEY_B     (0x42)
#define X_KEY_C     (0x43)
#define X_KEY_D     (0x44)
#define X_KEY_Q     (0x51)
#if X_WINDOWS
#define X_KEY_LEFT  (0x4B)
#define X_KEY_UP    (0x48)
#define X_KEY_RIGHT (0x4D)
#define X_KEY_DOWN  (0x50)
#else
#define X_KEY_LEFT  (-1)
#define X_KEY_UP    (-2)
#define X_KEY_RIGHT (-3)
#define X_KEY_DOWN  (-4)
#endif

// Misc
#if X_WINDOWS
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

#define __PRETTY_FUNCTION__ __FUNCSIG__

#define X_PATH_MAX _MAX_PATH
#else
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define X_PATH_MAX PATH_MAX

#ifndef _FILE_OFFSET_BITS
#define _FILE_OFFSET_BITS (64)
#endif
#endif
// Env Specific}}}

#ifdef __cplusplus  //******************************************** C++ Specific
#define X_INL inline

template<class T, size_t N>
X_INL size_t x_count(const T (&array)[N])
{
  return N;
}

template<typename T, bool array>
void x_delete(T*& ptr)
{
  if (ptr != nullptr) {
    if (array) {
      delete[] ptr;
    } else {
      delete ptr;
    }
    ptr = nullptr;
  }
}
#else  //*********************************************************** C Specific
#define X_INL static inline

#define x_count(a) ((sizeof(a) / sizeof(*(a))) / (size_t)(!(sizeof(a) % sizeof(*(a)))))
#endif  // __cplusplus

#ifdef __cplusplus
extern "C" {
#endif
//************************************************************** DECL_Gadget{{{
typedef struct _x_err_
{
  int32_t cat;
  int32_t val;
  bool (*fail)(const int32_t);
} x_err;

#define x_assert(expr, ...) do { \
  if (!(expr)) { \
    fprintf(stderr, "Assertion failed: %s\n", #expr); \
    if (strlen(#__VA_ARGS__)) { \
      fprintf(stderr, "Message: %s\n", __VA_ARGS__); \
    } \
    fprintf(stderr, "Position: %s:%lld: %s\n", \
        __FILENAME__, (long long)__LINE__, __PRETTY_FUNCTION__); \
    abort(); \
  } \
} while (false)

#define _x_arg_n( \
      _1,   _2,   _3,   _4,   _5,   _6,   _7,   _8, \
      _9,  _10,  _11,  _12,  _13,  _14,  _15,  _16, \
     _17,  _18,  _19,  _20,  _21,  _22,  _23,  _24, \
     _25,  _26,  _27,  _28,  _29,  _30,  _31,  _32, \
     _33,  _34,  _35,  _36,  _37,  _38,  _39,  _40, \
     _41,  _42,  _43,  _44,  _45,  _46,  _47,  _48, \
     _49,  _50,  _51,  _52,  _53,  _54,  _55,  _56, \
     _57,  _58,  _59,  _60,  _61,  _62,  _63,  _64, \
     _65,  _66,  _67,  _68,  _69,  _70,  _71,  _72, \
     _73,  _74,  _75,  _76,  _77,  _78,  _79,  _80, \
     _81,  _82,  _83,  _84,  _85,  _86,  _87,  _88, \
     _89,  _90,  _91,  _92,  _93,  _94,  _95,  _96, \
     _97,  _98,  _99, _100, _101, _102, _103, _104, \
    _105, _106, _107, _108, _109, _110, _111, _112, \
    _113, _114, _115, _116, _117, _118, _119, _120, \
    _121, _122, _123, _124, _125, _126, _127,    N, ...) N

#define _x_seq_n() \
  127, 126, 125, 124, 123, 122, 121, 120, \
  119, 118, 117, 116, 115, 114, 113, 112, \
  111, 110, 109, 108, 107, 106, 105, 104, \
  103, 102, 101, 100,  99,  98,  97,  96, \
   95,  94,  93,  92,  91,  90,  89,  88, \
   87,  86,  85,  84,  83,  82,  81,  80, \
   79,  78,  77,  76,  75,  74,  73,  72, \
   71,  70,  69,  68,  67,  66,  65,  64, \
   63,  62,  61,  60,  59,  58,  57,  56, \
   55,  54,  53,  52,  51,  50,  49,  48, \
   47,  46,  45,  44,  43,  42,  41,  40, \
   39,  38,  37,  36,  35,  34,  33,  32, \
   31,  30,  29,  28,  27,  26,  25,  24, \
   23,  22,  21,  20,  19,  18,  17,  16, \
   15,  14,  13,  12,  11,  10,   9,   8, \
    7,   6,   5,   4,   3,   2,   1,   0

#define _x_narg(...) _x_arg_n(__VA_ARGS__)

#define x_narg(...) _x_narg(__VA_ARGS__, _x_seq_n())

#define x_Pi(T) ((T)3.141592653589793238462643383279502884197169399375)

#define x_KiB(T, n) ((T)n * (T)1024)

#define x_MiB(T, n) ((T)n * (T)1048576)

#define x_GiB(T, n) ((T)n * (T)1073741824)

#define x_TiB(T, n) ((T)n * (T)1099511627776)

#define x_TiB(T, n) ((T)n * (T)1099511627776)

#define x_PiB(T, n) ((T)n * (T)1125899906842620)

#define x_bit(bit) (1 << (bit))

X_INL double x_duration(
    const char* unit, const struct timespec start, const struct timespec stop);

#if X_ENABLE_CUDA
X_INL double x_duration_cu(
    const char* unit, const cudaEvent_t start, const cudaEvent_t stop);
#endif

X_INL bool x_fail(const x_err err);

X_INL bool x_fexist(const char* path);

X_INL x_err x_fopen(FILE** stream, const char* file, const char* mode);

X_INL const char* x_fpath(char* dst, const char* src);

#define x_free(ptr) do { \
  if ((ptr) != NULL) { \
    free((void*)ptr); \
    ptr = NULL; \
  } \
} while (false)

#if X_ENABLE_CUDA
#define x_free_cu(ptr) do { \
  if ((ptr) != NULL) { \
    cudaFree((void*)ptr); \
    ptr = NULL; \
  } \
} while (false)
#endif

X_INL long long x_fsize(const char* file);

X_INL size_t x_gcd(const size_t m, const size_t n);

X_INL int x_getch();

X_INL size_t x_lcm(const size_t m, const size_t n);

X_INL x_err x_malloc(void** ptr, const size_t size);

#if X_ENABLE_CUDA
X_INL x_err x_malloc_cu(void** ptr, const size_t size);
#endif

X_INL x_err x_memcpy(void* dst, const void* src, const size_t size);

#if X_ENABLE_CUDA
X_INL x_err x_memcpy_cu(void* dst, const void* src, const size_t size);
#endif

X_INL x_err x_meminfo(size_t* avail, size_t* total);

#if X_ENABLE_CUDA
X_INL x_err x_meminfo_cu(size_t* avail, size_t* total);
#endif

X_INL size_t x_ncpu();

X_INL size_t x_ngpu();

X_INL size_t x_next_exp(const uint64_t base, const uint64_t src);

X_INL size_t x_next_mul(const uint64_t base, const uint64_t src);

X_INL struct timespec x_now();

X_INL size_t x_prev_exp(const size_t base, const size_t src);

X_INL size_t x_prev_mul(const size_t base, const size_t src);

X_INL x_err x_split_path(
    const char* path,
    char* root, const size_t rsz, char* dir, const size_t dsz,
    char* file, const size_t fsz, char* ext, const size_t esz);

X_INL void x_sleep(const unsigned long ms);

X_INL x_err x_strcpy(char* dst, size_t dsz, const char* src);

X_INL bool x_strmty(const char* string);

X_INL bool x_succ(const x_err err);

X_INL const char* x_timestamp(char* buf, const size_t bsz);
// DECL_Gadget}}}

//*************************************************************** DECL_x_log{{{
#define X_LOG_NONE   (-1)
#define X_LOG_PLAIN   (0)
#define X_LOG_FATAL   (1)
#define X_LOG_ERROR   (2)
#define X_LOG_WARNING (3)
#define X_LOG_INFO    (4)
#define X_LOG_DEBUG   (5)

#ifndef X_LOG_LEVEL
#ifdef NDEBUG
#define X_LOG_LEVEL X_LOG_INFO
#else
#define X_LOG_LEVEL X_LOG_DEBUG
#endif
#endif

#ifndef X_LOG_PREFIX_LIMIT
#ifdef NDEBUG
#define X_LOG_PREFIX_LIMIT (64)
#else
#define X_LOG_PREFIX_LIMIT (256)
#endif
#endif

#ifndef X_LOG_MSG_LIMIT
#define X_LOG_MSG_LIMIT (256)
#endif

X_INL void _x_log_impl(
    const char* filename, const char* function, const long line,
    const char level, FILE* file, const char* format, ...);

#define x_log(level, file, format, ...) do { \
  _x_log_impl(__FILENAME__, __FUNCTION__, __LINE__, level, file, format, ##__VA_ARGS__); \
} while (false)
// DECL_x_log}}}

//*************************************************************** DECL_x_err{{{
enum
{
  x_err_custom = 0,
  x_err_posix  = 1,
  x_err_win32  = 2,
  x_err_socket = 3,
#if X_ENABLE_CUDA
  x_err_cuda   = 4,
#endif
  x_err_max,
#if X_WINDOWS
  x_err_system = x_err_win32,
#else
  x_err_system = x_err_posix,
#endif
};

// NOTE: Defined previously in DECL_Gadget.
// typedef struct _x_err_
// {
//   int32_t cat;
//   int32_t val;
//   bool (*fail)(const int32_t);
// } x_err;

X_INL x_err x_ok();

X_INL const char* x_err_msg(char* msg, const size_t msz, const x_err err);

X_INL x_err _x_err_set(const int32_t cat);
X_INL x_err _x_err_set_val(const int32_t cat, ... /*const int32_t val*/);
X_INL x_err _x_err_set_val_fail(const int32_t cat, ... /*const int32_t val, bool (*fail)(const int32_t)*/);

#define x_err_set(cat,  ...) \
  x_narg(cat, ##__VA_ARGS__) == 1 ? _x_err_set(cat) \
    : (x_narg(cat, ##__VA_ARGS__) == 2 ? _x_err_set_val(cat, ##__VA_ARGS__) \
        : _x_err_set_val_fail(cat, ##__VA_ARGS__))
// DECL_x_err}}}

typedef struct _x_cnd_ x_cnd;
typedef struct _x_mtx_ x_mtx;
typedef struct _x_sem_ x_sem;
typedef struct _x_thd_ x_thd;
//*************************************************************** DECL_x_cnd{{{
struct _x_cnd_
{
#if X_WINDOWS
  CONDITION_VARIABLE hndl;
#else
  pthread_cond_t hndl;
#endif
};

#if X_WINDOWS
#define X_CND_INIT {CONDITION_VARIABLE_INIT}
#else
#define X_CND_INIT {PTHREAD_COND_INITIALIZER}
#endif

X_INL x_err x_cnd_init(x_cnd* cnd);

X_INL void x_cnd_dstr(x_cnd* cnd);

X_INL x_err x_cnd_broadcast(x_cnd* cnd);

X_INL x_err x_cnd_signal(x_cnd* cnd);

X_INL x_err x_cnd_timedwait(
    x_cnd* cnd, x_mtx* mtx, const struct timespec* time_point);

X_INL x_err x_cnd_wait(x_cnd* cnd, x_mtx* mtx);
// DECL_x_cnd}}}

//*************************************************************** DECL_x_mtx{{{
struct _x_mtx_
{
#if X_WINDOWS
  void* hndl;
#else
  pthread_mutex_t hndl;
#endif
  int type;
};

enum
{
  x_mtx_plain     = 0,
  x_mtx_recursive = 1,
  x_mtx_timed     = 2,
};

#if X_WINDOWS
#define X_MTX_INIT {NULL, x_mtx_plain}
#else
#define X_MTX_INIT {PTHREAD_MUTEX_INITIALIZER, x_mtx_plain}
#endif

X_INL x_err x_mtx_init(x_mtx* mtx, int type);

X_INL void x_mtx_dstr(x_mtx* mtx);

X_INL x_err x_mtx_lock(x_mtx* mtx);

X_INL x_err x_mtx_timedlock(x_mtx* mtx, const struct timespec* time_point);

X_INL x_err x_mtx_trylock(x_mtx* mtx);

X_INL x_err x_mtx_unlock(x_mtx* mtx);
// DECL_x_mtx}}}

//*************************************************************** DECL_x_sem{{{
struct _x_sem_
{
#if X_WINDOWS
  HANDLE hndl;
#else
  sem_t* hndl;
#endif
};

#if X_WINDOWS
#define X_SEM_INIT {INVALID_HANDLE_VALUE}
#define X_SEM_VALUE_MAX INT_MAX
#else
#define X_SEM_INIT {NULL}
#define X_SEM_VALUE_MAX SEM_VALUE_MAX
#endif

X_INL x_err x_sem_init(x_sem* sem, int pshared, unsigned int value);

X_INL x_err x_sem_dstr(x_sem* sem);

X_INL x_err x_sem_close(x_sem* sem);

X_INL x_err x_sem_getvalue(x_sem* sem, int* sval);

X_INL x_err x_sem_open(x_sem* sem, const char* name, int oflag, ...);

X_INL x_err x_sem_post(x_sem* sem);

X_INL x_err x_sem_unlink(const char* name);

X_INL x_err x_sem_timedwait(x_sem* sem, const struct timespec* abs_timeout);

X_INL x_err x_sem_trywait(x_sem* sem);

X_INL x_err x_sem_wait(x_sem* sem);
// DECL_x_sem}}}

//*************************************************************** DECL_x_thd{{{
struct _x_thd_
{
#if X_WINDOWS
  HANDLE hndl;
#else
  pthread_t hndl;
#endif
  bool exit;
};

#if X_WINDOWS
#define X_THD_INIT {INVALID_HANDLE_VALUE, false}
typedef unsigned int x_thd_rv;
#else
#define X_THD_INIT {{0}, false}
typedef void* x_thd_rv;
#endif
typedef x_thd_rv (*x_thd_routine)(void*);

#if X_WINDOWS
X_INL HANDLE x_thd_current();
#else
X_INL pthread_t x_thd_current();
#endif

X_INL x_err x_thd_init(x_thd* thd, x_thd_routine func, void* data);

X_INL x_err x_thd_detach(x_thd* thd);

X_INL bool x_thd_equal(x_thd lhs, x_thd rhs);

X_INL void x_thd_exit(x_thd_rv exit_code);

X_INL x_err x_thd_getname(x_thd* thd, char* name, const size_t size);

X_INL x_err x_thd_join(x_thd* thd, x_thd_rv* exit_code);

X_INL x_err x_thd_setname(x_thd* thd, const char* name);

X_INL x_err x_thd_yield();
// DECL_x_thd}}}

//************************************************************ DECL_x_atomic{{{
#if X_WINDOWS && X_MSVC
#pragma intrinsic(_ReadBarrier, _ReadWriteBarrier, _WriteBarrier, \
    _InterlockedExchange8, _InterlockedExchange16, \
    _InterlockedExchange, _InterlockedExchange64, \
    _InterlockedCompareExchange8, _InterlockedCompareExchange16, \
    _InterlockedCompareExchange, _InterlockedCompareExchange64, \
    _InterlockedExchangeAdd8, _InterlockedExchangeAdd16, \
    _InterlockedExchangeAdd, _InterlockedExchangeAdd64, \
    _InterlockedOr8, _InterlockedOr16, \
    _InterlockedOr, _InterlockedOr64, \
    _InterlockedXor8, _InterlockedXor16, \
    _InterlockedXor, _InterlockedXor64, \
    _InterlockedAnd8, _InterlockedAnd16, \
    _InterlockedAnd, _InterlockedAnd64, \
    )
#endif  // X_WINDOWS && X_MSVC

typedef struct _x_atomic_8_ x_atomic_8;
typedef struct _x_atomic_16_ x_atomic_16;
typedef struct _x_atomic_32_ x_atomic_32;
typedef struct _x_atomic_64_ x_atomic_64;
typedef struct _x_atomic_ptr_ x_atomic_ptr;
typedef struct _x_atomic_bool_ x_atomic_bool;
typedef struct _x_atomic_flag_ x_atomic_flag;

#define X_ATOMIC_VAR_INIT(bit) { \
  {0}, x_atomic_init_##bit, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL}

#define X_ATOMIC_FLAG_INIT {\
  {false}, x_atomic_flag_test_and_set, x_atomic_flag_clear}

typedef enum _x_memory_order_
{
#if X_CLANG || X_GCC
    x_mo_relaxed = __ATOMIC_RELAXED,
    x_mo_consume = __ATOMIC_CONSUME,
    x_mo_acquire = __ATOMIC_ACQUIRE,
    x_mo_release = __ATOMIC_RELEASE,
    x_mo_acq_rel = __ATOMIC_ACQ_REL,
    x_mo_seq_cst = __ATOMIC_SEQ_CST
#else
    x_mo_relaxed = 0,
    x_mo_consume = 1,
    x_mo_acquire = 2,
    x_mo_release = 3,
    x_mo_acq_rel = 4,
    x_mo_seq_cst = 5
#endif
} x_memory_order;

union _x_a8
{
  uint8_t real;
  char digi;
};

union _x_a16
{
  uint16_t real;
  short digi;
};

union _x_a32
{
  uint32_t real;
#if X_WINDOWS
  long digi;
#else
  int32_t digi;
#endif
};

union _x_a64
{
  uint64_t real;
#if X_WINDOWS
  __int64 digi;
#else
  uint64_t digi;
#endif
};

union _x_abool
{
  bool real;
  char digi;
};

#if X_64BIT
union _x_aptr
{
  void* real;
#if X_WINDOWS
  __int64 digi;
#else
  uint64_t digi;
#endif
};
#else
union _x_aptr
{
  void* real;
#if X_WINDOWS
  long digi;
#else
  int32_t digi;
#endif
};
#endif

#define _X_DECL_ATOMIC_STRUCT(T, bit) \
  struct _x_atomic_##bit##_ { \
    union _x_a##bit data; \
    void (*init)(volatile x_atomic_##bit* obj, T desired); \
    void (*store)( \
        volatile x_atomic_##bit* obj, T desired, x_memory_order order); \
    T (*load)(volatile x_atomic_##bit* obj, x_memory_order order); \
    T (*exchange)( \
        volatile x_atomic_##bit* obj, T desired, x_memory_order order); \
    bool (*compare_exchange)( \
        volatile x_atomic_##bit* obj, T* expected, T desired, \
        x_memory_order succ, x_memory_order fail); \
    T (*fetch_add)(volatile x_atomic_##bit* obj, T arg, x_memory_order order); \
    T (*fetch_sub)(volatile x_atomic_##bit* obj, T arg, x_memory_order order); \
    T (*fetch_or)(volatile x_atomic_##bit* obj, T arg, x_memory_order order); \
    T (*fetch_xor)(volatile x_atomic_##bit* obj, T arg, x_memory_order order); \
    T (*fetch_and)(volatile x_atomic_##bit* obj, T arg, x_memory_order order); \
  };

struct _x_atomic_flag_
{
  union _x_abool data;
  bool (*test_and_set)(volatile x_atomic_flag*, x_memory_order);
  bool (*clear)(volatile x_atomic_flag*, x_memory_order);
};

#define _X_DECL_ATOMIC_FUNCTION(T, bit) \
  X_INL void x_atomic_init_##bit(volatile x_atomic_##bit*, T); \
  X_INL void x_atomic_store_##bit(volatile x_atomic_##bit*, T, x_memory_order); \
  X_INL T x_atomic_load_##bit(volatile x_atomic_##bit*, x_memory_order); \
  X_INL T x_atomic_exchange_##bit(volatile x_atomic_##bit*, T, x_memory_order); \
  X_INL bool x_atomic_compare_exchange_##bit( \
    volatile x_atomic_##bit*, T*, T, x_memory_order, x_memory_order); \
  X_INL T x_atomic_fetch_add_##bit(volatile x_atomic_##bit*, T, x_memory_order); \
  X_INL T x_atomic_fetch_sub_##bit(volatile x_atomic_##bit*, T, x_memory_order); \
  X_INL T x_atomic_fetch_Or_##bit(volatile x_atomic_##bit*, T, x_memory_order); \
  X_INL T x_atomic_fetch_Xor_##bit(volatile x_atomic_##bit*, T, x_memory_order); \
  X_INL T x_atomic_fetch_And_##bit(volatile x_atomic_##bit*, T, x_memory_order);

_X_DECL_ATOMIC_STRUCT(uint8_t, 8)
_X_DECL_ATOMIC_STRUCT(uint16_t, 16)
_X_DECL_ATOMIC_STRUCT(uint32_t, 32)
_X_DECL_ATOMIC_STRUCT(uint64_t, 64)
_X_DECL_ATOMIC_STRUCT(void*, ptr)
_X_DECL_ATOMIC_STRUCT(bool, bool)

_X_DECL_ATOMIC_FUNCTION(uint8_t, 8)
_X_DECL_ATOMIC_FUNCTION(uint16_t, 16)
_X_DECL_ATOMIC_FUNCTION(uint32_t, 32)
_X_DECL_ATOMIC_FUNCTION(uint64_t, 64)
_X_DECL_ATOMIC_FUNCTION(void*, ptr)
_X_DECL_ATOMIC_FUNCTION(bool, bool)

#define x_kill_dependency(x) (x)

#define x_atomic_is_lock_free(T) _x_is_size_lock_free(sizeof(T))

X_INL bool x_atomic_flag_test_and_set(volatile x_atomic_flag*, x_memory_order);

X_INL void x_atomic_flag_clear(volatile x_atomic_flag*, x_memory_order);

X_INL void x_atomic_signal_fence(const x_memory_order order);

X_INL void x_atomic_thread_fence(const x_memory_order order);
// DECL_x_atomic}}}

//*************************************************************** DECL_x_cks{{{
X_INL uint32_t x_cks_crc32(
    const void* data, const size_t size, const uint32_t* prev);

X_INL uint16_t x_cks_rfc1071(const void* data, const size_t size);

X_INL uint8_t x_cks_xor(const void* data, const size_t size);
// DECL_x_cks}}}

//*************************************************************** DECL_x_pkt{{{
typedef struct _x_hdr_
{
  uint16_t sof;  // start of frame
  uint16_t ctl;  // control code
  uint32_t opt;  // option, just use it freely
  uint64_t cnt;  // total count of packets
  uint64_t idx;  // index of current packet
  uint64_t dsz;  // size of the data chunk
  uint64_t cks;  // checksum of packet
} x_hdr;

typedef struct _x_pkt_
{
  x_hdr head;
  void* body;
} x_pkt;

#ifndef X_PKT_SOF
#define X_PKT_SOF (0x55AA)
#endif

#ifndef X_PKT_CNT_INF
#define X_PKT_CNT_INF UINT64_MAX
#endif

#define X_HDR_INIT {X_PKT_SOF, 0, 0, X_PKT_CNT_INF, 0, 0, 0}
#define X_PKT_INIT {X_HDR_INIT, NULL}
// DECL_x_pkt}}}

//*************************************************************** DECL_x_iov{{{
typedef struct _x_iov_
{
  void* buf;
  size_t len;
} x_iov;

#define X_IOV_INIT {NULL, 0}
// DECL_x_iov}}}

#if X_ENABLE_SOCKET
//*************************************************************** DECL_x_skt{{{
typedef struct _x_skt_ x_skt;
struct _x_skt_
{
#if X_WINDOWS
  SOCKET hndl;
#else
  int hndl;
#endif
  struct sockaddr addr;
};

#if X_WINDOWS
#define X_SKT_INIT {INVALID_SOCKET, {0}}
#else
#define X_SKT_INIT {-1, {0}}
#endif

X_INL x_err x_skt_init(x_skt* skt, const int type);

X_INL x_err x_skt_accpet(x_skt* skt, x_skt* acceptee);

X_INL x_err x_skt_addr(x_skt* skt, char* ip, uint16_t* port);

X_INL x_err x_skt_close(x_skt* skt);

X_INL x_err x_skt_connect(x_skt* skt, const char* ip, const uint16_t port);

X_INL x_err x_skt_getopt(
    x_skt* skt, const int lvl, const int opt, void* val, socklen_t* len);

X_INL x_err x_skt_listen(x_skt* skt, const char* ip, const uint16_t port);

X_INL x_err x_skt_recv(
    x_skt* skt, void* buf, const size_t size, const int flags);

X_INL x_err x_skt_recvv(
    x_skt* skt, x_iov* iov, const size_t count, const int flags);

X_INL x_err x_skt_send(
    x_skt* skt, const void* buf, const size_t size, const int flags);

X_INL x_err x_skt_sendv(
    x_skt* skt, const x_iov* iov, const size_t count, const int flags);

X_INL x_err x_skt_setopt(
    x_skt* skt, const int lvl, const int opt, const void* val,
    const socklen_t len);
// DECL_x_skt}}}
#endif  // X_ENABLE_SOCKET

//************************************************************** DECL_x_node{{{
typedef struct _x_node_
{
  void* data;
  struct _x_node_* prev;
  struct _x_node_* next;
} x_node;

#define X_NODE_INIT  {NULL, NULL, NULL}

X_INL x_node* x_node_create(void* data, x_node* prev, x_node* next);

typedef struct _x_anode_ x_anode;

typedef struct _x_anode_
{
  void* data;
  x_atomic_ptr prev;
  x_atomic_ptr next;
} x_anode;

#define X_ANODE_INIT {NULL, X_ATOMIC_VAR_INIT(ptr), X_ATOMIC_VAR_INIT(ptr)}

X_INL x_anode* x_anode_create(void* data, void* prev, void* next);
// DECL_x_node}}}

//************************************************************* DECL_x_deque{{{
#ifndef X_QUE_CAP_INF
#define X_QUE_CAP_INF UINT64_MAX
#endif

typedef struct _x_deque_
{
  uint64_t capacity;
  uint64_t count;
  x_node* head;
  x_node* tail;
} x_deque;

#define X_DEQUE_INIT {X_QUE_CAP_INF, 0, NULL, NULL}

X_INL x_err x_deque_init(x_deque* que, const uint64_t capacity);

X_INL void x_deque_dstr(x_deque* que, void (*dealloc)(void*));

X_INL void x_deque_clear(x_deque* que, void (*dealloc)(void*));

X_INL x_node* x_deque_deq_back(x_deque* que);

X_INL x_node* x_deque_deq_front(x_deque* que);

X_INL x_err x_deque_enq_back(x_deque* que, x_node* const node);

X_INL x_err x_deque_enq_front(x_deque* que, x_node* const node);

X_INL bool x_deque_empty(x_deque* que);

X_INL bool x_deque_full(x_deque* que);

X_INL void* x_deque_pop_back(x_deque* que);

X_INL void* x_deque_pop_front(x_deque* que);

X_INL x_err x_deque_push_back(x_deque* que, void* const data);

X_INL x_err x_deque_push_front(x_deque* que, void* const data);

X_INL x_err x_deque_reserve(x_deque* que, const uint64_t capacity);

X_INL uint64_t x_deque_size(x_deque* que);
// DECL_x_deque}}}

//************************************************************* DECL_x_nbque{{{
typedef struct _x_nbque_ x_nbque;
struct _x_nbque_
{
  volatile x_atomic_64 capacity;
  volatile x_atomic_64 ocnt;
  volatile x_atomic_64 icnt;
  volatile x_atomic_ptr head;
  volatile x_atomic_ptr tail;
  x_err (*init)(x_nbque*, const uint64_t);
  void (*dstr)(x_nbque*, void (*dealloc)(void*));
  x_err (*clear)(x_nbque*, void (*dealloc)(void*));
  bool (*empty)(x_nbque*);
  bool (*full)(x_nbque*);
  void* (*pop)(x_nbque*);
  x_err (*push)(x_nbque*, void* const);
  x_err (*reserve)(x_nbque*, const uint64_t);
  uint64_t (*size)(x_nbque*);
};

#define X_NBQUE_INIT { \
  X_ATOMIC_VAR_INIT(64), X_ATOMIC_VAR_INIT(64), X_ATOMIC_VAR_INIT(64), \
  X_ATOMIC_VAR_INIT(ptr), X_ATOMIC_VAR_INIT(ptr), \
  x_nbque_init, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL}

X_INL x_err x_nbque_init(x_nbque* que, const uint64_t capacity);

X_INL void x_nbque_dstr(x_nbque* que, void (*dealloc)(void*));

X_INL x_err x_nbque_clear(x_nbque* que, void (*dealloc)(void*));

X_INL bool x_nbque_empty(x_nbque* que);

X_INL bool x_nbque_full(x_nbque* que);

X_INL void* x_nbque_pop(x_nbque* que);

X_INL x_err x_nbque_push(x_nbque* que, void* const data);

X_INL x_err x_nbque_reserve(x_nbque* que, const uint64_t capacity);

X_INL uint64_t x_nbque_size(x_nbque* que);
// DECL_x_nbque}}}

//************************************************************* DECL_x_tlque{{{
typedef struct _x_tlque_ x_tlque;
struct _x_tlque_
{
  volatile x_atomic_64 capacity;
  volatile x_atomic_64 count;
  x_deque pool;
  x_node* head;
  x_node* tail;
  x_cnd nmty;
  x_cnd nful;
  x_mtx hlck;
  x_mtx tlck;
  x_err (*init)(x_tlque*, const uint64_t);
  void (*dstr)(x_tlque*, void (*dealloc)(void*));
  x_err (*clear)(x_tlque*, void (*dealloc)(void*));
  bool (*empty)(x_tlque*);
  bool (*full)(x_tlque*);
  void* (*pop)(x_tlque*);
  x_err (*push)(x_tlque*, void* const);
  x_err (*reserve)(x_tlque*, const uint64_t);
  uint64_t (*size)(x_tlque*);
};

#if X_ENABLE_STRUCT_FUNCTION
#define X_TLQUE_INIT { \
  X_ATOMIC_VAR_INIT(64), X_ATOMIC_VAR_INIT(64), X_DEQUE_INIT, NULL, NULL, \
  X_CND_INIT, X_CND_INIT, X_MTX_INIT, X_MTX_INIT, \
  x_tlque_init, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL}
#else
#define X_TLQUE_INIT { \
  X_ATOMIC_VAR_INIT(64), X_ATOMIC_VAR_INIT(64), X_DEQUE_INIT, NULL, NULL, \
  X_CND_INIT, X_CND_INIT, X_MTX_INIT, X_MTX_INIT}
#endif

X_INL x_err x_tlque_init(x_tlque* que, const uint64_t capacity);

X_INL void x_tlque_dstr(x_tlque* que, void (*dealloc)(void*));

X_INL x_err x_tlque_clear(x_tlque* que, void (*dealloc)(void*));

X_INL bool x_tlque_empty(x_tlque* que);

X_INL bool x_tlque_full(x_tlque* que);

X_INL void* x_tlque_pop(x_tlque* que);

X_INL x_err x_tlque_push(x_tlque* que, void* const data);

X_INL x_err x_tlque_reserve(x_tlque* que, const uint64_t capacity);

X_INL uint64_t x_tlque_size(x_tlque* que);
// DECL_x_tlque}}}

//********************************************************* DECL_x_stopwatch{{{
typedef struct _x_swstats_
{
  bool ready;
  size_t cyc;
  double sum;
  double avg;
  struct
  {
    size_t idx;
    double val;
  } max, min;
} x_swstats;

typedef struct _x_stopwatch_
{
  struct timespec start;
  x_swstats stats;
  double elapsed;
} x_stopwatch;

X_INL x_err x_swstats_init(x_swstats* stats);

X_INL x_err x_stopwatch_init(x_stopwatch* sw);

X_INL void x_tic(x_stopwatch* sw, const bool echo);

X_INL void x_toc(x_stopwatch* sw, const char* unit, const bool echo);

X_INL void x_toc_avg(
    x_stopwatch* sw, const char* unit, char* msg, size_t* msz,
    const long long cycle, const char* title, const bool echo);
// DECL_x_stopwatch}}}

//****************************************************** DECL_x_stopwatch_cu{{{
#if X_ENABLE_CUDA
typedef struct _x_stopwatch_cu_
{
  cudaEvent_t start;
  cudaEvent_t stop;
  x_swstats stats;
  double elapsed;
} x_stopwatch_cu;

X_INL void x_stopwatch_cu_dstr(x_stopwatch_cu* sw);

X_INL x_err x_stopwatch_cu_init(x_stopwatch_cu* sw);

X_INL void x_tic_cu(x_stopwatch_cu* sw, const bool echo);

X_INL void x_toc_cu(x_stopwatch_cu* sw, const char* unit, const bool echo);

X_INL void x_toc_avg_cu(
    x_stopwatch_cu* sw, const char* unit, char* msg, size_t* msz,
    const long long cycle, const char* title, const bool echo);
#endif
// DECL_x_stopwatch_cu}}}

//************************************************************** IMPL_Compat{{{
#if !X_WINDOWS
X_INL int _kbhit()
{
  static bool initialized = false;
  if (!initialized) {
    struct termios settings = {0};
    tcgetattr(STDIN_FILENO, &settings);
    settings.c_lflag &= ~ICANON;
    tcsetattr(STDIN_FILENO, TCSANOW, &settings);
    setbuf(stdin, NULL);
    initialized = true;
  }

  int bytes = 0;
  ioctl(STDIN_FILENO, FIONREAD, &bytes);
  return bytes;
}
#endif
// IMPL_Compat}}}

//************************************************************** IMPL_Gadget{{{
double x_duration(
    const char* unit, const struct timespec start, const struct timespec stop)
{
  double diff = (double)(
      (stop.tv_sec - start.tv_sec) * 1000000000 + stop.tv_nsec - start.tv_nsec);

  if (strcmp(unit, "h") == 0) {
    return diff / 3600000000000.0;
  } else if (strcmp(unit, "m") == 0) {
    return diff / 60000000000.0;
  } else if (strcmp(unit, "s") == 0) {
    return diff / 1000000000.0;
  } else if (strcmp(unit, "ms") == 0) {
    return diff / 1000000.0;
  } else if (strcmp(unit, "us") == 0) {
    return diff / 1000.0;
  } else { // if (strcmp(unit, "ns") == 0)
    return diff;
  }
}

#if X_ENABLE_CUDA
double x_duration_cu(
    const char* unit, const cudaEvent_t start, const cudaEvent_t stop)
{
  cudaError_t cerr = cudaEventSynchronize(stop);
  if (cerr != cudaSuccess) {
    fprintf(stderr, "cudaEventSynchronize: %s\n", cudaGetErrorString(cerr));
    return -1.0;
  }

  float ms = 0.0f;
  cerr = cudaEventElapsedTime(&ms, start, stop);
  if (cerr != cudaSuccess) {
    fprintf(stderr, "cudaEventElapsedTime: %s\n", cudaGetErrorString(cerr));
    return -1.0;
  }

  if (strcmp(unit, "h") == 0) {
    return (double)ms / 3600000.0;
  } else if (strcmp(unit, "m") == 0) {
    return (double)ms / 60000.0;
  } else if (strcmp(unit, "s") == 0) {
    return (double)ms / 1000.0;
  } else if (strcmp(unit, "ms") == 0) {
    return (double)ms;
  } else if (strcmp(unit, "us") == 0) {
    return (double)ms * 1000.0;
  } else { // if (strcmp(unit, "ns") == 0)
    return (double)ms * 1000000;
  }
}
#endif

bool x_fail(const x_err err)
{
  if (err.fail) {
    // NOTE: Covers the x_err_custom and other customized cases.
    return err.fail(err.val);
  } else {
    switch (err.cat) {
#if X_WINDOWS
      case x_err_win32:
        return err.val != 0;
#if X_ENABLE_SOCKET
      case x_err_socket:
        return err.val != 0;
#endif
#endif
#if X_ENABLE_CUDA
      case x_err_cuda:
        return err.val != cudaSuccess;
#endif
      default:
        // NOTE: Covers the x_err_posix case.
        return err.val != 0;
    }
  }
}

bool x_fexist(const char* file)
{
  int ierr = 0;

#if X_WINDOWS
  struct _stat64 s = {0};
  ierr = _stat64(file, &s);
#else
  struct stat s = {0};
  ierr = stat(file, &s);
#endif

  return ierr == 0;
}

x_err x_fopen(FILE** stream, const char* file, const char* mode)
{
#if X_WINDOWS
  errno_t ierr = fopen_s(stream, file, mode);
  if (ierr != 0) {
    return x_err_set(x_err_posix, ierr);
  }
#else
  *stream = fopen(file, mode);
  if (*stream == NULL) {
    return x_err_set(x_err_posix);
  }
#endif

  return x_ok();
}

const char* x_fpath(char* dst, const char* src)
{
#if X_WINDOWS
  return dst != NULL ? _fullpath(dst, src, X_PATH_MAX) : NULL;
#else
  return dst != NULL ? realpath(src, dst) : NULL;
#endif
}

long long x_fsize(const char* file)
{
  int ierr = 0;

#if X_WINDOWS
  struct _stat64 s = {0};
  ierr = _stat64(file, &s);
#else
  struct stat s = {0};
  ierr = stat(file, &s);
#endif

  return ierr == 0 ? s.st_size : -1;
}

size_t x_gcd(const size_t m, const size_t n)
{
  return n == 0 ? m : x_gcd(n, m % n);
}

int x_getch()
{
#if X_WINDOWS
  return _kbhit() ? toupper(_getch()) : 0;
#else
  int key = 0;

  int bytes_waiting = _kbhit();
  if (bytes_waiting <= 0) {
    return 0;
  }

  struct termios old_settings = {0};
  struct termios new_settings = {0};
  union {
    int in;
    char ch[4];
  } buf = {0};
  int ierr = 0;
  ssize_t bytes_read = 0;

  ierr = tcgetattr(0, &old_settings);
  if (ierr != 0) {
    return 0;
  }

  new_settings = old_settings;
  new_settings.c_lflag &= ~ICANON;
  new_settings.c_lflag &= ~ECHO;

  ierr = tcsetattr(0, TCSANOW, &new_settings);
  if (ierr != 0) {
    tcsetattr(0, TCSANOW, &old_settings);
    return 0;
  }

  bytes_read = read(STDIN_FILENO, &buf.in, bytes_waiting);
  if (bytes_read <= 0) {
    tcsetattr(0, TCSANOW, &old_settings);
    return 0;
  } else if (bytes_read >= 2) {
    if (buf.ch[0] == 0x1B && buf.ch[1] == 0x5B) {
      if (bytes_read == 2) {
        key = X_KEY_ESC;
      } else {
        switch (buf.ch[2]) {
          case X_KEY_A:
            key = X_KEY_UP;
            break;
          case X_KEY_B:
            key = X_KEY_DOWN;
            break;
          case X_KEY_C:
            key = X_KEY_RIGHT;
            break;
          case X_KEY_D:
            key = X_KEY_LEFT;
            break;
        }
      }
    } else {
      key = buf.ch[0];
    }
  } else {
    key = buf.ch[0];
  }

  tcsetattr(0, TCSADRAIN, &old_settings);

  return isalpha(key) ? toupper(key) : key;
#endif
}

size_t x_lcm(const size_t m, const size_t n)
{
  if (m == 0 || n == 0) {
    return 0;
  }

  return m / x_gcd(m, n) * n;
}

x_err x_malloc(void** ptr, const size_t size)
{
  if (*ptr != NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

  *ptr = malloc(size);
  if (*ptr == NULL) {
    return x_err_set(x_err_posix);
  }

  return x_ok();
}

#if X_ENABLE_CUDA
X_INL x_err x_malloc_cu(void** ptr, const size_t size)
{
  if (*ptr != NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

  cudaError_t cerr = cudaMalloc(ptr, size);
  if (cerr != cudaSuccess) {
    return x_err_set(x_err_cuda, cerr);
  }

  return x_ok();
}
#endif

x_err x_memcpy(void* dst, const void* src, const size_t size)
{
  if (dst == NULL || src == NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

  if (size != 0) {
    memcpy(dst, src, size);
  }

  return x_ok();
}

#if X_ENABLE_CUDA
x_err x_memcpy_cu(void* dst, const void* src, const size_t size)
{
  if (dst == NULL || src == NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

  if (size != 0) {
    cudaError_t cerr = cudaMemcpy(dst, src, size, cudaMemcpyDefault);
    if (cerr != cudaSuccess) {
      return x_err_set(x_err_cuda, cerr);
    }
  }

  return x_ok();
}
#endif

x_err x_meminfo(size_t* avail, size_t* total)
{
  if (avail == NULL && total == NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

#if X_WINDOWS
  MEMORYSTATUSEX status = {0};
  status.dwLength = sizeof(status);

  if (!GlobalMemoryStatusEx(&status)) {
    return x_err_set(x_err_win32);
  }

  if (avail != NULL) {
    *avail = (size_t)status.ullAvailPhys;
  }
  if (total != NULL) {
    *total = (size_t)status.ullTotalPhys;
  }
#else
  struct sysinfo info = {0};
  if (sysinfo(&info) != 0) {
    return x_err_set(x_err_posix);
  }

  if (avail != NULL) {
    *avail = (size_t)info.freeram;
  }
  if (total != NULL) {
    *total = (size_t)info.totalram;
  }
#endif

  return x_ok();
}

#if X_ENABLE_CUDA
x_err x_meminfo_cu(size_t* avail, size_t* total)
{
  if (avail == NULL && total == NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

  cudaError_t cerr = cudaMemGetInfo(avail, total);
  if (cerr != cudaSuccess) {
    return x_err_set(x_err_cuda, cerr);
  }

  return x_ok();
}
#endif

size_t x_ncpu()
{
#if X_WINDOWS
  SYSTEM_INFO info = {0};
  GetSystemInfo(&info);
  return (size_t)info.dwNumberOfProcessors;
#else
  return (size_t)sysconf(_SC_NPROCESSORS_ONLN);
#endif
}

size_t x_ngpu()
{
#if X_ENABLE_CUDA
  int count = 0;
  cudaError_t cerr = cudaGetDeviceCount(&count);
  if (cerr != cudaSuccess) {
    fprintf(stderr, "cudaGetDeviceCount: %s\n", cudaGetErrorString(cerr));
    return 0;
  }

  return (size_t)count;
#else
  return 0;
#endif
}

size_t x_next_exp(const size_t base, const size_t src)
{
  if (src == 0) {
    return 1;
  }

  if (base == 2) {
    if ((src & (src - 1)) == 0) {
      return src;
    }

    size_t s = src;
    size_t count = 0;
    while (s != 0) {
      s >>= 1;
      count += 1;
    }

    return 1 << count;
  } else {
    double exp = log((double)src) / log((double)base);

    if (exp == round(exp)) {
      return src;
    }

    return (size_t)pow((double)base, ceil(exp));
  }
}

size_t x_next_mul(const size_t base, const size_t src)
{
  return (src / base + 1) * base;
}

struct timespec x_now()
{
  struct timespec ts = {0};

#if X_WINDOWS || __STDC_VERSION__ >= 201112L
  timespec_get(&ts, TIME_UTC);
#else
  clock_gettime(CLOCK_MONOTONIC, &ts);
#endif

  return ts;
}

size_t x_prev_exp(const size_t base, const size_t src)
{
  if (src == 0) {
    return 0;
  }

  if (base == 2) {
    if ((src & (src - 1)) == 0) {
      return src;
    }

    size_t s = src;
    size_t count = 0;
    while (s != 0) {
      s >>= 1;
      count += 1;
    }

    return 1 << (count - 1);
  } else {
    double exp = log((double)src) / log((double)base);

    if (exp == round(exp)) {
      return src;
    }

    return (size_t)pow((double)base, floor(exp));
  }
}

size_t x_prev_mul(const size_t base, const size_t src)
{
  return (src / base) * base;
}

x_err x_split_path(
    const char *path,
    char *root, const size_t rsz, char *dir, const size_t dsz,
    char *file, const size_t fsz, char *ext, const size_t esz)
{
  char full[X_PATH_MAX] = {0};
  x_fpath(full, path);

  if (!x_fexist(full)) {
    return x_err_set(x_err_posix, ENOENT);
  }

#if X_WINDOWS
  return x_err_set(
      x_err_posix,
      _splitpath_s(full, root, rsz, dir, dsz, file, fsz, ext, esz));
#else
  if (root == NULL || rsz == 0 || dir == NULL || dsz == 0
      || file == NULL || fsz == 0 || ext == NULL || esz == 0) {
    return x_err_set(x_err_posix, EINVAL);
  }

  if (root != NULL) { root[0] = '\0'; }
  if (dir != NULL) { dir[0] = '\0'; }
  if (file != NULL) { file[0] = '\0'; }
  if (ext != NULL) { ext[0] = '\0'; }

  size_t psz = strlen(full);
  size_t sz = 0;
  char *begin = NULL;
  char *end = NULL;

  // root
  begin = strchr((char*)path, '/');
  if (begin == NULL) {
    return x_err_set(x_err_posix, ENOENT);
  }

  end = strchr(begin + 1, '/');
  if (end == NULL) {
    end = full + psz;
  }

  if (root != NULL) {
    sz = end - begin;
    if (sz >= rsz) {
      return x_err_set(x_err_posix, ENOBUFS);
    }

    memcpy(root, begin, sz);
    root[sz] = '\0';

    if (end == NULL) {
      return x_ok();
    }
  }

  // dir
  begin = strchr(end, '/');
  if (begin == NULL) {
    return x_ok();
  }

  end = strrchr((char*)path, '/');
  if (end <= begin) {
    return x_ok();
  };
  if (end == NULL) {
    end = full + psz;
  }

  if (dir != NULL) {
    sz = end - begin;
    if (sz >= dsz) {
      return x_err_set(x_err_posix, ENOBUFS);
    }

    memcpy(dir, begin, sz);
    dir[sz] = '\0';

    if (end == NULL) {
      return x_ok();
    }
  }

  // file
  begin = end + 1;
  if ((begin - full) >= 0) {
    return x_ok();
  }

  end = strrchr((char*)path, '.');
  if (end <= begin) {
    return x_ok();
  }
  if (end == NULL) {
    end = full + psz;
  }

  if (file != NULL) {
    sz = end - begin;
    if (sz >= fsz) {
      return x_err_set(x_err_posix, ENOBUFS);
    }

    memcpy(file, begin, sz);
    file[sz] = '\0';
  }

  // ext
  if (ext != NULL) {
    begin = end;
    end = full + psz;
    if (end <= begin) {
      return x_ok();
    }

    sz = end - begin;
    memcpy(ext, begin, sz);
    ext[sz] = '\0';
  }

  return x_ok();
#endif
}

void x_sleep(const unsigned long ms)
{
#if X_WINDOWS
  Sleep(ms);
#else
  struct timespec req = {0};
  struct timespec rem = {0};

  req.tv_sec = ms / 1000;
  req.tv_nsec = (long)((ms % 1000) * 1000000);

  if (nanosleep(&req, &rem) == EINTR) {
    nanosleep(&rem, NULL);
  }
#endif
}

x_err x_strcpy(char* dst, size_t dsz, const char* src)
{
  if (dst == NULL || dsz == 0) {
    return x_err_set(x_err_posix, EINVAL);
  }

  size_t cpy_sz = dsz - 1;
  size_t src_sz = strlen(src);

  if (src_sz > 0) {
    cpy_sz = cpy_sz < src_sz ? cpy_sz : src_sz;

    x_err err = x_memcpy(dst, src, cpy_sz);
    if (x_fail(err)) {
      return err;
    }
  }

  dst[cpy_sz] = '\0';

  return x_ok();
}

bool x_strmty(const char* string)
{
  return string == NULL || string[0] == '\0';
}

bool x_succ(const x_err err)
{
  return !x_fail(err);
}

const char* x_timestamp(char* buf, const size_t bsz)
{
  if (buf == NULL) {
    return "";
  }

  time_t now = time(NULL);

#if X_WINDOWS
  int ierr = ctime_s(buf, bsz, &now);
  if (ierr != 0) {
    return "";
  }
#else
  ctime_r(&now, buf);
#endif

  buf[strlen(buf) - 1] = '\0';

  return buf;
}
// IMPL_Gadget}}}

//*************************************************************** IMPL_x_log{{{
#define _X_COLOR_BLACK   "\033[90m"
#define _X_COLOR_RED     "\033[91m"
#define _X_COLOR_GREEN   "\033[92m"
#define _X_COLOR_YELLOW  "\033[93m"
#define _X_COLOR_BLUE    "\033[94m"
#define _X_COLOR_MAGENTA "\033[95m"
#define _X_COLOR_CYAN    "\033[96m"
#define _X_COLOR_WHITE   "\033[97m"
#define _X_COLOR_RESET   "\033[0m"

#define _X_LOG_COLOR_P _X_COLOR_WHITE
#define _X_LOG_COLOR_F _X_COLOR_MAGENTA
#define _X_LOG_COLOR_E _X_COLOR_RED
#define _X_LOG_COLOR_W _X_COLOR_YELLOW
#define _X_LOG_COLOR_I _X_COLOR_GREEN
#define _X_LOG_COLOR_D _X_COLOR_CYAN

X_INL void _x_log_prefix(
    char* buf, size_t bsz,
    const int level, const char* filename, const char* function, const long line)
{
  char timestamp[26] = {0};

#ifdef NDEBUG
  snprintf(buf, bsz, "[%c %s] ", toupper(level), x_timestamp(timestamp, 26));
#else
  snprintf(
      buf, bsz, "[%c %s | %s - %s - %ld] ",
      toupper(level), x_timestamp(timestamp, 26), filename, function, line);
#endif
}

void _x_log_impl(
    const char* filename, const char* function, const long line,
    const char level, FILE* file, const char* format, ...)
{
  char color_level[8] = {0};
  char color_reset[8] = {0};

  if (level == 'p' || level == 'P') {
#if X_LOG_LEVEL >= X_LOG_PLAIN
    snprintf(color_level, 8, _X_LOG_COLOR_P);
#else
    return;
#endif
  } else if (level == 'f' || level == 'F') {
#if X_LOG_LEVEL >= X_LOG_FATAL
    snprintf(color_level, 8, _X_LOG_COLOR_F);
#else
    return;
#endif
  } else if (level == 'e' || level == 'E') {
#if X_LOG_LEVEL >= X_LOG_ERROR
    snprintf(color_level, 8, _X_LOG_COLOR_E);
#else
    return;
#endif
  } else if (level == 'w' || level == 'W') {
#if X_LOG_LEVEL >= X_LOG_WARNING
    snprintf(color_level, 8, _X_LOG_COLOR_W);
#else
    return;
#endif
  } else if (level == 'i' || level == 'I') {
#if X_LOG_LEVEL >= X_LOG_INFO
    snprintf(color_level, 8, _X_LOG_COLOR_I);
#else
    return;
#endif
  } else if (level == 'd' || level == 'D') {
#if X_LOG_LEVEL >= X_LOG_DEBUG
    snprintf(color_level, 8, _X_LOG_COLOR_D);
#else
    return;
#endif
  } else {
    return;
  }

  snprintf(color_reset, 8, _X_COLOR_RESET);

  char prefix[X_LOG_PREFIX_LIMIT] = {0};
  _x_log_prefix(prefix, X_LOG_PREFIX_LIMIT, level, filename, function, line);

  char msg[X_LOG_MSG_LIMIT] = {0};
  va_list args;
  va_start(args, format);
  vsnprintf(msg, X_LOG_MSG_LIMIT, format, args);
  va_end(args);

  if (file == NULL || file == stdout || file == stderr) {
    fprintf(
        file == NULL ? stdout : file,
        "%s%s%s%s\n", color_level, prefix, msg, color_reset);
  } else {
    fprintf(file, "%s%s\n", prefix, msg);
  }
}
// IMPL_x_log}}}

//*************************************************************** IMPL_x_err{{{
x_err _x_err_set(const int32_t cat)
{
  x_err err = x_ok();

  switch (cat) {
    case x_err_posix:
      err.cat = cat;
      err.val = (int32_t)errno;
      break;
#if X_WINDOWS
    case x_err_win32:
      err.cat = cat;
      err.val = (int32_t)GetLastError();
      break;
#if X_ENABLE_SOCKET
    case x_err_socket:
      err.cat = cat;
      err.val = (int32_t)WSAGetLastError();
      break;
#endif
#endif
#if X_ENABLE_CUDA
    case x_err_cuda:
      err.cat = cat;
      err.val = (int32_t)cudaGetLastError();
      break;
#endif
    default:
      char msg[64] = {0};
      snprintf(msg, 32, "Unsupported error category: %d", cat);
#if X_ENABLE_CUDA
      x_assert(
          cat == x_err_posix || cat == x_err_win32 || cat == x_err_socket || cat == x_err_cuda, msg);
#else
      x_assert(
          cat == x_err_posix || cat == x_err_win32 || cat == x_err_socket, msg);
#endif
  }

  return err;
}

x_err _x_err_set_val(const int32_t cat, ...)
{
  va_list args;
  va_start(args, cat);
  int32_t val = va_arg(args, int32_t);
  va_end(args);

  x_err err = {cat, val, NULL};

  return err;
}

x_err _x_err_set_val_fail(const int32_t cat, ...)
{
  typedef bool (*_x_fail_t)(const int32_t);

  va_list args;
  va_start(args, cat);
  int32_t val = va_arg(args, int32_t);
  _x_fail_t fail = va_arg(args, _x_fail_t);
  va_end(args);

  x_err err = {cat, val, fail};

  return err;
}

const char* x_err_msg(char* msg, const size_t msz, const x_err err)
{
  if (msg == NULL || msz == 0) {
    return "";
  }

  switch (err.cat) {
#if X_WINDOWS
    case x_err_posix:
      strerror_s(msg, msz, (int)err.val);
      break;
    case x_err_win32:
    case x_err_socket:
      FormatMessageA(
          FORMAT_MESSAGE_FROM_SYSTEM
          | FORMAT_MESSAGE_IGNORE_INSERTS
          | FORMAT_MESSAGE_MAX_WIDTH_MASK,
          NULL, (DWORD)err.val, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
          msg, msz, NULL);
      break;
#else
    case x_err_posix:
      snprintf(msg, msz, "%s", strerror((int)err.val));
      break;
#endif
#if X_ENABLE_CUDA
    case x_err_cuda:
      snprintf(msg, msz, "%s", cudaGetErrorString((cudaError_t)err.val));
      break;
#endif
    default:
      snprintf(msg, msz, "Custom error %d", err.val);
  }

  return msg;
}

x_err x_ok()
{
  static x_err err = {x_err_posix, 0, NULL};
  return err;
}
// IMPL_x_err}}}

//*************************************************************** IMPL_x_cnd{{{
x_err x_cnd_init(x_cnd* cnd)
{
  if (cnd == NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

#if X_WINDOWS
  InitializeConditionVariable(&cnd->hndl);
  return x_ok();
#else
  return x_err_set(x_err_posix, (int32_t)pthread_cond_init(&cnd->hndl, NULL));
#endif
}

void x_cnd_dstr(x_cnd* cnd)
{
  if (cnd == NULL) {
    return;
  }

#if X_WINDOWS
  (void)cnd;
#else
  pthread_cond_destroy(&cnd->hndl);
#endif
}

x_err x_cnd_broadcast(x_cnd* cnd)
{
  if (cnd == NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

#if X_WINDOWS
  WakeAllConditionVariable(&cnd->hndl);
  return x_ok();
#else
  return x_err_set(x_err_posix, (int32_t)pthread_cond_broadcast(&cnd->hndl));
#endif
}

x_err x_cnd_signal(x_cnd* cnd)
{
  if (cnd == NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

#if X_WINDOWS
  WakeConditionVariable(&cnd->hndl);
  return x_ok();
#else
  return x_err_set(x_err_posix, (int32_t)pthread_cond_signal(&cnd->hndl));
#endif
}

x_err x_cnd_timedwait(
    x_cnd* cnd, x_mtx* mtx, const struct timespec* time_point)
{
#if X_WINDOWS
  if (cnd == NULL || mtx == NULL || mtx->hndl == NULL || time_point == NULL) {
#else
  if (cnd == NULL || mtx == NULL || time_point == NULL) {
#endif
    return x_err_set(x_err_posix, EINVAL);
  }

#if X_WINDOWS
  DWORD d = (DWORD)x_duration("ms", x_now(), *time_point);
  if (mtx->type & x_mtx_recursive) {
    return SleepConditionVariableCS(&cnd->hndl, (CRITICAL_SECTION*)mtx->hndl, d)
      ? x_ok() : x_err_set(x_err_win32);
  } else {
    return SleepConditionVariableSRW(&cnd->hndl, (SRWLOCK*)mtx->hndl, d, 0)
      ? x_ok() : x_err_set(x_err_win32);
  }
#else
  return x_err_set(
      x_err_posix,
      (int32_t)pthread_cond_timedwait(&cnd->hndl, &mtx->hndl, time_point));
#endif
}

x_err x_cnd_wait(x_cnd* cnd, x_mtx* mtx)
{
#if X_WINDOWS
  if (cnd == NULL || mtx == NULL || mtx->hndl == NULL) {
#else
  if (cnd == NULL || mtx == NULL) {
#endif
    return x_err_set(x_err_posix, EINVAL);
  }

#if X_WINDOWS
  BOOL succeeded = FALSE;

  if (mtx->type & x_mtx_recursive) {
    succeeded = SleepConditionVariableCS(
        &cnd->hndl, (CRITICAL_SECTION*)mtx->hndl, INFINITE);
  } else {
    succeeded = SleepConditionVariableSRW(
        &cnd->hndl, (SRWLOCK*)mtx->hndl, INFINITE, 0);
  }
  if (!succeeded) {
    return x_err_set(x_err_win32);
  }

  return x_ok();
#else
  return x_err_set(
      x_err_posix, (int32_t)pthread_cond_wait(&cnd->hndl, &mtx->hndl));
#endif
}
// IMPL_x_cnd}}}

//*************************************************************** IMPL_x_mtx{{{
x_err x_mtx_init(x_mtx* mtx, int type)
{
#if X_WINDOWS
  if (mtx == NULL || mtx->hndl != NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

  if (type & x_mtx_recursive) {
    mtx->hndl = malloc(sizeof(CRITICAL_SECTION));
    if (mtx->hndl == NULL) {
      return x_err_set(x_err_posix);
    }
    InitializeCriticalSection((CRITICAL_SECTION*)mtx->hndl);
  } else {
    mtx->hndl = malloc(sizeof(SRWLOCK));
    if (mtx->hndl == NULL) {
      return x_err_set(x_err_posix);
    }
    InitializeSRWLock((SRWLOCK*)mtx->hndl);
  }

  mtx->type = type;

  return x_ok();
#else
  if (mtx == NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

  int ierr = 0;

  pthread_mutexattr_t attr;
  ierr = pthread_mutexattr_init(&attr);
  if (ierr != 0) {
    return x_err_set(x_err_posix, (int32_t)ierr);
  }

  if (type & x_mtx_recursive) {
    ierr = pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
  } else {
    ierr = pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_NORMAL);
  }
  if (ierr != 0) {
    return x_err_set(x_err_posix, (int32_t)ierr);
  }

  mtx->type = type;

  return x_err_set(
      x_err_posix, (int32_t)pthread_mutex_init(&mtx->hndl, &attr));
#endif
}

void x_mtx_dstr(x_mtx* mtx)
{
#if X_WINDOWS
  if (mtx == NULL || mtx->hndl == NULL) {
    return;
  }

  if (mtx->type & x_mtx_recursive) {
    CRITICAL_SECTION* m = (CRITICAL_SECTION*)mtx->hndl;
    DeleteCriticalSection(m);
    x_free(m);
  } else {
    SRWLOCK* m = (SRWLOCK*)mtx->hndl;
    x_free(m);
  }
#else
  if (mtx == NULL) {
    return;
  }

  pthread_mutex_destroy(&mtx->hndl);
#endif
}

x_err x_mtx_lock(x_mtx* mtx)
{
#if X_WINDOWS
  if (mtx == NULL || mtx->hndl == NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

  if (mtx->type & x_mtx_recursive) {
    EnterCriticalSection((CRITICAL_SECTION*)mtx->hndl);
  } else {
    AcquireSRWLockExclusive((SRWLOCK*)mtx->hndl);
  }

  return x_ok();
#else
  if (mtx == NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

  return x_err_set(x_err_posix, (int32_t)pthread_mutex_lock(&mtx->hndl));
#endif
}

x_err x_mtx_timedlock(x_mtx* mtx, const struct timespec* time_point)
{
#if X_WINDOWS
  if (mtx == NULL || mtx->hndl == NULL || (mtx->type & x_mtx_timed) == 0
      || time_point == NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

  DWORD ms = (DWORD)x_duration("ms", x_now(), *time_point);
  return (WaitForSingleObject(mtx->hndl, ms) == WAIT_OBJECT_0
      ? x_ok() : x_err_set(x_err_win32));
#else
  if (mtx == NULL || (mtx->type & x_mtx_timed) == 0 || time_point == NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

  return x_err_set(
      x_err_posix, (int32_t)pthread_mutex_timedlock(&mtx->hndl, time_point));
#endif
}

x_err x_mtx_trylock(x_mtx* mtx)
{
#if X_WINDOWS
  if (mtx == NULL || mtx->hndl == NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

  if (mtx->type & x_mtx_recursive) {
    return TryEnterCriticalSection((CRITICAL_SECTION*)mtx->hndl)
      ? x_ok() : x_err_set(x_err_posix, EAGAIN);
  } else {
    return TryAcquireSRWLockExclusive((SRWLOCK*)mtx->hndl)
      ? x_ok() : x_err_set(x_err_posix, EAGAIN);
  }
#else
  if (mtx == NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

  return x_err_set(x_err_posix, (int32_t)pthread_mutex_trylock(&mtx->hndl));
#endif
}

x_err x_mtx_unlock(x_mtx* mtx)
{
#if X_WINDOWS
  if (mtx == NULL || mtx->hndl == NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

  if (mtx->type & x_mtx_recursive) {
    LeaveCriticalSection((CRITICAL_SECTION*)mtx->hndl);
  } else {
    ReleaseSRWLockExclusive((SRWLOCK*)mtx->hndl);
  }

  return x_ok();
#else
  if (mtx == NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

  return x_err_set(x_err_posix, (int32_t)pthread_mutex_unlock(&mtx->hndl));
#endif
}
// IMPL_x_mtx}}}

//*************************************************************** IMPL_x_sem{{{
x_err x_sem_init(x_sem* sem, int pshared, unsigned int value)
{
#if X_WINDOWS
  if (sem == NULL || value > X_SEM_VALUE_MAX) {
    return x_err_set(x_err_posix, EINVAL);
  }

  HANDLE s = CreateSemaphoreA(NULL, value, X_SEM_VALUE_MAX, NULL);
  if (s == NULL) {
    return x_err_set(x_err_win32);
  }

  sem->hndl = s;

  return x_ok();
#else
  if (sem == NULL || sem->hndl != NULL || value > X_SEM_VALUE_MAX) {
    return x_err_set(x_err_posix, EINVAL);
  }

  sem->hndl = (sem_t*)malloc(sizeof(sem_t));
  if (sem->hndl == NULL) {
    return x_err_set(x_err_posix);
  }

  return sem_init(sem->hndl, pshared, value) == 0 ? x_ok() : x_err_set(x_err_posix);
#endif
}

x_err x_sem_dstr(x_sem* sem)
{
#if X_WINDOWS
  if (sem == NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

  return CloseHandle(sem->hndl) ? x_ok() : x_err_set(x_err_win32);
#else
  if (sem == NULL || sem->hndl == NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

  x_err err = x_ok();

  if (sem_destroy(sem->hndl) != 0) {
    err = x_err_set(x_err_posix);
  }

  x_free(sem->hndl);

  return err;
#endif
}

x_err x_sem_close(x_sem* sem)
{
#if X_WINDOWS
  if (sem == NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

  return CloseHandle(sem->hndl) ? x_ok() : x_err_set(x_err_win32);
#else
  if (sem == NULL || sem->hndl == NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

  return sem_close(sem->hndl) == 0 ? x_ok() : x_err_set(x_err_posix);
#endif
}

x_err x_sem_getvalue(x_sem* sem, int* sval)
{
#if X_WINDOWS
  if (sem == NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

  if (WaitForSingleObject(sem->hndl, 0) != WAIT_OBJECT_0) {
    return x_err_set(x_err_win32);
  }

  long value = 0;
  if (!ReleaseSemaphore(sem->hndl, 1, &value)) {
    return x_err_set(x_err_win32);
  }

  *sval = (int)value;

  return x_ok();
#else
  if (sem == NULL || sem->hndl == NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

  return sem_getvalue(sem->hndl, sval) == 0 ? x_ok() : x_err_set(x_err_posix);
#endif
}

x_err x_sem_open(x_sem* sem, const char* name, int oflag, ...)
{
#if X_WINDOWS
  if (sem == NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

  HANDLE s = INVALID_HANDLE_VALUE;

  if (oflag & _O_CREAT) {
    va_list args;
    va_start(args, oflag);
    va_arg(args, int);
    unsigned int value = va_arg(args, unsigned int);
    s = CreateSemaphoreA(NULL, value, X_SEM_VALUE_MAX, name);
    va_end(args);
  } else {
    s = OpenSemaphoreA(STANDARD_RIGHTS_ALL, TRUE, name);
  }

  if (s == NULL) {
    return x_err_set(x_err_win32);
  }

  sem->hndl = s;
#else
  if (sem == NULL || sem->hndl != NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

  sem_t* s = SEM_FAILED;

  if (oflag & O_CREAT) {
    va_list args;
    va_start(args, oflag);
    s = sem_open(name, oflag, args);
    va_end(args);
  } else {
    s = sem_open(name, oflag);
  }

  if (s == SEM_FAILED) {
    return x_err_set(x_err_posix);
  }

  sem->hndl = s;
#endif

  return x_ok();
}

x_err x_sem_post(x_sem* sem)
{
#if X_WINDOWS
  if (sem == NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

  return ReleaseSemaphore(sem->hndl, 1, NULL) ? x_ok() : x_err_set(x_err_win32);
#else
  if (sem == NULL || sem->hndl != NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

  return sem_post(sem->hndl) == 0 ? x_ok() : x_err_set(x_err_posix);
#endif
}

x_err x_sem_unlink(const char* name)
{
#if X_WINDOWS
  HANDLE s = OpenSemaphoreA(STANDARD_RIGHTS_ALL, TRUE, name);
  if (s == NULL) {
    return x_err_set(x_err_win32);
  }

  return CloseHandle(s) ? x_ok() : x_err_set(x_err_win32);
#else
  return sem_unlink(name) == 0 ? x_ok() : x_err_set(x_err_posix);
#endif
}

x_err x_sem_timedwait(x_sem* sem, const struct timespec* abs_timeout)
{
#if X_WINDOWS
  if (sem == NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

  DWORD ms = (DWORD)x_duration("ms", x_now(), *abs_timeout);
  return WaitForSingleObject(sem->hndl, ms) == WAIT_OBJECT_0
    ? x_ok() : x_err_set(x_err_win32);
#else
  if (sem == NULL || sem->hndl != NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

  return sem_timedwait(sem->hndl, abs_timeout) == 0
    ? x_ok() : x_err_set(x_err_posix);
#endif
}

x_err x_sem_trywait(x_sem* sem)
{
#if X_WINDOWS
  if (sem == NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

  return WaitForSingleObject(sem->hndl, 0) == WAIT_OBJECT_0
    ? x_ok() : x_err_set(x_err_win32);
#else
  if (sem == NULL || sem->hndl != NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

  return sem_trywait(sem->hndl) == 0 ? x_ok() : x_err_set(x_err_posix);
#endif
}

x_err x_sem_wait(x_sem* sem)
{
#if X_WINDOWS
  if (sem == NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

  return WaitForSingleObject(sem->hndl, INFINITE) == WAIT_OBJECT_0
    ? x_ok() : x_err_set(x_err_win32);
#else
  if (sem == NULL || sem->hndl != NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

  return sem_wait(sem->hndl) == 0 ? x_ok() : x_err_set(x_err_posix);
#endif
}
// IMPL_x_sem}}}

//*************************************************************** IMPL_x_thd{{{
x_err x_thd_init(x_thd* thd, x_thd_routine func, void* data)
{
  if (thd == NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

#if X_WINDOWS
  thd->hndl = (HANDLE)_beginthreadex(NULL, 0, func, data, 0, NULL);
  if (thd->hndl == 0) {
    return x_err_set(x_err_posix);
  }
#else
  int ierr = pthread_create(&thd->hndl, NULL, func, data);
  if (ierr != 0) {
    return x_err_set(x_err_posix, (int32_t)ierr);
  }
#endif

  thd->exit = false;

  return x_ok();
}

#if X_WINDOWS
HANDLE x_thd_current()
{
  return GetCurrentThread();
}
#else
pthread_t x_thd_current()
{
  return pthread_self();
}
#endif

x_err x_thd_detach(x_thd* thd)
{
  if (thd == NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

  thd->exit = true;

#if X_WINDOWS
  return CloseHandle(thd->hndl) ? x_ok() : x_err_set(x_err_win32);
#else
  return pthread_detach(thd->hndl) == 0 ? x_ok() : x_err_set(x_err_posix);
#endif
}

bool x_thd_equal(x_thd lhs, x_thd rhs)
{
  return lhs.hndl == rhs.hndl;
}

void x_thd_exit(x_thd_rv exit_code)
{
#if X_WINDOWS
  _endthreadex(exit_code);
#else
  pthread_exit(exit_code);
#endif
}

x_err x_thd_getname(x_thd* thd, char* name, const size_t size)
{
  if (name == NULL || size == 0 || thd == NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

#if X_WINDOWS
  wchar_t* src = NULL;
  HRESULT hr = GetThreadDescription(thd->hndl, &src);
  if (FAILED(hr)) {
    return x_err_set(x_err_win32, (int32_t)hr);
  }

  size_t len = 0;
  char dst[16] = {0};
  errno_t ierr = wcstombs_s(&len, dst, 16, src, 15);
  if (ierr == 0) {
    ierr = strcpy_s(name, size, dst);
  }

  LocalFree(src);

  return ierr == 0 ? x_ok() : x_err_set(x_err_posix, (int32_t)ierr);
#else
  return x_err_set(x_err_posix, (int32_t)pthread_getname_np(thd->hndl, name, 16));
#endif
}

x_err x_thd_join(x_thd* thd, x_thd_rv* exit_code)
{
  if (thd == NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

#if X_WINDOWS
  if (WaitForSingleObject(thd->hndl, INFINITE) != WAIT_OBJECT_0) {
    return x_err_set(x_err_win32);
  }

  DWORD ierr = 0;
  if (GetExitCodeThread(thd->hndl, &ierr) == 0) {
    return x_err_set(x_err_win32);
  }

  if (exit_code != NULL) {
    *exit_code = (x_thd_rv)ierr;
  }

  return x_thd_detach(thd);
#else
  void* rv = NULL;
  int ierr = pthread_join(thd->hndl, &rv);

  if (exit_code != NULL) {
    *exit_code = (x_thd_rv)(intptr_t)ierr;  // intptr_t to avoid a warning.
  }

  return x_err_set(x_err_posix, (int32_t)ierr);
#endif
}

x_err x_thd_setname(x_thd* thd, const char* name)
{
  if (thd == NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

  if (strlen(name) > 16) {
    return x_err_set(x_err_posix, ENOBUFS);
  }

#if X_WINDOWS
  size_t len = 0;
  wchar_t data[16] = {0};
  errno_t ierr = mbstowcs_s(&len, data, 16, name, 15);
  if (ierr != 0) {
    return x_err_set(x_err_posix, ierr);
  }

  HRESULT hr = SetThreadDescription(thd->hndl, data);

  return SUCCEEDED(hr) ? x_ok() : x_err_set(x_err_win32, hr);
#else
  return x_err_set(x_err_posix, (int32_t)pthread_setname_np(thd->hndl, name));
#endif
}

x_err x_thd_yield()
{
#if X_WINDOWS
  return SwitchToThread() ? x_ok() : x_err_set(x_err_win32);
#else
  return sched_yield() == 0 ? x_ok() : x_err_set(x_err_posix);
#endif
}
// IMPL_x_thd}}}

//************************************************************ IMPL_x_atomic{{{
#if X_MSVC
#ifdef __cplusplus
#define _InterlockedExchangebool        _InterlockedExchange8
#define _InterlockedCompareExchangebool _InterlockedCompareExchange8
#define _InterlockedExchangeAddbool     _InterlockedExchangeAdd8
#define _InterlockedOrbool              _InterlockedOr8
#define _InterlockedXorbool             _InterlockedXor8
#define _InterlockedAndbool             _InterlockedAnd8
#else
#define _InterlockedExchange_Bool        _InterlockedExchange8
#define _InterlockedCompareExchange_Bool _InterlockedCompareExchange8
#define _InterlockedExchangeAdd_Bool     _InterlockedExchangeAdd8
#define _InterlockedOr_Bool              _InterlockedOr8
#define _InterlockedXor_Bool             _InterlockedXor8
#define _InterlockedAnd_Bool             _InterlockedAnd8
#endif  // __cplusplus

#if X_64BIT
#define _InterlockedExchangeptr        _InterlockedExchange64
#define _InterlockedCompareExchangeptr _InterlockedCompareExchange64
#define _InterlockedExchangeAddptr     _InterlockedExchangeAdd64
#define _InterlockedOrptr              _InterlockedOr64
#define _InterlockedXorptr             _InterlockedXor64
#define _InterlockedAndptr             _InterlockedAnd64
#else
#define _InterlockedExchangeptr        _InterlockedExchange
#define _InterlockedCompareExchangeptr _InterlockedCompareExchange
#define _InterlockedExchangeAddptr     _InterlockedExchangeAdd
#define _InterlockedOrptr              _InterlockedOr
#define _InterlockedXorptr             _InterlockedXor
#define _InterlockedAndptr             _InterlockedAnd
#endif

#define _InterlockedExchange32        _InterlockedExchange
#define _InterlockedCompareExchange32 _InterlockedCompareExchange
#define _InterlockedExchangeAdd32     _InterlockedExchangeAdd
#define _InterlockedOr32              _InterlockedOr
#define _InterlockedXor32             _InterlockedXor
#define _InterlockedAnd32             _InterlockedAnd
#elif X_CLANG || X_GCC
#define _X_atomic_fetch_Or  __atomic_fetch_or
#define _X_atomic_fetch_Xor __atomic_fetch_xor
#define _X_atomic_fetch_And __atomic_fetch_and
#endif

#if X_MSVC
#define _X_SNIP_ATOMIC_XCHG(ret, obj, des, order, bit) do { \
  (void)order; \
  ret.digi = _InterlockedExchange##bit(&(obj->data.digi), des.digi); \
} while (false)
#elif X_CLANG || X_GCC
#define _X_SNIP_ATOMIC_XCHG(ret, obj, des, order, bit) do { \
  ret.real = __atomic_exchange_n(&(obj->data.real), des.real, order); \
} while (false)
#endif

#if X_MSVC
#define _X_SNIP_ATOMIC_CMP_XCHG(ret, obj, exp, des, succ, fail, ...) do { \
  (void)succ; (void)fail; \
  ret = (obj->data.digi == exp.digi); \
  _InterlockedCompareExchange##__VA_ARGS__( \
      &(obj->data.digi), des.digi, exp.digi); \
} while (false)
#elif X_CLANG || X_GCC
#define _X_SNIP_ATOMIC_CMP_XCHG(ret, obj, exp, des, succ, fail, ...) do { \
  ret = __atomic_compare_exchange_n( \
      &(obj->data.real), &(exp.real), des.real, false, succ, fail); \
} while (false)
#endif

#if X_MSVC
#define _X_SNIP_ATOMIC_ADD(ret, obj, arg, order, bit) do { \
  (void)order; \
  ret.digi = _InterlockedExchangeAdd##bit(&(obj->data.digi), arg.digi); \
} while (false)

#define _X_SNIP_ATOMIC_ADD_BOOL(ret, obj, arg, order, bit) do { \
  ret.digi = _InterlockedExchangeAdd##bit(&(obj->data.digi), arg.digi); \
  ret.real = (ret.digi != 0); \
} while (false)
#elif X_CLANG || X_GCC
#define _X_SNIP_ATOMIC_ADD(ret, obj, arg, order, bit) do { \
  ret.digi = __atomic_fetch_add(&(obj->data.digi), arg.digi, order); \
} while (false)

#define _X_SNIP_ATOMIC_ADD_BOOL(ret, obj, arg, order, bit) do { \
  ret.digi = __atomic_fetch_add(&(obj->data.digi), arg.digi, order); \
  ret.real = (ret.digi != 0); \
} while (false)
#endif

#if X_MSVC
#define _X_SNIP_ATOMIC_SUB(ret, obj, arg, order, bit) do { \
  (void)order; \
  ret.digi = _InterlockedExchangeAdd##bit(&(obj->data.digi), -(arg.digi)); \
} while (false)

#define _X_SNIP_ATOMIC_SUB_BOOL(ret, obj, arg, order, bit) do { \
  ret.digi = _InterlockedExchangeAdd##bit(&(obj->data.digi), -(arg.digi)); \
  ret.real = (ret.digi != 0); \
} while (false)
#elif X_CLANG || X_GCC
#define _X_SNIP_ATOMIC_SUB(ret, obj, arg, order, bit) do { \
  ret.digi = __atomic_fetch_sub(&(obj->data.digi), arg.digi, order); \
} while (false)

#define _X_SNIP_ATOMIC_SUB_BOOL(ret, obj, arg, order, bit) do { \
  ret.digi = __atomic_fetch_sub(&(obj->data.digi), arg.digi, order); \
  ret.real = (ret.digi != 0); \
} while (false)
#endif

#if X_MSVC
#define _X_SNIP_ATOMIC_LOGIC(op, ret, obj, arg, order, bit) do { \
  (void)order; \
  ret.digi = _Interlocked##op##bit(&(obj->data.digi), arg.digi); \
} while (false)

#define _X_SNIP_ATOMIC_LOGIC_BOOL(op, ret, obj, arg, order, bit) do { \
  ret.digi = _Interlocked##op##bit(&(obj->data.digi), arg.digi); \
  ret.real = (ret.digi != 0); \
} while (false)
#elif X_CLANG || X_GCC
#define _X_SNIP_ATOMIC_LOGIC(op, ret, obj, arg, order, bit) do { \
  ret.digi = _X_atomic_fetch_##op(&(obj->data.digi), arg.digi, order); \
} while (false)

#define _X_SNIP_ATOMIC_LOGIC_BOOL(op, ret, obj, arg, order, bit) do { \
  ret.digi = _X_atomic_fetch_##op(&(obj->data.digi), arg.digi, order); \
  ret.real = (ret.digi != 0); \
} while (false)
#endif

#define _X_ATOMIC_LOCK(mtx) \
  x_mtx mtx = X_MTX_INIT; \
  x_mtx_init(&mtx, x_mtx_plain); \
  x_mtx_lock(&mtx);

#define _X_ATOMIC_UNLOCK(mtx) \
  x_mtx_lock(&mtx); \
  x_mtx_destroy(&mtx);

#define _X_IMPL_ATOMIC_INIT(T, bit) \
  void x_atomic_init_##bit(volatile x_atomic_##bit* obj, T desired) { \
    assert(obj != NULL); \
    obj->data.real = desired; \
    obj->init = x_atomic_init_##bit; \
    obj->store = x_atomic_store_##bit; \
    obj->load = x_atomic_load_##bit; \
    obj->exchange = x_atomic_exchange_##bit; \
    obj->compare_exchange = x_atomic_compare_exchange_##bit; \
    obj->fetch_add = x_atomic_fetch_add_##bit; \
    obj->fetch_sub = x_atomic_fetch_sub_##bit; \
    obj->fetch_or = x_atomic_fetch_Or_##bit; \
    obj->fetch_xor = x_atomic_fetch_Xor_##bit; \
    obj->fetch_and = x_atomic_fetch_And_##bit; \
  }

#define _X_IMPL_ATOMIC_STORE(T, bit, LOCK, UNLOCK) \
  void x_atomic_store_##bit( \
      volatile x_atomic_##bit* obj, T desired, x_memory_order order) { \
    assert(obj != NULL); \
    if (order == x_mo_acquire || order == x_mo_acq_rel) { \
      order = x_mo_seq_cst; \
    } \
    LOCK \
    x_atomic_thread_fence(order); \
    obj->data.real = desired; \
    UNLOCK \
  }

#define _X_IMPL_ATOMIC_LOAD(T, bit, LOCK, UNLOCK) \
  T x_atomic_load_##bit(volatile x_atomic_##bit* obj, x_memory_order order) { \
    assert(obj != NULL); \
    if (order == x_mo_release || order == x_mo_acq_rel) { \
      order = x_mo_seq_cst; \
    } \
    LOCK \
    T val = obj->data.real; \
    x_atomic_thread_fence(order); \
    UNLOCK \
    return val; \
  }

#define _X_IMPL_ATOMIC_XCHG(T, bit, LOCK, UNLOCK) \
  T x_atomic_exchange_##bit( \
      volatile x_atomic_##bit* obj, T desired, x_memory_order order) { \
    assert(obj != NULL); \
    union _x_a##bit old = {0}; \
    union _x_a##bit des = {desired}; \
    LOCK \
    _X_SNIP_ATOMIC_XCHG(old, obj, des, order, bit); \
    UNLOCK \
    return old.real; \
  }

#define _X_IMPL_ATOMIC_CMP_XCHG(T, bit, LOCK, UNLOCK) \
  bool x_atomic_compare_exchange_##bit( \
      volatile x_atomic_##bit* obj, T* expected, T desired, \
      x_memory_order succ, x_memory_order fail) { \
    assert(obj != NULL); \
    bool succeeded = false; \
    union _x_a##bit exp = {*expected}; \
    union _x_a##bit des = {desired}; \
    LOCK \
    _X_SNIP_ATOMIC_CMP_XCHG(succeeded, obj, exp, des, succ, fail, bit); \
    UNLOCK \
    return succeeded; \
  }

#define _X_IMPL_ATOMIC_ADD(T, bit, LOCK, UNLOCK) \
  T x_atomic_fetch_add_##bit( \
      volatile x_atomic_##bit* obj, T arg, x_memory_order order) { \
    assert(obj != NULL); \
    union _x_a##bit old = {0}; \
    union _x_a##bit opd = {arg}; \
    LOCK \
    _X_SNIP_ATOMIC_ADD(old, obj, opd, order, bit); \
    UNLOCK \
    return old.real; \
  }

#define _X_IMPL_ATOMIC_ADD_BOOL(T, bit, LOCK, UNLOCK) \
  T x_atomic_fetch_add_##bit( \
      volatile x_atomic_##bit* obj, T arg, x_memory_order order) { \
    assert(obj != NULL); \
    union _x_a##bit old = {0}; \
    union _x_a##bit opd = {arg}; \
    LOCK \
    _X_SNIP_ATOMIC_ADD_BOOL(old, obj, opd, order, bit); \
    UNLOCK \
    return old.real; \
  }

#define _X_IMPL_ATOMIC_SUB(T, bit, LOCK, UNLOCK) \
  T x_atomic_fetch_sub_##bit( \
      volatile x_atomic_##bit* obj, T arg, x_memory_order order) { \
    assert(obj != NULL); \
    union _x_a##bit old = {0}; \
    union _x_a##bit opd = {arg}; \
    LOCK \
    _X_SNIP_ATOMIC_SUB(old, obj, opd, order, bit); \
    UNLOCK \
    return old.real; \
  }

#define _X_IMPL_ATOMIC_SUB_BOOL(T, bit, LOCK, UNLOCK) \
  T x_atomic_fetch_sub_##bit( \
      volatile x_atomic_##bit* obj, T arg, x_memory_order order) { \
    assert(obj != NULL); \
    union _x_a##bit old = {0}; \
    union _x_a##bit opd = {arg}; \
    LOCK \
    _X_SNIP_ATOMIC_SUB_BOOL(old, obj, opd, order, bit); \
    UNLOCK \
    return old.real; \
  }

#define _X_IMPL_ATOMIC_LOGIC(op, T, bit, LOCK, UNLOCK) \
  T x_atomic_fetch_##op##_##bit( \
      volatile x_atomic_##bit* obj, T arg, x_memory_order order) { \
    assert(obj != NULL); \
    union _x_a##bit old = {0}; \
    union _x_a##bit opd = {arg}; \
    LOCK \
    _X_SNIP_ATOMIC_LOGIC(op, old, obj, opd, order, bit); \
    UNLOCK \
    return old.real; \
  }

#define _X_IMPL_ATOMIC_LOGIC_BOOL(op, T, bit, LOCK, UNLOCK) \
  T x_atomic_fetch_##op##_##bit( \
      volatile x_atomic_##bit* obj, T arg, x_memory_order order) { \
    assert(obj != NULL); \
    union _x_a##bit old = {0}; \
    union _x_a##bit opd = {arg}; \
    LOCK \
    _X_SNIP_ATOMIC_LOGIC_BOOL(op, old, obj, opd, order, bit); \
    UNLOCK \
    return old.real; \
  }

_X_IMPL_ATOMIC_INIT      (uint8_t, 8)
_X_IMPL_ATOMIC_STORE     (uint8_t, 8, X_EMPTINESS, X_EMPTINESS)
_X_IMPL_ATOMIC_LOAD      (uint8_t, 8, X_EMPTINESS, X_EMPTINESS)
_X_IMPL_ATOMIC_XCHG      (uint8_t, 8, X_EMPTINESS, X_EMPTINESS)
_X_IMPL_ATOMIC_CMP_XCHG  (uint8_t, 8, X_EMPTINESS, X_EMPTINESS)
_X_IMPL_ATOMIC_ADD       (uint8_t, 8, X_EMPTINESS, X_EMPTINESS)
_X_IMPL_ATOMIC_SUB       (uint8_t, 8, X_EMPTINESS, X_EMPTINESS)
_X_IMPL_ATOMIC_LOGIC(Or , uint8_t, 8, X_EMPTINESS, X_EMPTINESS)
_X_IMPL_ATOMIC_LOGIC(Xor, uint8_t, 8, X_EMPTINESS, X_EMPTINESS)
_X_IMPL_ATOMIC_LOGIC(And, uint8_t, 8, X_EMPTINESS, X_EMPTINESS)

_X_IMPL_ATOMIC_INIT      (uint16_t, 16)
_X_IMPL_ATOMIC_STORE     (uint16_t, 16, X_EMPTINESS, X_EMPTINESS)
_X_IMPL_ATOMIC_LOAD      (uint16_t, 16, X_EMPTINESS, X_EMPTINESS)
_X_IMPL_ATOMIC_XCHG      (uint16_t, 16, X_EMPTINESS, X_EMPTINESS)
_X_IMPL_ATOMIC_CMP_XCHG  (uint16_t, 16, X_EMPTINESS, X_EMPTINESS)
_X_IMPL_ATOMIC_ADD       (uint16_t, 16, X_EMPTINESS, X_EMPTINESS)
_X_IMPL_ATOMIC_SUB       (uint16_t, 16, X_EMPTINESS, X_EMPTINESS)
_X_IMPL_ATOMIC_LOGIC(Or , uint16_t, 16, X_EMPTINESS, X_EMPTINESS)
_X_IMPL_ATOMIC_LOGIC(Xor, uint16_t, 16, X_EMPTINESS, X_EMPTINESS)
_X_IMPL_ATOMIC_LOGIC(And, uint16_t, 16, X_EMPTINESS, X_EMPTINESS)

_X_IMPL_ATOMIC_INIT      (uint32_t, 32)
_X_IMPL_ATOMIC_STORE     (uint32_t, 32, X_EMPTINESS, X_EMPTINESS)
_X_IMPL_ATOMIC_LOAD      (uint32_t, 32, X_EMPTINESS, X_EMPTINESS)
_X_IMPL_ATOMIC_XCHG      (uint32_t, 32, X_EMPTINESS, X_EMPTINESS)
_X_IMPL_ATOMIC_CMP_XCHG  (uint32_t, 32, X_EMPTINESS, X_EMPTINESS)
_X_IMPL_ATOMIC_ADD       (uint32_t, 32, X_EMPTINESS, X_EMPTINESS)
_X_IMPL_ATOMIC_SUB       (uint32_t, 32, X_EMPTINESS, X_EMPTINESS)
_X_IMPL_ATOMIC_LOGIC(Or , uint32_t, 32, X_EMPTINESS, X_EMPTINESS)
_X_IMPL_ATOMIC_LOGIC(Xor, uint32_t, 32, X_EMPTINESS, X_EMPTINESS)
_X_IMPL_ATOMIC_LOGIC(And, uint32_t, 32, X_EMPTINESS, X_EMPTINESS)

#if X_64BIT
_X_IMPL_ATOMIC_INIT      (uint64_t, 64)
_X_IMPL_ATOMIC_STORE     (uint64_t, 64, X_EMPTINESS, X_EMPTINESS)
_X_IMPL_ATOMIC_LOAD      (uint64_t, 64, X_EMPTINESS, X_EMPTINESS)
_X_IMPL_ATOMIC_XCHG      (uint64_t, 64, X_EMPTINESS, X_EMPTINESS)
_X_IMPL_ATOMIC_CMP_XCHG  (uint64_t, 64, X_EMPTINESS, X_EMPTINESS)
_X_IMPL_ATOMIC_ADD       (uint64_t, 64, X_EMPTINESS, X_EMPTINESS)
_X_IMPL_ATOMIC_SUB       (uint64_t, 64, X_EMPTINESS, X_EMPTINESS)
_X_IMPL_ATOMIC_LOGIC(Or , uint64_t, 64, X_EMPTINESS, X_EMPTINESS)
_X_IMPL_ATOMIC_LOGIC(Xor, uint64_t, 64, X_EMPTINESS, X_EMPTINESS)
_X_IMPL_ATOMIC_LOGIC(And, uint64_t, 64, X_EMPTINESS, X_EMPTINESS)
#else
_X_IMPL_ATOMIC_INIT      (uint64_t, 64)
_X_IMPL_ATOMIC_STORE     (uint64_t, 64, _X_ATOMIC_LOCK, _X_ATOMIC_UNLOCK)
_X_IMPL_ATOMIC_LOAD      (uint64_t, 64, _X_ATOMIC_LOCK, _X_ATOMIC_UNLOCK)
_X_IMPL_ATOMIC_XCHG      (uint64_t, 64, _X_ATOMIC_LOCK, _X_ATOMIC_UNLOCK)
_X_IMPL_ATOMIC_CMP_XCHG  (uint64_t, 64, _X_ATOMIC_LOCK, _X_ATOMIC_UNLOCK)
_X_IMPL_ATOMIC_ADD       (uint64_t, 64, _X_ATOMIC_LOCK, _X_ATOMIC_UNLOCK)
_X_IMPL_ATOMIC_SUB       (uint64_t, 64, _X_ATOMIC_LOCK, _X_ATOMIC_UNLOCK)
_X_IMPL_ATOMIC_LOGIC(Or , uint64_t, 64, _X_ATOMIC_LOCK, _X_ATOMIC_UNLOCK)
_X_IMPL_ATOMIC_LOGIC(Xor, uint64_t, 64, _X_ATOMIC_LOCK, _X_ATOMIC_UNLOCK)
_X_IMPL_ATOMIC_LOGIC(And, uint64_t, 64, _X_ATOMIC_LOCK, _X_ATOMIC_UNLOCK)
#endif

_X_IMPL_ATOMIC_INIT      (void*, ptr)
_X_IMPL_ATOMIC_STORE     (void*, ptr, X_EMPTINESS, X_EMPTINESS)
_X_IMPL_ATOMIC_LOAD      (void*, ptr, X_EMPTINESS, X_EMPTINESS)
_X_IMPL_ATOMIC_XCHG      (void*, ptr, X_EMPTINESS, X_EMPTINESS)
_X_IMPL_ATOMIC_CMP_XCHG  (void*, ptr, X_EMPTINESS, X_EMPTINESS)
_X_IMPL_ATOMIC_ADD       (void*, ptr, X_EMPTINESS, X_EMPTINESS)
_X_IMPL_ATOMIC_SUB       (void*, ptr, X_EMPTINESS, X_EMPTINESS)
_X_IMPL_ATOMIC_LOGIC(Or , void*, ptr, X_EMPTINESS, X_EMPTINESS)
_X_IMPL_ATOMIC_LOGIC(Xor, void*, ptr, X_EMPTINESS, X_EMPTINESS)
_X_IMPL_ATOMIC_LOGIC(And, void*, ptr, X_EMPTINESS, X_EMPTINESS)

_X_IMPL_ATOMIC_INIT           (bool, bool)
_X_IMPL_ATOMIC_STORE          (bool, bool, X_EMPTINESS, X_EMPTINESS)
_X_IMPL_ATOMIC_LOAD           (bool, bool, X_EMPTINESS, X_EMPTINESS)
_X_IMPL_ATOMIC_XCHG           (bool, bool, X_EMPTINESS, X_EMPTINESS)
_X_IMPL_ATOMIC_CMP_XCHG       (bool, bool, X_EMPTINESS, X_EMPTINESS)
_X_IMPL_ATOMIC_ADD_BOOL       (bool, bool, X_EMPTINESS, X_EMPTINESS)
_X_IMPL_ATOMIC_SUB_BOOL       (bool, bool, X_EMPTINESS, X_EMPTINESS)
_X_IMPL_ATOMIC_LOGIC_BOOL(Or , bool, bool, X_EMPTINESS, X_EMPTINESS)
_X_IMPL_ATOMIC_LOGIC_BOOL(Xor, bool, bool, X_EMPTINESS, X_EMPTINESS)
_X_IMPL_ATOMIC_LOGIC_BOOL(And, bool, bool, X_EMPTINESS, X_EMPTINESS)

X_INL bool _x_is_size_lock_free(const size_t size)
{
#if X_64BIT
  return size <= 8 && (size & (size - 1)) == 0;
#else
  return size <= 4 && (size & (size - 1)) == 0;
#endif
}

bool x_atomic_flag_test_and_set(
    volatile x_atomic_flag* obj, x_memory_order order)
{
  assert(obj != NULL);

#if X_MSVC
  (void)order;
  union _x_abool old = {0};
  old.digi = _InterlockedExchange8(&(obj->data.digi), 1);
  return old.real;
#else
  return __atomic_test_and_set(&(obj->data.real), order);
#endif
}

void x_atomic_flag_clear(volatile x_atomic_flag* obj, x_memory_order order)
{
  assert(obj != NULL);

#if X_MSVC
  (void)order;
  _InterlockedExchange8(&(obj->data.digi), 0);
#else
  __atomic_clear(&(obj->data.real), order);
#endif
}

void x_atomic_signal_fence(const x_memory_order order)
{
#if X_ARM || X_ARM64
  if (order != x_mo_relaxed) {
    __asm__ __volatile__("" : : : "memory");
  }
#elif X_X86 || X_X64
#if X_MSVC
  switch (order) {
    case x_mo_relaxed:
      break;
    case x_mo_consume:
    case x_mo_acquire:
      _ReadBarrier();
      break;
    case x_mo_release:
      _WriteBarrier();
      break;
    default:
      _ReadWriteBarrier();
      break;
  }
#elif X_CLANG || X_GCC
  if (order != x_mo_relaxed) {
    __asm__ __volatile__("" : : : "memory");
  }
#endif
#else
#error "Unsupported hardware."
#endif
}

void x_atomic_thread_fence(const x_memory_order order)
{
#if X_ARM || X_ARM64
  if (order != x_mo_relaxed) {
    if (order == x_mo_consume || order == x_mo_acquire) {
      __asm__ __volatile__ ("dmb ishld\n\t" : : : "memory");
    } else {
      __asm__ __volatile__ ("dmb ish\n\t" : : : "memory");
    }
  }
#elif X_X86 || X_X64
#if X_MSVC
  if (order != x_mo_relaxed) {
    MemoryBarrier();
  }
#elif X_CLANG || X_GCC
  if (order != x_mo_relaxed) {
    if (order == x_mo_seq_cst) {
#if X_32BIT
      __asm__ __volatile__ ("lock;" "orl $0, (%%" "esp" ")" : : : "memory");
#else
      __asm__ __volatile__ ("lock;" "orl $0, (%%" "rsp" ")" : : : "memory");
#endif
    } else {
      __asm__ __volatile__("" : : : "memory");
    }
  }
#endif
#else
#error "Unsupported hardware."
#endif
}
// IMPL_x_atomic}}}

//*************************************************************** IMPL_x_cks{{{
uint32_t x_cks_crc32(const void* data, const size_t size, const uint32_t* prev)
{
  uint8_t* d = (uint8_t*)data;
  size_t cnt = size / sizeof(uint8_t);
  int i = 0;

  uint32_t cks = prev ? ~(*prev) : 0xFFFFFFFF;

  while (cnt--) {
    cks ^= *d++;

    for (i = 0; i < 8; ++i) {
      cks = (cks >> 1) ^ (-(int32_t)(cks & 1) & 0xEDB88320);
    }
  }

  return ~cks;
}

uint16_t x_cks_rfc1071(const void* data, const size_t size)
{
  uint16_t* d = (uint16_t*)data;
  size_t cnt = size / sizeof(uint8_t);
  uint32_t cks = 0;

  while (cnt > 1) {
    cks += *d++;
    cnt -= 2;
  }

  if (cnt > 0) {
    cks += *d;
  }

  while (cks >> 16) {
    cks = (cks & 0xFFFF) + (cks >> 16);
  }

  return (uint16_t)(~cks);
}

uint8_t x_cks_xor(const void* data, const size_t size)
{
  const uint8_t* d8 = (const uint8_t*)data;
  const uint64_t* d64 = (const uint64_t*)data;
  const size_t dsz = sizeof(uint64_t);
  const size_t cnt = size / dsz;

  union {
    uint8_t u8[8];
    uint64_t u64;
  } cks = {0};

  size_t i = 0;
  for (i = 0; i < (cnt & (~0x07)); i += 8) {
    cks.u64 ^= d64[i] ^ d64[i + 1] ^ d64[i + 2] ^ d64[i + 3]
      ^ d64[i + 4] ^ d64[i + 5] ^ d64[i + 6] ^ d64[i + 7];
  }

  for (size_t j = i * dsz; j < size; ++j) {
    cks.u8[0] ^= d8[j];
  }

  cks.u8[0] ^= cks.u8[1] ^ cks.u8[2] ^ cks.u8[3]
    ^ cks.u8[4] ^ cks.u8[5] ^ cks.u8[6] ^ cks.u8[7];

  return cks.u8[0];
}
// IMPL_x_cks}}}

#if X_ENABLE_SOCKET
//*************************************************************** IMPL_x_skt{{{
x_err x_skt_init(x_skt* skt, const int type)
{
  if (skt == NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

#if X_WINDOWS
  WSADATA data = {0};
  if (WSAStartup(MAKEWORD(2, 2), &data) != 0) {
    return x_err_set(x_err_socket);
  }
#endif

  if (type == SOCK_STREAM) {
    skt->hndl = socket(AF_INET, type, IPPROTO_TCP);
  } else if (type == SOCK_DGRAM) {
    skt->hndl = socket(AF_INET, type, IPPROTO_UDP);
  } else {
    return x_err_set(x_err_posix, ENOTSUP);
  }

#if X_WINDOWS
  if (skt->hndl == INVALID_SOCKET) {
    return x_err_set(x_err_socket);
  }
#else
  if (skt->hndl == -1) {
    return x_err_set(x_err_socket);
  }
#endif

  int ierr = 0;
  int val = 1;
  socklen_t len = (socklen_t)sizeof(val);

  ierr = setsockopt(skt->hndl, SOL_SOCKET, SO_KEEPALIVE, (char*)&val, len);
  if (ierr != 0) {
    return x_err_set(x_err_socket);
  }

#if X_WINDOWS
  ierr = setsockopt(skt->hndl, SOL_SOCKET, SO_EXCLUSIVEADDRUSE, (char*)&val, len);
#else
  val = 0;
  ierr = setsockopt(skt->hndl, SOL_SOCKET, SO_REUSEADDR, (char*)&val, len);
#endif
  if (ierr != 0) {
    return x_err_set(x_err_socket);
  }

  return x_ok();
}

x_err x_skt_accpet(x_skt* skt, x_skt* acceptee)
{
  if (skt == NULL || acceptee == NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

  struct sockaddr_in sin = {0};
  socklen_t len = 0;

  acceptee->hndl = accept(skt->hndl, (struct sockaddr*)&sin, &len);
#if X_WINDOWS
  if (acceptee->hndl == INVALID_SOCKET) {
#else
  if (acceptee->hndl == -1) {
#endif
    return x_err_set(x_err_socket);
  }

  memcpy(&acceptee->addr, &sin, len);

  return x_ok();
}

x_err x_skt_addr(x_skt* skt, char* ip, uint16_t* port)
{
  if (skt == NULL || ip == NULL || port == NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

  struct sockaddr_in* sin = (struct sockaddr_in*)&skt->addr;

  if (inet_ntop(AF_INET, &sin->sin_addr, ip, 16) == NULL) {
    return x_err_set(x_err_socket);
  }

  *port = sin->sin_port;

  return x_ok();
}

x_err x_skt_close(x_skt* skt)
{
  if (skt == NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

#if X_WINDOWS
  if (closesocket(skt->hndl) != 0) {
    return x_err_set(x_err_socket);
  }

  return WSACleanup() == 0 ? x_ok() : x_err_set(x_err_socket);
#else
  return close(skt->hndl) == 0 ? x_ok() : x_err_set(x_err_posix);
#endif
}

x_err x_skt_connect(x_skt* skt, const char* ip, const uint16_t port)
{
  if (skt == NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

  struct sockaddr_in sin = {0};
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  int ierr = inet_pton(AF_INET, ip, &sin.sin_addr);
  if (ierr == 0) {
    return x_err_set(x_err_posix, EFAULT);
  } else if (ierr == -1) {
    return x_err_set(x_err_socket);
  }

  memcpy(&skt->addr, &sin, sizeof(struct sockaddr));

  return connect(skt->hndl, &skt->addr, sizeof(struct sockaddr_in)) == 0
    ? x_ok() : x_err_set(x_err_socket);
}

x_err x_skt_getopt(
    x_skt* skt, const int lvl, const int opt, void* val, socklen_t* len)
{
  if (skt == NULL || val == NULL || len == NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

  return getsockopt(skt->hndl, lvl, opt, (char*)val, len) == 0
    ? x_ok() : x_err_set(x_err_socket);
}

x_err x_skt_listen(x_skt* skt, const char* ip, const uint16_t port)
{
  if (skt == NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

  struct sockaddr_in sin = {0};
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  int ierr = inet_pton(AF_INET, ip, &sin.sin_addr);
  if (ierr == 0) {
    return x_err_set(x_err_posix, EFAULT);
  } else if (ierr == -1) {
    return x_err_set(x_err_socket);
  }

  memcpy(&skt->addr, &sin, sizeof(struct sockaddr));

  ierr = bind(skt->hndl, &skt->addr, sizeof(struct sockaddr_in));
  if (ierr == 0) {
    ierr = listen(skt->hndl, SOMAXCONN);
  }

  return ierr == 0 ? x_ok() : x_err_set(x_err_socket);
}

x_err x_skt_recv(x_skt* skt, void* buf, const size_t size, const int flags)
{
  if (skt == NULL || buf == NULL || size == 0) {
    return x_err_set(x_err_posix, EINVAL);
  }

#if X_WINDOWS
  int remain = (int)size;
  int bytes = 0;
#else
  size_t remain = size;
  ssize_t bytes = 0;
#endif
  size_t offset = 0;

  while (remain > 0) {
    bytes = recv(skt->hndl, (char*)buf + offset, remain, flags);
    if (bytes <= 0) {
      return x_err_set(x_err_posix);
    }

    offset += bytes;
    remain -= bytes;
  }

  return x_ok();
}

x_err x_skt_recvv(x_skt* skt, x_iov* iov, const size_t count, const int flags)
{
  if (skt == NULL || iov == NULL || count == 0) {
    return x_err_set(x_err_posix, EINVAL);
  }

  size_t total = 0;
  for (size_t i = 0; i < count; ++i) {
    if (iov[i].buf == NULL || iov[i].len == 0) {
      return x_err_set(x_err_posix, EINVAL);
    }

    if (iov[i].len > (SIZE_MAX - total)) {
      return x_err_set(x_err_posix, EOVERFLOW);
    }

    total += iov[i].len;
  }

  // NOTE: _alloca/alloca may be used if all data received are rather small.
  void* buf = malloc(total);
  if (buf == NULL) {
    return x_err_set(x_err_posix);
  }

  x_err err = x_skt_recv(skt, buf, total, flags);
  if (x_succ(err)) {
    size_t offset = 0;
    for (size_t i = 0; i < count; ++i) {
      memcpy(iov[i].buf, (char*)buf + offset, iov[i].len);
      offset += iov[i].len;
    }
  }

  free(buf);

  return err;
}

x_err x_skt_send(
    x_skt* skt, const void* buf, const size_t size, const int flags)
{
  if (skt == NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

#if X_WINDOWS
  int remain = (int)size;
#else
  size_t remain = size;
#endif
  size_t offset = 0;
  int bytes = 0;

  while (remain > 0) {
    bytes = send(skt->hndl, (char*)buf + offset, remain, flags);
    if (bytes <= 0) {
      return x_err_set(x_err_posix);
    }

    offset += bytes;
    remain -= bytes;
  }

  return x_ok();
}

x_err x_skt_sendv(
    x_skt* skt, const x_iov* iov, const size_t count, const int flags)
{
  if (iov == NULL || count == 0 || skt == NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

  size_t total = 0;
  for (size_t i = 0; i < count; ++i) {
    if (iov[i].buf == NULL || iov[i].len == 0) {
      return x_err_set(x_err_posix, EINVAL);
    }

    if (iov[i].len > (SIZE_MAX - total)) {
      return x_err_set(x_err_posix, EOVERFLOW);
    }

    total += iov[i].len;
  }

  // NOTE: _alloca/alloca may be used if all data sent are rather small.
  void* buf = malloc(total);
  if (buf == NULL) {
    return x_err_set(x_err_posix);
  }

  size_t offset = 0;
  for (size_t i = 0; i < count; ++i) {
    memcpy((char*)buf + offset, iov[i].buf, iov[i].len);
    offset += iov[i].len;
  }

  x_err err = x_skt_send(skt, buf, total, flags);

  free(buf);

  return err;
}

x_err x_skt_setopt(
    x_skt* skt, const int lvl, const int opt, const void* val,
    const socklen_t len)
{
  if (skt == NULL || val == NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

  return setsockopt(skt->hndl, lvl, opt, (char*)val, len) == 0
    ? x_ok() : x_err_set(x_err_socket);
}
// IMPL_x_skt}}}
#endif  // X_ENABLE_SOCKET

//************************************************************** IMPL_x_node{{{
x_node* x_node_create(void* data, x_node* prev, x_node* next)
{
  x_node* node = (x_node*)malloc(sizeof(x_node));
  if (node == NULL) {
    return NULL;
  }

  node->data = data;
  node->prev = prev;
  node->next = next;

  return node;
}

x_anode* x_anode_create(void* data, void* prev, void* next)
{
  x_anode* node = (x_anode*)malloc(sizeof(x_anode));
  if (node == NULL) {
    return NULL;
  }

  node->data = data;
  x_atomic_init_ptr(&node->prev, prev);
  x_atomic_init_ptr(&node->next, next);

  return node;
}
// IMPL_x_node}}}

//************************************************************* IMPL_x_deque{{{
x_err x_deque_init(x_deque* que, const uint64_t capacity)
{
  if (que == NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

  que->capacity = capacity;
  que->count = 0;
  que->head = NULL;
  que->tail = NULL;

  return x_ok();
}

void x_deque_dstr(x_deque* que, void (*dealloc)(void*))
{
  x_deque_clear(que, dealloc);
}

void x_deque_clear(x_deque* que, void (*dealloc)(void*))
{
  if (que == NULL) {
    return;
  }

  x_node* newh = NULL;

  while (que->head != NULL) {
    newh = que->head->next;

    if (dealloc != NULL && que->head->data != NULL) {
      dealloc(que->head->data);
      que->head->data = NULL;
    }
    x_free(que->head);

    que->head = newh;
  }

  que->count = 0;
}

x_node* x_deque_deq_back(x_deque* que)
{
  if (que == NULL || x_deque_empty(que)) {
    return NULL;
  }

  x_node* oldt = que->tail;

  if (que->tail == que->head) {
    que->tail = NULL;
    que->head = NULL;
  } else {
    que->tail = oldt->prev;
    if (que->tail != NULL) {
      que->tail->next = NULL;
    }
  }

  que->count -= 1;

  return oldt;
}

x_node* x_deque_deq_front(x_deque* que)
{
  if (que == NULL || x_deque_empty(que)) {
    return NULL;
  }

  x_node* oldh = que->head;

  if (que->head == que->tail) {
    que->head = NULL;
    que->tail = NULL;
  } else {
    que->head = oldh->next;
    if (que->head != NULL) {
      que->head->prev = NULL;
    }
  }

  que->count -= 1;

  return oldh;
}

x_err x_deque_enq_back(x_deque* que, x_node* const node)
{
  if (que == NULL || node == NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

  if (x_deque_full(que)) {
    return x_err_set(x_err_posix, ENOBUFS);
  }

  if (que->tail == NULL) {
    que->head = node;
  } else {
    que->tail->next = node;
  }
  que->tail = node;

  que->count += 1;

  return x_ok();
}

x_err x_deque_enq_front(x_deque* que, x_node* const node)
{
  if (que == NULL || node == NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

  if (x_deque_full(que)) {
    return x_err_set(x_err_posix, ENOBUFS);
  }

  if (que->head == NULL) {
    que->tail = node;
  } else {
    que->head->prev = node;
  }
  que->head = node;

  que->count += 1;

  return x_ok();
}

bool x_deque_empty(x_deque* que)
{
  assert(que != NULL);
  return (que->count == 0 || (que->head == NULL && que->tail == NULL));
}

bool x_deque_full(x_deque* que)
{
  assert(que != NULL);
  return (que->capacity == X_QUE_CAP_INF ? false : que->count == que->capacity);
}

void* x_deque_pop_back(x_deque* que)
{
  x_node* oldt = x_deque_deq_back(que);
  void* data = oldt->data;

  x_free(oldt);

  return data;
}

void* x_deque_pop_front(x_deque* que)
{
  x_node* oldh = x_deque_deq_front(que);
  void* data = oldh->data;

  x_free(oldh);

  return data;
}

x_err x_deque_push_back(x_deque* que, void* const data)
{
  if (que == NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

  x_node* node = x_node_create(data, que->tail, NULL);
  if (node == NULL) {
    return x_err_set(x_err_posix, ENOMEM);
  }

  x_err err = x_deque_enq_back(que, node);
  if (x_fail(err)) {
    x_free(node);
  }

  return err;
}

x_err x_deque_push_front(x_deque* que, void* const data)
{
  if (que == NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

  x_node* node = x_node_create(data, NULL, que->head);
  if (node == NULL) {
    return x_err_set(x_err_posix, ENOMEM);
  }

  x_err err = x_deque_enq_front(que, node);
  if (x_fail(err)) {
    x_free(node);
  }

  return err;
}

x_err x_deque_reserve(x_deque* que, const uint64_t capacity)
{
  if (que == NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

  if (capacity > X_QUE_CAP_INF) {
    return x_err_set(x_err_posix, EOVERFLOW);
  }

  que->capacity = capacity;

  return x_ok();
}

uint64_t x_deque_size(x_deque* que)
{
  return que->count;
}
// IMPL_x_deque}}}

//************************************************************* IMPL_x_nbque{{{
x_err x_nbque_init(x_nbque* que, const uint64_t capacity)
{
  if (que == NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

  x_anode* node = x_anode_create(NULL, NULL, NULL);
  if (node == NULL) {
    return x_err_set(x_err_posix, ENOMEM);
  }

  x_atomic_init_64(&que->capacity, capacity);
  x_atomic_init_64(&que->ocnt, 0);
  x_atomic_init_64(&que->icnt, 0);
  x_atomic_init_ptr(&que->head, node);
  x_atomic_init_ptr(&que->tail, node);

#if X_ENABLE_STRUCT_FUNCTION
  que->init = x_nbque_init;
  que->dstr = x_nbque_dstr;
  que->clear = x_nbque_clear;
  que->empty = x_nbque_empty;
  que->full = x_nbque_full;
  que->pop = x_nbque_pop;
  que->push = x_nbque_push;
  que->reserve = x_nbque_reserve;
  que->size = x_nbque_size;
#endif

  return x_ok();
}

void x_nbque_dstr(x_nbque* que, void (*dealloc)(void*))
{
  if (que == NULL) {
    return;
  }

  x_nbque_clear(que, dealloc);

  x_anode* head = (x_anode*)que->head.load(&que->head, x_mo_acquire);
  if (head != NULL) {
    if (dealloc != NULL && head->data != NULL) {
      dealloc(head->data);
      head->data = NULL;
    }
    x_free(head);
  }
}

x_err x_nbque_clear(x_nbque* que, void (*dealloc)(void*))
{
  if (que == NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

  x_anode* oldh = (x_anode*)que->head.load(&que->head, x_mo_acquire);
  x_anode* newh = (x_anode*)oldh->next.load(&oldh->next, x_mo_acquire);

  while (newh != NULL) {
    if (dealloc != NULL && newh->data != NULL) {
      dealloc(newh->data);
      newh->data = NULL;
    }

    que->head.compare_exchange(
        &que->head, (void**)&oldh, newh, x_mo_release, x_mo_relaxed);

    x_free(oldh);

    oldh = (x_anode*)que->head.load(&que->head, x_mo_acquire);
    newh = (x_anode*)oldh->next.load(&oldh->next, x_mo_acquire);
  }

  que->ocnt.store(&que->ocnt, 0, x_mo_release);
  que->icnt.store(&que->icnt, 0, x_mo_release);

  return x_ok();
}

bool x_nbque_empty(x_nbque* que)
{
  assert(que != NULL);
  return que->icnt.load(&que->icnt, x_mo_acquire)
    == que->ocnt.load(&que->ocnt, x_mo_acquire);
}

bool x_nbque_full(x_nbque* que)
{
  assert(que != NULL);
  if (que->capacity.load(&que->capacity, x_mo_acquire) == X_QUE_CAP_INF) {
    return false;
  } else {
    return que->icnt.load(&que->icnt, x_mo_acquire)
      >= (que->ocnt.load(&que->ocnt, x_mo_acquire)
          + que->capacity.load(&que->capacity, x_mo_acquire));
  }
}

void* x_nbque_pop(x_nbque* que)
{
  if (que == NULL) {
    return NULL;
  }

  while (x_nbque_empty(que)) {
    x_sleep(10);
  }

  x_anode* oldh = NULL;
  x_anode* oldt = NULL;
  x_anode* oldn = NULL;
  void* data = NULL;

  for (;;) {
    oldh = (x_anode*)que->head.load(&que->head, x_mo_acquire);
    oldt = (x_anode*)que->tail.load(&que->tail, x_mo_acquire);
    oldn = (x_anode*)oldh->next.load(&oldh->next, x_mo_acquire);

    if (oldh == que->head.load(&que->head, x_mo_acquire)) {
      if (oldh == oldt) {
        if (oldn  == NULL) {
          return NULL;
        }

        que->tail.compare_exchange(
            &que->tail, (void**)&oldt, oldn, x_mo_release, x_mo_relaxed);
      } else {
        if (oldn == NULL) {
          continue;
        }

        data = oldn->data;

        if (que->head.compare_exchange(
              &que->head, (void**)&oldh, oldn, x_mo_release, x_mo_relaxed)) {
          break;
        }
      }
    }
  }

  x_free(oldh);

  que->ocnt.fetch_add(&que->ocnt, 1, x_mo_release);

  return data;
}

x_err x_nbque_push(x_nbque* que, void* const data)
{
  if (que == NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

  while (x_nbque_full(que)) {
    x_sleep(10);
  }

  x_anode* node = x_anode_create(data, NULL, NULL);
  if (node == NULL) {
    return x_err_set(x_err_posix, ENOMEM);
  }

  x_anode* oldt = NULL;
  x_anode* oldn = NULL;

  for (;;) {
    oldt = (x_anode*)que->tail.load(&que->tail, x_mo_acquire);
    oldn = (x_anode*)oldt->next.load(&oldt->next, x_mo_acquire);

    if (oldt == que->tail.load(&que->tail, x_mo_acquire)) {
      if (oldn == NULL) {
        if (oldt->next.compare_exchange(
              &oldt->next, (void**)&oldn, node, x_mo_release, x_mo_relaxed)) {
          break;
        }
      } else {
        que->tail.compare_exchange(
            &que->tail, (void**)&oldt, oldn, x_mo_release, x_mo_relaxed);
      }
    }
  }

  que->tail.compare_exchange(
      &que->tail, (void**)&oldt, node, x_mo_release, x_mo_relaxed);

  que->icnt.fetch_add(&que->icnt, 1, x_mo_release);

  return x_ok();
}

x_err x_nbque_reserve(x_nbque* que, const uint64_t capacity)
{
  if (que == NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

  if (capacity > X_QUE_CAP_INF) {
    return x_err_set(x_err_posix, EOVERFLOW);
  }

  que->capacity.store(&que->capacity, capacity, x_mo_release);

  return x_ok();
}

uint64_t x_nbque_size(x_nbque* que)
{
  if (que == NULL || x_nbque_empty(que)) {
    return 0;
  }

  return que->icnt.load(&que->icnt, x_mo_acquire)
    - que->ocnt.load(&que->ocnt, x_mo_acquire);
}
// IMPL_x_nbque}}}

//************************************************************* IMPL_x_tlque{{{
x_err x_tlque_init(x_tlque* que, const uint64_t capacity)
{
  if (que == NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

  x_node* node = x_node_create(NULL, NULL, NULL);
  if (node == NULL) {
    return x_err_set(x_err_posix, ENOMEM);
  }

  x_err err = x_cnd_init(&que->nmty);
  if (x_succ(err)) {
    err = x_cnd_init(&que->nful);
    if (x_succ(err)) {
      err = x_mtx_init(&que->hlck, x_mtx_plain);
      if (x_succ(err)) {
        err = x_mtx_init(&que->tlck, x_mtx_plain);
      }
    }
  }

  if (x_fail(err)) {
    x_free(node);
    x_cnd_dstr(&que->nmty);
    x_cnd_dstr(&que->nful);
    x_mtx_dstr(&que->hlck);
    x_mtx_dstr(&que->tlck);
  }

  x_atomic_init_64(&que->capacity, capacity);
  x_atomic_init_64(&que->count, 0);
  x_deque_init(&que->pool, X_QUE_CAP_INF);
  que->head = node;
  que->tail = node;

#if X_ENABLE_STRUCT_FUNCTION
  que->init = x_tlque_init;
  que->dstr = x_tlque_dstr;
  que->clear = x_tlque_clear;
  que->empty = x_tlque_empty;
  que->full = x_tlque_full;
  que->pop = x_tlque_pop;
  que->push = x_tlque_push;
  que->reserve = x_tlque_reserve;
  que->size = x_tlque_size;
#endif

  return err;
}

void x_tlque_dstr(x_tlque* que, void (*dealloc)(void*))
{
  if (que == NULL) {
    return;
  }

  x_tlque_clear(que, dealloc);

  if (que->head != NULL) {
    if (dealloc != NULL && que->head->data != NULL) {
      dealloc(que->head->data);
      que->head->data = NULL;
    }
    x_free(que->head);
  }

  x_node* node = NULL;
  while (!x_deque_empty(&que->pool)) {
    node = x_deque_deq_front(&que->pool);
    if (dealloc != NULL && node != NULL && node->data != NULL) {
      dealloc(node->data);
      node->data = NULL;
    }
    x_free(node);
  }

  x_cnd_dstr(&que->nmty);
  x_cnd_dstr(&que->nful);
  x_mtx_dstr(&que->hlck);
  x_mtx_dstr(&que->tlck);
}

x_err x_tlque_clear(x_tlque* que, void (*dealloc)(void*))
{
  if (que == NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

  x_err err = x_mtx_trylock(&que->tlck);
  if (x_succ(err)) {
    err = x_mtx_trylock(&que->hlck);
    if (x_succ(err)) {
      x_node* oldh = que->head;
      x_node* newh = oldh->next;

      while (newh != NULL) {
        if (dealloc != NULL && newh->data != NULL) {
          dealloc(newh->data);
          newh->data = NULL;
        }
        x_free(oldh);

        que->head = newh;

        oldh = que->head;
        newh = oldh->next;
      }

      que->count.store(&que->count, 0, x_mo_release);
    }
  }

  x_cnd_signal(&que->nful);

  x_mtx_unlock(&que->hlck);
  x_mtx_unlock(&que->tlck);

  return err;
}

bool x_tlque_empty(x_tlque* que)
{
  assert(que != NULL);
  return que->count.load(&que->count, x_mo_acquire) == 0;
}

bool x_tlque_full(x_tlque* que)
{
  assert(que != NULL);
  if (que->capacity.load(&que->capacity, x_mo_acquire) == X_QUE_CAP_INF) {
    return false;
  } else {
    return que->count.load(&que->count, x_mo_acquire)
      == que->capacity.load(&que->capacity, x_mo_acquire);
  }
}

void* x_tlque_pop(x_tlque* que)
{
  if (que == NULL) {
    return NULL;
  }

  x_err err = x_mtx_lock(&que->hlck);
  if (x_fail(err)) {
    return NULL;
  }

  while (x_tlque_empty(que)) {
    err = x_cnd_wait(&que->nmty, &que->hlck);
    if (x_fail(err)) {
      x_mtx_unlock(&que->hlck);
      return NULL;
    }
  }

  x_node* oldh = que->head;
  x_node* newh = oldh->next;
  if (newh == NULL) {
    x_mtx_unlock(&que->hlck);
    return NULL;
  }

  void* data = newh->data;
  que->head = newh;

  uint64_t oldc = que->count.fetch_sub(&que->count, 1, x_mo_release);
  if (oldc <= que->capacity.load(&que->capacity, x_mo_acquire)) {
    x_cnd_signal(&que->nful);
  }

  if (x_fail(x_deque_enq_back(&que->pool, oldh))) {
    x_free(oldh);
  }

  x_mtx_unlock(&que->hlck);

  return data;
}

x_err x_tlque_push(x_tlque* que, void* const data)
{
  if (que == NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

  x_err err = x_mtx_lock(&que->tlck);
  if (x_fail(err)) {
    return err;
  }

  x_node* node = x_deque_deq_front(&que->pool);
  if (node != NULL) {
    node->data = data;
    node->prev = NULL;
    node->next = NULL;
  } else {
    node = x_node_create(data, NULL, NULL);
    if (node == NULL) {
      return x_err_set(x_err_posix, ENOMEM);
    }
  }

  while (x_tlque_full(que)) {
    err = x_cnd_wait(&que->nful, &que->tlck);
    if (x_fail(err)) {
      x_mtx_unlock(&que->tlck);
      x_free(node);
      return err;
    }
  }

  que->tail->next = node;
  que->tail = node;

  uint64_t oldc = que->count.fetch_add(&que->count, 1, x_mo_release);
  if (oldc > 0) {
    x_cnd_signal(&que->nmty);
  }

  x_mtx_unlock(&que->tlck);

  return err;
}

x_err x_tlque_reserve(x_tlque* que, const uint64_t capacity)
{
  if (que == NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

  if (capacity > X_QUE_CAP_INF) {
    return x_err_set(x_err_posix, EOVERFLOW);
  }

  que->capacity.store(&que->capacity, capacity, x_mo_release);

  return x_ok();
}

uint64_t x_tlque_size(x_tlque* que)
{
  return que->count.load(&que->count, x_mo_acquire);
}
// IMPL_x_tlque}}}

//********************************************************* IMPL_x_stopwatch{{{
X_INL x_err x_swstats_init(x_swstats* stats)
{
  if (stats == NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

  stats->ready = false;
  stats->cyc = 0;
  stats->sum = 0.0;
  stats->avg = 0.0;
  stats->max.idx = 0;
  stats->max.val = DBL_MIN;
  stats->min.idx = 0;
  stats->min.val = DBL_MAX;

  return x_ok();
}

x_err x_stopwatch_init(x_stopwatch* sw)
{
  if (sw == NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

  sw->start = x_now();
  x_swstats_init(&sw->stats);
  sw->elapsed = 0.0;

  return x_ok();
}

void x_tic(x_stopwatch* sw, const bool echo)
{
  assert(sw != NULL);

  sw->start = x_now();

  if (echo) {
    char ts[26] = {0};
    printf("Timing starts at: %s.\n", x_timestamp(ts, x_count(ts)));
  }
}

void x_toc(x_stopwatch* sw, const char* unit, const bool echo)
{
  assert(sw != NULL);

  if (x_strmty(unit)) {
    unit = "ms";
  }

  sw->elapsed = x_duration(unit, sw->start, x_now());

  if (echo) {
    char ts[26] = {0};
    printf("Timing stops at: %s (%f%s elapsed).\n",
        x_timestamp(ts, x_count(ts)), sw->elapsed, unit);
  }
}

void x_toc_avg(
    x_stopwatch* sw, const char* unit, char* msg, size_t* msz,
    const long long cycle, const char* title, const bool echo)
{
  x_assert(sw != NULL && cycle != 0, "Invalid arguments.");

  if (x_strmty(unit)) {
    unit = "ms";
  }

  x_toc(sw, unit, false);

  if (sw->elapsed > sw->stats.max.val) {
    sw->stats.max.idx = sw->stats.cyc;
    sw->stats.max.val = sw->elapsed;
  }
  if (sw->elapsed < sw->stats.min.val) {
    sw->stats.min.idx = sw->stats.cyc;
    sw->stats.min.val = sw->elapsed;
  }

  sw->stats.sum += sw->elapsed;
  sw->stats.cyc += 1;
  sw->stats.avg = sw->stats.sum / sw->stats.cyc;

  if (sw->stats.cyc % cycle == 0) {
    sw->stats.ready = true;

    if (msg != NULL && msz != NULL && *msz > 0) {
      const char* t = x_strmty(title) ? "STATS" : title;

      size_t bytes = (size_t)snprintf(msg, *msz,
          "[%s] %f%s in %zu cycles - avg: %f%s, min(%zu): %f%s, max(%zu): %f%s",
          t,
          sw->stats.sum, unit,
          sw->stats.cyc,
          sw->stats.avg, unit,
          sw->stats.min.idx, sw->stats.min.val, unit,
          sw->stats.max.idx, sw->stats.max.val, unit);
      *msz = bytes;

      if (echo) {
        printf("%s\n", msg);
      }
    }
  }
}
// IMPL_x_stopwatch}}}

//****************************************************** IMPL_x_stopwatch_cu{{{
#if X_ENABLE_CUDA
void x_stopwatch_cu_dstr(x_stopwatch_cu* sw)
{
  if (sw != NULL) {
    cudaEventDestroy(sw->start);
    cudaEventDestroy(sw->stop);
  }
}

x_err x_stopwatch_cu_init(x_stopwatch_cu* sw)
{
  if (sw == NULL) {
    return x_err_set(x_err_posix, EINVAL);
  }

  cudaError_t cerr = cudaEventCreate(&sw->start);
  if (cerr != cudaSuccess) {
    return x_err_set(x_err_cuda, cerr);
  }

  cerr = cudaEventCreate(&sw->stop);
  if (cerr != cudaSuccess) {
    return x_err_set(x_err_cuda, cerr);
  }

  x_swstats_init(&sw->stats);
  sw->elapsed = 0.0;

  return x_ok();
}

void x_tic_cu(x_stopwatch_cu* sw, const bool echo)
{
  assert(sw != NULL);

  cudaError_t cerr = cudaEventRecord(sw->start);
  x_assert(cerr == cudaSuccess, cudaGetErrorString(cerr));

  if (echo) {
    char ts[26] = {0};
    printf("Timing starts at: %s.\n", x_timestamp(ts, x_count(ts)));
  }
}

void x_toc_cu(x_stopwatch_cu* sw, const char* unit, const bool echo)
{
  assert(sw != NULL);

  cudaError_t cerr = cudaEventRecord(sw->stop);
  x_assert(cerr == cudaSuccess, cudaGetErrorString(cerr));

  cerr = cudaEventSynchronize(sw->stop);
  x_assert(cerr == cudaSuccess, cudaGetErrorString(cerr));

  float elapsed{0.0f};
  cerr = cudaEventElapsedTime(&elapsed, sw->start, sw->stop);
  x_assert(cerr == cudaSuccess, cudaGetErrorString(cerr));

  if (strcmp(unit, "h") == 0) {
    elapsed /= 3600000.0f;
  } else if (strcmp(unit, "m") == 0) {
    elapsed /= 60000.0f;
  } else if (strcmp(unit, "s") == 0) {
    elapsed /= 1000.0f;
  } else if (strcmp(unit, "us") == 0) {
    elapsed *= 1000.0f;
  } else if (strcmp(unit, "ns") == 0) {
    elapsed *= 1000000.0f;
  }
  sw->elapsed = (double)elapsed;

  if (echo) {
    char ts[26]{0};
    printf("Stopwatch stops at: %s (%f%s elapsed).\n",
        x_timestamp(ts, x_count(ts)), sw->elapsed, unit);
  }
}

void x_toc_avg_cu(
    x_stopwatch_cu* sw, const char* unit, char* msg, size_t* msz,
    const long long cycle, const char* title, const bool echo)
{
  assert(sw != NULL || cycle > 0);

  if (x_strmty(unit)) {
    unit = "ms";
  }

  x_toc_cu(sw, unit, false);

  if (sw->elapsed > sw->stats.max.val) {
    sw->stats.max.idx = sw->stats.cyc;
    sw->stats.max.val = sw->elapsed;
  }
  if (sw->elapsed < sw->stats.min.val) {
    sw->stats.min.idx = sw->stats.cyc;
    sw->stats.min.val = sw->elapsed;
  }

  sw->stats.sum += sw->elapsed;
  sw->stats.cyc += 1;
  sw->stats.avg = sw->stats.sum / sw->stats.cyc;

  if (sw->stats.cyc % cycle == 0) {
    sw->stats.ready = true;

    if (msg != NULL && msz != NULL && *msz > 0) {
      const char* t = x_strmty(title) ? "STATS" : title;

      size_t bytes = (size_t)snprintf(msg, *msz,
          "[%s] %f%s in %zu cycles - avg: %f%s, min(%zu): %f%s, max(%zu): %f%s",
          t,
          sw->stats.sum, unit,
          sw->stats.cyc,
          sw->stats.avg, unit,
          sw->stats.min.idx, sw->stats.min.val, unit,
          sw->stats.max.idx, sw->stats.max.val, unit);

      if (echo) {
        printf("%s\n", msg);
      }
    }
  }
}
#endif
// IMPL_x_stopwatch_cu}}}

#ifdef __cplusplus
}  // extern "C"
#endif


#endif  // X_H
