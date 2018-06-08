	.text
	.hsa_code_object_version 2,1
	.hsa_code_object_isa 9,0,0,"AMD","AMDGPU"
	.weak	_ZZ4mainEN67HIP_kernel_functor_name_begin_unnamed_HIP_kernel_functor_name_end_319__cxxamp_trampolineEPDv4_fS1_S1_ ; -- Begin function _ZZ4mainEN67HIP_kernel_functor_name_begin_unnamed_HIP_kernel_functor_name_end_319__cxxamp_trampolineEPDv4_fS1_S1_
	.p2align	8
	.type	_ZZ4mainEN67HIP_kernel_functor_name_begin_unnamed_HIP_kernel_functor_name_end_319__cxxamp_trampolineEPDv4_fS1_S1_,@function
	.amdgpu_hsa_kernel _ZZ4mainEN67HIP_kernel_functor_name_begin_unnamed_HIP_kernel_functor_name_end_319__cxxamp_trampolineEPDv4_fS1_S1_
_ZZ4mainEN67HIP_kernel_functor_name_begin_unnamed_HIP_kernel_functor_name_end_319__cxxamp_trampolineEPDv4_fS1_S1_: ; @_ZZ4mainEN67HIP_kernel_functor_name_begin_unnamed_HIP_kernel_functor_name_end_319__cxxamp_trampolineEPDv4_fS1_S1_
.Lfunc_begin0:
	.amd_kernel_code_t
		amd_code_version_major = 1
		amd_code_version_minor = 1
		amd_machine_kind = 1
		amd_machine_version_major = 9
		amd_machine_version_minor = 0
		amd_machine_version_stepping = 0
		kernel_code_entry_byte_offset = 256
		kernel_code_prefetch_byte_size = 0
		max_scratch_backing_memory_byte_size = 0
		granulated_workitem_vgpr_count = 20
		granulated_wavefront_sgpr_count = 0
		priority = 0
		float_mode = 192
		priv = 0
		enable_dx10_clamp = 1
		debug_mode = 0
		enable_ieee_mode = 1
		enable_sgpr_private_segment_wave_byte_offset = 0
		user_sgpr_count = 6
		enable_trap_handler = 1
		enable_sgpr_workgroup_id_x = 1
		enable_sgpr_workgroup_id_y = 0
		enable_sgpr_workgroup_id_z = 0
		enable_sgpr_workgroup_info = 0
		enable_vgpr_workitem_id = 0
		enable_exception_msb = 0
		granulated_lds_size = 0
		enable_exception = 0
		enable_sgpr_private_segment_buffer = 1
		enable_sgpr_dispatch_ptr = 0
		enable_sgpr_queue_ptr = 0
		enable_sgpr_kernarg_segment_ptr = 1
		enable_sgpr_dispatch_id = 0
		enable_sgpr_flat_scratch_init = 0
		enable_sgpr_private_segment_size = 0
		enable_sgpr_grid_workgroup_count_x = 0
		enable_sgpr_grid_workgroup_count_y = 0
		enable_sgpr_grid_workgroup_count_z = 0
		enable_ordered_append_gds = 0
		private_element_size = 1
		is_ptr64 = 1
		is_dynamic_callstack = 0
		is_debug_enabled = 0
		is_xnack_enabled = 0
		workitem_private_segment_byte_size = 0
		workgroup_group_segment_byte_size = 8192
		gds_segment_byte_size = 0
		kernarg_segment_byte_size = 24
		workgroup_fbarrier_count = 0
		wavefront_sgpr_count = 8
		workitem_vgpr_count = 78
		reserved_vgpr_first = 0
		reserved_vgpr_count = 0
		reserved_sgpr_first = 0
		reserved_sgpr_count = 0
		debug_wavefront_private_segment_offset_sgpr = 0
		debug_private_segment_buffer_sgpr = 0
		kernarg_segment_alignment = 4
		group_segment_alignment = 4
		private_segment_alignment = 4
		wavefront_size = 6
		call_convention = -1
		runtime_loader_kernel_symbol = 0
	.end_amd_kernel_code_t
; BB#0:
	s_load_dwordx2 s[0:1], s[4:5], 0x0
	v_lshlrev_b32_e32 v7, 4, v0
	v_mov_b32_e32 v6, 0
	s_load_dwordx2 s[2:3], s[4:5], 0x8
	s_mov_b32 m0, -1
	s_waitcnt lgkmcnt(0)
	v_add_co_u32 v1, vcc, s0, v7
	v_mov_b32_e32 v2, s1
	v_addc_co_u32 v2, vcc, v2, v6, vcc
	flat_load_dwordx4 v[1:4], v[1:2]
	v_mov_b32_e32 v8, s3
	v_add_co_u32 v5, vcc, s2, v7
	v_addc_co_u32 v6, vcc, v8, v6, vcc
	v_add_co_u32 v8, vcc, 0x1000, v7
	s_load_dwordx2 s[4:5], s[4:5], 0x10
	s_waitcnt lgkmcnt(0)
	v_mov_b32_e32 v9, s5
	s_waitcnt vmcnt(0)
	ds_write2_b64 v8, v[1:2], v[3:4] offset1:1
	flat_load_dwordx4 v[1:4], v[5:6]
	v_and_b32_e32 v5, 0xf0, v0
	v_add_co_u32 v8, vcc, 0x1000, v5
	v_lshlrev_b32_e32 v6, 8, v0
	v_add_co_u32 v5, vcc, 0x1100, v5
	v_add_co_u32 v64, vcc, s4, v6
	v_addc_co_u32 v65, vcc, 0, v9, vcc
	s_waitcnt vmcnt(0) lgkmcnt(0)
	ds_write2_b64 v7, v[1:2], v[3:4] offset1:1

	flat_load_dwordx4 v[12:15], v[64:65]
	flat_load_dwordx4 v[16:19], v[64:65] offset:16
	flat_load_dwordx4 v[20:23], v[64:65] offset:32
	flat_load_dwordx4 v[24:27], v[64:65] offset:48

	flat_load_dwordx4 v[28:31], v[64:65] offset:64
	flat_load_dwordx4 v[32:35], v[64:65] offset:80
	flat_load_dwordx4 v[36:39], v[64:65] offset:96
	flat_load_dwordx4 v[40:43], v[64:65] offset:112

	flat_load_dwordx4 v[44:47], v[64:65] offset:128
    flat_load_dwordx4 v[48:51], v[64:65] offset:144
    flat_load_dwordx4 v[52:55], v[64:65] offset:160
    flat_load_dwordx4 v[56:59], v[64:65] offset:176

    flat_load_dwordx4 v[60:63], v[64:65] offset:192
    flat_load_dwordx4 v[66:69], v[64:65] offset:208
    flat_load_dwordx4 v[70:73], v[64:65] offset:224
    flat_load_dwordx4 v[74:77], v[64:65] offset:240

	v_and_b32_e32 v1, 1, v0
	v_bfe_u32 v0, v0, 1, 3
	v_lshlrev_b32_e32 v1, 4, v1
	v_or_b32_e32 v0, v1, v0
	v_lshlrev_b32_e32 v9, 4, v0
	ds_read2_b64 v[0:3], v8 offset1:1
	ds_read2_b64 v[8:11], v9 offset1:1
	ds_read2_b64 v[4:7], v5 offset1:1
	s_waitcnt lgkmcnt(0)
        s_waitcnt vmcnt(0)
;
	v_mac_f32 v44, v0, v8  quad_perm:[1,1,3,3]
	v_mac_f32 v45, v0, v9  quad_perm:[1,1,3,3]
	v_mac_f32 v46, v0, v10 quad_perm:[1,1,3,3]
	v_mac_f32 v47, v0, v11 quad_perm:[1,1,3,3]
;
	v_mac_f32 v48, v1, v8  quad_perm:[1,1,3,3]
	v_mac_f32 v49, v1, v9  quad_perm:[1,1,3,3]
	v_mac_f32 v50, v1, v10 quad_perm:[1,1,3,3]
	v_mac_f32 v51, v1, v11 quad_perm:[1,1,3,3]
;
	v_mac_f32 v52, v2, v8  quad_perm:[1,1,3,3]
	v_mac_f32 v53, v2, v9  quad_perm:[1,1,3,3]
	v_mac_f32 v54, v2, v10 quad_perm:[1,1,3,3]
	v_mac_f32 v55, v2, v11 quad_perm:[1,1,3,3]
;
	v_mac_f32 v56, v3, v8  quad_perm:[1,1,3,3]
	v_mac_f32 v57, v3, v9  quad_perm:[1,1,3,3]
	v_mac_f32 v58, v3, v10 quad_perm:[1,1,3,3]
	v_mac_f32 v59, v3, v11 quad_perm:[1,1,3,3]
;
	v_mac_f32 v60, v4, v8  quad_perm:[1,1,3,3]
	v_mac_f32 v61, v4, v9  quad_perm:[1,1,3,3]
	v_mac_f32 v62, v4, v10 quad_perm:[1,1,3,3]
	v_mac_f32 v63, v4, v11 quad_perm:[1,1,3,3]
;
	v_mac_f32 v66, v5, v8  quad_perm:[1,1,3,3]
	v_mac_f32 v67, v5, v9  quad_perm:[1,1,3,3]
	v_mac_f32 v68, v5, v10 quad_perm:[1,1,3,3]
	v_mac_f32 v69, v5, v11 quad_perm:[1,1,3,3]
;
	v_mac_f32 v70, v6, v8  quad_perm:[1,1,3,3]
	v_mac_f32 v71, v6, v9  quad_perm:[1,1,3,3]
	v_mac_f32 v72, v6, v10 quad_perm:[1,1,3,3]
	v_mac_f32 v73, v6, v11 quad_perm:[1,1,3,3]
;
	v_mac_f32 v74, v7, v8  quad_perm:[1,1,3,3]
	v_mac_f32 v75, v7, v9  quad_perm:[1,1,3,3]
	v_mac_f32 v76, v7, v10 quad_perm:[1,1,3,3]
	v_mac_f32 v77, v7, v11 quad_perm:[1,1,3,3]
;
	v_mac_f32 v12, v0, v8  quad_perm:[0,0,2,2]
	v_mac_f32 v13, v0, v9  quad_perm:[0,0,2,2]
	v_mac_f32 v14, v0, v10 quad_perm:[0,0,2,2]
	v_mac_f32 v15, v0, v11 quad_perm:[0,0,2,2]
;
	v_mac_f32 v16, v1, v8  quad_perm:[0,0,2,2]
	v_mac_f32 v17, v1, v9  quad_perm:[0,0,2,2]
	v_mac_f32 v18, v1, v10 quad_perm:[0,0,2,2]
	v_mac_f32 v19, v1, v11 quad_perm:[0,0,2,2]
;
	v_mac_f32 v20, v2, v8  quad_perm:[0,0,2,2]
	v_mac_f32 v21, v2, v9  quad_perm:[0,0,2,2]
	v_mac_f32 v22, v2, v10 quad_perm:[0,0,2,2]
	v_mac_f32 v23, v2, v11 quad_perm:[0,0,2,2]
;
	v_mac_f32 v24, v3, v8  quad_perm:[0,0,2,2]
	v_mac_f32 v25, v3, v9  quad_perm:[0,0,2,2]
	v_mac_f32 v26, v3, v10 quad_perm:[0,0,2,2]
	v_mac_f32 v27, v3, v11 quad_perm:[0,0,2,2]
;
	v_mac_f32 v28, v4, v8  quad_perm:[0,0,2,2]
	v_mac_f32 v29, v4, v9  quad_perm:[0,0,2,2]
	v_mac_f32 v30, v4, v10 quad_perm:[0,0,2,2]
	v_mac_f32 v31, v4, v11 quad_perm:[0,0,2,2]
;
	v_mac_f32 v32, v5, v8  quad_perm:[0,0,2,2]
	v_mac_f32 v33, v5, v9  quad_perm:[0,0,2,2]
	v_mac_f32 v34, v5, v10 quad_perm:[0,0,2,2]
	v_mac_f32 v35, v5, v11 quad_perm:[0,0,2,2]
;
	v_mac_f32 v36, v6, v8  quad_perm:[0,0,2,2]
	v_mac_f32 v37, v6, v9  quad_perm:[0,0,2,2]
	v_mac_f32 v38, v6, v10 quad_perm:[0,0,2,2]
	v_mac_f32 v39, v6, v11 quad_perm:[0,0,2,2]
;
	v_mac_f32 v40, v7, v8  quad_perm:[0,0,2,2]
	v_mac_f32 v41, v7, v9  quad_perm:[0,0,2,2]
	v_mac_f32 v42, v7, v10 quad_perm:[0,0,2,2]
	v_mac_f32 v43, v7, v11 quad_perm:[0,0,2,2]
;
	flat_store_dwordx4 v[64:65], v[12:15]
	flat_store_dwordx4 v[64:65], v[16:19] offset:16
	flat_store_dwordx4 v[64:65], v[20:23] offset:32
	flat_store_dwordx4 v[64:65], v[24:27] offset:48
	flat_store_dwordx4 v[64:65], v[28:31] offset:64
	flat_store_dwordx4 v[64:65], v[32:35] offset:80
	flat_store_dwordx4 v[64:65], v[36:39] offset:96
	flat_store_dwordx4 v[64:65], v[40:43] offset:112
	flat_store_dwordx4 v[64:65], v[44:47] offset:128
	flat_store_dwordx4 v[64:65], v[48:51] offset:144
	flat_store_dwordx4 v[64:65], v[52:55] offset:160
	flat_store_dwordx4 v[64:65], v[56:59] offset:176
	flat_store_dwordx4 v[64:65], v[60:63] offset:192
	flat_store_dwordx4 v[64:65], v[66:69] offset:208
	flat_store_dwordx4 v[64:65], v[70:73] offset:224
	flat_store_dwordx4 v[64:65], v[74:77] offset:240
	s_endpgm
.Lfunc_end0:
	.size	_ZZ4mainEN67HIP_kernel_functor_name_begin_unnamed_HIP_kernel_functor_name_end_319__cxxamp_trampolineEPDv4_fS1_S1_, .Lfunc_end0-_ZZ4mainEN67HIP_kernel_functor_name_begin_unnamed_HIP_kernel_functor_name_end_319__cxxamp_trampolineEPDv4_fS1_S1_

