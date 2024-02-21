/*++

Module Name:

    efi.h

Abstract:

    Public EFI header files(single)



Revision History

--*/
/*++

Copyright (c) 1998  Intel Corporation

Module Name:

    efi.h

Abstract:

    Public EFI header files



Revision History

--*/


// Add a predefined macro to detect usage of the library
#ifndef _GNU_EFI
#define _GNU_EFI
#endif

//
// Build flags on input
//  EFI32
//  EFI_DEBUG               - Enable debugging code
//  EFI_NT_EMULATOR         - Building for running under NT
//


#ifndef _EFI_INCLUDE_
#define _EFI_INCLUDE_

#define EFI_FIRMWARE_VENDOR         L"INTEL"
#define EFI_FIRMWARE_MAJOR_REVISION 12
#define EFI_FIRMWARE_MINOR_REVISION 33
#define EFI_FIRMWARE_REVISION ((EFI_FIRMWARE_MAJOR_REVISION <<16) | (EFI_FIRMWARE_MINOR_REVISION))

#if defined(_M_X64) || defined(__x86_64__) || defined(__amd64__)
/*++

Copyright (c) 1998  Intel Corporation

Module Name:

    efefind.h

Abstract:

    EFI to compile bindings




Revision History

--*/
#ifndef X86_64_EFI_BIND
#define X86_64_EFI_BIND
#ifndef __GNUC__
#pragma pack()
#endif

#if defined(_MSC_VER)
    #define HAVE_USE_MS_ABI 1
#elif defined(GNU_EFI_USE_MS_ABI)
    #if (defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 7)))||(defined(__clang__) && (__clang_major__ > 3 || (__clang_major__ == 3 && __clang_minor__ >= 2)))
        #define HAVE_USE_MS_ABI 1
    #else
        #error Compiler is too old for GNU_EFI_USE_MS_ABI
    #endif
#endif

//
// Basic int types of various widths
//

#if !defined(__STDC_VERSION__) || (__STDC_VERSION__ < 199901L ) && !defined(__cplusplus)

    // No ANSI C 1999/2000 stdint.h integer width declarations 

    #if defined(_MSC_EXTENSIONS)

        // Use Microsoft C compiler integer width declarations 

        typedef unsigned __int64    uint64_t;
        typedef __int64             int64_t;
        typedef unsigned __int32    uint32_t;
        typedef __int32             int32_t;
        typedef unsigned short      uint16_t;
        typedef short               int16_t;
        typedef unsigned char       uint8_t;
        typedef char                int8_t;
    #elif defined(__GNUC__)
        typedef int __attribute__((__mode__(__DI__)))           int64_t;
        typedef unsigned int __attribute__((__mode__(__DI__)))  uint64_t;
        typedef unsigned int        uint32_t;
        typedef int                 int32_t;
        typedef unsigned short      uint16_t;
        typedef short               int16_t;
        typedef unsigned char       uint8_t;
        typedef signed char         int8_t;
    #elif defined(UNIX_LP64)

        /*  Use LP64 programming model from C_FLAGS for integer width declarations */

       typedef unsigned long       uint64_t;
       typedef long                int64_t;
       typedef unsigned int        uint32_t;
       typedef int                 int32_t;
       typedef unsigned short      uint16_t;
       typedef short               int16_t;
       typedef unsigned char       uint8_t;
       typedef char                int8_t;
    #else

       /*  Assume P64 programming model from C_FLAGS for integer width declarations */

       typedef unsigned long long  uint64_t __attribute__((aligned (8)));
       typedef long long           int64_t __attribute__((aligned (8)));
       typedef unsigned int        uint32_t;
       typedef int                 int32_t;
       typedef unsigned short      uint16_t;
       typedef short               int16_t;
       typedef unsigned char       uint8_t;
       typedef char                int8_t;
    #endif
    typedef uint64_t            uintptr_t;
    typedef int64_t             intptr_t;
#else
typedef signed char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef long long int64_t;

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

typedef int8_t int_least8_t;
typedef int16_t int_least16_t;
typedef int32_t int_least32_t;
typedef int64_t int_least64_t;
typedef uint8_t uint_least8_t;
typedef uint16_t uint_least16_t;
typedef uint32_t uint_least32_t;
typedef uint64_t uint_least64_t;

typedef int8_t int_fast8_t;
typedef int16_t int_fast16_t;
typedef int32_t int_fast32_t;
typedef int64_t int_fast64_t;
typedef uint8_t uint_fast8_t;
typedef uint16_t uint_fast16_t;
typedef uint32_t uint_fast32_t;
typedef uint64_t uint_fast64_t;

typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef short __int16_t;
typedef unsigned short __uint16_t;
typedef int __int32_t;
typedef unsigned int __uint32_t;
typedef long long __int64_t;
typedef unsigned long long __uint64_t;

typedef unsigned char u_int8_t;
typedef unsigned short u_int16_t;
typedef unsigned int u_int32_t;
typedef unsigned long long u_int64_t;

typedef unsigned long uintptr_t;

typedef long int intmax_t;
typedef long unsigned int uintmax_t;


#endif

//
// Basic EFI types of various widths
//

#ifndef __WCHAR_TYPE__
# define __WCHAR_TYPE__ short
#endif

typedef uint64_t   UINT64;
typedef int64_t    INT64;

#ifndef _BASETSD_H_
    typedef uint32_t   UINT32;
    typedef int32_t    INT32;
#endif

typedef uint16_t   UINT16;
typedef int16_t    INT16;
typedef uint8_t    UINT8;
typedef int8_t     INT8;
typedef __WCHAR_TYPE__ WCHAR;

#undef VOID
#define VOID    void


typedef int64_t    INTN;
typedef uint64_t   UINTN;

#ifdef EFI_NT_EMULATOR
    #define POST_CODE(_Data)
#else    
    #ifdef EFI_DEBUG
#define POST_CODE(_Data)    __asm mov eax,(_Data) __asm out 0x80,al
    #else
        #define POST_CODE(_Data)
    #endif  
#endif

#define EFIERR(a)           (0x8000000000000000 | a)
#define EFI_ERROR_MASK      0x8000000000000000
#define EFIERR_OEM(a)       (0xc000000000000000 | a)      


#define BAD_POINTER         0xFBFBFBFBFBFBFBFB
#define MAX_ADDRESS         0xFFFFFFFFFFFFFFFF

#ifdef EFI_NT_EMULATOR
    #define BREAKPOINT()        __asm { int 3 }
#else
    #define BREAKPOINT()        while (TRUE);    // Make it hang on Bios[Dbg]32
#endif

//
// Pointers must be aligned to these address to function
//

#define MIN_ALIGNMENT_SIZE  4

#define ALIGN_VARIABLE(Value ,Adjustment) \
            (UINTN)Adjustment = 0; \
            if((UINTN)Value % MIN_ALIGNMENT_SIZE) \
                (UINTN)Adjustment = MIN_ALIGNMENT_SIZE - ((UINTN)Value % MIN_ALIGNMENT_SIZE); \
            Value = (UINTN)Value + (UINTN)Adjustment


//
// Define macros to build data structure signatures from characters.
//

#define EFI_SIGNATURE_16(A,B)             ((A) | (B<<8))
#define EFI_SIGNATURE_32(A,B,C,D)         (EFI_SIGNATURE_16(A,B)     | (EFI_SIGNATURE_16(C,D)     << 16))
#define EFI_SIGNATURE_64(A,B,C,D,E,F,G,H) (EFI_SIGNATURE_32(A,B,C,D) | ((UINT64)(EFI_SIGNATURE_32(E,F,G,H)) << 32))
//
// To export & import functions in the EFI emulator environment
//

#ifdef EFI_NT_EMULATOR
    #define EXPORTAPI           __declspec( dllexport )
#else
    #define EXPORTAPI
#endif


//
// EFIAPI - prototype calling convention for EFI function pointers
// BOOTSERVICE - prototype for implementation of a boot service interface
// RUNTIMESERVICE - prototype for implementation of a runtime service interface
// RUNTIMEFUNCTION - prototype for implementation of a runtime function that is not a service
// RUNTIME_CODE - pragma macro for declaring runtime code    
//

#ifndef EFIAPI                  // Forces EFI calling conventions reguardless of compiler options 
    #ifdef _MSC_EXTENSIONS
        #define EFIAPI __cdecl  // Force C calling convention for Microsoft C compiler 
    #elif defined(HAVE_USE_MS_ABI)
        // Force amd64/ms calling conventions.
        #define EFIAPI __attribute__((ms_abi))
    #else
        #define EFIAPI          // Substitute expresion to force C calling convention 
    #endif
#endif

#define BOOTSERVICE
//#define RUNTIMESERVICE(proto,a)    alloc_text("rtcode",a); proto a
//#define RUNTIMEFUNCTION(proto,a)   alloc_text("rtcode",a); proto a
#define RUNTIMESERVICE
#define RUNTIMEFUNCTION


#define RUNTIME_CODE(a)         alloc_text("rtcode", a)
#define BEGIN_RUNTIME_DATA()    data_seg("rtdata")
#define END_RUNTIME_DATA()      data_seg("")

#define VOLATILE    volatile

#define MEMORY_FENCE()    

#ifdef EFI_NT_EMULATOR

//
// To help ensure proper coding of integrated drivers, they are
// compiled as DLLs.  In NT they require a dll init entry pointer.
// The macro puts a stub entry point into the DLL so it will load.
//

#define EFI_DRIVER_ENTRY_POINT(InitFunction)    \
    UINTN                                       \
    __stdcall                                   \
    _DllMainCRTStartup (                        \
        UINTN    Inst,                          \
        UINTN    reason_for_call,               \
        VOID    *rserved                        \
        )                                       \
    {                                           \
        return 1;                               \
    }                                           \
                                                \
    int                                         \
    EXPORTAPI                                   \
    __cdecl                                     \
    InitializeDriver (                          \
        void *ImageHandle,                      \
        void *SystemTable                       \
        )                                       \
    {                                           \
        return InitFunction(ImageHandle, SystemTable);       \
    }


    #define LOAD_INTERNAL_DRIVER(_if, type, name, entry)      \
        (_if)->LoadInternal(type, name, NULL)             

#else // EFI_NT_EMULATOR 

//
// When build similiar to FW, then link everything together as
// one big module. For the MSVC toolchain, we simply tell the
// linker what our driver init function is using /ENTRY.
//
#if defined(_MSC_EXTENSIONS)
    #define EFI_DRIVER_ENTRY_POINT(InitFunction) \
        __pragma(comment(linker, "/ENTRY:" # InitFunction))
#else
    #define EFI_DRIVER_ENTRY_POINT(InitFunction)    \
        UINTN                                       \
        InitializeDriver (                          \
            VOID    *ImageHandle,                   \
            VOID    *SystemTable                    \
            )                                       \
        {                                           \
            return InitFunction(ImageHandle,        \
                    SystemTable);                   \
        }                                           \
                                                    \
        EFI_STATUS efi_main(                        \
            EFI_HANDLE image,                       \
            EFI_SYSTEM_TABLE *systab                \
            ) __attribute__((weak,                  \
                    alias ("InitializeDriver")));
#endif

    #define LOAD_INTERNAL_DRIVER(_if, type, name, entry)    \
            (_if)->LoadInternal(type, name, entry)

#endif // EFI_NT_EMULATOR

//
// Some compilers don't support the forward reference construct:
//  typedef struct XXXXX
//
// The following macro provide a workaround for such cases.
//
#ifdef NO_INTERFACE_DECL
#define INTERFACE_DECL(x)
#else
#if defined(__GNUC__) || defined(_MSC_EXTENSIONS)
#define INTERFACE_DECL(x) struct x
#else
#define INTERFACE_DECL(x) typedef struct x
#endif
#endif

/* for x86_64, EFI_FUNCTION_WRAPPER must be defined */
#if defined(HAVE_USE_MS_ABI)
#define uefi_call_wrapper(func, va_num, ...) func(__VA_ARGS__)
#else
/*
  Credits for macro-magic:
    https://groups.google.com/forum/?fromgroups#!topic/comp.std.c/d-6Mj5Lko_s
    http://efesx.com/2010/08/31/overloading-macros/
*/
#define __VA_NARG__(...)                        \
  __VA_NARG_(_0, ## __VA_ARGS__, __RSEQ_N())
#define __VA_NARG_(...)                         \
  __VA_ARG_N(__VA_ARGS__)
#define __VA_ARG_N(                             \
  _0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,N,...) N
#define __RSEQ_N()                              \
  10, 9,  8,  7,  6,  5,  4,  3,  2,  1,  0

#define __VA_ARG_NSUFFIX__(prefix,...)                  \
  __VA_ARG_NSUFFIX_N(prefix, __VA_NARG__(__VA_ARGS__))
#define __VA_ARG_NSUFFIX_N(prefix,nargs)        \
  __VA_ARG_NSUFFIX_N_(prefix, nargs)
#define __VA_ARG_NSUFFIX_N_(prefix,nargs)       \
  prefix ## nargs

/* Prototypes of EFI cdecl -> stdcall trampolines */
UINT64 efi_call0(void *func);
UINT64 efi_call1(void *func, UINT64 arg1);
UINT64 efi_call2(void *func, UINT64 arg1, UINT64 arg2);
UINT64 efi_call3(void *func, UINT64 arg1, UINT64 arg2, UINT64 arg3);
UINT64 efi_call4(void *func, UINT64 arg1, UINT64 arg2, UINT64 arg3,
                 UINT64 arg4);
UINT64 efi_call5(void *func, UINT64 arg1, UINT64 arg2, UINT64 arg3,
                 UINT64 arg4, UINT64 arg5);
UINT64 efi_call6(void *func, UINT64 arg1, UINT64 arg2, UINT64 arg3,
                 UINT64 arg4, UINT64 arg5, UINT64 arg6);
UINT64 efi_call7(void *func, UINT64 arg1, UINT64 arg2, UINT64 arg3,
                 UINT64 arg4, UINT64 arg5, UINT64 arg6, UINT64 arg7);
UINT64 efi_call8(void *func, UINT64 arg1, UINT64 arg2, UINT64 arg3,
                 UINT64 arg4, UINT64 arg5, UINT64 arg6, UINT64 arg7,
                 UINT64 arg8);
UINT64 efi_call9(void *func, UINT64 arg1, UINT64 arg2, UINT64 arg3,
                 UINT64 arg4, UINT64 arg5, UINT64 arg6, UINT64 arg7,
                 UINT64 arg8, UINT64 arg9);
UINT64 efi_call10(void *func, UINT64 arg1, UINT64 arg2, UINT64 arg3,
                  UINT64 arg4, UINT64 arg5, UINT64 arg6, UINT64 arg7,
                  UINT64 arg8, UINT64 arg9, UINT64 arg10);

/* Front-ends to efi_callX to avoid compiler warnings */
#define _cast64_efi_call0(f) \
  efi_call0(f)
#define _cast64_efi_call1(f,a1) \
  efi_call1(f, (UINT64)(a1))
#define _cast64_efi_call2(f,a1,a2) \
  efi_call2(f, (UINT64)(a1), (UINT64)(a2))
#define _cast64_efi_call3(f,a1,a2,a3) \
  efi_call3(f, (UINT64)(a1), (UINT64)(a2), (UINT64)(a3))
#define _cast64_efi_call4(f,a1,a2,a3,a4) \
  efi_call4(f, (UINT64)(a1), (UINT64)(a2), (UINT64)(a3), (UINT64)(a4))
#define _cast64_efi_call5(f,a1,a2,a3,a4,a5) \
  efi_call5(f, (UINT64)(a1), (UINT64)(a2), (UINT64)(a3), (UINT64)(a4), \
            (UINT64)(a5))
#define _cast64_efi_call6(f,a1,a2,a3,a4,a5,a6) \
  efi_call6(f, (UINT64)(a1), (UINT64)(a2), (UINT64)(a3), (UINT64)(a4), \
            (UINT64)(a5), (UINT64)(a6))
#define _cast64_efi_call7(f,a1,a2,a3,a4,a5,a6,a7) \
  efi_call7(f, (UINT64)(a1), (UINT64)(a2), (UINT64)(a3), (UINT64)(a4), \
            (UINT64)(a5), (UINT64)(a6), (UINT64)(a7))
#define _cast64_efi_call8(f,a1,a2,a3,a4,a5,a6,a7,a8) \
  efi_call8(f, (UINT64)(a1), (UINT64)(a2), (UINT64)(a3), (UINT64)(a4), \
            (UINT64)(a5), (UINT64)(a6), (UINT64)(a7), (UINT64)(a8))
#define _cast64_efi_call9(f,a1,a2,a3,a4,a5,a6,a7,a8,a9) \
  efi_call9(f, (UINT64)(a1), (UINT64)(a2), (UINT64)(a3), (UINT64)(a4), \
            (UINT64)(a5), (UINT64)(a6), (UINT64)(a7), (UINT64)(a8), \
            (UINT64)(a9))
#define _cast64_efi_call10(f,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10) \
  efi_call10(f, (UINT64)(a1), (UINT64)(a2), (UINT64)(a3), (UINT64)(a4), \
             (UINT64)(a5), (UINT64)(a6), (UINT64)(a7), (UINT64)(a8), \
             (UINT64)(a9), (UINT64)(a10))

/* main wrapper (va_num ignored) */
#define uefi_call_wrapper(func,va_num,...)                        \
  __VA_ARG_NSUFFIX__(_cast64_efi_call, __VA_ARGS__) (func , ##__VA_ARGS__)

#endif

#if defined(HAVE_USE_MS_ABI) && !defined(_MSC_EXTENSIONS)
    #define EFI_FUNCTION __attribute__((ms_abi))
#else
    #define EFI_FUNCTION
#endif

#ifdef _MSC_EXTENSIONS
#pragma warning ( disable : 4731 )  // Suppress warnings about modification of EBP
#endif

#endif
#elif defined(_M_IX86) || defined(__i386__)
/*++

Copyright (c) 1998  Intel Corporation

Module Name:

    efefind.h

Abstract:

    EFI to compile bindings




Revision History

--*/

#ifndef __GNUC__
#pragma pack()
#endif

//
// Basic int types of various widths
//

#if !defined(__STDC_VERSION__) || (__STDC_VERSION__ < 199901L ) && !defined(__cplusplus)

    // No ANSI C 1999/2000 stdint.h integer width declarations 

    #if defined(_MSC_EXTENSIONS)

        // Use Microsoft C compiler integer width declarations 

        typedef unsigned __int64    uint64_t;
        typedef __int64             int64_t;
        typedef unsigned __int32    uint32_t;
        typedef __int32             int32_t;
        typedef unsigned short      uint16_t;
        typedef short               int16_t;
        typedef unsigned char       uint8_t;
        typedef char                int8_t;
    #elif defined(__GNUC__)
        typedef int __attribute__((__mode__(__DI__)))           int64_t;
        typedef unsigned int __attribute__((__mode__(__DI__)))  uint64_t;
        typedef unsigned int        uint32_t;
        typedef int                 int32_t;
        typedef unsigned short      uint16_t;
        typedef short               int16_t;
        typedef unsigned char       uint8_t;
        typedef signed char         int8_t;
    #elif defined(UNIX_LP64)

        /*  Use LP64 programming model from C_FLAGS for integer width declarations */

       typedef unsigned long       uint64_t;
       typedef long                int64_t;
       typedef unsigned int        uint32_t;
       typedef int                 int32_t;
       typedef unsigned short      uint16_t;
       typedef short               int16_t;
       typedef unsigned char       uint8_t;
       typedef char                int8_t;
    #else

       /*  Assume P64 programming model from C_FLAGS for integer width declarations */

       typedef unsigned long long  uint64_t __attribute__((aligned (8)));
       typedef long long           int64_t __attribute__((aligned (8)));
       typedef unsigned int        uint32_t;
       typedef int                 int32_t;
       typedef unsigned short      uint16_t;
       typedef short               int16_t;
       typedef unsigned char       uint8_t;
       typedef char                int8_t;
    #endif
    typedef uint32_t            uintptr_t;
    typedef int32_t             intptr_t;
#elif defined(__GNUC__)
typedef signed char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef long long int64_t;

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

typedef int8_t int_least8_t;
typedef int16_t int_least16_t;
typedef int32_t int_least32_t;
typedef int64_t int_least64_t;
typedef uint8_t uint_least8_t;
typedef uint16_t uint_least16_t;
typedef uint32_t uint_least32_t;
typedef uint64_t uint_least64_t;

typedef int8_t int_fast8_t;
typedef int16_t int_fast16_t;
typedef int32_t int_fast32_t;
typedef int64_t int_fast64_t;
typedef uint8_t uint_fast8_t;
typedef uint16_t uint_fast16_t;
typedef uint32_t uint_fast32_t;
typedef uint64_t uint_fast64_t;

typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef short __int16_t;
typedef unsigned short __uint16_t;
typedef int __int32_t;
typedef unsigned int __uint32_t;
typedef long long __int64_t;
typedef unsigned long long __uint64_t;

typedef unsigned char u_int8_t;
typedef unsigned short u_int16_t;
typedef unsigned int u_int32_t;
typedef unsigned long long u_int64_t;

typedef unsigned long uintptr_t;

typedef long int intmax_t;
typedef long unsigned int uintmax_t;


#endif

//
// Basic EFI types of various widths
//

#ifndef __WCHAR_TYPE__
# define __WCHAR_TYPE__ short
#endif

typedef uint64_t   UINT64;
typedef int64_t    INT64;

#ifndef _BASETSD_H_
    typedef uint32_t   UINT32;
    typedef int32_t    INT32;
#endif

typedef uint16_t   UINT16;
typedef int16_t    INT16;
typedef uint8_t    UINT8;
typedef int8_t     INT8;
typedef __WCHAR_TYPE__ WCHAR;

#undef VOID
#define VOID    void


typedef int32_t    INTN;
typedef uint32_t   UINTN;

#ifdef EFI_NT_EMULATOR
    #define POST_CODE(_Data)
#else    
    #ifdef EFI_DEBUG
#define POST_CODE(_Data)    __asm mov eax,(_Data) __asm out 0x80,al
    #else
        #define POST_CODE(_Data)
    #endif  
#endif

#define EFIERR(a)           (0x80000000 | a)
#define EFI_ERROR_MASK      0x80000000
#define EFIERR_OEM(a)       (0xc0000000 | a)      


#define BAD_POINTER         0xFBFBFBFB
#define MAX_ADDRESS         0xFFFFFFFF

#ifdef EFI_NT_EMULATOR
    #define BREAKPOINT()        __asm { int 3 }
#else
    #define BREAKPOINT()        while (TRUE);    // Make it hang on Bios[Dbg]32
#endif

//
// Pointers must be aligned to these address to function
//

#define MIN_ALIGNMENT_SIZE  4

#define ALIGN_VARIABLE(Value ,Adjustment) \
            (UINTN)Adjustment = 0; \
            if((UINTN)Value % MIN_ALIGNMENT_SIZE) \
                (UINTN)Adjustment = MIN_ALIGNMENT_SIZE - ((UINTN)Value % MIN_ALIGNMENT_SIZE); \
            Value = (UINTN)Value + (UINTN)Adjustment


//
// Define macros to build data structure signatures from characters.
//

#define EFI_SIGNATURE_16(A,B)             ((A) | (B<<8))
#define EFI_SIGNATURE_32(A,B,C,D)         (EFI_SIGNATURE_16(A,B)     | (EFI_SIGNATURE_16(C,D)     << 16))
#define EFI_SIGNATURE_64(A,B,C,D,E,F,G,H) (EFI_SIGNATURE_32(A,B,C,D) | ((UINT64)(EFI_SIGNATURE_32(E,F,G,H)) << 32))
//
// To export & import functions in the EFI emulator environment
//

#ifdef EFI_NT_EMULATOR
    #define EXPORTAPI           __declspec( dllexport )
#else
    #define EXPORTAPI
#endif


//
// EFIAPI - prototype calling convention for EFI function pointers
// BOOTSERVICE - prototype for implementation of a boot service interface
// RUNTIMESERVICE - prototype for implementation of a runtime service interface
// RUNTIMEFUNCTION - prototype for implementation of a runtime function that is not a service
// RUNTIME_CODE - pragma macro for declaring runtime code    
//

#ifndef EFIAPI                  // Forces EFI calling conventions reguardless of compiler options 
    #ifdef _MSC_EXTENSIONS
        #define EFIAPI __cdecl  // Force C calling convention for Microsoft C compiler 
    #else
        #define EFIAPI          // Substitute expresion to force C calling convention 
    #endif
#endif

#define BOOTSERVICE
//#define RUNTIMESERVICE(proto,a)    alloc_text("rtcode",a); proto a
//#define RUNTIMEFUNCTION(proto,a)   alloc_text("rtcode",a); proto a
#define RUNTIMESERVICE
#define RUNTIMEFUNCTION


#define RUNTIME_CODE(a)         alloc_text("rtcode", a)
#define BEGIN_RUNTIME_DATA()    data_seg("rtdata")
#define END_RUNTIME_DATA()      data_seg("")

#define VOLATILE    volatile

#define MEMORY_FENCE()    

#ifdef EFI_NT_EMULATOR

//
// To help ensure proper coding of integrated drivers, they are
// compiled as DLLs.  In NT they require a dll init entry pointer.
// The macro puts a stub entry point into the DLL so it will load.
//

#define EFI_DRIVER_ENTRY_POINT(InitFunction)    \
    UINTN                                       \
    __stdcall                                   \
    _DllMainCRTStartup (                        \
        UINTN    Inst,                          \
        UINTN    reason_for_call,               \
        VOID    *rserved                        \
        )                                       \
    {                                           \
        return 1;                               \
    }                                           \
                                                \
    int                                         \
    EXPORTAPI                                   \
    __cdecl                                     \
    InitializeDriver (                          \
        void *ImageHandle,                      \
        void *SystemTable                       \
        )                                       \
    {                                           \
        return InitFunction(ImageHandle, SystemTable);       \
    }


    #define LOAD_INTERNAL_DRIVER(_if, type, name, entry)      \
        (_if)->LoadInternal(type, name, NULL)             

#else // EFI_NT_EMULATOR 

//
// When build similiar to FW, then link everything together as
// one big module. For the MSVC toolchain, we simply tell the
// linker what our driver init function is using /ENTRY.
//
#if defined(_MSC_EXTENSIONS)
    #define EFI_DRIVER_ENTRY_POINT(InitFunction) \
        __pragma(comment(linker, "/ENTRY:" # InitFunction))
#else
    #define EFI_DRIVER_ENTRY_POINT(InitFunction)    \
        UINTN                                       \
        InitializeDriver (                          \
            VOID    *ImageHandle,                   \
            VOID    *SystemTable                    \
            )                                       \
        {                                           \
            return InitFunction(ImageHandle,        \
                    SystemTable);                   \
        }                                           \
                                                    \
        EFI_STATUS efi_main(                        \
            EFI_HANDLE image,                       \
            EFI_SYSTEM_TABLE *systab                \
            ) __attribute__((weak,                  \
                    alias ("InitializeDriver")));
#endif

    #define LOAD_INTERNAL_DRIVER(_if, type, name, entry)    \
            (_if)->LoadInternal(type, name, entry)

#endif // EFI_FW_NT 

//
// Some compilers don't support the forward reference construct:
//  typedef struct XXXXX
//
// The following macro provide a workaround for such cases.
//
#ifdef NO_INTERFACE_DECL
#define INTERFACE_DECL(x)
#else
#if defined(__GNUC__) || defined(_MSC_EXTENSIONS)
#define INTERFACE_DECL(x) struct x
#else
#define INTERFACE_DECL(x) typedef struct x
#endif
#endif

/* No efi call wrapper for IA32 architecture */
#define uefi_call_wrapper(func, va_num, ...)	func(__VA_ARGS__)
#define EFI_FUNCTION

#ifdef _MSC_EXTENSIONS
#pragma warning ( disable : 4731 )  // Suppress warnings about modification of EBP
#endif

#elif defined(_M_IA64) || defined(__ia64__)
/*++

Copyright (c) 1998  Intel Corporation

Module Name:

    efefind.h

Abstract:

    EFI to compile bindings




Revision History

--*/

#pragma pack()


//
// Basic int types of various widths
//

#if !defined(__STDC_VERSION__) || (__STDC_VERSION__ < 199901L ) && !defined(__cplusplus)

    // No ANSI C 1999/2000 stdint.h integer width declarations 

    #ifdef _MSC_EXTENSIONS
        // Use Microsoft C compiler integer width declarations 

        typedef unsigned __int64    uint64_t;
        typedef __int64             int64_t;
        typedef unsigned __int32    uint32_t;
        typedef __int32             int32_t;
        typedef unsigned __int16    uint16_t;
        typedef __int16             int16_t;
        typedef unsigned __int8     uint8_t;
        typedef __int8              int8_t;
    #elif defined(UNIX_LP64)
        // Use LP64 programming model from C_FLAGS for integer width declarations 

        typedef unsigned long       uint64_t;
        typedef long                int64_t;
        typedef unsigned int        uint32_t;
        typedef int                 int32_t;
        typedef unsigned short      uint16_t;
        typedef short               int16_t;
        typedef unsigned char       uint8_t;
        typedef char                int8_t;
    #else
        // Assume P64 programming model from C_FLAGS for integer width declarations 

        typedef unsigned long long  uint64_t;
        typedef long long           int64_t;
        typedef unsigned int        uint32_t;
        typedef int                 int32_t;
        typedef unsigned short      uint16_t;
        typedef short               int16_t;
        typedef unsigned char       uint8_t;
        typedef char                int8_t;
    #endif
    typedef uint64_t            uintptr_t;
    typedef int64_t             intptr_t;
#elif defined(__GNUC__)
typedef signed char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef long long int64_t;

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

typedef int8_t int_least8_t;
typedef int16_t int_least16_t;
typedef int32_t int_least32_t;
typedef int64_t int_least64_t;
typedef uint8_t uint_least8_t;
typedef uint16_t uint_least16_t;
typedef uint32_t uint_least32_t;
typedef uint64_t uint_least64_t;

typedef int8_t int_fast8_t;
typedef int16_t int_fast16_t;
typedef int32_t int_fast32_t;
typedef int64_t int_fast64_t;
typedef uint8_t uint_fast8_t;
typedef uint16_t uint_fast16_t;
typedef uint32_t uint_fast32_t;
typedef uint64_t uint_fast64_t;

typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef short __int16_t;
typedef unsigned short __uint16_t;
typedef int __int32_t;
typedef unsigned int __uint32_t;
typedef long long __int64_t;
typedef unsigned long long __uint64_t;

typedef unsigned char u_int8_t;
typedef unsigned short u_int16_t;
typedef unsigned int u_int32_t;
typedef unsigned long long u_int64_t;

typedef unsigned long uintptr_t;

typedef long int intmax_t;
typedef long unsigned int uintmax_t;


#endif

//
// Basic EFI types of various widths
//
#ifndef __WCHAR_TYPE__
# define __WCHAR_TYPE__	short
#endif


typedef uint64_t   UINT64;
typedef int64_t    INT64;
typedef uint32_t   UINT32;
typedef int32_t    INT32;
typedef uint16_t   UINT16;
typedef int16_t    INT16;
typedef uint8_t    UINT8;
typedef int8_t     INT8;
typedef __WCHAR_TYPE__ WCHAR;


#undef VOID
#define VOID    void


typedef int64_t    INTN;
typedef uint64_t   UINTN;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// BugBug: Code to debug
//
#define BIT63   0x8000000000000000

#define PLATFORM_IOBASE_ADDRESS   (0xffffc000000 | BIT63)                                               
#define PORT_TO_MEMD(_Port) (PLATFORM_IOBASE_ADDRESS | ( ( ( (_Port) & 0xfffc) << 10 ) | ( (_Port) & 0x0fff) ) )
                                                                           
//                                                                  
// Macro's with casts make this much easier to use and read.
//
#define PORT_TO_MEM8D(_Port)  (*(UINT8  *)(PORT_TO_MEMD(_Port)))
#define POST_CODE(_Data)  (PORT_TO_MEM8D(0x80) = (_Data))
//
// BugBug: End Debug Code!!!
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#define EFIERR(a)           (0x8000000000000000 | a)
#define EFI_ERROR_MASK      0x8000000000000000
#define EFIERR_OEM(a)       (0xc000000000000000 | a)      

#define BAD_POINTER         0xFBFBFBFBFBFBFBFB
#define MAX_ADDRESS         0xFFFFFFFFFFFFFFFF

#define BREAKPOINT()        while (TRUE)

//
// Pointers must be aligned to these address to function
//  you will get an alignment fault if this value is less than 8
//
#define MIN_ALIGNMENT_SIZE  8

#define ALIGN_VARIABLE(Value , Adjustment) \
            (UINTN) Adjustment = 0; \
            if((UINTN)Value % MIN_ALIGNMENT_SIZE) \
                (UINTN)Adjustment = MIN_ALIGNMENT_SIZE - ((UINTN)Value % MIN_ALIGNMENT_SIZE); \
            Value = (UINTN)Value + (UINTN)Adjustment

//
// Define macros to create data structure signatures.
//

#define EFI_SIGNATURE_16(A,B)             ((A) | (B<<8))
#define EFI_SIGNATURE_32(A,B,C,D)         (EFI_SIGNATURE_16(A,B)     | (EFI_SIGNATURE_16(C,D)     << 16))
#define EFI_SIGNATURE_64(A,B,C,D,E,F,G,H) (EFI_SIGNATURE_32(A,B,C,D) | ((UINT64)(EFI_SIGNATURE_32(E,F,G,H)) << 32))
//
// To export & import functions in the EFI emulator environment
//

    #define EXPORTAPI

//
// EFIAPI - prototype calling convention for EFI function pointers
// BOOTSERVICE - prototype for implementation of a boot service interface
// RUNTIMESERVICE - prototype for implementation of a runtime service interface
// RUNTIMEFUNCTION - prototype for implementation of a runtime function that is not a service
// RUNTIME_CODE - pragma macro for declaring runtime code    
//

#ifndef EFIAPI                  // Forces EFI calling conventions reguardless of compiler options 
    #ifdef _MSC_EXTENSIONS
        #define EFIAPI __cdecl  // Force C calling convention for Microsoft C compiler 
    #else
        #define EFIAPI          // Substitute expresion to force C calling convention 
    #endif
#endif

#define BOOTSERVICE
#define RUNTIMESERVICE
#define RUNTIMEFUNCTION

#define RUNTIME_CODE(a)         alloc_text("rtcode", a)
#define BEGIN_RUNTIME_DATA()    data_seg("rtdata")
#define END_RUNTIME_DATA()      data_seg("")

#define VOLATILE    volatile

//
// BugBug: Need to find out if this is portable accross compliers.
//
#ifdef __GNUC__
#define MEMORY_FENCE()    __asm__ __volatile__ ("mf.a" ::: "memory")
#else
void __mf (void);                       
#pragma intrinsic (__mf)  
#define MEMORY_FENCE()    __mf()
#endif

//
// When build similiar to FW, then link everything together as
// one big module. For the MSVC toolchain, we simply tell the
// linker what our driver init function is using /ENTRY.
//
#if defined(_MSC_EXTENSIONS)
    #define EFI_DRIVER_ENTRY_POINT(InitFunction) \
        __pragma(comment(linker, "/ENTRY:" # InitFunction))
#else
    #define EFI_DRIVER_ENTRY_POINT(InitFunction)    \
        UINTN                                       \
        InitializeDriver (                          \
            VOID    *ImageHandle,                   \
            VOID    *SystemTable                    \
            )                                       \
        {                                           \
            return InitFunction(ImageHandle,        \
                    SystemTable);                   \
        }                                           \
                                                    \
        EFI_STATUS efi_main(                        \
            EFI_HANDLE image,                       \
            EFI_SYSTEM_TABLE *systab                \
            ) __attribute__((weak,                  \
                    alias ("InitializeDriver")));
#endif

#define LOAD_INTERNAL_DRIVER(_if, type, name, entry)    \
        (_if)->LoadInternal(type, name, entry)

//
// Some compilers don't support the forward reference construct:
//  typedef struct XXXXX
//
// The following macro provide a workaround for such cases.
//
#ifdef NO_INTERFACE_DECL
#define INTERFACE_DECL(x)
#else
#if defined(__GNUC__) || defined(_MSC_EXTENSIONS)
#define INTERFACE_DECL(x) struct x
#else
#define INTERFACE_DECL(x) typedef struct x
#endif
#endif

/* No efi call wrapper for IA32 architecture */
#define uefi_call_wrapper(func, va_num, ...)	func(__VA_ARGS__)
#define EFI_FUNCTION
#elif defined (_M_ARM64) || defined(__aarch64__)
/*
 * Copright (C) 2014 - 2015 Linaro Ltd.
 * Author: Ard Biesheuvel <ard.biesheuvel@linaro.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice and this list of conditions, without modification.
 * 2. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License as published by the Free Software Foundation;
 * either version 2 of the License, or (at your option) any later version.
 */

#if !defined(_MSC_VER) && (!defined(__STDC_VERSION__) || (__STDC_VERSION__ < 199901L )) && !defined(__cplusplus)

// ANSI C 1999/2000 stdint.h integer width declarations

typedef unsigned long       uint64_t;
typedef long                int64_t;
typedef unsigned int        uint32_t;
typedef int                 int32_t;
typedef unsigned short      uint16_t;
typedef short               int16_t;
typedef unsigned char       uint8_t;
typedef signed char         int8_t;   // unqualified 'char' is unsigned on ARM
typedef uint64_t            uintptr_t;
typedef int64_t             intptr_t;

#else
typedef signed char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef long long int64_t;

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

typedef int8_t int_least8_t;
typedef int16_t int_least16_t;
typedef int32_t int_least32_t;
typedef int64_t int_least64_t;
typedef uint8_t uint_least8_t;
typedef uint16_t uint_least16_t;
typedef uint32_t uint_least32_t;
typedef uint64_t uint_least64_t;

typedef int8_t int_fast8_t;
typedef int16_t int_fast16_t;
typedef int32_t int_fast32_t;
typedef int64_t int_fast64_t;
typedef uint8_t uint_fast8_t;
typedef uint16_t uint_fast16_t;
typedef uint32_t uint_fast32_t;
typedef uint64_t uint_fast64_t;

typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef short __int16_t;
typedef unsigned short __uint16_t;
typedef int __int32_t;
typedef unsigned int __uint32_t;
typedef long long __int64_t;
typedef unsigned long long __uint64_t;

typedef unsigned char u_int8_t;
typedef unsigned short u_int16_t;
typedef unsigned int u_int32_t;
typedef unsigned long long u_int64_t;

typedef unsigned long uintptr_t;

typedef long int intmax_t;
typedef long unsigned int uintmax_t;


#endif

//
// Basic EFI types of various widths
//

#ifndef __WCHAR_TYPE__
# define __WCHAR_TYPE__ short
#endif

typedef uint64_t   UINT64;
typedef int64_t    INT64;

typedef uint32_t   UINT32;
typedef int32_t    INT32;

typedef uint16_t   UINT16;
typedef int16_t    INT16;
typedef uint8_t    UINT8;
typedef int8_t     INT8;
typedef __WCHAR_TYPE__ WCHAR;

#undef VOID
#define VOID    void

typedef int64_t    INTN;
typedef uint64_t   UINTN;

#define EFIERR(a)           (0x8000000000000000 | a)
#define EFI_ERROR_MASK      0x8000000000000000
#define EFIERR_OEM(a)       (0xc000000000000000 | a)

#define BAD_POINTER         0xFBFBFBFBFBFBFBFB
#define MAX_ADDRESS         0xFFFFFFFFFFFFFFFF

#define BREAKPOINT()        while (TRUE);    // Make it hang on Bios[Dbg]32

//
// Pointers must be aligned to these address to function
//

#define MIN_ALIGNMENT_SIZE  8

#define ALIGN_VARIABLE(Value ,Adjustment) \
            (UINTN)Adjustment = 0; \
            if((UINTN)Value % MIN_ALIGNMENT_SIZE) \
                (UINTN)Adjustment = MIN_ALIGNMENT_SIZE - ((UINTN)Value % MIN_ALIGNMENT_SIZE); \
            Value = (UINTN)Value + (UINTN)Adjustment


//
// Define macros to build data structure signatures from characters.
//

#define EFI_SIGNATURE_16(A,B)             ((A) | (B<<8))
#define EFI_SIGNATURE_32(A,B,C,D)         (EFI_SIGNATURE_16(A,B)     | (EFI_SIGNATURE_16(C,D)     << 16))
#define EFI_SIGNATURE_64(A,B,C,D,E,F,G,H) (EFI_SIGNATURE_32(A,B,C,D) | ((UINT64)(EFI_SIGNATURE_32(E,F,G,H)) << 32))

//
// EFIAPI - prototype calling convention for EFI function pointers
// BOOTSERVICE - prototype for implementation of a boot service interface
// RUNTIMESERVICE - prototype for implementation of a runtime service interface
// RUNTIMEFUNCTION - prototype for implementation of a runtime function that is not a service
// RUNTIME_CODE - pragma macro for declaring runtime code
//

#ifndef EFIAPI          // Forces EFI calling conventions reguardless of compiler options
#define EFIAPI          // Substitute expresion to force C calling convention
#endif

#define BOOTSERVICE
#define RUNTIMESERVICE
#define RUNTIMEFUNCTION


#define RUNTIME_CODE(a)         alloc_text("rtcode", a)
#define BEGIN_RUNTIME_DATA()    data_seg("rtdata")
#define END_RUNTIME_DATA()      data_seg("")

#define VOLATILE                volatile

#define MEMORY_FENCE            __sync_synchronize

//
// When build similiar to FW, then link everything together as
// one big module. For the MSVC toolchain, we simply tell the
// linker what our driver init function is using /ENTRY.
//
#if defined(_MSC_EXTENSIONS)
#define EFI_DRIVER_ENTRY_POINT(InitFunction) \
    __pragma(comment(linker, "/ENTRY:" # InitFunction))
#else
#define EFI_DRIVER_ENTRY_POINT(InitFunction)    \
    UINTN                                       \
    InitializeDriver (                          \
        VOID    *ImageHandle,                   \
        VOID    *SystemTable                    \
        )                                       \
    {                                           \
        return InitFunction(ImageHandle,        \
                SystemTable);                   \
    }                                           \
                                                \
    EFI_STATUS efi_main(                        \
        EFI_HANDLE image,                       \
        EFI_SYSTEM_TABLE *systab                \
        ) __attribute__((weak,                  \
                alias ("InitializeDriver")));
#endif

#define LOAD_INTERNAL_DRIVER(_if, type, name, entry)    \
        (_if)->LoadInternal(type, name, entry)


//
// Some compilers don't support the forward reference construct:
//  typedef struct XXXXX
//
// The following macro provide a workaround for such cases.

#define INTERFACE_DECL(x) struct x

#define uefi_call_wrapper(func, va_num, ...) func(__VA_ARGS__)
#define EFI_FUNCTION
#elif defined (_M_ARM) || defined(__arm__)
/*
 * Copright (C) 2014 - 2015 Linaro Ltd.
 * Author: Ard Biesheuvel <ard.biesheuvel@linaro.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice and this list of conditions, without modification.
 * 2. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License as published by the Free Software Foundation;
 * either version 2 of the License, or (at your option) any later version.
 */

#if !defined(_MSC_VER) && (!defined(__STDC_VERSION__) || (__STDC_VERSION__ < 199901L )) && !defined(__cplusplus)

// ANSI C 1999/2000 stdint.h integer width declarations

typedef unsigned long long  uint64_t;
typedef long long           int64_t;
typedef unsigned int        uint32_t;
typedef int                 int32_t;
typedef unsigned short      uint16_t;
typedef short               int16_t;
typedef unsigned char       uint8_t;
typedef signed char         int8_t;   // unqualified 'char' is unsigned on ARM
typedef uint32_t            uintptr_t;
typedef int32_t             intptr_t;

#else
typedef signed char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef long long int64_t;

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

typedef int8_t int_least8_t;
typedef int16_t int_least16_t;
typedef int32_t int_least32_t;
typedef int64_t int_least64_t;
typedef uint8_t uint_least8_t;
typedef uint16_t uint_least16_t;
typedef uint32_t uint_least32_t;
typedef uint64_t uint_least64_t;

typedef int8_t int_fast8_t;
typedef int16_t int_fast16_t;
typedef int32_t int_fast32_t;
typedef int64_t int_fast64_t;
typedef uint8_t uint_fast8_t;
typedef uint16_t uint_fast16_t;
typedef uint32_t uint_fast32_t;
typedef uint64_t uint_fast64_t;

typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef short __int16_t;
typedef unsigned short __uint16_t;
typedef int __int32_t;
typedef unsigned int __uint32_t;
typedef long long __int64_t;
typedef unsigned long long __uint64_t;

typedef unsigned char u_int8_t;
typedef unsigned short u_int16_t;
typedef unsigned int u_int32_t;
typedef unsigned long long u_int64_t;

typedef unsigned long uintptr_t;

typedef long int intmax_t;
typedef long unsigned int uintmax_t;


#endif

/*
 * This prevents GCC from emitting GOT based relocations, and use R_ARM_REL32
 * relative relocations instead, which are more suitable for static binaries.
 */
#if defined(__GNUC__) && !__STDC_HOSTED__
#pragma GCC visibility push (hidden)
#endif

//
// Basic EFI types of various widths
//

#ifndef __WCHAR_TYPE__
# define __WCHAR_TYPE__ short
#endif

typedef uint64_t   UINT64;
typedef int64_t    INT64;

typedef uint32_t   UINT32;
typedef int32_t    INT32;

typedef uint16_t   UINT16;
typedef int16_t    INT16;
typedef uint8_t    UINT8;
typedef int8_t     INT8;
typedef __WCHAR_TYPE__ WCHAR;

#undef VOID
#define VOID    void

typedef int32_t    INTN;
typedef uint32_t   UINTN;

#define EFIERR(a)           (0x80000000 | a)
#define EFI_ERROR_MASK      0x80000000
#define EFIERR_OEM(a)       (0xc0000000 | a)

#define BAD_POINTER         0xFBFBFBFB
#define MAX_ADDRESS         0xFFFFFFFF

#define BREAKPOINT()        while (TRUE);

//
// Pointers must be aligned to these address to function
//

#define MIN_ALIGNMENT_SIZE  4

#define ALIGN_VARIABLE(Value ,Adjustment) \
            (UINTN)Adjustment = 0; \
            if((UINTN)Value % MIN_ALIGNMENT_SIZE) \
                (UINTN)Adjustment = MIN_ALIGNMENT_SIZE - ((UINTN)Value % MIN_ALIGNMENT_SIZE); \
            Value = (UINTN)Value + (UINTN)Adjustment


//
// Define macros to build data structure signatures from characters.
//

#define EFI_SIGNATURE_16(A,B)             ((A) | (B<<8))
#define EFI_SIGNATURE_32(A,B,C,D)         (EFI_SIGNATURE_16(A,B)     | (EFI_SIGNATURE_16(C,D)     << 16))
#define EFI_SIGNATURE_64(A,B,C,D,E,F,G,H) (EFI_SIGNATURE_32(A,B,C,D) | ((UINT64)(EFI_SIGNATURE_32(E,F,G,H)) << 32))

//
// EFIAPI - prototype calling convention for EFI function pointers
// BOOTSERVICE - prototype for implementation of a boot service interface
// RUNTIMESERVICE - prototype for implementation of a runtime service interface
// RUNTIMEFUNCTION - prototype for implementation of a runtime function that is not a service
// RUNTIME_CODE - pragma macro for declaring runtime code
//

#ifndef EFIAPI          // Forces EFI calling conventions reguardless of compiler options
#define EFIAPI          // Substitute expresion to force C calling convention
#endif

#define BOOTSERVICE
#define RUNTIMESERVICE
#define RUNTIMEFUNCTION


#define RUNTIME_CODE(a)         alloc_text("rtcode", a)
#define BEGIN_RUNTIME_DATA()    data_seg("rtdata")
#define END_RUNTIME_DATA()      data_seg("")

#define VOLATILE                volatile

#define MEMORY_FENCE            __sync_synchronize

//
// When build similiar to FW, then link everything together as
// one big module. For the MSVC toolchain, we simply tell the
// linker what our driver init function is using /ENTRY.
//
#if defined(_MSC_EXTENSIONS)
#define EFI_DRIVER_ENTRY_POINT(InitFunction) \
    __pragma(comment(linker, "/ENTRY:" # InitFunction))
#else
#define EFI_DRIVER_ENTRY_POINT(InitFunction)    \
    UINTN                                       \
    InitializeDriver (                          \
        VOID    *ImageHandle,                   \
        VOID    *SystemTable                    \
        )                                       \
    {                                           \
        return InitFunction(ImageHandle,        \
                SystemTable);                   \
    }                                           \
                                                \
    EFI_STATUS efi_main(                        \
        EFI_HANDLE image,                       \
        EFI_SYSTEM_TABLE *systab                \
        ) __attribute__((weak,                  \
                alias ("InitializeDriver")));
#endif

#define LOAD_INTERNAL_DRIVER(_if, type, name, entry)    \
        (_if)->LoadInternal(type, name, entry)


//
// Some compilers don't support the forward reference construct:
//  typedef struct XXXXX
//
// The following macro provide a workaround for such cases.

#define INTERFACE_DECL(x) struct x

#define uefi_call_wrapper(func, va_num, ...) func(__VA_ARGS__)
#define EFI_FUNCTION
#elif defined (_M_MIPS64) || defined(__mips64__) || defined(__mips64)
/*
 * Copright (C) 2014 - 2015 Linaro Ltd.
 * Author: Ard Biesheuvel <ard.biesheuvel@linaro.org>
 * Copright (C) 2017 Lemote Co.
 * Author: Heiher <r@hev.cc>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice and this list of conditions, without modification.
 * 2. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License as published by the Free Software Foundation;
 * either version 2 of the License, or (at your option) any later version.
 */

#if !defined(__STDC_VERSION__) || (__STDC_VERSION__ < 199901L ) && !defined(__cplusplus)

// ANSI C 1999/2000 stdint.h integer width declarations

typedef unsigned long       uint64_t;
typedef long                int64_t;
typedef unsigned int        uint32_t;
typedef int                 int32_t;
typedef unsigned short      uint16_t;
typedef short               int16_t;
typedef unsigned char       uint8_t;
typedef signed char         int8_t;   // unqualified 'char' is unsigned on ARM
typedef uint64_t            uintptr_t;
typedef int64_t             intptr_t;

#else
typedef signed char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef long long int64_t;

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

typedef int8_t int_least8_t;
typedef int16_t int_least16_t;
typedef int32_t int_least32_t;
typedef int64_t int_least64_t;
typedef uint8_t uint_least8_t;
typedef uint16_t uint_least16_t;
typedef uint32_t uint_least32_t;
typedef uint64_t uint_least64_t;

typedef int8_t int_fast8_t;
typedef int16_t int_fast16_t;
typedef int32_t int_fast32_t;
typedef int64_t int_fast64_t;
typedef uint8_t uint_fast8_t;
typedef uint16_t uint_fast16_t;
typedef uint32_t uint_fast32_t;
typedef uint64_t uint_fast64_t;

typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef short __int16_t;
typedef unsigned short __uint16_t;
typedef int __int32_t;
typedef unsigned int __uint32_t;
typedef long long __int64_t;
typedef unsigned long long __uint64_t;

typedef unsigned char u_int8_t;
typedef unsigned short u_int16_t;
typedef unsigned int u_int32_t;
typedef unsigned long long u_int64_t;

typedef unsigned long uintptr_t;

typedef long int intmax_t;
typedef long unsigned int uintmax_t;


#endif

//
// Basic EFI types of various widths
//

#ifndef __WCHAR_TYPE__
# define __WCHAR_TYPE__ short
#endif

typedef uint64_t   UINT64;
typedef int64_t    INT64;

typedef uint32_t   UINT32;
typedef int32_t    INT32;

typedef uint16_t   UINT16;
typedef int16_t    INT16;
typedef uint8_t    UINT8;
typedef int8_t     INT8;
typedef __WCHAR_TYPE__ WCHAR;

#undef VOID
#define VOID    void

typedef int64_t    INTN;
typedef uint64_t   UINTN;

#define EFIERR(a)           (0x8000000000000000 | a)
#define EFI_ERROR_MASK      0x8000000000000000
#define EFIERR_OEM(a)       (0xc000000000000000 | a)

#define BAD_POINTER         0xFBFBFBFBFBFBFBFB
#define MAX_ADDRESS         0xFFFFFFFFFFFFFFFF

#define BREAKPOINT()        while (TRUE);    // Make it hang on Bios[Dbg]32

//
// Pointers must be aligned to these address to function
//

#define MIN_ALIGNMENT_SIZE  8

#define ALIGN_VARIABLE(Value ,Adjustment) \
            (UINTN)Adjustment = 0; \
            if((UINTN)Value % MIN_ALIGNMENT_SIZE) \
                (UINTN)Adjustment = MIN_ALIGNMENT_SIZE - ((UINTN)Value % MIN_ALIGNMENT_SIZE); \
            Value = (UINTN)Value + (UINTN)Adjustment


//
// Define macros to build data structure signatures from characters.
//

#define EFI_SIGNATURE_16(A,B)             ((A) | (B<<8))
#define EFI_SIGNATURE_32(A,B,C,D)         (EFI_SIGNATURE_16(A,B)     | (EFI_SIGNATURE_16(C,D)     << 16))
#define EFI_SIGNATURE_64(A,B,C,D,E,F,G,H) (EFI_SIGNATURE_32(A,B,C,D) | ((UINT64)(EFI_SIGNATURE_32(E,F,G,H)) << 32))

//
// EFIAPI - prototype calling convention for EFI function pointers
// BOOTSERVICE - prototype for implementation of a boot service interface
// RUNTIMESERVICE - prototype for implementation of a runtime service interface
// RUNTIMEFUNCTION - prototype for implementation of a runtime function that is not a service
// RUNTIME_CODE - pragma macro for declaring runtime code
//

#ifndef EFIAPI          // Forces EFI calling conventions reguardless of compiler options
#define EFIAPI          // Substitute expresion to force C calling convention
#endif

#define BOOTSERVICE
#define RUNTIMESERVICE
#define RUNTIMEFUNCTION


#define RUNTIME_CODE(a)         alloc_text("rtcode", a)
#define BEGIN_RUNTIME_DATA()    data_seg("rtdata")
#define END_RUNTIME_DATA()      data_seg("")

#define VOLATILE                volatile

#define MEMORY_FENCE            __sync_synchronize

//
// When build similiar to FW, then link everything together as
// one big module.
//

#define EFI_DRIVER_ENTRY_POINT(InitFunction)    \
    UINTN                                       \
    InitializeDriver (                          \
        VOID    *ImageHandle,                   \
        VOID    *SystemTable                    \
        )                                       \
    {                                           \
        return InitFunction(ImageHandle,        \
                SystemTable);                   \
    }                                           \
                                                \
    EFI_STATUS efi_main(                        \
        EFI_HANDLE image,                       \
        EFI_SYSTEM_TABLE *systab                \
        ) __attribute__((weak,                  \
                alias ("InitializeDriver")));

#define LOAD_INTERNAL_DRIVER(_if, type, name, entry)    \
        (_if)->LoadInternal(type, name, entry)


//
// Some compilers don't support the forward reference construct:
//  typedef struct XXXXX
//
// The following macro provide a workaround for such cases.

#define INTERFACE_DECL(x) struct x

#define uefi_call_wrapper(func, va_num, ...) func(__VA_ARGS__)
#define EFI_FUNCTION

static inline UINT64 swap_uint64 (UINT64 v)
{
	asm volatile (
		"dsbh	%[v], %[v] \n\t"
		"dshd	%[v], %[v] \n\t"
		:[v]"+r"(v)
	);

	return v;
}
#elif defined (__riscv) && __riscv_xlen == 64
/*
 * Copright (C) 2014 - 2015 Linaro Ltd.
 * Author: Ard Biesheuvel <ard.biesheuvel@linaro.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice and this list of conditions, without modification.
 * 2. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License as published by the Free Software Foundation;
 * either version 2 of the License, or (at your option) any later version.
 */

typedef signed char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef long long int64_t;

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

typedef int8_t int_least8_t;
typedef int16_t int_least16_t;
typedef int32_t int_least32_t;
typedef int64_t int_least64_t;
typedef uint8_t uint_least8_t;
typedef uint16_t uint_least16_t;
typedef uint32_t uint_least32_t;
typedef uint64_t uint_least64_t;

typedef int8_t int_fast8_t;
typedef int16_t int_fast16_t;
typedef int32_t int_fast32_t;
typedef int64_t int_fast64_t;
typedef uint8_t uint_fast8_t;
typedef uint16_t uint_fast16_t;
typedef uint32_t uint_fast32_t;
typedef uint64_t uint_fast64_t;

typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef short __int16_t;
typedef unsigned short __uint16_t;
typedef int __int32_t;
typedef unsigned int __uint32_t;
typedef long long __int64_t;
typedef unsigned long long __uint64_t;

typedef unsigned char u_int8_t;
typedef unsigned short u_int16_t;
typedef unsigned int u_int32_t;
typedef unsigned long long u_int64_t;

typedef unsigned long uintptr_t;

typedef long int intmax_t;
typedef long unsigned int uintmax_t;



//
// Basic EFI types of various widths
//



typedef uint64_t                UINT64;
typedef int64_t                 INT64;
typedef uint32_t                UINT32;
typedef int32_t                 INT32;
typedef uint16_t                UINT16;
typedef int16_t                 INT16;
typedef uint8_t                 UINT8;
typedef int8_t                  INT8;
#ifndef __WCHAR_TYPE__
#define __WCHAR_TYPE__          short
#endif
typedef __WCHAR_TYPE__          WCHAR;
#ifndef BOOLEAN
typedef uint8_t                 BOOLEAN;
#endif
#undef VOID
#define VOID                    void
typedef int64_t                 INTN;
typedef uint64_t                UINTN;

#define EFI_ERROR_MASK          0x8000000000000000
#define EFIERR(a)               (EFI_ERROR_MASK | a)
#define EFIERR_OEM(a)           (0xc000000000000000 | a)

#define BAD_POINTER             0xFBFBFBFBFBFBFBFB
#define MAX_ADDRESS             0xFFFFFFFFFFFFFFFF

#define BREAKPOINT()            while(1);

//
// Pointers must be aligned to these address to function
//
#define MIN_ALIGNMENT_SIZE      8

#define ALIGN_VARIABLE(Value, Adjustment) \
   (UINTN)Adjustment = 0; \
   if((UINTN)Value % MIN_ALIGNMENT_SIZE) \
       (UINTN)Adjustment = MIN_ALIGNMENT_SIZE - ((UINTN)Value % MIN_ALIGNMENT_SIZE); \
   Value = (UINTN)Value + (UINTN)Adjustment

//
// Define macros to build data structure signatures from characters.
//
#define EFI_SIGNATURE_16(A,B)             ((A) | (B<<8))
#define EFI_SIGNATURE_32(A,B,C,D)         (EFI_SIGNATURE_16(A,B)     | (EFI_SIGNATURE_16(C,D)     << 16))
#define EFI_SIGNATURE_64(A,B,C,D,E,F,G,H) (EFI_SIGNATURE_32(A,B,C,D) | ((UINT64)(EFI_SIGNATURE_32(E,F,G,H)) << 32))

//
// EFIAPI - prototype calling convention for EFI function pointers
// BOOTSERVICE - prototype for implementation of a boot service interface
// RUNTIMESERVICE - prototype for implementation of a runtime service interface
// RUNTIMEFUNCTION - prototype for implementation of a runtime function that is not a service
// RUNTIME_CODE - pragma macro for declaring runtime code
//
#ifndef EFIAPI                  // Forces EFI calling conventions reguardless of compiler options
#define EFIAPI                  // Substitute expresion to force C calling convention
#endif
#define BOOTSERVICE
#define RUNTIMESERVICE
#define RUNTIMEFUNCTION
#define RUNTIME_CODE(a)         alloc_text("rtcode", a)
#define BEGIN_RUNTIME_DATA()    data_seg("rtdata")
#define END_RUNTIME_DATA()      data_seg("")

#define VOLATILE                volatile
#define MEMORY_FENCE            __sync_synchronize

//
// When build similiar to FW, then link everything together as
// one big module. For the MSVC toolchain, we simply tell the
// linker what our driver init function is using /ENTRY.
//
#if defined(_MSC_EXTENSIONS)
#define EFI_DRIVER_ENTRY_POINT(InitFunction) \
    __pragma(comment(linker, "/ENTRY:" # InitFunction))
#else
#define EFI_DRIVER_ENTRY_POINT(InitFunction)    \
    UINTN                                       \
    InitializeDriver (                          \
        VOID    *ImageHandle,                   \
        VOID    *SystemTable                    \
        )                                       \
    {                                           \
        return InitFunction(ImageHandle,        \
                SystemTable);                   \
    }                                           \
                                                \
    EFI_STATUS efi_main(                        \
        EFI_HANDLE image,                       \
        EFI_SYSTEM_TABLE *systab                \
        ) __attribute__((weak,                  \
                alias ("InitializeDriver")));
#endif

#define LOAD_INTERNAL_DRIVER(_if, type, name, entry) \
   (_if)->LoadInternal(type, name, entry)

//
// Some compilers don't support the forward reference construct:
//  typedef struct XXXXX
//
// The following macro provide a workaround for such cases.
#define INTERFACE_DECL(x)       struct x

#define uefi_call_wrapper(func, va_num, ...) func(__VA_ARGS__)
#define EFI_FUNCTION
#else
#error Usupported architecture
#endif

/*++

Copyright (c) 2016 Pete Batard <pete@akeo.ie>

Module Name:

    eficompiler.h

Abstract:

    Compiler specific adjustments

--*/

#ifdef _MSC_EXTENSIONS
#define EFI_UNUSED
#else
#define EFI_UNUSED __attribute__((__unused__))
#endif

#ifdef _MSC_EXTENSIONS
#define ALIGN(x) __declspec(align(x))
#else
#define ALIGN(x) __attribute__((__aligned__(x)))
#endif

/* Also add a catch-all on __attribute__() for MS compilers */
#ifdef _MSC_EXTENSIONS
#define __attribute__(x)
#endif
#ifndef _EFI_DEF_H
#define _EFI_DEF_H

/*++

Copyright (c) 1998  Intel Corporation

Module Name:

    efidef.h

Abstract:

    EFI definitions




Revision History

--*/

typedef UINT16          CHAR16;
typedef UINT8           CHAR8;
typedef UINT8           BOOLEAN;
#ifndef CONST
   #define CONST const
#endif
#ifndef TRUE
    #define TRUE    ((BOOLEAN) 1)
    #define FALSE   ((BOOLEAN) 0)
#endif

#ifndef NULL
    #define NULL    ((VOID *) 0)
#endif

typedef UINTN           EFI_STATUS;
typedef UINT64          EFI_LBA;
typedef UINTN           EFI_TPL;
typedef VOID            *EFI_HANDLE;
typedef VOID            *EFI_EVENT;


//
// Prototype argument decoration for EFI parameters to indicate
// their direction
//
// IN - argument is passed into the function
// OUT - argument (pointer) is returned from the function
// OPTIONAL - argument is optional
//

#ifndef IN
    #define IN
    #define OUT
    #define OPTIONAL
#endif


//
// A GUID
//

typedef struct {          
    UINT32  Data1;
    UINT16  Data2;
    UINT16  Data3;
    UINT8   Data4[8]; 
} EFI_GUID;


//
// Time
//

typedef struct {          
    UINT16      Year;       // 1998 - 20XX
    UINT8       Month;      // 1 - 12
    UINT8       Day;        // 1 - 31
    UINT8       Hour;       // 0 - 23
    UINT8       Minute;     // 0 - 59
    UINT8       Second;     // 0 - 59
    UINT8       Pad1;
    UINT32      Nanosecond; // 0 - 999,999,999
    INT16       TimeZone;   // -1440 to 1440 or 2047
    UINT8       Daylight;
    UINT8       Pad2;
} EFI_TIME;

// Bit definitions for EFI_TIME.Daylight
#define EFI_TIME_ADJUST_DAYLIGHT    0x01
#define EFI_TIME_IN_DAYLIGHT        0x02

// Value definition for EFI_TIME.TimeZone
#define EFI_UNSPECIFIED_TIMEZONE    0x07FF



//
// Networking
//

typedef struct {
    UINT8                   Addr[4];
} EFI_IPv4_ADDRESS;

typedef struct {
    UINT8                   Addr[16];
} EFI_IPv6_ADDRESS;

typedef struct {
    UINT8                   Addr[32];
} EFI_MAC_ADDRESS;

typedef struct {
    UINT32 ReceivedQueueTimeoutValue;
    UINT32 TransmitQueueTimeoutValue;
    UINT16 ProtocolTypeFilter;
    BOOLEAN EnableUnicastReceive;
    BOOLEAN EnableMulticastReceive;
    BOOLEAN EnableBroadcastReceive;
    BOOLEAN EnablePromiscuousReceive;
    BOOLEAN FlushQueuesOnReset;
    BOOLEAN EnableReceiveTimestamps;
    BOOLEAN DisableBackgroundPolling;
} EFI_MANAGED_NETWORK_CONFIG_DATA;

//
// Memory
//

typedef UINT64          EFI_PHYSICAL_ADDRESS;
typedef UINT64          EFI_VIRTUAL_ADDRESS;

typedef enum {
    AllocateAnyPages,
    AllocateMaxAddress,
    AllocateAddress,
    MaxAllocateType
} EFI_ALLOCATE_TYPE;

//Preseve the attr on any range supplied.
//ConventialMemory must have WB,SR,SW when supplied.
//When allocating from ConventialMemory always make it WB,SR,SW
//When returning to ConventialMemory always make it WB,SR,SW
//When getting the memory map, or on RT for runtime types


typedef enum {
    EfiReservedMemoryType,
    EfiLoaderCode,
    EfiLoaderData,
    EfiBootServicesCode,
    EfiBootServicesData,
    EfiRuntimeServicesCode,
    EfiRuntimeServicesData,
    EfiConventionalMemory,
    EfiUnusableMemory,
    EfiACPIReclaimMemory,
    EfiACPIMemoryNVS,
    EfiMemoryMappedIO,
    EfiMemoryMappedIOPortSpace,
    EfiPalCode,
    EfiMaxMemoryType
} EFI_MEMORY_TYPE;

// possible caching types for the memory range
#define EFI_MEMORY_UC           0x0000000000000001
#define EFI_MEMORY_WC           0x0000000000000002
#define EFI_MEMORY_WT           0x0000000000000004
#define EFI_MEMORY_WB           0x0000000000000008
#define EFI_MEMORY_UCE          0x0000000000000010  

// physical memory protection on range 
#define EFI_MEMORY_WP           0x0000000000001000
#define EFI_MEMORY_RP           0x0000000000002000
#define EFI_MEMORY_XP           0x0000000000004000

// range requires a runtime mapping
#define EFI_MEMORY_RUNTIME      0x8000000000000000

#define EFI_MEMORY_DESCRIPTOR_VERSION  1
typedef struct {
    UINT32                          Type;           // Field size is 32 bits followed by 32 bit pad
    UINT32                          Pad;
    EFI_PHYSICAL_ADDRESS            PhysicalStart;  // Field size is 64 bits
    EFI_VIRTUAL_ADDRESS             VirtualStart;   // Field size is 64 bits
    UINT64                          NumberOfPages;  // Field size is 64 bits
    UINT64                          Attribute;      // Field size is 64 bits
} EFI_MEMORY_DESCRIPTOR;

//
// International Language
//

typedef UINT8   ISO_639_2;
#define ISO_639_2_ENTRY_SIZE    3

//
//
//

#define EFI_PAGE_SIZE   4096
#define EFI_PAGE_MASK   0xFFF
#define EFI_PAGE_SHIFT  12

#define EFI_SIZE_TO_PAGES(a)  \
    ( ((a) >> EFI_PAGE_SHIFT) + ((a) & EFI_PAGE_MASK ? 1 : 0) )

#define EFI_OS_INDICATIONS_BOOT_TO_FW_UI        0x0000000000000001
#define EFI_OS_INDICATIONS_TIMESTAMP_REVOCATION 0x0000000000000002
#define EFI_OS_INDICATIONS_FILE_CAPSULE_DELIVERY_SUPPORTED \
                                                0x0000000000000004
#define EFI_OS_INDICATIONS_FMP_CAPSULE_SUPPORTED \
                                                0x0000000000000008
#define EFI_OS_INDICATIONS_CAPSULE_RESULT_VAR_SUPPORTED \
                                                0x0000000000000010

#endif
#ifndef _DEVPATH_H
#define _DEVPATH_H

/*++

Copyright (c) 1998  Intel Corporation

Module Name:

    devpath.h

Abstract:

    Defines for parsing the EFI Device Path structures



Revision History

--*/

//
// Device Path structures - Section C
//

typedef struct _EFI_DEVICE_PATH_PROTOCOL {
        UINT8                           Type;
        UINT8                           SubType;
        UINT8                           Length[2];
} EFI_DEVICE_PATH_PROTOCOL;

typedef struct _EFI_DEVICE_PATH_PROTOCOL _EFI_DEVICE_PATH;
typedef EFI_DEVICE_PATH_PROTOCOL EFI_DEVICE_PATH;

#define EFI_DP_TYPE_MASK                    0x7F
#define EFI_DP_TYPE_UNPACKED                0x80

//#define END_DEVICE_PATH_TYPE                0xff
#define END_DEVICE_PATH_TYPE                0x7f
//#define END_DEVICE_PATH_TYPE_UNPACKED       0x7f

#define END_ENTIRE_DEVICE_PATH_SUBTYPE      0xff
#define END_INSTANCE_DEVICE_PATH_SUBTYPE    0x01
#define END_DEVICE_PATH_LENGTH              (sizeof(EFI_DEVICE_PATH_PROTOCOL))


#define DP_IS_END_TYPE(a)
#define DP_IS_END_SUBTYPE(a)        ( ((a)->SubType == END_ENTIRE_DEVICE_PATH_SUBTYPE )

#define DevicePathType(a)           ( ((a)->Type) & EFI_DP_TYPE_MASK )
#define DevicePathSubType(a)        ( (a)->SubType )
#define DevicePathNodeLength(a)     ( ((a)->Length[0]) | ((a)->Length[1] << 8) )
#define NextDevicePathNode(a)       ( (EFI_DEVICE_PATH_PROTOCOL *) ( ((UINT8 *) (a)) + DevicePathNodeLength(a)))
//#define IsDevicePathEndType(a)      ( DevicePathType(a) == END_DEVICE_PATH_TYPE_UNPACKED )
#define IsDevicePathEndType(a)      ( DevicePathType(a) == END_DEVICE_PATH_TYPE )
#define IsDevicePathEndSubType(a)   ( (a)->SubType == END_ENTIRE_DEVICE_PATH_SUBTYPE )
#define IsDevicePathEnd(a)          ( IsDevicePathEndType(a) && IsDevicePathEndSubType(a) )
#define IsDevicePathUnpacked(a)     ( (a)->Type & EFI_DP_TYPE_UNPACKED )


#define SetDevicePathNodeLength(a,l) {                  \
            (a)->Length[0] = (UINT8) (l);               \
            (a)->Length[1] = (UINT8) ((l) >> 8);        \
            }

#define SetDevicePathEndNode(a)  {                      \
            (a)->Type = END_DEVICE_PATH_TYPE;           \
            (a)->SubType = END_ENTIRE_DEVICE_PATH_SUBTYPE;     \
            (a)->Length[0] = sizeof(EFI_DEVICE_PATH_PROTOCOL); \
            (a)->Length[1] = 0;                         \
            }


/*
 * Hardware Device Path (UEFI 2.4 specification, version 2.4 § 9.3.2.)
 */

#define HARDWARE_DEVICE_PATH            0x01

#define HW_PCI_DP                       0x01
typedef struct _PCI_DEVICE_PATH {
        EFI_DEVICE_PATH_PROTOCOL        Header;
        UINT8                           Function;
        UINT8                           Device;
} PCI_DEVICE_PATH;

#define HW_PCCARD_DP                    0x02
typedef struct _PCCARD_DEVICE_PATH {
        EFI_DEVICE_PATH_PROTOCOL        Header;
        UINT8                           FunctionNumber ;
} PCCARD_DEVICE_PATH;

#define HW_MEMMAP_DP                    0x03
typedef struct _MEMMAP_DEVICE_PATH {
        EFI_DEVICE_PATH_PROTOCOL        Header;
        UINT32                          MemoryType;
        EFI_PHYSICAL_ADDRESS            StartingAddress;
        EFI_PHYSICAL_ADDRESS            EndingAddress;
} MEMMAP_DEVICE_PATH;

#define HW_VENDOR_DP                    0x04
typedef struct _VENDOR_DEVICE_PATH {
        EFI_DEVICE_PATH_PROTOCOL        Header;
        EFI_GUID                        Guid;
} VENDOR_DEVICE_PATH;

#define UNKNOWN_DEVICE_GUID \
    { 0xcf31fac5, 0xc24e, 0x11d2,  {0x85, 0xf3, 0x0, 0xa0, 0xc9, 0x3e, 0xc9, 0x3b}  }

typedef struct _UKNOWN_DEVICE_VENDOR_DP {
    VENDOR_DEVICE_PATH      DevicePath;
    UINT8                   LegacyDriveLetter;
} UNKNOWN_DEVICE_VENDOR_DEVICE_PATH;

#define HW_CONTROLLER_DP            0x05
typedef struct _CONTROLLER_DEVICE_PATH {
        EFI_DEVICE_PATH_PROTOCOL  Header;
        UINT32                    Controller;
} CONTROLLER_DEVICE_PATH;


/*
 * ACPI Device Path (UEFI 2.4 specification, version 2.4 § 9.3.3 and 9.3.4.)
 */
#define ACPI_DEVICE_PATH                0x02

#define ACPI_DP                         0x01
typedef struct _ACPI_HID_DEVICE_PATH {
        EFI_DEVICE_PATH_PROTOCOL        Header;
        UINT32                          HID;
        UINT32                          UID;
} ACPI_HID_DEVICE_PATH;

#define EXPANDED_ACPI_DP                0x02
typedef struct _EXPANDED_ACPI_HID_DEVICE_PATH {
        EFI_DEVICE_PATH_PROTOCOL        Header;
        UINT32                          HID;
        UINT32                          UID;
        UINT32                          CID;
        UINT8                           HidStr[1];
} EXPANDED_ACPI_HID_DEVICE_PATH;

#define ACPI_ADR_DP 3
typedef struct _ACPI_ADR_DEVICE_PATH {
    EFI_DEVICE_PATH_PROTOCOL Header ;
    UINT32 ADR ;
} ACPI_ADR_DEVICE_PATH ;

//
// EISA ID Macro
// EISA ID Definition 32-bits
//  bits[15:0] - three character compressed ASCII EISA ID.
//  bits[31:16] - binary number
//   Compressed ASCII is 5 bits per character 0b00001 = 'A' 0b11010 = 'Z'
//
#define PNP_EISA_ID_CONST       0x41d0
#define EISA_ID(_Name, _Num)    ((UINT32) ((_Name) | (_Num) << 16))
#define EISA_PNP_ID(_PNPId)     (EISA_ID(PNP_EISA_ID_CONST, (_PNPId)))

#define PNP_EISA_ID_MASK        0xffff
#define EISA_ID_TO_NUM(_Id)     ((_Id) >> 16)


/*
 * Messaging Device Path (UEFI 2.4 specification, version 2.4 § 9.3.5.)
 */
#define MESSAGING_DEVICE_PATH           0x03

#define MSG_ATAPI_DP                    0x01
typedef struct _ATAPI_DEVICE_PATH {
        EFI_DEVICE_PATH_PROTOCOL        Header;
        UINT8                           PrimarySecondary;
        UINT8                           SlaveMaster;
        UINT16                          Lun;
} ATAPI_DEVICE_PATH;

#define MSG_SCSI_DP                     0x02
typedef struct _SCSI_DEVICE_PATH {
        EFI_DEVICE_PATH_PROTOCOL        Header;
        UINT16                          Pun;
        UINT16                          Lun;
} SCSI_DEVICE_PATH;

#define MSG_FIBRECHANNEL_DP             0x03
typedef struct _FIBRECHANNEL_DEVICE_PATH {
        EFI_DEVICE_PATH_PROTOCOL        Header;
        UINT32                          Reserved;
        UINT64                          WWN;
        UINT64                          Lun;
} FIBRECHANNEL_DEVICE_PATH;

/**
 * Fibre Channel Ex SubType.
 * UEFI 2.0 specification version 2.4 § 9.3.5.6.
 */
#define MSG_FIBRECHANNELEX_DP 21
typedef struct _FIBRECHANNELEX_DEVICE_PATH {
    EFI_DEVICE_PATH_PROTOCOL Header ;
    UINT32 Reserved ;
    UINT8 WWN[ 8 ] ; /* World Wide Name */
    UINT8 Lun[ 8 ] ; /* Logical unit, T-10 SCSI Architecture Model 4 specification */
} FIBRECHANNELEX_DEVICE_PATH ;

#define MSG_1394_DP                     0x04
typedef struct _F1394_DEVICE_PATH {
        EFI_DEVICE_PATH_PROTOCOL        Header;
        UINT32                          Reserved;
        UINT64                          Guid;
} F1394_DEVICE_PATH;

#define MSG_USB_DP                      0x05
typedef struct _USB_DEVICE_PATH {
        EFI_DEVICE_PATH_PROTOCOL        Header;
        UINT8                           Port;
        UINT8                           Endpoint;
} USB_DEVICE_PATH;

/**
 * SATA Device Path SubType.
 * UEFI 2.0 specification version 2.4 § 9.3.5.6.
 */
#define MSG_SATA_DP 18
typedef struct _SATA_DEVICE_PATH {
    EFI_DEVICE_PATH_PROTOCOL Header ;
    UINT16 HBAPortNumber ;
    UINT16 PortMultiplierPortNumber ;
    UINT16 Lun ; /* Logical Unit Number */
} SATA_DEVICE_PATH ;

/**
 * USB WWID Device Path SubType.
 * UEFI 2.0 specification version 2.4 § 9.3.5.7.
 */
#define MSG_USB_WWID_DP 16
typedef struct _USB_WWID_DEVICE_PATH {
    EFI_DEVICE_PATH_PROTOCOL Header ;
    UINT16 InterfaceNumber ;
    UINT16 VendorId ;
    UINT16 ProductId ;
    CHAR16 SerialNumber[ 1 ] ; /* UTF-16 characters of the USB serial number */
} USB_WWID_DEVICE_PATH ;

/**
 * Device Logical Unit SubType.
 * UEFI 2.0 specification version 2.4 § 9.3.5.8.
 */
#define MSG_DEVICE_LOGICAL_UNIT_DP 17
typedef struct _DEVICE_LOGICAL_UNIT_DEVICE_PATH {
    EFI_DEVICE_PATH_PROTOCOL Header ;
    UINT8 Lun ; /* Logical Unit Number */
} DEVICE_LOGICAL_UNIT_DEVICE_PATH ;

#define MSG_USB_CLASS_DP                0x0F
typedef struct _USB_CLASS_DEVICE_PATH {
        EFI_DEVICE_PATH_PROTOCOL        Header;
        UINT16                          VendorId;
        UINT16                          ProductId;
        UINT8                           DeviceClass;
        UINT8                           DeviceSubclass;
        UINT8                           DeviceProtocol;
} USB_CLASS_DEVICE_PATH;

#define MSG_I2O_DP                      0x06
typedef struct _I2O_DEVICE_PATH {
        EFI_DEVICE_PATH_PROTOCOL        Header;
        UINT32                          Tid;
} I2O_DEVICE_PATH;

#define MSG_MAC_ADDR_DP                 0x0b
typedef struct _MAC_ADDR_DEVICE_PATH {
        EFI_DEVICE_PATH_PROTOCOL        Header;
        EFI_MAC_ADDRESS                 MacAddress;
        UINT8                           IfType;
} MAC_ADDR_DEVICE_PATH;

#define MSG_IPv4_DP                     0x0c
typedef struct _IPv4_DEVICE_PATH {
        EFI_DEVICE_PATH_PROTOCOL        Header;
        EFI_IPv4_ADDRESS                LocalIpAddress;
        EFI_IPv4_ADDRESS                RemoteIpAddress;
        UINT16                          LocalPort;
        UINT16                          RemotePort;
        UINT16                          Protocol;
        BOOLEAN                         StaticIpAddress;
        /* new from UEFI version 2, code must check Length field in Header */
        EFI_IPv4_ADDRESS                GatewayIpAddress ;
        EFI_IPv4_ADDRESS                SubnetMask ;
} IPv4_DEVICE_PATH;

#define MSG_IPv6_DP                     0x0d
typedef struct _IPv6_DEVICE_PATH {
        EFI_DEVICE_PATH_PROTOCOL        Header;
        EFI_IPv6_ADDRESS                LocalIpAddress;
        EFI_IPv6_ADDRESS                RemoteIpAddress;
        UINT16                          LocalPort;
        UINT16                          RemotePort;
        UINT16                          Protocol;
        BOOLEAN                         IPAddressOrigin ;
        /* new from UEFI version 2, code must check Length field in Header */
        UINT8                           PrefixLength ;
        EFI_IPv6_ADDRESS                GatewayIpAddress ;
} IPv6_DEVICE_PATH;


/**
 * Uniform Resource Identifiers SubType.
 * UEFI 2.0 specification version 2.4C § 9.3.5.23.
 */
#define MSG_URI_DP                      24
typedef struct _URI_DEVICE_PATH {
        EFI_DEVICE_PATH_PROTOCOL        Header;
        CHAR8                           Uri[1];
} URI_DEVICE_PATH;

/**
 * Device Logical Unit SubType.
 * UEFI 2.0 specification version 2.4 § 9.3.5.8.
 */
#define MSG_VLAN_DP 20
typedef struct _VLAN_DEVICE_PATH {
    EFI_DEVICE_PATH_PROTOCOL Header ;
    UINT16 VlanId ;
} VLAN_DEVICE_PATH;

#define MSG_INFINIBAND_DP               0x09
typedef struct _INFINIBAND_DEVICE_PATH {
        EFI_DEVICE_PATH_PROTOCOL        Header;
        UINT32                          ResourceFlags;
        UINT8                           PortGid[16];
        UINT64                          ServiceId;
        UINT64                          TargetPortId;
        UINT64                          DeviceId;
} INFINIBAND_DEVICE_PATH;

#define MSG_UART_DP                     0x0e
typedef struct _UART_DEVICE_PATH {
        EFI_DEVICE_PATH_PROTOCOL        Header;
        UINT32                          Reserved;
        UINT64                          BaudRate;
        UINT8                           DataBits;
        UINT8                           Parity;
        UINT8                           StopBits;
} UART_DEVICE_PATH;

#define MSG_VENDOR_DP                   0x0A
/* Use VENDOR_DEVICE_PATH struct */

#define EFI_PC_ANSI_GUID \
    { 0xe0c14753, 0xf9be, 0x11d2, {0x9a, 0x0c, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d} }
#define DEVICE_PATH_MESSAGING_PC_ANSI EFI_PC_ANSI_GUID

#define EFI_VT_100_GUID \
    { 0xdfa66065, 0xb419, 0x11d3, {0x9a, 0x2d, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d} }
#define DEVICE_PATH_MESSAGING_VT_100 EFI_VT_100_GUID

#define EFI_VT_100_PLUS_GUID \
    { 0x7baec70b, 0x57e0, 0x4c76, {0x8e, 0x87, 0x2f, 0x9e, 0x28, 0x08, 0x83, 0x43} }
#define DEVICE_PATH_MESSAGING_VT_100_PLUS EFI_VT_100_PLUS_GUID

#define EFI_VT_UTF8_GUID \
    { 0xad15a0d6, 0x8bec, 0x4acf, {0xa0, 0x73, 0xd0, 0x1d, 0xe7, 0x7e, 0x2d, 0x88} }
#define DEVICE_PATH_MESSAGING_VT_UTF8 EFI_VT_UTF8_GUID


/*
 * Media Device Path (UEFI 2.4 specification, version 2.4 § 9.3.6.)
 */
#define MEDIA_DEVICE_PATH               0x04

#define MEDIA_HARDDRIVE_DP              0x01
typedef struct _HARDDRIVE_DEVICE_PATH {
        EFI_DEVICE_PATH_PROTOCOL        Header;
        UINT32                          PartitionNumber;
        UINT64                          PartitionStart;
        UINT64                          PartitionSize;
        UINT8                           Signature[16];
        UINT8                           MBRType;
        UINT8                           SignatureType;
} HARDDRIVE_DEVICE_PATH;

#define MBR_TYPE_PCAT                       0x01
#define MBR_TYPE_EFI_PARTITION_TABLE_HEADER 0x02

#define SIGNATURE_TYPE_MBR                  0x01
#define SIGNATURE_TYPE_GUID                 0x02

#define MEDIA_CDROM_DP                  0x02
typedef struct _CDROM_DEVICE_PATH {
        EFI_DEVICE_PATH_PROTOCOL        Header;
        UINT32                          BootEntry;
        UINT64                          PartitionStart;
        UINT64                          PartitionSize;
} CDROM_DEVICE_PATH;

#define MEDIA_VENDOR_DP                 0x03
/* Use VENDOR_DEVICE_PATH struct */

#define MEDIA_FILEPATH_DP               0x04
typedef struct _FILEPATH_DEVICE_PATH {
        EFI_DEVICE_PATH_PROTOCOL        Header;
        CHAR16                          PathName[1];
} FILEPATH_DEVICE_PATH;

#define SIZE_OF_FILEPATH_DEVICE_PATH EFI_FIELD_OFFSET(FILEPATH_DEVICE_PATH,PathName)

#define MEDIA_PROTOCOL_DP               0x05
typedef struct _MEDIA_PROTOCOL_DEVICE_PATH {
        EFI_DEVICE_PATH_PROTOCOL        Header;
        EFI_GUID                        Protocol;
} MEDIA_PROTOCOL_DEVICE_PATH;

/**
 * PIWG Firmware File SubType.
 * UEFI 2.0 specification version 2.4 § 9.3.6.6.
 */
#define MEDIA_PIWG_FW_FILE_DP 6
typedef struct _MEDIA_FW_VOL_FILEPATH_DEVICE_PATH {
    EFI_DEVICE_PATH_PROTOCOL Header ;
    EFI_GUID FvFileName ;
} MEDIA_FW_VOL_FILEPATH_DEVICE_PATH ;

/**
 * PIWG Firmware Volume Device Path SubType.
 * UEFI 2.0 specification version 2.4 § 9.3.6.7.
 */
#define MEDIA_PIWG_FW_VOL_DP 7
typedef struct _MEDIA_FW_VOL_DEVICE_PATH {
    EFI_DEVICE_PATH_PROTOCOL Header ;
    EFI_GUID FvName ;
} MEDIA_FW_VOL_DEVICE_PATH ;

/**
 * Media relative offset range device path.
 * UEFI 2.0 specification version 2.4 § 9.3.6.8.
 */
#define MEDIA_RELATIVE_OFFSET_RANGE_DP 8
typedef struct _MEDIA_RELATIVE_OFFSET_RANGE_DEVICE_PATH {
    EFI_DEVICE_PATH_PROTOCOL Header ;
    UINT32 Reserved ;
    UINT64 StartingOffset ;
    UINT64 EndingOffset ;
} MEDIA_RELATIVE_OFFSET_RANGE_DEVICE_PATH ;


/*
 * BIOS Boot Specification Device Path (UEFI 2.4 specification, version 2.4 § 9.3.7.)
 */
#define BBS_DEVICE_PATH                 0x05

#define BBS_BBS_DP                      0x01
typedef struct _BBS_BBS_DEVICE_PATH {
        EFI_DEVICE_PATH_PROTOCOL        Header;
        UINT16                          DeviceType;
        UINT16                          StatusFlag;
        CHAR8                           String[1];
} BBS_BBS_DEVICE_PATH;

/* DeviceType definitions - from BBS specification */
#define BBS_TYPE_FLOPPY                 0x01
#define BBS_TYPE_HARDDRIVE              0x02
#define BBS_TYPE_CDROM                  0x03
#define BBS_TYPE_PCMCIA                 0x04
#define BBS_TYPE_USB                    0x05
#define BBS_TYPE_EMBEDDED_NETWORK       0x06
#define BBS_TYPE_DEV                    0x80
#define BBS_TYPE_UNKNOWN                0xFF

typedef union {
    EFI_DEVICE_PATH_PROTOCOL             DevPath;
    PCI_DEVICE_PATH                      Pci;
    PCCARD_DEVICE_PATH                   PcCard;
    MEMMAP_DEVICE_PATH                   MemMap;
    VENDOR_DEVICE_PATH                   Vendor;
    UNKNOWN_DEVICE_VENDOR_DEVICE_PATH    UnknownVendor;
    CONTROLLER_DEVICE_PATH               Controller;
    ACPI_HID_DEVICE_PATH                 Acpi;

    ATAPI_DEVICE_PATH                    Atapi;
    SCSI_DEVICE_PATH                     Scsi;
    FIBRECHANNEL_DEVICE_PATH             FibreChannel;

    F1394_DEVICE_PATH                    F1394;
    USB_DEVICE_PATH                      Usb;
    USB_CLASS_DEVICE_PATH                UsbClass;
    I2O_DEVICE_PATH                      I2O;
    MAC_ADDR_DEVICE_PATH                 MacAddr;
    IPv4_DEVICE_PATH                     Ipv4;
    IPv6_DEVICE_PATH                     Ipv6;
    URI_DEVICE_PATH                      Uri;
    INFINIBAND_DEVICE_PATH               InfiniBand;
    UART_DEVICE_PATH                     Uart;

    HARDDRIVE_DEVICE_PATH                HardDrive;
    CDROM_DEVICE_PATH                    CD;

    FILEPATH_DEVICE_PATH                 FilePath;
    MEDIA_PROTOCOL_DEVICE_PATH           MediaProtocol;

    BBS_BBS_DEVICE_PATH                  Bbs;

} EFI_DEV_PATH;

typedef union {
    EFI_DEVICE_PATH_PROTOCOL             *DevPath;
    PCI_DEVICE_PATH                      *Pci;
    PCCARD_DEVICE_PATH                   *PcCard;
    MEMMAP_DEVICE_PATH                   *MemMap;
    VENDOR_DEVICE_PATH                   *Vendor;
    UNKNOWN_DEVICE_VENDOR_DEVICE_PATH    *UnknownVendor;
    CONTROLLER_DEVICE_PATH               *Controller;
    ACPI_HID_DEVICE_PATH                 *Acpi;

    ATAPI_DEVICE_PATH                    *Atapi;
    SCSI_DEVICE_PATH                     *Scsi;
    FIBRECHANNEL_DEVICE_PATH             *FibreChannel;

    F1394_DEVICE_PATH                    *F1394;
    USB_DEVICE_PATH                      *Usb;
    USB_CLASS_DEVICE_PATH                *UsbClass;
    I2O_DEVICE_PATH                      *I2O;
    MAC_ADDR_DEVICE_PATH                 *MacAddr;
    IPv4_DEVICE_PATH                     *Ipv4;
    IPv6_DEVICE_PATH                     *Ipv6;
    URI_DEVICE_PATH                      *Uri;
    INFINIBAND_DEVICE_PATH               *InfiniBand;
    UART_DEVICE_PATH                     *Uart;

    HARDDRIVE_DEVICE_PATH                *HardDrive;

    FILEPATH_DEVICE_PATH                 *FilePath;
    MEDIA_PROTOCOL_DEVICE_PATH           *MediaProtocol;

    CDROM_DEVICE_PATH                    *CD;
    BBS_BBS_DEVICE_PATH                  *Bbs;

} EFI_DEV_PATH_PTR;

#define EFI_DEVICE_PATH_TO_TEXT_PROTOCOL_GUID \
  { 0x8b843e20, 0x8132, 0x4852, {0x90, 0xcc, 0x55, 0x1a, 0x4e, 0x4a, 0x7f, 0x1c} }

typedef
CHAR16*
(EFIAPI *EFI_DEVICE_PATH_TO_TEXT_NODE) (
    IN CONST EFI_DEVICE_PATH_PROTOCOL    *DeviceNode,
    IN BOOLEAN                           DisplayOnly,
    IN BOOLEAN                           AllowShortcuts
    );

typedef
CHAR16*
(EFIAPI *EFI_DEVICE_PATH_TO_TEXT_PATH) (
    IN CONST EFI_DEVICE_PATH_PROTOCOL    *DevicePath,
    IN BOOLEAN                           DisplayOnly,
    IN BOOLEAN                           AllowShortcuts
    );

typedef struct _EFI_DEVICE_PATH_TO_TEXT_PROTOCOL {
    EFI_DEVICE_PATH_TO_TEXT_NODE         ConvertDeviceNodeToText;
    EFI_DEVICE_PATH_TO_TEXT_PATH         ConvertDevicePathToText;
} EFI_DEVICE_PATH_TO_TEXT_PROTOCOL;

#define EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL_GUID \
  { 0x5c99a21, 0xc70f, 0x4ad2, {0x8a, 0x5f, 0x35, 0xdf, 0x33, 0x43, 0xf5, 0x1e} }

typedef
EFI_DEVICE_PATH_PROTOCOL*
(EFIAPI *EFI_DEVICE_PATH_FROM_TEXT_NODE) (
    IN CONST CHAR16                      *TextDeviceNode
    );

typedef
EFI_DEVICE_PATH_PROTOCOL*
(EFIAPI *EFI_DEVICE_PATH_FROM_TEXT_PATH) (
    IN CONST CHAR16                      *TextDevicePath
    );

typedef struct {
    EFI_DEVICE_PATH_FROM_TEXT_NODE       ConvertTextToDeviceNode;
    EFI_DEVICE_PATH_FROM_TEXT_PATH       ConvertTextToDevicePath;
} EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL;

#define EFI_DEVICE_PATH_UTILITIES_PROTOCOL_GUID \
  { 0x379be4e, 0xd706, 0x437d, {0xb0, 0x37, 0xed, 0xb8, 0x2f, 0xb7, 0x72, 0xa4} }

typedef
UINTN
(EFIAPI *EFI_DEVICE_PATH_UTILS_GET_DEVICE_PATH_SIZE) (
    IN CONST EFI_DEVICE_PATH_PROTOCOL    *DevicePath
    );

typedef
EFI_DEVICE_PATH_PROTOCOL*
(EFIAPI *EFI_DEVICE_PATH_UTILS_DUP_DEVICE_PATH) (
    IN CONST EFI_DEVICE_PATH_PROTOCOL    *DevicePath
    );

typedef
EFI_DEVICE_PATH_PROTOCOL*
(EFIAPI *EFI_DEVICE_PATH_UTILS_APPEND_PATH) (
    IN CONST EFI_DEVICE_PATH_PROTOCOL    *Src1,
    IN CONST EFI_DEVICE_PATH_PROTOCOL    *Src2
    );

typedef
EFI_DEVICE_PATH_PROTOCOL*
(EFIAPI *EFI_DEVICE_PATH_UTILS_APPEND_NODE) (
    IN CONST EFI_DEVICE_PATH_PROTOCOL    *DevicePath,
    IN CONST EFI_DEVICE_PATH_PROTOCOL    *DeviceNode
);

typedef
EFI_DEVICE_PATH_PROTOCOL*
(EFIAPI *EFI_DEVICE_PATH_UTILS_APPEND_INSTANCE) (
    IN CONST EFI_DEVICE_PATH_PROTOCOL    *DevicePath,
    IN CONST EFI_DEVICE_PATH_PROTOCOL    *DevicePathInstance
);

typedef
EFI_DEVICE_PATH_PROTOCOL*
(EFIAPI *EFI_DEVICE_PATH_UTILS_GET_NEXT_INSTANCE) (
    IN OUT EFI_DEVICE_PATH_PROTOCOL      **DevicePathInstance,
    OUT UINTN                            *DevicePathInstanceSize OPTIONAL
);

typedef
EFI_DEVICE_PATH_PROTOCOL*
(EFIAPI *EFI_DEVICE_PATH_UTILS_CREATE_NODE) (
    IN UINT8                             NodeType,
    IN UINT8                             NodeSubType,
    IN UINT16                            NodeLength
    );

typedef
BOOLEAN
(EFIAPI *EFI_DEVICE_PATH_UTILS_IS_MULTI_INSTANCE) (
    IN CONST EFI_DEVICE_PATH_PROTOCOL    *DevicePath
    );

typedef struct _EFI_DEVICE_PATH_UTILITIES_PROTOCOL {
    EFI_DEVICE_PATH_UTILS_GET_DEVICE_PATH_SIZE   GetDevicePathSize;
    EFI_DEVICE_PATH_UTILS_DUP_DEVICE_PATH        DuplicateDevicePath;
    EFI_DEVICE_PATH_UTILS_APPEND_PATH            AppendDevicePath;
    EFI_DEVICE_PATH_UTILS_APPEND_NODE            AppendDeviceNode;
    EFI_DEVICE_PATH_UTILS_APPEND_INSTANCE        AppendDevicePathInstance;
    EFI_DEVICE_PATH_UTILS_GET_NEXT_INSTANCE      GetNextDevicePathInstance;
    EFI_DEVICE_PATH_UTILS_IS_MULTI_INSTANCE      IsDevicePathMultiInstance;
    EFI_DEVICE_PATH_UTILS_CREATE_NODE            CreateDeviceNode;
} EFI_DEVICE_PATH_UTILITIES_PROTOCOL;

#endif
#ifndef _EFI_PCI_IO_H
#define _EFI_PCI_IO_H

#define EFI_PCI_IO_PROTOCOL_GUID \
    { 0x4cf5b200, 0x68b8, 0x4ca5, {0x9e, 0xec, 0xb2, 0x3e, 0x3f, 0x50, 0x02, 0x9a} }

#define EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_GUID \
    { 0x2f707ebb, 0x4a1a, 0x11d4, {0x9a, 0x38, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d} }

INTERFACE_DECL(_EFI_PCI_IO_PROTOCOL);
INTERFACE_DECL(_EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL);

typedef enum {
    EfiPciIoWidthUint8,
    EfiPciIoWidthUint16,
    EfiPciIoWidthUint32,
    EfiPciIoWidthUint64,
    EfiPciIoWidthFifoUint8,
    EfiPciIoWidthFifoUint16,
    EfiPciIoWidthFifoUint32,
    EfiPciIoWidthFifoUint64,
    EfiPciIoWidthFillUint8,
    EfiPciIoWidthFillUint16,
    EfiPciIoWidthFillUint32,
    EfiPciIoWidthFillUint64,
    EfiPciIoWidthMaximum
} EFI_PCI_IO_PROTOCOL_WIDTH, EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH;

#define EFI_PCI_IO_PASS_THROUGH_BAR 0xff

typedef
EFI_STATUS
(EFIAPI *EFI_PCI_IO_PROTOCOL_POLL_IO_MEM) (
  IN struct _EFI_PCI_IO_PROTOCOL  *This,
  IN EFI_PCI_IO_PROTOCOL_WIDTH    Width,
  IN UINT8                        BarIndex,
  IN UINT64                       Offset,
  IN UINT64                       Mask,
  IN UINT64                       Value,
  IN UINT64                       Delay,
  OUT UINT64                      *Result
);

typedef
EFI_STATUS
(EFIAPI *EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_POLL_IO_MEM) (
  IN struct _EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL  *This,
  IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH    Width,
  IN UINT64                                   Address,
  IN UINT64                                   Mask,
  IN UINT64                                   Value,
  IN UINT64                                   Delay,
  OUT UINT64                                  *Result
);

typedef
EFI_STATUS
(EFIAPI *EFI_PCI_IO_PROTOCOL_IO_MEM) (
  IN struct _EFI_PCI_IO_PROTOCOL  *This,
  IN EFI_PCI_IO_PROTOCOL_WIDTH    Width,
  IN UINT8                        BarIndex,
  IN UINT64                       Offset,
  IN UINTN                        Count,
  IN OUT VOID                     *Buffer
);

typedef
EFI_STATUS
(EFIAPI *EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_IO_MEM) (
  IN struct _EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL  *This,
  IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH    Width,
  IN UINT64                                   Address,
  IN UINTN                                    Count,
  IN OUT VOID                                 *Buffer
);

typedef struct {
  EFI_PCI_IO_PROTOCOL_IO_MEM    Read;
  EFI_PCI_IO_PROTOCOL_IO_MEM    Write;
} EFI_PCI_IO_PROTOCOL_ACCESS;

typedef struct {
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_IO_MEM  Read;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_IO_MEM  Write;
} EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_ACCESS;

typedef
EFI_STATUS
(EFIAPI *EFI_PCI_IO_PROTOCOL_CONFIG) (
  IN struct _EFI_PCI_IO_PROTOCOL  *This,
  IN EFI_PCI_IO_PROTOCOL_WIDTH    Width,
  IN UINT32                       Offset,
  IN UINTN                        Count,
  IN OUT VOID                     *Buffer
);

typedef
EFI_STATUS
(EFIAPI *EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_CONFIGURATION) (
  IN struct _EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL    *This,
  OUT VOID                                      **Resources
);

typedef struct {
  EFI_PCI_IO_PROTOCOL_CONFIG Read;
  EFI_PCI_IO_PROTOCOL_CONFIG Write;
} EFI_PCI_IO_PROTOCOL_CONFIG_ACCESS;

typedef
EFI_STATUS
(EFIAPI *EFI_PCI_IO_PROTOCOL_COPY_MEM) (
  IN struct _EFI_PCI_IO_PROTOCOL  *This,
  IN EFI_PCI_IO_PROTOCOL_WIDTH    Width,
  IN UINT8                        DestBarIndex,
  IN UINT64                       DestOffset,
  IN UINT8                        SrcBarIndex,
  IN UINT64                       SrcOffset,
  IN UINTN                        Count
);

typedef
EFI_STATUS
(EFIAPI *EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_COPY_MEM) (
  IN struct _EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL  *This,
  IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH    Width,
  IN UINT64                                   DestAddress,
  IN UINT64                                   SrcAddress,
  IN UINTN                                    Count
);

typedef enum {
    EfiPciIoOperationBusMasterRead,
    EfiPciIoOperationBusMasterWrite,
    EfiPciIoOperationBusMasterCommonBuffer,
    EfiPciIoOperationMaximum
} EFI_PCI_IO_PROTOCOL_OPERATION;

typedef enum {
  EfiPciOperationBusMasterRead,
  EfiPciOperationBusMasterWrite,
  EfiPciOperationBusMasterCommonBuffer,
  EfiPciOperationBusMasterRead64,
  EfiPciOperationBusMasterWrite64,
  EfiPciOperationBusMasterCommonBuffer64,
  EfiPciOperationMaximum
} EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_OPERATION;

typedef
EFI_STATUS
(EFIAPI *EFI_PCI_IO_PROTOCOL_MAP) (
  IN struct _EFI_PCI_IO_PROTOCOL   *This,
  IN EFI_PCI_IO_PROTOCOL_OPERATION Operation,
  IN VOID                          *HostAddress,
  IN OUT UINTN                     *NumberOfBytes,
  OUT EFI_PHYSICAL_ADDRESS         *DeviceAddress,
  OUT VOID                         **Mapping
);

typedef
EFI_STATUS
(EFIAPI *EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_MAP) (
  IN struct _EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL    *This,
  IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_OPERATION  Operation,
  IN VOID                                       *HostAddress,
  IN OUT UINTN                                  *NumberOfBytes,
  OUT EFI_PHYSICAL_ADDRESS                      *DeviceAddress,
  OUT VOID                                      **Mapping
);

typedef
EFI_STATUS
(EFIAPI *EFI_PCI_IO_PROTOCOL_UNMAP) (
  IN struct _EFI_PCI_IO_PROTOCOL  *This,
  IN VOID                         *Mapping
);

typedef
EFI_STATUS
(EFIAPI *EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_UNMAP) (
  IN struct _EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL    *This,
  IN VOID                                       *Mapping
);

typedef
EFI_STATUS
(EFIAPI *EFI_PCI_IO_PROTOCOL_ALLOCATE_BUFFER) (
  IN struct _EFI_PCI_IO_PROTOCOL  *This,
  IN EFI_ALLOCATE_TYPE            Type,
  IN EFI_MEMORY_TYPE              MemoryType,
  IN UINTN                        Pages,
  OUT VOID                        **HostAddress,
  IN UINT64                       Attributes
);

typedef
EFI_STATUS
(EFIAPI *EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_ALLOCATE_BUFFER) (
  IN struct _EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL    *This,
  IN EFI_ALLOCATE_TYPE                          Type,
  IN EFI_MEMORY_TYPE                            MemoryType,
  IN UINTN                                      Pages,
  IN OUT VOID                                   **HostAddress,
  IN UINT64                                     Attributes
);

typedef
EFI_STATUS
(EFIAPI *EFI_PCI_IO_PROTOCOL_FREE_BUFFER) (
  IN struct _EFI_PCI_IO_PROTOCOL  *This,
  IN UINTN                        Pages,
  IN VOID                         *HostAddress
  );

typedef
EFI_STATUS
(EFIAPI *EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_FREE_BUFFER) (
  IN struct _EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL    *This,
  IN UINTN                                      Pages,
  IN VOID                                       *HostAddress
);

typedef
EFI_STATUS
(EFIAPI *EFI_PCI_IO_PROTOCOL_FLUSH) (
  IN struct _EFI_PCI_IO_PROTOCOL  *This
);

typedef
EFI_STATUS
(EFIAPI *EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_FLUSH) (
  IN struct _EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL    *This
);

typedef
EFI_STATUS
(EFIAPI *EFI_PCI_IO_PROTOCOL_GET_LOCATION) (
  IN struct _EFI_PCI_IO_PROTOCOL  *This,
  OUT UINTN                       *SegmentNumber,
  OUT UINTN                       *BusNumber,
  OUT UINTN                       *DeviceNumber,
  OUT UINTN                       *FunctionNumber
);

#define EFI_PCI_ATTRIBUTE_ISA_MOTHERBOARD_IO      0x0001
#define EFI_PCI_ATTRIBUTE_ISA_IO                  0x0002
#define EFI_PCI_ATTRIBUTE_VGA_PALETTE_IO          0x0004
#define EFI_PCI_ATTRIBUTE_VGA_MEMORY              0x0008
#define EFI_PCI_ATTRIBUTE_VGA_IO                  0x0010
#define EFI_PCI_ATTRIBUTE_IDE_PRIMARY_IO          0x0020
#define EFI_PCI_ATTRIBUTE_IDE_SECONDARY_IO        0x0040
#define EFI_PCI_ATTRIBUTE_MEMORY_WRITE_COMBINE    0x0080
#define EFI_PCI_ATTRIBUTE_IO                      0x0100
#define EFI_PCI_ATTRIBUTE_MEMORY                  0x0200
#define EFI_PCI_ATTRIBUTE_BUS_MASTER              0x0400
#define EFI_PCI_ATTRIBUTE_MEMORY_CACHED           0x0800
#define EFI_PCI_ATTRIBUTE_MEMORY_DISABLE          0x1000
#define EFI_PCI_ATTRIBUTE_EMBEDDED_DEVICE         0x2000
#define EFI_PCI_ATTRIBUTE_EMBEDDED_ROM            0x4000
#define EFI_PCI_ATTRIBUTE_DUAL_ADDRESS_CYCLE      0x8000
#define EFI_PCI_ATTRIBUTE_ISA_IO_16               0x10000
#define EFI_PCI_ATTRIBUTE_VGA_PALETTE_IO_16       0x20000
#define EFI_PCI_ATTRIBUTE_VGA_IO_16               0x40000

#define EFI_PCI_IO_ATTRIBUTE_ISA_MOTHERBOARD_IO   EFI_PCI_ATTRIBUTE_ISA_MOTHERBOARD_IO
#define EFI_PCI_IO_ATTRIBUTE_ISA_IO               EFI_PCI_ATTRIBUTE_ISA_IO
#define EFI_PCI_IO_ATTRIBUTE_VGA_PALETTE_IO       EFI_PCI_ATTRIBUTE_VGA_PALETTE_IO
#define EFI_PCI_IO_ATTRIBUTE_VGA_MEMORY           EFI_PCI_ATTRIBUTE_VGA_MEMORY
#define EFI_PCI_IO_ATTRIBUTE_VGA_IO               EFI_PCI_ATTRIBUTE_VGA_IO
#define EFI_PCI_IO_ATTRIBUTE_IDE_PRIMARY_IO       EFI_PCI_ATTRIBUTE_IDE_PRIMARY_IO
#define EFI_PCI_IO_ATTRIBUTE_IDE_SECONDARY_IO     EFI_PCI_ATTRIBUTE_IDE_SECONDARY_IO
#define EFI_PCI_IO_ATTRIBUTE_MEMORY_WRITE_COMBINE EFI_PCI_ATTRIBUTE_MEMORY_WRITE_COMBINE
#define EFI_PCI_IO_ATTRIBUTE_IO                   EFI_PCI_ATTRIBUTE_IO
#define EFI_PCI_IO_ATTRIBUTE_MEMORY               EFI_PCI_ATTRIBUTE_MEMORY
#define EFI_PCI_IO_ATTRIBUTE_BUS_MASTER           EFI_PCI_ATTRIBUTE_BUS_MASTER
#define EFI_PCI_IO_ATTRIBUTE_MEMORY_CACHED        EFI_PCI_ATTRIBUTE_MEMORY_CACHED
#define EFI_PCI_IO_ATTRIBUTE_MEMORY_DISABLE       EFI_PCI_ATTRIBUTE_MEMORY_DISABLE
#define EFI_PCI_IO_ATTRIBUTE_EMBEDDED_DEVICE      EFI_PCI_ATTRIBUTE_EMBEDDED_DEVICE
#define EFI_PCI_IO_ATTRIBUTE_EMBEDDED_ROM         EFI_PCI_ATTRIBUTE_EMBEDDED_ROM
#define EFI_PCI_IO_ATTRIBUTE_DUAL_ADDRESS_CYCLE   EFI_PCI_ATTRIBUTE_DUAL_ADDRESS_CYCLE
#define EFI_PCI_IO_ATTRIBUTE_ISA_IO_16            EFI_PCI_ATTRIBUTE_ISA_IO_16
#define EFI_PCI_IO_ATTRIBUTE_VGA_PALETTE_IO_16    EFI_PCI_ATTRIBUTE_VGA_PALETTE_IO_16
#define EFI_PCI_IO_ATTRIBUTE_VGA_IO_16            EFI_PCI_ATTRIBUTE_VGA_IO_16

#define EFI_PCI_ATTRIBUTE_VALID_FOR_ALLOCATE_BUFFER \
    (EFI_PCI_ATTRIBUTE_MEMORY_WRITE_COMBINE | EFI_PCI_ATTRIBUTE_MEMORY_CACHED | EFI_PCI_ATTRIBUTE_DUAL_ADDRESS_CYCLE)

#define EFI_PCI_ATTRIBUTE_INVALID_FOR_ALLOCATE_BUFFER \
    (~EFI_PCI_ATTRIBUTE_VALID_FOR_ALLOCATE_BUFFER)

typedef struct {
    UINT8 Register;
    UINT8 Function;
    UINT8 Device;
    UINT8 Bus;
    UINT32 ExtendedRegister;
} EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_PCI_ADDRESS;

typedef enum {
    EfiPciIoAttributeOperationGet,
    EfiPciIoAttributeOperationSet,
    EfiPciIoAttributeOperationEnable,
    EfiPciIoAttributeOperationDisable,
    EfiPciIoAttributeOperationSupported,
    EfiPciIoAttributeOperationMaximum
} EFI_PCI_IO_PROTOCOL_ATTRIBUTE_OPERATION;

typedef
EFI_STATUS
(EFIAPI *EFI_PCI_IO_PROTOCOL_ATTRIBUTES) (
  IN struct _EFI_PCI_IO_PROTOCOL             *This,
  IN EFI_PCI_IO_PROTOCOL_ATTRIBUTE_OPERATION Operation,
  IN UINT64                                  Attributes,
  OUT UINT64                                 *Result OPTIONAL
);

typedef
EFI_STATUS
(EFIAPI *EFI_PCI_IO_PROTOCOL_GET_BAR_ATTRIBUTES) (
  IN struct _EFI_PCI_IO_PROTOCOL  *This,
  IN UINT8                        BarIndex,
  OUT UINT64                      *Supports   OPTIONAL,
  OUT VOID                        **Resources OPTIONAL
);

typedef
EFI_STATUS
(EFIAPI *EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_GET_ATTRIBUTES) (
  IN struct _EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL    *This,
  OUT UINT64                                    *Supports,
  OUT UINT64                                    *Attributes
);

typedef
EFI_STATUS
(EFIAPI *EFI_PCI_IO_PROTOCOL_SET_BAR_ATTRIBUTES) (
  IN struct _EFI_PCI_IO_PROTOCOL  *This,
  IN UINT64                       Attributes,
  IN UINT8                        BarIndex,
  IN OUT UINT64                   *Offset,
  IN OUT UINT64                   *Length
);

typedef
EFI_STATUS
(EFIAPI *EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_SET_ATTRIBUTES) (
  IN struct _EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL    *This,
  IN UINT64                                     Attributes,
  IN OUT UINT64                                 *ResourceBase,
  IN OUT UINT64                                 *ResourceLength
);

typedef struct _EFI_PCI_IO_PROTOCOL {
  EFI_PCI_IO_PROTOCOL_POLL_IO_MEM        PollMem;
  EFI_PCI_IO_PROTOCOL_POLL_IO_MEM        PollIo;
  EFI_PCI_IO_PROTOCOL_ACCESS             Mem;
  EFI_PCI_IO_PROTOCOL_ACCESS             Io;
  EFI_PCI_IO_PROTOCOL_CONFIG_ACCESS      Pci;
  EFI_PCI_IO_PROTOCOL_COPY_MEM           CopyMem;
  EFI_PCI_IO_PROTOCOL_MAP                Map;
  EFI_PCI_IO_PROTOCOL_UNMAP              Unmap;
  EFI_PCI_IO_PROTOCOL_ALLOCATE_BUFFER    AllocateBuffer;
  EFI_PCI_IO_PROTOCOL_FREE_BUFFER        FreeBuffer;
  EFI_PCI_IO_PROTOCOL_FLUSH              Flush;
  EFI_PCI_IO_PROTOCOL_GET_LOCATION       GetLocation;
  EFI_PCI_IO_PROTOCOL_ATTRIBUTES         Attributes;
  EFI_PCI_IO_PROTOCOL_GET_BAR_ATTRIBUTES GetBarAttributes;
  EFI_PCI_IO_PROTOCOL_SET_BAR_ATTRIBUTES SetBarAttributes;
  UINT64                                 RomSize;
  VOID                                   *RomImage;
} EFI_PCI_IO_PROTOCOL;

// Note: Because it conflicted with the EDK2 struct name, the
// 'EFI_PCI_IO_PROTOCOL' GUID definition, from older versions
// of gnu-efi, is now obsoleted.
// Use 'EFI_PCI_IO_PROTOCOL_GUID' instead.

typedef struct _EFI_PCI_IO_PROTOCOL _EFI_PCI_IO;
typedef EFI_PCI_IO_PROTOCOL EFI_PCI_IO;

typedef struct _EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL {
  EFI_HANDLE                                      ParentHandle;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_POLL_IO_MEM     PollMem;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_POLL_IO_MEM     PollIo;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_ACCESS          Mem;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_ACCESS          Io;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_ACCESS          Pci;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_COPY_MEM        CopyMem;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_MAP             Map;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_UNMAP           Unmap;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_ALLOCATE_BUFFER AllocateBuffer;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_FREE_BUFFER     FreeBuffer;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_FLUSH           Flush;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_GET_ATTRIBUTES  GetAttributes;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_SET_ATTRIBUTES  SetAttributes;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_CONFIGURATION   Configuration;
  UINT32                                          SegmentNumber;
} EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL;

#endif /* _EFI_PCI_IO_H */
#ifndef _EFI_PROT_H
#define _EFI_PROT_H

/*++

Copyright (c) 1998  Intel Corporation

Module Name:

    efiprot.h

Abstract:

    EFI Protocols



Revision History

--*/

//
//  FPSWA library protocol
//
#define EFI_FPSWA_PROTOCOL_GUID \
    { 0xc41b6531, 0x97b9, 0x11d3, {0x9a, 0x29, 0x0, 0x90, 0x27, 0x3f, 0xc1, 0x4d} }
#define FPSWA_PROTOCOL EFI_FPSWA_PROTOCOL_GUID

//
// Device Path protocol
//

#define EFI_DEVICE_PATH_PROTOCOL_GUID \
    { 0x9576e91, 0x6d3f, 0x11d2, {0x8e, 0x39, 0x0, 0xa0, 0xc9, 0x69, 0x72, 0x3b} }
#define DEVICE_PATH_PROTOCOL EFI_DEVICE_PATH_PROTOCOL_GUID


//
// Block IO protocol
//

#define EFI_BLOCK_IO_PROTOCOL_GUID \
    { 0x964e5b21, 0x6459, 0x11d2, {0x8e, 0x39, 0x0, 0xa0, 0xc9, 0x69, 0x72, 0x3b} }
#define BLOCK_IO_PROTOCOL EFI_BLOCK_IO_PROTOCOL_GUID

#define EFI_BLOCK_IO_PROTOCOL_REVISION    0x00010000
#define EFI_BLOCK_IO_PROTOCOL_REVISION2   0x00020001
#define EFI_BLOCK_IO_PROTOCOL_REVISION3   ((2<<16) | 31)
#define EFI_BLOCK_IO_INTERFACE_REVISION   EFI_BLOCK_IO_PROTOCOL_REVISION
#define EFI_BLOCK_IO_INTERFACE_REVISION2  EFI_BLOCK_IO_PROTOCOL_REVISION2
#define EFI_BLOCK_IO_INTERFACE_REVISION3  EFI_BLOCK_IO_PROTOCOL_REVISION3

INTERFACE_DECL(_EFI_BLOCK_IO_PROTOCOL);

typedef
EFI_STATUS
(EFIAPI *EFI_BLOCK_RESET) (
    IN struct _EFI_BLOCK_IO_PROTOCOL  *This,
    IN BOOLEAN                        ExtendedVerification
    );

typedef
EFI_STATUS
(EFIAPI *EFI_BLOCK_READ) (
    IN struct _EFI_BLOCK_IO_PROTOCOL  *This,
    IN UINT32                         MediaId,
    IN EFI_LBA                        LBA,
    IN UINTN                          BufferSize,
    OUT VOID                          *Buffer
    );


typedef
EFI_STATUS
(EFIAPI *EFI_BLOCK_WRITE) (
    IN struct _EFI_BLOCK_IO_PROTOCOL  *This,
    IN UINT32                         MediaId,
    IN EFI_LBA                        LBA,
    IN UINTN                          BufferSize,
    IN VOID                           *Buffer
    );


typedef
EFI_STATUS
(EFIAPI *EFI_BLOCK_FLUSH) (
    IN struct _EFI_BLOCK_IO_PROTOCOL  *This
    );



typedef struct {
    UINT32              MediaId;
    BOOLEAN             RemovableMedia;
    BOOLEAN             MediaPresent;

    BOOLEAN             LogicalPartition;
    BOOLEAN             ReadOnly;
    BOOLEAN             WriteCaching;

    UINT32              BlockSize;
    UINT32              IoAlign;

    EFI_LBA             LastBlock;

    /* revision 2 */
    EFI_LBA             LowestAlignedLba;
    UINT32              LogicalBlocksPerPhysicalBlock;
    /* revision 3 */
    UINT32              OptimalTransferLengthGranularity;
} EFI_BLOCK_IO_MEDIA;

typedef struct _EFI_BLOCK_IO_PROTOCOL {
    UINT64                  Revision;

    EFI_BLOCK_IO_MEDIA      *Media;

    EFI_BLOCK_RESET         Reset;
    EFI_BLOCK_READ          ReadBlocks;
    EFI_BLOCK_WRITE         WriteBlocks;
    EFI_BLOCK_FLUSH         FlushBlocks;

} EFI_BLOCK_IO_PROTOCOL;

typedef struct _EFI_BLOCK_IO_PROTOCOL _EFI_BLOCK_IO;
typedef EFI_BLOCK_IO_PROTOCOL EFI_BLOCK_IO;

#define EFI_BLOCK_IO2_PROTOCOL_GUID \
    { 0xa77b2472, 0xe282, 0x4e9f, {0xa2, 0x45, 0xc2, 0xc0, 0xe2, 0x7b, 0xbc, 0xc1} }

INTERFACE_DECL(_EFI_BLOCK_IO2_PROTOCOL);

typedef struct {
    EFI_EVENT               Event;
    EFI_STATUS              TransactionStatus;
} EFI_BLOCK_IO2_TOKEN;

typedef
EFI_STATUS
(EFIAPI *EFI_BLOCK_RESET_EX) (
    IN struct _EFI_BLOCK_IO2_PROTOCOL  *This,
    IN BOOLEAN                         ExtendedVerification
    );

typedef
EFI_STATUS
(EFIAPI *EFI_BLOCK_READ_EX) (
    IN struct _EFI_BLOCK_IO2_PROTOCOL  *This,
    IN UINT32                          MediaId,
    IN EFI_LBA                         LBA,
    IN OUT EFI_BLOCK_IO2_TOKEN         *Token,
    IN UINTN                           BufferSize,
    OUT VOID                           *Buffer
    );

typedef
EFI_STATUS
(EFIAPI *EFI_BLOCK_WRITE_EX) (
    IN struct _EFI_BLOCK_IO2_PROTOCOL  *This,
    IN UINT32                          MediaId,
    IN EFI_LBA                         LBA,
    IN OUT EFI_BLOCK_IO2_TOKEN         *Token,
    IN UINTN                           BufferSize,
    IN VOID                            *Buffer
    );

typedef
EFI_STATUS
(EFIAPI *EFI_BLOCK_FLUSH_EX) (
    IN struct _EFI_BLOCK_IO2_PROTOCOL  *This,
    IN OUT EFI_BLOCK_IO2_TOKEN         *Token
    );

typedef struct _EFI_BLOCK_IO2_PROTOCOL {
    EFI_BLOCK_IO_MEDIA  *Media;
    EFI_BLOCK_RESET_EX  Reset;
    EFI_BLOCK_READ_EX   ReadBlocksEx;
    EFI_BLOCK_WRITE_EX  WriteBlocksEx;
    EFI_BLOCK_FLUSH_EX  FlushBlocksEx;
} EFI_BLOCK_IO2_PROTOCOL;

//
// Disk Block IO protocol
//

#define EFI_DISK_IO_PROTOCOL_GUID \
    { 0xce345171, 0xba0b, 0x11d2,  {0x8e, 0x4f, 0x0, 0xa0, 0xc9, 0x69, 0x72, 0x3b} }
#define DISK_IO_PROTOCOL EFI_DISK_IO_PROTOCOL_GUID

#define EFI_DISK_IO_PROTOCOL_REVISION  0x00010000
#define EFI_DISK_IO_INTERFACE_REVISION EFI_DISK_IO_PROTOCOL_REVISION

INTERFACE_DECL(_EFI_DISK_IO_PROTOCOL);

typedef
EFI_STATUS
(EFIAPI *EFI_DISK_READ) (
    IN struct _EFI_DISK_IO_PROTOCOL  *This,
    IN UINT32                        MediaId,
    IN UINT64                        Offset,
    IN UINTN                         BufferSize,
    OUT VOID                         *Buffer
    );


typedef
EFI_STATUS
(EFIAPI *EFI_DISK_WRITE) (
    IN struct _EFI_DISK_IO_PROTOCOL  *This,
    IN UINT32                        MediaId,
    IN UINT64                        Offset,
    IN UINTN                         BufferSize,
    IN VOID                          *Buffer
    );


typedef struct _EFI_DISK_IO_PROTOCOL {
    UINT64              Revision;
    EFI_DISK_READ       ReadDisk;
    EFI_DISK_WRITE      WriteDisk;
} EFI_DISK_IO_PROTOCOL;

typedef struct _EFI_DISK_IO_PROTOCOL _EFI_DISK_IO;
typedef EFI_DISK_IO_PROTOCOL EFI_DISK_IO;


#define EFI_DISK_IO2_PROTOCOL_GUID \
    { 0x151c8eae, 0x7f2c, 0x472c,  {0x9e, 0x54, 0x98, 0x28, 0x19, 0x4f, 0x6a, 0x88} }

#define EFI_DISK_IO2_PROTOCOL_REVISION  0x00020000

INTERFACE_DECL(_EFI_DISK_IO2_PROTOCOL);

typedef struct {
    EFI_EVENT  Event;
    EFI_STATUS TransactionStatus;
} EFI_DISK_IO2_TOKEN;

typedef
EFI_STATUS
(EFIAPI *EFI_DISK_CANCEL_EX) (
    IN struct _EFI_DISK_IO2_PROTOCOL  *This
    );

typedef
EFI_STATUS
(EFIAPI *EFI_DISK_READ_EX) (
    IN struct _EFI_DISK_IO2_PROTOCOL  *This,
    IN UINT32                         MediaId,
    IN UINT64                         Offset,
    IN OUT EFI_DISK_IO2_TOKEN         *Token,
    IN UINTN                          BufferSize,
    OUT VOID                          *Buffer
    );

typedef
EFI_STATUS
(EFIAPI *EFI_DISK_WRITE_EX) (
    IN struct _EFI_DISK_IO2_PROTOCOL  *This,
    IN UINT32                         MediaId,
    IN UINT64                         Offset,
    IN OUT EFI_DISK_IO2_TOKEN         *Token,
    IN UINTN                          BufferSize,
    IN VOID                           *Buffer
    );

typedef
EFI_STATUS
(EFIAPI *EFI_DISK_FLUSH_EX) (
    IN struct _EFI_DISK_IO2_PROTOCOL  *This,
    IN OUT EFI_DISK_IO2_TOKEN         *Token
    );

typedef struct _EFI_DISK_IO2_PROTOCOL {
    UINT64                            Revision;
    EFI_DISK_CANCEL_EX                Cancel;
    EFI_DISK_READ_EX                  ReadDiskEx;
    EFI_DISK_WRITE_EX                 WriteDiskEx;
    EFI_DISK_FLUSH_EX                 FlushDiskEx;
} EFI_DISK_IO2_PROTOCOL;

//
// Simple file system protocol
//

#define EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID \
    { 0x964e5b22, 0x6459, 0x11d2, {0x8e, 0x39, 0x0, 0xa0, 0xc9, 0x69, 0x72, 0x3b} }
#define SIMPLE_FILE_SYSTEM_PROTOCOL EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID

INTERFACE_DECL(_EFI_SIMPLE_FILE_SYSTEM_PROTOCOL);
INTERFACE_DECL(_EFI_FILE_HANDLE);

typedef
EFI_STATUS
(EFIAPI *EFI_VOLUME_OPEN) (
    IN struct _EFI_SIMPLE_FILE_SYSTEM_PROTOCOL    *This,
    OUT struct _EFI_FILE_HANDLE                   **Root
    );

#define EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_REVISION  0x00010000
#define EFI_FILE_IO_INTERFACE_REVISION EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_REVISION

typedef struct _EFI_SIMPLE_FILE_SYSTEM_PROTOCOL {
    UINT64                  Revision;
    EFI_VOLUME_OPEN         OpenVolume;
} EFI_SIMPLE_FILE_SYSTEM_PROTOCOL;

typedef struct _EFI_SIMPLE_FILE_SYSTEM_PROTOCOL _EFI_FILE_IO_INTERFACE;
typedef EFI_SIMPLE_FILE_SYSTEM_PROTOCOL EFI_FILE_IO_INTERFACE;

//
//
//

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_OPEN) (
    IN struct _EFI_FILE_HANDLE  *File,
    OUT struct _EFI_FILE_HANDLE **NewHandle,
    IN CHAR16                   *FileName,
    IN UINT64                   OpenMode,
    IN UINT64                   Attributes
    );

// Open modes
#define EFI_FILE_MODE_READ      0x0000000000000001
#define EFI_FILE_MODE_WRITE     0x0000000000000002
#define EFI_FILE_MODE_CREATE    0x8000000000000000

// File attributes
#define EFI_FILE_READ_ONLY      0x0000000000000001
#define EFI_FILE_HIDDEN         0x0000000000000002
#define EFI_FILE_SYSTEM         0x0000000000000004
#define EFI_FILE_RESERVIED      0x0000000000000008
#define EFI_FILE_DIRECTORY      0x0000000000000010
#define EFI_FILE_ARCHIVE        0x0000000000000020
#define EFI_FILE_VALID_ATTR     0x0000000000000037

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_CLOSE) (
    IN struct _EFI_FILE_HANDLE  *File
    );

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_DELETE) (
    IN struct _EFI_FILE_HANDLE  *File
    );

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_READ) (
    IN struct _EFI_FILE_HANDLE  *File,
    IN OUT UINTN                *BufferSize,
    OUT VOID                    *Buffer
    );

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_WRITE) (
    IN struct _EFI_FILE_HANDLE  *File,
    IN OUT UINTN                *BufferSize,
    IN VOID                     *Buffer
    );

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_SET_POSITION) (
    IN struct _EFI_FILE_HANDLE  *File,
    IN UINT64                   Position
    );

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_GET_POSITION) (
    IN struct _EFI_FILE_HANDLE  *File,
    OUT UINT64                  *Position
    );

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_GET_INFO) (
    IN struct _EFI_FILE_HANDLE  *File,
    IN EFI_GUID                 *InformationType,
    IN OUT UINTN                *BufferSize,
    OUT VOID                    *Buffer
    );

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_SET_INFO) (
    IN struct _EFI_FILE_HANDLE  *File,
    IN EFI_GUID                 *InformationType,
    IN UINTN                    BufferSize,
    IN VOID                     *Buffer
    );

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_FLUSH) (
    IN struct _EFI_FILE_HANDLE  *File
    );

typedef struct {
    EFI_EVENT       Event;
    EFI_STATUS      Status;
    UINTN           BufferSize;
    VOID            *Buffer;
} EFI_FILE_IO_TOKEN;

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_OPEN_EX)(
    IN struct _EFI_FILE_HANDLE  *File,
    OUT struct _EFI_FILE_HANDLE **NewHandle,
    IN CHAR16                   *FileName,
    IN UINT64                   OpenMode,
    IN UINT64                   Attributes,
    IN OUT EFI_FILE_IO_TOKEN    *Token
    );

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_READ_EX) (
    IN struct _EFI_FILE_HANDLE  *File,
    IN OUT EFI_FILE_IO_TOKEN    *Token
    );

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_WRITE_EX) (
    IN struct _EFI_FILE_HANDLE  *File,
    IN OUT EFI_FILE_IO_TOKEN    *Token
    );

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_FLUSH_EX) (
    IN struct _EFI_FILE_HANDLE  *File,
    IN OUT EFI_FILE_IO_TOKEN    *Token
    );

#define EFI_FILE_PROTOCOL_REVISION         0x00010000
#define EFI_FILE_PROTOCOL_REVISION2        0x00020000
#define EFI_FILE_PROTOCOL_LATEST_REVISION  EFI_FILE_PROTOCOL_REVISION2
#define EFI_FILE_HANDLE_REVISION           EFI_FILE_PROTOCOL_REVISION

typedef struct _EFI_FILE_HANDLE {
    UINT64                  Revision;
    EFI_FILE_OPEN           Open;
    EFI_FILE_CLOSE          Close;
    EFI_FILE_DELETE         Delete;
    EFI_FILE_READ           Read;
    EFI_FILE_WRITE          Write;
    EFI_FILE_GET_POSITION   GetPosition;
    EFI_FILE_SET_POSITION   SetPosition;
    EFI_FILE_GET_INFO       GetInfo;
    EFI_FILE_SET_INFO       SetInfo;
    EFI_FILE_FLUSH          Flush;
    EFI_FILE_OPEN_EX        OpenEx;
    EFI_FILE_READ_EX        ReadEx;
    EFI_FILE_WRITE_EX       WriteEx;
    EFI_FILE_FLUSH_EX       FlushEx;
} EFI_FILE_PROTOCOL, *EFI_FILE_HANDLE;

typedef EFI_FILE_PROTOCOL EFI_FILE;


//
// File information types
//

#define EFI_FILE_INFO_ID   \
    { 0x9576e92, 0x6d3f, 0x11d2, {0x8e, 0x39, 0x0, 0xa0, 0xc9, 0x69, 0x72, 0x3b} }

typedef struct {
    UINT64                  Size;
    UINT64                  FileSize;
    UINT64                  PhysicalSize;
    EFI_TIME                CreateTime;
    EFI_TIME                LastAccessTime;
    EFI_TIME                ModificationTime;
    UINT64                  Attribute;
    CHAR16                  FileName[1];
} EFI_FILE_INFO;

//
// The FileName field of the EFI_FILE_INFO data structure is variable length.
// Whenever code needs to know the size of the EFI_FILE_INFO data structure, it needs to
// be the size of the data structure without the FileName field.  The following macro
// computes this size correctly no matter how big the FileName array is declared.
// This is required to make the EFI_FILE_INFO data structure ANSI compilant.
//

#define SIZE_OF_EFI_FILE_INFO EFI_FIELD_OFFSET(EFI_FILE_INFO,FileName)

#define EFI_FILE_SYSTEM_INFO_ID    \
    { 0x9576e93, 0x6d3f, 0x11d2, {0x8e, 0x39, 0x0, 0xa0, 0xc9, 0x69, 0x72, 0x3b} }

typedef struct {
    UINT64                  Size;
    BOOLEAN                 ReadOnly;
    UINT64                  VolumeSize;
    UINT64                  FreeSpace;
    UINT32                  BlockSize;
    CHAR16                  VolumeLabel[1];
} EFI_FILE_SYSTEM_INFO;

//
// The VolumeLabel field of the EFI_FILE_SYSTEM_INFO data structure is variable length.
// Whenever code needs to know the size of the EFI_FILE_SYSTEM_INFO data structure, it needs
// to be the size of the data structure without the VolumeLable field.  The following macro
// computes this size correctly no matter how big the VolumeLable array is declared.
// This is required to make the EFI_FILE_SYSTEM_INFO data structure ANSI compilant.
//

#define SIZE_OF_EFI_FILE_SYSTEM_INFO EFI_FIELD_OFFSET(EFI_FILE_SYSTEM_INFO,VolumeLabel)

#define EFI_FILE_SYSTEM_VOLUME_LABEL_ID    \
    { 0xDB47D7D3,0xFE81, 0x11d3, {0x9A, 0x35, 0x00, 0x90, 0x27, 0x3F, 0xC1, 0x4D} }

typedef struct {
    CHAR16                  VolumeLabel[1];
} EFI_FILE_SYSTEM_VOLUME_LABEL;

#define SIZE_OF_EFI_FILE_SYSTEM_VOLUME_LABEL_INFO EFI_FIELD_OFFSET(EFI_FILE_SYSTEM_VOLUME_LABEL,VolumeLabel)

//
// For compatibility with older versions of gnu-efi
//
#define EFI_FILE_SYSTEM_VOLUME_LABEL_INFO_ID EFI_FILE_SYSTEM_VOLUME_LABEL_ID
#define EFI_FILE_SYSTEM_VOLUME_LABEL_INFO    EFI_FILE_SYSTEM_VOLUME_LABEL

//
// Load file protocol
//


#define EFI_LOAD_FILE_PROTOCOL_GUID \
    { 0x56EC3091, 0x954C, 0x11d2, {0x8E, 0x3F, 0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3B} }
#define LOAD_FILE_PROTOCOL EFI_LOAD_FILE_PROTOCOL_GUID

INTERFACE_DECL(_EFI_LOAD_FILE_PROTOCOL);

typedef
EFI_STATUS
(EFIAPI *EFI_LOAD_FILE) (
    IN struct _EFI_LOAD_FILE_PROTOCOL  *This,
    IN EFI_DEVICE_PATH                  *FilePath,
    IN BOOLEAN                          BootPolicy,
    IN OUT UINTN                        *BufferSize,
    IN VOID                             *Buffer OPTIONAL
    );

typedef struct _EFI_LOAD_FILE_PROTOCOL {
    EFI_LOAD_FILE                       LoadFile;
} EFI_LOAD_FILE_PROTOCOL;

typedef struct _EFI_LOAD_FILE_PROTOCOL _EFI_LOAD_FILE_INTERFACE;
typedef EFI_LOAD_FILE_PROTOCOL EFI_LOAD_FILE_INTERFACE;

//
// Device IO protocol
//

#define EFI_DEVICE_IO_PROTOCOL_GUID \
    { 0xaf6ac311, 0x84c3, 0x11d2, {0x8e, 0x3c, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b} }
#define DEVICE_IO_PROTOCOL EFI_DEVICE_IO_PROTOCOL_GUID

INTERFACE_DECL(_EFI_DEVICE_IO_PROTOCOL);

typedef enum {
    IO_UINT8,
    IO_UINT16,
    IO_UINT32,
    IO_UINT64,
//
// Specification Change: Copy from MMIO to MMIO vs. MMIO to buffer, buffer to MMIO
//
    MMIO_COPY_UINT8,
    MMIO_COPY_UINT16,
    MMIO_COPY_UINT32,
    MMIO_COPY_UINT64
} EFI_IO_WIDTH;

#define EFI_PCI_ADDRESS(_bus,_dev,_func) \
    ( (UINT64) ( (((UINTN)_bus) << 24) + (((UINTN)_dev) << 16) + (((UINTN)_func) << 8) ) )


typedef
EFI_STATUS
(EFIAPI *EFI_DEVICE_IO) (
    IN struct _EFI_DEVICE_IO_PROTOCOL *This,
    IN EFI_IO_WIDTH                 Width,
    IN UINT64                       Address,
    IN UINTN                        Count,
    IN OUT VOID                     *Buffer
    );

typedef struct {
    EFI_DEVICE_IO                   Read;
    EFI_DEVICE_IO                   Write;
} EFI_IO_ACCESS;

typedef
EFI_STATUS
(EFIAPI *EFI_PCI_DEVICE_PATH) (
    IN struct _EFI_DEVICE_IO_PROTOCOL   *This,
    IN UINT64                           Address,
    IN OUT EFI_DEVICE_PATH              **PciDevicePath
    );

typedef enum {
    EfiBusMasterRead,
    EfiBusMasterWrite,
    EfiBusMasterCommonBuffer
} EFI_IO_OPERATION_TYPE;

typedef
EFI_STATUS
(EFIAPI *EFI_IO_MAP) (
    IN struct _EFI_DEVICE_IO_PROTOCOL   *This,
    IN EFI_IO_OPERATION_TYPE            Operation,
    IN EFI_PHYSICAL_ADDRESS             *HostAddress,
    IN OUT UINTN                        *NumberOfBytes,
    OUT EFI_PHYSICAL_ADDRESS            *DeviceAddress,
    OUT VOID                            **Mapping
    );

typedef
EFI_STATUS
(EFIAPI *EFI_IO_UNMAP) (
    IN struct _EFI_DEVICE_IO_PROTOCOL   *This,
    IN VOID                             *Mapping
    );

typedef
EFI_STATUS
(EFIAPI *EFI_IO_ALLOCATE_BUFFER) (
    IN struct _EFI_DEVICE_IO_PROTOCOL   *This,
    IN EFI_ALLOCATE_TYPE                Type,
    IN EFI_MEMORY_TYPE                  MemoryType,
    IN UINTN                            Pages,
    IN OUT EFI_PHYSICAL_ADDRESS         *HostAddress
    );

typedef
EFI_STATUS
(EFIAPI *EFI_IO_FLUSH) (
    IN struct _EFI_DEVICE_IO_PROTOCOL   *This
    );

typedef
EFI_STATUS
(EFIAPI *EFI_IO_FREE_BUFFER) (
    IN struct _EFI_DEVICE_IO_PROTOCOL   *This,
    IN UINTN                            Pages,
    IN EFI_PHYSICAL_ADDRESS             HostAddress
    );

typedef struct _EFI_DEVICE_IO_PROTOCOL {
    EFI_IO_ACCESS                       Mem;
    EFI_IO_ACCESS                       Io;
    EFI_IO_ACCESS                       Pci;
    EFI_IO_MAP                          Map;
    EFI_PCI_DEVICE_PATH                 PciDevicePath;
    EFI_IO_UNMAP                        Unmap;
    EFI_IO_ALLOCATE_BUFFER              AllocateBuffer;
    EFI_IO_FLUSH                        Flush;
    EFI_IO_FREE_BUFFER                  FreeBuffer;
} EFI_DEVICE_IO_PROTOCOL;

typedef struct _EFI_DEVICE_IO_PROTOCOL _EFI_DEVICE_IO_INTERFACE;
typedef EFI_DEVICE_IO_PROTOCOL EFI_DEVICE_IO_INTERFACE;

//
// Unicode Collation protocol
//

#define EFI_UNICODE_COLLATION_PROTOCOL_GUID \
    { 0x1d85cd7f, 0xf43d, 0x11d2, {0x9a, 0xc,  0x0, 0x90, 0x27, 0x3f, 0xc1, 0x4d} }
#define UNICODE_COLLATION_PROTOCOL EFI_UNICODE_COLLATION_PROTOCOL_GUID

#define EFI_UNICODE_BYTE_ORDER_MARK       (CHAR16)(0xfeff)
#define UNICODE_BYTE_ORDER_MARK EFI_UNICODE_BYTE_ORDER_MARK

INTERFACE_DECL(_EFI_UNICODE_COLLATION_PROTOCOL);

typedef
INTN
(EFIAPI *EFI_UNICODE_STRICOLL) (
    IN struct _EFI_UNICODE_COLLATION_PROTOCOL  *This,
    IN CHAR16                         *s1,
    IN CHAR16                         *s2
    );

typedef
BOOLEAN
(EFIAPI *EFI_UNICODE_METAIMATCH) (
    IN struct _EFI_UNICODE_COLLATION_PROTOCOL  *This,
    IN CHAR16                         *String,
    IN CHAR16                         *Pattern
    );

typedef
VOID
(EFIAPI *EFI_UNICODE_STRLWR) (
    IN struct _EFI_UNICODE_COLLATION_PROTOCOL  *This,
    IN OUT CHAR16                       *Str
    );

typedef
VOID
(EFIAPI *EFI_UNICODE_STRUPR) (
    IN struct _EFI_UNICODE_COLLATION_PROTOCOL  *This,
    IN OUT CHAR16                       *Str
    );

typedef
VOID
(EFIAPI *EFI_UNICODE_FATTOSTR) (
    IN struct _EFI_UNICODE_COLLATION_PROTOCOL  *This,
    IN UINTN                            FatSize,
    IN CHAR8                            *Fat,
    OUT CHAR16                          *String
    );

typedef
BOOLEAN
(EFIAPI *EFI_UNICODE_STRTOFAT) (
    IN struct _EFI_UNICODE_COLLATION_PROTOCOL  *This,
    IN CHAR16                           *String,
    IN UINTN                            FatSize,
    OUT CHAR8                           *Fat
    );

//
// Hash Protocol
//
#define EFI_HASH_PROTOCOL_GUID \
  { 0xC5184932, 0xDBA5, 0x46DB, { 0xA5, 0xBA, 0xCC, 0x0B, 0xDA, 0x9C, 0x14, 0x35 } }
#define HASH_PROTOCOL EFI_HASH_PROTOCOL_GUID

#define EFI_HASH_ALGORITHM_SHA1_GUID \
  { 0x2AE9D80F, 0x3FB2, 0x4095, { 0xB7, 0xB1, 0xE9, 0x31, 0x57, 0xB9, 0x46, 0xB6 } } // Deprecated
#define EFI_HASH_ALGORITHM_SHA1 EFI_HASH_ALGORITHM_SHA1_GUID

#define EFI_HASH_ALGORITHM_SHA224_GUID \
  { 0x8DF01A06, 0x9BD5, 0x4BF7, { 0xB0, 0x21, 0xDB, 0x4F, 0xD9, 0xCC, 0xF4, 0x5B } } // Deprecated
#define EFI_HASH_ALGORITHM_SHA224 EFI_HASH_ALGORITHM_SHA224_GUID

#define EFI_HASH_ALGORITHM_SHA256_GUID \
  { 0x51AA59DE, 0xFDF2, 0x4EA3, { 0xBC, 0x63, 0x87, 0x5F, 0xB7, 0x84, 0x2E, 0xE9 } } // Deprecated
#define EFI_HASH_ALGORITHM_SHA256 EFI_HASH_ALGORITHM_SHA256_GUID

#define EFI_HASH_ALGORITHM_SHA384_GUID \
  { 0xEFA96432, 0xDE33, 0x4DD2, { 0xAE, 0xE6, 0x32, 0x8C, 0x33, 0xDF, 0x77, 0x7A } } // Deprecated
#define EFI_HASH_ALGORITHM_SHA384 EFI_HASH_ALGORITHM_SHA384_GUID

#define EFI_HASH_ALGORITHM_SHA512_GUID \
  { 0xCAA4381E, 0x750C, 0x4770, { 0xB8, 0x70, 0x7A, 0x23, 0xB4, 0xE4, 0x21, 0x30 } } // Deprecated
#define EFI_HASH_ALGORITHM_SHA512 EFI_HASH_ALGORITHM_SHA512_GUID

#define EFI_HASH_ALGORITHM_MD5_GUID \
  { 0x0AF7C79C, 0x65B5, 0x4319, { 0xB0, 0xAE, 0x44, 0xEC, 0x48, 0x4E, 0x4A, 0xD7 } } // Deprecated
#define EFI_HASH_ALGORITHM_MD5 EFI_HASH_ALGORITHM_MD5_GUID

#define EFI_HASH_ALGORITHM_SHA1_NOPAD_GUID \
  { 0x24C5DC2F, 0x53E2, 0x40CA, { 0x9E, 0xD6, 0xA5, 0xD9, 0xA4, 0x9F, 0x46, 0x3B } }
#define EFI_HASH_ALGORITHM_SHA1_NOPAD EFI_HASH_ALGORITHM_SHA1_NOPAD_GUID

#define EFI_HASH_ALGORITHM_SHA256_NOPAD_GUID \
  { 0x8628752A, 0x6CB7, 0x4814, { 0x96, 0xFC, 0x24, 0xA8, 0x15, 0xAC, 0x22, 0x26 } }
#define EFI_HASH_ALGORITHM_SHA256_NOPAD EFI_HASH_ALGORITHM_SHA256_NOPAD_GUID


INTERFACE_DECL(_EFI_HASH_PROTOCOL);

typedef UINT8 EFI_MD5_HASH[16];
typedef UINT8 EFI_SHA1_HASH[20];
typedef UINT8 EFI_SHA224_HASH[28];
typedef UINT8 EFI_SHA256_HASH[32];
typedef UINT8 EFI_SHA384_HASH[48];
typedef UINT8 EFI_SHA512_HASH[64];
typedef union _EFI_HASH_OUTPUT {
  EFI_MD5_HASH                    *Md5Hash;
  EFI_SHA1_HASH                   *Sha1Hash;
  EFI_SHA224_HASH                 *Sha224Hash;
  EFI_SHA256_HASH                 *Sha256Hash;
  EFI_SHA384_HASH                 *Sha384Hash;
  EFI_SHA512_HASH                 *Sha512Hash;
} EFI_HASH_OUTPUT;

typedef
EFI_STATUS
(EFIAPI *EFI_HASH_GET_HASH_SIZE) (
  IN CONST struct _EFI_HASH_PROTOCOL  *This,
  IN CONST EFI_GUID               *HashAlgorithm,
  OUT UINTN                       *HashSize);

typedef
EFI_STATUS
(EFIAPI *EFI_HASH_HASH) (
  IN CONST struct _EFI_HASH_PROTOCOL  *This,
  IN CONST EFI_GUID               *HashAlgorithm,
  IN BOOLEAN                      Extend,
  IN CONST UINT8                  *Message,
  IN UINT64                       MessageSize,
  IN OUT EFI_HASH_OUTPUT          *Hash);

typedef struct _EFI_HASH_PROTOCOL {
  EFI_HASH_GET_HASH_SIZE                  GetHashSize;
  EFI_HASH_HASH                           Hash;
} EFI_HASH_PROTOCOL;

typedef struct _EFI_HASH_PROTOCOL _EFI_HASH;
typedef EFI_HASH_PROTOCOL EFI_HASH;


typedef struct _EFI_UNICODE_COLLATION_PROTOCOL {

    // general
    EFI_UNICODE_STRICOLL                StriColl;
    EFI_UNICODE_METAIMATCH              MetaiMatch;
    EFI_UNICODE_STRLWR                  StrLwr;
    EFI_UNICODE_STRUPR                  StrUpr;

    // for supporting fat volumes
    EFI_UNICODE_FATTOSTR                FatToStr;
    EFI_UNICODE_STRTOFAT                StrToFat;

    CHAR8                               *SupportedLanguages;
} EFI_UNICODE_COLLATION_PROTOCOL;

typedef EFI_UNICODE_COLLATION_PROTOCOL EFI_UNICODE_COLLATION_INTERFACE;

/* Graphics output protocol */
#define EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID \
   { 0x9042a9de, 0x23dc, 0x4a38, {0x96, 0xfb, 0x7a, 0xde, 0xd0, 0x80, 0x51, 0x6a } }
typedef struct _EFI_GRAPHICS_OUTPUT_PROTOCOL EFI_GRAPHICS_OUTPUT_PROTOCOL;

typedef struct {
  UINT32            RedMask;
  UINT32            GreenMask;
  UINT32            BlueMask;
  UINT32            ReservedMask;
} EFI_PIXEL_BITMASK;

typedef enum {
  PixelRedGreenBlueReserved8BitPerColor,
  PixelBlueGreenRedReserved8BitPerColor,
  PixelBitMask,
  PixelBltOnly,
  PixelFormatMax
} EFI_GRAPHICS_PIXEL_FORMAT;

typedef struct {
  UINT32                     Version;
  UINT32                     HorizontalResolution;
  UINT32                     VerticalResolution;
  EFI_GRAPHICS_PIXEL_FORMAT  PixelFormat;
  EFI_PIXEL_BITMASK          PixelInformation;
  UINT32                     PixelsPerScanLine;
} EFI_GRAPHICS_OUTPUT_MODE_INFORMATION;

/**
  Return the current video mode information.

  @param  This       Protocol instance pointer.
  @param  ModeNumber The mode number to return information on.
  @param  SizeOfInfo A pointer to the size, in bytes, of the Info buffer.
  @param  Info       A pointer to callee allocated buffer that returns information about ModeNumber.

  @retval EFI_SUCCESS           Mode information returned.
  @retval EFI_BUFFER_TOO_SMALL  The Info buffer was too small.
  @retval EFI_DEVICE_ERROR      A hardware error occurred trying to retrieve the video mode.
  @retval EFI_NOT_STARTED       Video display is not initialized. Call SetMode ()
  @retval EFI_INVALID_PARAMETER One of the input args was NULL.

**/
typedef
EFI_STATUS
(EFIAPI *EFI_GRAPHICS_OUTPUT_PROTOCOL_QUERY_MODE) (
  IN  EFI_GRAPHICS_OUTPUT_PROTOCOL          *This,
  IN  UINT32                                ModeNumber,
  OUT UINTN                                 *SizeOfInfo,
  OUT EFI_GRAPHICS_OUTPUT_MODE_INFORMATION  **Info
  )
;

/**
  Return the current video mode information.

  @param  This              Protocol instance pointer.
  @param  ModeNumber        The mode number to be set.

  @retval EFI_SUCCESS       Graphics mode was changed.
  @retval EFI_DEVICE_ERROR  The device had an error and could not complete the request.
  @retval EFI_UNSUPPORTED   ModeNumber is not supported by this device.

**/
typedef
EFI_STATUS
(EFIAPI *EFI_GRAPHICS_OUTPUT_PROTOCOL_SET_MODE) (
  IN  EFI_GRAPHICS_OUTPUT_PROTOCOL *This,
  IN  UINT32                       ModeNumber
  );

typedef struct {
  UINT8 Blue;
  UINT8 Green;
  UINT8 Red;
  UINT8 Reserved;
} EFI_GRAPHICS_OUTPUT_BLT_PIXEL;

typedef union {
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL Pixel;
  UINT32                        Raw;
} EFI_GRAPHICS_OUTPUT_BLT_PIXEL_UNION;

typedef enum {
  EfiBltVideoFill,
  EfiBltVideoToBltBuffer,
  EfiBltBufferToVideo,
  EfiBltVideoToVideo,
  EfiGraphicsOutputBltOperationMax
} EFI_GRAPHICS_OUTPUT_BLT_OPERATION;

/**
  The following table defines actions for BltOperations:

  <B>EfiBltVideoFill</B> - Write data from the  BltBuffer pixel (SourceX, SourceY)
  directly to every pixel of the video display rectangle
  (DestinationX, DestinationY) (DestinationX + Width, DestinationY + Height).
  Only one pixel will be used from the BltBuffer. Delta is NOT used.

  <B>EfiBltVideoToBltBuffer</B> - Read data from the video display rectangle
  (SourceX, SourceY) (SourceX + Width, SourceY + Height) and place it in
  the BltBuffer rectangle (DestinationX, DestinationY )
  (DestinationX + Width, DestinationY + Height). If DestinationX or
  DestinationY is not zero then Delta must be set to the length in bytes
  of a row in the BltBuffer.

  <B>EfiBltBufferToVideo</B> - Write data from the  BltBuffer rectangle
  (SourceX, SourceY) (SourceX + Width, SourceY + Height) directly to the
  video display rectangle (DestinationX, DestinationY)
  (DestinationX + Width, DestinationY + Height). If SourceX or SourceY is
  not zero then Delta must be set to the length in bytes of a row in the
  BltBuffer.

  <B>EfiBltVideoToVideo</B> - Copy from the video display rectangle (SourceX, SourceY)
  (SourceX + Width, SourceY + Height) .to the video display rectangle
  (DestinationX, DestinationY) (DestinationX + Width, DestinationY + Height).
  The BltBuffer and Delta  are not used in this mode.

  @param  This         Protocol instance pointer.
  @param  BltBuffer    Buffer containing data to blit into video buffer. This
                       buffer has a size of Width*Height*sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL)
  @param  BltOperation Operation to perform on BlitBuffer and video memory
  @param  SourceX      X coordinate of source for the BltBuffer.
  @param  SourceY      Y coordinate of source for the BltBuffer.
  @param  DestinationX X coordinate of destination for the BltBuffer.
  @param  DestinationY Y coordinate of destination for the BltBuffer.
  @param  Width        Width of rectangle in BltBuffer in pixels.
  @param  Height       Hight of rectangle in BltBuffer in pixels.
  @param  Delta        OPTIONAL

  @retval EFI_SUCCESS           The Blt operation completed.
  @retval EFI_INVALID_PARAMETER BltOperation is not valid.
  @retval EFI_DEVICE_ERROR      A hardware error occured writting to the video buffer.

**/
typedef
EFI_STATUS
(EFIAPI *EFI_GRAPHICS_OUTPUT_PROTOCOL_BLT) (
  IN  EFI_GRAPHICS_OUTPUT_PROTOCOL            *This,
  IN  EFI_GRAPHICS_OUTPUT_BLT_PIXEL           *BltBuffer,   OPTIONAL
  IN  EFI_GRAPHICS_OUTPUT_BLT_OPERATION       BltOperation,
  IN  UINTN                                   SourceX,
  IN  UINTN                                   SourceY,
  IN  UINTN                                   DestinationX,
  IN  UINTN                                   DestinationY,
  IN  UINTN                                   Width,
  IN  UINTN                                   Height,
  IN  UINTN                                   Delta         OPTIONAL
  );

typedef struct {
  UINT32                                 MaxMode;
  UINT32                                 Mode;
  EFI_GRAPHICS_OUTPUT_MODE_INFORMATION   *Info;
  UINTN                                  SizeOfInfo;
  EFI_PHYSICAL_ADDRESS                   FrameBufferBase;
  UINTN                                  FrameBufferSize;
} EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE;

struct _EFI_GRAPHICS_OUTPUT_PROTOCOL {
  EFI_GRAPHICS_OUTPUT_PROTOCOL_QUERY_MODE  QueryMode;
  EFI_GRAPHICS_OUTPUT_PROTOCOL_SET_MODE    SetMode;
  EFI_GRAPHICS_OUTPUT_PROTOCOL_BLT         Blt;
  EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE        *Mode;
};



/*
 * EFI EDID Discovered Protocol
 * UEFI Specification Version 2.5 Section 11.9
 */
#define EFI_EDID_DISCOVERED_PROTOCOL_GUID \
    { 0x1C0C34F6, 0xD380, 0x41FA, { 0xA0, 0x49, 0x8a, 0xD0, 0x6C, 0x1A, 0x66, 0xAA} }

typedef struct _EFI_EDID_DISCOVERED_PROTOCOL {
    UINT32   SizeOfEdid;
    UINT8   *Edid;
} EFI_EDID_DISCOVERED_PROTOCOL;



/*
 * EFI EDID Active Protocol
 * UEFI Specification Version 2.5 Section 11.9
 */
#define EFI_EDID_ACTIVE_PROTOCOL_GUID \
    { 0xBD8C1056, 0x9F36, 0x44EC, { 0x92, 0xA8, 0xA6, 0x33, 0x7F, 0x81, 0x79, 0x86} }

typedef struct _EFI_EDID_ACTIVE_PROTOCOL {
    UINT32   SizeOfEdid;
    UINT8   *Edid;
} EFI_EDID_ACTIVE_PROTOCOL;



/*
 * EFI EDID Override Protocol
 * UEFI Specification Version 2.5 Section 11.9
 */
#define EFI_EDID_OVERRIDE_PROTOCOL_GUID \
    { 0x48ECB431, 0xFB72, 0x45C0, { 0xA9, 0x22, 0xF4, 0x58, 0xFE, 0x04, 0x0B, 0xD5} }

INTERFACE_DECL(_EFI_EDID_OVERRIDE_PROTOCOL);

typedef
EFI_STATUS
(EFIAPI *EFI_EDID_OVERRIDE_PROTOCOL_GET_EDID) (
  IN      struct _EFI_EDID_OVERRIDE_PROTOCOL   *This,
  IN      EFI_HANDLE                           *ChildHandle,
  OUT     UINT32                               *Attributes,
  IN OUT  UINTN                                *EdidSize,
  IN OUT  UINT8                               **Edid);

typedef struct _EFI_EDID_OVERRIDE_PROTOCOL {
    EFI_EDID_OVERRIDE_PROTOCOL_GET_EDID  GetEdid;
} EFI_EDID_OVERRIDE_PROTOCOL;



INTERFACE_DECL(_EFI_SERVICE_BINDING);

typedef
EFI_STATUS
(EFIAPI *EFI_SERVICE_BINDING_CREATE_CHILD) (
    IN struct _EFI_SERVICE_BINDING *This,
    IN EFI_HANDLE                  *ChildHandle
    );

typedef
EFI_STATUS
(EFIAPI *EFI_SERVICE_BINDING_DESTROY_CHILD) (
    IN struct _EFI_SERVICE_BINDING *This,
    IN EFI_HANDLE                  ChildHandle
    );

typedef struct _EFI_SERVICE_BINDING {
    EFI_SERVICE_BINDING_CREATE_CHILD  CreateChild;
    EFI_SERVICE_BINDING_DESTROY_CHILD DestroyChild;
} EFI_SERVICE_BINDING;



/*
 * EFI Driver Binding Protocol
 * UEFI Specification Version 2.5 Section 10.1
 */
#define EFI_DRIVER_BINDING_PROTOCOL_GUID \
    { 0x18A031AB, 0xB443, 0x4D1A, { 0xA5, 0xC0, 0x0C, 0x09, 0x26, 0x1E, 0x9F, 0x71} }
#define DRIVER_BINDING_PROTOCOL EFI_DRIVER_BINDING_PROTOCOL_GUID

INTERFACE_DECL(_EFI_DRIVER_BINDING_PROTOCOL);

typedef
EFI_STATUS
(EFIAPI *EFI_DRIVER_BINDING_PROTOCOL_SUPPORTED) (
  IN      struct _EFI_DRIVER_BINDING_PROTOCOL *This,
  IN      EFI_HANDLE                          ControllerHandle,
  IN      EFI_DEVICE_PATH                     *RemainingDevicePath OPTIONAL);

typedef
EFI_STATUS
(EFIAPI *EFI_DRIVER_BINDING_PROTOCOL_START) (
  IN      struct _EFI_DRIVER_BINDING_PROTOCOL *This,
  IN      EFI_HANDLE                          ControllerHandle,
  IN      EFI_DEVICE_PATH                     *RemainingDevicePath OPTIONAL);

typedef
EFI_STATUS
(EFIAPI *EFI_DRIVER_BINDING_PROTOCOL_STOP) (
  IN      struct _EFI_DRIVER_BINDING_PROTOCOL *This,
  IN      EFI_HANDLE                          ControllerHandle,
  IN      UINTN                               NumberOfChildren,
  IN      EFI_HANDLE                          *ChildHandleBuffer OPTIONAL);

typedef struct _EFI_DRIVER_BINDING_PROTOCOL {
  EFI_DRIVER_BINDING_PROTOCOL_SUPPORTED       Supported;
  EFI_DRIVER_BINDING_PROTOCOL_START           Start;
  EFI_DRIVER_BINDING_PROTOCOL_STOP            Stop;
  UINT32                                      Version;
  EFI_HANDLE                                  ImageHandle;
  EFI_HANDLE                                  DriverBindingHandle;
} EFI_DRIVER_BINDING_PROTOCOL;

typedef struct _EFI_DRIVER_BINDING_PROTOCOL _EFI_DRIVER_BINDING;
typedef EFI_DRIVER_BINDING_PROTOCOL EFI_DRIVER_BINDING;


/*
 * Backwards compatibility with older GNU-EFI versions. Deprecated.
 */
#define EFI_DRIVER_SUPPORTED         EFI_DRIVER_BINDING_PROTOCOL_SUPPORTED
#define EFI_DRIVER_START             EFI_DRIVER_BINDING_PROTOCOL_START
#define EFI_DRIVER_STOP              EFI_DRIVER_BINDING_PROTOCOL_STOP



/*
 * EFI Component Name Protocol
 * Deprecated - use EFI Component Name 2 Protocol instead
 */
#define EFI_COMPONENT_NAME_PROTOCOL_GUID \
    {0x107A772C, 0xD5E1, 0x11D4, { 0x9A, 0x46, 0x00, 0x90, 0x27, 0x3F, 0xC1, 0x4D} }
#define COMPONENT_NAME_PROTOCOL EFI_COMPONENT_NAME_PROTOCOL_GUID

INTERFACE_DECL(_EFI_COMPONENT_NAME_PROTOCOL);

typedef
EFI_STATUS
(EFIAPI *EFI_COMPONENT_NAME_GET_DRIVER_NAME) (
  IN      struct _EFI_COMPONENT_NAME_PROTOCOL   *This,
  IN      CHAR8                                 *Language,
  OUT     CHAR16                                **DriverName);

typedef
EFI_STATUS
(EFIAPI *EFI_COMPONENT_NAME_GET_CONTROLLER_NAME) (
  IN      struct _EFI_COMPONENT_NAME_PROTOCOL   *This,
  IN      EFI_HANDLE                            ControllerHandle,
  IN      EFI_HANDLE                            ChildHandle OPTIONAL,
  IN      CHAR8                                 *Language,
  OUT     CHAR16                                **ControllerName);

typedef struct _EFI_COMPONENT_NAME_PROTOCOL {
  EFI_COMPONENT_NAME_GET_DRIVER_NAME      GetDriverName;
  EFI_COMPONENT_NAME_GET_CONTROLLER_NAME  GetControllerName;
  CHAR8                                   *SupportedLanguages;
} EFI_COMPONENT_NAME_PROTOCOL;

typedef struct _EFI_COMPONENT_NAME_PROTOCOL _EFI_COMPONENT_NAME;
typedef EFI_COMPONENT_NAME_PROTOCOL EFI_COMPONENT_NAME;


/*
 * EFI Component Name 2 Protocol
 * UEFI Specification Version 2.5 Section 10.5
 */
#define EFI_COMPONENT_NAME2_PROTOCOL_GUID \
    {0x6A7A5CFF, 0xE8D9, 0x4F70, { 0xBA, 0xDA, 0x75, 0xAB, 0x30, 0x25, 0xCE, 0x14} }
#define COMPONENT_NAME2_PROTOCOL EFI_COMPONENT_NAME2_PROTOCOL_GUID

INTERFACE_DECL(_EFI_COMPONENT_NAME2_PROTOCOL);

typedef
EFI_STATUS
(EFIAPI *EFI_COMPONENT_NAME2_GET_DRIVER_NAME) (
  IN      struct _EFI_COMPONENT_NAME2_PROTOCOL   *This,
  IN      CHAR8                                  *Language,
  OUT     CHAR16                                 **DriverName);

typedef
EFI_STATUS
(EFIAPI *EFI_COMPONENT_NAME2_GET_CONTROLLER_NAME) (
  IN      struct _EFI_COMPONENT_NAME2_PROTOCOL   *This,
  IN      EFI_HANDLE                             ControllerHandle,
  IN      EFI_HANDLE                             ChildHandle OPTIONAL,
  IN      CHAR8                                  *Language,
  OUT     CHAR16                                 **ControllerName);

typedef struct _EFI_COMPONENT_NAME2_PROTOCOL {
  EFI_COMPONENT_NAME2_GET_DRIVER_NAME       GetDriverName;
  EFI_COMPONENT_NAME2_GET_CONTROLLER_NAME   GetControllerName;
  CHAR8                                     *SupportedLanguages;
} EFI_COMPONENT_NAME2_PROTOCOL;

typedef struct _EFI_COMPONENT_NAME2_PROTOCOL _EFI_COMPONENT_NAME2;
typedef EFI_COMPONENT_NAME2_PROTOCOL EFI_COMPONENT_NAME2;



/*
 * EFI Loaded Image Protocol
 * UEFI Specification Version 2.5 Section 8.1
 */
#define EFI_LOADED_IMAGE_PROTOCOL_GUID \
    { 0x5B1B31A1, 0x9562, 0x11d2, {0x8E, 0x3F, 0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3B} }
#define LOADED_IMAGE_PROTOCOL EFI_LOADED_IMAGE_PROTOCOL_GUID

#define EFI_LOADED_IMAGE_PROTOCOL_REVISION  0x1000
#define EFI_IMAGE_INFORMATION_REVISION  EFI_LOADED_IMAGE_PROTOCOL_REVISION

typedef
EFI_STATUS
(EFIAPI *EFI_IMAGE_UNLOAD) (
    IN EFI_HANDLE                   ImageHandle
    );

typedef struct {
    UINT32                          Revision;
    EFI_HANDLE                      ParentHandle;
    struct _EFI_SYSTEM_TABLE        *SystemTable;

    // Source location of image
    EFI_HANDLE                      DeviceHandle;
    EFI_DEVICE_PATH                 *FilePath;
    VOID                            *Reserved;

    // Images load options
    UINT32                          LoadOptionsSize;
    VOID                            *LoadOptions;

    // Location of where image was loaded
    VOID                            *ImageBase;
    UINT64                          ImageSize;
    EFI_MEMORY_TYPE                 ImageCodeType;
    EFI_MEMORY_TYPE                 ImageDataType;

    // If the driver image supports a dynamic unload request
    EFI_IMAGE_UNLOAD                Unload;
} EFI_LOADED_IMAGE_PROTOCOL;

typedef EFI_LOADED_IMAGE_PROTOCOL EFI_LOADED_IMAGE;

#define EFI_LOADED_IMAGE_DEVICE_PATH_PROTOCOL_GUID \
    {0xbc62157e, 0x3e33, 0x4fec, {0x99, 0x20, 0x2d, 0x3b, 0x36, 0xd7, 0x50, 0xdf} }

/*
 * Random Number Generator Protocol
 * UEFI Specification Version 2.5 Section 35.5
 */
#define EFI_RNG_PROTOCOL_GUID                          \
          { 0x3152bca5, 0xeade, 0x433d, {0x86, 0x2e, 0xc0, 0x1c, 0xdc, 0x29, 0x1f, 0x44} }

typedef EFI_GUID EFI_RNG_ALGORITHM;

#define EFI_RNG_ALGORITHM_SP800_90_HASH_256_GUID       \
     {0xa7af67cb, 0x603b, 0x4d42, {0xba, 0x21, 0x70, 0xbf, 0xb6, 0x29, 0x3f, 0x96} }

#define EFI_RNG_ALGORITHM_SP800_90_HMAC_256_GUID       \
     {0xc5149b43, 0xae85, 0x4f53, {0x99, 0x82, 0xb9, 0x43, 0x35, 0xd3, 0xa9, 0xe7} }

#define EFI_RNG_ALGORITHM_SP800_90_CTR_256_GUID        \
     {0x44f0de6e, 0x4d8c, 0x4045, {0xa8, 0xc7, 0x4d, 0xd1, 0x68, 0x85, 0x6b, 0x9e} }

#define EFI_RNG_ALGORITHM_X9_31_3DES_GUID              \
     {0x63c4785a, 0xca34, 0x4012, {0xa3, 0xc8, 0x0b, 0x6a, 0x32, 0x4f, 0x55, 0x46} }

#define EFI_RNG_ALGORITHM_X9_31_AES_GUID               \
     {0xacd03321, 0x777e, 0x4d3d, {0xb1, 0xc8, 0x20, 0xcf, 0xd8, 0x88, 0x20, 0xc9} }

#define EFI_RNG_ALGORITHM_RAW                          \
     {0xe43176d7, 0xb6e8, 0x4827, {0xb7, 0x84, 0x7f, 0xfd, 0xc4, 0xb6, 0x85, 0x61} }

INTERFACE_DECL(_EFI_RNG_PROTOCOL);

typedef
EFI_STATUS
(EFIAPI *EFI_RNG_GET_INFO) (
  IN      struct _EFI_RNG_PROTOCOL   *This,
  IN OUT  UINTN                      *RNGAlgorithmListSize,
  OUT     EFI_RNG_ALGORITHM          *RNGAlgorithmList
);

typedef
EFI_STATUS
(EFIAPI *EFI_RNG_GET_RNG) (
  IN      struct _EFI_RNG_PROTOCOL   *This,
  IN      EFI_RNG_ALGORITHM          *RNGAlgorithm,           OPTIONAL
  IN      UINTN                      RNGValueLength,
  OUT     UINT8                      *RNGValue
);

typedef struct _EFI_RNG_PROTOCOL {
          EFI_RNG_GET_INFO           GetInfo;
          EFI_RNG_GET_RNG            GetRNG;
} EFI_RNG_PROTOCOL;


//
// EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL
//

#define EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL_GUID          \
          { 0x6b30c738, 0xa391, 0x11d4, {0x9a, 0x3b, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d} }

INTERFACE_DECL(_EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL);

typedef
EFI_STATUS
(EFIAPI *EFI_PLATFORM_DRIVER_OVERRIDE_GET_DRIVER) (
IN      struct _EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL  *This,
IN      EFI_HANDLE                                      ControllerHandle,
IN OUT  EFI_HANDLE                                     *DriverImageHandle);

typedef
EFI_STATUS
(EFIAPI *EFI_PLATFORM_DRIVER_OVERRIDE_GET_DRIVER_PATH) (
IN      struct _EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL  *This,
IN      EFI_HANDLE                                      ControllerHandle,
IN OUT  EFI_DEVICE_PATH                               **DriverImagePath);

typedef
EFI_STATUS
(EFIAPI *EFI_PLATFORM_DRIVER_OVERRIDE_DRIVER_LOADED) (
IN      struct _EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL  *This,
IN      EFI_HANDLE                                      ControllerHandle,
IN      EFI_DEVICE_PATH                                *DriverImagePath,
IN      EFI_HANDLE                                      DriverImageHandle);

typedef struct _EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL {
  EFI_PLATFORM_DRIVER_OVERRIDE_GET_DRIVER       GetDriver;
  EFI_PLATFORM_DRIVER_OVERRIDE_GET_DRIVER_PATH  GetDriverPath;
  EFI_PLATFORM_DRIVER_OVERRIDE_DRIVER_LOADED    DriverLoaded;
} EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL;

//
// EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL
//

#define EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL_GUID          \
          { 0x3bc1b285, 0x8a15, 0x4a82, {0xaa, 0xbf, 0x4d, 0x7d, 0x13, 0xfb, 0x32, 0x65} }

INTERFACE_DECL(_EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL);

typedef
EFI_STATUS
(EFIAPI *EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_GET_DRIVER) (
IN      struct _EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL  *This,
IN OUT  EFI_HANDLE                                         *DriverImageHandle);

typedef struct _EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL {
  EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_GET_DRIVER       GetDriver;
} EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL;

//
// EFI_DRIVER_FAMILY_OVERRIDE_PROTOCOL
//

#define EFI_DRIVER_FAMILY_OVERRIDE_PROTOCOL_GUID          \
          { 0xb1ee129e, 0xda36, 0x4181, {0x91, 0xf8, 0x04, 0xa4, 0x92, 0x37, 0x66, 0xa7} }

INTERFACE_DECL(_EFI_DRIVER_FAMILY_OVERRIDE_PROTOCOL);

typedef
UINT32
(EFIAPI *EFI_DRIVER_FAMILY_OVERRIDE_GET_VERSION) (
IN      struct _EFI_DRIVER_FAMILY_OVERRIDE_PROTOCOL  *This);

typedef struct _EFI_DRIVER_FAMILY_OVERRIDE_PROTOCOL {
  EFI_DRIVER_FAMILY_OVERRIDE_GET_VERSION       GetVersion;
} EFI_DRIVER_FAMILY_OVERRIDE_PROTOCOL;

//
// EFI_EBC_PROTOCOL
//

#define EFI_EBC_INTERPRETER_PROTOCOL_GUID              \
     {0x13ac6dd1, 0x73d0, 0x11d4, {0xb0, 0x6b, 0x00, 0xaa, 0x00, 0xbd, 0x6d, 0xe7} }

#define EFI_EBC_PROTOCOL_GUID EFI_EBC_INTERPRETER_PROTOCOL_GUID

INTERFACE_DECL(_EFI_EBC_PROTOCOL);

typedef
EFI_STATUS
(EFIAPI *EFI_EBC_CREATE_THUNK)(
  IN struct _EFI_EBC_PROTOCOL   *This,
  IN EFI_HANDLE                 ImageHandle,
  IN VOID                       *EbcEntryPoint,
  OUT VOID                      **Thunk);

typedef
EFI_STATUS
(EFIAPI *EFI_EBC_UNLOAD_IMAGE)(
  IN struct _EFI_EBC_PROTOCOL   *This,
  IN EFI_HANDLE                 ImageHandle);

typedef
EFI_STATUS
(EFIAPI *EBC_ICACHE_FLUSH)(
  IN EFI_PHYSICAL_ADDRESS       Start,
  IN UINT64                     Length);

typedef
EFI_STATUS
(EFIAPI *EFI_EBC_REGISTER_ICACHE_FLUSH)(
  IN struct _EFI_EBC_PROTOCOL   *This,
  IN EBC_ICACHE_FLUSH           Flush);

typedef
EFI_STATUS
(EFIAPI *EFI_EBC_GET_VERSION)(
  IN struct _EFI_EBC_PROTOCOL   *This,
  IN OUT UINT64                 *Version);

typedef struct _EFI_EBC_PROTOCOL {
  EFI_EBC_CREATE_THUNK          CreateThunk;
  EFI_EBC_UNLOAD_IMAGE          UnloadImage;
  EFI_EBC_REGISTER_ICACHE_FLUSH RegisterICacheFlush;
  EFI_EBC_GET_VERSION           GetVersion;
} EFI_EBC_PROTOCOL;

#endif
#ifndef _EFI_CON_H
#define _EFI_CON_H

/*++

Copyright (c) 1998  Intel Corporation

Module Name:

    eficon.h

Abstract:

    EFI console protocols



Revision History

--*/

//
// Text output protocol
//

#define EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL_GUID \
    { 0x387477c2, 0x69c7, 0x11d2, {0x8e, 0x39, 0x0, 0xa0, 0xc9, 0x69, 0x72, 0x3b} }
#define SIMPLE_TEXT_OUTPUT_PROTOCOL EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL_GUID

INTERFACE_DECL(_SIMPLE_TEXT_OUTPUT_INTERFACE);

typedef
EFI_STATUS
(EFIAPI *EFI_TEXT_RESET) (
    IN struct _SIMPLE_TEXT_OUTPUT_INTERFACE     *This,
    IN BOOLEAN                      ExtendedVerification
    );

typedef
EFI_STATUS
(EFIAPI *EFI_TEXT_OUTPUT_STRING) (
    IN struct _SIMPLE_TEXT_OUTPUT_INTERFACE     *This,
    IN CHAR16                       *String
    );

typedef
EFI_STATUS
(EFIAPI *EFI_TEXT_TEST_STRING) (
    IN struct _SIMPLE_TEXT_OUTPUT_INTERFACE     *This,
    IN CHAR16                       *String
    );

typedef
EFI_STATUS
(EFIAPI *EFI_TEXT_QUERY_MODE) (
    IN struct _SIMPLE_TEXT_OUTPUT_INTERFACE     *This,
    IN UINTN                        ModeNumber,
    OUT UINTN                       *Columns,
    OUT UINTN                       *Rows
    );

typedef
EFI_STATUS
(EFIAPI *EFI_TEXT_SET_MODE) (
    IN struct _SIMPLE_TEXT_OUTPUT_INTERFACE     *This,
    IN UINTN                        ModeNumber
    );

typedef
EFI_STATUS
(EFIAPI *EFI_TEXT_SET_ATTRIBUTE) (
    IN struct _SIMPLE_TEXT_OUTPUT_INTERFACE     *This,
    IN UINTN                        Attribute
    );

#define EFI_BLACK   0x00
#define EFI_BLUE    0x01
#define EFI_GREEN   0x02
#define EFI_CYAN            (EFI_BLUE | EFI_GREEN)
#define EFI_RED     0x04
#define EFI_MAGENTA         (EFI_BLUE | EFI_RED)
#define EFI_BROWN           (EFI_GREEN | EFI_RED)
#define EFI_LIGHTGRAY       (EFI_BLUE | EFI_GREEN | EFI_RED)
#define EFI_BRIGHT  0x08
#define EFI_DARKGRAY        (EFI_BRIGHT)
#define EFI_LIGHTBLUE       (EFI_BLUE | EFI_BRIGHT)
#define EFI_LIGHTGREEN      (EFI_GREEN | EFI_BRIGHT)
#define EFI_LIGHTCYAN       (EFI_CYAN | EFI_BRIGHT)
#define EFI_LIGHTRED        (EFI_RED | EFI_BRIGHT)
#define EFI_LIGHTMAGENTA    (EFI_MAGENTA | EFI_BRIGHT)
#define EFI_YELLOW          (EFI_BROWN | EFI_BRIGHT)
#define EFI_WHITE           (EFI_BLUE | EFI_GREEN | EFI_RED | EFI_BRIGHT)

#define EFI_TEXT_ATTR(f,b)  ((f) | ((b) << 4))

#define EFI_BACKGROUND_BLACK        0x00
#define EFI_BACKGROUND_BLUE         0x10
#define EFI_BACKGROUND_GREEN        0x20
#define EFI_BACKGROUND_CYAN         (EFI_BACKGROUND_BLUE | EFI_BACKGROUND_GREEN)
#define EFI_BACKGROUND_RED          0x40
#define EFI_BACKGROUND_MAGENTA      (EFI_BACKGROUND_BLUE | EFI_BACKGROUND_RED)
#define EFI_BACKGROUND_BROWN        (EFI_BACKGROUND_GREEN | EFI_BACKGROUND_RED)
#define EFI_BACKGROUND_LIGHTGRAY    (EFI_BACKGROUND_BLUE | EFI_BACKGROUND_GREEN | EFI_BACKGROUND_RED)


typedef
EFI_STATUS
(EFIAPI *EFI_TEXT_CLEAR_SCREEN) (
    IN struct _SIMPLE_TEXT_OUTPUT_INTERFACE     *This
    );

typedef
EFI_STATUS
(EFIAPI *EFI_TEXT_SET_CURSOR_POSITION) (
    IN struct _SIMPLE_TEXT_OUTPUT_INTERFACE     *This,
    IN UINTN                        Column,
    IN UINTN                        Row
    );

typedef
EFI_STATUS
(EFIAPI *EFI_TEXT_ENABLE_CURSOR) (
    IN struct _SIMPLE_TEXT_OUTPUT_INTERFACE     *This,
    IN BOOLEAN                      Enable
    );

typedef struct {
    INT32                           MaxMode;
    // current settings
    INT32                           Mode;
    INT32                           Attribute;
    INT32                           CursorColumn;
    INT32                           CursorRow;
    BOOLEAN                         CursorVisible;
} SIMPLE_TEXT_OUTPUT_MODE;

typedef struct _SIMPLE_TEXT_OUTPUT_INTERFACE {
    EFI_TEXT_RESET                  Reset;

    EFI_TEXT_OUTPUT_STRING          OutputString;
    EFI_TEXT_TEST_STRING            TestString;

    EFI_TEXT_QUERY_MODE             QueryMode;
    EFI_TEXT_SET_MODE               SetMode;
    EFI_TEXT_SET_ATTRIBUTE          SetAttribute;

    EFI_TEXT_CLEAR_SCREEN           ClearScreen;
    EFI_TEXT_SET_CURSOR_POSITION    SetCursorPosition;
    EFI_TEXT_ENABLE_CURSOR          EnableCursor;

    // Current mode
    SIMPLE_TEXT_OUTPUT_MODE         *Mode;
} SIMPLE_TEXT_OUTPUT_INTERFACE, EFI_SIMPLE_TEXT_OUT_PROTOCOL;

//
// Define's for required EFI Unicode Box Draw character
//

#define BOXDRAW_HORIZONTAL                  0x2500
#define BOXDRAW_VERTICAL                    0x2502
#define BOXDRAW_DOWN_RIGHT                  0x250c
#define BOXDRAW_DOWN_LEFT                   0x2510
#define BOXDRAW_UP_RIGHT                    0x2514
#define BOXDRAW_UP_LEFT                     0x2518
#define BOXDRAW_VERTICAL_RIGHT              0x251c
#define BOXDRAW_VERTICAL_LEFT               0x2524
#define BOXDRAW_DOWN_HORIZONTAL             0x252c
#define BOXDRAW_UP_HORIZONTAL               0x2534
#define BOXDRAW_VERTICAL_HORIZONTAL         0x253c

#define BOXDRAW_DOUBLE_HORIZONTAL           0x2550
#define BOXDRAW_DOUBLE_VERTICAL             0x2551
#define BOXDRAW_DOWN_RIGHT_DOUBLE           0x2552
#define BOXDRAW_DOWN_DOUBLE_RIGHT           0x2553
#define BOXDRAW_DOUBLE_DOWN_RIGHT           0x2554

#define BOXDRAW_DOWN_LEFT_DOUBLE            0x2555
#define BOXDRAW_DOWN_DOUBLE_LEFT            0x2556
#define BOXDRAW_DOUBLE_DOWN_LEFT            0x2557

#define BOXDRAW_UP_RIGHT_DOUBLE             0x2558
#define BOXDRAW_UP_DOUBLE_RIGHT             0x2559
#define BOXDRAW_DOUBLE_UP_RIGHT             0x255a

#define BOXDRAW_UP_LEFT_DOUBLE              0x255b
#define BOXDRAW_UP_DOUBLE_LEFT              0x255c
#define BOXDRAW_DOUBLE_UP_LEFT              0x255d

#define BOXDRAW_VERTICAL_RIGHT_DOUBLE       0x255e
#define BOXDRAW_VERTICAL_DOUBLE_RIGHT       0x255f
#define BOXDRAW_DOUBLE_VERTICAL_RIGHT       0x2560

#define BOXDRAW_VERTICAL_LEFT_DOUBLE        0x2561
#define BOXDRAW_VERTICAL_DOUBLE_LEFT        0x2562
#define BOXDRAW_DOUBLE_VERTICAL_LEFT        0x2563

#define BOXDRAW_DOWN_HORIZONTAL_DOUBLE      0x2564
#define BOXDRAW_DOWN_DOUBLE_HORIZONTAL      0x2565
#define BOXDRAW_DOUBLE_DOWN_HORIZONTAL      0x2566

#define BOXDRAW_UP_HORIZONTAL_DOUBLE        0x2567
#define BOXDRAW_UP_DOUBLE_HORIZONTAL        0x2568
#define BOXDRAW_DOUBLE_UP_HORIZONTAL        0x2569

#define BOXDRAW_VERTICAL_HORIZONTAL_DOUBLE  0x256a
#define BOXDRAW_VERTICAL_DOUBLE_HORIZONTAL  0x256b
#define BOXDRAW_DOUBLE_VERTICAL_HORIZONTAL  0x256c

//
// EFI Required Block Elements Code Chart
//

#define BLOCKELEMENT_FULL_BLOCK             0x2588
#define BLOCKELEMENT_LIGHT_SHADE            0x2591
//
// EFI Required Geometric Shapes Code Chart
//

#define GEOMETRICSHAPE_UP_TRIANGLE           0x25b2
#define GEOMETRICSHAPE_RIGHT_TRIANGLE        0x25ba
#define GEOMETRICSHAPE_DOWN_TRIANGLE         0x25bc
#define GEOMETRICSHAPE_LEFT_TRIANGLE         0x25c4

//
// EFI Required Arrow shapes
//

#define ARROW_UP                            0x2191
#define ARROW_DOWN                          0x2193

//
// Text input protocol
//

#define EFI_SIMPLE_TEXT_INPUT_PROTOCOL_GUID \
    { 0x387477c1, 0x69c7, 0x11d2, {0x8e, 0x39, 0x0, 0xa0, 0xc9, 0x69, 0x72, 0x3b} }
#define SIMPLE_TEXT_INPUT_PROTOCOL EFI_SIMPLE_TEXT_INPUT_PROTOCOL_GUID

INTERFACE_DECL(_SIMPLE_INPUT_INTERFACE);

typedef struct {
    UINT16                              ScanCode;
    CHAR16                              UnicodeChar;
} EFI_INPUT_KEY;

//
// Baseline unicode control chars
//

#define CHAR_NULL                       0x0000
#define CHAR_BACKSPACE                  0x0008
#define CHAR_TAB                        0x0009
#define CHAR_LINEFEED                   0x000A
#define CHAR_CARRIAGE_RETURN            0x000D

//
// Scan codes for base line keys
//

#define SCAN_NULL                       0x0000
#define SCAN_UP                         0x0001
#define SCAN_DOWN                       0x0002
#define SCAN_RIGHT                      0x0003
#define SCAN_LEFT                       0x0004
#define SCAN_HOME                       0x0005
#define SCAN_END                        0x0006
#define SCAN_INSERT                     0x0007
#define SCAN_DELETE                     0x0008
#define SCAN_PAGE_UP                    0x0009
#define SCAN_PAGE_DOWN                  0x000A
#define SCAN_F1                         0x000B
#define SCAN_F2                         0x000C
#define SCAN_F3                         0x000D
#define SCAN_F4                         0x000E
#define SCAN_F5                         0x000F
#define SCAN_F6                         0x0010
#define SCAN_F7                         0x0011
#define SCAN_F8                         0x0012
#define SCAN_F9                         0x0013
#define SCAN_F10                        0x0014
#define SCAN_F11                        0x0015
#define SCAN_F12                        0x0016
#define SCAN_ESC                        0x0017

typedef
EFI_STATUS
(EFIAPI *EFI_INPUT_RESET) (
    IN struct _SIMPLE_INPUT_INTERFACE   *This,
    IN BOOLEAN                          ExtendedVerification
    );

typedef
EFI_STATUS
(EFIAPI *EFI_INPUT_READ_KEY) (
    IN struct _SIMPLE_INPUT_INTERFACE   *This,
    OUT EFI_INPUT_KEY                   *Key
    );

typedef struct _SIMPLE_INPUT_INTERFACE {
    EFI_INPUT_RESET                     Reset;
    EFI_INPUT_READ_KEY                  ReadKeyStroke;
    EFI_EVENT                           WaitForKey;
} SIMPLE_INPUT_INTERFACE, EFI_SIMPLE_TEXT_IN_PROTOCOL;

#endif

#ifndef _EFI_CONEX_H
#define _EFI_CONEX_H

/*++

Copyright (c) 2020 Kagurazaka Kotori <kagurazakakotori@gmail.com>

Module Name:

    eficonex.h

Abstract:

    EFI console extension protocols

--*/

//
// Simple Text Input Ex Protocol
//

#define EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL_GUID \
    { 0xdd9e7534, 0x7762, 0x4698, {0x8c, 0x14, 0xf5, 0x85, 0x17, 0xa6, 0x25, 0xaa} }

INTERFACE_DECL(_EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL);

typedef UINT8 EFI_KEY_TOGGLE_STATE;

typedef struct EFI_KEY_STATE {
    UINT32                                         KeyShiftState;
    EFI_KEY_TOGGLE_STATE                           KeyToggleState;
} EFI_KEY_STATE;

typedef struct {
    EFI_INPUT_KEY                                  Key;
    EFI_KEY_STATE                                  KeyState;
} EFI_KEY_DATA;

// Shift states
#define EFI_SHIFT_STATE_VALID                      0x80000000
#define EFI_RIGHT_SHIFT_PRESSED                    0x00000001
#define EFI_LEFT_SHIFT_PRESSED                     0x00000002
#define EFI_RIGHT_CONTROL_PRESSED                  0x00000004
#define EFI_LEFT_CONTROL_PRESSED                   0x00000008
#define EFI_RIGHT_ALT_PRESSED                      0x00000010
#define EFI_LEFT_ALT_PRESSED                       0x00000020
#define EFI_RIGHT_LOGO_PRESSED                     0x00000040
#define EFI_LEFT_LOGO_PRESSED                      0x00000080
#define EFI_MENU_KEY_PRESSED                       0x00000100
#define EFI_SYS_REQ_PRESSED                        0x00000200

// Toggle states
#define EFI_TOGGLE_STATE_VALID                     0x80
#define EFI_KEY_STATE_EXPOSED                      0x40
#define EFI_SCROLL_LOCK_ACTIVE                     0x01
#define EFI_NUM_LOCK_ACTIVE                        0x02
#define EFI_CAPS_LOCK_ACTIVE                       0x04

typedef
EFI_STATUS
(EFIAPI *EFI_INPUT_RESET_EX) (
    IN struct _EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL   *This,
    IN BOOLEAN                                     ExtendedVerification
    );

typedef
EFI_STATUS
(EFIAPI *EFI_INPUT_READ_KEY_EX) (
    IN struct _EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL   *This,
    OUT EFI_KEY_DATA                               *KeyData
    );

typedef
EFI_STATUS
(EFIAPI *EFI_SET_STATE) (
    IN struct _EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL   *This,
    IN EFI_KEY_TOGGLE_STATE                        *KeyToggleState
    );

typedef
EFI_STATUS
(EFIAPI *EFI_KEY_NOTIFY_FUNCTION) (
    IN EFI_KEY_DATA                                *KeyData
    );

typedef
EFI_STATUS
(EFIAPI *EFI_REGISTER_KEYSTROKE_NOTIFY) (
    IN struct _EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL   *This,
    IN EFI_KEY_DATA                                *KeyData,
    IN EFI_KEY_NOTIFY_FUNCTION                     KeyNotificationFunction,
    OUT VOID                                       **NotifyHandle
    );

typedef
EFI_STATUS
(EFIAPI *EFI_UNREGISTER_KEYSTROKE_NOTIFY) (
    IN struct _EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL   *This,
    IN VOID                                        *NotificationHandle
    );

typedef struct _EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL{
    EFI_INPUT_RESET_EX                             Reset;
    EFI_INPUT_READ_KEY_EX                          ReadKeyStrokeEx;
    EFI_EVENT                                      WaitForKeyEx;
    EFI_SET_STATE                                  SetState;
    EFI_REGISTER_KEYSTROKE_NOTIFY                  RegisterKeyNotify;
    EFI_UNREGISTER_KEYSTROKE_NOTIFY                UnregisterKeyNotify;
} EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL;

#endif
#ifndef _EFI_SER_H
#define _EFI_SER_H

/*++

Copyright (c) 1998  Intel Corporation

Module Name:

    efiser.h

Abstract:

    EFI serial protocol

Revision History

--*/

//
// Serial protocol
//

#define EFI_SERIAL_IO_PROTOCOL_GUID \
    { 0xBB25CF6F, 0xF1D4, 0x11D2, {0x9A, 0x0C, 0x00, 0x90, 0x27, 0x3F, 0xC1, 0xFD} }
#define SERIAL_IO_PROTOCOL EFI_SERIAL_IO_PROTOCOL_GUID

INTERFACE_DECL(_EFI_SERIAL_IO_PROTOCOL);

typedef enum {
    DefaultParity,
    NoParity,
    EvenParity,
    OddParity,
    MarkParity,
    SpaceParity
} EFI_PARITY_TYPE;

typedef enum {
    DefaultStopBits,
    OneStopBit,         // 1 stop bit
    OneFiveStopBits,    // 1.5 stop bits
    TwoStopBits         // 2 stop bits
} EFI_STOP_BITS_TYPE;

#define EFI_SERIAL_CLEAR_TO_SEND                   0x0010  // RO
#define EFI_SERIAL_DATA_SET_READY                  0x0020  // RO
#define EFI_SERIAL_RING_INDICATE                   0x0040  // RO
#define EFI_SERIAL_CARRIER_DETECT                  0x0080  // RO
#define EFI_SERIAL_REQUEST_TO_SEND                 0x0002  // WO
#define EFI_SERIAL_DATA_TERMINAL_READY             0x0001  // WO
#define EFI_SERIAL_INPUT_BUFFER_EMPTY              0x0100  // RO
#define EFI_SERIAL_OUTPUT_BUFFER_EMPTY             0x0200  // RO
#define EFI_SERIAL_HARDWARE_LOOPBACK_ENABLE        0x1000  // RW
#define EFI_SERIAL_SOFTWARE_LOOPBACK_ENABLE        0x2000  // RW
#define EFI_SERIAL_HARDWARE_FLOW_CONTROL_ENABLE    0x4000  // RW

typedef
EFI_STATUS
(EFIAPI *EFI_SERIAL_RESET) (
    IN struct _EFI_SERIAL_IO_PROTOCOL  *This
    );

typedef
EFI_STATUS
(EFIAPI *EFI_SERIAL_SET_ATTRIBUTES) (
    IN struct _EFI_SERIAL_IO_PROTOCOL  *This,
    IN UINT64                          BaudRate,
    IN UINT32                          ReceiveFifoDepth,
    IN UINT32                          Timeout,
    IN EFI_PARITY_TYPE                 Parity,
    IN UINT8                           DataBits,
    IN EFI_STOP_BITS_TYPE              StopBits
    );

typedef
EFI_STATUS
(EFIAPI *EFI_SERIAL_SET_CONTROL_BITS) (
    IN struct _EFI_SERIAL_IO_PROTOCOL  *This,
    IN UINT32                          Control
    );

typedef
EFI_STATUS
(EFIAPI *EFI_SERIAL_GET_CONTROL_BITS) (
    IN struct _EFI_SERIAL_IO_PROTOCOL  *This,
    OUT UINT32                         *Control
    );

typedef
EFI_STATUS
(EFIAPI *EFI_SERIAL_WRITE) (
    IN struct _EFI_SERIAL_IO_PROTOCOL  *This,
    IN OUT UINTN                       *BufferSize,
    IN VOID                            *Buffer
    );

typedef
EFI_STATUS
(EFIAPI *EFI_SERIAL_READ) (
    IN struct _EFI_SERIAL_IO_PROTOCOL  *This,
    IN OUT UINTN                       *BufferSize,
    OUT VOID                           *Buffer
    );

typedef struct {
    UINT32                  ControlMask;

    // current Attributes
    UINT32                  Timeout;
    UINT64                  BaudRate;
    UINT32                  ReceiveFifoDepth;
    UINT32                  DataBits;
    UINT32                  Parity;
    UINT32                  StopBits;
} SERIAL_IO_MODE;

#define SERIAL_IO_INTERFACE_REVISION    0x00010000

typedef struct _EFI_SERIAL_IO_PROTOCOL {
    UINT32                       Revision;
    EFI_SERIAL_RESET             Reset;
    EFI_SERIAL_SET_ATTRIBUTES    SetAttributes;
    EFI_SERIAL_SET_CONTROL_BITS  SetControl;
    EFI_SERIAL_GET_CONTROL_BITS  GetControl;
    EFI_SERIAL_WRITE             Write;
    EFI_SERIAL_READ              Read;

    SERIAL_IO_MODE               *Mode;
} EFI_SERIAL_IO_PROTOCOL;

typedef struct _EFI_SERIAL_IO_PROTOCOL _SERIAL_IO_INTERFACE;
typedef EFI_SERIAL_IO_PROTOCOL SERIAL_IO_INTERFACE;

#endif

#ifndef _EFI_NII_H
#define _EFI_NII_H

/*++
Copyright (c) 2000  Intel Corporation

Module name:
    efi_nii.h

Abstract:

Revision history:
    2000-Feb-18 M(f)J   GUID updated.
                Structure order changed for machine word alignment.
                Added StringId[4] to structure.

    2000-Feb-14 M(f)J   Genesis.
--*/

#define EFI_NETWORK_INTERFACE_IDENTIFIER_PROTOCOL_GUID \
    { 0xE18541CD, 0xF755, 0x4f73, {0x92, 0x8D, 0x64, 0x3C, 0x8A, 0x79, 0xB2, 0x29} }

#define EFI_NETWORK_INTERFACE_IDENTIFIER_PROTOCOL_REVISION  0x00010000
#define EFI_NETWORK_INTERFACE_IDENTIFIER_INTERFACE_REVISION EFI_NETWORK_INTERFACE_IDENTIFIER_PROTOCOL_REVISION

typedef enum {
    EfiNetworkInterfaceUndi = 1
} EFI_NETWORK_INTERFACE_TYPE;

typedef struct _EFI_NETWORK_INTERFACE_IDENTIFIER_PROTOCOL {

    UINT64 Revision;
    // Revision of the network interface identifier protocol interface.

    UINT64 ID;
    // Address of the first byte of the identifying structure for this
    // network interface.  This is set to zero if there is no structure.
    //
    // For PXE/UNDI this is the first byte of the !PXE structure.

    UINT64 ImageAddr;
    // Address of the UNrelocated driver/ROM image.  This is set
    // to zero if there is no driver/ROM image.
    //
    // For 16-bit UNDI, this is the first byte of the option ROM in
    // upper memory.
    //
    // For 32/64-bit S/W UNDI, this is the first byte of the EFI ROM
    // image.
    //
    // For H/W UNDI, this is set to zero.

    UINT32 ImageSize;
    // Size of the UNrelocated driver/ROM image of this network interface.
    // This is set to zero if there is no driver/ROM image.

    CHAR8 StringId[4];
    // 4 char ASCII string to go in class identifier (option 60) in DHCP
    // and Boot Server discover packets.
    // For EfiNetworkInterfaceUndi this field is "UNDI".
    // For EfiNetworkInterfaceSnp this field is "SNPN".

    UINT8 Type;
    UINT8 MajorVer;
    UINT8 MinorVer;
    // Information to be placed into the PXE DHCP and Discover packets.
    // This is the network interface type and version number that will
    // be placed into DHCP option 94 (client network interface identifier).
    BOOLEAN Ipv6Supported;
    UINT8   IfNum;	// interface number to be used with pxeid structure
} EFI_NETWORK_INTERFACE_IDENTIFIER_PROTOCOL, EFI_NETWORK_INTERFACE_IDENTIFIER_INTERFACE;

// Note: Because it conflicted with the EDK2 struct name, the
// 'EFI_NETWORK_INTERFACE_IDENTIFIER_PROTOCOL' GUID definition,
// from older versions of gnu-efi, is now obsoleted.
// Use 'EFI_NETWORK_INTERFACE_IDENTIFIER_PROTOCOL_GUID' instead.

#endif // _EFI_NII_H
#ifndef _EFIPXEBC_H
#define _EFIPXEBC_H

/*++

Copyright (c) 1998  Intel Corporation

Module Name:

    efipxebc.h

Abstract:

    EFI PXE Base Code Protocol



Revision History

--*/

//
// PXE Base Code protocol
//

#define EFI_PXE_BASE_CODE_PROTOCOL_GUID \
    { 0x03c4e603, 0xac28, 0x11d3, {0x9a, 0x2d, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d} }

INTERFACE_DECL(_EFI_PXE_BASE_CODE_PROTOCOL);

#define DEFAULT_TTL 4
#define DEFAULT_ToS 0
//
// Address definitions
//

typedef union {
    UINT32      Addr[4];
    EFI_IPv4_ADDRESS    v4;
    EFI_IPv6_ADDRESS    v6;
} EFI_IP_ADDRESS;

typedef UINT16 EFI_PXE_BASE_CODE_UDP_PORT;

//
// Packet definitions
//

typedef struct {
    UINT8                           BootpOpcode;
    UINT8                           BootpHwType;
    UINT8                           BootpHwAddrLen;
    UINT8                           BootpGateHops;
    UINT32                          BootpIdent;
    UINT16                          BootpSeconds;
    UINT16                          BootpFlags;
    UINT8                           BootpCiAddr[4];
    UINT8                           BootpYiAddr[4];
    UINT8                           BootpSiAddr[4];
    UINT8                           BootpGiAddr[4];
    UINT8                           BootpHwAddr[16];
    UINT8                           BootpSrvName[64];
    UINT8                           BootpBootFile[128];
    UINT32                          DhcpMagik;
    UINT8                           DhcpOptions[56];
} EFI_PXE_BASE_CODE_DHCPV4_PACKET;

typedef struct {
    UINT32                          MessageType:8;
    UINT32                          TransactionId:24;
    UINT8                           DhcpOptions[1024];
} EFI_PXE_BASE_CODE_DHCPV6_PACKET;

typedef union {
    UINT8                               Raw[1472];
    EFI_PXE_BASE_CODE_DHCPV4_PACKET     Dhcpv4;
    EFI_PXE_BASE_CODE_DHCPV6_PACKET     Dhcpv6;
} EFI_PXE_BASE_CODE_PACKET;

typedef struct {
    UINT8                   Type;
    UINT8                   Code;
    UINT16                  Checksum;
    union {
        UINT32              reserved;
        UINT32              Mtu;
        UINT32              Pointer;
        struct {
            UINT16          Identifier;
            UINT16          Sequence;
        } Echo;
    } u;
    UINT8                   Data[494];
} EFI_PXE_BASE_CODE_ICMP_ERROR;

typedef struct {
    UINT8                   ErrorCode;
    CHAR8                   ErrorString[127];
} EFI_PXE_BASE_CODE_TFTP_ERROR;

//
// IP Receive Filter definitions
//
#define EFI_PXE_BASE_CODE_MAX_IPCNT             8
typedef struct {
    UINT8                       Filters;
    UINT8                       IpCnt;
    UINT16                      reserved;
    EFI_IP_ADDRESS              IpList[EFI_PXE_BASE_CODE_MAX_IPCNT];
} EFI_PXE_BASE_CODE_IP_FILTER;

#define EFI_PXE_BASE_CODE_IP_FILTER_STATION_IP             0x0001
#define EFI_PXE_BASE_CODE_IP_FILTER_BROADCAST              0x0002
#define EFI_PXE_BASE_CODE_IP_FILTER_PROMISCUOUS            0x0004
#define EFI_PXE_BASE_CODE_IP_FILTER_PROMISCUOUS_MULTICAST  0x0008

//
// ARP Cache definitions
//

typedef struct {
    EFI_IP_ADDRESS       IpAddr;
    EFI_MAC_ADDRESS      MacAddr;
} EFI_PXE_BASE_CODE_ARP_ENTRY;

typedef struct {
    EFI_IP_ADDRESS       IpAddr;
    EFI_IP_ADDRESS       SubnetMask;
    EFI_IP_ADDRESS       GwAddr;
} EFI_PXE_BASE_CODE_ROUTE_ENTRY;

//
// UDP definitions
//

#define EFI_PXE_BASE_CODE_UDP_OPFLAGS_ANY_SRC_IP    0x0001
#define EFI_PXE_BASE_CODE_UDP_OPFLAGS_ANY_SRC_PORT  0x0002
#define EFI_PXE_BASE_CODE_UDP_OPFLAGS_ANY_DEST_IP   0x0004
#define EFI_PXE_BASE_CODE_UDP_OPFLAGS_ANY_DEST_PORT 0x0008
#define EFI_PXE_BASE_CODE_UDP_OPFLAGS_USE_FILTER    0x0010
#define EFI_PXE_BASE_CODE_UDP_OPFLAGS_MAY_FRAGMENT  0x0020

//
// Discover() definitions
//

#define EFI_PXE_BASE_CODE_BOOT_TYPE_BOOTSTRAP           0
#define EFI_PXE_BASE_CODE_BOOT_TYPE_MS_WINNT_RIS        1
#define EFI_PXE_BASE_CODE_BOOT_TYPE_INTEL_LCM           2
#define EFI_PXE_BASE_CODE_BOOT_TYPE_DOSUNDI             3
#define EFI_PXE_BASE_CODE_BOOT_TYPE_NEC_ESMPRO          4
#define EFI_PXE_BASE_CODE_BOOT_TYPE_IBM_WSoD            5
#define EFI_PXE_BASE_CODE_BOOT_TYPE_IBM_LCCM            6
#define EFI_PXE_BASE_CODE_BOOT_TYPE_CA_UNICENTER_TNG    7
#define EFI_PXE_BASE_CODE_BOOT_TYPE_HP_OPENVIEW         8
#define EFI_PXE_BASE_CODE_BOOT_TYPE_ALTIRIS_9           9
#define EFI_PXE_BASE_CODE_BOOT_TYPE_ALTIRIS_10          10
#define EFI_PXE_BASE_CODE_BOOT_TYPE_ALTIRIS_11          11
#define EFI_PXE_BASE_CODE_BOOT_TYPE_NOT_USED_12         12
#define EFI_PXE_BASE_CODE_BOOT_TYPE_REDHAT_INSTALL      13
#define EFI_PXE_BASE_CODE_BOOT_TYPE_REDHAT_BOOT         14
#define EFI_PXE_BASE_CODE_BOOT_TYPE_REMBO               15
#define EFI_PXE_BASE_CODE_BOOT_TYPE_BEOBOOT             16
//
// 17 through 32767 are reserved
// 32768 through 65279 are for vendor use
// 65280 through 65534 are reserved
//
#define EFI_PXE_BASE_CODE_BOOT_TYPE_PXETEST             65535

#define EFI_PXE_BASE_CODE_BOOT_LAYER_MASK               0x7FFF
#define EFI_PXE_BASE_CODE_BOOT_LAYER_INITIAL            0x0000


typedef struct {
    UINT16                      Type;
    BOOLEAN                     AcceptAnyResponse;
    UINT8                       Reserved;
    EFI_IP_ADDRESS              IpAddr;
} EFI_PXE_BASE_CODE_SRVLIST;

typedef struct {
    BOOLEAN                     UseMCast;
    BOOLEAN                     UseBCast;
    BOOLEAN                     UseUCast;
    BOOLEAN                     MustUseList;
    EFI_IP_ADDRESS              ServerMCastIp;
    UINT16                      IpCnt;
    EFI_PXE_BASE_CODE_SRVLIST   SrvList[1];
} EFI_PXE_BASE_CODE_DISCOVER_INFO;

//
// Mtftp() definitions
//

typedef enum {
    EFI_PXE_BASE_CODE_TFTP_FIRST,
    EFI_PXE_BASE_CODE_TFTP_GET_FILE_SIZE,
    EFI_PXE_BASE_CODE_TFTP_READ_FILE,
    EFI_PXE_BASE_CODE_TFTP_WRITE_FILE,
    EFI_PXE_BASE_CODE_TFTP_READ_DIRECTORY,
    EFI_PXE_BASE_CODE_MTFTP_GET_FILE_SIZE,
    EFI_PXE_BASE_CODE_MTFTP_READ_FILE,
    EFI_PXE_BASE_CODE_MTFTP_READ_DIRECTORY,
    EFI_PXE_BASE_CODE_MTFTP_LAST
} EFI_PXE_BASE_CODE_TFTP_OPCODE;

typedef struct {
    EFI_IP_ADDRESS   MCastIp;
    EFI_PXE_BASE_CODE_UDP_PORT  CPort;
    EFI_PXE_BASE_CODE_UDP_PORT  SPort;
    UINT16                      ListenTimeout;
    UINT16                      TransmitTimeout;
} EFI_PXE_BASE_CODE_MTFTP_INFO;

//
// PXE Base Code Mode structure
//

#define EFI_PXE_BASE_CODE_MAX_ARP_ENTRIES       8
#define EFI_PXE_BASE_CODE_MAX_ROUTE_ENTRIES     8

typedef struct {
    BOOLEAN                         Started;
    BOOLEAN                         Ipv6Available;
    BOOLEAN                         Ipv6Supported;
    BOOLEAN                         UsingIpv6;
    BOOLEAN                         BisSupported;
    BOOLEAN                         BisDetected;
    BOOLEAN                         AutoArp;
    BOOLEAN                         SendGUID;
    BOOLEAN                         DhcpDiscoverValid;
    BOOLEAN                         DhcpAckReceived;
    BOOLEAN                         ProxyOfferReceived;
    BOOLEAN                         PxeDiscoverValid;
    BOOLEAN                         PxeReplyReceived;
    BOOLEAN                         PxeBisReplyReceived;
    BOOLEAN                         IcmpErrorReceived;
    BOOLEAN                         TftpErrorReceived;
    BOOLEAN                         MakeCallbacks;
    UINT8                           TTL;
    UINT8                           ToS;
    EFI_IP_ADDRESS                  StationIp;
    EFI_IP_ADDRESS                  SubnetMask;
    EFI_PXE_BASE_CODE_PACKET        DhcpDiscover;
    EFI_PXE_BASE_CODE_PACKET        DhcpAck;
    EFI_PXE_BASE_CODE_PACKET        ProxyOffer;
    EFI_PXE_BASE_CODE_PACKET        PxeDiscover;
    EFI_PXE_BASE_CODE_PACKET        PxeReply;
    EFI_PXE_BASE_CODE_PACKET        PxeBisReply;
    EFI_PXE_BASE_CODE_IP_FILTER     IpFilter;
    UINT32                          ArpCacheEntries;
    EFI_PXE_BASE_CODE_ARP_ENTRY     ArpCache[EFI_PXE_BASE_CODE_MAX_ARP_ENTRIES];
    UINT32                          RouteTableEntries;
    EFI_PXE_BASE_CODE_ROUTE_ENTRY   RouteTable[EFI_PXE_BASE_CODE_MAX_ROUTE_ENTRIES];
    EFI_PXE_BASE_CODE_ICMP_ERROR    IcmpError;
    EFI_PXE_BASE_CODE_TFTP_ERROR    TftpError;
} EFI_PXE_BASE_CODE_MODE;

//
// PXE Base Code Interface Function definitions
//

typedef
EFI_STATUS
(EFIAPI *EFI_PXE_BASE_CODE_START) (
    IN struct _EFI_PXE_BASE_CODE_PROTOCOL  *This,
    IN BOOLEAN                             UseIpv6
    );

typedef
EFI_STATUS
(EFIAPI *EFI_PXE_BASE_CODE_STOP) (
    IN struct _EFI_PXE_BASE_CODE_PROTOCOL  *This
    );

typedef
EFI_STATUS
(EFIAPI *EFI_PXE_BASE_CODE_DHCP) (
    IN struct _EFI_PXE_BASE_CODE_PROTOCOL  *This,
    IN BOOLEAN                             SortOffers
    );

typedef
EFI_STATUS
(EFIAPI *EFI_PXE_BASE_CODE_DISCOVER) (
    IN struct _EFI_PXE_BASE_CODE_PROTOCOL   *This,
    IN UINT16                               Type,
    IN UINT16                               *Layer,
    IN BOOLEAN                              UseBis,
    IN OUT EFI_PXE_BASE_CODE_DISCOVER_INFO  *Info   OPTIONAL
    );

typedef
EFI_STATUS
(EFIAPI *EFI_PXE_BASE_CODE_MTFTP) (
    IN struct _EFI_PXE_BASE_CODE_PROTOCOL  *This,
    IN EFI_PXE_BASE_CODE_TFTP_OPCODE       Operation,
    IN OUT VOID                            *BufferPtr  OPTIONAL,
    IN BOOLEAN                             Overwrite,
    IN OUT UINT64                          *BufferSize,
    IN UINTN                               *BlockSize  OPTIONAL,
    IN EFI_IP_ADDRESS                      *ServerIp,
    IN UINT8                               *Filename,
    IN EFI_PXE_BASE_CODE_MTFTP_INFO        *Info       OPTIONAL,
    IN BOOLEAN                             DontUseBuffer
    );

typedef
EFI_STATUS
(EFIAPI *EFI_PXE_BASE_CODE_UDP_WRITE) (
    IN struct _EFI_PXE_BASE_CODE_PROTOCOL  *This,
    IN UINT16                              OpFlags,
    IN EFI_IP_ADDRESS                      *DestIp,
    IN EFI_PXE_BASE_CODE_UDP_PORT          *DestPort,
    IN EFI_IP_ADDRESS                      *GatewayIp,  OPTIONAL
    IN EFI_IP_ADDRESS                      *SrcIp,      OPTIONAL
    IN OUT EFI_PXE_BASE_CODE_UDP_PORT      *SrcPort,    OPTIONAL
    IN UINTN                               *HeaderSize, OPTIONAL
    IN VOID                                *HeaderPtr,  OPTIONAL
    IN UINTN                               *BufferSize,
    IN VOID                                *BufferPtr
    );

typedef
EFI_STATUS
(EFIAPI *EFI_PXE_BASE_CODE_UDP_READ) (
    IN struct _EFI_PXE_BASE_CODE_PROTOCOL  *This,
    IN UINT16                              OpFlags,
    IN OUT EFI_IP_ADDRESS                  *DestIp,      OPTIONAL
    IN OUT EFI_PXE_BASE_CODE_UDP_PORT      *DestPort,    OPTIONAL
    IN OUT EFI_IP_ADDRESS                  *SrcIp,       OPTIONAL
    IN OUT EFI_PXE_BASE_CODE_UDP_PORT      *SrcPort,     OPTIONAL
    IN UINTN                               *HeaderSize,  OPTIONAL
    IN VOID                                *HeaderPtr,   OPTIONAL
    IN OUT UINTN                           *BufferSize,
    IN VOID                                *BufferPtr
    );

typedef
EFI_STATUS
(EFIAPI *EFI_PXE_BASE_CODE_SET_IP_FILTER) (
    IN struct _EFI_PXE_BASE_CODE_PROTOCOL  *This,
    IN EFI_PXE_BASE_CODE_IP_FILTER         *NewFilter
    );

typedef
EFI_STATUS
(EFIAPI *EFI_PXE_BASE_CODE_ARP) (
    IN struct _EFI_PXE_BASE_CODE_PROTOCOL  *This,
    IN EFI_IP_ADDRESS                      *IpAddr,
    IN EFI_MAC_ADDRESS                     *MacAddr      OPTIONAL
    );

typedef
EFI_STATUS
(EFIAPI *EFI_PXE_BASE_CODE_SET_PARAMETERS) (
    IN struct _EFI_PXE_BASE_CODE_PROTOCOL  *This,
    IN BOOLEAN                             *NewAutoArp,    OPTIONAL
    IN BOOLEAN                             *NewSendGUID,   OPTIONAL
    IN UINT8                               *NewTTL,        OPTIONAL
    IN UINT8                               *NewToS,        OPTIONAL
    IN BOOLEAN                             *NewMakeCallback    OPTIONAL
    );

typedef
EFI_STATUS
(EFIAPI *EFI_PXE_BASE_CODE_SET_STATION_IP) (
    IN struct _EFI_PXE_BASE_CODE_PROTOCOL  *This,
    IN EFI_IP_ADDRESS                      *NewStationIp,  OPTIONAL
    IN EFI_IP_ADDRESS                      *NewSubnetMask  OPTIONAL
    );

typedef
EFI_STATUS
(EFIAPI *EFI_PXE_BASE_CODE_SET_PACKETS) (
    IN struct _EFI_PXE_BASE_CODE_PROTOCOL  *This,
    BOOLEAN                                *NewDhcpDiscoverValid,  OPTIONAL
    BOOLEAN                                *NewDhcpAckReceived,    OPTIONAL
    BOOLEAN                                *NewProxyOfferReceived, OPTIONAL
    BOOLEAN                                *NewPxeDiscoverValid,   OPTIONAL
    BOOLEAN                                *NewPxeReplyReceived,   OPTIONAL
    BOOLEAN                                *NewPxeBisReplyReceived,OPTIONAL
    IN EFI_PXE_BASE_CODE_PACKET            *NewDhcpDiscover, OPTIONAL
    IN EFI_PXE_BASE_CODE_PACKET            *NewDhcpAck,      OPTIONAL
    IN EFI_PXE_BASE_CODE_PACKET            *NewProxyOffer,   OPTIONAL
    IN EFI_PXE_BASE_CODE_PACKET            *NewPxeDiscover,  OPTIONAL
    IN EFI_PXE_BASE_CODE_PACKET            *NewPxeReply,     OPTIONAL
    IN EFI_PXE_BASE_CODE_PACKET            *NewPxeBisReply   OPTIONAL
    );

//
// PXE Base Code Protocol structure
//

#define EFI_PXE_BASE_CODE_PROTOCOL_REVISION  0x00010000
#define EFI_PXE_BASE_CODE_INTERFACE_REVISION EFI_PXE_BASE_CODE_PROTOCOL_REVISION

typedef struct _EFI_PXE_BASE_CODE_PROTOCOL {
    UINT64                              Revision;
    EFI_PXE_BASE_CODE_START             Start;
    EFI_PXE_BASE_CODE_STOP              Stop;
    EFI_PXE_BASE_CODE_DHCP              Dhcp;
    EFI_PXE_BASE_CODE_DISCOVER          Discover;
    EFI_PXE_BASE_CODE_MTFTP             Mtftp;
    EFI_PXE_BASE_CODE_UDP_WRITE         UdpWrite;
    EFI_PXE_BASE_CODE_UDP_READ          UdpRead;
    EFI_PXE_BASE_CODE_SET_IP_FILTER     SetIpFilter;
    EFI_PXE_BASE_CODE_ARP               Arp;
    EFI_PXE_BASE_CODE_SET_PARAMETERS    SetParameters;
    EFI_PXE_BASE_CODE_SET_STATION_IP    SetStationIp;
    EFI_PXE_BASE_CODE_SET_PACKETS       SetPackets;
    EFI_PXE_BASE_CODE_MODE              *Mode;
} EFI_PXE_BASE_CODE_PROTOCOL;

// Note: Because it conflicted with the EDK2 struct name, the
// 'EFI_PXE_BASE_CODE_PROTOCOL' GUID definition, from older
// versions of gnu-efi, is now obsoleted.
// Use 'EFI_PXE_BASE_CODE_PROTOCOL_GUID' instead.

typedef struct _EFI_PXE_BASE_CODE_PROTOCOL _EFI_PXE_BASE_CODE;
typedef struct _EFI_PXE_BASE_CODE_PROTOCOL EFI_PXE_BASE_CODE;

//
// Call Back Definitions
//

#define EFI_PXE_BASE_CODE_CALLBACK_PROTOCOL_GUID \
    { 0x245dca21, 0xfb7b, 0x11d3, {0x8f, 0x01, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b} }

//
// Revision Number
//

#define EFI_PXE_BASE_CODE_CALLBACK_PROTOCOL_REVISION  0x00010000
#define EFI_PXE_BASE_CODE_CALLBACK_INTERFACE_REVISION EFI_PXE_BASE_CODE_CALLBACK_PROTOCOL_REVISION

INTERFACE_DECL(_EFI_PXE_BASE_CODE_CALLBACK_PROTOCOL);

typedef enum {
    EFI_PXE_BASE_CODE_FUNCTION_FIRST,
    EFI_PXE_BASE_CODE_FUNCTION_DHCP,
    EFI_PXE_BASE_CODE_FUNCTION_DISCOVER,
    EFI_PXE_BASE_CODE_FUNCTION_MTFTP,
    EFI_PXE_BASE_CODE_FUNCTION_UDP_WRITE,
    EFI_PXE_BASE_CODE_FUNCTION_UDP_READ,
    EFI_PXE_BASE_CODE_FUNCTION_ARP,
    EFI_PXE_BASE_CODE_FUNCTION_IGMP,
    EFI_PXE_BASE_CODE_PXE_FUNCTION_LAST
} EFI_PXE_BASE_CODE_FUNCTION;

typedef enum {
    EFI_PXE_BASE_CODE_CALLBACK_STATUS_FIRST,
    EFI_PXE_BASE_CODE_CALLBACK_STATUS_CONTINUE,
    EFI_PXE_BASE_CODE_CALLBACK_STATUS_ABORT,
    EFI_PXE_BASE_CODE_CALLBACK_STATUS_LAST
} EFI_PXE_BASE_CODE_CALLBACK_STATUS;

typedef
EFI_PXE_BASE_CODE_CALLBACK_STATUS
(EFIAPI *EFI_PXE_CALLBACK) (
    IN struct _EFI_PXE_BASE_CODE_CALLBACK_PROTOCOL  *This,
    IN EFI_PXE_BASE_CODE_FUNCTION                   Function,
    IN BOOLEAN                                      Received,
    IN UINT32                                       PacketLen,
    IN EFI_PXE_BASE_CODE_PACKET                     *Packet     OPTIONAL
    );

typedef struct _EFI_PXE_BASE_CODE_CALLBACK_PROTOCOL {
    UINT64                      Revision;
    EFI_PXE_CALLBACK            Callback;
} EFI_PXE_BASE_CODE_CALLBACK_PROTOCOL;

// Note: Because it conflicted with the EDK2 struct name, the
// 'EFI_PXE_BASE_CODE_CALLBACK_PROTOCOL' GUID definition, from
// older versions of gnu-efi, is now obsoleted.
// Use 'EFI_PXE_BASE_CODE_CALLBACK_PROTOCOL_GUID' instead.

typedef struct _EFI_PXE_BASE_CODE_CALLBACK_PROTOCOL _EFI_PXE_BASE_CODE_CALLBACK;
typedef EFI_PXE_BASE_CODE_CALLBACK_PROTOCOL EFI_PXE_BASE_CODE_CALLBACK;

#endif /* _EFIPXEBC_H */
#ifndef _EFINET_H
#define _EFINET_H


/*++
Copyright (c) 1999  Intel Corporation

Module Name:
    efinet.h

Abstract:
    EFI Simple Network protocol

Revision History
--*/


///////////////////////////////////////////////////////////////////////////////
//
//      Simple Network Protocol
//

#define EFI_SIMPLE_NETWORK_PROTOCOL_GUID \
    { 0xA19832B9, 0xAC25, 0x11D3, {0x9A, 0x2D, 0x00, 0x90, 0x27, 0x3F, 0xC1, 0x4D} }

INTERFACE_DECL(_EFI_SIMPLE_NETWORK_PROTOCOL);

///////////////////////////////////////////////////////////////////////////////
//

typedef struct {
    //
    // Total number of frames received.  Includes frames with errors and
    // dropped frames.
    //
    UINT64  RxTotalFrames;

    //
    // Number of valid frames received and copied into receive buffers.
    //
    UINT64  RxGoodFrames;

    //
    // Number of frames below the minimum length for the media.
    // This would be <64 for ethernet.
    //
    UINT64  RxUndersizeFrames;

    //
    // Number of frames longer than the maxminum length for the
    // media.  This would be >1500 for ethernet.
    //
    UINT64  RxOversizeFrames;

    //
    // Valid frames that were dropped because receive buffers were full.
    //
    UINT64  RxDroppedFrames;

    //
    // Number of valid unicast frames received and not dropped.
    //
    UINT64  RxUnicastFrames;

    //
    // Number of valid broadcast frames received and not dropped.
    //
    UINT64  RxBroadcastFrames;

    //
    // Number of valid mutlicast frames received and not dropped.
    //
    UINT64  RxMulticastFrames;

    //
    // Number of frames w/ CRC or alignment errors.
    //
    UINT64  RxCrcErrorFrames;

    //
    // Total number of bytes received.  Includes frames with errors
    // and dropped frames.
    //
    UINT64  RxTotalBytes;

    //
    // Transmit statistics.
    //
    UINT64  TxTotalFrames;
    UINT64  TxGoodFrames;
    UINT64  TxUndersizeFrames;
    UINT64  TxOversizeFrames;
    UINT64  TxDroppedFrames;
    UINT64  TxUnicastFrames;
    UINT64  TxBroadcastFrames;
    UINT64  TxMulticastFrames;
    UINT64  TxCrcErrorFrames;
    UINT64  TxTotalBytes;

    //
    // Number of collisions detection on this subnet.
    //
    UINT64  Collisions;

    //
    // Number of frames destined for unsupported protocol.
    //
    UINT64  UnsupportedProtocol;

} EFI_NETWORK_STATISTICS;

///////////////////////////////////////////////////////////////////////////////
//

typedef enum {
    EfiSimpleNetworkStopped,
    EfiSimpleNetworkStarted,
    EfiSimpleNetworkInitialized,
    EfiSimpleNetworkMaxState
} EFI_SIMPLE_NETWORK_STATE;

///////////////////////////////////////////////////////////////////////////////
//

#define EFI_SIMPLE_NETWORK_RECEIVE_UNICAST               0x01
#define EFI_SIMPLE_NETWORK_RECEIVE_MULTICAST             0x02
#define EFI_SIMPLE_NETWORK_RECEIVE_BROADCAST             0x04
#define EFI_SIMPLE_NETWORK_RECEIVE_PROMISCUOUS           0x08
#define EFI_SIMPLE_NETWORK_RECEIVE_PROMISCUOUS_MULTICAST 0x10

///////////////////////////////////////////////////////////////////////////////
//

#define EFI_SIMPLE_NETWORK_RECEIVE_INTERRUPT        0x01
#define EFI_SIMPLE_NETWORK_TRANSMIT_INTERRUPT       0x02
#define EFI_SIMPLE_NETWORK_COMMAND_INTERRUPT        0x04
#define EFI_SIMPLE_NETWORK_SOFTWARE_INTERRUPT       0x08

///////////////////////////////////////////////////////////////////////////////
//
#define MAX_MCAST_FILTER_CNT    16
typedef struct {
    UINT32                      State;
    UINT32                      HwAddressSize;
    UINT32                      MediaHeaderSize;
    UINT32                      MaxPacketSize;
    UINT32                      NvRamSize;
    UINT32                      NvRamAccessSize;
    UINT32                      ReceiveFilterMask;
    UINT32                      ReceiveFilterSetting;
    UINT32                      MaxMCastFilterCount;
    UINT32                      MCastFilterCount;
    EFI_MAC_ADDRESS             MCastFilter[MAX_MCAST_FILTER_CNT];
    EFI_MAC_ADDRESS             CurrentAddress;
    EFI_MAC_ADDRESS             BroadcastAddress;
    EFI_MAC_ADDRESS             PermanentAddress;
    UINT8                       IfType;
    BOOLEAN                     MacAddressChangeable;
    BOOLEAN                     MultipleTxSupported;
    BOOLEAN                     MediaPresentSupported;
    BOOLEAN                     MediaPresent;
} EFI_SIMPLE_NETWORK_MODE;

///////////////////////////////////////////////////////////////////////////////
//

typedef
EFI_STATUS
(EFIAPI *EFI_SIMPLE_NETWORK_START) (
    IN struct _EFI_SIMPLE_NETWORK_PROTOCOL  *This
);

///////////////////////////////////////////////////////////////////////////////
//

typedef
EFI_STATUS
(EFIAPI *EFI_SIMPLE_NETWORK_STOP) (
    IN struct _EFI_SIMPLE_NETWORK_PROTOCOL  *This
);

///////////////////////////////////////////////////////////////////////////////
//

typedef
EFI_STATUS
(EFIAPI *EFI_SIMPLE_NETWORK_INITIALIZE) (
    IN struct _EFI_SIMPLE_NETWORK_PROTOCOL  *This,
    IN UINTN                                ExtraRxBufferSize  OPTIONAL,
    IN UINTN                                ExtraTxBufferSize  OPTIONAL
);

///////////////////////////////////////////////////////////////////////////////
//

typedef
EFI_STATUS
(EFIAPI *EFI_SIMPLE_NETWORK_RESET) (
    IN struct _EFI_SIMPLE_NETWORK_PROTOCOL  *This,
    IN BOOLEAN                              ExtendedVerification
);

///////////////////////////////////////////////////////////////////////////////
//

typedef
EFI_STATUS
(EFIAPI *EFI_SIMPLE_NETWORK_SHUTDOWN) (
    IN struct _EFI_SIMPLE_NETWORK_PROTOCOL  *This
);

///////////////////////////////////////////////////////////////////////////////
//

typedef
EFI_STATUS
(EFIAPI *EFI_SIMPLE_NETWORK_RECEIVE_FILTERS) (
    IN struct _EFI_SIMPLE_NETWORK_PROTOCOL  *This,
    IN UINT32                               Enable,
    IN UINT32                               Disable,
    IN BOOLEAN                              ResetMCastFilter,
    IN UINTN                                MCastFilterCnt     OPTIONAL,
    IN EFI_MAC_ADDRESS                      *MCastFilter       OPTIONAL
);

///////////////////////////////////////////////////////////////////////////////
//

typedef
EFI_STATUS
(EFIAPI *EFI_SIMPLE_NETWORK_STATION_ADDRESS) (
    IN struct _EFI_SIMPLE_NETWORK_PROTOCOL  *This,
    IN BOOLEAN                              Reset,
    IN EFI_MAC_ADDRESS                      *New      OPTIONAL
);

///////////////////////////////////////////////////////////////////////////////
//

typedef
EFI_STATUS
(EFIAPI *EFI_SIMPLE_NETWORK_STATISTICS) (
    IN struct _EFI_SIMPLE_NETWORK_PROTOCOL  *This,
    IN BOOLEAN                              Reset,
    IN OUT UINTN                            *StatisticsSize   OPTIONAL,
    OUT EFI_NETWORK_STATISTICS              *StatisticsTable  OPTIONAL
);

///////////////////////////////////////////////////////////////////////////////
//

typedef
EFI_STATUS
(EFIAPI *EFI_SIMPLE_NETWORK_MCAST_IP_TO_MAC) (
    IN struct _EFI_SIMPLE_NETWORK_PROTOCOL  *This,
    IN BOOLEAN                              IPv6,
    IN EFI_IP_ADDRESS                       *IP,
    OUT EFI_MAC_ADDRESS                     *MAC
);

///////////////////////////////////////////////////////////////////////////////
//

typedef
EFI_STATUS
(EFIAPI *EFI_SIMPLE_NETWORK_NVDATA) (
    IN struct _EFI_SIMPLE_NETWORK_PROTOCOL  *This,
    IN BOOLEAN                              ReadWrite,
    IN UINTN                                Offset,
    IN UINTN                                BufferSize,
    IN OUT VOID                             *Buffer
);

///////////////////////////////////////////////////////////////////////////////
//

typedef
EFI_STATUS
(EFIAPI *EFI_SIMPLE_NETWORK_GET_STATUS) (
    IN struct _EFI_SIMPLE_NETWORK_PROTOCOL  *This,
    OUT UINT32                              *InterruptStatus  OPTIONAL,
    OUT VOID                                **TxBuf           OPTIONAL
);

///////////////////////////////////////////////////////////////////////////////
//

typedef
EFI_STATUS
(EFIAPI *EFI_SIMPLE_NETWORK_TRANSMIT) (
    IN struct _EFI_SIMPLE_NETWORK_PROTOCOL  *This,
    IN UINTN                                HeaderSize,
    IN UINTN                                BufferSize,
    IN VOID                                 *Buffer,
    IN EFI_MAC_ADDRESS                      *SrcAddr     OPTIONAL,
    IN EFI_MAC_ADDRESS                      *DestAddr    OPTIONAL,
    IN UINT16                               *Protocol    OPTIONAL
);

///////////////////////////////////////////////////////////////////////////////
//

typedef
EFI_STATUS
(EFIAPI *EFI_SIMPLE_NETWORK_RECEIVE) (
    IN struct _EFI_SIMPLE_NETWORK_PROTOCOL  *This,
    OUT UINTN                               *HeaderSize  OPTIONAL,
    IN OUT UINTN                            *BufferSize,
    OUT VOID                                *Buffer,
    OUT EFI_MAC_ADDRESS                     *SrcAddr     OPTIONAL,
    OUT EFI_MAC_ADDRESS                     *DestAddr    OPTIONAL,
    OUT UINT16                              *Protocol    OPTIONAL
);

///////////////////////////////////////////////////////////////////////////////
//

#define EFI_SIMPLE_NETWORK_PROTOCOL_REVISION  0x00010000
#define EFI_SIMPLE_NETWORK_INTERFACE_REVISION EFI_SIMPLE_NETWORK_PROTOCOL_REVISION

typedef struct _EFI_SIMPLE_NETWORK_PROTOCOL {
    UINT64                              Revision;
    EFI_SIMPLE_NETWORK_START            Start;
    EFI_SIMPLE_NETWORK_STOP             Stop;
    EFI_SIMPLE_NETWORK_INITIALIZE       Initialize;
    EFI_SIMPLE_NETWORK_RESET            Reset;
    EFI_SIMPLE_NETWORK_SHUTDOWN         Shutdown;
    EFI_SIMPLE_NETWORK_RECEIVE_FILTERS  ReceiveFilters;
    EFI_SIMPLE_NETWORK_STATION_ADDRESS  StationAddress;
    EFI_SIMPLE_NETWORK_STATISTICS       Statistics;
    EFI_SIMPLE_NETWORK_MCAST_IP_TO_MAC  MCastIpToMac;
    EFI_SIMPLE_NETWORK_NVDATA           NvData;
    EFI_SIMPLE_NETWORK_GET_STATUS       GetStatus;
    EFI_SIMPLE_NETWORK_TRANSMIT         Transmit;
    EFI_SIMPLE_NETWORK_RECEIVE          Receive;
    EFI_EVENT                           WaitForPacket;
    EFI_SIMPLE_NETWORK_MODE             *Mode;
} EFI_SIMPLE_NETWORK_PROTOCOL;

// Note: Because it conflicted with the EDK2 struct name, the
// 'EFI_SIMPLE_NETWORK_PROTOCOL' GUID definition, from older
// versions of gnu-efi, is now obsoleted.
// Use 'EFI_SIMPLE_NETWORK_PROTOCOL_GUID' instead.

typedef struct _EFI_SIMPLE_NETWORK_PROTOCOL _EFI_SIMPLE_NETWORK;
typedef EFI_SIMPLE_NETWORK_PROTOCOL EFI_SIMPLE_NETWORK;

#endif /* _EFINET_H */
#ifndef _EFI_API_H
#define _EFI_API_H

/*++

Copyright (c) 1998  Intel Corporation

Module Name:

    efiapi.h

Abstract:

    Global EFI runtime & boot service interfaces




Revision History

--*/

//
// EFI Specification Revision
//

#define EFI_SPECIFICATION_MAJOR_REVISION 1
#define EFI_SPECIFICATION_MINOR_REVISION 02

//
// Declare forward referenced data structures
//

INTERFACE_DECL(_EFI_SYSTEM_TABLE);

//
// EFI Memory
//

typedef
EFI_STATUS
(EFIAPI *EFI_ALLOCATE_PAGES) (
    IN EFI_ALLOCATE_TYPE            Type,
    IN EFI_MEMORY_TYPE              MemoryType,
    IN UINTN                        NoPages,
    OUT EFI_PHYSICAL_ADDRESS        *Memory
    );

typedef
EFI_STATUS
(EFIAPI *EFI_FREE_PAGES) (
    IN EFI_PHYSICAL_ADDRESS         Memory,
    IN UINTN                        NoPages
    );

typedef
EFI_STATUS
(EFIAPI *EFI_GET_MEMORY_MAP) (
    IN OUT UINTN                    *MemoryMapSize,
    IN OUT EFI_MEMORY_DESCRIPTOR    *MemoryMap,
    OUT UINTN                       *MapKey,
    OUT UINTN                       *DescriptorSize,
    OUT UINT32                      *DescriptorVersion
    );

#define NextMemoryDescriptor(Ptr,Size)  ((EFI_MEMORY_DESCRIPTOR *) (((UINT8 *) Ptr) + Size))


typedef
EFI_STATUS
(EFIAPI *EFI_ALLOCATE_POOL) (
    IN EFI_MEMORY_TYPE              PoolType,
    IN UINTN                        Size,
    OUT VOID                        **Buffer
    );

typedef
EFI_STATUS
(EFIAPI *EFI_FREE_POOL) (
    IN VOID                         *Buffer
    );

typedef 
EFI_STATUS
(EFIAPI *EFI_SET_VIRTUAL_ADDRESS_MAP) (
    IN UINTN                        MemoryMapSize,
    IN UINTN                        DescriptorSize,
    IN UINT32                       DescriptorVersion,
    IN EFI_MEMORY_DESCRIPTOR        *VirtualMap
    );


#define EFI_OPTIONAL_PTR            0x00000001
#define EFI_INTERNAL_FNC            0x00000002      // Pointer to internal runtime fnc
#define EFI_INTERNAL_PTR            0x00000004      // Pointer to internal runtime data


typedef 
EFI_STATUS
(EFIAPI *EFI_CONVERT_POINTER) (
    IN UINTN                        DebugDisposition,
    IN OUT VOID                     **Address
    );


//
// EFI Events
//

#define EVT_TIMER                           0x80000000
#define EVT_RUNTIME                         0x40000000
#define EVT_RUNTIME_CONTEXT                 0x20000000

#define EVT_NOTIFY_WAIT                     0x00000100
#define EVT_NOTIFY_SIGNAL                   0x00000200

#define EVT_SIGNAL_EXIT_BOOT_SERVICES       0x00000201
#define EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE   0x60000202

#define EVT_EFI_SIGNAL_MASK                 0x000000FF
#define EVT_EFI_SIGNAL_MAX                  4

#define EFI_EVENT_TIMER                         EVT_TIMER
#define EFI_EVENT_RUNTIME                       EVT_RUNTIME
#define EFI_EVENT_RUNTIME_CONTEXT               EVT_RUNTIME_CONTEXT
#define EFI_EVENT_NOTIFY_WAIT                   EVT_NOTIFY_WAIT
#define EFI_EVENT_NOTIFY_SIGNAL                 EVT_NOTIFY_SIGNAL
#define EFI_EVENT_SIGNAL_EXIT_BOOT_SERVICES     EVT_SIGNAL_EXIT_BOOT_SERVICES
#define EFI_EVENT_SIGNAL_VIRTUAL_ADDRESS_CHANGE EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE
#define EFI_EVENT_EFI_SIGNAL_MASK               EVT_EFI_SIGNAL_MASK
#define EFI_EVENT_EFI_SIGNAL_MAX                EVT_EFI_SIGNAL_MAX


typedef
VOID
(EFIAPI *EFI_EVENT_NOTIFY) (
    IN EFI_EVENT                Event,
    IN VOID                     *Context
    );

typedef
EFI_STATUS
(EFIAPI *EFI_CREATE_EVENT) (
    IN UINT32                       Type,
    IN EFI_TPL                      NotifyTpl,
    IN EFI_EVENT_NOTIFY             NotifyFunction,
    IN VOID                         *NotifyContext,
    OUT EFI_EVENT                   *Event
    );

typedef enum {
    TimerCancel,
    TimerPeriodic,
    TimerRelative,
    TimerTypeMax
} EFI_TIMER_DELAY;

typedef
EFI_STATUS
(EFIAPI *EFI_SET_TIMER) (
    IN EFI_EVENT                Event,
    IN EFI_TIMER_DELAY          Type,
    IN UINT64                   TriggerTime
    );

typedef
EFI_STATUS
(EFIAPI *EFI_SIGNAL_EVENT) (
    IN EFI_EVENT                Event
    );

typedef 
EFI_STATUS
(EFIAPI *EFI_WAIT_FOR_EVENT) (
    IN UINTN                    NumberOfEvents,
    IN EFI_EVENT                *Event,
    OUT UINTN                   *Index
    );

typedef
EFI_STATUS
(EFIAPI *EFI_CLOSE_EVENT) (
    IN EFI_EVENT                Event
    );

typedef
EFI_STATUS
(EFIAPI *EFI_CHECK_EVENT) (
    IN EFI_EVENT                Event
    );

//
// Task priority level
//

#define TPL_APPLICATION       4
#define TPL_CALLBACK          8
#define TPL_NOTIFY           16
#define TPL_HIGH_LEVEL       31
#define EFI_TPL_APPLICATION  TPL_APPLICATION
#define EFI_TPL_CALLBACK     TPL_CALLBACK
#define EFI_TPL_NOTIFY       TPL_NOTIFY
#define EFI_TPL_HIGH_LEVEL   TPL_HIGH_LEVEL
typedef
EFI_TPL
(EFIAPI *EFI_RAISE_TPL) (
    IN EFI_TPL      NewTpl
    );

typedef
VOID
(EFIAPI *EFI_RESTORE_TPL) (
    IN EFI_TPL      OldTpl
    );


//
// EFI platform varibles
//

#define EFI_GLOBAL_VARIABLE     \
    { 0x8BE4DF61, 0x93CA, 0x11d2, {0xAA, 0x0D, 0x00, 0xE0, 0x98, 0x03, 0x2B, 0x8C} }

// Variable attributes
#define EFI_VARIABLE_NON_VOLATILE                          0x00000001
#define EFI_VARIABLE_BOOTSERVICE_ACCESS                    0x00000002
#define EFI_VARIABLE_RUNTIME_ACCESS                        0x00000004
#define EFI_VARIABLE_HARDWARE_ERROR_RECORD                 0x00000008
#define EFI_VARIABLE_AUTHENTICATED_WRITE_ACCESS            0x00000010
#define EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS 0x00000020
#define EFI_VARIABLE_APPEND_WRITE                          0x00000040

// Variable size limitation
#define EFI_MAXIMUM_VARIABLE_SIZE           1024

typedef
EFI_STATUS
(EFIAPI *EFI_GET_VARIABLE) (
    IN CHAR16                       *VariableName,
    IN EFI_GUID                     *VendorGuid,
    OUT UINT32                      *Attributes OPTIONAL,
    IN OUT UINTN                    *DataSize,
    OUT VOID                        *Data
    );

typedef
EFI_STATUS
(EFIAPI *EFI_GET_NEXT_VARIABLE_NAME) (
    IN OUT UINTN                    *VariableNameSize,
    IN OUT CHAR16                   *VariableName,
    IN OUT EFI_GUID                 *VendorGuid
    );


typedef
EFI_STATUS
(EFIAPI *EFI_SET_VARIABLE) (
    IN CHAR16                       *VariableName,
    IN EFI_GUID                     *VendorGuid,
    IN UINT32                       Attributes,
    IN UINTN                        DataSize,
    IN VOID                         *Data
    );


//
// EFI Time
//

typedef struct {
        UINT32                      Resolution;     // 1e-6 parts per million
        UINT32                      Accuracy;       // hertz
        BOOLEAN                     SetsToZero;     // Set clears sub-second time
} EFI_TIME_CAPABILITIES;


typedef
EFI_STATUS
(EFIAPI *EFI_GET_TIME) (
    OUT EFI_TIME                    *Time,
    OUT EFI_TIME_CAPABILITIES       *Capabilities OPTIONAL
    );

typedef
EFI_STATUS
(EFIAPI *EFI_SET_TIME) (
    IN EFI_TIME                     *Time
    );

typedef
EFI_STATUS
(EFIAPI *EFI_GET_WAKEUP_TIME) (
    OUT BOOLEAN                     *Enabled,
    OUT BOOLEAN                     *Pending,
    OUT EFI_TIME                    *Time
    );

typedef
EFI_STATUS
(EFIAPI *EFI_SET_WAKEUP_TIME) (
    IN BOOLEAN                      Enable,
    IN EFI_TIME                     *Time OPTIONAL
    );


//
// Image functions
//


// PE32+ Subsystem type for EFI images

#if !defined(IMAGE_SUBSYSTEM_EFI_APPLICATION)
#define IMAGE_SUBSYSTEM_EFI_APPLICATION             10
#define IMAGE_SUBSYSTEM_EFI_BOOT_SERVICE_DRIVER     11
#define IMAGE_SUBSYSTEM_EFI_RUNTIME_DRIVER          12
#endif

// PE32+ Machine type for EFI images

#if !defined(EFI_IMAGE_MACHINE_IA32)
#define EFI_IMAGE_MACHINE_IA32      0x014c
#endif

#if !defined(EFI_IMAGE_MACHINE_IA64)
#define EFI_IMAGE_MACHINE_IA64      0x0200
#endif

#if !defined(EFI_IMAGE_MACHINE_EBC)
#define EFI_IMAGE_MACHINE_EBC      0x0EBC
#endif

#if !defined(EFI_IMAGE_MACHINE_X64)
#define EFI_IMAGE_MACHINE_X64       0x8664
#endif

#if !defined(EFI_IMAGE_MACHINE_ARMTHUMB_MIXED)
#define EFI_IMAGE_MACHINE_ARMTHUMB_MIXED 0x01C2
#endif

#if !defined(EFI_IMAGE_MACHINE_AARCH64)
#define EFI_IMAGE_MACHINE_AARCH64   0xAA64
#endif

#if !defined(EFI_IMAGE_MACHINE_RISCV32)
#define EFI_IMAGE_MACHINE_RISCV32   0x5032
#endif

#if !defined(EFI_IMAGE_MACHINE_RISCV64)
#define EFI_IMAGE_MACHINE_RISCV64   0x5064
#endif

#if !defined(EFI_IMAGE_MACHINE_RISCV128)
#define EFI_IMAGE_MACHINE_RISCV128  0x5128
#endif

// Image Entry prototype

typedef 
EFI_STATUS
(EFIAPI *EFI_IMAGE_ENTRY_POINT) (
    IN EFI_HANDLE                   ImageHandle,
    IN struct _EFI_SYSTEM_TABLE     *SystemTable
    );

typedef 
EFI_STATUS
(EFIAPI *EFI_IMAGE_LOAD) (
    IN BOOLEAN                      BootPolicy,
    IN EFI_HANDLE                   ParentImageHandle,
    IN EFI_DEVICE_PATH              *FilePath,
    IN VOID                         *SourceBuffer   OPTIONAL,
    IN UINTN                        SourceSize,
    OUT EFI_HANDLE                  *ImageHandle
    );

typedef 
EFI_STATUS
(EFIAPI *EFI_IMAGE_START) (
    IN EFI_HANDLE                   ImageHandle,
    OUT UINTN                       *ExitDataSize,
    OUT CHAR16                      **ExitData  OPTIONAL
    );

typedef
EFI_STATUS
(EFIAPI *EFI_EXIT) (
    IN EFI_HANDLE                   ImageHandle,
    IN EFI_STATUS                   ExitStatus,
    IN UINTN                        ExitDataSize,
    IN CHAR16                       *ExitData OPTIONAL
    );


// Image handle
/*#define LOADED_IMAGE_PROTOCOL      \
    { 0x5B1B31A1, 0x9562, 0x11d2, {0x8E, 0x3F, 0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3B} }

#define EFI_IMAGE_INFORMATION_REVISION      0x1000
typedef struct {
    UINT32                          Revision;
    EFI_HANDLE                      ParentHandle;
    struct _EFI_SYSTEM_TABLE        *SystemTable;

    // Source location of image
    EFI_HANDLE                      DeviceHandle;
    EFI_DEVICE_PATH                 *FilePath;
    VOID                            *Reserved;

    // Images load options
    UINT32                          LoadOptionsSize;
    VOID                            *LoadOptions;

    // Location of where image was loaded
    VOID                            *ImageBase;
    UINT64                          ImageSize;
    EFI_MEMORY_TYPE                 ImageCodeType;
    EFI_MEMORY_TYPE                 ImageDataType;

    // If the driver image supports a dynamic unload request
    EFI_IMAGE_UNLOAD                Unload;

} EFI_LOADED_IMAGE;*/


typedef
EFI_STATUS
(EFIAPI *EFI_EXIT_BOOT_SERVICES) (
    IN EFI_HANDLE                   ImageHandle,
    IN UINTN                        MapKey
    );

//
// Misc
//


typedef
EFI_STATUS
(EFIAPI *EFI_STALL) (
    IN UINTN                    Microseconds
    );

typedef
EFI_STATUS
(EFIAPI *EFI_SET_WATCHDOG_TIMER) (
    IN UINTN                    Timeout,
    IN UINT64                   WatchdogCode,
    IN UINTN                    DataSize,
    IN CHAR16                   *WatchdogData OPTIONAL
    );

typedef
EFI_STATUS
(EFIAPI *EFI_CONNECT_CONTROLLER) (
    IN EFI_HANDLE               ControllerHandle,
    IN EFI_HANDLE               *DriverImageHandle OPTIONAL,
    IN EFI_DEVICE_PATH          *RemainingDevicePath OPTIONAL,
    IN BOOLEAN                  Recursive
    );

typedef
EFI_STATUS
(EFIAPI *EFI_DISCONNECT_CONTROLLER) (
    IN EFI_HANDLE               ControllerHandle,
    IN EFI_HANDLE               DriverImageHandle OPTIONAL,
    IN EFI_HANDLE               ChildHandle OPTIONAL
    );

#define EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL  0x00000001
#define EFI_OPEN_PROTOCOL_GET_PROTOCOL        0x00000002
#define EFI_OPEN_PROTOCOL_TEST_PROTOCOL       0x00000004
#define EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER 0x00000008
#define EFI_OPEN_PROTOCOL_BY_DRIVER           0x00000010
#define EFI_OPEN_PROTOCOL_EXCLUSIVE           0x00000020

typedef
EFI_STATUS
(EFIAPI *EFI_OPEN_PROTOCOL) (
    IN EFI_HANDLE               Handle,
    IN EFI_GUID                 *Protocol,
    OUT VOID                    **Interface OPTIONAL,
    IN EFI_HANDLE               AgentHandle,
    IN EFI_HANDLE               ControllerHandle,
    IN UINT32                   Attributes
    );

typedef
EFI_STATUS
(EFIAPI *EFI_CLOSE_PROTOCOL) (
    IN EFI_HANDLE               Handle,
    IN EFI_GUID                 *Protocol,
    IN EFI_HANDLE               AgentHandle,
    IN EFI_HANDLE               ControllerHandle
    );

typedef struct {
    EFI_HANDLE                  AgentHandle;
    EFI_HANDLE                  ControllerHandle;
    UINT32                      Attributes;
    UINT32                      OpenCount;
} EFI_OPEN_PROTOCOL_INFORMATION_ENTRY;

typedef
EFI_STATUS
(EFIAPI *EFI_OPEN_PROTOCOL_INFORMATION) (
    IN EFI_HANDLE               Handle,
    IN EFI_GUID                 *Protocol,
    OUT EFI_OPEN_PROTOCOL_INFORMATION_ENTRY **EntryBuffer,
    OUT UINTN                   *EntryCount
    );

typedef
EFI_STATUS
(EFIAPI *EFI_PROTOCOLS_PER_HANDLE) (
    IN EFI_HANDLE               Handle,
    OUT EFI_GUID                ***ProtocolBuffer,
    OUT UINTN                   *ProtocolBufferCount
    );

typedef enum {
    AllHandles,
    ByRegisterNotify,
    ByProtocol
} EFI_LOCATE_SEARCH_TYPE;

typedef
EFI_STATUS
(EFIAPI *EFI_LOCATE_HANDLE_BUFFER) (
    IN EFI_LOCATE_SEARCH_TYPE   SearchType,
    IN EFI_GUID                 *Protocol OPTIONAL,
    IN VOID                     *SearchKey OPTIONAL,
    IN OUT UINTN                *NoHandles,
    OUT EFI_HANDLE              **Buffer
    );

typedef
EFI_STATUS
(EFIAPI *EFI_LOCATE_PROTOCOL) (
    IN EFI_GUID                 *Protocol,
    IN VOID                     *Registration OPTIONAL,
    OUT VOID                    **Interface
    );

typedef
EFI_STATUS
(EFIAPI *EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES) (
    IN OUT EFI_HANDLE           *Handle,
    ...
    );

typedef
EFI_STATUS
(EFIAPI *EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES) (
    IN OUT EFI_HANDLE           Handle,
    ...
    );

typedef
EFI_STATUS
(EFIAPI *EFI_CALCULATE_CRC32) (
    IN VOID                     *Data,
    IN UINTN                    DataSize,
    OUT UINT32                  *Crc32
    );

typedef
VOID
(EFIAPI *EFI_COPY_MEM) (
    IN VOID                     *Destination,
    IN VOID                     *Source,
    IN UINTN                    Length
    );

typedef
VOID
(EFIAPI *EFI_SET_MEM) (
    IN VOID                     *Buffer,
    IN UINTN                    Size,
    IN UINT8                    Value
    );


typedef
EFI_STATUS
(EFIAPI *EFI_CREATE_EVENT_EX) (
    IN UINT32                   Type,
    IN EFI_TPL                  NotifyTpl,
    IN EFI_EVENT_NOTIFY         NotifyFunction OPTIONAL,
    IN const VOID               *NotifyContext OPTIONAL,
    IN const EFI_GUID           *EventGroup OPTIONAL,
    OUT EFI_EVENT               *Event
    );

typedef enum {
    EfiResetCold,
    EfiResetWarm,
    EfiResetShutdown
} EFI_RESET_TYPE;

typedef
EFI_STATUS
(EFIAPI *EFI_RESET_SYSTEM) (
    IN EFI_RESET_TYPE           ResetType,
    IN EFI_STATUS               ResetStatus,
    IN UINTN                    DataSize,
    IN CHAR16                   *ResetData OPTIONAL
    );

typedef
EFI_STATUS
(EFIAPI *EFI_GET_NEXT_MONOTONIC_COUNT) (
    OUT UINT64                  *Count
    );

typedef
EFI_STATUS
(EFIAPI *EFI_GET_NEXT_HIGH_MONO_COUNT) (
    OUT UINT32                  *HighCount
    );

typedef struct {
    UINT64                      Length;
    union {
        EFI_PHYSICAL_ADDRESS    DataBlock;
       EFI_PHYSICAL_ADDRESS    ContinuationPointer;
    } Union;
} EFI_CAPSULE_BLOCK_DESCRIPTOR;

typedef struct {
    EFI_GUID                    CapsuleGuid;
    UINT32                      HeaderSize;
    UINT32                      Flags;
    UINT32                      CapsuleImageSize;
} EFI_CAPSULE_HEADER;

#define CAPSULE_FLAGS_PERSIST_ACROSS_RESET    0x00010000
#define CAPSULE_FLAGS_POPULATE_SYSTEM_TABLE   0x00020000
#define CAPSULE_FLAGS_INITIATE_RESET          0x00040000

typedef
EFI_STATUS
(EFIAPI *EFI_UPDATE_CAPSULE) (
    IN EFI_CAPSULE_HEADER       **CapsuleHeaderArray,
    IN UINTN                    CapsuleCount,
    IN EFI_PHYSICAL_ADDRESS     ScatterGatherList OPTIONAL
    );

typedef
EFI_STATUS
(EFIAPI *EFI_QUERY_CAPSULE_CAPABILITIES) (
    IN  EFI_CAPSULE_HEADER       **CapsuleHeaderArray,
    IN  UINTN                    CapsuleCount,
    OUT UINT64                   *MaximumCapsuleSize,
    OUT EFI_RESET_TYPE           *ResetType
    );

typedef
EFI_STATUS
(EFIAPI *EFI_QUERY_VARIABLE_INFO) (
    IN  UINT32                  Attributes,
    OUT UINT64                  *MaximumVariableStorageSize,
    OUT UINT64                  *RemainingVariableStorageSize,
    OUT UINT64                  *MaximumVariableSize
    );

//
// Protocol handler functions
//

typedef enum {
    EFI_NATIVE_INTERFACE,
    EFI_PCODE_INTERFACE
} EFI_INTERFACE_TYPE;

typedef
EFI_STATUS
(EFIAPI *EFI_INSTALL_PROTOCOL_INTERFACE) (
    IN OUT EFI_HANDLE           *Handle,
    IN EFI_GUID                 *Protocol,
    IN EFI_INTERFACE_TYPE       InterfaceType,
    IN VOID                     *Interface
    );

typedef
EFI_STATUS
(EFIAPI *EFI_REINSTALL_PROTOCOL_INTERFACE) (
    IN EFI_HANDLE               Handle,
    IN EFI_GUID                 *Protocol,
    IN VOID                     *OldInterface,
    IN VOID                     *NewInterface
    );

typedef
EFI_STATUS
(EFIAPI *EFI_UNINSTALL_PROTOCOL_INTERFACE) (
    IN EFI_HANDLE               Handle,
    IN EFI_GUID                 *Protocol,
    IN VOID                     *Interface
    );

typedef
EFI_STATUS
(EFIAPI *EFI_HANDLE_PROTOCOL) (
    IN EFI_HANDLE               Handle,
    IN EFI_GUID                 *Protocol,
    OUT VOID                    **Interface
    );

typedef
EFI_STATUS 
(EFIAPI *EFI_REGISTER_PROTOCOL_NOTIFY) (
    IN EFI_GUID                 *Protocol,
    IN EFI_EVENT                Event,
    OUT VOID                    **Registration
    );

typedef
EFI_STATUS
(EFIAPI *EFI_LOCATE_HANDLE) (
    IN EFI_LOCATE_SEARCH_TYPE   SearchType,
    IN EFI_GUID                 *Protocol OPTIONAL,
    IN VOID                     *SearchKey OPTIONAL,
    IN OUT UINTN                *BufferSize,
    OUT EFI_HANDLE              *Buffer
    );

typedef
EFI_STATUS
(EFIAPI *EFI_LOCATE_DEVICE_PATH) (
    IN EFI_GUID                 *Protocol,
    IN OUT EFI_DEVICE_PATH      **DevicePath,
    OUT EFI_HANDLE              *Device
    );

typedef
EFI_STATUS
(EFIAPI *EFI_INSTALL_CONFIGURATION_TABLE) (
    IN EFI_GUID                 *Guid,
    IN VOID                     *Table
    );

typedef
EFI_STATUS
(EFIAPI *EFI_RESERVED_SERVICE) (
    );

//
// Standard EFI table header
//

typedef struct _EFI_TABLE_HEADER {
    UINT64                      Signature;
    UINT32                      Revision;
    UINT32                      HeaderSize;
    UINT32                      CRC32;
    UINT32                      Reserved;
} EFI_TABLE_HEADER;


//
// EFI Runtime Serivces Table
//

#define EFI_RUNTIME_SERVICES_SIGNATURE  0x56524553544e5552
#define EFI_RUNTIME_SERVICES_REVISION   (EFI_SPECIFICATION_MAJOR_REVISION<<16) | (EFI_SPECIFICATION_MINOR_REVISION)

typedef struct  {
    EFI_TABLE_HEADER                Hdr;

    //
    // Time services
    //

    EFI_GET_TIME                    GetTime;
    EFI_SET_TIME                    SetTime;
    EFI_GET_WAKEUP_TIME             GetWakeupTime;
    EFI_SET_WAKEUP_TIME             SetWakeupTime;

    //
    // Virtual memory services
    //

    EFI_SET_VIRTUAL_ADDRESS_MAP     SetVirtualAddressMap;
    EFI_CONVERT_POINTER             ConvertPointer;

    //
    // Variable serviers
    //

    EFI_GET_VARIABLE                GetVariable;
    EFI_GET_NEXT_VARIABLE_NAME      GetNextVariableName;
    EFI_SET_VARIABLE                SetVariable;

    //
    // Misc
    //

    EFI_GET_NEXT_HIGH_MONO_COUNT    GetNextHighMonotonicCount;
    EFI_RESET_SYSTEM                ResetSystem;

    EFI_UPDATE_CAPSULE              UpdateCapsule;
    EFI_QUERY_CAPSULE_CAPABILITIES  QueryCapsuleCapabilities;
    EFI_QUERY_VARIABLE_INFO         QueryVariableInfo;
} EFI_RUNTIME_SERVICES;


//
// EFI Boot Services Table
//

#define EFI_BOOT_SERVICES_SIGNATURE     0x56524553544f4f42
#define EFI_BOOT_SERVICES_REVISION      (EFI_SPECIFICATION_MAJOR_REVISION<<16) | (EFI_SPECIFICATION_MINOR_REVISION)

typedef struct _EFI_BOOT_SERVICES {

    EFI_TABLE_HEADER                Hdr;

    //
    // Task priority functions
    //

    EFI_RAISE_TPL                   RaiseTPL;
    EFI_RESTORE_TPL                 RestoreTPL;

    //
    // Memory functions
    //

    EFI_ALLOCATE_PAGES              AllocatePages;
    EFI_FREE_PAGES                  FreePages;
    EFI_GET_MEMORY_MAP              GetMemoryMap;
    EFI_ALLOCATE_POOL               AllocatePool;
    EFI_FREE_POOL                   FreePool;

    //
    // Event & timer functions
    //

    EFI_CREATE_EVENT                CreateEvent;
    EFI_SET_TIMER                   SetTimer;
    EFI_WAIT_FOR_EVENT              WaitForEvent;
    EFI_SIGNAL_EVENT                SignalEvent;
    EFI_CLOSE_EVENT                 CloseEvent;
    EFI_CHECK_EVENT                 CheckEvent;

    //
    // Protocol handler functions
    //

    EFI_INSTALL_PROTOCOL_INTERFACE  InstallProtocolInterface;
    EFI_REINSTALL_PROTOCOL_INTERFACE ReinstallProtocolInterface;
    EFI_UNINSTALL_PROTOCOL_INTERFACE UninstallProtocolInterface;
    EFI_HANDLE_PROTOCOL             HandleProtocol;
    EFI_HANDLE_PROTOCOL             PCHandleProtocol;
    EFI_REGISTER_PROTOCOL_NOTIFY    RegisterProtocolNotify;
    EFI_LOCATE_HANDLE               LocateHandle;
    EFI_LOCATE_DEVICE_PATH          LocateDevicePath;
    EFI_INSTALL_CONFIGURATION_TABLE InstallConfigurationTable;

    //
    // Image functions
    //

    EFI_IMAGE_LOAD                  LoadImage;
    EFI_IMAGE_START                 StartImage;
    EFI_EXIT                        Exit;
    EFI_IMAGE_UNLOAD                UnloadImage;
    EFI_EXIT_BOOT_SERVICES          ExitBootServices;

    //
    // Misc functions
    //

    EFI_GET_NEXT_MONOTONIC_COUNT    GetNextMonotonicCount;
    EFI_STALL                       Stall;
    EFI_SET_WATCHDOG_TIMER          SetWatchdogTimer;

    //
    // DriverSupport Services
    //

    EFI_CONNECT_CONTROLLER          ConnectController;
    EFI_DISCONNECT_CONTROLLER       DisconnectController;

    //
    // Open and Close Protocol Services
    //
    EFI_OPEN_PROTOCOL               OpenProtocol;
    EFI_CLOSE_PROTOCOL              CloseProtocol;
    EFI_OPEN_PROTOCOL_INFORMATION   OpenProtocolInformation;

    //
    // Library Services
    //
    EFI_PROTOCOLS_PER_HANDLE        ProtocolsPerHandle;
    EFI_LOCATE_HANDLE_BUFFER        LocateHandleBuffer;
    EFI_LOCATE_PROTOCOL             LocateProtocol;
    EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES InstallMultipleProtocolInterfaces;
    EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES UninstallMultipleProtocolInterfaces;

    //
    // 32-bit CRC Services
    //
    EFI_CALCULATE_CRC32             CalculateCrc32;

    //
    // Misc Services
    //
    EFI_COPY_MEM                    CopyMem;
    EFI_SET_MEM                     SetMem;
    EFI_CREATE_EVENT_EX             CreateEventEx;
} EFI_BOOT_SERVICES;


//
// EFI Configuration Table and GUID definitions
//

#define MPS_TABLE_GUID    \
    { 0xeb9d2d2f, 0x2d88, 0x11d3, {0x9a, 0x16, 0x0, 0x90, 0x27, 0x3f, 0xc1, 0x4d} }

#define ACPI_TABLE_GUID    \
    { 0xeb9d2d30, 0x2d88, 0x11d3, {0x9a, 0x16, 0x0, 0x90, 0x27, 0x3f, 0xc1, 0x4d} }

#define ACPI_20_TABLE_GUID  \
    { 0x8868e871, 0xe4f1, 0x11d3, {0xbc, 0x22, 0x0, 0x80, 0xc7, 0x3c, 0x88, 0x81} }

#define SMBIOS_TABLE_GUID    \
    { 0xeb9d2d31, 0x2d88, 0x11d3, {0x9a, 0x16, 0x0, 0x90, 0x27, 0x3f, 0xc1, 0x4d} }

#define SMBIOS3_TABLE_GUID    \
    { 0xf2fd1544, 0x9794, 0x4a2c, {0x99, 0x2e, 0xe5, 0xbb, 0xcf, 0x20, 0xe3, 0x94} }

#define SAL_SYSTEM_TABLE_GUID    \
    { 0xeb9d2d32, 0x2d88, 0x11d3, {0x9a, 0x16, 0x0, 0x90, 0x27, 0x3f, 0xc1, 0x4d} }

#define EFI_DTB_TABLE_GUID \
    { 0xb1b621d5, 0xf19c, 0x41a5, {0x83, 0x0b, 0xd9, 0x15, 0x2c, 0x69, 0xaa, 0xe0} }

typedef struct _EFI_CONFIGURATION_TABLE {
    EFI_GUID                VendorGuid;
    VOID                    *VendorTable;
} EFI_CONFIGURATION_TABLE;


//
// EFI System Table
//




#define EFI_SYSTEM_TABLE_SIGNATURE      0x5453595320494249
#define EFI_SYSTEM_TABLE_REVISION      (EFI_SPECIFICATION_MAJOR_REVISION<<16) | (EFI_SPECIFICATION_MINOR_REVISION)

typedef struct _EFI_SYSTEM_TABLE {
    EFI_TABLE_HEADER                Hdr;

    CHAR16                          *FirmwareVendor;
    UINT32                          FirmwareRevision;

    EFI_HANDLE                      ConsoleInHandle;
    SIMPLE_INPUT_INTERFACE          *ConIn;

    EFI_HANDLE                      ConsoleOutHandle;
    SIMPLE_TEXT_OUTPUT_INTERFACE    *ConOut;

    EFI_HANDLE                      StandardErrorHandle;
    SIMPLE_TEXT_OUTPUT_INTERFACE    *StdErr;

    EFI_RUNTIME_SERVICES            *RuntimeServices;
    EFI_BOOT_SERVICES               *BootServices;

    UINTN                           NumberOfTableEntries;
    EFI_CONFIGURATION_TABLE         *ConfigurationTable;

} EFI_SYSTEM_TABLE;

#endif

#ifndef _EFI_FS_H
#define _EFI_FS_H

/*++

Copyright (c) 1998  Intel Corporation

Module Name:

    efifs.h

Abstract:

    EFI File System structures



Revision History

--*/


//
// EFI Partition header (normaly starts in LBA 1)
//

#define EFI_PARTITION_SIGNATURE         0x5053595320494249
#define EFI_PARTITION_REVISION          0x00010001
#define MIN_EFI_PARTITION_BLOCK_SIZE    512
#define EFI_PARTITION_LBA               1

typedef struct _EFI_PARTITION_HEADER {
    EFI_TABLE_HEADER    Hdr;
    UINT32              DirectoryAllocationNumber;
    UINT32              BlockSize;
    EFI_LBA             FirstUsableLba;
    EFI_LBA             LastUsableLba;
    EFI_LBA             UnusableSpace;
    EFI_LBA             FreeSpace;
    EFI_LBA             RootFile;
    EFI_LBA             SecutiryFile;
} EFI_PARTITION_HEADER;


//
// File header
//

#define EFI_FILE_HEADER_SIGNATURE   0x454c494620494249
#define EFI_FILE_HEADER_REVISION    0x00010000
#define EFI_FILE_STRING_SIZE        260

typedef struct _EFI_FILE_HEADER {
    EFI_TABLE_HEADER    Hdr;
    UINT32              Class;
    UINT32              LBALOffset;
    EFI_LBA             Parent;
    UINT64              FileSize;
    UINT64              FileAttributes;
    EFI_TIME            FileCreateTime;
    EFI_TIME            FileModificationTime;
    EFI_GUID            VendorGuid;
    CHAR16              FileString[EFI_FILE_STRING_SIZE];
} EFI_FILE_HEADER;


//
// Return the file's first LBAL which is in the same
// logical block as the file header
//

#define EFI_FILE_LBAL(a)    ((EFI_LBAL *) (((CHAR8 *) (a)) + (a)->LBALOffset))

#define EFI_FILE_CLASS_FREE_SPACE   1
#define EFI_FILE_CLASS_EMPTY        2
#define EFI_FILE_CLASS_NORMAL       3


//
// Logical Block Address List - the fundemental block
// description structure
//

#define EFI_LBAL_SIGNATURE      0x4c41424c20494249
#define EFI_LBAL_REVISION       0x00010000

typedef struct _EFI_LBAL {
    EFI_TABLE_HEADER    Hdr;
    UINT32              Class;
    EFI_LBA             Parent;
    EFI_LBA             Next;
    UINT32              ArraySize;
    UINT32              ArrayCount;
} EFI_LBAL;

// Array size 
#define EFI_LBAL_ARRAY_SIZE(lbal,offs,blks)  \
        (((blks) - (offs) - (lbal)->Hdr.HeaderSize) / sizeof(EFI_RL))

//
// Logical Block run-length
//

typedef struct {
    EFI_LBA     Start;
    UINT64      Length;
} EFI_RL;

//
// Return the run-length structure from an LBAL header
//

#define EFI_LBAL_RL(a)      ((EFI_RL*) (((CHAR8 *) (a)) + (a)->Hdr.HeaderSize))

#endif

#ifndef _EFI_ERR_H
#define _EFI_ERR_H

/*++

Copyright (c) 1998  Intel Corporation

Module Name:

    efierr.h

Abstract:

    EFI error codes




Revision History

--*/


#define EFIWARN(a)                            (a)
#define EFI_ERROR(a)              (((INTN) a) < 0)


#define EFI_SUCCESS                             0
#define EFI_LOAD_ERROR                  EFIERR(1)
#define EFI_INVALID_PARAMETER           EFIERR(2)
#define EFI_UNSUPPORTED                 EFIERR(3)
#define EFI_BAD_BUFFER_SIZE             EFIERR(4)
#define EFI_BUFFER_TOO_SMALL            EFIERR(5)
#define EFI_NOT_READY                   EFIERR(6)
#define EFI_DEVICE_ERROR                EFIERR(7)
#define EFI_WRITE_PROTECTED             EFIERR(8)
#define EFI_OUT_OF_RESOURCES            EFIERR(9)
#define EFI_VOLUME_CORRUPTED            EFIERR(10)
#define EFI_VOLUME_FULL                 EFIERR(11)
#define EFI_NO_MEDIA                    EFIERR(12)
#define EFI_MEDIA_CHANGED               EFIERR(13)
#define EFI_NOT_FOUND                   EFIERR(14)
#define EFI_ACCESS_DENIED               EFIERR(15)
#define EFI_NO_RESPONSE                 EFIERR(16)
#define EFI_NO_MAPPING                  EFIERR(17)
#define EFI_TIMEOUT                     EFIERR(18)
#define EFI_NOT_STARTED                 EFIERR(19)
#define EFI_ALREADY_STARTED             EFIERR(20)
#define EFI_ABORTED                     EFIERR(21)
#define EFI_ICMP_ERROR                  EFIERR(22)
#define EFI_TFTP_ERROR                  EFIERR(23)
#define EFI_PROTOCOL_ERROR              EFIERR(24)
#define EFI_INCOMPATIBLE_VERSION        EFIERR(25)
#define EFI_SECURITY_VIOLATION          EFIERR(26)
#define EFI_CRC_ERROR                   EFIERR(27)
#define EFI_END_OF_MEDIA                EFIERR(28)
#define EFI_END_OF_FILE                 EFIERR(31)
#define EFI_INVALID_LANGUAGE            EFIERR(32)
#define EFI_COMPROMISED_DATA            EFIERR(33)

#define EFI_WARN_UNKOWN_GLYPH           EFIWARN(1)
#define EFI_WARN_UNKNOWN_GLYPH          EFIWARN(1)
#define EFI_WARN_DELETE_FAILURE         EFIWARN(2)
#define EFI_WARN_WRITE_FAILURE          EFIWARN(3)
#define EFI_WARN_BUFFER_TOO_SMALL       EFIWARN(4)

#endif

#ifndef _EFI_UI_H
#define _EFI_UI_H

/*++

Copyright (c) 200  Intel Corporation

Module Name:

    EfiUi.h

Abstract:
    Protocol used to build User Interface (UI) stuff.

    This protocol is just data. It is a multi dimentional array.
    For each string there is an array of UI_STRING_ENTRY. Each string
    is for a different language translation of the same string. The list
    is terminated by a NULL UiString. There can be any number of
    UI_STRING_ENTRY arrays. A NULL array terminates the list. A NULL array
    entry contains all zeros.

    Thus the shortest possible EFI_UI_PROTOCOL has three UI_STRING_ENTRY.
    The String, it's NULL terminator, and the NULL terminator for the entire
    thing.


Revision History

--*/

#define EFI_UI_INTERFACE_PROTOCOL_GUID \
    { 0x32dd7981, 0x2d27, 0x11d4, {0xbc, 0x8b, 0x0, 0x80, 0xc7, 0x3c, 0x88, 0x81} }
#define EFI_UI_PROTOCOL EFI_UI_INTERFACE_PROTOCOL_GUID


typedef enum {
    UiDeviceString,
    UiVendorString,
    UiMaxString
} UI_STRING_TYPE;

typedef struct {
    ISO_639_2   *LangCode;
    CHAR16      *UiString;
} UI_STRING_ENTRY;

#define EFI_UI_INTERFACE_PROTOCOL_VERSION 0x00010000
#define EFI_UI_VERSION                    EFI_UI_INTERFACE_PROTOCOL_VERSION

typedef struct _EFI_UI_INTERFACE_PROTOCOL {
    UINT32          Version;
    UI_STRING_ENTRY *Entry;
} EFI_UI_INTERFACE_PROTOCOL;

typedef struct _EFI_UI_INTERFACE_PROTOCOL _UI_INTERFACE;
typedef EFI_UI_INTERFACE_PROTOCOL UI_INTERFACE;

#endif
#ifndef _EFI_IP_H
#define _EFI_IP_H

/*++
Copyright (c) 2013  Intel Corporation

--*/

#define EFI_IP4_SERVICE_BINDING_PROTOCOL \
   {0xc51711e7,0xb4bf,0x404a,{0xbf,0xb8,0x0a,0x04, 0x8e,0xf1,0xff,0xe4}}

#define EFI_IP4_PROTOCOL \
    {0x41d94cd2,0x35b6,0x455a,{0x82,0x58,0xd4,0xe5,0x13,0x34,0xaa,0xdd}}

#define EFI_IP6_SERVICE_BINDING_PROTOCOL \
    {0xec835dd3,0xfe0f,0x617b,{0xa6,0x21,0xb3,0x50,0xc3,0xe1,0x33,0x88}}

#define EFI_IP6_PROTOCOL \
    {0x2c8759d5,0x5c2d,0x66ef,{0x92,0x5f,0xb6,0x6c,0x10,0x19,0x57,0xe2}}

INTERFACE_DECL(_EFI_IP4);
INTERFACE_DECL(_EFI_IP6);

typedef struct {
    EFI_HANDLE       InstanceHandle;
    EFI_IPv4_ADDRESS Ip4Address;
    EFI_IPv4_ADDRESS SubnetMask;
} EFI_IP4_ADDRESS_PAIR;

typedef struct {
    EFI_HANDLE           DriverHandle;
    UINT32               AddressCount;
    EFI_IP4_ADDRESS_PAIR AddressPairs[1];
} EFI_IP4_VARIABLE_DATA;

typedef struct {
    UINT8            DefaultProtocol;
    BOOLEAN          AcceptAnyProtocol;
    BOOLEAN          AcceptIcmpErrors;
    BOOLEAN          AcceptBroadcast;
    BOOLEAN          AcceptPromiscuous;
    BOOLEAN          UseDefaultAddress;
    EFI_IPv4_ADDRESS StationAddress;
    EFI_IPv4_ADDRESS SubnetMask;
    UINT8            TypeOfService;
    UINT8            TimeToLive;
    BOOLEAN          DoNotFragment;
    BOOLEAN          RawData;
    UINT32           ReceiveTimeout;
    UINT32           TransmitTimeout;
} EFI_IP4_CONFIG_DATA;

typedef struct {
    EFI_IPv4_ADDRESS SubnetAddress;
    EFI_IPv4_ADDRESS SubnetMask;
    EFI_IPv4_ADDRESS GatewayAddress;
} EFI_IP4_ROUTE_TABLE;

typedef struct {
    UINT8 Type;
    UINT8 Code;
} EFI_IP4_ICMP_TYPE;

typedef struct {
    BOOLEAN             IsStarted;
    UINT32              MaxPacketSize;
    EFI_IP4_CONFIG_DATA ConfigData;
    BOOLEAN             IsConfigured;
    UINT32              GroupCount;
    EFI_IPv4_ADDRESS    *GroupTable;
    UINT32              RouteCount;
    EFI_IP4_ROUTE_TABLE *RouteTable;
    UINT32              IcmpTypeCount;
    EFI_IP4_ICMP_TYPE   *IcmpTypeList;
} EFI_IP4_MODE_DATA;

typedef
EFI_STATUS
(EFIAPI *EFI_IP4_GET_MODE_DATA) (
    IN struct _EFI_IP4                  *This,
    OUT EFI_IP4_MODE_DATA               *Ip4ModeData   OPTIONAL,
    OUT EFI_MANAGED_NETWORK_CONFIG_DATA *MnpConfigData OPTIONAL,
    OUT EFI_SIMPLE_NETWORK_MODE         *SnpModeData   OPTIONAL
    );

typedef
EFI_STATUS
(EFIAPI *EFI_IP4_CONFIGURE) (
    IN struct _EFI_IP4     *This,
    IN EFI_IP4_CONFIG_DATA *IpConfigData OPTIONAL
    );

typedef
EFI_STATUS
(EFIAPI *EFI_IP4_GROUPS) (
    IN struct _EFI_IP4  *This,
    IN BOOLEAN          JoinFlag,
    IN EFI_IPv4_ADDRESS *GroupAddress OPTIONAL
    );

typedef
EFI_STATUS
(EFIAPI *EFI_IP4_ROUTES) (
    IN struct _EFI_IP4  *This,
    IN BOOLEAN          DeleteRoute,
    IN EFI_IPv4_ADDRESS *SubnetAddress,
    IN EFI_IPv4_ADDRESS *SubnetMask,
    IN EFI_IPv4_ADDRESS *GatewayAddress
    );

#pragma pack(1)
typedef struct {
    UINT8            HeaderLength:4;
    UINT8            Version:4;
    UINT8            TypeOfService;
    UINT16           TotalLength;
    UINT16           Identification;
    UINT16           Fragmentation;
    UINT8            TimeToLive;
    UINT8            Protocol;
    UINT16           Checksum;
    EFI_IPv4_ADDRESS SourceAddress;
    EFI_IPv4_ADDRESS DestinationAddress;
} EFI_IP4_HEADER;
#pragma pack()

typedef struct {
    UINT32 FragmentLength;
    VOID   *FragmentBuffer;
} EFI_IP4_FRAGMENT_DATA;

typedef struct {
    EFI_TIME              TimeStamp;
    EFI_EVENT             RecycleSignal;
    UINT32                HeaderLength;
    EFI_IP4_HEADER        *Header;
    UINT32                OptionsLength;
    VOID                  *Options;
    UINT32                DataLength;
    UINT32                FragmentCount;
    EFI_IP4_FRAGMENT_DATA FragmentTable[1];
} EFI_IP4_RECEIVE_DATA;

typedef struct {
    EFI_IPv4_ADDRESS SourceAddress;
    EFI_IPv4_ADDRESS GatewayAddress;
    UINT8            Protocol;
    UINT8            TypeOfService;
    UINT8            TimeToLive;
    BOOLEAN          DoNotFragment;
} EFI_IP4_OVERRIDE_DATA;

typedef struct {
    EFI_IPv4_ADDRESS      DestinationAddress;
    EFI_IP4_OVERRIDE_DATA *OverrideData;
    UINT32                OptionsLength;
    VOID                  *OptionsBuffer;
    UINT32                TotalDataLength;
    UINT32                FragmentCount;
    EFI_IP4_FRAGMENT_DATA FragmentTable[1];
} EFI_IP4_TRANSMIT_DATA;

typedef struct {
    EFI_EVENT                 Event;
    EFI_STATUS                Status;
    union {
        EFI_IP4_RECEIVE_DATA  *RxData;
        EFI_IP4_TRANSMIT_DATA *TxData;
    } Packet;
} EFI_IP4_COMPLETION_TOKEN;

typedef
EFI_STATUS
(EFIAPI *EFI_IP4_TRANSMIT) (
    IN struct _EFI_IP4          *This,
    IN EFI_IP4_COMPLETION_TOKEN *Token
    );

typedef
EFI_STATUS
(EFIAPI *EFI_IP4_RECEIVE) (
    IN struct _EFI_IP4          *This,
    IN EFI_IP4_COMPLETION_TOKEN *Token
    );

typedef
EFI_STATUS
(EFIAPI *EFI_IP4_CANCEL)(
    IN struct _EFI_IP4          *This,
    IN EFI_IP4_COMPLETION_TOKEN *Token OPTIONAL
    );

typedef
EFI_STATUS
(EFIAPI *EFI_IP4_POLL) (
    IN struct _EFI_IP4 *This
    );

typedef struct _EFI_IP4 {
    EFI_IP4_GET_MODE_DATA GetModeData;
    EFI_IP4_CONFIGURE     Configure;
    EFI_IP4_GROUPS        Groups;
    EFI_IP4_ROUTES        Routes;
    EFI_IP4_TRANSMIT      Transmit;
    EFI_IP4_RECEIVE       Receive;
    EFI_IP4_CANCEL        Cancel;
    EFI_IP4_POLL          Poll;
} EFI_IP4;

typedef struct {
    UINT8            DefaultProtocol;
    BOOLEAN          AcceptAnyProtocol;
    BOOLEAN          AcceptIcmpErrors;
    BOOLEAN          AcceptPromiscuous;
    EFI_IPv6_ADDRESS DestinationAddress;
    EFI_IPv6_ADDRESS StationAddress;
    UINT8            TrafficClass;
    UINT8            HopLimit;
    UINT32           FlowLabel;
    UINT32           ReceiveTimeout;
    UINT32           TransmitTimeout;
} EFI_IP6_CONFIG_DATA;

typedef struct {
    EFI_IPv6_ADDRESS Address;
    UINT8            PrefixLength;
} EFI_IP6_ADDRESS_INFO;

typedef struct {
    EFI_IPv6_ADDRESS Gateway;
    EFI_IPv6_ADDRESS Destination;
    UINT8            PrefixLength;
} EFI_IP6_ROUTE_TABLE;

typedef enum {
    EfiNeighborInComplete,
    EfiNeighborReachable,
    EfiNeighborStale,
    EfiNeighborDelay,
    EfiNeighborProbe
} EFI_IP6_NEIGHBOR_STATE;

typedef struct {
    EFI_IPv6_ADDRESS       Neighbor;
    EFI_MAC_ADDRESS        LinkAddress;
    EFI_IP6_NEIGHBOR_STATE State;
} EFI_IP6_NEIGHBOR_CACHE;

typedef struct {
    UINT8 Type;
    UINT8 Code;
} EFI_IP6_ICMP_TYPE;

//***********************************************************
// ICMPv6 type definitions for error messages
//***********************************************************
#define ICMP_V6_DEST_UNREACHABLE     0x1
#define ICMP_V6_PACKET_TOO_BIG       0x2
#define ICMP_V6_TIME_EXCEEDED        0x3
#define ICMP_V6_PARAMETER_PROBLEM    0x4

//***********************************************************
// ICMPv6 type definition for informational messages
//***********************************************************
#define ICMP_V6_ECHO_REQUEST         0x80
#define ICMP_V6_ECHO_REPLY           0x81
#define ICMP_V6_LISTENER_QUERY       0x82
#define ICMP_V6_LISTENER_REPORT      0x83
#define ICMP_V6_LISTENER_DONE        0x84
#define ICMP_V6_ROUTER_SOLICIT       0x85
#define ICMP_V6_ROUTER_ADVERTISE     0x86
#define ICMP_V6_NEIGHBOR_SOLICIT     0x87
#define ICMP_V6_NEIGHBOR_ADVERTISE   0x88
#define ICMP_V6_REDIRECT             0x89
#define ICMP_V6_LISTENER_REPORT_2    0x8F

//***********************************************************
// ICMPv6 code definitions for ICMP_V6_DEST_UNREACHABLE
//***********************************************************
#define ICMP_V6_NO_ROUTE_TO_DEST     0x0
#define ICMP_V6_COMM_PROHIBITED      0x1
#define ICMP_V6_BEYOND_SCOPE         0x2
#define ICMP_V6_ADDR_UNREACHABLE     0x3
#define ICMP_V6_PORT_UNREACHABLE     0x4
#define ICMP_V6_SOURCE_ADDR_FAILED   0x5
#define ICMP_V6_ROUTE_REJECTED       0x6

//***********************************************************
// ICMPv6 code definitions for ICMP_V6_TIME_EXCEEDED
//***********************************************************
#define ICMP_V6_TIMEOUT_HOP_LIMIT    0x0
#define ICMP_V6_TIMEOUT_REASSEMBLE   0x1

//***********************************************************
// ICMPv6 code definitions for ICMP_V6_PARAMETER_PROBLEM
//***********************************************************
#define ICMP_V6_ERRONEOUS_HEADER     0x0
#define ICMP_V6_UNRECOGNIZE_NEXT_HDR 0x1
#define ICMP_V6_UNRECOGNIZE_OPTION   0x2

typedef struct {
    BOOLEAN                IsStarted;
    UINT32                 MaxPacketSize;
    EFI_IP6_CONFIG_DATA    ConfigData;
    BOOLEAN                IsConfigured;
    UINT32                 AddressCount;
    EFI_IP6_ADDRESS_INFO   *AddressList;
    UINT32                 GroupCount;
    EFI_IPv6_ADDRESS       *GroupTable;
    UINT32                 RouteCount;
    EFI_IP6_ROUTE_TABLE    *RouteTable;
    UINT32                 NeighborCount;
    EFI_IP6_NEIGHBOR_CACHE *NeighborCache;
    UINT32                 PrefixCount;
    EFI_IP6_ADDRESS_INFO   *PrefixTable;
    UINT32                 IcmpTypeCount;
    EFI_IP6_ICMP_TYPE      *IcmpTypeList;
} EFI_IP6_MODE_DATA;

typedef
EFI_STATUS
(EFIAPI *EFI_IP6_GET_MODE_DATA) (
    IN struct _EFI_IP6                  *This,
    OUT EFI_IP6_MODE_DATA               *Ip6ModeData   OPTIONAL,
    OUT EFI_MANAGED_NETWORK_CONFIG_DATA *MnpConfigData OPTIONAL,
    OUT EFI_SIMPLE_NETWORK_MODE         *SnpModeData   OPTIONAL
    );

typedef
EFI_STATUS
(EFIAPI *EFI_IP6_CONFIGURE) (
    IN struct _EFI_IP6     *This,
    IN EFI_IP6_CONFIG_DATA *Ip6ConfigData OPTIONAL
    );
typedef
EFI_STATUS
(EFIAPI *EFI_IP6_GROUPS) (
    IN struct _EFI_IP6  *This,
    IN BOOLEAN          JoinFlag,
    IN EFI_IPv6_ADDRESS *GroupAddress OPTIONAL
    );

typedef
EFI_STATUS
(EFIAPI *EFI_IP6_ROUTES) (
    IN struct _EFI_IP6  *This,
    IN BOOLEAN          DeleteRoute,
    IN EFI_IPv6_ADDRESS *Destination    OPTIONAL,
    IN UINT8            PrefixLength,
    IN EFI_IPv6_ADDRESS *GatewayAddress OPTIONAL
    );

typedef
EFI_STATUS
(EFIAPI *EFI_IP6_NEIGHBORS) (
    IN struct _EFI_IP6  *This,
    IN BOOLEAN          DeleteFlag,
    IN EFI_IPv6_ADDRESS *TargetIp6Address,
    IN EFI_MAC_ADDRESS  *TargetLinkAddress OPTIONAL,
    IN UINT32           Timeout,
    IN BOOLEAN          Override
    );

typedef struct _EFI_IP6_FRAGMENT_DATA {
    UINT32 FragmentLength;
    VOID   *FragmentBuffer;
} EFI_IP6_FRAGMENT_DATA;

typedef struct _EFI_IP6_OVERRIDE_DATA {
    UINT8  Protocol;
    UINT8  HopLimit;
    UINT32 FlowLabel;
} EFI_IP6_OVERRIDE_DATA;

typedef struct _EFI_IP6_TRANSMIT_DATA {
    EFI_IPv6_ADDRESS      DestinationAddress;
    EFI_IP6_OVERRIDE_DATA *OverrideData;
    UINT32                ExtHdrsLength;
    VOID                  *ExtHdrs;
    UINT8                 NextHeader;
    UINT32                DataLength;
    UINT32                FragmentCount;
    EFI_IP6_FRAGMENT_DATA FragmentTable[1];
} EFI_IP6_TRANSMIT_DATA;

#pragma pack(1)
typedef struct _EFI_IP6_HEADER {
    UINT8            TrafficClassH:4;
    UINT8            Version:4;
    UINT8            FlowLabelH:4;
    UINT8            TrafficClassL:4;
    UINT16           FlowLabelL;
    UINT16           PayloadLength;
    UINT8            NextHeader;
    UINT8            HopLimit;
    EFI_IPv6_ADDRESS SourceAddress;
    EFI_IPv6_ADDRESS DestinationAddress;
} EFI_IP6_HEADER;
#pragma pack()

typedef struct _EFI_IP6_RECEIVE_DATA {
    EFI_TIME              TimeStamp;
    EFI_EVENT             RecycleSignal;
    UINT32                HeaderLength;
    EFI_IP6_HEADER        *Header;
    UINT32                DataLength;
    UINT32                FragmentCount;
    EFI_IP6_FRAGMENT_DATA FragmentTable[1];
} EFI_IP6_RECEIVE_DATA;

typedef struct {
    EFI_EVENT                 Event;
    EFI_STATUS                Status;
    union {
	EFI_IP6_RECEIVE_DATA  *RxData;
	EFI_IP6_TRANSMIT_DATA *TxData;
    }                         Packet;
} EFI_IP6_COMPLETION_TOKEN;

typedef
EFI_STATUS
(EFIAPI *EFI_IP6_TRANSMIT) (
    IN struct _EFI_IP6          *This,
    IN EFI_IP6_COMPLETION_TOKEN *Token
    );

typedef
EFI_STATUS
(EFIAPI *EFI_IP6_RECEIVE) (
    IN struct _EFI_IP6          *This,
    IN EFI_IP6_COMPLETION_TOKEN *Token
    );

typedef
EFI_STATUS
(EFIAPI *EFI_IP6_CANCEL)(
    IN struct _EFI_IP6          *This,
    IN EFI_IP6_COMPLETION_TOKEN *Token OPTIONAL
    );

typedef
EFI_STATUS
(EFIAPI *EFI_IP6_POLL) (
    IN struct _EFI_IP6 *This
    );

typedef struct _EFI_IP6 {
    EFI_IP6_GET_MODE_DATA GetModeData;
    EFI_IP6_CONFIGURE     Configure;
    EFI_IP6_GROUPS        Groups;
    EFI_IP6_ROUTES        Routes;
    EFI_IP6_NEIGHBORS     Neighbors;
    EFI_IP6_TRANSMIT      Transmit;
    EFI_IP6_RECEIVE       Receive;
    EFI_IP6_CANCEL        Cancel;
    EFI_IP6_POLL          Poll;
} EFI_IP6;

#endif /* _EFI_IP_H */
#ifndef _EFI_UDP_H
#define _EFI_UDP_H


/*++
Copyright (c) 2013  Intel Corporation

--*/

#define EFI_UDP4_SERVICE_BINDING_PROTOCOL \
    { 0x83f01464, 0x99bd, 0x45e5, {0xb3, 0x83, 0xaf, 0x63, 0x05, 0xd8, 0xe9, 0xe6} }

#define EFI_UDP4_PROTOCOL \
    { 0x3ad9df29, 0x4501, 0x478d, {0xb1, 0xf8, 0x7f, 0x7f, 0xe7, 0x0e, 0x50, 0xf3} }

#define EFI_UDP6_SERVICE_BINDING_PROTOCOL \
    { 0x66ed4721, 0x3c98, 0x4d3e, {0x81, 0xe3, 0xd0, 0x3d, 0xd3, 0x9a, 0x72, 0x54} }

#define EFI_UDP6_PROTOCOL \
    { 0x4f948815, 0xb4b9, 0x43cb, {0x8a, 0x33, 0x90, 0xe0, 0x60, 0xb3,0x49, 0x55} }

INTERFACE_DECL(_EFI_UDP4);
INTERFACE_DECL(_EFI_UDP6);

typedef struct {
    BOOLEAN          AcceptBroadcast;
    BOOLEAN          AcceptPromiscuous;
    BOOLEAN          AcceptAnyPort;
    BOOLEAN          AllowDuplicatePort;
    UINT8            TypeOfService;
    UINT8            TimeToLive;
    BOOLEAN          DoNotFragment;
    UINT32           ReceiveTimeout;
    UINT32           TransmitTimeout;
    BOOLEAN          UseDefaultAddress;
    EFI_IPv4_ADDRESS StationAddress;
    EFI_IPv4_ADDRESS SubnetMask;
    UINT16           StationPort;
    EFI_IPv4_ADDRESS RemoteAddress;
    UINT16           RemotePort;
} EFI_UDP4_CONFIG_DATA;

typedef
EFI_STATUS
(EFIAPI *EFI_UDP4_GET_MODE_DATA) (
    IN struct _EFI_UDP4                 *This,
    OUT EFI_UDP4_CONFIG_DATA            *Udp4ConfigData OPTIONAL,
    OUT EFI_IP4_MODE_DATA               *Ip4ModeData    OPTIONAL,
    OUT EFI_MANAGED_NETWORK_CONFIG_DATA *MnpConfigData  OPTIONAL,
    OUT EFI_SIMPLE_NETWORK_MODE         *SnpModeData    OPTIONAL
    );

typedef
EFI_STATUS
(EFIAPI *EFI_UDP4_CONFIGURE) (
    IN struct _EFI_UDP4     *This,
    IN EFI_UDP4_CONFIG_DATA *UdpConfigData OPTIONAL
    );

typedef
EFI_STATUS
(EFIAPI *EFI_UDP4_GROUPS) (
    IN struct _EFI_UDP4 *This,
    IN BOOLEAN          JoinFlag,
    IN EFI_IPv4_ADDRESS *MulticastAddress OPTIONAL
    );

typedef
EFI_STATUS
(EFIAPI *EFI_UDP4_ROUTES) (
    IN struct _EFI_UDP4 *This,
    IN BOOLEAN          DeleteRoute,
    IN EFI_IPv4_ADDRESS *SubnetAddress,
    IN EFI_IPv4_ADDRESS *SubnetMask,
    IN EFI_IPv4_ADDRESS *GatewayAddress
    );

#define EFI_NETWORK_UNREACHABLE  EFIERR(100)
#define EFI_HOST_UNREACHABLE     EFIERR(101)
#define EFI_PROTOCOL_UNREACHABLE EFIERR(102)
#define EFI_PORT_UNREACHABLE     EFIERR(103)

typedef struct {
    EFI_IPv4_ADDRESS SourceAddress;
    UINT16           SourcePort;
    EFI_IPv4_ADDRESS DestinationAddress;
    UINT16           DestinationPort;
} EFI_UDP4_SESSION_DATA;

typedef struct {
    UINT32 FragmentLength;
    VOID   *FragmentBuffer;
} EFI_UDP4_FRAGMENT_DATA;

typedef struct {
    EFI_TIME               TimeStamp;
    EFI_EVENT              RecycleSignal;
    EFI_UDP4_SESSION_DATA  UdpSession;
    UINT32                 DataLength;
    UINT32                 FragmentCount;
    EFI_UDP4_FRAGMENT_DATA FragmentTable[1];
} EFI_UDP4_RECEIVE_DATA;

typedef struct {
    EFI_UDP4_SESSION_DATA  *UdpSessionData;
    EFI_IPv4_ADDRESS       *GatewayAddress;
    UINT32                 DataLength;
    UINT32                 FragmentCount;
    EFI_UDP4_FRAGMENT_DATA FragmentTable[1];
} EFI_UDP4_TRANSMIT_DATA;

typedef struct {
    EFI_EVENT                  Event;
    EFI_STATUS                 Status;
    union {
        EFI_UDP4_RECEIVE_DATA  *RxData;
	EFI_UDP4_TRANSMIT_DATA *TxData;
    }                          Packet;
} EFI_UDP4_COMPLETION_TOKEN;

typedef
EFI_STATUS
(EFIAPI *EFI_UDP4_TRANSMIT) (
    IN struct _EFI_UDP4          *This,
    IN EFI_UDP4_COMPLETION_TOKEN *Token
    );

typedef
EFI_STATUS
(EFIAPI *EFI_UDP4_RECEIVE) (
    IN struct _EFI_UDP4          *This,
    IN EFI_UDP4_COMPLETION_TOKEN *Token
    );

typedef
EFI_STATUS
(EFIAPI *EFI_UDP4_CANCEL)(
    IN struct _EFI_UDP4          *This,
    IN EFI_UDP4_COMPLETION_TOKEN *Token OPTIONAL
    );

typedef
EFI_STATUS
(EFIAPI *EFI_UDP4_POLL) (
    IN struct _EFI_UDP4 *This
    );

typedef struct _EFI_UDP4 {
    EFI_UDP4_GET_MODE_DATA GetModeData;
    EFI_UDP4_CONFIGURE     Configure;
    EFI_UDP4_GROUPS        Groups;
    EFI_UDP4_ROUTES        Routes;
    EFI_UDP4_TRANSMIT      Transmit;
    EFI_UDP4_RECEIVE       Receive;
    EFI_UDP4_CANCEL        Cancel;
    EFI_UDP4_POLL          Poll;
} EFI_UDP4;

typedef struct {
    BOOLEAN          AcceptPromiscuous;
    BOOLEAN          AcceptAnyPort;
    BOOLEAN          AllowDuplicatePort;
    UINT8            TrafficClass;
    UINT8            HopLimit;
    UINT32           ReceiveTimeout;
    UINT32           TransmitTimeout;
    EFI_IPv6_ADDRESS StationAddress;
    UINT16           StationPort;
    EFI_IPv6_ADDRESS RemoteAddress;
    UINT16           RemotePort;
} EFI_UDP6_CONFIG_DATA;

typedef
EFI_STATUS
(EFIAPI *EFI_UDP6_GET_MODE_DATA) (
    IN struct _EFI_UDP6                 *This,
    OUT EFI_UDP6_CONFIG_DATA            *Udp6ConfigData OPTIONAL,
    OUT EFI_IP6_MODE_DATA               *Ip6ModeData    OPTIONAL,
    OUT EFI_MANAGED_NETWORK_CONFIG_DATA *MnpConfigData  OPTIONAL,
    OUT EFI_SIMPLE_NETWORK_MODE         *SnpModeData    OPTIONAL
    );

typedef
EFI_STATUS
(EFIAPI *EFI_UDP6_CONFIGURE) (
    IN struct _EFI_UDP6     *This,
    IN EFI_UDP6_CONFIG_DATA *UdpConfigData OPTIONAL
    );

typedef
EFI_STATUS
(EFIAPI *EFI_UDP6_GROUPS) (
    IN struct _EFI_UDP6 *This,
    IN BOOLEAN          JoinFlag,
    IN EFI_IPv6_ADDRESS *MulticastAddress OPTIONAL
    );

typedef struct {
    EFI_IPv6_ADDRESS SourceAddress;
    UINT16           SourcePort;
    EFI_IPv6_ADDRESS DestinationAddress;
    UINT16           DestinationPort;
} EFI_UDP6_SESSION_DATA;

typedef struct {
    UINT32 FragmentLength;
    VOID   *FragmentBuffer;
} EFI_UDP6_FRAGMENT_DATA;

typedef struct {
    EFI_TIME               TimeStamp;
    EFI_EVENT              RecycleSignal;
    EFI_UDP6_SESSION_DATA  UdpSession;
    UINT32                 DataLength;
    UINT32                 FragmentCount;
    EFI_UDP6_FRAGMENT_DATA FragmentTable[1];
} EFI_UDP6_RECEIVE_DATA;

typedef struct {
    EFI_UDP6_SESSION_DATA  *UdpSessionData;
    UINT32                 DataLength;
    UINT32                 FragmentCount;
    EFI_UDP6_FRAGMENT_DATA FragmentTable[1];
} EFI_UDP6_TRANSMIT_DATA;

typedef struct {
    EFI_EVENT                  Event;
    EFI_STATUS                 Status;
    union {
        EFI_UDP6_RECEIVE_DATA  *RxData;
        EFI_UDP6_TRANSMIT_DATA *TxData;
    }                          Packet;
} EFI_UDP6_COMPLETION_TOKEN;

typedef
EFI_STATUS
(EFIAPI *EFI_UDP6_TRANSMIT) (
    IN struct _EFI_UDP6          *This,
    IN EFI_UDP6_COMPLETION_TOKEN *Token
    );

typedef
EFI_STATUS
(EFIAPI *EFI_UDP6_RECEIVE) (
    IN struct _EFI_UDP6          *This,
    IN EFI_UDP6_COMPLETION_TOKEN *Token
    );

typedef
EFI_STATUS
(EFIAPI *EFI_UDP6_CANCEL)(
    IN struct _EFI_UDP6          *This,
    IN EFI_UDP6_COMPLETION_TOKEN *Token OPTIONAL
    );

typedef
EFI_STATUS
(EFIAPI *EFI_UDP6_POLL) (
    IN struct _EFI_UDP6 *This
    );

typedef struct _EFI_UDP6 {
    EFI_UDP6_GET_MODE_DATA GetModeData;
    EFI_UDP6_CONFIGURE     Configure;
    EFI_UDP6_GROUPS        Groups;
    EFI_UDP6_TRANSMIT      Transmit;
    EFI_UDP6_RECEIVE       Receive;
    EFI_UDP6_CANCEL        Cancel;
    EFI_UDP6_POLL          Poll;
} EFI_UDP6;

#endif /* _EFI_UDP_H */
#ifndef _EFI_TCP_H
#define _EFI_TCP_H

/*++
Copyright (c) 2013  Intel Corporation

--*/

#define EFI_TCP4_SERVICE_BINDING_PROTOCOL \
    { 0x00720665, 0x67eb, 0x4a99, {0xba, 0xf7, 0xd3, 0xc3, 0x3a, 0x1c,0x7c, 0xc9}}

#define EFI_TCP4_PROTOCOL \
    { 0x65530bc7, 0xa359, 0x410f, {0xb0, 0x10, 0x5a, 0xad, 0xc7, 0xec, 0x2b, 0x62}}

#define EFI_TCP6_SERVICE_BINDING_PROTOCOL \
    { 0xec20eb79, 0x6c1a, 0x4664, {0x9a, 0xd, 0xd2, 0xe4, 0xcc, 0x16, 0xd6, 0x64}}

#define EFI_TCP6_PROTOCOL \
    { 0x46e44855, 0xbd60, 0x4ab7, {0xab, 0xd, 0xa6, 0x79, 0xb9, 0x44, 0x7d, 0x77}}

INTERFACE_DECL(_EFI_TCP4);
INTERFACE_DECL(_EFI_TCP6);

typedef struct {
    BOOLEAN            UseDefaultAddress;
    EFI_IPv4_ADDRESS   StationAddress;
    EFI_IPv4_ADDRESS   SubnetMask;
    UINT16             StationPort;
    EFI_IPv4_ADDRESS   RemoteAddress;
    UINT16             RemotePort;
    BOOLEAN            ActiveFlag;
} EFI_TCP4_ACCESS_POINT;

typedef struct {
    UINT32             ReceiveBufferSize;
    UINT32             SendBufferSize;
    UINT32             MaxSynBackLog;
    UINT32             ConnectionTimeout;
    UINT32             DataRetries;
    UINT32             FinTimeout;
    UINT32             TimeWaitTimeout;
    UINT32             KeepAliveProbes;
    UINT32             KeepAliveTime;
    UINT32             KeepAliveInterval;
    BOOLEAN            EnableNagle;
    BOOLEAN            EnableTimeStamp;
    BOOLEAN            EnableWindowScaling;
    BOOLEAN            EnableSelectiveAck;
    BOOLEAN            EnablePAthMtuDiscovery;
} EFI_TCP4_OPTION;

typedef struct {
    // Receiving Filters
    // I/O parameters
    UINT8                 TypeOfService;
    UINT8                 TimeToLive;

    // Access Point
    EFI_TCP4_ACCESS_POINT AccessPoint;

    // TCP Control Options
    EFI_TCP4_OPTION       *ControlOption;
} EFI_TCP4_CONFIG_DATA;

typedef enum {
    Tcp4StateClosed      = 0,
    Tcp4StateListen      = 1,
    Tcp4StateSynSent     = 2,
    Tcp4StateSynReceived = 3,
    Tcp4StateEstablished = 4,
    Tcp4StateFinWait1    = 5,
    Tcp4StateFinWait2    = 6,
    Tcp4StateClosing     = 7,
    Tcp4StateTimeWait    = 8,
    Tcp4StateCloseWait   = 9,
    Tcp4StateLastAck     = 10
} EFI_TCP4_CONNECTION_STATE;

typedef
EFI_STATUS
(EFIAPI *EFI_TCP4_GET_MODE_DATA) (
    IN struct _EFI_TCP4                 *This,
    OUT EFI_TCP4_CONNECTION_STATE       *Tcp4State      OPTIONAL,
    OUT EFI_TCP4_CONFIG_DATA            *Tcp4ConfigData OPTIONAL,
    OUT EFI_IP4_MODE_DATA               *Ip4ModeData    OPTIONAL,
    OUT EFI_MANAGED_NETWORK_CONFIG_DATA *MnpConfigData  OPTIONAL,
    OUT EFI_SIMPLE_NETWORK_MODE         *SnpModeData    OPTIONAL
    );

typedef
EFI_STATUS
(EFIAPI *EFI_TCP4_CONFIGURE) (
    IN struct _EFI_TCP4     *This,
    IN EFI_TCP4_CONFIG_DATA *TcpConfigData OPTIONAL
    );

typedef
EFI_STATUS
(EFIAPI *EFI_TCP4_ROUTES) (
    IN struct _EFI_TCP4 *This,
    IN BOOLEAN          DeleteRoute,
    IN EFI_IPv4_ADDRESS *SubnetAddress,
    IN EFI_IPv4_ADDRESS *SubnetMask,
    IN EFI_IPv4_ADDRESS *GatewayAddress
);

typedef struct {
    EFI_EVENT  Event;
    EFI_STATUS Status;
} EFI_TCP4_COMPLETION_TOKEN;

typedef struct {
    EFI_TCP4_COMPLETION_TOKEN CompletionToken;
} EFI_TCP4_CONNECTION_TOKEN;

typedef
EFI_STATUS
(EFIAPI *EFI_TCP4_CONNECT) (
    IN struct _EFI_TCP4          *This,
    IN EFI_TCP4_CONNECTION_TOKEN *ConnectionToken
    );

typedef struct {
    EFI_TCP4_COMPLETION_TOKEN CompletionToken;
    EFI_HANDLE                NewChildHandle;
} EFI_TCP4_LISTEN_TOKEN;

typedef
EFI_STATUS
(EFIAPI *EFI_TCP4_ACCEPT) (
    IN struct _EFI_TCP4      *This,
    IN EFI_TCP4_LISTEN_TOKEN *ListenToken
    );

#define EFI_CONNECTION_FIN     EFIERR(104)
#define EFI_CONNECTION_RESET   EFIERR(105)
#define EFI_CONNECTION_REFUSED EFIERR(106)

typedef struct {
    UINT32 FragmentLength;
    VOID   *FragmentBuffer;
} EFI_TCP4_FRAGMENT_DATA;

typedef struct {
    BOOLEAN                UrgentFlag;
    UINT32                 DataLength;
    UINT32                 FragmentCount;
    EFI_TCP4_FRAGMENT_DATA FragmentTable[1];
} EFI_TCP4_RECEIVE_DATA;

typedef struct {
    BOOLEAN                Push;
    BOOLEAN                Urgent;
    UINT32                 DataLength;
    UINT32                 FragmentCount;
    EFI_TCP4_FRAGMENT_DATA FragmentTable[1];
} EFI_TCP4_TRANSMIT_DATA;

typedef struct {
    EFI_TCP4_COMPLETION_TOKEN  CompletionToken;
    union {
	EFI_TCP4_RECEIVE_DATA  *RxData;
	EFI_TCP4_TRANSMIT_DATA *TxData;
    }                          Packet;
} EFI_TCP4_IO_TOKEN;

typedef
EFI_STATUS
(EFIAPI *EFI_TCP4_TRANSMIT) (
    IN struct _EFI_TCP4  *This,
    IN EFI_TCP4_IO_TOKEN *Token
    );

typedef
EFI_STATUS
(EFIAPI *EFI_TCP4_RECEIVE) (
    IN struct _EFI_TCP4  *This,
    IN EFI_TCP4_IO_TOKEN *Token
    );

typedef struct {
    EFI_TCP4_COMPLETION_TOKEN CompletionToken;
    BOOLEAN                   AbortOnClose;
} EFI_TCP4_CLOSE_TOKEN;

typedef
EFI_STATUS
(EFIAPI *EFI_TCP4_CLOSE)(
    IN struct _EFI_TCP4     *This,
    IN EFI_TCP4_CLOSE_TOKEN *CloseToken
    );

typedef
EFI_STATUS
(EFIAPI *EFI_TCP4_CANCEL)(
    IN struct _EFI_TCP4 *This,
    IN EFI_TCP4_COMPLETION_TOKEN *Token OPTIONAL
);

typedef
EFI_STATUS
(EFIAPI *EFI_TCP4_POLL) (
    IN struct _EFI_TCP4 *This
    );

typedef struct _EFI_TCP4 {
    EFI_TCP4_GET_MODE_DATA GetModeData;
    EFI_TCP4_CONFIGURE     Configure;
    EFI_TCP4_ROUTES        Routes;
    EFI_TCP4_CONNECT       Connect;
    EFI_TCP4_ACCEPT        Accept;
    EFI_TCP4_TRANSMIT      Transmit;
    EFI_TCP4_RECEIVE       Receive;
    EFI_TCP4_CLOSE         Close;
    EFI_TCP4_CANCEL        Cancel;
    EFI_TCP4_POLL          Poll;
} EFI_TCP4;

typedef enum {
    Tcp6StateClosed      = 0,
    Tcp6StateListen      = 1,
    Tcp6StateSynSent     = 2,
    Tcp6StateSynReceived = 3,
    Tcp6StateEstablished = 4,
    Tcp6StateFinWait1    = 5,
    Tcp6StateFinWait2    = 6,
    Tcp6StateClosing     = 7,
    Tcp6StateTimeWait    = 8,
    Tcp6StateCloseWait   = 9,
    Tcp6StateLastAck     = 10
} EFI_TCP6_CONNECTION_STATE;

typedef struct {
    EFI_IPv6_ADDRESS StationAddress;
    UINT16           StationPort;
    EFI_IPv6_ADDRESS RemoteAddress;
    UINT16           RemotePort;
    BOOLEAN          ActiveFlag;
} EFI_TCP6_ACCESS_POINT;

typedef struct {
    UINT32             ReceiveBufferSize;
    UINT32             SendBufferSize;
    UINT32             MaxSynBackLog;
    UINT32             ConnectionTimeout;
    UINT32             DataRetries;
    UINT32             FinTimeout;
    UINT32             TimeWaitTimeout;
    UINT32             KeepAliveProbes;
    UINT32             KeepAliveTime;
    UINT32             KeepAliveInterval;
    BOOLEAN            EnableNagle;
    BOOLEAN            EnableTimeStamp;
    BOOLEAN            EnableWindbowScaling;
    BOOLEAN            EnableSelectiveAck;
    BOOLEAN            EnablePathMtuDiscovery;
} EFI_TCP6_OPTION;

typedef struct {
    UINT8                 TrafficClass;
    UINT8                 HopLimit;
    EFI_TCP6_ACCESS_POINT AccessPoint;
    EFI_TCP6_OPTION       *ControlOption;
} EFI_TCP6_CONFIG_DATA;

typedef
EFI_STATUS
(EFIAPI *EFI_TCP6_GET_MODE_DATA) (
    IN struct _EFI_TCP6                 *This,
    OUT EFI_TCP6_CONNECTION_STATE       *Tcp6State      OPTIONAL,
    OUT EFI_TCP6_CONFIG_DATA            *Tcp6ConfigData OPTIONAL,
    OUT EFI_IP6_MODE_DATA               *Ip6ModeData    OPTIONAL,
    OUT EFI_MANAGED_NETWORK_CONFIG_DATA *MnpConfigData  OPTIONAL,
    OUT EFI_SIMPLE_NETWORK_MODE         *SnpModeData    OPTIONAL
    );

typedef
EFI_STATUS
(EFIAPI *EFI_TCP6_CONFIGURE) (
    IN struct _EFI_TCP6     *This,
    IN EFI_TCP6_CONFIG_DATA *Tcp6ConfigData OPTIONAL
    );

typedef struct {
    EFI_EVENT  Event;
    EFI_STATUS Status;
} EFI_TCP6_COMPLETION_TOKEN;

typedef struct {
    EFI_TCP6_COMPLETION_TOKEN CompletionToken;
} EFI_TCP6_CONNECTION_TOKEN;

typedef
EFI_STATUS
(EFIAPI *EFI_TCP6_CONNECT) (
    IN struct _EFI_TCP6          *This,
    IN EFI_TCP6_CONNECTION_TOKEN *ConnectionToken
    );

typedef struct {
    EFI_TCP6_COMPLETION_TOKEN CompletionToken;
    EFI_HANDLE                NewChildHandle;
} EFI_TCP6_LISTEN_TOKEN;

typedef
EFI_STATUS
(EFIAPI *EFI_TCP6_ACCEPT) (
    IN struct _EFI_TCP6      *This,
    IN EFI_TCP6_LISTEN_TOKEN *ListenToken
    );

typedef struct {
    UINT32 FragmentLength;
    VOID   *FragmentBuffer;
} EFI_TCP6_FRAGMENT_DATA;

typedef struct {
    BOOLEAN                UrgentFlag;
    UINT32                 DataLength;
    UINT32                 FragmentCount;
    EFI_TCP6_FRAGMENT_DATA FragmentTable[1];
} EFI_TCP6_RECEIVE_DATA;

typedef struct {
    BOOLEAN                Push;
    BOOLEAN                Urgent;
    UINT32                 DataLength;
    UINT32                 FragmentCount;
    EFI_TCP6_FRAGMENT_DATA FragmentTable[1];
} EFI_TCP6_TRANSMIT_DATA;

typedef struct {
    EFI_TCP6_COMPLETION_TOKEN  CompletionToken;
    union {
	EFI_TCP6_RECEIVE_DATA  *RxData;
	EFI_TCP6_TRANSMIT_DATA *TxData;
    }                          Packet;
} EFI_TCP6_IO_TOKEN;

typedef
EFI_STATUS
(EFIAPI *EFI_TCP6_TRANSMIT) (
    IN struct _EFI_TCP6  *This,
    IN EFI_TCP6_IO_TOKEN *Token
    );

typedef
EFI_STATUS
(EFIAPI *EFI_TCP6_RECEIVE) (
    IN struct _EFI_TCP6  *This,
    IN EFI_TCP6_IO_TOKEN *Token
    );

typedef struct {
    EFI_TCP6_COMPLETION_TOKEN CompletionToken;
    BOOLEAN                   AbortOnClose;
} EFI_TCP6_CLOSE_TOKEN;

typedef
EFI_STATUS
(EFIAPI *EFI_TCP6_CLOSE)(
    IN struct _EFI_TCP6     *This,
    IN EFI_TCP6_CLOSE_TOKEN *CloseToken
    );

typedef
EFI_STATUS
(EFIAPI *EFI_TCP6_CANCEL)(
    IN struct _EFI_TCP6          *This,
    IN EFI_TCP6_COMPLETION_TOKEN *Token OPTIONAL
    );

typedef
EFI_STATUS
(EFIAPI *EFI_TCP6_POLL) (
    IN struct _EFI_TCP6 *This
    );

typedef struct _EFI_TCP6 {
    EFI_TCP6_GET_MODE_DATA GetModeData;
    EFI_TCP6_CONFIGURE     Configure;
    EFI_TCP6_CONNECT       Connect;
    EFI_TCP6_ACCEPT        Accept;
    EFI_TCP6_TRANSMIT      Transmit;
    EFI_TCP6_RECEIVE       Receive;
    EFI_TCP6_CLOSE         Close;
    EFI_TCP6_CANCEL        Cancel;
    EFI_TCP6_POLL          Poll;
} EFI_TCP6;

#endif /* _EFI_TCP_H */
/* Copyright (C) 2014 by John Cronin
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef _EFI_POINT_H
#define _EFI_POINT_H

#define EFI_SIMPLE_POINTER_PROTOCOL_GUID \
	{ 0x31878c87, 0xb75, 0x11d5, { 0x9a, 0x4f, 0x0, 0x90, 0x27, 0x3f, 0xc1, 0x4d } }

INTERFACE_DECL(_EFI_SIMPLE_POINTER);

typedef struct {
	INT32 RelativeMovementX;
	INT32 RelativeMovementY;
	INT32 RelativeMovementZ;
	BOOLEAN LeftButton;
	BOOLEAN RightButton;
} EFI_SIMPLE_POINTER_STATE;

typedef struct {
	UINT64 ResolutionX;
	UINT64 ResolutionY;
	UINT64 ResolutionZ;
	BOOLEAN LeftButton;
	BOOLEAN RightButton;
} EFI_SIMPLE_POINTER_MODE;

typedef
EFI_STATUS
(EFIAPI *EFI_SIMPLE_POINTER_RESET) (
	IN struct _EFI_SIMPLE_POINTER *This,
	IN BOOLEAN ExtendedVerification
);

typedef
EFI_STATUS
(EFIAPI *EFI_SIMPLE_POINTER_GET_STATE) (
	IN struct _EFI_SIMPLE_POINTER *This,
	IN OUT EFI_SIMPLE_POINTER_STATE *State
);

typedef struct _EFI_SIMPLE_POINTER {
	EFI_SIMPLE_POINTER_RESET Reset;
	EFI_SIMPLE_POINTER_GET_STATE GetState;
	EFI_EVENT WaitForInput;
	EFI_SIMPLE_POINTER_MODE *Mode;
} EFI_SIMPLE_POINTER_PROTOCOL;

#define EFI_ABSOLUTE_POINTER_PROTOCOL_GUID \
	{ 0x8D59D32B, 0xC655, 0x4AE9, { 0x9B, 0x15, 0xF2, 0x59, 0x04, 0x99, 0x2A, 0x43 } }

INTERFACE_DECL(_EFI_ABSOLUTE_POINTER_PROTOCOL);

typedef struct {
	UINT64 AbsoluteMinX;
	UINT64 AbsoluteMinY;
	UINT64 AbsoluteMinZ;
	UINT64 AbsoluteMaxX;
	UINT64 AbsoluteMaxY;
	UINT64 AbsoluteMaxZ;
	UINT32 Attributes;
} EFI_ABSOLUTE_POINTER_MODE;

typedef struct {
	UINT64 CurrentX;
	UINT64 CurrentY;
	UINT64 CurrentZ;
	UINT32 ActiveButtons;
} EFI_ABSOLUTE_POINTER_STATE;

#define EFI_ABSP_SupportsAltActive 0x00000001
#define EFI_ABSP_SupportsPressureAsZ 0x00000002
#define EFI_ABSP_TouchActive 0x00000001
#define EFI_ABS_AltActive 0x00000002

typedef
EFI_STATUS
(EFIAPI *EFI_ABSOLUTE_POINTER_RESET) (
	IN struct _EFI_ABSOLUTE_POINTER_PROTOCOL *This,
	IN BOOLEAN ExtendedVerification
);

typedef
EFI_STATUS
(EFIAPI *EFI_ABSOLUTE_POINTER_GET_STATE) (
	IN struct _EFI_ABSOLUTE_POINTER_PROTOCOL *This,
	IN OUT EFI_ABSOLUTE_POINTER_STATE *State
);

typedef struct _EFI_ABSOLUTE_POINTER_PROTOCOL {
	EFI_ABSOLUTE_POINTER_RESET Reset;
	EFI_ABSOLUTE_POINTER_GET_STATE GetState;
	EFI_EVENT WaitForInput;
	EFI_ABSOLUTE_POINTER_MODE *Mode;
} EFI_ABSOLUTE_POINTER_PROTOCOL;

#endif
/**
  EFI Shell protocol as defined in the UEFI Shell Specification 2.2.

  (C) Copyright 2014 Hewlett-Packard Development Company, L.P.<BR>
  Copyright (c) 2006 - 2018, Intel Corporation. All rights reserved.<BR>
  SPDX-License-Identifier: BSD-2-Clause-Patent

  This file is based on MdePkg/Include/Protocol/Shell.h from EDK2
  Ported to gnu-efi by Jiaqing Zhao <jiaqing.zhao@intel.com>
**/

#ifndef _EFI_SHELL_H
#define _EFI_SHELL_H

#ifndef _EFI_LINK_H
#define _EFI_LINK_H

/*++

Copyright (c) 1998  Intel Corporation

Module Name:

    link.h (renamed efilink.h to avoid conflicts)

Abstract:

    EFI link list macro's



Revision History

--*/

#ifndef EFI_NT_EMUL

//
// List entry - doubly linked list
//

typedef struct _LIST_ENTRY {
    struct _LIST_ENTRY  *Flink;
    struct _LIST_ENTRY  *Blink;
} LIST_ENTRY, EFI_LIST_ENTRY;

#endif 


//
//  VOID
//  InitializeListHead(
//      LIST_ENTRY *ListHead
//      );
//

#define InitializeListHead(ListHead) \
    (ListHead)->Flink = ListHead;    \
    (ListHead)->Blink = ListHead;

//
//  BOOLEAN
//  IsListEmpty(
//      PLIST_ENTRY ListHead
//      );
//

#define IsListEmpty(ListHead) \
    ((ListHead)->Flink == (ListHead))

//
//  VOID
//  RemoveEntryList(
//      PLIST_ENTRY Entry
//      );
//

#define _RemoveEntryList(Entry) {       \
        LIST_ENTRY *_Blink, *_Flink;    \
        _Flink = (Entry)->Flink;        \
        _Blink = (Entry)->Blink;        \
        _Blink->Flink = _Flink;         \
        _Flink->Blink = _Blink;         \
        }

#if EFI_DEBUG
    #define RemoveEntryList(Entry)                      \
        _RemoveEntryList(Entry);                        \
        (Entry)->Flink = (LIST_ENTRY *) BAD_POINTER;    \
        (Entry)->Blink = (LIST_ENTRY *) BAD_POINTER; 
#else
    #define RemoveEntryList(Entry)      \
        _RemoveEntryList(Entry);
#endif

//
//  VOID
//  InsertTailList(
//      PLIST_ENTRY ListHead,
//      PLIST_ENTRY Entry
//      );
//

#define InsertTailList(ListHead,Entry) {\
    LIST_ENTRY *_ListHead, *_Blink;     \
    _ListHead = (ListHead);             \
    _Blink = _ListHead->Blink;          \
    (Entry)->Flink = _ListHead;         \
    (Entry)->Blink = _Blink;            \
    _Blink->Flink = (Entry);            \
    _ListHead->Blink = (Entry);         \
    }

//
//  VOID
//  InsertHeadList(
//      PLIST_ENTRY ListHead,
//      PLIST_ENTRY Entry
//      );
//

#define InsertHeadList(ListHead,Entry) {\
    LIST_ENTRY *_ListHead, *_Flink;     \
    _ListHead = (ListHead);             \
    _Flink = _ListHead->Flink;          \
    (Entry)->Flink = _Flink;            \
    (Entry)->Blink = _ListHead;         \
    _Flink->Blink = (Entry);            \
    _ListHead->Flink = (Entry);         \
    }

//  VOID
//  SwapListEntries(
//      PLIST_ENTRY Entry1,
//      PLIST_ENTRY Entry2
//      );
//
// Put Entry2 before Entry1
//
#define SwapListEntries(Entry1,Entry2) {\
    LIST_ENTRY *Entry1Flink, *Entry1Blink;     \
    LIST_ENTRY *Entry2Flink, *Entry2Blink;     \
    Entry2Flink = (Entry2)->Flink;             \
    Entry2Blink = (Entry2)->Blink;             \
    Entry1Flink = (Entry1)->Flink;             \
    Entry1Blink = (Entry1)->Blink;             \
    Entry2Blink->Flink = Entry2Flink;       \
    Entry2Flink->Blink = Entry2Blink;        \
    (Entry2)->Flink = Entry1;               \
    (Entry2)->Blink = Entry1Blink;          \
    Entry1Blink->Flink = (Entry2);            \
    (Entry1)->Blink = (Entry2);             \
    }

//
//  EFI_FIELD_OFFSET - returns the byte offset to a field within a structure
//

#define EFI_FIELD_OFFSET(TYPE,Field) ((UINTN)(intptr_t)(&(((TYPE *) 0)->Field)))

//
//  CONTAINING_RECORD - returns a pointer to the structure
//      from one of it's elements.
//

#define _CR(Record, TYPE, Field)  \
    ((TYPE *) ( (CHAR8 *)(Record) - (CHAR8 *) &(((TYPE *) 0)->Field)))

//
// EDK2 uses BASE_CR for the above
//
#define BASE_CR _CR

#if EFI_DEBUG
    #define CR(Record, TYPE, Field, Sig)     \
        _CR(Record, TYPE, Field)->Signature != Sig ?        \
            (TYPE *) ASSERT_STRUCT(_CR(Record, TYPE, Field), Record) : \
            _CR(Record, TYPE, Field)
#else
    #define CR(Record, TYPE, Field, Signature)   \
        _CR(Record, TYPE, Field)                           
#endif


//
// A lock structure
//

typedef struct _FLOCK {
    EFI_TPL     Tpl;
    EFI_TPL     OwnerTpl;
    UINTN       Lock;
} FLOCK;

#endif


#define EFI_SHELL_PROTOCOL_GUID \
    { 0x6302d008, 0x7f9b, 0x4f30, { 0x87, 0xac, 0x60, 0xc9, 0xfe, 0xf5, 0xda, 0x4e } }

INTERFACE_DECL(_EFI_SHELL_PROTOCOL);

typedef enum {
    SHELL_SUCCESS              = 0,
    SHELL_LOAD_ERROR           = 1,
    SHELL_INVALID_PARAMETER    = 2,
    SHELL_UNSUPPORTED          = 3,
    SHELL_BAD_BUFFER_SIZE      = 4,
    SHELL_BUFFER_TOO_SMALL     = 5,
    SHELL_NOT_READY            = 6,
    SHELL_DEVICE_ERROR         = 7,
    SHELL_WRITE_PROTECTED      = 8,
    SHELL_OUT_OF_RESOURCES     = 9,
    SHELL_VOLUME_CORRUPTED     = 10,
    SHELL_VOLUME_FULL          = 11,
    SHELL_NO_MEDIA             = 12,
    SHELL_MEDIA_CHANGED        = 13,
    SHELL_NOT_FOUND            = 14,
    SHELL_ACCESS_DENIED        = 15,
    SHELL_TIMEOUT              = 18,
    SHELL_NOT_STARTED          = 19,
    SHELL_ALREADY_STARTED      = 20,
    SHELL_ABORTED              = 21,
    SHELL_INCOMPATIBLE_VERSION = 25,
    SHELL_SECURITY_VIOLATION   = 26,
    SHELL_NOT_EQUAL            = 27
} SHELL_STATUS;

typedef VOID *SHELL_FILE_HANDLE;

typedef struct {
    EFI_LIST_ENTRY    Link;
    EFI_STATUS        Status;
    CONST CHAR16      *FullName;
    CONST CHAR16      *FileName;
    SHELL_FILE_HANDLE Handle;
    EFI_FILE_INFO     *Info;
} EFI_SHELL_FILE_INFO;

typedef
BOOLEAN
(EFIAPI *EFI_SHELL_BATCH_IS_ACTIVE) (
    VOID
    );

typedef
EFI_STATUS
(EFIAPI *EFI_SHELL_CLOSE_FILE) (
    IN SHELL_FILE_HANDLE FileHandle
    );

typedef
EFI_STATUS
(EFIAPI *EFI_SHELL_CREATE_FILE) (
    IN CONST CHAR16       *FileName,
    IN UINT64             FileAttribs,
    OUT SHELL_FILE_HANDLE *FileHandle
    );

typedef
EFI_STATUS
(EFIAPI *EFI_SHELL_DELETE_FILE) (
    IN SHELL_FILE_HANDLE FileHandle
    );

typedef
EFI_STATUS
(EFIAPI *EFI_SHELL_DELETE_FILE_BY_NAME) (
    IN CONST CHAR16 *FileName
    );

typedef
VOID
(EFIAPI *EFI_SHELL_DISABLE_PAGE_BREAK) (
    VOID
    );

typedef
VOID
(EFIAPI *EFI_SHELL_ENABLE_PAGE_BREAK) (
    VOID
    );

typedef
EFI_STATUS
(EFIAPI *EFI_SHELL_EXECUTE) (
    IN EFI_HANDLE  *ParentImageHandle,
    IN CHAR16      *CommandLine OPTIONAL,
    IN CHAR16      **Environment OPTIONAL,
    OUT EFI_STATUS *StatusCode OPTIONAL
    );

typedef
EFI_STATUS
(EFIAPI *EFI_SHELL_FIND_FILES) (
    IN CONST CHAR16         *FilePattern,
    OUT EFI_SHELL_FILE_INFO **FileList
    );

typedef
EFI_STATUS
(EFIAPI *EFI_SHELL_FIND_FILES_IN_DIR) (
    IN SHELL_FILE_HANDLE    FileDirHandle,
    OUT EFI_SHELL_FILE_INFO **FileList
    );

typedef
EFI_STATUS
(EFIAPI *EFI_SHELL_FLUSH_FILE) (
    IN SHELL_FILE_HANDLE FileHandle
    );

typedef
EFI_STATUS
(EFIAPI *EFI_SHELL_FREE_FILE_LIST) (
    IN EFI_SHELL_FILE_INFO **FileList
    );

typedef
CONST CHAR16 *
(EFIAPI *EFI_SHELL_GET_ALIAS) (
  IN  CONST CHAR16 *Alias,
  OUT BOOLEAN      *Volatile OPTIONAL
  );

typedef
CONST CHAR16 *
(EFIAPI *EFI_SHELL_GET_CUR_DIR) (
  IN CONST CHAR16 *FileSystemMapping OPTIONAL
  );

typedef UINT32 EFI_SHELL_DEVICE_NAME_FLAGS;
#define EFI_DEVICE_NAME_USE_COMPONENT_NAME 0x00000001
#define EFI_DEVICE_NAME_USE_DEVICE_PATH    0x00000002

typedef
EFI_STATUS
(EFIAPI *EFI_SHELL_GET_DEVICE_NAME) (
    IN EFI_HANDLE                   DeviceHandle,
    IN EFI_SHELL_DEVICE_NAME_FLAGS  Flags,
    IN CHAR8                        *Language,
    OUT CHAR16                      **BestDeviceName
    );

typedef
CONST EFI_DEVICE_PATH_PROTOCOL *
(EFIAPI *EFI_SHELL_GET_DEVICE_PATH_FROM_MAP) (
    IN CONST CHAR16 *Mapping
    );

typedef
EFI_DEVICE_PATH_PROTOCOL *
(EFIAPI *EFI_SHELL_GET_DEVICE_PATH_FROM_FILE_PATH) (
    IN CONST CHAR16 *Path
    );

typedef
CONST CHAR16 *
(EFIAPI *EFI_SHELL_GET_ENV) (
    IN CONST CHAR16 *Name
    );

typedef
CONST CHAR16 *
(EFIAPI *EFI_SHELL_GET_ENV_EX) (
    IN CONST CHAR16 *Name,
    OUT UINT32      *Attributes OPTIONAL
    );

typedef
EFI_FILE_INFO *
(EFIAPI *EFI_SHELL_GET_FILE_INFO) (
    IN SHELL_FILE_HANDLE FileHandle
    );

typedef
CHAR16 *
(EFIAPI *EFI_SHELL_GET_FILE_PATH_FROM_DEVICE_PATH) (
    IN CONST EFI_DEVICE_PATH_PROTOCOL *Path
    );

typedef
EFI_STATUS
(EFIAPI *EFI_SHELL_GET_FILE_POSITION) (
    IN SHELL_FILE_HANDLE FileHandle,
    OUT UINT64           *Position
    );

typedef
EFI_STATUS
(EFIAPI *EFI_SHELL_GET_FILE_SIZE) (
    IN SHELL_FILE_HANDLE FileHandle,
    OUT UINT64           *Size
    );

typedef
EFI_STATUS
(EFIAPI *EFI_SHELL_GET_GUID_FROM_NAME) (
    IN CONST CHAR16 *GuidName,
    OUT EFI_GUID    *Guid
    );

typedef
EFI_STATUS
(EFIAPI *EFI_SHELL_GET_GUID_NAME)(
    IN CONST EFI_GUID *Guid,
    OUT CONST CHAR16  **GuidName
    );

typedef
EFI_STATUS
(EFIAPI *EFI_SHELL_GET_HELP_TEXT) (
    IN CONST CHAR16 *Command,
    IN CONST CHAR16 *Sections,
    OUT CHAR16      **HelpText
    );

typedef
CONST CHAR16 *
(EFIAPI *EFI_SHELL_GET_MAP_FROM_DEVICE_PATH) (
    IN OUT EFI_DEVICE_PATH_PROTOCOL **DevicePath
    );

typedef
BOOLEAN
(EFIAPI *EFI_SHELL_GET_PAGE_BREAK) (
    VOID
    );

typedef
BOOLEAN
(EFIAPI *EFI_SHELL_IS_ROOT_SHELL) (
    VOID
    );

typedef
EFI_STATUS
(EFIAPI *EFI_SHELL_OPEN_FILE_BY_NAME) (
    IN CONST CHAR16       *FileName,
    OUT SHELL_FILE_HANDLE *FileHandle,
    IN UINT64             OpenMode
    );

typedef
EFI_STATUS
(EFIAPI *EFI_SHELL_OPEN_FILE_LIST) (
    IN CHAR16                  *Path,
    IN UINT64                  OpenMode,
    IN OUT EFI_SHELL_FILE_INFO **FileList
    );

typedef
EFI_STATUS
(EFIAPI *EFI_SHELL_OPEN_ROOT) (
    IN EFI_DEVICE_PATH_PROTOCOL *DevicePath,
    OUT SHELL_FILE_HANDLE       *FileHandle
    );

typedef
EFI_STATUS
(EFIAPI *EFI_SHELL_OPEN_ROOT_BY_HANDLE) (
    IN EFI_HANDLE         DeviceHandle,
    OUT SHELL_FILE_HANDLE *FileHandle
    );

typedef
EFI_STATUS
(EFIAPI *EFI_SHELL_READ_FILE) (
    IN SHELL_FILE_HANDLE FileHandle,
    IN OUT UINTN         *ReadSize,
    IN OUT VOID          *Buffer
    );

typedef
EFI_STATUS
(EFIAPI *EFI_SHELL_REGISTER_GUID_NAME) (
    IN CONST EFI_GUID *Guid,
    IN CONST CHAR16   *GuidName
    );

typedef
EFI_STATUS
(EFIAPI *EFI_SHELL_REMOVE_DUP_IN_FILE_LIST) (
    IN EFI_SHELL_FILE_INFO **FileList
    );

typedef
EFI_STATUS
(EFIAPI *EFI_SHELL_SET_ALIAS) (
    IN CONST CHAR16 *Command,
    IN CONST CHAR16 *Alias,
    IN BOOLEAN      Replace,
    IN BOOLEAN      Volatile
    );

typedef
EFI_STATUS
(EFIAPI *EFI_SHELL_SET_CUR_DIR) (
    IN CONST CHAR16 *FileSystem OPTIONAL,
    IN CONST CHAR16 *Dir
    );

typedef
EFI_STATUS
(EFIAPI *EFI_SHELL_SET_ENV) (
    IN CONST CHAR16 *Name,
    IN CONST CHAR16 *Value,
    IN BOOLEAN      Volatile
    );

typedef
EFI_STATUS
(EFIAPI *EFI_SHELL_SET_FILE_INFO) (
    IN SHELL_FILE_HANDLE   FileHandle,
    IN CONST EFI_FILE_INFO *FileInfo
    );

typedef
EFI_STATUS
(EFIAPI *EFI_SHELL_SET_FILE_POSITION) (
    IN SHELL_FILE_HANDLE FileHandle,
    IN UINT64            Position
    );

typedef
EFI_STATUS
(EFIAPI *EFI_SHELL_SET_MAP) (
    IN CONST EFI_DEVICE_PATH_PROTOCOL *DevicePath,
    IN CONST CHAR16                   *Mapping
    );

typedef
EFI_STATUS
(EFIAPI *EFI_SHELL_WRITE_FILE) (
    IN SHELL_FILE_HANDLE FileHandle,
    IN OUT UINTN         *BufferSize,
    IN VOID              *Buffer
    );

typedef struct _EFI_SHELL_PROTOCOL {
    EFI_SHELL_EXECUTE                         Execute;
    EFI_SHELL_GET_ENV                         GetEnv;
    EFI_SHELL_SET_ENV                         SetEnv;
    EFI_SHELL_GET_ALIAS                       GetAlias;
    EFI_SHELL_SET_ALIAS                       SetAlias;
    EFI_SHELL_GET_HELP_TEXT                   GetHelpText;
    EFI_SHELL_GET_DEVICE_PATH_FROM_MAP        GetDevicePathFromMap;
    EFI_SHELL_GET_MAP_FROM_DEVICE_PATH        GetMapFromDevicePath;
    EFI_SHELL_GET_DEVICE_PATH_FROM_FILE_PATH  GetDevicePathFromFilePath;
    EFI_SHELL_GET_FILE_PATH_FROM_DEVICE_PATH  GetFilePathFromDevicePath;
    EFI_SHELL_SET_MAP                         SetMap;
    EFI_SHELL_GET_CUR_DIR                     GetCurDir;
    EFI_SHELL_SET_CUR_DIR                     SetCurDir;
    EFI_SHELL_OPEN_FILE_LIST                  OpenFileList;
    EFI_SHELL_FREE_FILE_LIST                  FreeFileList;
    EFI_SHELL_REMOVE_DUP_IN_FILE_LIST         RemoveDupInFileList;
    EFI_SHELL_BATCH_IS_ACTIVE                 BatchIsActive;
    EFI_SHELL_IS_ROOT_SHELL                   IsRootShell;
    EFI_SHELL_ENABLE_PAGE_BREAK               EnablePageBreak;
    EFI_SHELL_DISABLE_PAGE_BREAK              DisablePageBreak;
    EFI_SHELL_GET_PAGE_BREAK                  GetPageBreak;
    EFI_SHELL_GET_DEVICE_NAME                 GetDeviceName;
    EFI_SHELL_GET_FILE_INFO                   GetFileInfo;
    EFI_SHELL_SET_FILE_INFO                   SetFileInfo;
    EFI_SHELL_OPEN_FILE_BY_NAME               OpenFileByName;
    EFI_SHELL_CLOSE_FILE                      CloseFile;
    EFI_SHELL_CREATE_FILE                     CreateFile;
    EFI_SHELL_READ_FILE                       ReadFile;
    EFI_SHELL_WRITE_FILE                      WriteFile;
    EFI_SHELL_DELETE_FILE                     DeleteFile;
    EFI_SHELL_DELETE_FILE_BY_NAME             DeleteFileByName;
    EFI_SHELL_GET_FILE_POSITION               GetFilePosition;
    EFI_SHELL_SET_FILE_POSITION               SetFilePosition;
    EFI_SHELL_FLUSH_FILE                      FlushFile;
    EFI_SHELL_FIND_FILES                      FindFiles;
    EFI_SHELL_FIND_FILES_IN_DIR               FindFilesInDir;
    EFI_SHELL_GET_FILE_SIZE                   GetFileSize;
    EFI_SHELL_OPEN_ROOT                       OpenRoot;
    EFI_SHELL_OPEN_ROOT_BY_HANDLE             OpenRootByHandle;
    EFI_EVENT                                 ExecutionBreak;
    UINT32                                    MajorVersion;
    UINT32                                    MinorVersion;
    // Added for Shell 2.1
    EFI_SHELL_REGISTER_GUID_NAME              RegisterGuidName;
    EFI_SHELL_GET_GUID_NAME                   GetGuidName;
    EFI_SHELL_GET_GUID_FROM_NAME              GetGuidFromName;
    EFI_SHELL_GET_ENV_EX                      GetEnvEx;
} EFI_SHELL_PROTOCOL;

#define EFI_SHELL_PARAMETERS_PROTOCOL_GUID \
    { 0x752f3136, 0x4e16, 0x4fdc, { 0xa2, 0x2a, 0xe5, 0xf4, 0x68, 0x12, 0xf4, 0xca } }

INTERFACE_DECL(_EFI_SHELL_PARAMETERS_PROTOCOL);

typedef struct _EFI_SHELL_PARAMETERS_PROTOCOL {
    CHAR16            **Argv;
    UINTN             Argc;
    SHELL_FILE_HANDLE StdIn;
    SHELL_FILE_HANDLE StdOut;
    SHELL_FILE_HANDLE StdErr;
} EFI_SHELL_PARAMETERS_PROTOCOL;

#define EFI_SHELL_DYNAMIC_COMMAND_PROTOCOL_GUID \
    { 0x3c7200e9, 0x005f, 0x4ea4, { 0x87, 0xde, 0xa3, 0xdf, 0xac, 0x8a, 0x27, 0xc3 } }

INTERFACE_DECL(_EFI_SHELL_DYNAMIC_COMMAND_PROTOCOL);

typedef
SHELL_STATUS
(EFIAPI *SHELL_COMMAND_HANDLER)(
    IN struct _EFI_SHELL_DYNAMIC_COMMAND_PROTOCOL *This,
    IN EFI_SYSTEM_TABLE                           *SystemTable,
    IN EFI_SHELL_PARAMETERS_PROTOCOL              *ShellParameters,
    IN EFI_SHELL_PROTOCOL                         *Shell
    );

typedef
CHAR16*
(EFIAPI *SHELL_COMMAND_GETHELP)(
    IN struct _EFI_SHELL_DYNAMIC_COMMAND_PROTOCOL *This,
    IN CONST CHAR8                                *Language
    );

typedef struct _EFI_SHELL_DYNAMIC_COMMAND_PROTOCOL {
    CONST CHAR16          *CommandName;
    SHELL_COMMAND_HANDLER Handler;
    SHELL_COMMAND_GETHELP GetHelp;
} EFI_SHELL_DYNAMIC_COMMAND_PROTOCOL;

#endif

#endif
