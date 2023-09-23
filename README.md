<!------------------------------------------------------------------ HEADER -->
<pre align="center">
  █▀▀▄ ▄▀▀█    █▀▀▀█▀▀▀█
  ▀▀▄ ▀ ▄▀▀    █   █   █
     █ █       █       █
  ▄▄▀ ▄ ▀▄▄    █   █   █
  █▄▄▀ ▀▄▄█ ██ █▄▄▄█▄▄▄█
</pre>


<p align="center">
  <img src="https://img.shields.io/badge/C-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white" alt="C">
  <img src="https://img.shields.io/badge/C++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white" alt="C++">

  <a href="./LICENSE">
    <img src="https://img.shields.io/badge/license-mulax_psl_v2-green.svg?style=for-the-badge" alt="license-mulan-psl-v2">
  </a>
</p>

<p align="center">
  Cross platform C/C++ utilities.
</p>


<!------------------------------------------------------- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#installation">Installation</a></li>
        <li><a href="#usage">Usage</a></li>
      </ul>
    </li>
    <li><a href="#documentation">Documentation</a>
      <ul>
        <li><a href="#toggling-features">Toggling Features</a></li>
        <li><a href="#version-number-generator">Version Number Generator</a></li>
        <li><a href="#architecture-detection">Architecture Detection</a></li>
        <li><a href="#compiler-detection">Compiler Detection</a></li>
        <li><a href="#os-detection">OS Detection</a></li>
        <li><a href="#platform-detection">Platform Detection</a></li>
        <li><a href="#x_export-x_import">X_EXPORT, X_IMPORT</a></li>
        <li><a href="#x_key">X_KEY</a></li>
        <li><a href="#x_assert">x_assert</a></li>
        <li><a href="#x_buffer_valid">x_buffer_valid</a></li>
        <li><a href="#x_bit">x_bit</a></li>
        <li><a href="#x_count">x_count</a></li>
        <li><a href="#x_fail">x_fail</a></li>
        <li><a href="#x_free">x_free</a></li>
        <li><a href="#x_pi">x_pi</a></li>
        <li><a href="#x_succ">x_succ</a></li>
        <li><a href="#x_cpu_count">x_cpu_count</a></li>
        <li><a href="#x_duration">x_duration</a></li>
        <li><a href="#x_file_size">x_file_size</a></li>
        <li><a href="#x_full_path">x_full_path</a></li>
        <li><a href="#x_getch">x_getch</a></li>
        <li><a href="#x_now">x_now</a></li>
        <li><a href="#x_path_exists">x_path_exists</a></li>
        <li><a href="#x_spli_tpath">x_split_path</a></li>
        <li><a href="#x_sleep">x_sleep</a></li>
        <li><a href="#x_strmty">x_strmty</a></li>
        <li><a href="#x_timestamp">x_timestamp</a></li>
        <li><a href="#x_log">x_log</a></li>
        <li><a href="#x_err">x_err</a></li>
        <li><a href="#concurrency">Concurrency</a></li>
        <li><a href="#x_cks">x_cks</a></li>
        <li><a href="#x_pkt">x_pkt</a></li>
        <li><a href="#x_iov">x_iov</a></li>
        <li><a href="#x_skt">x_skt</a></li>
        <li><a href="#x_node">x_node</a></li>
        <li><a href="#x_deque">x_deque</a></li>
        <li><a href="#x_lfque">x_lfque</a></li>
        <li><a href="#x_tlque">x_tlque</a></li>
        <li><a href="#x_tictoc">x_tictoc</a></li>
      </ul>
    </li>
    <li><a href="#license">LICENSE</a></li>
  </ol>
</details>


<!--------------------------------------------------------- GETTING STARTED -->
## Getting Started
### Installation
Put `x.h` into your project.


### Usage
`x.h` is a single-header library which mean users can simply use its
functionalities by including it anywhere:

```c
// in some foo.h file
#include "x.h"

// in some foo.c file
#include "x.h"
```


<!----------------------------------------------------------- DOCUMENTATION -->
## Documentation
### Toggling Features
Several macros are provided for toggling features, some of which may be used to
avoid redundant build dependencies in some cases.

```c
#ifndef X_ENABLE_ATOMIC
#define X_ENABLE_ATOMIC (0)
#endif

#ifndef X_ENABLE_CONCURRENCY
#define X_ENABLE_CONCURRENCY (0)
#endif

#ifndef X_ENABLE_CUDA
#define X_ENABLE_CUDA (0)
#endif

#ifndef X_ENABLE_SOCKET
#define X_ENABLE_SOCKET (0)
#endif

#ifndef X_ENABLE_STRUCT_FUNCTION
#define X_ENABLE_STRUCT_FUNCTION (1)
#endif
```

---

### Version Number Generator
X\_VER: Combines `major`, `minor`, `patch` numbers into a version number. The
ranges of each component is:
- major: [0, 99]
- minor: [0, 99]
- patch: [0, 99999]

A big range of patch allow the result version number specifically work with
[\_MSC\_FULL\_VER](https://learn.microsoft.com/en-us/cpp/preprocessor/predefined-macros?view=msvc-170).

---

### Architecture Detection
- X\_32BIT: Defined as 1 if the architecture is 32-bit, 0 otherwise.
- X\_64BIT: Defined as 1 if the architecture is 64-bit, 0 otherwise.
- X\_ARM: Defined as 1 if the architecture is ARM, 0 otherwise.
- X\_ARM64: Defined as 1 if the architecture is 64-bit ARM, 0 otherwise.
- X\_X86: Defined as 1 if the architecture is 32-bit x86, 0 otherwise.
- X\_X64: Defined as 1 if the architecture is 64-bit x86, 0 otherwise.

---

### Compiler Detection
- X\_CLANG: Defined as the version number of Clang if it is being used, 0 otherwise.
- X\_GCC: Defined as the version number of GCC if it is being used, 0 otherwise.
- X\_MSVC: Defined as the version number of MSVC if it is being used, 0 otherwise.

The version number is generated by `X_VER`. For instance, `X_VER(15, 0, 6)`
(version `15.0.6`) results in `150000006`.

---

### OS Detection
- X\_CYGWIN: Defined as the version number of Cygwin if it is the target OS,
0 otherwise.
- X\_LINUX: Defined as 1 if Linux is the target OS, 0 otherwise.
- X\_MACOS: Defined as the version number if MACOS is the target OS, 0 otherwise.
- X\_WINDOWS: Defined as 1 if Windows is the target OS, 0 otherwise.

---

### Platform Detection
- X\_ANDROID: Defined as 1 if Android is the target platform, 0 otherwise.
- X\_MINGW: Defined as 1 if MinGW32/64 is the target platform, 0 otherwise.
- X\_MINGW32: Defined as the version number if MinGW32 is the target platform,
0 otherwise.
- X\_MINGW64: Defined as the version number if MinGW64 is the target platform,
0 otherwise.

---

### X\_EXPORT, X\_IMPORT
```c
#ifndef X_EXPORT
#if X_WINDOWS
#define X_EXPORT __declspec(dllexport)
#else
#define X_EXPORT __attribute__ ((visibility("default")))
#endif
#endif

#ifndef X_IMPORT
#if X_WINDOWS
#define X_IMPORT __declspec(dllimport)
#else
#define X_IMPORT __attribute__ ((visibility("hidden")))
#endif
#endif
```

See [Microsoft Docs](https://docs.microsoft.com/en-us/cpp/cpp/dllexport-dllimport?view=msvc-170)
and [GCC Wiki](https://gcc.gnu.org/wiki/Visibility) for more details.

---

### X\_KEY
```c
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
```

Several virtual key macros, most of which are defined as their corresponding
[ASCII code](https://www.asciitable.com). However, the arrow keys are handled
differently among OSs (please tell me if this statement is not accurate), they
are defined as negative integers to work around. Please checkout
<a href="#x_getch">x_getch</a> for their usage.

---

### x\_assert
An macro enables the assertion functionality for both debug and release builds.
For debug build, it is the same as the assertion macro in assert.h/cassert
header.

```c
x_assert(expr)
```

#### Parameters
- `expr`: The assertion expression.

#### Examples
```c
x_assert(1 == 1);
x_assert(1 != 1);
```

---

### x\_bit
A macro used to generate an integer with only the n-th bit set to 1. This is
useful when one needs enumerations like `0b0001`, `0b0010`, `0b0100` to perform
the `&`, `|`, `~` operations.

```c
T x_bit(bit)  // In this document, T indicats a return type from a macro.
```

#### Parameters
- `bit`: Specification for which bit of the integer should be set to 1.

#### Returns
- The generated integer, may be `int`, `long`, etc.

#### Examples
```c
enum
{
  FLAG_NONE   = 0,
  FLAG_READ   = x_bit(1),
  FLAG_WRITE  = x_bit(2),
};

int read_and_write = FLAG_READ | FLAG_WRITE;
```

---

### x\_buffer\_valid
The definition of this macro should have explained itself well:

```c
#define x_buffer_valid(buffer, size) \
  (((buffer) == NULL && (size) == 0) || ((buffer) != NULL && (size) != 0))
```

It is not implemented as function since `size` can be `int`, `size_t` etc. So
please pass arguments carefully.

#### Parameters
- `buffer`: The pointer to a buffer.
- `size`: The size of the contents in the pointer.

#### Returns
- `true` if the buffer is valid.

#### Examples
```c
int read_file(const char* file, void* buffer, size_t size)
{
  if (!x_buffer_valid(buffer, size)) {
    return EINVAL;
  }

  // operations

  return 0;
}
```

---

### x\_count
Get length of an array. This macro only works with static arrays.

```c
T x_count(array)
```

For C++, it is implemented as a templated function:

```cpp
template<class T, size_t N>
size_t x_count(const T (&array)[N])
{
  return N;
}
```

#### Parameters
- `array`: The array of which the size to be queried.

#### Returns
- The length (count of elements) of the input array.

#### Examples
```c
int a[5] = {1, 2, 3, 4, 5};

for (size_t i = 0; i < x_count(a); ++i)
{
  printf("%d", a[i]);
}
```

---

### x\_fail
A macro to check if an error number indicates a failure. It only works with
an error handling system that defines `0` as a success, e.g. POSIX errno.

```c
bool x_fail(err)
```

#### Parameters
- `err`: An error number.

#### Returns
Boolean value indicating if the error number means a failure.

#### Examples
```c
int err = EINVAL;
if (x_fail(err))
{
  printf("%s\n", strerror(err));
}
```

---

### x\_free
A macro to free a memory block allocated on heap and set it to NULL.

```c
void x_free(ptr)
```

#### Parameters
- `ptr`: A pointer was allocated with memory previously.

#### Examples
```c
int *a = (int*)malloc(5 * sizeof(int));
x_free(a);
```

---

### x\_pi
A macro for retrieving the constant [Pi](https://en.wikipedia.org/wiki/Pi). The
input argument is used to specify the target data type.

```c
T x_pi(T)
```

In C++, one may use the following template:

```cpp
template<class T>
static constexpr T x_pi = (T)3.141592653589793238462643383279502884197169399375;
// Usage: x_pi<float>, x_pi<double>, etc.
```

#### Parameters
- `T`: Target type, e.g. `float`, `double`, `long`.

#### Returns
- Pi of specified type.

#### Examples
```c
float a = x_pi(float);
double b = x_pi(double);
```

---

### x\_succ
A macro to check if an error number indicates a success. It only works with
an error handling system that defines `0` as a success, e.g. POSIX errno.

```c
bool x_succ(err)
```

#### Parameters
- `err`: An error number.

#### Returns
Boolean value indicating if the error number means a success.

#### Examples
```c
int err = 0;
if (x_succ(err))
{
  printf("%s\n", strerror(err));
}
```

---

### x\_cpu\_count
```c
size_t x_cpu_count()
```

#### Returns
- Count of CPU of current host.

---

### x\_duration
```c
double x_duration(const struct timespec start, const struct timespec end, const char* unit)
```

#### Parameters
- `start`: The start time point.
- `end`: The end time point.
- `unit`: The unit of the outcome.

#### Returns
- The duration of the two time points in specified unit.

---

### x\_file\_size
```c
long long x_file_size(const char* file)
```

#### Parameters
- `file`: File name of which the size to be exam.

#### Returns
- Size of the file in bytes.

---

### x\_full\_path
```c
const char* x_full_path(char* dst, const char* src)
```

#### Parameters
- `dst`: The full/absolute path to the input file. It should be allocated with
sufficient memory before passed into this function, otherwise `NULL` is returned.
- `src`: The (maybe relative) path to a file.

#### Returns
- The same value contained in `dst`, or `NULL` when the operation failed.

#### Examples
```c
const char* file = "./foo/bar.txt";
char buf[X_PATH_MAX] = {0};
x_full_path(buf, file);
```

---

### x\_getch
A cross-platform version of Win32's
[\_getch](https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/getch-getwch?view=msvc-170) function.

```c
int x_getch()
```

#### Returns
- The pressed key.

#### Examples
This function only works with console programs. One may use it to break a
infinity loop manually:

```c
int main(int argc, char** argv)
{
  while (true)
  {
    if (x_getch() == X_KEY_ESC)
    {
      break;  // When the 'Esc' key is pressed, the loop breaks.
    }

    x_sleep(10);
  }

  return 0;
}
```

---

### x\_now
```c
struct timespec x_now();
```

#### Returns
- A `struct timespec` instance indicating the current time.

---

### x\_path\_exists
```c
bool x_path_exists(const char* path)
```

#### Parameters
- `path`: The path to a querying file/directory.

#### Returns
- `true` if the file/directory exists.

---

### x\_split\_path
A cross-platform version of Win32's
[\_splitpath](https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/splitpath-s-wsplitpath-s?view=msvc-170) function.

```c
int x_spli_tpath(
    const char *path,
    char *root, const size_t rsz, char *dir, const size_t dsz,
    char *file, const size_t fsz, char *ext, const size_t esz)
```

---

### x\_sleep
```c
void x_sleep(const unsigned long ms)
```

#### Parameters
- `ms`: The length of the sleep duration in milliseconds.

---

### x\_strmty
```c
bool x_strmty(const char* string)
```

#### Parameters
- `string`: The string.

#### Returns
- `true` if the string is NULL or '\0' is the first character it contains.

---

### x\_timestamp
```c
const char* x_timestamp(char* buffer, const size_t size)
```

#### Parameters
- `buffer`: Buffer to store timestamp string.
- `size`: Size of the buffer.

#### Returns
- Same content of the input buffer. A empty string ("") will be returned if the
operation failed.

---

### x\_log
```c
void x_log(char level, FILE* file, const char* format, ...)
```

#### Parameters
- `level`: Logging level specification, available values are `P` (Public),
`F` (Fatal), `E` (Error), `W` (Warning), `I` (Info), `D` (Debug) and they are
**case insensitive**.
- `file`: File stream for saving the loggings. If `NULL` provided, no loggings
will be saved.
- `format`: Same as that in [printf](https://www.cplusplus.com/reference/cstdio/printf/).
- `...`: Same as that in [printf](https://www.cplusplus.com/reference/cstdio/printf/).

#### Examples
```c
int a = 0;

x_log('P', NULL "hello");
x_log('D', NULL "%s", "world");
x_log('I', NULL "%d", 10);
x_log('W', NULL "%d", ++a);
x_log('E', pf, "%d", ++a);  // e.g. FILE* pf = fopen("log.txt", "w")
x_log('F', pf, "%s", "fatal");
```

The formats of each level are almost identical. What differentiate them are the
level prefixes and the colors.

<table class="center" style="text-align:center">
<thead>
  <tr>
    <th>Level</th>
    <th>Color</th>
    <th>Debug Build Format</th>
    <th>Release Build Format</th>
  </tr>
</thead>
<tbody>
  <tr>
    <td>P</td>
    <td><div><span style="background-color:white;">&emsp;</span></div></td>
    <td rowspan="6">[level timestamp | file | function | line] message</td>
    <td rowspan="6">[level timestamp] message</td>
  </tr>
  <tr>
    <td>F</td>
    <td><div><span style="background-color:purple;">&emsp;</span></div></td>
  </tr>
  <tr>
    <td>E</td>
    <td><div><span style="background-color:red;">&emsp;</span></div></td>
  </tr>
  <tr>
    <td>W</td>
    <td><div><span style="background-color:orange;">&emsp;</span></div></td>
  </tr>
  <tr>
    <td>I</td>
    <td><div><span style="background-color:green;">&emsp;</span></div></td>
  </tr>
  <tr>
    <td>D</td>
    <td><div><span style="background-color:cyan;">&emsp;</span></div></td>
  </tr>
</tbody>
</table>

---

### x\_err
```c
// Enumerations of error categories.
enum
{
  x_err_custom = 0,           // Custom errors.
  x_err_posix  = x_bit(1),    // POSIX errors.
  x_err_win32  = x_bit(2),    // Win32 API errors, which also includes WSA errors.
  x_err_socket = x_bit(3),    // WSA errors (on Windows) or POSIX errors.
#if X_ENABLE_CUDA
  x_err_cuda   = x_bit(4),    // CUDA errors.
#endif
#if X_WINDOWS
  x_err_system = x_err_win32, // System errors, for Windows OS.
#else
  x_err_system = x_err_posix, // System errors, for POSIX OS.
#endif
};

// Enumerations of error message querying method.
enum
{
  x_err_msg_literal = 0,
  x_err_msg_lookup  = 1,
};

typedef struct _x_err_
{
  int32_t cat; // Category of the error.
  int32_t val; // Numeric value of the error.
} x_err;

// Error message lookup function API.
typedef const char* (*x_err_msg_fn)(char* msg, const size_t msz, const int32_t val);

// Retrieves the last error of specific category, via GetLastError() or
// WSAGetLastError() from Win32 API or errno from POSIX.
x_err x_err_get(const int32_t cat);

// If err.cat is x_err_custom, two additional arguments are required for
// specifying the error message querying method and the method itself. Please
// checkout test/test_x_err.c, which should be self explained.
//
// Otherwish, the description will be retrieved according to the value of the
// error via FormatMessage from Win32 API or strerror from POSIX.
const char* x_err_msg(char* msg, const size_t msz, const x_err err, ...
    /* const int method, const char* generator*/);

// Constructs an x_err instance.
x_err x_err_set(const int32_t cat, const int32_t val);

// Can be used to initialize an x_err instance.
x_err x_ok();
```

#### Examples
Please checkout *test/test_x_err.c* and *test/test_x_err.cu*.

---

### Concurrency
These are pretty much similar to those provided by
[C11 concurrency support library](https://en.cppreference.com/w/c/thread)
- x\_cnd: Condition variable utilities.
- x\_mtx: Mutex utilities.
- x\_sem: Semaphore utilities.
- x\_thd: Thread utilities.
- x\_atomic\_B: Atomic utilities of 8-bit, 16-bit, 32-bit, 64-bit, bool,
pointer (`void*`) and flag. The structs and functions are generated by macros
during compilation.

Available atomic types:
- x\_atomic\_8: contains a `uint8_t` data.
- x\_atomic\_16: contains a `uint16_t` data.
- x\_atomic\_32: contains a `uint32_t` data.
- x\_atomic\_64: contains a `uint64_t` data.
- x\_atomic\_ptr: contains a `uint32_t` or `uint64_t` (`sizeof(void*)`, depends on architecture) data.
- x\_atomic\_bool: contains a `_Bool` data.
- x\_atomic\_flag: contains a `_Bool` data.

Available atomic functions (where `B` is one of `8`, `16`, `32`, `64`, `ptr`,
`bool`, `T` is one of `uint8_t`, `uint16_t`, `uint32_t`, `uint64_t`, `void*`,
'bool'):

```c
void x_atomic_init_B(volatile x_atomic_B* obj, T desired)

void x_atomic_store_B(volatile x_atomic_B* obj, T desired, x_memory_order order)

T x_atomic_load_B(volatile x_atomic_B* obj, x_memory_order order)

T x_atomic_exchange_B(volatile x_atomic_B* obj, T desired, x_memory_order order)

bool x_atomic_compare_exchange_B(
    volatile x_atomic_B* obj, T* expected, T desired,
    x_memory_order succ, x_memory_order fail)

T x_atomic_fetch_add_B(volatile x_atomic_B* obj, T desired, x_memory_order order)

T x_atomic_fetch_sub_B(volatile x_atomic_B* obj, T desired, x_memory_order order)

T x_atomic_fetch_Or_B(volatile x_atomic_B* obj, T desired, x_memory_order order)

T x_atomic_fetch_Xor_B(volatile x_atomic_B* obj, T desired, x_memory_order order)

T x_atomic_fetch_And_B(volatile x_atomic_B* obj, T desired, x_memory_order order)

#define x_kill_dependency(x) (x)

#define x_atomic_is_lock_free(T) _x_is_size_lock_free(sizeof(T))

bool x_atomic_flag_test_and_set(volatile x_atomic_flag* obj, x_memory_order order)

void x_atomic_flag_clear(volatile x_atomic_flag* obj, x_memory_order order)

void x_atomic_signal_fence(const x_memory_order order)

void x_atomic_thread_fence(const x_memory_order order)
```

Function pointers inside `x_atomic_B` are provided to unified APIs so that
different atomic object can be replaced easily during code refactor. For
example:

```c
// before
x_atomic_32 obj = X_ATOMIC_VAR_INIT(32);  // was 32-bit data
obj.init(&obj, 0);
obj.fetch_add(&obj, 1);

// after
x_atomic_64 obj = X_ATOMIC_VAR_INIT(64);  // refactor to 64-bit
obj.init(&obj, 0);                        // no need to change this
obj.fetch_add(&obj, 1);                   // this too, woohoo!
```

Definition of `x_memory_order`:

```c
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
```

Except `x_atomic_bool` and `x_atomic_flag`, `x_atomic_B` objects only care
about how many bits of the internal data has. Therefore, one should perform
proper data type casting when storing to or loading from these atomic objects.

---

### x\_cks
#### CRC-32 (on the fly) Checksum
```c
uint32_t x_cks_crc32(const void* data, const size_t size, const uint32_t* prev)
```

#### Parameters
- `data`: Source data of the checksum.
- `size`: Size of the data in bytes.
- `prev`: Optional previous checksum result. Can be `NULL`.

#### Returns
- A CRC-32 checksum.

#### IPv4 Header Checksum
```c
uint16_t x_cks_rfc1071(const void* data, const size_t size)
```

#### Parameters
- `data`: Source data of the checksum.
- `size`: Size of the data in bytes.

#### Returns
- An IPv4 header checksum. Checkout [RFC 1071](https://www.rfc-editor.org/info/rfc1071)
for more details.

#### XOR Checksum
```c
uint8_t x_cks_xor(const void* data, const size_t size)
```

#### Parameters
- `data`: Source data of the checksum.
- `size`: Size of the data in bytes.

#### Returns
- A checksum calculated by perform XOR of all data in `data`.

---

### x\_pkt
Packet utilities. The source code should have explained itself.

---

### x\_iov
IO vector utilities. The source code should have explained itself.

---

### x\_skt
Socket utilities.

---

### x\_node
Nodes for linked queues and lists.

---

### x\_deque
Simple double ended queue without synchronization.

---

### x\_lfque
**L**ock-**f**ree queue.

---

### x\_tlque
**T**wo-**l**ock queue.

---

### x\_tictoc
Utilities for recording code execution time.

```c
typedef struct _x_tictoc_
{
  struct timespec start;  // Timestamp when the recording starts.
  double elapsed;         // Execution time of last cycle.

  struct
  {
    bool ready;  // Set to `true` once targe execution cycles are reached.
    size_t cyc;  // Total cycles to be record.
    double sum;  // Total elapsed time.
    double avg;  // Average execution time per cycle.
    struct
    {
      size_t idx;  // The index of the cycle that max/min execution time happened.
      double val;  // The execution time of `idx`th cycle.
    } max, min;  // Most (max) and least (min) execution time information.
  } report;
} x_tictoc;

X_INLINE int x_tictoc_init(x_tictoc* tictoc);

// Start point of timing.
X_INLINE int x_tic(x_tictoc* tictoc, const bool echo);

// End point of timing.
X_INLINE int x_toc(x_tictoc* tictoc, const char* unit, const bool echo);

// End point of timing in a multi-cycle recording operation.
X_INLINE int x_toc_ex(
    x_tictoc* tictoc,
    const char* unit, const long long cycle, const char* title,
    char* echo, size_t* size);
```


<!----------------------------------------------------------------- LICENSE -->
## License
Distributed under the [Mulan PSL v2](http://license.coscl.org.cn/MulanPSL2)
license. See [LICENSE](LICENSE) for more information.
