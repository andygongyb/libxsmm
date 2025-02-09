/******************************************************************************
* Copyright (c) Intel Corporation - All rights reserved.                      *
* This file is part of the LIBXSMM library.                                   *
*                                                                             *
* For information on the license, see the LICENSE file.                       *
* Further information: https://github.com/hfp/libxsmm/                        *
* SPDX-License-Identifier: BSD-3-Clause                                       *
******************************************************************************/
/* Hans Pabst (Intel Corp.)
******************************************************************************/
#ifndef LIBXSMM_TYPEDEFS_H
#define LIBXSMM_TYPEDEFS_H

#include "libxsmm_macros.h"

/** Check ILP64 configuration for sanity. */
#if !defined(LIBXSMM_ILP64) || (0 == LIBXSMM_ILP64 && defined(MKL_ILP64))
# error "Inconsistent ILP64 configuration detected!"
#elif (0 != LIBXSMM_ILP64 && !defined(MKL_ILP64))
# define MKL_ILP64
#endif
#if (0 != LIBXSMM_ILP64)
# define LIBXSMM_BLASINT_NBITS 64
# define LIBXSMM_BLASINT long long
#else /* LP64 */
# define LIBXSMM_BLASINT_NBITS 32
# define LIBXSMM_BLASINT int
#endif

/** Generic prefetches; similar to LIBXSMM_PREFETCH_AUTO (libxsmm_frontend.h) */
#define LIBXSMM_PREFETCH_SIGONLY 1
#define LIBXSMM_PREFETCH_NONE 0

/** Helper macro for type names. */
#define LIBXSMM_TYPENAME(TYPE) LIBXSMM_STRINGIFY(LIBXSMM_CONCATENATE(LIBXSMM_TYPENAME_, TYPE))
#define LIBXSMM_TYPENAME_double f64
#define LIBXSMM_TYPENAME_float f32
#define LIBXSMM_TYPENAME_libxsmm_bfloat16 bf16
#define LIBXSMM_TYPENAME_libxsmm_float16 f16
#define LIBXSMM_TYPENAME_int i32
#define LIBXSMM_TYPENAME_short i16
#define LIBXSMM_TYPENAME_char i8

/** Helper macro for type information: INFO := { FP }. */
#define LIBXSMM_TYPEINFO(TYPE, INFO) LIBXSMM_CONCATENATE4(LIBXSMM_TYPEINFO_, INFO, _, TYPE)
#define LIBXSMM_TYPEINFO_FP_double 1
#define LIBXSMM_TYPEINFO_FP_float 1
#define LIBXSMM_TYPEINFO_FP_libxsmm_bfloat16 1
#define LIBXSMM_TYPEINFO_FP_libxsmm_float16 1
#define LIBXSMM_TYPEINFO_FP_int 0
#define LIBXSMM_TYPEINFO_FP_short 0
#define LIBXSMM_TYPEINFO_FP_char 0

/** Helper macro for type postfixes. */
#define LIBXSMM_TYPESYMBOL(TYPE) LIBXSMM_CONCATENATE(LIBXSMM_TYPESYMBOL_, TYPE)
#define LIBXSMM_TYPESYMBOL_double F64
#define LIBXSMM_TYPESYMBOL_float F32
#define LIBXSMM_TYPESYMBOL_libxsmm_bfloat16 BF16
#define LIBXSMM_TYPESYMBOL_libxsmm_float16 F16
#define LIBXSMM_TYPESYMBOL_int I32
#define LIBXSMM_TYPESYMBOL_short I16
#define LIBXSMM_TYPESYMBOL_char I8

#define LIBXSMM_TYPESIZE(ENUM) ( \
  ((int)(ENUM)) == LIBXSMM_DATATYPE_F64  ? 8 : ( \
  ((int)(ENUM)) == LIBXSMM_DATATYPE_F32  ? 4 : ( \
  ((int)(ENUM)) == LIBXSMM_DATATYPE_BF16 ? 2 : ( \
  ((int)(ENUM)) == LIBXSMM_DATATYPE_F16  ? 2 : ( \
  ((int)(ENUM)) == LIBXSMM_DATATYPE_I64  ? 8 : ( \
  ((int)(ENUM)) == LIBXSMM_DATATYPE_I32  ? 4 : ( \
  ((int)(ENUM)) == LIBXSMM_DATATYPE_I16  ? 2 : ( \
  ((int)(ENUM)) == LIBXSMM_DATATYPE_I8   ? 1 : ( \
  0/*invalid*/)))))))))

/* Get input or output precision */
#define LIBXSMM_GETENUM_INP(SRC) ((SRC) & 0x0F)
#define LIBXSMM_GETENUM_OUT(SRC) (0 == ((SRC) >> 4) ? LIBXSMM_GETENUM_INP(SRC) : ((SRC) >> 4))
/* Get/Set input and output precision */
#define LIBXSMM_GETENUM(INP, OUT) (((INP) == (OUT)) ? (INP) : ((INP) | ((OUT) << 4)))
#define LIBXSMM_SETENUM(DST, INP, OUT) DST = LIBXSMM_GETENUM(INP, OUT)

/* Construct an enumerator (libxsmm_datatype) from a built-in type (float, double, etc.). */
#define LIBXSMM_DATATYPE(TYPE) LIBXSMM_CONCATENATE(LIBXSMM_DATATYPE_, LIBXSMM_TYPESYMBOL(TYPE))
/* Construct a type-id from built-in input/output types (float, double, etc.). */
#define LIBXSMM_DATATYPE2(ITYPE, OTYPE) LIBXSMM_GETENUM(LIBXSMM_DATATYPE(ITYPE), LIBXSMM_DATATYPE(OTYPE))

/* Construct an enumerator (libxsmm_gemm_precision) from a built-in type (float, double, etc.). */
#define LIBXSMM_GEMM_PRECISION(TYPE) LIBXSMM_CONCATENATE(LIBXSMM_GEMM_PRECISION_, LIBXSMM_TYPESYMBOL(TYPE))
/* Construct GEMM-precision from built-in input/output types (float, double, etc.). */
#define LIBXSMM_GEMM_PRECISION2(ITYPE, OTYPE) (libxsmm_gemm_precision)LIBXSMM_GETENUM( \
  LIBXSMM_GEMM_PRECISION(ITYPE), LIBXSMM_GEMM_PRECISION(OTYPE))

/** Maximum size available to store a descriptor/blob (GEMM, MCOPY, TRANS, TRSM, TRMM). */
#if !defined(LIBXSMM_DESCRIPTOR_MAXSIZE)
# define LIBXSMM_DESCRIPTOR_MAXSIZE 96
#endif
/** Size of the descriptor considered as unique/small signature. */
#if !defined(LIBXSMM_DESCRIPTOR_SIGSIZE)
# if defined(LIBXSMM_UNPACKED)
#   define LIBXSMM_DESCRIPTOR_SIGSIZE 64
# else
#   define LIBXSMM_DESCRIPTOR_SIGSIZE 32
# endif
#endif


/* Support for Bfloat16 */
typedef unsigned short libxsmm_bfloat16;
typedef unsigned short libxsmm_float16;

LIBXSMM_EXTERN_C typedef union LIBXSMM_RETARGETABLE libxsmm_bfloat16_hp {
  libxsmm_bfloat16 i[2];
  float f;
} libxsmm_bfloat16_hp;

#if defined(__cplusplus)
namespace Eigen { struct bfloat16; }
#endif /*__cplusplus*/

/** Integer type for LAPACK/BLAS (LP64: 32-bit, and ILP64: 64-bit). */
typedef LIBXSMM_BLASINT libxsmm_blasint;

/** Type representing sufficient storage space for a GEMM handle. */
LIBXSMM_EXTERN_C typedef struct LIBXSMM_RETARGETABLE libxsmm_gemm_blob { char data[128]; } libxsmm_gemm_blob;
LIBXSMM_EXTERN_C typedef struct LIBXSMM_RETARGETABLE libxsmm_gemm_handle libxsmm_gemm_handle;

/** Type representing sufficient storage space for descriptors (GEMM, TCOPY, MCOPY). */
LIBXSMM_EXTERN_C typedef struct LIBXSMM_RETARGETABLE libxsmm_descriptor_blob {
  char data[LIBXSMM_DESCRIPTOR_MAXSIZE];
} libxsmm_descriptor_blob;

/** Structure storing arguments of GEMM-like routines. */
LIBXSMM_EXTERN_C typedef struct LIBXSMM_RETARGETABLE libxsmm_gemm_descriptor libxsmm_gemm_descriptor;
/** Structure storing arguments of the matrix-eltw routine. */
LIBXSMM_EXTERN_C typedef struct LIBXSMM_RETARGETABLE libxsmm_meltw_descriptor libxsmm_meltw_descriptor;
/** Structure storing arguments of the matrix-equation routine. */
LIBXSMM_EXTERN_C typedef struct LIBXSMM_RETARGETABLE libxsmm_meqn_descriptor libxsmm_meqn_descriptor;

/** Enumerates element/data types. */
typedef enum libxsmm_datatype {
  LIBXSMM_DATATYPE_F64,
  LIBXSMM_DATATYPE_F32,
  LIBXSMM_DATATYPE_BF16,
  LIBXSMM_DATATYPE_F16,
  LIBXSMM_DATATYPE_I64,
  LIBXSMM_DATATYPE_I32,
  LIBXSMM_DATATYPE_I16,
  LIBXSMM_DATATYPE_I8,
  LIBXSMM_DATATYPE_UNSUPPORTED
} libxsmm_datatype;

/** Denotes the precision/data type of GEMM. */
typedef enum libxsmm_gemm_precision {
  LIBXSMM_GEMM_PRECISION_F64  = LIBXSMM_DATATYPE_F64,
  LIBXSMM_GEMM_PRECISION_F32  = LIBXSMM_DATATYPE_F32,
  LIBXSMM_GEMM_PRECISION_BF16 = LIBXSMM_DATATYPE_BF16,
  LIBXSMM_GEMM_PRECISION_F16  = LIBXSMM_DATATYPE_F16,
  LIBXSMM_GEMM_PRECISION_I32  = LIBXSMM_DATATYPE_I32,
  LIBXSMM_GEMM_PRECISION_I16  = LIBXSMM_DATATYPE_I16,
  LIBXSMM_GEMM_PRECISION_I8   = LIBXSMM_DATATYPE_I8
} libxsmm_gemm_precision;

typedef enum libxsmm_meltw_operation {
  LIBXSMM_MELTW_OPERATION_NONE                                             =  0,
  /* for fusion into AMX GEMM */
  LIBXSMM_MELTW_OPERATION_CVTFP32BF16                                      =  1,
  LIBXSMM_MELTW_OPERATION_CVTFP32BF16_ACT                                  =  2,
  LIBXSMM_MELTW_OPERATION_ACT_CVTFP32BF16                                  =  3,
  LIBXSMM_MELTW_OPERATION_COLBIAS_ACT                                      =  4,
  LIBXSMM_MELTW_OPERATION_DECOMPRESS_A                                     =  5,
  LIBXSMM_MELTW_OPERATION_COLBIAS_ACT_DECOMPRESS_A                         =  6,
  LIBXSMM_MELTW_OPERATION_TRANSFORM_B_NORM_TO_NORMT_EXT_BUFFER             =  7,
  LIBXSMM_MELTW_OPERATION_COLBIAS_ACT_TRANSFORM_B_NORM_TO_NORMT_EXT_BUFFER =  8,
  LIBXSMM_MELTW_OPERATION_TRANSFORM_C_NORM_TO_VNNI_EXT_BUFFER              =  9,
  LIBXSMM_MELTW_OPERATION_ACT_TRANSFORM_C_NORM_TO_VNNI_EXT_BUFFER          = 10,
  /* standalone TPPs */
  LIBXSMM_MELTW_OPERATION_OPREDUCE_VECS_IDX                                = 11,
  LIBXSMM_MELTW_OPERATION_UNARY                                            = 12,
  LIBXSMM_MELTW_OPERATION_BINARY                                           = 13,
  LIBXSMM_MELTW_OPERATION_TERNARY                                          = 14
} libxsmm_meltw_operation;

typedef enum libxsmm_meltw_null_flags {
  LIBXSMM_MELTW_FLAG_NONE                = 0
} libxsmm_meltw_null_flags;

typedef enum libxsmm_meltw_relu_flags {
  LIBXSMM_MELTW_FLAG_RELU_NONE    = 0,
  LIBXSMM_MELTW_FLAG_RELU_FWD     = 1,
  LIBXSMM_MELTW_FLAG_RELU_BWD     = 2,
  LIBXSMM_MELTW_FLAG_RELU_BITMASK = 4,
  LIBXSMM_MELTW_FLAG_RELU_FWD_BITMASK = LIBXSMM_MELTW_FLAG_RELU_FWD | LIBXSMM_MELTW_FLAG_RELU_BITMASK,
  LIBXSMM_MELTW_FLAG_RELU_BWD_BITMASK = LIBXSMM_MELTW_FLAG_RELU_BWD | LIBXSMM_MELTW_FLAG_RELU_BITMASK
} libxsmm_meltw_relu_flags;

typedef enum libxsmm_meltw_cvt_flags {
  LIBXSMM_MELTW_FLAG_CVT_NONE           = 0,
  LIBXSMM_MELTW_FLAG_CVT_VNNI_FORMAT    = 1
} libxsmm_meltw_cvt_flags;

typedef enum libxsmm_meltw_cvta_flags {
  LIBXSMM_MELTW_FLAG_CVTA_NONE           = 0,
  LIBXSMM_MELTW_FLAG_CVTA_FUSE_RELU      = 1,
  LIBXSMM_MELTW_FLAG_CVTA_FUSE_TANH      = 2,
  LIBXSMM_MELTW_FLAG_CVTA_FUSE_SIGM      = 4
} libxsmm_meltw_cvta_flags;

typedef enum libxsmm_meltw_acvt_flags {
  LIBXSMM_MELTW_FLAG_ACVT_NONE           = 0,
  LIBXSMM_MELTW_FLAG_ACVT_FUSE_TANH      = 1,
  LIBXSMM_MELTW_FLAG_ACVT_FUSE_SIGM      = 2
} libxsmm_meltw_acvt_flags;

typedef enum libxsmm_meltw_flags {
  LIBXSMM_MELTW_FLAG_FUSE_NONE          =  0,
  LIBXSMM_MELTW_FLAG_COLBIAS            =  1,
  LIBXSMM_MELTW_FLAG_ACT_RELU           =  2,
  LIBXSMM_MELTW_FLAG_ACT_RELU_NOBITMASK =  4,
  LIBXSMM_MELTW_FLAG_ACT_TANH           =  8,
  LIBXSMM_MELTW_FLAG_ACT_SIGM           = 16,
  LIBXSMM_MELTW_FLAG_ACT_GELU           = 32,
  LIBXSMM_MELTW_FLAG_OVERWRITE_C        = 64,
  LIBXSMM_MELTW_FLAG_ACT_RELU_BWD       = 128,
  LIBXSMM_MELTW_FLAG_COLBIAS_OVERWRITE_C     =  LIBXSMM_MELTW_FLAG_COLBIAS  | LIBXSMM_MELTW_FLAG_OVERWRITE_C,
  LIBXSMM_MELTW_FLAG_ACT_RELU_OVERWRITE_C    =  LIBXSMM_MELTW_FLAG_ACT_RELU | LIBXSMM_MELTW_FLAG_OVERWRITE_C,
  LIBXSMM_MELTW_FLAG_ACT_RELU_NOBITMASK_OVERWRITE_C    =  LIBXSMM_MELTW_FLAG_ACT_RELU_NOBITMASK | LIBXSMM_MELTW_FLAG_OVERWRITE_C,
  LIBXSMM_MELTW_FLAG_ACT_TANH_OVERWRITE_C    =  LIBXSMM_MELTW_FLAG_ACT_TANH | LIBXSMM_MELTW_FLAG_OVERWRITE_C,
  LIBXSMM_MELTW_FLAG_ACT_SIGM_OVERWRITE_C    =  LIBXSMM_MELTW_FLAG_ACT_SIGM | LIBXSMM_MELTW_FLAG_OVERWRITE_C,
  LIBXSMM_MELTW_FLAG_ACT_GELU_OVERWRITE_C    =  LIBXSMM_MELTW_FLAG_ACT_GELU | LIBXSMM_MELTW_FLAG_OVERWRITE_C,
  LIBXSMM_MELTW_FLAG_ACT_RELU_BWD_OVERWRITE_C    =  LIBXSMM_MELTW_FLAG_ACT_RELU_BWD | LIBXSMM_MELTW_FLAG_OVERWRITE_C,
  LIBXSMM_MELTW_FLAG_COLBIAS_ACT_RELU = LIBXSMM_MELTW_FLAG_COLBIAS | LIBXSMM_MELTW_FLAG_ACT_RELU,
  LIBXSMM_MELTW_FLAG_COLBIAS_ACT_RELU_NOBITMASK = LIBXSMM_MELTW_FLAG_COLBIAS | LIBXSMM_MELTW_FLAG_ACT_RELU_NOBITMASK,
  LIBXSMM_MELTW_FLAG_COLBIAS_ACT_TANH = LIBXSMM_MELTW_FLAG_COLBIAS | LIBXSMM_MELTW_FLAG_ACT_TANH,
  LIBXSMM_MELTW_FLAG_COLBIAS_ACT_SIGM = LIBXSMM_MELTW_FLAG_COLBIAS | LIBXSMM_MELTW_FLAG_ACT_SIGM,
  LIBXSMM_MELTW_FLAG_COLBIAS_ACT_GELU = LIBXSMM_MELTW_FLAG_COLBIAS | LIBXSMM_MELTW_FLAG_ACT_GELU,
  LIBXSMM_MELTW_FLAG_COLBIAS_ACT_RELU_OVERWRITE_C = LIBXSMM_MELTW_FLAG_COLBIAS | LIBXSMM_MELTW_FLAG_ACT_RELU | LIBXSMM_MELTW_FLAG_OVERWRITE_C,
  LIBXSMM_MELTW_FLAG_COLBIAS_ACT_RELU_NOBITMASK_OVERWRITE_C = LIBXSMM_MELTW_FLAG_COLBIAS | LIBXSMM_MELTW_FLAG_ACT_RELU_NOBITMASK | LIBXSMM_MELTW_FLAG_OVERWRITE_C,
  LIBXSMM_MELTW_FLAG_COLBIAS_ACT_TANH_OVERWRITE_C = LIBXSMM_MELTW_FLAG_COLBIAS | LIBXSMM_MELTW_FLAG_ACT_TANH | LIBXSMM_MELTW_FLAG_OVERWRITE_C,
  LIBXSMM_MELTW_FLAG_COLBIAS_ACT_SIGM_OVERWRITE_C = LIBXSMM_MELTW_FLAG_COLBIAS | LIBXSMM_MELTW_FLAG_ACT_SIGM | LIBXSMM_MELTW_FLAG_OVERWRITE_C,
  LIBXSMM_MELTW_FLAG_COLBIAS_ACT_GELU_OVERWRITE_C = LIBXSMM_MELTW_FLAG_COLBIAS | LIBXSMM_MELTW_FLAG_ACT_GELU | LIBXSMM_MELTW_FLAG_OVERWRITE_C
} libxsmm_meltw_flags;

typedef enum libxsmm_meltw_opreduce_vecs_flags {
  LIBXSMM_MELTW_FLAG_OPREDUCE_VECS_NONE                           = 0,
  LIBXSMM_MELTW_FLAG_OPREDUCE_VECS_OPORDER_VECIN_VECIDX           = 1,
  LIBXSMM_MELTW_FLAG_OPREDUCE_VECS_OPORDER_VECIDX_VECIN           = 2,
  LIBXSMM_MELTW_FLAG_OPREDUCE_VECS_OP_COPY                        = 4,
  LIBXSMM_MELTW_FLAG_OPREDUCE_VECS_OP_ADD                         = 8,
  LIBXSMM_MELTW_FLAG_OPREDUCE_VECS_OP_SUB                         = 16,
  LIBXSMM_MELTW_FLAG_OPREDUCE_VECS_OP_MUL                         = 32,
  LIBXSMM_MELTW_FLAG_OPREDUCE_VECS_OP_DIV                         = 64,
  LIBXSMM_MELTW_FLAG_OPREDUCE_VECS_OP_DOT                         = 128,
  LIBXSMM_MELTW_FLAG_OPREDUCE_VECS_SCALE_OP_RESULT                = 256,
  LIBXSMM_MELTW_FLAG_OPREDUCE_VECS_REDOP_NONE                     = 512,
  LIBXSMM_MELTW_FLAG_OPREDUCE_VECS_REDOP_SUM                      = 1024,
  LIBXSMM_MELTW_FLAG_OPREDUCE_VECS_REDOP_MAX                      = 2048,
  LIBXSMM_MELTW_FLAG_OPREDUCE_VECS_REDOP_MIN                      = 4096,
  LIBXSMM_MELTW_FLAG_OPREDUCE_VECS_INDEXED_VEC                    = 8192,
  LIBXSMM_MELTW_FLAG_OPREDUCE_VECS_IMPLICIT_INDEXED_VEC           = 16384,
  LIBXSMM_MELTW_FLAG_OPREDUCE_VECS_IMPLICIT_INDEXED_VECIDX        = 32768,
  LIBXSMM_MELTW_FLAG_OPREDUCE_VECS_RECORD_ARGOP_OFF_VEC_0         = 65536,
  LIBXSMM_MELTW_FLAG_OPREDUCE_VECS_RECORD_ARGOP_OFF_VEC_1         = 131072,
  LIBXSMM_MELTW_FLAG_OPREDUCE_VECS_OP_COPY_REDOP_SUM              = LIBXSMM_MELTW_FLAG_OPREDUCE_VECS_OP_COPY | LIBXSMM_MELTW_FLAG_OPREDUCE_VECS_REDOP_SUM,
  LIBXSMM_MELTW_FLAG_OPREDUCE_VECS_OP_MUL_REDOP_SUM               = LIBXSMM_MELTW_FLAG_OPREDUCE_VECS_OP_MUL  | LIBXSMM_MELTW_FLAG_OPREDUCE_VECS_REDOP_SUM,
  LIBXSMM_MELTW_FLAG_OPREDUCE_VECS_OP_COPY_REDOP_MAX              = LIBXSMM_MELTW_FLAG_OPREDUCE_VECS_OP_COPY | LIBXSMM_MELTW_FLAG_OPREDUCE_VECS_REDOP_MAX,
  LIBXSMM_MELTW_FLAG_OPREDUCE_VECS_OP_COPY_REDOP_MIN              = LIBXSMM_MELTW_FLAG_OPREDUCE_VECS_OP_COPY | LIBXSMM_MELTW_FLAG_OPREDUCE_VECS_REDOP_MIN
} libxsmm_meltw_opreduce_vecs_flags;

typedef enum libxsmm_meltw_unary_flags {
  LIBXSMM_MELTW_FLAG_UNARY_NONE              = 0,
  LIBXSMM_MELTW_FLAG_UNARY_BITMASK_2BYTEMULT = 1,
  LIBXSMM_MELTW_FLAG_UNARY_BCAST_ROW         = 2,
  LIBXSMM_MELTW_FLAG_UNARY_BCAST_COL         = 4,
  LIBXSMM_MELTW_FLAG_UNARY_BCAST_SCALAR      = 8,
  LIBXSMM_MELTW_FLAG_UNARY_REDUCE_COLS       = 16,
  LIBXSMM_MELTW_FLAG_UNARY_REDUCE_ROWS       = 32,
  LIBXSMM_MELTW_FLAG_UNARY_REDUCE_XOR_ACC    = 64,
  LIBXSMM_MELTW_FLAG_UNARY_IDX_SIZE_4BYTES   = 128,
  LIBXSMM_MELTW_FLAG_UNARY_IDX_SIZE_8BYTES   = 256
} libxsmm_meltw_unary_flags;

typedef enum libxsmm_meltw_unary_type {
  LIBXSMM_MELTW_TYPE_UNARY_NONE                         =  0,
  LIBXSMM_MELTW_TYPE_UNARY_IDENTITY                     =  1,  /* this is copy */
  LIBXSMM_MELTW_TYPE_UNARY_XOR                          =  2,  /* this is zero */
  LIBXSMM_MELTW_TYPE_UNARY_X2                           =  3,
  LIBXSMM_MELTW_TYPE_UNARY_SQRT                         =  4,
  LIBXSMM_MELTW_TYPE_UNARY_RELU                         =  5,
  LIBXSMM_MELTW_TYPE_UNARY_RELU_INV                     =  6,
  LIBXSMM_MELTW_TYPE_UNARY_TANH                         =  7,
  LIBXSMM_MELTW_TYPE_UNARY_TANH_INV                     =  8,
  LIBXSMM_MELTW_TYPE_UNARY_SIGMOID                      =  9,
  LIBXSMM_MELTW_TYPE_UNARY_SIGMOID_INV                  = 10,
  LIBXSMM_MELTW_TYPE_UNARY_GELU                         = 11,
  LIBXSMM_MELTW_TYPE_UNARY_GELU_INV                     = 12,
  LIBXSMM_MELTW_TYPE_UNARY_NEGATE                       = 13,
  LIBXSMM_MELTW_TYPE_UNARY_INC                          = 14,
  LIBXSMM_MELTW_TYPE_UNARY_RECIPROCAL                   = 15,
  LIBXSMM_MELTW_TYPE_UNARY_RECIPROCAL_SQRT              = 16,
  LIBXSMM_MELTW_TYPE_UNARY_EXP                          = 17,
  LIBXSMM_MELTW_TYPE_UNARY_REDUCE_X_OP_ADD              = 18,
  LIBXSMM_MELTW_TYPE_UNARY_REDUCE_X2_OP_ADD             = 19,
  LIBXSMM_MELTW_TYPE_UNARY_REDUCE_X_X2_OP_ADD           = 20,
  LIBXSMM_MELTW_TYPE_UNARY_REDUCE_X_OP_MAX              = 21,
  LIBXSMM_MELTW_TYPE_UNARY_REDUCE_X_OP_MUL              = 22,
  LIBXSMM_MELTW_TYPE_UNARY_REDUCE_X_OP_ADD_NCNC_FORMAT  = 23,
  LIBXSMM_MELTW_TYPE_UNARY_REDUCE_TO_SCALAR_OP_ADD      = 24,
  LIBXSMM_MELTW_TYPE_UNARY_DROPOUT                      = 25,
  LIBXSMM_MELTW_TYPE_UNARY_DROPOUT_INV                  = 26,
  LIBXSMM_MELTW_TYPE_UNARY_REPLICATE_COL_VAR            = 27,
  LIBXSMM_MELTW_TYPE_UNARY_TRANSFORM_NORM_TO_VNNI       = 28,
  LIBXSMM_MELTW_TYPE_UNARY_TRANSFORM_NORM_TO_NORMT      = 29,
  LIBXSMM_MELTW_TYPE_UNARY_TRANSFORM_VNNI_TO_VNNIT      = 30,
  LIBXSMM_MELTW_TYPE_UNARY_TRANSFORM_NORM_TO_VNNIT      = 31,
  LIBXSMM_MELTW_TYPE_UNARY_TRANSFORM_NORM_TO_VNNI_PAD   = 32,
  LIBXSMM_MELTW_TYPE_UNARY_UNPACK_TO_BLOCKS             = 33,
  LIBXSMM_MELTW_TYPE_UNARY_LEAKY_RELU                   = 34,
  LIBXSMM_MELTW_TYPE_UNARY_LEAKY_RELU_INV               = 35,
  LIBXSMM_MELTW_TYPE_UNARY_ELU                          = 36,
  LIBXSMM_MELTW_TYPE_UNARY_ELU_INV                      = 37,
  LIBXSMM_MELTW_TYPE_UNARY_STOCHASTIC_ROUND             = 38,
  LIBXSMM_MELTW_TYPE_UNARY_TRANSFORM_PADM_MOD2          = 39,
  LIBXSMM_MELTW_TYPE_UNARY_TRANSFORM_PADN_MOD2          = 40,
  LIBXSMM_MELTW_TYPE_UNARY_TRANSFORM_PADNM_MOD2         = 41,
  LIBXSMM_MELTW_TYPE_UNARY_QUANT                        = 42,
  LIBXSMM_MELTW_TYPE_UNARY_DEQUANT                      = 43,
  LIBXSMM_MELTW_TYPE_UNARY_REDUCE_COLS_IDX              = 44
} libxsmm_meltw_unary_type;

typedef enum libxsmm_meltw_binary_flags {
  LIBXSMM_MELTW_FLAG_BINARY_NONE              = 0,
  LIBXSMM_MELTW_FLAG_BINARY_BCAST_ROW_IN_0    = 1,
  LIBXSMM_MELTW_FLAG_BINARY_BCAST_ROW_IN_1    = 2,
  LIBXSMM_MELTW_FLAG_BINARY_BCAST_COL_IN_0    = 4,
  LIBXSMM_MELTW_FLAG_BINARY_BCAST_COL_IN_1    = 8,
  LIBXSMM_MELTW_FLAG_BINARY_BCAST_SCALAR_IN_0 = 16,
  LIBXSMM_MELTW_FLAG_BINARY_BCAST_SCALAR_IN_1 = 32
} libxsmm_meltw_binary_flags;

typedef enum libxsmm_meltw_binary_type {
  LIBXSMM_MELTW_TYPE_BINARY_NONE        =  0,
  LIBXSMM_MELTW_TYPE_BINARY_ADD         =  1,
  LIBXSMM_MELTW_TYPE_BINARY_MUL         =  2,
  LIBXSMM_MELTW_TYPE_BINARY_SUB         =  3,
  LIBXSMM_MELTW_TYPE_BINARY_DIV         =  4,
  LIBXSMM_MELTW_TYPE_BINARY_MULADD      =  5,
  LIBXSMM_MELTW_TYPE_BINARY_MATMUL      =  6,
  LIBXSMM_MELTW_TYPE_BINARY_MUL_AND_REDUCE_TO_SCALAR_OP_ADD = 7,
  LIBXSMM_MELTW_TYPE_BINARY_PACK        =  8
} libxsmm_meltw_binary_type;

typedef enum libxsmm_meltw_ternary_flags {
  LIBXSMM_MELTW_FLAG_TERNARY_NONE              =   0,
  LIBXSMM_MELTW_FLAG_TERNARY_BCAST_ROW_IN_0    =   1,
  LIBXSMM_MELTW_FLAG_TERNARY_BCAST_ROW_IN_1    =   2,
  LIBXSMM_MELTW_FLAG_TERNARY_BCAST_ROW_IN_2    =   4,
  LIBXSMM_MELTW_FLAG_TERNARY_BCAST_COL_IN_0    =   8,
  LIBXSMM_MELTW_FLAG_TERNARY_BCAST_COL_IN_1    =  16,
  LIBXSMM_MELTW_FLAG_TERNARY_BCAST_COL_IN_2    =  32,
  LIBXSMM_MELTW_FLAG_TERNARY_BCAST_SCALAR_IN_0 =  64,
  LIBXSMM_MELTW_FLAG_TERNARY_BCAST_SCALAR_IN_1 = 128,
  LIBXSMM_MELTW_FLAG_TERNARY_BCAST_SCALAR_IN_2 = 256,
  LIBXSMM_MELTW_FLAG_TERNARY_REUSE_IN_2_AS_OUT = 512
} libxsmm_meltw_ternary_flags;

typedef enum libxsmm_meltw_ternary_type {
  LIBXSMM_MELTW_TYPE_TERNARY_NONE        =  0,
  LIBXSMM_MELTW_TYPE_TERNARY_MULADD      =  1,
  LIBXSMM_MELTW_TYPE_TERNARY_MATMUL      =  2,
  LIBXSMM_MELTW_TYPE_TERNARY_BLEND       =  3,
  LIBXSMM_MELTW_TYPE_TERNARY_NMULADD     =  4
} libxsmm_meltw_ternary_type;

LIBXSMM_EXTERN_C typedef union LIBXSMM_RETARGETABLE libxsmm_xmelt_flags {
  libxsmm_meltw_null_flags          elt_null;
  libxsmm_meltw_opreduce_vecs_flags elt_opredvecs;
  libxsmm_meltw_relu_flags          elt_relu;
  libxsmm_meltw_cvta_flags          elt_cvta;
  libxsmm_meltw_cvt_flags           elt_cvt;
  libxsmm_meltw_acvt_flags          elt_acvt;
  libxsmm_meltw_flags               elt_meltwfused;
} libxsmm_xmelt_flags;

/** Flag enumeration which can be binary ORed. */
typedef enum libxsmm_gemm_flags {
  LIBXSMM_GEMM_FLAG_NONE = 0,
  /** Transpose matrix A. */
  LIBXSMM_GEMM_FLAG_TRANS_A = 1,
  /** Transpose matrix B. */
  LIBXSMM_GEMM_FLAG_TRANS_B = 2,
  /** Transpose matrix A and B. */
  LIBXSMM_GEMM_FLAG_TRANS_AB = LIBXSMM_GEMM_FLAG_TRANS_A | LIBXSMM_GEMM_FLAG_TRANS_B,
  /** Beta=0|1 */
  LIBXSMM_GEMM_FLAG_BETA_0 = 4,
  /** Generate aligned load instructions. */
  LIBXSMM_GEMM_FLAG_ALIGN_A = 8,
  /** Aligned load/store instructions. */
  LIBXSMM_GEMM_FLAG_ALIGN_C = 16,
  /** Batch-reduce Ai * Bi. */
  /** AMX hint to avoid tileconfig/release, it's negated bits, so that 0 is default "on" */
  LIBXSMM_GEMM_FLAG_NO_RESET_TILECONFIG = 32,
  LIBXSMM_GEMM_FLAG_NO_SETUP_TILECONFIG = 64,
  LIBXSMM_GEMM_FLAG_BATCH_REDUCE_ADDRESS = 128,
  /** Batch-reduce Ai * Bi. */
  LIBXSMM_GEMM_FLAG_BATCH_REDUCE_OFFSET = 256,
  /** Batch-reduce Ai * Bi. */
  LIBXSMM_GEMM_FLAG_BATCH_REDUCE_STRIDE = 512,
  /** Aligned C matrix, but using NTS Hint when storing */
  LIBXSMM_GEMM_FLAG_ALIGN_C_NTS_HINT = 1024 | LIBXSMM_GEMM_FLAG_ALIGN_C,
  /* in case of integer GEMM, if A is unsigned */
  LIBXSMM_GEMM_FLAG_A_UNSIGNED = 2048,
  /* in case of integer GEMM, if B is unsigned */
  LIBXSMM_GEMM_FLAG_B_UNSIGNED = 4096,
  /* in case of integer GEMM, if C is unsigned */
  LIBXSMM_GEMM_FLAG_C_UNSIGNED = 8192,
  /* in case of integer GEMM, if A and B are unsigned */
  LIBXSMM_GEMM_FLAG_AB_UNSIGNED = LIBXSMM_GEMM_FLAG_A_UNSIGNED | LIBXSMM_GEMM_FLAG_B_UNSIGNED,
  /* for low precision we also require up-front packed formats "VNNI" for best performance, this flag indicates A */
  LIBXSMM_GEMM_FLAG_VNNI_A = 16384,
  /* for low precision we also require up-front packed formats "VNNI" for best performance, this flag indicates B */
  LIBXSMM_GEMM_FLAG_VNNI_B = 32768,
  /* for low precision we also require post packed formats "VNNI" for best performance, this flag indicated C */
  LIBXSMM_GEMM_FLAG_VNNI_C = 65536,
  /* combined types */
  LIBXSMM_GEMM_FLAG_ALIGN_C_NTS_HINT_BETA_0                      = LIBXSMM_GEMM_FLAG_BETA_0       | LIBXSMM_GEMM_FLAG_ALIGN_C_NTS_HINT,
  LIBXSMM_GEMM_FLAG_ALIGN_C_NTS_HINT_BATCH_REDUCE_ADDRESS        = LIBXSMM_GEMM_FLAG_BATCH_REDUCE_ADDRESS | LIBXSMM_GEMM_FLAG_ALIGN_C_NTS_HINT,
  LIBXSMM_GEMM_FLAG_ALIGN_C_NTS_HINT_BETA_0_BATCH_REDUCE_ADDRESS = LIBXSMM_GEMM_FLAG_BETA_0       | LIBXSMM_GEMM_FLAG_ALIGN_C_NTS_HINT | LIBXSMM_GEMM_FLAG_BATCH_REDUCE_ADDRESS,
  LIBXSMM_GEMM_FLAG_ALIGN_C_NTS_HINT_BATCH_REDUCE_OFFSET         = LIBXSMM_GEMM_FLAG_BATCH_REDUCE_OFFSET | LIBXSMM_GEMM_FLAG_ALIGN_C_NTS_HINT,
  LIBXSMM_GEMM_FLAG_ALIGN_C_NTS_HINT_BETA_0_BATCH_REDUCE_OFFSET  = LIBXSMM_GEMM_FLAG_BETA_0       | LIBXSMM_GEMM_FLAG_ALIGN_C_NTS_HINT | LIBXSMM_GEMM_FLAG_BATCH_REDUCE_OFFSET,
  LIBXSMM_GEMM_FLAG_ALIGN_C_NTS_HINT_BATCH_REDUCE_STRIDE         = LIBXSMM_GEMM_FLAG_BATCH_REDUCE_STRIDE | LIBXSMM_GEMM_FLAG_ALIGN_C_NTS_HINT,
  LIBXSMM_GEMM_FLAG_ALIGN_C_NTS_HINT_BETA_0_BATCH_REDUCE_STRIDE  = LIBXSMM_GEMM_FLAG_BETA_0       | LIBXSMM_GEMM_FLAG_ALIGN_C_NTS_HINT | LIBXSMM_GEMM_FLAG_BATCH_REDUCE_STRIDE,
  LIBXSMM_GEMM_FLAG_ALIGN_C_NTS_HINT_BETA_0_A_UNSIGNED                      = LIBXSMM_GEMM_FLAG_BETA_0       | LIBXSMM_GEMM_FLAG_ALIGN_C_NTS_HINT | LIBXSMM_GEMM_FLAG_A_UNSIGNED,
  LIBXSMM_GEMM_FLAG_ALIGN_C_NTS_HINT_BATCH_REDUCE_ADDRESS_A_UNSIGNED        = LIBXSMM_GEMM_FLAG_BATCH_REDUCE_ADDRESS | LIBXSMM_GEMM_FLAG_ALIGN_C_NTS_HINT | LIBXSMM_GEMM_FLAG_A_UNSIGNED,
  LIBXSMM_GEMM_FLAG_ALIGN_C_NTS_HINT_BETA_0_BATCH_REDUCE_ADDRESS_A_UNSIGNED = LIBXSMM_GEMM_FLAG_BETA_0       | LIBXSMM_GEMM_FLAG_ALIGN_C_NTS_HINT | LIBXSMM_GEMM_FLAG_BATCH_REDUCE_ADDRESS | LIBXSMM_GEMM_FLAG_A_UNSIGNED,
  LIBXSMM_GEMM_FLAG_ALIGN_C_NTS_HINT_BATCH_REDUCE_OFFSET_A_UNSIGNED         = LIBXSMM_GEMM_FLAG_BATCH_REDUCE_OFFSET | LIBXSMM_GEMM_FLAG_ALIGN_C_NTS_HINT | LIBXSMM_GEMM_FLAG_A_UNSIGNED,
  LIBXSMM_GEMM_FLAG_ALIGN_C_NTS_HINT_BETA_0_BATCH_REDUCE_OFFSET_A_UNSIGNED  = LIBXSMM_GEMM_FLAG_BETA_0       | LIBXSMM_GEMM_FLAG_ALIGN_C_NTS_HINT | LIBXSMM_GEMM_FLAG_BATCH_REDUCE_OFFSET | LIBXSMM_GEMM_FLAG_A_UNSIGNED,
  LIBXSMM_GEMM_FLAG_ALIGN_C_NTS_HINT_BATCH_REDUCE_STRIDE_A_UNSIGNED         = LIBXSMM_GEMM_FLAG_BATCH_REDUCE_STRIDE | LIBXSMM_GEMM_FLAG_ALIGN_C_NTS_HINT | LIBXSMM_GEMM_FLAG_A_UNSIGNED,
  LIBXSMM_GEMM_FLAG_ALIGN_C_NTS_HINT_BETA_0_BATCH_REDUCE_STRIDE_A_UNSIGNED  = LIBXSMM_GEMM_FLAG_BETA_0       | LIBXSMM_GEMM_FLAG_ALIGN_C_NTS_HINT | LIBXSMM_GEMM_FLAG_BATCH_REDUCE_STRIDE | LIBXSMM_GEMM_FLAG_A_UNSIGNED,
  LIBXSMM_GEMM_FLAG_ALIGN_C_NTS_HINT_BETA_0_B_UNSIGNED                      = LIBXSMM_GEMM_FLAG_BETA_0       | LIBXSMM_GEMM_FLAG_ALIGN_C_NTS_HINT | LIBXSMM_GEMM_FLAG_B_UNSIGNED,
  LIBXSMM_GEMM_FLAG_ALIGN_C_NTS_HINT_BATCH_REDUCE_ADDRESS_B_UNSIGNED        = LIBXSMM_GEMM_FLAG_BATCH_REDUCE_ADDRESS | LIBXSMM_GEMM_FLAG_ALIGN_C_NTS_HINT | LIBXSMM_GEMM_FLAG_B_UNSIGNED,
  LIBXSMM_GEMM_FLAG_ALIGN_C_NTS_HINT_BETA_0_BATCH_REDUCE_ADDRESS_B_UNSIGNED = LIBXSMM_GEMM_FLAG_BETA_0       | LIBXSMM_GEMM_FLAG_ALIGN_C_NTS_HINT | LIBXSMM_GEMM_FLAG_BATCH_REDUCE_ADDRESS | LIBXSMM_GEMM_FLAG_B_UNSIGNED,
  LIBXSMM_GEMM_FLAG_ALIGN_C_NTS_HINT_BATCH_REDUCE_OFFSET_B_UNSIGNED         = LIBXSMM_GEMM_FLAG_BATCH_REDUCE_OFFSET | LIBXSMM_GEMM_FLAG_ALIGN_C_NTS_HINT | LIBXSMM_GEMM_FLAG_B_UNSIGNED,
  LIBXSMM_GEMM_FLAG_ALIGN_C_NTS_HINT_BETA_0_BATCH_REDUCE_OFFSET_B_UNSIGNED  = LIBXSMM_GEMM_FLAG_BETA_0       | LIBXSMM_GEMM_FLAG_ALIGN_C_NTS_HINT | LIBXSMM_GEMM_FLAG_BATCH_REDUCE_OFFSET | LIBXSMM_GEMM_FLAG_B_UNSIGNED,
  LIBXSMM_GEMM_FLAG_ALIGN_C_NTS_HINT_BATCH_REDUCE_STRIDE_B_UNSIGNED         = LIBXSMM_GEMM_FLAG_BATCH_REDUCE_STRIDE | LIBXSMM_GEMM_FLAG_ALIGN_C_NTS_HINT | LIBXSMM_GEMM_FLAG_B_UNSIGNED,
  LIBXSMM_GEMM_FLAG_ALIGN_C_NTS_HINT_BETA_0_BATCH_REDUCE_STRIDE_B_UNSIGNED  = LIBXSMM_GEMM_FLAG_BETA_0       | LIBXSMM_GEMM_FLAG_ALIGN_C_NTS_HINT | LIBXSMM_GEMM_FLAG_BATCH_REDUCE_STRIDE | LIBXSMM_GEMM_FLAG_B_UNSIGNED,
  LIBXSMM_GEMM_FLAG_ALIGN_C_NTS_HINT_BETA_0_AB_UNSIGNED                      = LIBXSMM_GEMM_FLAG_BETA_0       | LIBXSMM_GEMM_FLAG_ALIGN_C_NTS_HINT | LIBXSMM_GEMM_FLAG_AB_UNSIGNED,
  LIBXSMM_GEMM_FLAG_ALIGN_C_NTS_HINT_BATCH_REDUCE_ADDRESS_AB_UNSIGNED        = LIBXSMM_GEMM_FLAG_BATCH_REDUCE_ADDRESS | LIBXSMM_GEMM_FLAG_ALIGN_C_NTS_HINT | LIBXSMM_GEMM_FLAG_AB_UNSIGNED,
  LIBXSMM_GEMM_FLAG_ALIGN_C_NTS_HINT_BETA_0_BATCH_REDUCE_ADDRESS_AB_UNSIGNED = LIBXSMM_GEMM_FLAG_BETA_0       | LIBXSMM_GEMM_FLAG_ALIGN_C_NTS_HINT | LIBXSMM_GEMM_FLAG_BATCH_REDUCE_ADDRESS | LIBXSMM_GEMM_FLAG_AB_UNSIGNED,
  LIBXSMM_GEMM_FLAG_ALIGN_C_NTS_HINT_BATCH_REDUCE_OFFSET_AB_UNSIGNED         = LIBXSMM_GEMM_FLAG_BATCH_REDUCE_OFFSET | LIBXSMM_GEMM_FLAG_ALIGN_C_NTS_HINT | LIBXSMM_GEMM_FLAG_AB_UNSIGNED,
  LIBXSMM_GEMM_FLAG_ALIGN_C_NTS_HINT_BETA_0_BATCH_REDUCE_OFFSET_AB_UNSIGNED  = LIBXSMM_GEMM_FLAG_BETA_0       | LIBXSMM_GEMM_FLAG_ALIGN_C_NTS_HINT | LIBXSMM_GEMM_FLAG_BATCH_REDUCE_OFFSET | LIBXSMM_GEMM_FLAG_AB_UNSIGNED,
  LIBXSMM_GEMM_FLAG_ALIGN_C_NTS_HINT_BATCH_REDUCE_STRIDE_AB_UNSIGNED         = LIBXSMM_GEMM_FLAG_BATCH_REDUCE_STRIDE | LIBXSMM_GEMM_FLAG_ALIGN_C_NTS_HINT | LIBXSMM_GEMM_FLAG_AB_UNSIGNED,
  LIBXSMM_GEMM_FLAG_ALIGN_C_NTS_HINT_BETA_0_BATCH_REDUCE_STRIDE_AB_UNSIGNED  = LIBXSMM_GEMM_FLAG_BETA_0       | LIBXSMM_GEMM_FLAG_ALIGN_C_NTS_HINT | LIBXSMM_GEMM_FLAG_BATCH_REDUCE_STRIDE | LIBXSMM_GEMM_FLAG_AB_UNSIGNED,
  /** Marker flag; do not use. */
  LIBXSMM_GEMM_FLAG_INVALID = 131072
} libxsmm_gemm_flags;

/** Flag enumeration which can be binary ORed. */
typedef enum libxsmm_gemm_handle_flags {
  LIBXSMM_GEMM_HANDLE_FLAG_AUTO   = 0,
  LIBXSMM_GEMM_HANDLE_FLAG_COPY_A = 1,
  LIBXSMM_GEMM_HANDLE_FLAG_COPY_B = 2,
  LIBXSMM_GEMM_HANDLE_FLAG_COPY_C = 4
} libxsmm_gemm_handle_flags;

/** Auto-batch flags (can be ORed) applicable to mmbatch_begin/mmbatch_end. */
typedef enum libxsmm_mmbatch_flags {
  /** Handle recorded batch unsynchronized-parallel. */
  LIBXSMM_MMBATCH_FLAG_DEFAULT      = LIBXSMM_GEMM_FLAG_INVALID * 0,
  /** Synchronize among C matrices. */
  LIBXSMM_MMBATCH_FLAG_SYNCHRONIZED = LIBXSMM_GEMM_FLAG_INVALID * 1,
  /** Handle recorded batch sequentially. */
  LIBXSMM_MMBATCH_FLAG_SEQUENTIAL   = LIBXSMM_GEMM_FLAG_INVALID * 2,
  /** Only record a statistic of potential SMMs. */
  LIBXSMM_MMBATCH_FLAG_STATISTIC    = LIBXSMM_GEMM_FLAG_INVALID * 4
} libxsmm_mmbatch_flags;

/** Enumeration of the available prefetch strategies. */
typedef enum libxsmm_gemm_prefetch_type {
  /** No prefetching and no prefetch fn. signature. */
  LIBXSMM_GEMM_PREFETCH_NONE               = LIBXSMM_PREFETCH_NONE,
  /** Only function prefetch signature. */
  LIBXSMM_GEMM_PREFETCH_SIGONLY            = LIBXSMM_PREFETCH_SIGONLY,
  /** Prefetch PA using accesses to A. */
  LIBXSMM_GEMM_PREFETCH_AL2                = 2,
  /** Prefetch PA (aggressive). */
  LIBXSMM_GEMM_PREFETCH_BL2_VIA_C          = 4,
  /** Prefetch A ahead. */
  LIBXSMM_GEMM_PREFETCH_AL2_AHEAD          = 8,
  LIBXSMM_GEMM_PREFETCH_AL2BL2_VIA_C       = LIBXSMM_GEMM_PREFETCH_BL2_VIA_C | LIBXSMM_GEMM_PREFETCH_AL2,
  LIBXSMM_GEMM_PREFETCH_AL2BL2_VIA_C_AHEAD = LIBXSMM_GEMM_PREFETCH_BL2_VIA_C | LIBXSMM_GEMM_PREFETCH_AL2_AHEAD,
  /** Backward compatibility: AL2CL2BL2_VIA_C is an alias for AL2BL2_VIA_C (Eigen library). */
  LIBXSMM_PREFETCH_AL2CL2BL2_VIA_C         = LIBXSMM_GEMM_PREFETCH_AL2BL2_VIA_C,
  /** Current B into L1. */
  LIBXSMM_GEMM_PREFETCH_BL1                = 16,
  LIBXSMM_GEMM_PREFETCH_BRGEMM_OOB         = 32
} libxsmm_gemm_prefetch_type;

/** Flag enumeration which can be binary ORed. */
typedef enum libxsmm_matcopy_flags {
  LIBXSMM_MATCOPY_FLAG_DEFAULT = 0,
  /** If set, then use zero matrix as source */
  LIBXSMM_MATCOPY_FLAG_ZERO_SOURCE = 1
} libxsmm_matcopy_flags;

/** Determines the kernel kind. */
typedef enum libxsmm_kernel_kind {
  /** Matrix multiplication kernel */
  LIBXSMM_KERNEL_KIND_MATMUL  = 0,
  /** Mateltw kernel kind */
  LIBXSMM_KERNEL_KIND_MELTW   = 1,
  /** Mateqn kernel kind */
  LIBXSMM_KERNEL_KIND_MEQN    = 2,
  /** User-defined kernels */
  LIBXSMM_KERNEL_KIND_USER    = 3,
  /** Not a JIT kernel */
  LIBXSMM_KERNEL_UNREGISTERED = 4
} libxsmm_kernel_kind;

typedef enum libxsmm_dnn_tensor_format {
  /* use LIBXSMM internal format, we need to copy data into that */
  LIBXSMM_DNN_TENSOR_FORMAT_LIBXSMM  = 1,
  /* use NHWC format internally, this allows no-copy operations */
  LIBXSMM_DNN_TENSOR_FORMAT_NHWC     = 2,
  /* use NCHW format internally, this will include shadow copies, not preferred */
  LIBXSMM_DNN_TENSOR_FORMAT_NCHW     = 4,
  /* use RSCK format internally, this allows no-copy operations */
  LIBXSMM_DNN_TENSOR_FORMAT_RSCK     = 8,
  /* use KCRS format internally, this will include shadow copies, not preferred */
  LIBXSMM_DNN_TENSOR_FORMAT_KCRS     = 16,
  LIBXSMM_DNN_TENSOR_FORMAT_CK       = 32,
  LIBXSMM_DNN_TENSOR_FORMAT_CKPACKED = 64,
  LIBXSMM_DNN_TENSOR_FORMAT_NCPACKED = 128,
  LIBXSMM_DNN_TENSOR_FORMAT_NC       = 256
} libxsmm_dnn_tensor_format;

/** Denotes the element/pixel type of an image/channel. */
typedef enum libxsmm_dnn_datatype {
  LIBXSMM_DNN_DATATYPE_F64  = LIBXSMM_DATATYPE_F64,
  LIBXSMM_DNN_DATATYPE_F32  = LIBXSMM_DATATYPE_F32,
  LIBXSMM_DNN_DATATYPE_BF16 = LIBXSMM_DATATYPE_BF16,
  LIBXSMM_DNN_DATATYPE_F16  = LIBXSMM_DATATYPE_F16,
  LIBXSMM_DNN_DATATYPE_I32  = LIBXSMM_DATATYPE_I32,
  LIBXSMM_DNN_DATATYPE_I16  = LIBXSMM_DATATYPE_I16,
  LIBXSMM_DNN_DATATYPE_I8   = LIBXSMM_DATATYPE_I8
} libxsmm_dnn_datatype;

typedef enum libxsmm_dnn_conv_option {
  /* we get default settings */
  LIBXSMM_DNN_CONV_OPTION_NONE = 0,
  /* overwrite results buffer (set it to zero before running the operations) */
  LIBXSMM_DNN_CONV_OPTION_OVERWRITE = 1,
  /* external filter transpose to bwd convolutions */
  LIBXSMM_DNN_CONV_OPTION_BWD_NO_FILTER_TRANSPOSE = 2,
  /* compound types */
  LIBXSMM_DNN_CONV_OPTION_BWD_NO_FILTER_TRANSPOSE_OVERWRITE = LIBXSMM_DNN_CONV_OPTION_OVERWRITE | LIBXSMM_DNN_CONV_OPTION_BWD_NO_FILTER_TRANSPOSE
} libxsmm_dnn_conv_option;

typedef enum libxsmm_dnn_fusedbatchnorm_fuse_order {
  /* the fuse order is: 1. BN, 2. element-wise 3. RELU */
  LIBXSMM_DNN_FUSEDBN_ORDER_BN_ELTWISE_RELU = 0
} libxsmm_dnn_fusedbatchnorm_fuse_order;

typedef enum libxsmm_dnn_fusedbatchnorm_fuse_op {
  /* the fuse order is: 1. BN, 2. element-wise 3. RELU */
  LIBXSMM_DNN_FUSEDBN_OPS_BN = 1,
  LIBXSMM_DNN_FUSEDBN_OPS_BNSCALE = 2,
  LIBXSMM_DNN_FUSEDBN_OPS_BNSTATS = 4,
  LIBXSMM_DNN_FUSEDBN_OPS_BNSTATS_NORED = 8,
  LIBXSMM_DNN_FUSEDBN_OPS_ELTWISE = 16,
  LIBXSMM_DNN_FUSEDBN_OPS_RELU = 32,
  LIBXSMM_DNN_FUSEDBN_OPS_RELU_WITH_MASK = 64,
  LIBXSMM_DNN_FUSEDBN_OPS_ELTWISE_RELU = LIBXSMM_DNN_FUSEDBN_OPS_ELTWISE | LIBXSMM_DNN_FUSEDBN_OPS_RELU,
  LIBXSMM_DNN_FUSEDBN_OPS_ELTWISE_RELU_WITH_MASK = LIBXSMM_DNN_FUSEDBN_OPS_ELTWISE | LIBXSMM_DNN_FUSEDBN_OPS_RELU_WITH_MASK,
  LIBXSMM_DNN_FUSEDBN_OPS_BN_ELTWISE = LIBXSMM_DNN_FUSEDBN_OPS_BN | LIBXSMM_DNN_FUSEDBN_OPS_ELTWISE,
  LIBXSMM_DNN_FUSEDBN_OPS_BN_RELU = LIBXSMM_DNN_FUSEDBN_OPS_BN | LIBXSMM_DNN_FUSEDBN_OPS_RELU,
  LIBXSMM_DNN_FUSEDBN_OPS_BN_RELU_WITH_MASK = LIBXSMM_DNN_FUSEDBN_OPS_BN | LIBXSMM_DNN_FUSEDBN_OPS_RELU_WITH_MASK,
  LIBXSMM_DNN_FUSEDBN_OPS_BN_ELTWISE_RELU = LIBXSMM_DNN_FUSEDBN_OPS_BN | LIBXSMM_DNN_FUSEDBN_OPS_ELTWISE | LIBXSMM_DNN_FUSEDBN_OPS_RELU,
  LIBXSMM_DNN_FUSEDBN_OPS_BN_ELTWISE_RELU_WITH_MASK = LIBXSMM_DNN_FUSEDBN_OPS_BN | LIBXSMM_DNN_FUSEDBN_OPS_ELTWISE | LIBXSMM_DNN_FUSEDBN_OPS_RELU_WITH_MASK,
  LIBXSMM_DNN_FUSEDBN_OPS_BNSCALE_ELTWISE = LIBXSMM_DNN_FUSEDBN_OPS_BNSCALE | LIBXSMM_DNN_FUSEDBN_OPS_ELTWISE,
  LIBXSMM_DNN_FUSEDBN_OPS_BNSCALE_RELU = LIBXSMM_DNN_FUSEDBN_OPS_BNSCALE | LIBXSMM_DNN_FUSEDBN_OPS_RELU,
  LIBXSMM_DNN_FUSEDBN_OPS_BNSCALE_RELU_WITH_MASK = LIBXSMM_DNN_FUSEDBN_OPS_BNSCALE | LIBXSMM_DNN_FUSEDBN_OPS_RELU_WITH_MASK,
  LIBXSMM_DNN_FUSEDBN_OPS_BNSCALE_ELTWISE_RELU = LIBXSMM_DNN_FUSEDBN_OPS_BNSCALE | LIBXSMM_DNN_FUSEDBN_OPS_ELTWISE | LIBXSMM_DNN_FUSEDBN_OPS_RELU,
  LIBXSMM_DNN_FUSEDBN_OPS_BNSCALE_ELTWISE_RELU_WITH_MASK = LIBXSMM_DNN_FUSEDBN_OPS_BNSCALE | LIBXSMM_DNN_FUSEDBN_OPS_ELTWISE | LIBXSMM_DNN_FUSEDBN_OPS_RELU_WITH_MASK,
  LIBXSMM_DNN_FUSEDBN_OPS_BNSTATS_ELTWISE = LIBXSMM_DNN_FUSEDBN_OPS_BNSTATS | LIBXSMM_DNN_FUSEDBN_OPS_ELTWISE,
  LIBXSMM_DNN_FUSEDBN_OPS_BNSTATS_RELU = LIBXSMM_DNN_FUSEDBN_OPS_BNSTATS | LIBXSMM_DNN_FUSEDBN_OPS_RELU,
  LIBXSMM_DNN_FUSEDBN_OPS_BNSTATS_RELU_WITH_MASK = LIBXSMM_DNN_FUSEDBN_OPS_BNSTATS | LIBXSMM_DNN_FUSEDBN_OPS_RELU_WITH_MASK,
  LIBXSMM_DNN_FUSEDBN_OPS_BNSTATS_ELTWISE_RELU = LIBXSMM_DNN_FUSEDBN_OPS_BNSTATS | LIBXSMM_DNN_FUSEDBN_OPS_ELTWISE | LIBXSMM_DNN_FUSEDBN_OPS_RELU,
  LIBXSMM_DNN_FUSEDBN_OPS_BNSTATS_ELTWISE_RELU_WITH_MASK = LIBXSMM_DNN_FUSEDBN_OPS_BNSTATS | LIBXSMM_DNN_FUSEDBN_OPS_ELTWISE | LIBXSMM_DNN_FUSEDBN_OPS_RELU_WITH_MASK,
  LIBXSMM_DNN_FUSEDBN_OPS_BNSTATS_NORED_ELTWISE = LIBXSMM_DNN_FUSEDBN_OPS_BNSTATS_NORED | LIBXSMM_DNN_FUSEDBN_OPS_ELTWISE,
  LIBXSMM_DNN_FUSEDBN_OPS_BNSTATS_NORED_RELU = LIBXSMM_DNN_FUSEDBN_OPS_BNSTATS_NORED | LIBXSMM_DNN_FUSEDBN_OPS_RELU,
  LIBXSMM_DNN_FUSEDBN_OPS_BNSTATS_NORED_RELU_WITH_MASK = LIBXSMM_DNN_FUSEDBN_OPS_BNSTATS_NORED | LIBXSMM_DNN_FUSEDBN_OPS_RELU_WITH_MASK,
  LIBXSMM_DNN_FUSEDBN_OPS_BNSTATS_NORED_ELTWISE_RELU = LIBXSMM_DNN_FUSEDBN_OPS_BNSTATS_NORED | LIBXSMM_DNN_FUSEDBN_OPS_ELTWISE | LIBXSMM_DNN_FUSEDBN_OPS_RELU,
  LIBXSMM_DNN_FUSEDBN_OPS_BNSTATS_NORED_ELTWISE_RELU_WITH_MASK = LIBXSMM_DNN_FUSEDBN_OPS_BNSTATS_NORED | LIBXSMM_DNN_FUSEDBN_OPS_ELTWISE | LIBXSMM_DNN_FUSEDBN_OPS_RELU_WITH_MASK
} libxsmm_dnn_fusedbatchnorm_fuse_op;

LIBXSMM_EXTERN_C typedef struct LIBXSMM_RETARGETABLE libxsmm_dnn_fusedbatchnorm_desc {
  int partN;                                 /* number of images in mini-batch, used for all elementwise computations */
  int fullN;                                 /* number of images in mini-batch, used for statistics computations */
  int C;                                     /* number of input feature maps */
  int H;                                     /* height of input image */
  int W;                                     /* width of input image */
  int u;                                     /* vertical stride */
  int v;                                     /* horizontal stride */
  int pad_h_in;                              /* height of physical zero-padding in input buffer */
  int pad_w_in;                              /* width of physical zero-padding in input buffer */
  int pad_h_out;                             /* height of physical zero-padding in output buffer */
  int pad_w_out;                             /* width of physical zero-padding in output buffer */
  int threads;                               /* number of threads used */
  libxsmm_dnn_datatype datatype_in;          /* datatype used for all input related buffers */
  libxsmm_dnn_datatype datatype_out;         /* datatype used for all output related buffers */
  libxsmm_dnn_datatype datatype_stats;       /* datatype used for all stats related buffers */
  libxsmm_dnn_tensor_format buffer_format;   /* format which is for activation buffers */
  libxsmm_dnn_fusedbatchnorm_fuse_order fuse_order; /* additional options */
  libxsmm_dnn_fusedbatchnorm_fuse_op fuse_ops;      /* used ops into convolutions */
} libxsmm_dnn_fusedbatchnorm_desc;

typedef enum libxsmm_dnn_fusedgroupnorm_fuse_order {
  /* the fuse order is: 1. BN, 2. element-wise 3. RELU */
  LIBXSMM_DNN_FUSEDGN_ORDER_GN_ELTWISE_RELU = 0
} libxsmm_dnn_fusedgroupnorm_fuse_order;

typedef enum libxsmm_dnn_fusedgroupnorm_fuse_op {
  /* the fuse order is: 1. GN, 2. element-wise 3. RELU */
  LIBXSMM_DNN_FUSEDGN_OPS_GN = 1,
  LIBXSMM_DNN_FUSEDGN_OPS_ELTWISE = 2,
  LIBXSMM_DNN_FUSEDGN_OPS_RELU = 4,
  LIBXSMM_DNN_FUSEDGN_OPS_RELU_WITH_MASK = 8,
  LIBXSMM_DNN_FUSEDGN_OPS_ELTWISE_RELU = LIBXSMM_DNN_FUSEDGN_OPS_ELTWISE | LIBXSMM_DNN_FUSEDGN_OPS_RELU,
  LIBXSMM_DNN_FUSEDGN_OPS_ELTWISE_RELU_WITH_MASK = LIBXSMM_DNN_FUSEDGN_OPS_ELTWISE | LIBXSMM_DNN_FUSEDGN_OPS_RELU_WITH_MASK,
  LIBXSMM_DNN_FUSEDGN_OPS_GN_ELTWISE = LIBXSMM_DNN_FUSEDGN_OPS_GN | LIBXSMM_DNN_FUSEDGN_OPS_ELTWISE,
  LIBXSMM_DNN_FUSEDGN_OPS_GN_RELU = LIBXSMM_DNN_FUSEDGN_OPS_GN | LIBXSMM_DNN_FUSEDGN_OPS_RELU,
  LIBXSMM_DNN_FUSEDGN_OPS_GN_RELU_WITH_MASK = LIBXSMM_DNN_FUSEDGN_OPS_GN | LIBXSMM_DNN_FUSEDGN_OPS_RELU_WITH_MASK,
  LIBXSMM_DNN_FUSEDGN_OPS_GN_ELTWISE_RELU = LIBXSMM_DNN_FUSEDGN_OPS_GN | LIBXSMM_DNN_FUSEDGN_OPS_ELTWISE | LIBXSMM_DNN_FUSEDGN_OPS_RELU,
  LIBXSMM_DNN_FUSEDGN_OPS_GN_ELTWISE_RELU_WITH_MASK = LIBXSMM_DNN_FUSEDGN_OPS_GN | LIBXSMM_DNN_FUSEDGN_OPS_ELTWISE | LIBXSMM_DNN_FUSEDGN_OPS_RELU_WITH_MASK
} libxsmm_dnn_fusedgroupnorm_fuse_op;

LIBXSMM_EXTERN_C typedef struct LIBXSMM_RETARGETABLE libxsmm_dnn_fusedgroupnorm_desc {
  int N;                                     /* number of images in mini-batch */
  int G;                                     /* groups of channels to norm */
  int C;                                     /* number of input feature maps */
  int H;                                     /* height of input image */
  int W;                                     /* width of input image */
  int u;                                     /* vertical stride */
  int v;                                     /* horizontal stride */
  int pad_h_in;                              /* height of physical zero-padding in input buffer */
  int pad_w_in;                              /* width of physical zero-padding in input buffer */
  int pad_h_out;                             /* height of physical zero-padding in output buffer */
  int pad_w_out;                             /* width of physical zero-padding in output buffer */
  int threads;                               /* number of threads used */
  libxsmm_dnn_datatype datatype_in;          /* datatype used for all input related buffers */
  libxsmm_dnn_datatype datatype_out;         /* datatype used for all output related buffers */
  libxsmm_dnn_datatype datatype_stats;       /* datatype used for all stats related buffers */
  libxsmm_dnn_tensor_format buffer_format;   /* format which is for activation buffers */
  libxsmm_dnn_fusedgroupnorm_fuse_order fuse_order; /* additional options */
  libxsmm_dnn_fusedgroupnorm_fuse_op fuse_ops;      /* used ops into convolutions */
} libxsmm_dnn_fusedgroupnorm_desc;

LIBXSMM_EXTERN_C typedef struct LIBXSMM_RETARGETABLE libxsmm_matrix_arg {
  void* primary;
  void* secondary;
  void* tertiary;
} libxsmm_matrix_arg;

LIBXSMM_EXTERN_C typedef struct LIBXSMM_RETARGETABLE libxsmm_matrix_op_arg {
  void* primary;
  void* secondary;
  void* tertiary;
  void* quaternary;
} libxsmm_matrix_op_arg;

/** argument struct for matrix-eltwise: opreduce vecs indexed */
LIBXSMM_EXTERN_C typedef struct LIBXSMM_RETARGETABLE libxsmm_meltw_opreduce_vecs_idx_param {
  unsigned long long n;
  const void* indices;       /* index array pointer */
  const void* in_matrix;     /* input matrix pointer */
  const void* in_vec;        /* input vector pointer */
  void* out_vec;             /* output pointer */
  const void* scale_vals;    /* scale values of indexed vectors after ops */
  const void* indices2;       /* index array pointer */
  const void* in_matrix2;     /* input matrix pointer */
  void* argop_off_vec_0;
  void* argop_off_vec_1;
} libxsmm_meltw_opreduce_vecs_idx_param;

/** argument struct for matrix-eltwise: unary */
LIBXSMM_EXTERN_C typedef struct LIBXSMM_RETARGETABLE libxsmm_meltw_unary_param {
  libxsmm_matrix_op_arg op;   /* op state & parameters */
  libxsmm_matrix_arg in;      /* input  */
  libxsmm_matrix_arg out;     /* output */
} libxsmm_meltw_unary_param;

/** argument struct for matrix-eltwise: binary */
LIBXSMM_EXTERN_C typedef struct LIBXSMM_RETARGETABLE libxsmm_meltw_binary_param {
  libxsmm_matrix_op_arg op;   /* op state & paramters */
  libxsmm_matrix_arg in0;     /* 1st input  */
  libxsmm_matrix_arg in1;     /* 2nd input  */
  libxsmm_matrix_arg out;     /* output     */
} libxsmm_meltw_binary_param;

/** argument struct for matrix-eltwise: ternary */
LIBXSMM_EXTERN_C typedef struct LIBXSMM_RETARGETABLE libxsmm_meltw_ternary_param {
  libxsmm_matrix_op_arg op;   /* op state & parameters */
  libxsmm_matrix_arg in0;     /* 1st input  */
  libxsmm_matrix_arg in1;     /* 2nd input  */
  libxsmm_matrix_arg in2;     /* 3rd input  */
  libxsmm_matrix_arg out;     /* output     */
} libxsmm_meltw_ternary_param;

/** argument struct for matrix equation */
LIBXSMM_EXTERN_C typedef struct LIBXSMM_RETARGETABLE libxsmm_matrix_eqn_param {
  const libxsmm_matrix_op_arg* ops_args;    /* op state & parameters */
  const libxsmm_matrix_arg*    inputs;      /* array of input args */
  libxsmm_matrix_arg           output;      /* output arg */
} libxsmm_matrix_eqn_param;

LIBXSMM_EXTERN_C typedef struct LIBXSMM_RETARGETABLE libxsmm_meltw_gemm_param {
  const void* bias_ptr;        /* optional, col-bias pointer */
  void* out_ptr;               /* optional, pointer to output after eltwise (contains mask in case of ReLU); */
                               /* Need for some activation functions, assumed to have the same shape as C matrix, */
                               /* may not be set when OVERWRITE_C option is chosen */
                               /* If OVERWRITE_C is false: out_ptr contains the post-act output, C has the pre-act output */
                               /* If OVERWRITE_C is true:  C contains post-act output, out_ptr contains the ReLU mask (only when act was ReLU) for other act unused */
  void* sparse_bitmap;
  void* decompress_buffer;
  void* relu_bitmask_bwd;
} libxsmm_meltw_gemm_param;

/** Specialized function for matrix-eltw (weak-typed). */
LIBXSMM_EXTERN_C typedef LIBXSMM_RETARGETABLE void (*libxsmm_meltwfunction_opreduce_vecs_idx)(const libxsmm_meltw_opreduce_vecs_idx_param* in_struct);
LIBXSMM_EXTERN_C typedef LIBXSMM_RETARGETABLE void (*libxsmm_meltwfunction_unary)(const libxsmm_meltw_unary_param* in_struct);
LIBXSMM_EXTERN_C typedef LIBXSMM_RETARGETABLE void (*libxsmm_meltwfunction_binary)(const libxsmm_meltw_binary_param* in_struct);
LIBXSMM_EXTERN_C typedef LIBXSMM_RETARGETABLE void (*libxsmm_meltwfunction_ternary)(const libxsmm_meltw_ternary_param* in_struct);

LIBXSMM_EXTERN_C typedef union LIBXSMM_RETARGETABLE libxsmm_xmeltwfunction {
  void (*xmeltw)(const void* in_struct);
  libxsmm_meltwfunction_opreduce_vecs_idx meltw_opreduce_vecs_idx;
  libxsmm_meltwfunction_unary meltw_unary;
  libxsmm_meltwfunction_binary meltw_binary;
  libxsmm_meltwfunction_ternary meltw_ternary;
} libxsmm_xmeltwfunction;

/** Specialized function with fused alpha and beta arguments, and optional prefetch locations (double-precision). */
LIBXSMM_EXTERN_C typedef LIBXSMM_RETARGETABLE void (*libxsmm_dmmfunction)(const double* a, const double* b, double* c, ...);
/** Specialized function with fused alpha and beta arguments, and optional prefetch locations (single-precision). */
LIBXSMM_EXTERN_C typedef LIBXSMM_RETARGETABLE void (*libxsmm_smmfunction)(const float* a, const float* b, float* c, ...);
/** Specialized function with fused alpha and beta arguments, and optional prefetch locations (bf16, fp32-accumulate). */
LIBXSMM_EXTERN_C typedef LIBXSMM_RETARGETABLE void (*libxsmm_bsmmfunction)(const libxsmm_bfloat16* a, const libxsmm_bfloat16* b, float* c, ...);
/** Specialized function with fused alpha and beta arguments, and optional prefetch locations (bf16, fp32-accumulate). */
LIBXSMM_EXTERN_C typedef LIBXSMM_RETARGETABLE void (*libxsmm_bmmfunction)(const libxsmm_bfloat16* a, const libxsmm_bfloat16* b, libxsmm_bfloat16* c, ...);
/** Specialized function with fused alpha and beta arguments, and optional prefetch locations (low-precision). */
LIBXSMM_EXTERN_C typedef LIBXSMM_RETARGETABLE void (*libxsmm_wimmfunction)(const short* a, const short* b, int* c, ...);
/** Specialized function with fused alpha and beta arguments, and optional prefetch locations (int8, int32 accumulate). */
LIBXSMM_EXTERN_C typedef LIBXSMM_RETARGETABLE void (*libxsmm_ssbimmfunction)(const          char* a, const          char* b, int* c, ...);
LIBXSMM_EXTERN_C typedef LIBXSMM_RETARGETABLE void (*libxsmm_usbimmfunction)(const unsigned char* a, const          char* b, int* c, ...);
LIBXSMM_EXTERN_C typedef LIBXSMM_RETARGETABLE void (*libxsmm_subimmfunction)(const          char* a, const unsigned char* b, int* c, ...);
LIBXSMM_EXTERN_C typedef LIBXSMM_RETARGETABLE void (*libxsmm_uubimmfunction)(const unsigned char* a, const unsigned char* b, int* c, ...);
/** Specialized function with fused alpha and beta arguments, and optional prefetch locations (int8, int32 accumulate, int8 downconvert). */
LIBXSMM_EXTERN_C typedef LIBXSMM_RETARGETABLE void (*libxsmm_sububmmfunction)(const          char* a, const unsigned char* b, unsigned char* c, float* scf, ...);

LIBXSMM_EXTERN_C typedef LIBXSMM_RETARGETABLE void (*libxsmm_dmmfunction_reducebatch_addr)(const double** a, const double** b, double* c, const unsigned long long* count, ...);
LIBXSMM_EXTERN_C typedef LIBXSMM_RETARGETABLE void (*libxsmm_smmfunction_reducebatch_addr)(const float** a, const float** b, float* c, const unsigned long long* count, ...);
LIBXSMM_EXTERN_C typedef LIBXSMM_RETARGETABLE void (*libxsmm_bsmmfunction_reducebatch_addr)(const libxsmm_bfloat16** a, const libxsmm_bfloat16** b, float* c, const unsigned long long* count, ...);
LIBXSMM_EXTERN_C typedef LIBXSMM_RETARGETABLE void (*libxsmm_bmmfunction_reducebatch_addr)(const libxsmm_bfloat16** a, const libxsmm_bfloat16** b, libxsmm_bfloat16* c, const unsigned long long* count, ...);
LIBXSMM_EXTERN_C typedef LIBXSMM_RETARGETABLE void (*libxsmm_wimmfunction_reducebatch_addr)(const short** a, const short** b, int* c, const unsigned long long* count, ...);
LIBXSMM_EXTERN_C typedef LIBXSMM_RETARGETABLE void (*libxsmm_ssbimmfunction_reducebatch_addr)(const          char** a, const          char** b, int* c, const unsigned long long* count, ...);
LIBXSMM_EXTERN_C typedef LIBXSMM_RETARGETABLE void (*libxsmm_usbimmfunction_reducebatch_addr)(const unsigned char** a, const          char** b, int* c, const unsigned long long* count, ...);
LIBXSMM_EXTERN_C typedef LIBXSMM_RETARGETABLE void (*libxsmm_subimmfunction_reducebatch_addr)(const          char** a, const unsigned char** b, int* c, const unsigned long long* count, ...);
LIBXSMM_EXTERN_C typedef LIBXSMM_RETARGETABLE void (*libxsmm_uubimmfunction_reducebatch_addr)(const unsigned char** a, const unsigned char** b, int* c, const unsigned long long* count, ...);
LIBXSMM_EXTERN_C typedef LIBXSMM_RETARGETABLE void (*libxsmm_sububmmfunction_reducebatch_addr)(const          char** a, const unsigned char** b, unsigned char* c, const unsigned long long* count, float* scf, ...);

LIBXSMM_EXTERN_C typedef LIBXSMM_RETARGETABLE void (*libxsmm_dmmfunction_reducebatch_offs)(const double* a, const double* b, double* c, const unsigned long long* count, const unsigned long long* a_offs, const unsigned long long* b_offs, ...);
LIBXSMM_EXTERN_C typedef LIBXSMM_RETARGETABLE void (*libxsmm_smmfunction_reducebatch_offs)(const float* a, const float* b, float* c, const unsigned long long* count, const unsigned long long* a_offs, const unsigned long long* b_offs, ...);
LIBXSMM_EXTERN_C typedef LIBXSMM_RETARGETABLE void (*libxsmm_bsmmfunction_reducebatch_offs)(const libxsmm_bfloat16* a, const libxsmm_bfloat16* b, float* c, const unsigned long long* count, const unsigned long long* a_offs, const unsigned long long* b_offs, ...);
LIBXSMM_EXTERN_C typedef LIBXSMM_RETARGETABLE void (*libxsmm_bmmfunction_reducebatch_offs)(const libxsmm_bfloat16* a, const libxsmm_bfloat16* b, libxsmm_bfloat16* c, const unsigned long long* count, const unsigned long long* a_offs, const unsigned long long* b_offs, ...);
LIBXSMM_EXTERN_C typedef LIBXSMM_RETARGETABLE void (*libxsmm_wimmfunction_reducebatch_offs)(const short* a, const short* b, int* c, const unsigned long long* count, const unsigned long long* a_offs, const unsigned long long* b_offs, ...);
LIBXSMM_EXTERN_C typedef LIBXSMM_RETARGETABLE void (*libxsmm_ssbimmfunction_reducebatch_offs)(const          char* a, const          char* b, int* c, const unsigned long long* count, const unsigned long long* a_offs, const unsigned long long* b_offs, ...);
LIBXSMM_EXTERN_C typedef LIBXSMM_RETARGETABLE void (*libxsmm_usbimmfunction_reducebatch_offs)(const unsigned char* a, const          char* b, int* c, const unsigned long long* count, const unsigned long long* a_offs, const unsigned long long* b_offs, ...);
LIBXSMM_EXTERN_C typedef LIBXSMM_RETARGETABLE void (*libxsmm_subimmfunction_reducebatch_offs)(const          char* a, const unsigned char* b, int* c, const unsigned long long* count, const unsigned long long* a_offs, const unsigned long long* b_offs, ...);
LIBXSMM_EXTERN_C typedef LIBXSMM_RETARGETABLE void (*libxsmm_uubimmfunction_reducebatch_offs)(const unsigned char* a, const unsigned char* b, int* c, const unsigned long long* count, const unsigned long long* a_offs, const unsigned long long* b_offs, ...);
LIBXSMM_EXTERN_C typedef LIBXSMM_RETARGETABLE void (*libxsmm_sububmmfunction_reducebatch_offs)(const          char* a, const unsigned char* b, unsigned char* c, const unsigned long long* count, const unsigned long long* a_offs, const unsigned long long* b_offs, float* scf, ...);

LIBXSMM_EXTERN_C typedef LIBXSMM_RETARGETABLE void (*libxsmm_dmmfunction_reducebatch_strd)(const double* a, const double* b, double* c, const unsigned long long* count, ...);
LIBXSMM_EXTERN_C typedef LIBXSMM_RETARGETABLE void (*libxsmm_smmfunction_reducebatch_strd)(const float* a, const float* b, float* c, const unsigned long long* count, ...);
LIBXSMM_EXTERN_C typedef LIBXSMM_RETARGETABLE void (*libxsmm_bsmmfunction_reducebatch_strd)(const libxsmm_bfloat16* a, const libxsmm_bfloat16* b, float* c, const unsigned long long* count, ...);
LIBXSMM_EXTERN_C typedef LIBXSMM_RETARGETABLE void (*libxsmm_bmmfunction_reducebatch_strd)(const libxsmm_bfloat16* a, const libxsmm_bfloat16* b, libxsmm_bfloat16* c, const unsigned long long* count, ...);
LIBXSMM_EXTERN_C typedef LIBXSMM_RETARGETABLE void (*libxsmm_wimmfunction_reducebatch_strd)(const short* a, const short* b, int* c, const unsigned long long* count, ...);
LIBXSMM_EXTERN_C typedef LIBXSMM_RETARGETABLE void (*libxsmm_ssbimmfunction_reducebatch_strd)(const          char* a, const          char* b, int* c, const unsigned long long* count, ...);
LIBXSMM_EXTERN_C typedef LIBXSMM_RETARGETABLE void (*libxsmm_usbimmfunction_reducebatch_strd)(const unsigned char* a, const          char* b, int* c, const unsigned long long* count, ...);
LIBXSMM_EXTERN_C typedef LIBXSMM_RETARGETABLE void (*libxsmm_subimmfunction_reducebatch_strd)(const          char* a, const unsigned char* b, int* c, const unsigned long long* count, ...);
LIBXSMM_EXTERN_C typedef LIBXSMM_RETARGETABLE void (*libxsmm_uubimmfunction_reducebatch_strd)(const unsigned char* a, const unsigned char* b, int* c, const unsigned long long* count, ...);
LIBXSMM_EXTERN_C typedef LIBXSMM_RETARGETABLE void (*libxsmm_sububmmfunction_reducebatch_strd)(const          char* a, const unsigned char* b, unsigned char* c, const unsigned long long* count, float* scf, ...);

/* GEMM fused with elwise */
LIBXSMM_EXTERN_C typedef LIBXSMM_RETARGETABLE void (*libxsmm_bmmfunction_reducebatch_offs_meltwfused)(const libxsmm_bfloat16* a, const libxsmm_bfloat16* b, libxsmm_bfloat16* c, const unsigned long long* count, const unsigned long long* a_offs, const unsigned long long* b_offs, const libxsmm_meltw_gemm_param* meltw_param, ...);

LIBXSMM_EXTERN_C typedef LIBXSMM_RETARGETABLE void (*libxsmm_bmmfunction_reducebatch_strd_meltwfused)(const libxsmm_bfloat16* a, const libxsmm_bfloat16* b, libxsmm_bfloat16* c, const unsigned long long* count, const libxsmm_meltw_gemm_param* meltw_param, ...);
LIBXSMM_EXTERN_C typedef LIBXSMM_RETARGETABLE void (*libxsmm_bsmmfunction_reducebatch_strd_meltwfused)(const libxsmm_bfloat16* a, const libxsmm_bfloat16* b, float* c, const unsigned long long* count, const libxsmm_meltw_gemm_param* meltw_param, ...);

/** Function type which is either libxsmm_smmfunction or libxsmm_dmmfunction (weak-typed). */
LIBXSMM_EXTERN_C typedef union LIBXSMM_RETARGETABLE libxsmm_xmmfunction {
  void (*xmm)(const void* a, const void* b, void* c, ...);
  void (*xbm)(const void** a, const void** b, void* c, const unsigned long long* count, ...);
  libxsmm_dmmfunction dmm; libxsmm_smmfunction smm; libxsmm_wimmfunction wimm; libxsmm_bsmmfunction bsmm; libxsmm_bmmfunction bmm;
  libxsmm_ssbimmfunction ssbimm; libxsmm_usbimmfunction usbimm; libxsmm_subimmfunction subimm; libxsmm_uubimmfunction uubimm; libxsmm_sububmmfunction sububmm;
  libxsmm_dmmfunction_reducebatch_addr dmra; libxsmm_smmfunction_reducebatch_addr smra; libxsmm_bsmmfunction_reducebatch_addr bsmra; libxsmm_bmmfunction_reducebatch_addr bmra;
  libxsmm_wimmfunction_reducebatch_addr wimra; libxsmm_ssbimmfunction_reducebatch_addr ssbimra; libxsmm_usbimmfunction_reducebatch_addr usbimra; libxsmm_subimmfunction_reducebatch_addr subimra; libxsmm_uubimmfunction_reducebatch_addr uubimra;
  libxsmm_sububmmfunction_reducebatch_addr sububmra;
  libxsmm_dmmfunction_reducebatch_offs dmro; libxsmm_smmfunction_reducebatch_offs smro; libxsmm_bsmmfunction_reducebatch_offs bsmro; libxsmm_bmmfunction_reducebatch_offs bmro;
  libxsmm_wimmfunction_reducebatch_offs wimro; libxsmm_ssbimmfunction_reducebatch_offs ssbimro; libxsmm_usbimmfunction_reducebatch_offs usbimro; libxsmm_subimmfunction_reducebatch_offs subimro; libxsmm_uubimmfunction_reducebatch_offs uubimro;
  libxsmm_sububmmfunction_reducebatch_offs sububmro;
  libxsmm_dmmfunction_reducebatch_strd dmrs; libxsmm_smmfunction_reducebatch_strd smrs; libxsmm_bsmmfunction_reducebatch_strd bsmrs; libxsmm_bmmfunction_reducebatch_strd bmrs;
  libxsmm_wimmfunction_reducebatch_strd wimrs; libxsmm_ssbimmfunction_reducebatch_strd ssbimrs; libxsmm_usbimmfunction_reducebatch_strd usbimrs; libxsmm_subimmfunction_reducebatch_strd subimrs; libxsmm_uubimmfunction_reducebatch_strd uubimrs;
  libxsmm_sububmmfunction_reducebatch_strd sububmrs;
  libxsmm_bmmfunction_reducebatch_strd_meltwfused bmrs_meltwfused;
  libxsmm_bmmfunction_reducebatch_offs_meltwfused bmro_meltwfused;
  libxsmm_bsmmfunction_reducebatch_strd_meltwfused bsmrs_meltwfused;
} libxsmm_xmmfunction;

/* matrix equation function */
LIBXSMM_EXTERN_C typedef LIBXSMM_RETARGETABLE void (*libxsmm_matrix_eqn_function)(const libxsmm_matrix_eqn_param* in_struct);

/** Structure to receive information about GEMM-kernels (libxsmm_get_mmkernel_info). */
LIBXSMM_EXTERN_C typedef struct LIBXSMM_RETARGETABLE libxsmm_mmkernel_info {
  /** Input/output data-type */
  libxsmm_gemm_precision iprecision, oprecision;
  /** Prefetch strategy. */
  libxsmm_gemm_prefetch_type prefetch;
  /** Leading dimensions. */
  unsigned int lda, ldb, ldc;
  /** Extents/shape. */
  unsigned int m, n, k;
  /** Set of flags. */
  int flags;
} libxsmm_mmkernel_info;

/** Structure to receive information about matrix-eltw kernels (libxsmm_get_meltwkernel_info). */
LIBXSMM_EXTERN_C typedef struct LIBXSMM_RETARGETABLE libxsmm_meltwkernel_info {
  /** LDx, M, and N. */
  unsigned int ldi, ldo, m, n;
  /** Size of data element. */
  unsigned int datatype;
  /** Set of flags. */
  unsigned int flags;
  /** Set of operation. */
  unsigned int operation;
} libxsmm_meltwkernel_info;

LIBXSMM_EXTERN_C typedef struct LIBXSMM_RETARGETABLE libxsmm_kernel_info {
  libxsmm_kernel_kind kind;
  /** Number of FLoating Point OperationS (FLOPS). */
  unsigned int nflops;
  /** Code size (Bytes). */
  size_t code_size;
} libxsmm_kernel_info;

/** Structure to receive information about the code registry status (libxsmm_get_registry_info). */
LIBXSMM_EXTERN_C typedef struct LIBXSMM_RETARGETABLE libxsmm_registry_info {
  size_t capacity, size, nbytes, nstatic, ncache;
} libxsmm_registry_info;

#endif /*LIBXSMM_TYPEDEFS_H*/

