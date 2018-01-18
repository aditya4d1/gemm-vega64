#pragma once

#define OP_MATH_1(type, op) \
type operator op (const type &a, const type &b) { \
    type c; \
    c.x = a.x op b.x; \
    return c; \
}

#define OP_MATH_2(type, op) \
type operator op (const type &a, const type &b) { \
    type c; \
    c.x = a.x op b.x; \
    c.y = a.y op b.y; \
    return c; \
}

#define OP_MATH_3(type, op) \
type operator op (const type &a, const type &b) { \
    type c; \
    c.x = a.x op b.x; \
    c.y = a.y op b.y; \
    c.z = a.z op b.z; \
    return c; \
}

#define OP_MATH_4(type, op) \
type operator op (const type &a, const type &b) { \
    type c; \
    c.x = a.x op b.x; \
    c.y = a.y op b.y; \
    c.z = a.z op b.z; \
    c.w = a.w op b.w; \
    return c; \
}

#define OP_CMP_1(type, op) \
bool operator op (const type &a, const type &b) { \
    return a.x op b.x; \
}

#define OP_CMP_2(type, op) \
bool operator op (const type &a, const type &b) { \
    return (a.x op b.x) && (a.y op b.y); \
}

#define OP_CMP_3(type, op) \
bool operator op (const type &a, const type &b) { \
    return (a.x op b.x) && (a.y op b.y) && (a.z op b.z); \
}

#define OP_CMP_4(type, op) \
bool operator op (const type &a, const type &b) { \
    return (a.x op b.x) && (a.y op b.y) && (a.z op b.z) && (a.w op b.w); \
}

namespace stinger {

typedef struct {
    unsigned int x  : 24;
} uint24_t;

OP_MATH_1(uint24_t, +)
OP_MATH_1(uint24_t, -)
OP_MATH_1(uint24_t, *)
OP_CMP_1(uint24_t, ==)
OP_CMP_1(uint24_t, !=)

typedef struct {
    unsigned short x: 11;
} ushort11_t;

OP_MATH_1(ushort11_t, +)
OP_MATH_1(ushort11_t, -)
OP_MATH_1(ushort11_t, *)
OP_CMP_1(ushort11_t, ==)
OP_CMP_1(ushort11_t, !=)

typedef struct {
    unsigned short x: 10;
} ushort10_t;

OP_MATH_1(ushort10_t, +)
OP_MATH_1(ushort10_t, -)
OP_MATH_1(ushort10_t, *)
OP_CMP_1(ushort10_t, ==)
OP_CMP_1(ushort10_t, !=)

typedef struct {
    unsigned short x : 9;
} ushort9_t;

OP_MATH_1(ushort9_t, +)
OP_MATH_1(ushort9_t, -)
OP_MATH_1(ushort9_t, *)
OP_CMP_1(ushort9_t, ==)
OP_CMP_1(ushort9_t, !=)

typedef struct {
    unsigned short x : 6;
} ushort6_t;

OP_MATH_1(ushort6_t, +)
OP_MATH_1(ushort6_t, -)
OP_MATH_1(ushort6_t, *)
OP_CMP_1(ushort6_t, ==)
OP_CMP_1(ushort6_t, !=)

typedef struct {
    unsigned short x : 5;
} ushort5_t;

OP_MATH_1(ushort5_t, +)
OP_CMP_1(ushort5_t, ==)
OP_CMP_1(ushort5_t, !=)

typedef struct {
    unsigned short x : 4;
} ushort4_t;

OP_MATH_1(ushort4_t, +)
OP_CMP_1(ushort4_t, ==)
OP_CMP_1(ushort4_t, !=)

typedef struct {
    unsigned short x : 2;
} ushort2_t;

OP_MATH_1(ushort2_t, +)
OP_CMP_1(ushort2_t, ==)
OP_CMP_1(ushort2_t, !=)

typedef struct {
    unsigned short x : 1;
} ushort1_t;

OP_MATH_1(ushort1_t, +)
OP_CMP_1(ushort1_t, ==)
OP_CMP_1(ushort1_t, !=)

typedef struct {
    unsigned int x : 10, y : 11, z : 11;
} uint10_11_11_t;

OP_MATH_3(uint10_11_11_t, +)
OP_CMP_3(uint10_11_11_t, ==)
OP_CMP_3(uint10_11_11_t, !=)

typedef struct {
    unsigned int x : 11, y : 11, z : 10;
} uint11_11_10_t;

OP_MATH_3(uint11_11_10_t, +)
OP_CMP_3(uint11_11_10_t, ==)
OP_CMP_3(uint11_11_10_t, !=)

typedef struct {
    unsigned int x : 10, y : 10, z : 10, w : 2;
} uint10_10_10_2_t;

OP_MATH_4(uint10_10_10_2_t, +)
OP_CMP_4(uint10_10_10_2_t, ==)
OP_CMP_4(uint10_10_10_2_t, !=)

typedef struct {
    unsigned int x : 2, y : 10, z : 10, w : 10;
} uint2_10_10_10_t;

OP_MATH_4(uint2_10_10_10_t, +)
OP_CMP_4(uint2_10_10_10_t, ==)
OP_CMP_4(uint2_10_10_10_t, !=)

typedef struct {
    unsigned short x : 5, y : 6, z : 5;
} ushort5_6_5_t;

OP_MATH_3(ushort5_6_5_t, +)
OP_CMP_3(ushort5_6_5_t, ==)
OP_CMP_3(ushort5_6_5_t, !=)

typedef struct {
    unsigned short x : 1, y : 5, z : 5, w : 5;
} ushort1_5_5_5_t;

OP_MATH_4(ushort1_5_5_5_t, +)
OP_CMP_4(ushort1_5_5_5_t, ==)
OP_CMP_4(ushort1_5_5_5_t, !=)

typedef struct {
    unsigned short x : 5, y : 5, z : 5, w : 1;
} ushort5_5_5_1_t;

OP_MATH_4(ushort5_5_5_1_t, +)
OP_CMP_4(ushort5_5_5_1_t, ==)
OP_CMP_4(ushort5_5_5_1_t, !=)

typedef struct {
    unsigned short x : 4, y : 4, z : 4, w : 4;
} ushort4_4_4_4_t;

OP_MATH_4(ushort4_4_4_4_t, +)
OP_CMP_4(ushort4_4_4_4_t, ==)
OP_CMP_4(ushort4_4_4_4_t, !=)

typedef struct {
    unsigned int x : 8, y : 24;
} uint8_24_t;

OP_MATH_2(uint8_24_t, +)
OP_CMP_2(uint8_24_t, ==)
OP_CMP_2(uint8_24_t, !=)

typedef struct {
    unsigned int x : 24, y : 8;
} uint24_8_t;

OP_MATH_2(uint24_8_t, +)
OP_CMP_2(uint24_8_t, ==)
OP_CMP_2(uint24_8_t, !=)

typedef struct {
    unsigned int x : 5, y : 9, z : 9, w : 9;
} uint5_9_9_9_t;

OP_MATH_4(uint5_9_9_9_t, +)
OP_CMP_4(uint5_9_9_9_t, ==)
OP_CMP_4(uint5_9_9_9_t, !=)

} // end namespace stinger
