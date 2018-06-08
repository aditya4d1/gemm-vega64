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
        enable_sgpr_workgroup_id_x = 1
        enable_sgpr_workgroup_id_y = 0
        enable_sgpr_workgroup_id_z = 0
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
    s_waitcnt lgkmcnt(0)

    s_endpgm
.Lfunc_end0:
    .size       hello_world, .Lfunc_end0-hello_world


