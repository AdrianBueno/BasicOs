
struct JoinPoint { 
	void** (*fp) (struct JoinPoint *);
	void ** args;
	int argsCount;
	const char ** argsType;
	 void * (*arg)(int, struct JoinPoint *); 
	 const char * (*argType)(int , struct JoinPoint *); 
	void ** retValue;
	const char * retType;
	const char * funcName ;
	const char * targetName ;
	const char * fileName ;
	const char * kind ;
	void * excep_return ;
};

 struct __UTAC__EXCEPTION {
	void * jumpbuf ;
	unsigned long long int prtValue ;
	int pops;
	struct __UTAC__CFLOW_FUNC {
		int (*func)(int,int) ;
		int val ;
		struct __UTAC__CFLOW_FUNC * next; 
	} * cflowfuncs; 
}; 


# 1 "Processor.c" 
# 1 "<built-in>" 
# 1 "<command-line>" 
# 1 "Processor.c" 
# 1 "./Processor.h" 1
# 1 "./MainMemory.h" 1
# 1 "./Simulator.h" 1
# 15 "./MainMemory.h" 2
typedef struct {char operationCode; int operand1; int operand2; 
}MEMORYCELL; 
#line 18 "./MainMemory.h"
void MainMemory_readMemory(); 
#line 19 "./MainMemory.h"
void MainMemory_writeMemory(); 
#line 21 "./MainMemory.h"
extern  MEMORYCELL registerMBR_MainMemory; 
#line 22 "./MainMemory.h"
extern int registerMAR_MainMemory; 
#line 12 "./Processor.h"
enum PSW_BITS {POWEROFF_BIT=0,IOEND_BIT=1,CLOCKINT_BIT=2,EXCEPTION_BIT=8,SYSCALL_BIT=9}; 
#line 14 "./Processor.h"
enum EXCEPTIONS {DIVISIONBYZERO,INVALIDADDRESS,INVALIDINSTRUCTION}; 
#line 16 "./Processor.h"
void Processor_InitializeInterruptVectorTable(); 
#line 17 "./Processor.h"
void Processor_InstructionCycleLoop(); 
#line 18 "./Processor.h"
void Processor_FetchInstruction(); 
#line 19 "./Processor.h"
void Processor_DecodeAndExecuteInstruction(); 
#line 20 "./Processor.h"
void Processor_ManageInterrupts(); 
#line 21 "./Processor.h"
void Processor_CopyInSystemStack(int , int ); 
#line 22 "./Processor.h"
void Processor_ActivateBit(const unsigned int ); 
#line 23 "./Processor.h"
void Processor_DeactivateBit(const unsigned int ); 
#line 24 "./Processor.h"
unsigned int Processor_BitState(const unsigned int ); 
#line 25 "./Processor.h"
void Processor_RaiseException(int ); 
#line 28 "./Processor.h"
extern  MEMORYCELL registerMBR_CPU; 
#line 29 "./Processor.h"
extern int registerMAR_CPU; 
#line 33 "./Processor.h"
extern int registerPC_CPU; 
#line 38 "./Processor.h"
extern int registerAccumulator_CPU; 
#line 43 "./Processor.h"
extern int registerA_CPU; 
#line 46 "./Processor.h"
extern int registerB_CPU; 
# 5 "./Processor.h" 2
# 2 "Processor.c" 2
# 1 "./ComputerSystem.h" 1
# 5 "./Clock.h" 1
void Clock_Update(); 
#line 6 "./Clock.h"
int Clock_GetTime(); 
#line 8 "./ComputerSystem.h"
void ComputerSystem_PowerOn(int argc, char *argv[]); 
#line 9 "./ComputerSystem.h"
void ComputerSystem_PowerOff(); 
#line 10 "./ComputerSystem.h"
void ComputerSystem_DebugMessage(char , char *, ...); 
#line 11 "./ComputerSystem.h"
void ComputerSystem_ShowPartitionsUse(); 
#line 12 "./ComputerSystem.h"
int ComputerSystem_ObtainProgramList(int argc, char *argv[]); 
#line 13 "./ComputerSystem.h"
void ComputerSystem_PrintProgramList(); 
# 6 "./ComputerSystem.h" 2
# 37 "./ComputerSystem.h" 
typedef struct UserProgramsData {char *executableName; unsigned int arrivalTime; 
}USER_PROGRAMS_DATA; 
#line 41 "./ComputerSystem.h"
extern  USER_PROGRAMS_DATA *userProgramsList[20]; 
#line 42 "./ComputerSystem.h"
extern int registerAccumulator_CPU; 
#line 43 "./ComputerSystem.h"
extern int registerPC_CPU; 
#line 44 "./ComputerSystem.h"
extern int registerPSW_CPU; 
# 3 "Processor.c" 2
# 1 "./OperatingSystem.h" 1
# 1 "/usr/include/stdio.h" 1 3 4
# 28 "/usr/include/stdio.h" 3 4
# 1 "/usr/include/features.h" 1 3 4
# 313 "/usr/include/features.h" 3 4
# 1 "/usr/include/bits/predefs.h" 1 3 4
# 314 "/usr/include/features.h" 2 3 4
# 346 "/usr/include/features.h" 3 4
# 1 "/usr/include/sys/cdefs.h" 1 3 4
# 353 "/usr/include/sys/cdefs.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 354 "/usr/include/sys/cdefs.h" 2 3 4
# 347 "/usr/include/features.h" 2 3 4
# 378 "/usr/include/features.h" 3 4
# 1 "/usr/include/gnu/stubs.h" 1 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 5 "/usr/include/gnu/stubs.h" 2 3 4
# 1 "/usr/include/gnu/stubs-64.h" 1 3 4
# 10 "/usr/include/gnu/stubs.h" 2 3 4
# 379 "/usr/include/features.h" 2 3 4
# 29 "/usr/include/stdio.h" 2 3 4
# 1 "/usr/lib/gcc/x86_64-linux-gnu/4.4.5/include/stddef.h" 1 3 4
# 211 "/usr/lib/gcc/x86_64-linux-gnu/4.4.5/include/stddef.h" 3 4
typedef long unsigned int size_t; 
# 35 "/usr/include/stdio.h" 2 3 4
# 1 "/usr/include/bits/types.h" 1 3 4
# 28 "/usr/include/bits/types.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 31 "/usr/include/bits/types.h" 2 3 4
typedef unsigned char __u_char; 
#line 32 "/usr/include/bits/types.h"
typedef unsigned short int __u_short; 
#line 33 "/usr/include/bits/types.h"
typedef unsigned int __u_int; 
#line 34 "/usr/include/bits/types.h"
typedef unsigned long int __u_long; 
#line 37 "/usr/include/bits/types.h"
typedef signed char __int8_t; 
#line 38 "/usr/include/bits/types.h"
typedef unsigned char __uint8_t; 
#line 39 "/usr/include/bits/types.h"
typedef signed short int __int16_t; 
#line 40 "/usr/include/bits/types.h"
typedef unsigned short int __uint16_t; 
#line 41 "/usr/include/bits/types.h"
typedef signed int __int32_t; 
#line 42 "/usr/include/bits/types.h"
typedef unsigned int __uint32_t; 
#line 44 "/usr/include/bits/types.h"
typedef signed long int __int64_t; 
#line 45 "/usr/include/bits/types.h"
typedef unsigned long int __uint64_t; 
#line 53 "/usr/include/bits/types.h"
typedef long int __quad_t; 
#line 54 "/usr/include/bits/types.h"
typedef unsigned long int __u_quad_t; 
# 131 "/usr/include/bits/types.h" 3 4
# 1 "/usr/include/bits/typesizes.h" 1 3 4
# 134 "/usr/include/bits/types.h" 2 3 4
typedef unsigned long int __dev_t; 
#line 135 "/usr/include/bits/types.h"
typedef unsigned int __uid_t; 
#line 136 "/usr/include/bits/types.h"
typedef unsigned int __gid_t; 
#line 137 "/usr/include/bits/types.h"
typedef unsigned long int __ino_t; 
#line 138 "/usr/include/bits/types.h"
typedef unsigned long int __ino64_t; 
#line 139 "/usr/include/bits/types.h"
typedef unsigned int __mode_t; 
#line 140 "/usr/include/bits/types.h"
typedef unsigned long int __nlink_t; 
#line 141 "/usr/include/bits/types.h"
typedef long int __off_t; 
#line 142 "/usr/include/bits/types.h"
typedef long int __off64_t; 
#line 143 "/usr/include/bits/types.h"
typedef int __pid_t; 
#line 144 "/usr/include/bits/types.h"
typedef struct {int __val[2]; 
}__fsid_t; 
#line 145 "/usr/include/bits/types.h"
typedef long int __clock_t; 
#line 146 "/usr/include/bits/types.h"
typedef unsigned long int __rlim_t; 
#line 147 "/usr/include/bits/types.h"
typedef unsigned long int __rlim64_t; 
#line 148 "/usr/include/bits/types.h"
typedef unsigned int __id_t; 
#line 149 "/usr/include/bits/types.h"
typedef long int __time_t; 
#line 150 "/usr/include/bits/types.h"
typedef unsigned int __useconds_t; 
#line 151 "/usr/include/bits/types.h"
typedef long int __suseconds_t; 
#line 153 "/usr/include/bits/types.h"
typedef int __daddr_t; 
#line 154 "/usr/include/bits/types.h"
typedef long int __swblk_t; 
#line 155 "/usr/include/bits/types.h"
typedef int __key_t; 
#line 158 "/usr/include/bits/types.h"
typedef int __clockid_t; 
#line 161 "/usr/include/bits/types.h"
typedef void *__timer_t; 
#line 164 "/usr/include/bits/types.h"
typedef long int __blksize_t; 
#line 169 "/usr/include/bits/types.h"
typedef long int __blkcnt_t; 
#line 170 "/usr/include/bits/types.h"
typedef long int __blkcnt64_t; 
#line 173 "/usr/include/bits/types.h"
typedef unsigned long int __fsblkcnt_t; 
#line 174 "/usr/include/bits/types.h"
typedef unsigned long int __fsblkcnt64_t; 
#line 177 "/usr/include/bits/types.h"
typedef unsigned long int __fsfilcnt_t; 
#line 178 "/usr/include/bits/types.h"
typedef unsigned long int __fsfilcnt64_t; 
#line 180 "/usr/include/bits/types.h"
typedef long int __ssize_t; 
#line 184 "/usr/include/bits/types.h"
typedef  __off64_t __loff_t; 
#line 185 "/usr/include/bits/types.h"
typedef  __quad_t *__qaddr_t; 
#line 186 "/usr/include/bits/types.h"
typedef char *__caddr_t; 
#line 189 "/usr/include/bits/types.h"
typedef long int __intptr_t; 
#line 192 "/usr/include/bits/types.h"
typedef unsigned int __socklen_t; 
# 37 "/usr/include/stdio.h" 2 3 4
# 45 "/usr/include/stdio.h" 3 4
struct _IO_FILE ; 
#line 49 "/usr/include/stdio.h"
typedef struct _IO_FILE FILE; 
#line 65 "/usr/include/stdio.h"
typedef struct _IO_FILE __FILE; 
# 65 "/usr/include/stdio.h" 3 4
# 75 "/usr/include/stdio.h" 3 4
# 1 "/usr/include/libio.h" 1 3 4
# 32 "/usr/include/libio.h" 3 4
# 1 "/usr/include/_G_config.h" 1 3 4
# 15 "/usr/include/_G_config.h" 3 4
# 1 "/usr/lib/gcc/x86_64-linux-gnu/4.4.5/include/stddef.h" 1 3 4
# 16 "/usr/include/_G_config.h" 2 3 4
# 1 "/usr/include/wchar.h" 1 3 4
# 95 "/usr/include/wchar.h" 3 4
typedef struct {int __count; union {unsigned int __wch; char __wchb[4]; 
}__value; 
}__mbstate_t; 
#line 26 "/usr/include/_G_config.h"
typedef struct { __off_t __pos;  __mbstate_t __state; 
}_G_fpos_t; 
#line 31 "/usr/include/_G_config.h"
typedef struct { __off64_t __pos;  __mbstate_t __state; 
}_G_fpos64_t; 
# 21 "/usr/include/_G_config.h" 2 3 4
# 53 "/usr/include/_G_config.h" 3 4
typedef int _G_int16_t __attribute__  (( __mode__ ( __HI__ )  )) ; 
#line 54 "/usr/include/_G_config.h"
typedef int _G_int32_t __attribute__  (( __mode__ ( __SI__ )  )) ; 
#line 55 "/usr/include/_G_config.h"
typedef unsigned int _G_uint16_t __attribute__  (( __mode__ ( __HI__ )  )) ; 
#line 56 "/usr/include/_G_config.h"
typedef unsigned int _G_uint32_t __attribute__  (( __mode__ ( __SI__ )  )) ; 
# 33 "/usr/include/libio.h" 2 3 4
# 53 "/usr/include/libio.h" 3 4
# 1 "/usr/lib/gcc/x86_64-linux-gnu/4.4.5/include/stdarg.h" 1 3 4
# 40 "/usr/lib/gcc/x86_64-linux-gnu/4.4.5/include/stdarg.h" 3 4
typedef __builtin_va_list __gnuc_va_list; 
# 54 "/usr/include/libio.h" 2 3 4
# 170 "/usr/include/libio.h" 3 4
struct _IO_jump_t ; 
#line 170 "/usr/include/libio.h"
struct _IO_FILE ; 
#line 180 "/usr/include/libio.h"
typedef void _IO_lock_t; 
# 180 "/usr/include/libio.h" 3 4
# 203 "/usr/include/libio.h" 3 4
struct _IO_marker {struct _IO_marker *_next; struct _IO_FILE *_sbuf; int _pos; 
}; 
#line 212 "/usr/include/libio.h"
enum __codecvt_result {__codecvt_ok,__codecvt_partial,__codecvt_error,__codecvt_noconv}; 
# 271 "/usr/include/libio.h" 3 4
# 319 "/usr/include/libio.h" 3 4
# 338 "/usr/include/libio.h" 3 4
struct _IO_FILE {int _flags; char *_IO_read_ptr; char *_IO_read_end; char *_IO_read_base; char *_IO_write_base; char *_IO_write_ptr; char *_IO_write_end; char *_IO_buf_base; char *_IO_buf_end; char *_IO_save_base; char *_IO_backup_base; char *_IO_save_end; struct _IO_marker *_markers; struct _IO_FILE *_chain; int _fileno; int _flags2;  __off_t _old_offset; unsigned short _cur_column; signed char _vtable_offset; char _shortbuf[1];  _IO_lock_t *_lock;  __off64_t _offset; void *__pad1; void *__pad2; void *__pad3; void *__pad4;  size_t __pad5; int _mode; char _unused2[15 * sizeof (int ) - 4 * sizeof (void *) - sizeof ( size_t )]; 
}; 
#line 341 "/usr/include/libio.h"
typedef struct _IO_FILE _IO_FILE; 
#line 344 "/usr/include/libio.h"
struct _IO_FILE_plus ; 
#line 346 "/usr/include/libio.h"
extern struct _IO_FILE_plus _IO_2_1_stdin_; 
#line 347 "/usr/include/libio.h"
extern struct _IO_FILE_plus _IO_2_1_stdout_; 
#line 348 "/usr/include/libio.h"
extern struct _IO_FILE_plus _IO_2_1_stderr_; 
#line 364 "/usr/include/libio.h"
typedef  __ssize_t __io_read_fn(void *__cookie, char *__buf,  size_t __nbytes); 
#line 373 "/usr/include/libio.h"
typedef  __ssize_t __io_write_fn(void *__cookie, __const char *__buf,  size_t __n); 
#line 381 "/usr/include/libio.h"
typedef int __io_seek_fn(void *__cookie,  __off64_t *__pos, int __w); 
#line 384 "/usr/include/libio.h"
typedef int __io_close_fn(void *__cookie); 
# 364 "/usr/include/libio.h" 3 4
# 416 "/usr/include/libio.h" 3 4
extern int __underflow( _IO_FILE *); 
#line 417 "/usr/include/libio.h"
extern int __uflow( _IO_FILE *); 
#line 418 "/usr/include/libio.h"
extern int __overflow( _IO_FILE *, int ); 
#line 460 "/usr/include/libio.h"
extern int _IO_getc( _IO_FILE *__fp); 
#line 461 "/usr/include/libio.h"
extern int _IO_putc(int __c,  _IO_FILE *__fp); 
#line 462 "/usr/include/libio.h"
extern int _IO_feof( _IO_FILE *__fp) __attribute__  (( __nothrow__ )) ; 
#line 463 "/usr/include/libio.h"
extern int _IO_ferror( _IO_FILE *__fp) __attribute__  (( __nothrow__ )) ; 
#line 465 "/usr/include/libio.h"
extern int _IO_peekc_locked( _IO_FILE *__fp); 
#line 471 "/usr/include/libio.h"
extern void _IO_flockfile( _IO_FILE *) __attribute__  (( __nothrow__ )) ; 
#line 472 "/usr/include/libio.h"
extern void _IO_funlockfile( _IO_FILE *) __attribute__  (( __nothrow__ )) ; 
#line 473 "/usr/include/libio.h"
extern int _IO_ftrylockfile( _IO_FILE *) __attribute__  (( __nothrow__ )) ; 
# 460 "/usr/include/libio.h" 3 4
# 491 "/usr/include/libio.h" 3 4
extern int _IO_vfscanf( _IO_FILE *__restrict , const char *__restrict ,  __gnuc_va_list , int *__restrict ); 
#line 493 "/usr/include/libio.h"
extern int _IO_vfprintf( _IO_FILE *__restrict , const char *__restrict ,  __gnuc_va_list ); 
#line 494 "/usr/include/libio.h"
extern  __ssize_t _IO_padn( _IO_FILE *, int ,  __ssize_t ); 
#line 495 "/usr/include/libio.h"
extern  size_t _IO_sgetn( _IO_FILE *, void *,  size_t ); 
#line 497 "/usr/include/libio.h"
extern  __off64_t _IO_seekoff( _IO_FILE *,  __off64_t , int , int ); 
#line 498 "/usr/include/libio.h"
extern  __off64_t _IO_seekpos( _IO_FILE *,  __off64_t , int ); 
#line 500 "/usr/include/libio.h"
extern void _IO_free_backup_area( _IO_FILE *) __attribute__  (( __nothrow__ )) ; 
# 76 "/usr/include/stdio.h" 2 3 4
# 91 "/usr/include/stdio.h" 3 4
typedef  _G_fpos_t fpos_t; 
# 141 "/usr/include/stdio.h" 3 4
# 1 "/usr/include/bits/stdio_lim.h" 1 3 4
# 145 "/usr/include/stdio.h" 2 3 4
extern struct _IO_FILE *stdin; 
#line 146 "/usr/include/stdio.h"
extern struct _IO_FILE *stdout; 
#line 147 "/usr/include/stdio.h"
extern struct _IO_FILE *stderr; 
#line 155 "/usr/include/stdio.h"
extern int remove(__const char *__filename) __attribute__  (( __nothrow__ )) ; 
#line 157 "/usr/include/stdio.h"
extern int rename(__const char *__old, __const char *__new) __attribute__  (( __nothrow__ )) ; 
#line 163 "/usr/include/stdio.h"
extern int renameat(int __oldfd, __const char *__old, int __newfd, __const char *__new) __attribute__  (( __nothrow__ )) ; 
#line 172 "/usr/include/stdio.h"
extern  FILE *tmpfile(void ); 
#line 186 "/usr/include/stdio.h"
extern char *tmpnam(char *__s) __attribute__  (( __nothrow__ )) ; 
#line 192 "/usr/include/stdio.h"
extern char *tmpnam_r(char *__s) __attribute__  (( __nothrow__ )) ; 
# 186 "/usr/include/stdio.h" 3 4
# 205 "/usr/include/stdio.h" 3 4
extern char *tempnam(__const char *__dir, __const char *__pfx) __attribute__  (( __nothrow__ ))  __attribute__  (( __malloc__ )) ; 
#line 214 "/usr/include/stdio.h"
extern int fclose( FILE *__stream); 
#line 219 "/usr/include/stdio.h"
extern int fflush( FILE *__stream); 
#line 229 "/usr/include/stdio.h"
extern int fflush_unlocked( FILE *__stream); 
# 229 "/usr/include/stdio.h" 3 4
# 250 "/usr/include/stdio.h" 3 4
extern  FILE *fopen(__const char *__restrict __filename, __const char *__restrict __modes); 
#line 257 "/usr/include/stdio.h"
extern  FILE *freopen(__const char *__restrict __filename, __const char *__restrict __modes,  FILE *__restrict __stream); 
# 272 "/usr/include/stdio.h" 3 4
# 283 "/usr/include/stdio.h" 3 4
extern  FILE *fdopen(int __fd, __const char *__modes) __attribute__  (( __nothrow__ )) ; 
#line 297 "/usr/include/stdio.h"
extern  FILE *fmemopen(void *__s,  size_t __len, __const char *__modes) __attribute__  (( __nothrow__ )) ; 
#line 302 "/usr/include/stdio.h"
extern  FILE *open_memstream(char **__bufloc,  size_t *__sizeloc) __attribute__  (( __nothrow__ )) ; 
#line 309 "/usr/include/stdio.h"
extern void setbuf( FILE *__restrict __stream, char *__restrict __buf) __attribute__  (( __nothrow__ )) ; 
#line 314 "/usr/include/stdio.h"
extern int setvbuf( FILE *__restrict __stream, char *__restrict __buf, int __modes,  size_t __n) __attribute__  (( __nothrow__ )) ; 
#line 321 "/usr/include/stdio.h"
extern void setbuffer( FILE *__restrict __stream, char *__restrict __buf,  size_t __size) __attribute__  (( __nothrow__ )) ; 
#line 324 "/usr/include/stdio.h"
extern void setlinebuf( FILE *__stream) __attribute__  (( __nothrow__ )) ; 
#line 334 "/usr/include/stdio.h"
extern int fprintf( FILE *__restrict __stream, __const char *__restrict __format, ...); 
#line 339 "/usr/include/stdio.h"
extern int printf(__const char *__restrict __format, ...); 
#line 342 "/usr/include/stdio.h"
extern int sprintf(char *__restrict __s, __const char *__restrict __format, ...) __attribute__  (( __nothrow__ )) ; 
#line 349 "/usr/include/stdio.h"
extern int vfprintf( FILE *__restrict __s, __const char *__restrict __format,  __gnuc_va_list __arg); 
#line 354 "/usr/include/stdio.h"
extern int vprintf(__const char *__restrict __format,  __gnuc_va_list __arg); 
#line 357 "/usr/include/stdio.h"
extern int vsprintf(char *__restrict __s, __const char *__restrict __format,  __gnuc_va_list __arg) __attribute__  (( __nothrow__ )) ; 
#line 365 "/usr/include/stdio.h"
extern int snprintf(char *__restrict __s,  size_t __maxlen, __const char *__restrict __format, ...) __attribute__  (( __nothrow__ ))  __attribute__  (( __format__ ( __printf__, 3, 4 )  )) ; 
#line 369 "/usr/include/stdio.h"
extern int vsnprintf(char *__restrict __s,  size_t __maxlen, __const char *__restrict __format,  __gnuc_va_list __arg) __attribute__  (( __nothrow__ ))  __attribute__  (( __format__ ( __printf__, 3, 0 )  )) ; 
# 296 "/usr/include/stdio.h" 3 4
# 396 "/usr/include/stdio.h" 3 4
extern int vdprintf(int __fd, __const char *__restrict __fmt,  __gnuc_va_list __arg) __attribute__  (( __format__ ( __printf__, 2, 0 )  )) ; 
#line 398 "/usr/include/stdio.h"
extern int dprintf(int __fd, __const char *__restrict __fmt, ...) __attribute__  (( __format__ ( __printf__, 2, 3 )  )) ; 
#line 408 "/usr/include/stdio.h"
extern int fscanf( FILE *__restrict __stream, __const char *__restrict __format, ...); 
#line 413 "/usr/include/stdio.h"
extern int scanf(__const char *__restrict __format, ...); 
#line 416 "/usr/include/stdio.h"
extern int sscanf(__const char *__restrict __s, __const char *__restrict __format, ...) __attribute__  (( __nothrow__ )) ; 
#line 425 "/usr/include/stdio.h"
extern int fscanf( FILE *__restrict __stream, __const char *__restrict __format, ...) __asm__ ("""__isoc99_fscanf"); 
#line 428 "/usr/include/stdio.h"
extern int scanf(__const char *__restrict __format, ...) __asm__ ("""__isoc99_scanf"); 
#line 430 "/usr/include/stdio.h"
extern int sscanf(__const char *__restrict __s, __const char *__restrict __format, ...) __asm__ ("""__isoc99_sscanf") __attribute__  (( __nothrow__ )) ; 
# 425 "/usr/include/stdio.h" 3 4
# 455 "/usr/include/stdio.h" 3 4
extern int vfscanf( FILE *__restrict __s, __const char *__restrict __format,  __gnuc_va_list __arg) __attribute__  (( __format__ ( __scanf__, 2, 0 )  )) ; 
#line 462 "/usr/include/stdio.h"
extern int vscanf(__const char *__restrict __format,  __gnuc_va_list __arg) __attribute__  (( __format__ ( __scanf__, 1, 0 )  )) ; 
#line 467 "/usr/include/stdio.h"
extern int vsscanf(__const char *__restrict __s, __const char *__restrict __format,  __gnuc_va_list __arg) __attribute__  (( __nothrow__ ))  __attribute__  (( __format__ ( __scanf__, 2, 0 )  )) ; 
#line 480 "/usr/include/stdio.h"
extern int vfscanf( FILE *__restrict __s, __const char *__restrict __format,  __gnuc_va_list __arg) __asm__ ("""__isoc99_vfscanf") __attribute__  (( __format__ ( __scanf__, 2, 0 )  )) ; 
#line 483 "/usr/include/stdio.h"
extern int vscanf(__const char *__restrict __format,  __gnuc_va_list __arg) __asm__ ("""__isoc99_vscanf") __attribute__  (( __format__ ( __scanf__, 1, 0 )  )) ; 
#line 488 "/usr/include/stdio.h"
extern int vsscanf(__const char *__restrict __s, __const char *__restrict __format,  __gnuc_va_list __arg) __asm__ ("""__isoc99_vsscanf") __attribute__  (( __nothrow__ ))  __attribute__  (( __format__ ( __scanf__, 2, 0 )  )) ; 
# 476 "/usr/include/stdio.h" 3 4
# 513 "/usr/include/stdio.h" 3 4
extern int fgetc( FILE *__stream); 
#line 514 "/usr/include/stdio.h"
extern int getc( FILE *__stream); 
#line 520 "/usr/include/stdio.h"
extern int getchar(void ); 
#line 532 "/usr/include/stdio.h"
extern int getc_unlocked( FILE *__stream); 
#line 533 "/usr/include/stdio.h"
extern int getchar_unlocked(void ); 
# 532 "/usr/include/stdio.h" 3 4
# 543 "/usr/include/stdio.h" 3 4
extern int fgetc_unlocked( FILE *__stream); 
#line 555 "/usr/include/stdio.h"
extern int fputc(int __c,  FILE *__stream); 
#line 556 "/usr/include/stdio.h"
extern int putc(int __c,  FILE *__stream); 
#line 562 "/usr/include/stdio.h"
extern int putchar(int __c); 
#line 576 "/usr/include/stdio.h"
extern int fputc_unlocked(int __c,  FILE *__stream); 
#line 584 "/usr/include/stdio.h"
extern int putc_unlocked(int __c,  FILE *__stream); 
#line 585 "/usr/include/stdio.h"
extern int putchar_unlocked(int __c); 
#line 592 "/usr/include/stdio.h"
extern int getw( FILE *__stream); 
#line 595 "/usr/include/stdio.h"
extern int putw(int __w,  FILE *__stream); 
#line 605 "/usr/include/stdio.h"
extern char *fgets(char *__restrict __s, int __n,  FILE *__restrict __stream); 
#line 612 "/usr/include/stdio.h"
extern char *gets(char *__s); 
# 576 "/usr/include/stdio.h" 3 4
# 640 "/usr/include/stdio.h" 3 4
extern  __ssize_t __getdelim(char **__restrict __lineptr,  size_t *__restrict __n, int __delimiter,  FILE *__restrict __stream); 
#line 643 "/usr/include/stdio.h"
extern  __ssize_t getdelim(char **__restrict __lineptr,  size_t *__restrict __n, int __delimiter,  FILE *__restrict __stream); 
#line 653 "/usr/include/stdio.h"
extern  __ssize_t getline(char **__restrict __lineptr,  size_t *__restrict __n,  FILE *__restrict __stream); 
#line 662 "/usr/include/stdio.h"
extern int fputs(__const char *__restrict __s,  FILE *__restrict __stream); 
#line 668 "/usr/include/stdio.h"
extern int puts(__const char *__s); 
#line 675 "/usr/include/stdio.h"
extern int ungetc(int __c,  FILE *__stream); 
#line 683 "/usr/include/stdio.h"
extern  size_t fread(void *__restrict __ptr,  size_t __size,  size_t __n,  FILE *__restrict __stream); 
#line 689 "/usr/include/stdio.h"
extern  size_t fwrite(__const void *__restrict __ptr,  size_t __size,  size_t __n,  FILE *__restrict __s); 
#line 711 "/usr/include/stdio.h"
extern  size_t fread_unlocked(void *__restrict __ptr,  size_t __size,  size_t __n,  FILE *__restrict __stream); 
#line 713 "/usr/include/stdio.h"
extern  size_t fwrite_unlocked(__const void *__restrict __ptr,  size_t __size,  size_t __n,  FILE *__restrict __stream); 
#line 722 "/usr/include/stdio.h"
extern int fseek( FILE *__stream, long int __off, int __whence); 
#line 727 "/usr/include/stdio.h"
extern long int ftell( FILE *__stream); 
#line 732 "/usr/include/stdio.h"
extern void rewind( FILE *__stream); 
# 710 "/usr/include/stdio.h" 3 4
# 746 "/usr/include/stdio.h" 3 4
extern int fseeko( FILE *__stream,  __off_t __off, int __whence); 
#line 751 "/usr/include/stdio.h"
extern  __off_t ftello( FILE *__stream); 
#line 771 "/usr/include/stdio.h"
extern int fgetpos( FILE *__restrict __stream,  fpos_t *__restrict __pos); 
#line 776 "/usr/include/stdio.h"
extern int fsetpos( FILE *__stream, __const  fpos_t *__pos); 
# 765 "/usr/include/stdio.h" 3 4
# 788 "/usr/include/stdio.h" 3 4
# 799 "/usr/include/stdio.h" 3 4
extern void clearerr( FILE *__stream) __attribute__  (( __nothrow__ )) ; 
#line 801 "/usr/include/stdio.h"
extern int feof( FILE *__stream) __attribute__  (( __nothrow__ )) ; 
#line 803 "/usr/include/stdio.h"
extern int ferror( FILE *__stream) __attribute__  (( __nothrow__ )) ; 
#line 808 "/usr/include/stdio.h"
extern void clearerr_unlocked( FILE *__stream) __attribute__  (( __nothrow__ )) ; 
#line 809 "/usr/include/stdio.h"
extern int feof_unlocked( FILE *__stream) __attribute__  (( __nothrow__ )) ; 
#line 810 "/usr/include/stdio.h"
extern int ferror_unlocked( FILE *__stream) __attribute__  (( __nothrow__ )) ; 
#line 819 "/usr/include/stdio.h"
extern void perror(__const char *__s); 
# 1 "/usr/include/bits/sys_errlist.h" 1 3 4
# 27 "/usr/include/bits/sys_errlist.h" 3 4
extern int sys_nerr; 
#line 28 "/usr/include/bits/sys_errlist.h"
extern __const char *__const sys_errlist[]; 
#line 831 "/usr/include/stdio.h"
extern int fileno( FILE *__stream) __attribute__  (( __nothrow__ )) ; 
#line 836 "/usr/include/stdio.h"
extern int fileno_unlocked( FILE *__stream) __attribute__  (( __nothrow__ )) ; 
# 827 "/usr/include/stdio.h" 2 3 4
# 846 "/usr/include/stdio.h" 3 4
extern  FILE *popen(__const char *__command, __const char *__modes); 
#line 852 "/usr/include/stdio.h"
extern int pclose( FILE *__stream); 
#line 858 "/usr/include/stdio.h"
extern char *ctermid(char *__s) __attribute__  (( __nothrow__ )) ; 
#line 886 "/usr/include/stdio.h"
extern void flockfile( FILE *__stream) __attribute__  (( __nothrow__ )) ; 
#line 890 "/usr/include/stdio.h"
extern int ftrylockfile( FILE *__stream) __attribute__  (( __nothrow__ )) ; 
#line 893 "/usr/include/stdio.h"
extern void funlockfile( FILE *__stream) __attribute__  (( __nothrow__ )) ; 
# 886 "/usr/include/stdio.h" 3 4
# 916 "/usr/include/stdio.h" 3 4
# 6 "./OperatingSystem.h" 2
# 34 "./OperatingSystem.h" 
extern int arrivalTimeQueue[20]; 
#line 35 "./OperatingSystem.h"
extern int numberOfProgramsInArrivalTimeQueue; 
#line 36 "./OperatingSystem.h"
extern int executingProcessID; 
#line 37 "./OperatingSystem.h"
extern int numberOfYIELDchange; 
#line 38 "./OperatingSystem.h"
extern int numberOfYIELDnoChange; 
#line 42 "./OperatingSystem.h"
enum ProcessStates {NEW,READY,EXECUTING,BLOCKED,EXIT}; 
#line 45 "./OperatingSystem.h"
enum SystemCallIdentifiers {SYSCALL_PRINTPID=2,SYSCALL_END=3,SYSCALL_YIELD=4,SYSCALL_PRINTEXECPID=5,SYSCALL_SLEEP=7}; 
#line 61 "./OperatingSystem.h"
typedef struct {int busy; int initialPhysicalAddress; int processSize; int state; int priority; int copyOfPCRegister; int copyOfAccumulatorRegister; int copyOfPSWRegister; int queueID; int whenToWakeUp; int partition; 
}PCB; 
#line 69 "./OperatingSystem.h"
typedef struct {int occupied; int initAddress; int size; int PID; int count; 
}PARTITIONDATA; 
#line 71 "./OperatingSystem.h"
extern  PARTITIONDATA partitionsTable[4]; 
#line 72 "./OperatingSystem.h"
extern  PCB processTable[4]; 
#line 74 "./OperatingSystem.h"
void OperatingSystem_Initialize(); 
#line 75 "./OperatingSystem.h"
void OperatingSystem_InicilizateProcessTable(); 
#line 76 "./OperatingSystem.h"
void OperatingSystem_CreateDaemons(); 
#line 77 "./OperatingSystem.h"
void OperatingSystem_PCBInitialization(int , int , int , int , int ); 
#line 78 "./OperatingSystem.h"
void OperatingSystem_MoveToTheREADYState(int ); 
#line 79 "./OperatingSystem.h"
void OperatingSystem_PrintReadyToRunQueue(); 
#line 80 "./OperatingSystem.h"
void OperatingSystem_Dispatch(int ); 
#line 81 "./OperatingSystem.h"
void OperatingSystem_RestoreContext(int ); 
#line 82 "./OperatingSystem.h"
void OperatingSystem_SaveContext(int ); 
#line 83 "./OperatingSystem.h"
void OperatingSystem_HandleException(); 
#line 84 "./OperatingSystem.h"
void OperatingSystem_TerminateProcess(); 
#line 85 "./OperatingSystem.h"
void OperatingSystem_HandleSystemCall(); 
#line 86 "./OperatingSystem.h"
void OperatingSystem_PrintStatus(); 
#line 87 "./OperatingSystem.h"
void OperatingSystem_HandleClockInterrupt(); 
#line 88 "./OperatingSystem.h"
void OperatingSystem_PrintArrivalTimeQueue(); 
#line 89 "./OperatingSystem.h"
void OperatingSystem_ShowPartitionTable(); 
#line 90 "./OperatingSystem.h"
void OperatingSystem_ReleaseMainMemory(); 
#line 91 "./OperatingSystem.h"
void OperatingSystem_End(); 
#line 92 "./OperatingSystem.h"
void OperatingSystem_LongTermSchedulerERROR(int ); 
#line 93 "./OperatingSystem.h"
void OperatingSystem_InitializePartitionTable(); 
#line 94 "./OperatingSystem.h"
int OperatingSystem_LongTermScheduler(); 
#line 95 "./OperatingSystem.h"
void OperatingSystem_PreemptRunningProcess(); 
#line 96 "./OperatingSystem.h"
int OperatingSystem_CreateProcess( USER_PROGRAMS_DATA , int ); 
#line 97 "./OperatingSystem.h"
int OperatingSystem_ObtainAnEntryInTheProcessTable(); 
#line 98 "./OperatingSystem.h"
int OperatingSystem_ObtainMainMemory(int , int ); 
#line 99 "./OperatingSystem.h"
int OperatingSystem_ShortTermScheduler(); 
#line 100 "./OperatingSystem.h"
int OperatingSystem_ExtractFromReadyToRun(int ); 
#line 101 "./OperatingSystem.h"
int OperatingSystem_LoadProgram( FILE *, int ); 
#line 102 "./OperatingSystem.h"
int OperatingSystem_ObtainProgramSize( FILE **, char *); 
#line 103 "./OperatingSystem.h"
int OperatingSystem_ObtainPriority( FILE *); 
#line 104 "./OperatingSystem.h"
int OperatingSystem_lineBeginsWithANumber(char *); 
#line 105 "./OperatingSystem.h"
int OperatingSystem_ExtractFromReadyToRun(int queueID); 
#line 106 "./OperatingSystem.h"
int OperatingSystem_GetNewProgram(); 
# 4 "Processor.c" 2
# 7 "./Buses.h" 1
void Buses_write_AddressBus_From_To(int , int *); 
#line 8 "./Buses.h"
void Buses_write_DataBus_From_To( MEMORYCELL ,  MEMORYCELL *); 
# 5 "Processor.c" 2
# 1 "./MMU.h" 1
# 10 "./MMU.h" 
int MMU_readMemory(); 
#line 11 "./MMU.h"
int MMU_writeMemory(); 
#line 15 "./MMU.h"
extern int registerBase_MMU; 
#line 16 "./MMU.h"
extern int registerLimit_MMU; 
#line 17 "./MMU.h"
extern int registerMAR_MMU; 
# 6 "Processor.c" 2
# 1 "/usr/include/string.h" 1 3 4
# 28 "/usr/include/string.h" 3 4
# 1 "/usr/lib/gcc/x86_64-linux-gnu/4.4.5/include/stddef.h" 1 3 4
# 45 "/usr/include/string.h" 2 3 4
extern void *memcpy(void *__restrict __dest, __const void *__restrict __src,  size_t __n) __attribute__  (( __nothrow__ ))  __attribute__  (( __nonnull__ ( 1, 2 )  )) ; 
#line 49 "/usr/include/string.h"
extern void *memmove(void *__dest, __const void *__src,  size_t __n) __attribute__  (( __nothrow__ ))  __attribute__  (( __nonnull__ ( 1, 2 )  )) ; 
#line 58 "/usr/include/string.h"
extern void *memccpy(void *__restrict __dest, __const void *__restrict __src, int __c,  size_t __n) __attribute__  (( __nothrow__ ))  __attribute__  (( __nonnull__ ( 1, 2 )  )) ; 
#line 64 "/usr/include/string.h"
extern void *memset(void *__s, int __c,  size_t __n) __attribute__  (( __nothrow__ ))  __attribute__  (( __nonnull__ ( 1 )  )) ; 
#line 68 "/usr/include/string.h"
extern int memcmp(__const void *__s1, __const void *__s2,  size_t __n) __attribute__  (( __nothrow__ ))  __attribute__  (( __pure__ ))  __attribute__  (( __nonnull__ ( 1, 2 )  )) ; 
#line 95 "/usr/include/string.h"
extern void *memchr(__const void *__s, int __c,  size_t __n) __attribute__  (( __nothrow__ ))  __attribute__  (( __pure__ ))  __attribute__  (( __nonnull__ ( 1 )  )) ; 
# 94 "/usr/include/string.h" 3 4
# 128 "/usr/include/string.h" 3 4
extern char *strcpy(char *__restrict __dest, __const char *__restrict __src) __attribute__  (( __nothrow__ ))  __attribute__  (( __nonnull__ ( 1, 2 )  )) ; 
#line 132 "/usr/include/string.h"
extern char *strncpy(char *__restrict __dest, __const char *__restrict __src,  size_t __n) __attribute__  (( __nothrow__ ))  __attribute__  (( __nonnull__ ( 1, 2 )  )) ; 
#line 136 "/usr/include/string.h"
extern char *strcat(char *__restrict __dest, __const char *__restrict __src) __attribute__  (( __nothrow__ ))  __attribute__  (( __nonnull__ ( 1, 2 )  )) ; 
#line 139 "/usr/include/string.h"
extern char *strncat(char *__restrict __dest, __const char *__restrict __src,  size_t __n) __attribute__  (( __nothrow__ ))  __attribute__  (( __nonnull__ ( 1, 2 )  )) ; 
#line 143 "/usr/include/string.h"
extern int strcmp(__const char *__s1, __const char *__s2) __attribute__  (( __nothrow__ ))  __attribute__  (( __pure__ ))  __attribute__  (( __nonnull__ ( 1, 2 )  )) ; 
#line 146 "/usr/include/string.h"
extern int strncmp(__const char *__s1, __const char *__s2,  size_t __n) __attribute__  (( __nothrow__ ))  __attribute__  (( __pure__ ))  __attribute__  (( __nonnull__ ( 1, 2 )  )) ; 
#line 150 "/usr/include/string.h"
extern int strcoll(__const char *__s1, __const char *__s2) __attribute__  (( __nothrow__ ))  __attribute__  (( __pure__ ))  __attribute__  (( __nonnull__ ( 1, 2 )  )) ; 
#line 154 "/usr/include/string.h"
extern  size_t strxfrm(char *__restrict __dest, __const char *__restrict __src,  size_t __n) __attribute__  (( __nothrow__ ))  __attribute__  (( __nonnull__ ( 2 )  )) ; 
# 1 "/usr/include/xlocale.h" 1 3 4
# 40 "/usr/include/xlocale.h" 3 4
typedef struct __locale_struct {struct locale_data *__locales[13]; const unsigned short int *__ctype_b; const int *__ctype_tolower; const int *__ctype_toupper; const char *__names[13]; 
}*__locale_t; 
#line 43 "/usr/include/xlocale.h"
typedef  __locale_t locale_t; 
#line 165 "/usr/include/string.h"
extern int strcoll_l(__const char *__s1, __const char *__s2,  __locale_t __l) __attribute__  (( __nothrow__ ))  __attribute__  (( __pure__ ))  __attribute__  (( __nonnull__ ( 1, 2, 3 )  )) ; 
#line 168 "/usr/include/string.h"
extern  size_t strxfrm_l(char *__dest, __const char *__src,  size_t __n,  __locale_t __l) __attribute__  (( __nothrow__ ))  __attribute__  (( __nonnull__ ( 2, 4 )  )) ; 
#line 174 "/usr/include/string.h"
extern char *strdup(__const char *__s) __attribute__  (( __nothrow__ ))  __attribute__  (( __malloc__ ))  __attribute__  (( __nonnull__ ( 1 )  )) ; 
#line 182 "/usr/include/string.h"
extern char *strndup(__const char *__string,  size_t __n) __attribute__  (( __nothrow__ ))  __attribute__  (( __malloc__ ))  __attribute__  (( __nonnull__ ( 1 )  )) ; 
# 162 "/usr/include/string.h" 2 3 4
# 208 "/usr/include/string.h" 3 4
# 234 "/usr/include/string.h" 3 4
extern char *strchr(__const char *__s, int __c) __attribute__  (( __nothrow__ ))  __attribute__  (( __pure__ ))  __attribute__  (( __nonnull__ ( 1 )  )) ; 
#line 261 "/usr/include/string.h"
extern char *strrchr(__const char *__s, int __c) __attribute__  (( __nothrow__ ))  __attribute__  (( __pure__ ))  __attribute__  (( __nonnull__ ( 1 )  )) ; 
# 260 "/usr/include/string.h" 3 4
# 283 "/usr/include/string.h" 3 4
extern  size_t strcspn(__const char *__s, __const char *__reject) __attribute__  (( __nothrow__ ))  __attribute__  (( __pure__ ))  __attribute__  (( __nonnull__ ( 1, 2 )  )) ; 
#line 287 "/usr/include/string.h"
extern  size_t strspn(__const char *__s, __const char *__accept) __attribute__  (( __nothrow__ ))  __attribute__  (( __pure__ ))  __attribute__  (( __nonnull__ ( 1, 2 )  )) ; 
#line 313 "/usr/include/string.h"
extern char *strpbrk(__const char *__s, __const char *__accept) __attribute__  (( __nothrow__ ))  __attribute__  (( __pure__ ))  __attribute__  (( __nonnull__ ( 1, 2 )  )) ; 
# 312 "/usr/include/string.h" 3 4
# 341 "/usr/include/string.h" 3 4
extern char *strstr(__const char *__haystack, __const char *__needle) __attribute__  (( __nothrow__ ))  __attribute__  (( __pure__ ))  __attribute__  (( __nonnull__ ( 1, 2 )  )) ; 
#line 347 "/usr/include/string.h"
extern char *strtok(char *__restrict __s, __const char *__restrict __delim) __attribute__  (( __nothrow__ ))  __attribute__  (( __nonnull__ ( 2 )  )) ; 
#line 355 "/usr/include/string.h"
extern char *__strtok_r(char *__restrict __s, __const char *__restrict __delim, char **__restrict __save_ptr) __attribute__  (( __nothrow__ ))  __attribute__  (( __nonnull__ ( 2, 3 )  )) ; 
#line 359 "/usr/include/string.h"
extern char *strtok_r(char *__restrict __s, __const char *__restrict __delim, char **__restrict __save_ptr) __attribute__  (( __nothrow__ ))  __attribute__  (( __nonnull__ ( 2, 3 )  )) ; 
#line 398 "/usr/include/string.h"
extern  size_t strlen(__const char *__s) __attribute__  (( __nothrow__ ))  __attribute__  (( __pure__ ))  __attribute__  (( __nonnull__ ( 1 )  )) ; 
#line 405 "/usr/include/string.h"
extern  size_t strnlen(__const char *__string,  size_t __maxlen) __attribute__  (( __nothrow__ ))  __attribute__  (( __pure__ ))  __attribute__  (( __nonnull__ ( 1 )  )) ; 
#line 411 "/usr/include/string.h"
extern char *strerror(int __errnum) __attribute__  (( __nothrow__ )) ; 
# 395 "/usr/include/string.h" 3 4
# 425 "/usr/include/string.h" 3 4
extern int strerror_r(int __errnum, char *__buf,  size_t __buflen) __asm__ ("""__xpg_strerror_r") __attribute__  (( __nothrow__ ))  __attribute__  (( __nonnull__ ( 2 )  )) ; 
#line 443 "/usr/include/string.h"
extern char *strerror_l(int __errnum,  __locale_t __l) __attribute__  (( __nothrow__ )) ; 
#line 449 "/usr/include/string.h"
extern void __bzero(void *__s,  size_t __n) __attribute__  (( __nothrow__ ))  __attribute__  (( __nonnull__ ( 1 )  )) ; 
#line 454 "/usr/include/string.h"
extern void bcopy(__const void *__src, void *__dest,  size_t __n) __attribute__  (( __nothrow__ ))  __attribute__  (( __nonnull__ ( 1, 2 )  )) ; 
#line 457 "/usr/include/string.h"
extern void bzero(void *__s,  size_t __n) __attribute__  (( __nothrow__ ))  __attribute__  (( __nonnull__ ( 1 )  )) ; 
#line 461 "/usr/include/string.h"
extern int bcmp(__const void *__s1, __const void *__s2,  size_t __n) __attribute__  (( __nothrow__ ))  __attribute__  (( __pure__ ))  __attribute__  (( __nonnull__ ( 1, 2 )  )) ; 
# 443 "/usr/include/string.h" 3 4
# 488 "/usr/include/string.h" 3 4
extern char *index(__const char *__s, int __c) __attribute__  (( __nothrow__ ))  __attribute__  (( __pure__ ))  __attribute__  (( __nonnull__ ( 1 )  )) ; 
#line 516 "/usr/include/string.h"
extern char *rindex(__const char *__s, int __c) __attribute__  (( __nothrow__ ))  __attribute__  (( __pure__ ))  __attribute__  (( __nonnull__ ( 1 )  )) ; 
#line 521 "/usr/include/string.h"
extern int ffs(int __i) __attribute__  (( __nothrow__ ))  __attribute__  (( __const__ )) ; 
# 515 "/usr/include/string.h" 3 4
# 535 "/usr/include/string.h" 3 4
extern int strcasecmp(__const char *__s1, __const char *__s2) __attribute__  (( __nothrow__ ))  __attribute__  (( __pure__ ))  __attribute__  (( __nonnull__ ( 1, 2 )  )) ; 
#line 539 "/usr/include/string.h"
extern int strncasecmp(__const char *__s1, __const char *__s2,  size_t __n) __attribute__  (( __nothrow__ ))  __attribute__  (( __pure__ ))  __attribute__  (( __nonnull__ ( 1, 2 )  )) ; 
#line 559 "/usr/include/string.h"
extern char *strsep(char **__restrict __stringp, __const char *__restrict __delim) __attribute__  (( __nothrow__ ))  __attribute__  (( __nonnull__ ( 1, 2 )  )) ; 
#line 564 "/usr/include/string.h"
extern char *strsignal(int __sig) __attribute__  (( __nothrow__ )) ; 
#line 568 "/usr/include/string.h"
extern char *__stpcpy(char *__restrict __dest, __const char *__restrict __src) __attribute__  (( __nothrow__ ))  __attribute__  (( __nonnull__ ( 1, 2 )  )) ; 
#line 570 "/usr/include/string.h"
extern char *stpcpy(char *__restrict __dest, __const char *__restrict __src) __attribute__  (( __nothrow__ ))  __attribute__  (( __nonnull__ ( 1, 2 )  )) ; 
#line 576 "/usr/include/string.h"
extern char *__stpncpy(char *__restrict __dest, __const char *__restrict __src,  size_t __n) __attribute__  (( __nothrow__ ))  __attribute__  (( __nonnull__ ( 1, 2 )  )) ; 
#line 579 "/usr/include/string.h"
extern char *stpncpy(char *__restrict __dest, __const char *__restrict __src,  size_t __n) __attribute__  (( __nothrow__ ))  __attribute__  (( __nonnull__ ( 1, 2 )  )) ; 
# 557 "/usr/include/string.h" 3 4
# 644 "/usr/include/string.h" 3 4
# 10 "Processor.c" 2
int registerPC_CPU; 
#line 11 "Processor.c"
int registerAccumulator_CPU; 
#line 12 "Processor.c"
 MEMORYCELL registerIR_CPU; 
#line 13 "Processor.c"
int registerPSW_CPU; 
#line 14 "Processor.c"
int registerMAR_CPU; 
#line 15 "Processor.c"
int registerB_CPU; 
#line 16 "Processor.c"
 MEMORYCELL registerMBR_CPU; 
#line 17 "Processor.c"
int registerA_CPU; 
#line 20 "Processor.c"
void (*interruptVectorTable[10])(); 
#line 24 "Processor.c"
void Processor_InitializeInterruptVectorTable()  
# 812 "ProcessorAspect.c"
{



# 817 "ProcessorAspect.c"
{

#line 25 "Processor.c"
interruptVectorTable[EXCEPTION_BIT] = OperatingSystem_HandleException; 
#line 26 "Processor.c"
interruptVectorTable[SYSCALL_BIT] = OperatingSystem_HandleSystemCall; 
#line 27 "Processor.c"
interruptVectorTable[CLOCKINT_BIT] = OperatingSystem_HandleClockInterrupt; 
# 826 "ProcessorAspect.c"

}

# 830 "ProcessorAspect.c"

}
 
#line 34 "Processor.c"
void Processor_InstructionCycleLoop()  
# 836 "ProcessorAspect.c"
{



# 841 "ProcessorAspect.c"
{

#line 42 "Processor.c"
while((!Processor_BitState(POWEROFF_BIT))) { { 
#line 37 "Processor.c"
Processor_FetchInstruction(); 
#line 38 "Processor.c"
if (Processor_BitState(EXCEPTION_BIT) != 1){
Processor_DecodeAndExecuteInstruction(); }
#line 40 "Processor.c"
Processor_ManageInterrupts(); } } 
# 853 "ProcessorAspect.c"

}

# 857 "ProcessorAspect.c"

}
 
  void __utac_acc__Aspect__1 (void);


#line 46 "Processor.c"
void Processor_FetchInstruction()  
# 866 "ProcessorAspect.c"
{



# 871 "ProcessorAspect.c"
{

#line 48 "Processor.c"
registerMAR_CPU = registerPC_CPU; 
#line 50 "Processor.c"
Buses_write_AddressBus_From_To(registerMAR_CPU, (&registerMAR_MMU)); 
#line 52 "Processor.c"
MMU_readMemory(); 
#line 58 "Processor.c"
memcpy(((void *)((&registerIR_CPU))), ((void *)((&registerMBR_CPU))), sizeof ( MEMORYCELL )); 
#line 59 "Processor.c"
ComputerSystem_DebugMessage('h', "CkMcsYdsYd", registerIR_CPU.operationCode, " ", registerIR_CPU.operand1, " ", registerIR_CPU.operand2); 
# 884 "ProcessorAspect.c"

}

{
__utac_acc__Aspect__1();

}

# 893 "ProcessorAspect.c"

}
 
#line 64 "Processor.c"
void Processor_DecodeAndExecuteInstruction()  
# 899 "ProcessorAspect.c"
{



# 904 "ProcessorAspect.c"
{

#line 156 "Processor.c"
switch(registerIR_CPU.operationCode){ { 
#line 69 "Processor.c"
case 'a': registerAccumulator_CPU = registerIR_CPU.operand1 + registerIR_CPU.operand2; 
#line 70 "Processor.c"
registerPC_CPU++; 
#line 71 "Processor.c"
break; 
#line 74 "Processor.c"
case 's': registerAccumulator_CPU = registerIR_CPU.operand1 - registerIR_CPU.operand2; 
#line 75 "Processor.c"
registerPC_CPU++; 
#line 76 "Processor.c"
break; 
#line 79 "Processor.c"
case 'd': if (registerIR_CPU.operand2 == 0){
Processor_RaiseException(DIVISIONBYZERO); }else{
{ 
#line 83 "Processor.c"
registerAccumulator_CPU = registerIR_CPU.operand1 / registerIR_CPU.operand2; 
#line 84 "Processor.c"
registerPC_CPU++; } }
#line 86 "Processor.c"
break; 
#line 89 "Processor.c"
case 't': Processor_ActivateBit(SYSCALL_BIT); 
#line 90 "Processor.c"
registerA_CPU = registerIR_CPU.operand1; 
#line 91 "Processor.c"
registerPC_CPU++; 
#line 92 "Processor.c"
break; 
#line 95 "Processor.c"
case 'n': registerPC_CPU++; 
#line 96 "Processor.c"
break; 
#line 99 "Processor.c"
case 'j': registerPC_CPU += registerIR_CPU.operand1; 
#line 100 "Processor.c"
break; 
#line 103 "Processor.c"
case 'z': if (registerAccumulator_CPU == 0){
registerPC_CPU += registerIR_CPU.operand1; }else{
registerPC_CPU++; }
#line 108 "Processor.c"
break; 
#line 111 "Processor.c"
case 'w': registerMBR_CPU.operationCode = registerMBR_CPU.operand1 = registerMBR_CPU.operand2 = registerAccumulator_CPU; 
#line 112 "Processor.c"
registerMAR_CPU = registerIR_CPU.operand1; 
#line 114 "Processor.c"
Buses_write_DataBus_From_To(registerMBR_CPU, (&registerMBR_MainMemory)); 
#line 116 "Processor.c"
Buses_write_AddressBus_From_To(registerMAR_CPU, (&registerMAR_MMU)); 
#line 118 "Processor.c"
MMU_writeMemory(); 
#line 119 "Processor.c"
registerPC_CPU++; 
#line 120 "Processor.c"
break; 
#line 123 "Processor.c"
case 'r': registerMAR_CPU = registerIR_CPU.operand1; 
#line 125 "Processor.c"
Buses_write_AddressBus_From_To(registerMAR_CPU, (&registerMAR_MMU)); 
#line 127 "Processor.c"
MMU_readMemory(); 
#line 129 "Processor.c"
registerAccumulator_CPU = registerMBR_CPU.operand1; 
#line 130 "Processor.c"
registerPC_CPU++; 
#line 131 "Processor.c"
break; 
#line 134 "Processor.c"
case 'm': registerMAR_CPU = registerIR_CPU.operand2; 
#line 135 "Processor.c"
Buses_write_AddressBus_From_To(registerMAR_CPU, (&registerMAR_MMU)); 
#line 136 "Processor.c"
MMU_readMemory(); 
#line 137 "Processor.c"
registerAccumulator_CPU = registerMBR_CPU.operand1; 
#line 138 "Processor.c"
registerAccumulator_CPU = registerAccumulator_CPU + registerIR_CPU.operand1; 
#line 139 "Processor.c"
registerPC_CPU++; 
#line 140 "Processor.c"
break; 
#line 143 "Processor.c"
case 'i': registerAccumulator_CPU += registerIR_CPU.operand1; 
#line 144 "Processor.c"
registerPC_CPU++; 
#line 145 "Processor.c"
break; 
#line 148 "Processor.c"
case 'h': Processor_ActivateBit(POWEROFF_BIT); 
#line 149 "Processor.c"
break; 
#line 152 "Processor.c"
default: Processor_RaiseException(INVALIDINSTRUCTION); 
#line 155 "Processor.c"
break; } } 
#line 157 "Processor.c"
ComputerSystem_DebugMessage('h', "GsGdWsYdWsYdWsYdWs", " (PID: ", executingProcessID, ", PC: ", registerPC_CPU, ",Accumulator: ", registerAccumulator_CPU, " PSW: ", registerPSW_CPU, ")\n"); 
# 1009 "ProcessorAspect.c"

}

# 1013 "ProcessorAspect.c"

}
 
#line 162 "Processor.c"
void Processor_ManageInterrupts()  
# 1019 "ProcessorAspect.c"
{



# 1024 "ProcessorAspect.c"
{

#line 164 "Processor.c"

#line 164 "Processor.c"
int i;
#line 167 "Processor.c"
Processor_CopyInSystemStack(256 - 1, registerPC_CPU); 
#line 168 "Processor.c"
Processor_CopyInSystemStack(256 - 2, registerPSW_CPU); 
#line 171 "Processor.c"
for(i = 1;i < 10;i++) { if (Processor_BitState(i)){
{ 
#line 175 "Processor.c"
Processor_DeactivateBit(i); 
#line 177 "Processor.c"
interruptVectorTable[i](); } }} 
# 1042 "ProcessorAspect.c"

}

# 1046 "ProcessorAspect.c"

}
 
#line 183 "Processor.c"
void Processor_CopyInSystemStack(int physicalMemoryAddress, int data)  
# 1052 "ProcessorAspect.c"
{



# 1057 "ProcessorAspect.c"
{

#line 185 "Processor.c"
registerMBR_CPU.operationCode = registerMBR_CPU.operand1 = registerMBR_CPU.operand2 = data; 
#line 186 "Processor.c"
registerMAR_CPU = physicalMemoryAddress; 
#line 187 "Processor.c"
Buses_write_AddressBus_From_To(registerMAR_CPU, (&registerMAR_MainMemory)); 
#line 188 "Processor.c"
Buses_write_DataBus_From_To(registerMBR_CPU, (&registerMBR_MainMemory)); 
#line 189 "Processor.c"
MainMemory_writeMemory(); 
# 1070 "ProcessorAspect.c"

}

# 1074 "ProcessorAspect.c"

}
 
#line 194 "Processor.c"
void Processor_ActivateBit(const unsigned int nbit)  
# 1080 "ProcessorAspect.c"
{



# 1085 "ProcessorAspect.c"
{

#line 195 "Processor.c"

#line 195 "Processor.c"
unsigned int mask = 1;
#line 197 "Processor.c"
mask = mask << nbit; 
#line 198 "Processor.c"
registerPSW_CPU = registerPSW_CPU | mask; 
# 1096 "ProcessorAspect.c"

}

# 1100 "ProcessorAspect.c"

}
 
#line 202 "Processor.c"
void Processor_DeactivateBit(const unsigned int nbit)  
# 1106 "ProcessorAspect.c"
{



# 1111 "ProcessorAspect.c"
{

#line 203 "Processor.c"

#line 203 "Processor.c"
unsigned int mask = 1;
#line 205 "Processor.c"
mask = mask << nbit; 
#line 206 "Processor.c"
mask = (~mask); 
#line 208 "Processor.c"
registerPSW_CPU = registerPSW_CPU & mask; 
# 1124 "ProcessorAspect.c"

}

# 1128 "ProcessorAspect.c"

}
 
#line 212 "Processor.c"
unsigned int Processor_BitState(const unsigned int nbit)  
# 1134 "ProcessorAspect.c"
{
# 1136 "ProcessorAspect.c"
unsigned int retValue_acc;




# 1142 "ProcessorAspect.c"
{

#line 213 "Processor.c"

#line 213 "Processor.c"
unsigned int mask = 1;
#line 215 "Processor.c"
mask = mask << nbit; 
#line 216 "Processor.c"

# 1153 "ProcessorAspect.c"
retValue_acc = (registerPSW_CPU & mask) >> nbit;
# 1155 "ProcessorAspect.c"
return (unsigned int )retValue_acc;
 
# 1158 "ProcessorAspect.c"

}

# 1162 "ProcessorAspect.c"
return (unsigned int )retValue_acc;

# 1165 "ProcessorAspect.c"

}
 
#line 220 "Processor.c"
void Processor_RaiseException(int typeOfException)  
# 1171 "ProcessorAspect.c"
{



# 1176 "ProcessorAspect.c"
{

#line 221 "Processor.c"
Processor_ActivateBit(EXCEPTION_BIT); 
#line 222 "Processor.c"
registerB_CPU = typeOfException; 
# 1183 "ProcessorAspect.c"

}

# 1187 "ProcessorAspect.c"

}
 
