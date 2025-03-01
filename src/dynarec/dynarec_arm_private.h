#ifndef __DYNAREC_ARM_PRIVATE_H_
#define __DYNAREC_ARM_PRIVATE_H_

#include "dynarec_private.h"

typedef struct x86emu_s x86emu_t;
typedef struct dynablock_s dynablock_t;

#define BARRIER_MAYBE   8

#define NEON_CACHE_NONE 0
#define NEON_CACHE_ST_D 1
#define NEON_CACHE_ST_F 2
#define NEON_CACHE_MM   3
#define NEON_CACHE_XMMW 4
#define NEON_CACHE_XMMR 5
#define NEON_CACHE_SCR  6
typedef union neon_cache_s {
    int8_t           v;
    struct {
        uint8_t t:4;   // reg type
        uint8_t n:4;   // reg number
    };
} neon_cache_t;
typedef union sse_cache_s {
    int8_t     v;
    struct {
        uint8_t reg;
        uint8_t write;
    };
} sse_cache_t;
typedef struct neoncache_s {
    // Neon cache
    neon_cache_t        neoncache[24];
    int8_t              stack;
    int8_t              stack_next;
    int8_t              stack_pop;
    int8_t              stack_push;
    uint8_t             combined1;
    uint8_t             combined2;
    uint8_t             swapped;    // the combined reg were swapped
    uint8_t             barrier;    // is there a barrier at instruction epilog?
    uint32_t            news;       // bitmask, wich neoncache are new for this opcode
    // fpu cache
    int8_t              x87cache[8];// cache status for the 8 x87 register behind the fpu stack
    int8_t              x87reg[8];  // reg used for x87cache entry
    int8_t              mmxcache[8];// cache status for the 8 MMX registers
    sse_cache_t         ssecache[8];// cache status for the 8 SSE(2) registers
    int8_t              fpuused[24];// all 8..31 double reg from fpu, used by x87, sse and mmx
    int8_t              x87stack;   // cache stack counter
    int8_t              mmxcount;   // number of mmx register used (not both mmx and x87 at the same time)
    int8_t              fpu_scratch;// scratch counter
    int8_t              fpu_extra_qscratch; // some opcode need an extra quad scratch register
    int8_t              fpu_reg;    // x87/sse/mmx reg counter
} neoncache_t;

typedef struct flagcache_s {
    int                 pending;    // is there a pending flags here, or to check?
    int                 dfnone;     // if defered flags is already set to df_none
} flagcache_t;

typedef struct instruction_arm_s {
    instruction_x86_t   x86;
    uintptr_t           address;    // (start) address of the arm emited instruction
    uintptr_t           epilog;     // epilog of current instruction (can be start of next, of barrier stuff)
    int                 size;       // size of the arm emited instruction
    int                 size2;      // size of the arm emited instrucion after pass2
    int                 pred_sz;    // size of predecessor list
    int                 *pred;      // predecessor array
    uintptr_t           mark, mark2, mark3;
    uintptr_t           markf;
    uintptr_t           markseg;
    uintptr_t           marklock;
    int                 pass2choice;// value for choices that are fixed on pass2 for pass3
    uintptr_t           natcall;
    int                 retn;
    int                 barrier_maybe;
    flagcache_t         f_exit;     // flags status at end of intruction
    neoncache_t         n;          // neoncache at end of intruction (but before poping)
    flagcache_t         f_entry;    // flags status before the instruction begin
} instruction_arm_t;


typedef struct dynarec_arm_s {
    instruction_arm_t   *insts;
    int32_t             size;
    int32_t             cap;
    uintptr_t           start;      // start of the block
    uint32_t            isize;      // size in byte of x86 instructions included
    void*               block;      // memory pointer where next instruction is emited
    uintptr_t           arm_start;  // start of the arm code
    int                 arm_size;   // size of emitted arm code
    flagcache_t         f;
    neoncache_t         n;          // cache for the 8..31 double reg from fpu, plus x87 stack delta
    uintptr_t*          next;       // variable array of "next" jump address
    int                 next_sz;
    int                 next_cap;
    uintptr_t*          sons_x86;   // the x86 address of potential dynablock sons
    void**              sons_arm;   // the arm address of potential dynablock sons
    int                 sons_size;  // number of potential dynablock sons
    int*                predecessor;// single array of all predecessor
    dynablock_t*        dynablock;
    uint8_t             smread;    // for strongmem model emulation
    uint8_t             smwrite;    // for strongmem model emulation
} dynarec_arm_t;

void add_next(dynarec_arm_t *dyn, uintptr_t addr);
uintptr_t get_closest_next(dynarec_arm_t *dyn, uintptr_t addr);
int is_nops(dynarec_arm_t *dyn, uintptr_t addr, int n);
int is_instructions(dynarec_arm_t *dyn, uintptr_t addr, int n);

#endif //__DYNAREC_ARM_PRIVATE_H_