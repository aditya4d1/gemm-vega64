    .hsa_code_object_version 2,1
    .hsa_code_object_isa 9,0,0,"AMD","AMDGPU"
    .p2align    8
    .type       hello_world,@function
    .amdgpu_hsa_kernel hello_world
hello_world:
.Lfunc_begin0:
    .amd_kernel_code_t
        enable_sgpr_kernarg_segment_ptr = 1
        float_mode = 192
        enable_ieee_mode = 1
        enable_trap_handler = 1
        is_ptr64 = 1
        compute_pgm_rsrc1_vgprs = 0
        compute_pgm_rsrc1_sgprs = 0
        compute_pgm_rsrc2_user_sgpr = 2
        ; size of your packed argument block
        kernarg_segment_byte_size = 24
        wavefront_sgpr_count = 10
        workitem_vgpr_count = 96
        enable_vgpr_workitem_id = 2
    .end_amd_kernel_code_t
; we launch 16*16 workitems
.set sArgs, 0
.set sA, 2
.set sB, 4
.set sC, 2
.set sldsA, 8
.set sldsB, 9

.set vtid, 0
.set vtidx, 1
.set vtidy, 2
.set vtida, 3
.set vtidc, 4
.set vldsWriteA, 5
.set vldsWriteB, 6
.set vldsReadA, 7 ; len = 2
.set vldsReadB, 9 ; len = 2
.set vgReadA, 11 ; v[vgReadA:vgReadA+1]
.set vgReadB, 13
.set vgWriteC, 15
.set va0, 16 ; va0:va0+3
.set va1, 20 ; va1:va1+3
.set vb0, 24 ; vb0:vb0+3
.set vb1, 28 ; vb1:vb1+3
.set vc, 32 ; vc:vc+63 = 32+63 = 95

; entry:
    s_load_dwordx2 s[sA:sA+1], s[sArgs:sArgs+1], 0x0
    s_load_dwordx2 s[sB:sB+1], s[sArgs:sArgs+1], 0x8
    s_load_dwordx2 s[sC:sC+1], s[sArgs:sArgs+1], 0x16

    ; calculate tx
; tx = tid % 16
; implemented as tid && 0xF
    v_and_b32 v[vtidx], v[vtid], 0xF
; calculate ty
; ty = tid / 16
; implemented as tid >> 4
    v_lshrrev_b32 v[vtidy], v[vtid], 4
; calculate tid for A
; as we load 4 dwords, which is 16 bytes for A and B,
; we multiply tid with 16 (= 1<<4)
    v_lshlrev_b32 v[vtida], v[vtid], 4
; wait for args to get loaded
    s_waitcnt lgkmcnt(0)
; populate each workitem vgprs with their own address of A, B and C
; for A
    v_mov_b32 v[vgReadA+1], s[sA+1]
    v_add_co_u32 v[vgReadA], vcc, s[sA], v[vtida]
    v_addc_co_u32 v[vgReadA+1], vcc, v[vgReadA+1], 0,  vcc
    global_load_dwordx4 v[va0:va0+3], v[vgReadA:vgReadA+1], off
; for B
    v_mov_b32 v[vgReadB+1], s[sB+1]
    v_add_co_u32 v[vgReadB], vcc, s[sB], v[vtida]
    v_addc_co_u32 v[vgReadB+1], vcc, v[vgReadB+1], 0, vcc
    global_load_dwordx4 v[vb0:vb0+3], v[vgReadB:vgReadB+1], off

    s_waitcnt vmcnt(0)

    s_endpgm
.Lfunc_end0:
    .size       hello_world, .Lfunc_end0-hello_world


