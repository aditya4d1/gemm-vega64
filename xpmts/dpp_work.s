    .text
    .hsa_code_object_version 2,1
    .hsa_code_object_isa 9,0,0,"AMD","AMDGPU"
    .weak       hello_world                ; -- Begin function hello_world
    .p2align    8
    .type       hello_world,@function
    .amdgpu_hsa_kernel hello_world
hello_world:                               ; @hello_world
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
                kernarg_segment_byte_size = 24
              wavefront_sgpr_count = 5
              workitem_vgpr_count = 3
                enable_vgpr_workitem_id = 2
                enable_sgpr_workgroup_id_x = 1
                enable_sgpr_workgroup_id_y = 0
                enable_sgpr_workgroup_id_z = 0
    .end_amd_kernel_code_t
; %bb.0:
    ; block_height = 128
    ; block_width = 128
    ; block_widthx4 = 32
    ; matrix_width = 32
    s_load_dwordx2 s[0:1], s[0:1], 0x10
    ; (bid % matrix_width) * 32
    s_and_b32 s3, s2, 31
    s_lshl_b32 s3, s3, 5
    ; (bid / matrix_width) * block_widthx4 * matrix_width * block_height
    ; (bid / 32) * 32 * 32 * 128
    s_lshr_b32 s4, s2, 5
    s_lshl_b32 s4, s4, 17
    ; block_widthx4 * matrix_width
    s_mov_b32 s5, 1024
    ; block_widthx4 * matrix_width * 16 * 4
    s_mov_b32 s6, 65536
    ; (bid % matrix) * 32 + (bid / matrix_width) * block_widthx4 * matrix_width * block_height
    s_add_u32 s7, s3, s4
    ; s7 + block_widthx4 * matrix_width
    s_add_u32 s8, s7, s6
    ; (tid % 16)
    ; = tid & 15
    v_and_b32 v3, v0, 0xF
    ; (tid / 16) * block_widthx4 * matrix_width * 4
    ; = (tid >> 4) * 32 * 32 * 4
    ; = (tid >> 4) << 12
    v_lshrrev_b32 v4, v0, 4
    v_lshlrev_b32 v4, v4, 12
    ; (tid % 16) + (tid / 16) * block_widthx4 * matrix_width * 4
    v_add_u32 v5, v3, v4
    ; v5 + (bid % matrix) * 32 + (bid / matrix_width) * block_widthx4 * matrix_width * block_height
    v_add_u32 v6, v5, s7
    ; v7 = v6 * (sizeof(float4))
    ; = v6 << 4
    v_lshlrev_b32 v7, v6, 4
    ; wait for args load
    s_waitcnt lgkmcnt(0)
    v_mov_b32 v2, s1
    v_add_co_u32 v1, vcc, s0, v7
    v_addc_co_u32 v2, vcc, v2, 0, vcc
    global_load_dwordx4 v[8:11], v[1:2], off
    global_load_dwordx4 v[12:15], v[1:2], off offset:16*4*4
    s_waitcnt vmcnt(0)
    v_add_f32 v8, v8, 1.0
    v_add_f32 v9, v9, 1.0
    v_add_f32 v10, v10, 1.0
    v_add_f32 v11, v11, 1.0
    v_add_f32 v12, v12, 1.0
    v_add_f32 v13, v13, 1.0
    v_add_f32 v14, v14, 1.0
    v_add_f32 v15, v15, 1.0
    global_store_dwordx4 v[1:2], v[8:11], off
    global_store_dwordx4 v[1:2], v[12:15], off offset:16*4*4
    s_endpgm
.Lfunc_end0:
    .size       hello_world, .Lfunc_end0-hello_world

; s[0:1] - C
; s2 - bid
; s3 - (bid % matrix_width) * 32
; s4 - (bid / matrix_width) * block_widthx4 * matrix_width * block_height
; s5 - block_widthx4 * matrix_width
; s6 - block_widthx4 * matrix_width * 16 * 4 = 1024 * 64 = 65536
; s7 = s3 + s4
; v0 - tid
; v[1:2] - C + ......
; v3 - tid % 16
; v4 - (tid / 16) * block_widthx4 * matrix_width * 4
; v5 - tid % 16 + (tid / 16) * block_widthx4 * matrix_width * 4
; v6 = v5 + s7

;; TODO: Later, move all thread id ops to end of c[16]
