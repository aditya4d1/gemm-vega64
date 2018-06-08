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

; tid for C is a bit different.
; Each workitem stores 64 floats or 16 float4s continuously
; so, tidc = tid * 16 for float4s
; byte addressing tidc is, tid * 16 * 16 (1<<8) [which comes down to 256 bytes = 64 floats]
    v_lshlrev_b32 v[vtidc], v[vtid], 8

; wait for args to get loaded
    s_waitcnt lgkmcnt(0)

; for C
    v_mov_b32 v[vgWriteC+1], s[sC+1]
    v_add_co_u32 v[vgWriteC], vcc, s[sC], v[vtidc]
    v_addc_co_u32 v[vgWriteC+1], vcc, v[vgWriteC+1], 0, vcc
    global_load_dwordx4 v[vc+0*4+0:vc+0*4+3], v[vgWriteC:vgWriteC+1], off offset:0*64+0
    global_load_dwordx4 v[vc+1*4+0:vc+1*4+3], v[vgWriteC:vgWriteC+1], off offset:0*64+16
    global_load_dwordx4 v[vc+2*4+0:vc+2*4+3], v[vgWriteC:vgWriteC+1], off offset:0*64+32
    global_load_dwordx4 v[vc+3*4+0:vc+3*4+3], v[vgWriteC:vgWriteC+1], off offset:0*64+48
    ;
    global_load_dwordx4 v[vc+4*4+0:vc+4*4+3], v[vgWriteC:vgWriteC+1], off offset:1*64+0
    global_load_dwordx4 v[vc+5*4+0:vc+5*4+3], v[vgWriteC:vgWriteC+1], off offset:1*64+16
    global_load_dwordx4 v[vc+6*4+0:vc+6*4+3], v[vgWriteC:vgWriteC+1], off offset:1*64+32
    global_load_dwordx4 v[vc+7*4+0:vc+7*4+3], v[vgWriteC:vgWriteC+1], off offset:1*64+48
    ;
    global_load_dwordx4 v[vc+8*4+0:vc+8*4+3], v[vgWriteC:vgWriteC+1], off offset:2*64+0
    global_load_dwordx4 v[vc+9*4+0:vc+9*4+3], v[vgWriteC:vgWriteC+1], off offset:2*64+16
    global_load_dwordx4 v[vc+10*4+0:vc+10*4+3], v[vgWriteC:vgWriteC+1], off offset:2*64+32
    global_load_dwordx4 v[vc+11*4+0:vc+11*4+3], v[vgWriteC:vgWriteC+1], off offset:2*64+48
    ;
    global_load_dwordx4 v[vc+12*4+0:vc+12*4+3], v[vgWriteC:vgWriteC+1], off offset:3*64+0
    global_load_dwordx4 v[vc+13*4+0:vc+13*4+3], v[vgWriteC:vgWriteC+1], off offset:3*64+16
    global_load_dwordx4 v[vc+14*4+0:vc+14*4+3], v[vgWriteC:vgWriteC+1], off offset:3*64+32
    global_load_dwordx4 v[vc+15*4+0:vc+15*4+3], v[vgWriteC:vgWriteC+1], off offset:3*64+48
    ;


    s_waitcnt vmcnt(0)

    s_endpgm
.Lfunc_end0:
    .size       hello_world, .Lfunc_end0-hello_world


