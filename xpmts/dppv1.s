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
		granulated_workitem_vgpr_count = 19
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
		workitem_vgpr_count = 79
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
	v_lshlrev_b32_e32 v13, 4, v0
	v_mov_b32_e32 v6, 0
	s_load_dwordx2 s[2:3], s[4:5], 0x8
	s_mov_b32 m0, -1
	s_waitcnt lgkmcnt(0)
	v_add_co_u32 v1, vcc, s0, v13
	v_mov_b32_e32 v2, s1
	v_addc_co_u32 v2, vcc, v2, v6, vcc
	flat_load_dwordx4 v[1:4], v[1:2]
	v_mov_b32_e32 v7, s3
	v_add_co_u32 v5, vcc, s2, v13
	v_addc_co_u32 v6, vcc, v7, v6, vcc
	v_add_co_u32 v7, vcc, 0x1000, v13
	s_load_dwordx2 s[4:5], s[4:5], 0x10
	s_waitcnt vmcnt(0) lgkmcnt(0)
	ds_write2_b64 v7, v[1:2], v[3:4] offset1:1
	flat_load_dwordx4 v[1:4], v[5:6]
	v_and_b32_e32 v5, 0xf0, v0
	v_add_co_u32 v9, vcc, 0x1100, v5
	v_lshlrev_b32_e32 v6, 8, v0
	v_add_co_u32 v7, vcc, 0x1000, v5
	v_mov_b32_e32 v5, s5
	v_add_co_u32 v77, vcc, s4, v6
	v_addc_co_u32 v78, vcc, 0, v5, vcc
	v_and_b32_e32 v0, 15, v0
	v_lshlrev_b32_e32 v14, 4, v0
	ds_read2_b64 v[5:8], v7 offset1:1
	ds_read2_b64 v[9:12], v9 offset1:1
	s_waitcnt vmcnt(0) lgkmcnt(2)
	ds_write2_b64 v13, v[1:2], v[3:4] offset1:1
	flat_load_dwordx4 v[17:20], v[77:78]
	flat_load_dwordx4 v[21:24], v[77:78] offset:16
	flat_load_dwordx4 v[25:28], v[77:78] offset:32
	flat_load_dwordx4 v[29:32], v[77:78] offset:48
	flat_load_dwordx4 v[33:36], v[77:78] offset:64
	flat_load_dwordx4 v[37:40], v[77:78] offset:80
	flat_load_dwordx4 v[41:44], v[77:78] offset:96
	flat_load_dwordx4 v[45:48], v[77:78] offset:112
	ds_read2_b64 v[0:3], v14 offset1:1
	flat_load_dwordx4 v[49:52], v[77:78] offset:128
	flat_load_dwordx4 v[53:56], v[77:78] offset:144
	flat_load_dwordx4 v[57:60], v[77:78] offset:160
	flat_load_dwordx4 v[61:64], v[77:78] offset:176
	flat_load_dwordx4 v[65:68], v[77:78] offset:192
	flat_load_dwordx4 v[69:72], v[77:78] offset:208
	flat_load_dwordx4 v[73:76], v[77:78] offset:224
	ds_read2_b64 v[13:16], v14 offset0:32 offset1:33
	s_waitcnt vmcnt(0) lgkmcnt(8)
;
	v_mac_f32 v17, v5, v0 quad_perm:[0,1,2,3]
	v_mac_f32 v18, v5, v1 quad_perm:[0,1,2,3]
	v_mac_f32 v19, v5, v2 quad_perm:[0,1,2,3]
	v_mac_f32 v20, v5, v3 quad_perm:[0,1,2,3]
;
	v_mac_f32 v21, v6, v0 quad_perm:[0,1,2,3]
	v_mac_f32 v22, v6, v1 quad_perm:[0,1,2,3]
	v_mac_f32 v23, v6, v2 quad_perm:[0,1,2,3]
	v_mac_f32 v24, v6, v3 quad_perm:[0,1,2,3]
;
	v_mac_f32 v25, v7, v0 quad_perm:[0,1,2,3]
	v_mac_f32 v26, v7, v1 quad_perm:[0,1,2,3]
	v_mac_f32 v27, v7, v2 quad_perm:[0,1,2,3]
	v_mac_f32 v28, v7, v3 quad_perm:[0,1,2,3]
;
	v_mac_f32 v29, v8, v0 quad_perm:[0,1,2,3]
	v_mac_f32 v30, v8, v1 quad_perm:[0,1,2,3]
	v_mac_f32 v31, v8, v2 quad_perm:[0,1,2,3]
	v_mac_f32 v32, v8, v3 quad_perm:[0,1,2,3]
;
	v_mac_f32 v33, v9, v0 quad_perm:[0,1,2,3]
	v_mac_f32 v34, v9, v1 quad_perm:[0,1,2,3]
	v_mac_f32 v35, v9, v2 quad_perm:[0,1,2,3]
	v_mac_f32 v36, v9, v3 quad_perm:[0,1,2,3]
;
	v_mac_f32 v37, v10, v0 quad_perm:[0,1,2,3]
	v_mac_f32 v38, v10, v1 quad_perm:[0,1,2,3]
	v_mac_f32 v39, v10, v2 quad_perm:[0,1,2,3]
	v_mac_f32 v40, v10, v3 quad_perm:[0,1,2,3]
;
	v_mac_f32 v41, v11, v0 quad_perm:[0,1,2,3]
	v_mac_f32 v42, v11, v1 quad_perm:[0,1,2,3]
	v_mac_f32 v43, v11, v2 quad_perm:[0,1,2,3]
	v_mac_f32 v44, v11, v3 quad_perm:[0,1,2,3]
;
	v_mac_f32 v45, v12, v0 quad_perm:[0,1,2,3]
	v_mac_f32 v46, v12, v1 quad_perm:[0,1,2,3]
	v_mac_f32 v47, v12, v2 quad_perm:[0,1,2,3]
	v_mac_f32 v48, v12, v3 quad_perm:[0,1,2,3]
;
	flat_load_dwordx4 v[0:3], v[77:78] offset:240
	s_waitcnt lgkmcnt(1)
	v_mac_f32 v49, v5, v13 quad_perm:[0,1,2,3]
	v_mac_f32 v50, v5, v14 quad_perm:[0,1,2,3]
	v_mac_f32 v51, v5, v15 quad_perm:[0,1,2,3]
	v_mac_f32 v52, v5, v16 quad_perm:[0,1,2,3]
;
	v_mac_f32 v53, v6, v13 quad_perm:[0,1,2,3]
	v_mac_f32 v54, v6, v14 quad_perm:[0,1,2,3]
	v_mac_f32 v55, v6, v15 quad_perm:[0,1,2,3]
	v_mac_f32 v56, v6, v16 quad_perm:[0,1,2,3]
;
	v_mac_f32 v57, v7, v13 quad_perm:[0,1,2,3]
	v_mac_f32 v58, v7, v14 quad_perm:[0,1,2,3]
	v_mac_f32 v59, v7, v15 quad_perm:[0,1,2,3]
	v_mac_f32 v60, v7, v16 quad_perm:[0,1,2,3]
;
	v_mac_f32 v61, v8, v13 quad_perm:[0,1,2,3]
	v_mac_f32 v62, v8, v14 quad_perm:[0,1,2,3]
	v_mac_f32 v63, v8, v15 quad_perm:[0,1,2,3]
	v_mac_f32 v64, v8, v16 quad_perm:[0,1,2,3]
;
	v_mac_f32 v65, v9, v13 quad_perm:[0,1,2,3]
	v_mac_f32 v66, v9, v14 quad_perm:[0,1,2,3]
	v_mac_f32 v67, v9, v15 quad_perm:[0,1,2,3]
	v_mac_f32 v68, v9, v16 quad_perm:[0,1,2,3]
;
	v_mac_f32 v69, v10, v13 quad_perm:[0,1,2,3]
	v_mac_f32 v70, v10, v14 quad_perm:[0,1,2,3]
	v_mac_f32 v71, v10, v15 quad_perm:[0,1,2,3]
	v_mac_f32 v72, v10, v16 quad_perm:[0,1,2,3]
;
	v_mac_f32 v73, v11, v13 quad_perm:[0,1,2,3]
	v_mac_f32 v74, v11, v14 quad_perm:[0,1,2,3]
	v_mac_f32 v75, v11, v15 quad_perm:[0,1,2,3]
	v_mac_f32 v76, v11, v16 quad_perm:[0,1,2,3]
;
	flat_store_dwordx4 v[77:78], v[17:20]
	flat_store_dwordx4 v[77:78], v[21:24] offset:16
	flat_store_dwordx4 v[77:78], v[25:28] offset:32
	flat_store_dwordx4 v[77:78], v[29:32] offset:48
	flat_store_dwordx4 v[77:78], v[33:36] offset:64
	flat_store_dwordx4 v[77:78], v[37:40] offset:80
	flat_store_dwordx4 v[77:78], v[41:44] offset:96
	flat_store_dwordx4 v[77:78], v[45:48] offset:112
	flat_store_dwordx4 v[77:78], v[49:52] offset:128
	flat_store_dwordx4 v[77:78], v[53:56] offset:144
	flat_store_dwordx4 v[77:78], v[57:60] offset:160
	flat_store_dwordx4 v[77:78], v[61:64] offset:176
	flat_store_dwordx4 v[77:78], v[65:68] offset:192
	flat_store_dwordx4 v[77:78], v[69:72] offset:208
	flat_store_dwordx4 v[77:78], v[73:76] offset:224
	s_waitcnt vmcnt(0)
	v_mac_f32 v0, v12, v13 quad_perm:[0,1,2,3]
	v_mac_f32 v1, v12, v14 quad_perm:[0,1,2,3]
	v_mac_f32 v2, v12, v15 quad_perm:[0,1,2,3]
	v_mac_f32 v3, v12, v16 quad_perm:[0,1,2,3]
	flat_store_dwordx4 v[77:78], v[0:3] offset:240
	s_endpgm
.Lfunc_end0:
	.size	_ZZ4mainEN67HIP_kernel_functor_name_begin_unnamed_HIP_kernel_functor_name_end_319__cxxamp_trampolineEPDv4_fS1_S1_, .Lfunc_end0-_ZZ4mainEN67HIP_kernel_functor_name_begin_unnamed_HIP_kernel_functor_name_end_319__cxxamp_trampolineEPDv4_fS1_S1_

