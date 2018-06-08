	.text
	.hsa_code_object_version 2,1
	.hsa_code_object_isa 9,0,0,"AMD","AMDGPU"
	.weak	_ZZ4mainEN67HIP_kernel_functor_name_begin_unnamed_HIP_kernel_functor_name_end_519__cxxamp_trampolineEPDv4_fS1_S1_PiS2_ ; -- Begin function _ZZ4mainEN67HIP_kernel_functor_name_begin_unnamed_HIP_kernel_functor_name_end_519__cxxamp_trampolineEPDv4_fS1_S1_PiS2_
	.p2align	8
	.type	_ZZ4mainEN67HIP_kernel_functor_name_begin_unnamed_HIP_kernel_functor_name_end_519__cxxamp_trampolineEPDv4_fS1_S1_PiS2_,@function
	.amdgpu_hsa_kernel _ZZ4mainEN67HIP_kernel_functor_name_begin_unnamed_HIP_kernel_functor_name_end_519__cxxamp_trampolineEPDv4_fS1_S1_PiS2_
_ZZ4mainEN67HIP_kernel_functor_name_begin_unnamed_HIP_kernel_functor_name_end_519__cxxamp_trampolineEPDv4_fS1_S1_PiS2_: ; @_ZZ4mainEN67HIP_kernel_functor_name_begin_unnamed_HIP_kernel_functor_name_end_519__cxxamp_trampolineEPDv4_fS1_S1_PiS2_
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
		granulated_workitem_vgpr_count = 30
		granulated_wavefront_sgpr_count = 2
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
		workgroup_group_segment_byte_size = 0
		gds_segment_byte_size = 0
		kernarg_segment_byte_size = 40
		workgroup_fbarrier_count = 0
		wavefront_sgpr_count = 17
		workitem_vgpr_count = 121
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
	s_load_dwordx2 s[2:3], s[4:5], 0x0
	s_load_dwordx2 s[8:9], s[4:5], 0x8
	s_load_dwordx2 s[0:1], s[4:5], 0x10
	s_ashr_i32 s4, s6, 31
	s_lshr_b32 s4, s4, 27
	s_add_i32 s4, s6, s4
	v_lshrrev_b32_e32 v3, 4, v0
	s_and_b32 s11, s4, 0xffffffe0
	v_and_b32_e32 v2, 15, v0
	v_lshlrev_b32_e32 v1, 12, v3
	s_sub_i32 s5, s6, s11
	s_ashr_i32 s4, s4, 5
	s_lshl_b32 s10, s5, 5
	v_or_b32_e32 v1, v1, v2
	s_lshl_b32 s6, s4, 17
	v_add_i32_e32 v1, vcc, s10, v1
	v_add_i32_e32 v1, vcc, s6, v1
	v_lshlrev_b32_e32 v75, 4, v2
	v_ashrrev_i32_e32 v2, 31, v1
	v_lshlrev_b64 v[40:41], 4, v[1:2]
	v_lshrrev_b32_e32 v4, 5, v0
	s_lshl_b32 s4, s4, 9
	s_lshl_b32 s5, s5, 9
	v_and_b32_e32 v73, 31, v0
	v_lshlrev_b32_e32 v76, 4, v0
	s_waitcnt lgkmcnt(0)
	v_add_i32_e32 v0, vcc, s0, v40
	v_mov_b32_e32 v1, s1
	v_lshlrev_b32_e32 v77, 10, v4
	v_mov_b32_e32 v9, s4
	v_mov_b32_e32 v10, s5
	v_lshlrev_b32_e32 v4, 14, v4
	v_mov_b32_e32 v5, s2
	v_mov_b32_e32 v6, s3
	v_mov_b32_e32 v7, s8
	v_mov_b32_e32 v8, s9
	v_addc_u32_e32 v1, vcc, v1, v41, vcc
	s_movk_i32 s12, 0x4000
	;;#ASMSTART
	
	v_readfirstlane_b32 s0, v5
	v_readfirstlane_b32 s1, v6
	s_mov_b32 s2, 0x8000000
	s_mov_b32 s3, 0x0020000
	v_readfirstlane_b32 s4, v7
	v_readfirstlane_b32 s5, v8
	s_mov_b32 s6, 0x8000000
	s_mov_b32 s7, 0x0020000
	v_readfirstlane_b32 s8, v9
	v_readfirstlane_b32 s9, v10
	;s_mov_b32 s8, 0x0
	;s_mov_b32 s9, 0x0
	tbuffer_load_format_xyzw v[79:82], v4, s[0:3], dfmt:14, nfmt:5, s8 offen 
	tbuffer_load_format_xyzw v[83:86], v4, s[4:7], dfmt:15, nfmt:5, s9 offen 
	
	;;#ASMEND
	v_add_i32_e32 v10, vcc, s12, v0
	v_mov_b32_e32 v78, 0
	v_addc_u32_e32 v11, vcc, v1, v78, vcc
	s_mov_b32 s13, 0x8000
	v_add_i32_e32 v20, vcc, s13, v0
	v_addc_u32_e32 v21, vcc, v1, v78, vcc
	s_mov_b32 s14, 0xc000
	v_add_i32_e32 v30, vcc, s14, v0
	s_add_u32 s6, s0, 0x100000
	v_addc_u32_e32 v31, vcc, v1, v78, vcc
	s_addc_u32 s7, s1, 0
	v_add_i32_e32 v64, vcc, s6, v40
	v_mov_b32_e32 v40, s7
	v_addc_u32_e32 v65, vcc, v40, v41, vcc
	v_add_i32_e32 v44, vcc, s12, v64
	v_addc_u32_e32 v45, vcc, v65, v78, vcc
	v_add_i32_e32 v48, vcc, s13, v64
	v_addc_u32_e32 v49, vcc, v65, v78, vcc
	s_movk_i32 s4, 0x1000
	v_lshlrev_b32_e32 v74, 4, v3
	;;#ASMSTART
	
     global_load_dwordx4 v[6:9], v[0:1], off 
     
	;;#ASMEND
	;;#ASMSTART
	
     global_load_dwordx4 v[2:5], v[0:1], off offset:16*4*4 
     
	;;#ASMEND
	;;#ASMSTART
	
     global_load_dwordx4 v[16:19], v[10:11], off 
     
	;;#ASMEND
	;;#ASMSTART
	
     global_load_dwordx4 v[12:15], v[10:11], off offset:16*4*4 
     
	;;#ASMEND
	;;#ASMSTART
	
     global_load_dwordx4 v[26:29], v[20:21], off 
     
	;;#ASMEND
	;;#ASMSTART
	
     global_load_dwordx4 v[22:25], v[20:21], off offset:16*4*4 
     
	;;#ASMEND
	;;#ASMSTART
	
     global_load_dwordx4 v[36:39], v[30:31], off 
     
	;;#ASMEND
	;;#ASMSTART
	
     global_load_dwordx4 v[32:35], v[30:31], off offset:16*4*4 
     
	;;#ASMEND
	;;#ASMSTART
	
     global_load_dwordx4 v[52:55], v[64:65], off 
     
	;;#ASMEND
	;;#ASMSTART
	
     global_load_dwordx4 v[40:43], v[64:65], off offset:16*4*4 
     
	;;#ASMEND
	v_add_i32_e32 v64, vcc, s14, v64
	v_or_b32_e32 v73, v73, v77
	v_addc_u32_e32 v65, vcc, v65, v78, vcc
	v_add_i32_e32 v77, vcc, s10, v73
	v_add_i32_e32 v73, vcc, s11, v73
	v_or_b32_e32 v72, s4, v75
	s_movk_i32 s10, 0x2000
	;;#ASMSTART
	
     global_load_dwordx4 v[56:59], v[44:45], off 
     
	;;#ASMEND
	;;#ASMSTART
	
     global_load_dwordx4 v[44:47], v[44:45], off offset:16*4*4 
     
	;;#ASMEND
	;;#ASMSTART
	
     global_load_dwordx4 v[60:63], v[48:49], off 
     
	;;#ASMEND
	;;#ASMSTART
	
     global_load_dwordx4 v[48:51], v[48:49], off offset:16*4*4 
     
	;;#ASMEND
	;;#ASMSTART
	
     global_load_dwordx4 v[68:71], v[64:65], off 
     
	;;#ASMEND
	;;#ASMSTART
	
     global_load_dwordx4 v[64:67], v[64:65], off offset:16*4*4 
     
	;;#ASMEND
	;;#ASMSTART
	
       s_waitcnt vmcnt(0) 
       
	;;#ASMEND
	;;#ASMSTART
	
         ds_write_b128 v76, v[79:82] 
         
	;;#ASMEND
	;;#ASMSTART
	
           ds_write_b128 v76, v[83:86] offset:4096 
           
	;;#ASMEND
	;;#ASMSTART
	
     s_waitcnt lgkmcnt(0) 
     
	;;#ASMEND
	v_add_i32_e32 v80, vcc, s10, v73
	s_mov_b32 s5, 0
	;;#ASMSTART
	
     ds_read_b128 v[101:104], v74 offset:0 
     ds_read_b128 v[89:92], v74 offset:256 
     ds_read_b128 v[97:100], v72 offset:0 
     ds_read_b128 v[93:96], v72 offset:256 
     
	;;#ASMEND
	v_add_i32_e32 v79, vcc, s10, v77
	s_mov_b32 s11, 0
	v_mov_b32_e32 v73, v74
BB0_1:                                  ; =>This Inner Loop Header: Depth=1
	v_add_i32_e32 v77, vcc, s5, v80
	v_add_i32_e32 v81, vcc, s5, v79
	v_lshlrev_b64 v[82:83], 4, v[77:78]
	v_add_i32_e32 v84, vcc, s2, v82
	v_mov_b32_e32 v82, v78
	v_mov_b32_e32 v77, s3
	v_addc_u32_e32 v85, vcc, v77, v83, vcc
	v_lshlrev_b64 v[81:82], 4, v[81:82]
	v_mov_b32_e32 v77, s9
	v_add_i32_e32 v86, vcc, s8, v81
	v_addc_u32_e32 v87, vcc, v77, v82, vcc
	;;#ASMSTART
	
     global_load_dwordx4 v[81:84], v[84:85], off 
     
	;;#ASMEND
	;;#ASMSTART
	
     global_load_dwordx4 v[85:88], v[86:87], off 
     
	;;#ASMEND
	;;#ASMSTART
	
     ds_read_b128 v[105:108], v73 offset:1*512 
     ds_read_b128 v[109:112], v73 offset:1*512+256 
     ds_read_b128 v[113:116], v72 offset:1*512 
     ds_read_b128 v[117:120], v72 offset:1*512+256 
     
	;;#ASMEND
	;;#ASMSTART
	
     s_waitcnt lgkmcnt(4) 
     
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v6, v101, v97 
       v_mac_f32 v7, v101, v98 
       v_mac_f32 v8, v101, v99 
       v_mac_f32 v9, v101, v100 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v16, v102, v97 
       v_mac_f32 v17, v102, v98 
       v_mac_f32 v18, v102, v99 
       v_mac_f32 v19, v102, v100 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v26, v103, v97 
       v_mac_f32 v27, v103, v98 
       v_mac_f32 v28, v103, v99 
       v_mac_f32 v29, v103, v100 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v36, v104, v97 
       v_mac_f32 v37, v104, v98 
       v_mac_f32 v38, v104, v99 
       v_mac_f32 v39, v104, v100 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v2, v101, v93 
       v_mac_f32 v3, v101, v94 
       v_mac_f32 v4, v101, v95 
       v_mac_f32 v5, v101, v96 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v12, v102, v93 
       v_mac_f32 v13, v102, v94 
       v_mac_f32 v14, v102, v95 
       v_mac_f32 v15, v102, v96 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v22, v103, v93 
       v_mac_f32 v23, v103, v94 
       v_mac_f32 v24, v103, v95 
       v_mac_f32 v25, v103, v96 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v32, v104, v93 
       v_mac_f32 v33, v104, v94 
       v_mac_f32 v34, v104, v95 
       v_mac_f32 v35, v104, v96 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v52, v89, v97 
       v_mac_f32 v53, v89, v98 
       v_mac_f32 v54, v89, v99 
       v_mac_f32 v55, v89, v100 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v56, v90, v97 
       v_mac_f32 v57, v90, v98 
       v_mac_f32 v58, v90, v99 
       v_mac_f32 v59, v90, v100 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v60, v91, v97 
       v_mac_f32 v61, v91, v98 
       v_mac_f32 v62, v91, v99 
       v_mac_f32 v63, v91, v100 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v68, v92, v97 
       v_mac_f32 v69, v92, v98 
       v_mac_f32 v70, v92, v99 
       v_mac_f32 v71, v92, v100 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v40, v89, v93 
       v_mac_f32 v41, v89, v94 
       v_mac_f32 v42, v89, v95 
       v_mac_f32 v43, v89, v96 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v44, v90, v93 
       v_mac_f32 v45, v90, v94 
       v_mac_f32 v46, v90, v95 
       v_mac_f32 v47, v90, v96 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v48, v91, v93 
       v_mac_f32 v49, v91, v94 
       v_mac_f32 v50, v91, v95 
       v_mac_f32 v51, v91, v96 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v64, v92, v93 
       v_mac_f32 v65, v92, v94 
       v_mac_f32 v66, v92, v95 
       v_mac_f32 v67, v92, v96 
       
	;;#ASMEND
	;;#ASMSTART
	
     ds_read_b128 v[89:92], v73 offset:2*512 
     ds_read_b128 v[93:96], v73 offset:2*512+256 
     ds_read_b128 v[97:100], v72 offset:2*512 
     ds_read_b128 v[101:104], v72 offset:2*512+256 
     
	;;#ASMEND
	s_xor_b32 s11, s11, s10
	;;#ASMSTART
	
     s_waitcnt lgkmcnt(4) 
     
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v6, v105, v113 
       v_mac_f32 v7, v105, v114 
       v_mac_f32 v8, v105, v115 
       v_mac_f32 v9, v105, v116 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v16, v106, v113 
       v_mac_f32 v17, v106, v114 
       v_mac_f32 v18, v106, v115 
       v_mac_f32 v19, v106, v116 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v26, v107, v113 
       v_mac_f32 v27, v107, v114 
       v_mac_f32 v28, v107, v115 
       v_mac_f32 v29, v107, v116 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v36, v108, v113 
       v_mac_f32 v37, v108, v114 
       v_mac_f32 v38, v108, v115 
       v_mac_f32 v39, v108, v116 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v2, v105, v117 
       v_mac_f32 v3, v105, v118 
       v_mac_f32 v4, v105, v119 
       v_mac_f32 v5, v105, v120 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v12, v106, v117 
       v_mac_f32 v13, v106, v118 
       v_mac_f32 v14, v106, v119 
       v_mac_f32 v15, v106, v120 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v22, v107, v117 
       v_mac_f32 v23, v107, v118 
       v_mac_f32 v24, v107, v119 
       v_mac_f32 v25, v107, v120 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v32, v108, v117 
       v_mac_f32 v33, v108, v118 
       v_mac_f32 v34, v108, v119 
       v_mac_f32 v35, v108, v120 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v52, v109, v113 
       v_mac_f32 v53, v109, v114 
       v_mac_f32 v54, v109, v115 
       v_mac_f32 v55, v109, v116 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v56, v110, v113 
       v_mac_f32 v57, v110, v114 
       v_mac_f32 v58, v110, v115 
       v_mac_f32 v59, v110, v116 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v60, v111, v113 
       v_mac_f32 v61, v111, v114 
       v_mac_f32 v62, v111, v115 
       v_mac_f32 v63, v111, v116 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v68, v112, v113 
       v_mac_f32 v69, v112, v114 
       v_mac_f32 v70, v112, v115 
       v_mac_f32 v71, v112, v116 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v40, v109, v117 
       v_mac_f32 v41, v109, v118 
       v_mac_f32 v42, v109, v119 
       v_mac_f32 v43, v109, v120 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v44, v110, v117 
       v_mac_f32 v45, v110, v118 
       v_mac_f32 v46, v110, v119 
       v_mac_f32 v47, v110, v120 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v48, v111, v117 
       v_mac_f32 v49, v111, v118 
       v_mac_f32 v50, v111, v119 
       v_mac_f32 v51, v111, v120 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v64, v112, v117 
       v_mac_f32 v65, v112, v118 
       v_mac_f32 v66, v112, v119 
       v_mac_f32 v67, v112, v120 
       
	;;#ASMEND
	;;#ASMSTART
	
     ds_read_b128 v[105:108], v73 offset:3*512 
     ds_read_b128 v[109:112], v73 offset:3*512+256 
     ds_read_b128 v[113:116], v72 offset:3*512 
     ds_read_b128 v[117:120], v72 offset:3*512+256 
     
	;;#ASMEND
	;;#ASMSTART
	
     s_waitcnt lgkmcnt(4) 
     
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v6, v89, v97 
       v_mac_f32 v7, v89, v98 
       v_mac_f32 v8, v89, v99 
       v_mac_f32 v9, v89, v100 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v16, v90, v97 
       v_mac_f32 v17, v90, v98 
       v_mac_f32 v18, v90, v99 
       v_mac_f32 v19, v90, v100 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v26, v91, v97 
       v_mac_f32 v27, v91, v98 
       v_mac_f32 v28, v91, v99 
       v_mac_f32 v29, v91, v100 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v36, v92, v97 
       v_mac_f32 v37, v92, v98 
       v_mac_f32 v38, v92, v99 
       v_mac_f32 v39, v92, v100 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v2, v89, v101 
       v_mac_f32 v3, v89, v102 
       v_mac_f32 v4, v89, v103 
       v_mac_f32 v5, v89, v104 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v12, v90, v101 
       v_mac_f32 v13, v90, v102 
       v_mac_f32 v14, v90, v103 
       v_mac_f32 v15, v90, v104 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v22, v91, v101 
       v_mac_f32 v23, v91, v102 
       v_mac_f32 v24, v91, v103 
       v_mac_f32 v25, v91, v104 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v32, v92, v101 
       v_mac_f32 v33, v92, v102 
       v_mac_f32 v34, v92, v103 
       v_mac_f32 v35, v92, v104 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v52, v93, v97 
       v_mac_f32 v53, v93, v98 
       v_mac_f32 v54, v93, v99 
       v_mac_f32 v55, v93, v100 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v56, v94, v97 
       v_mac_f32 v57, v94, v98 
       v_mac_f32 v58, v94, v99 
       v_mac_f32 v59, v94, v100 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v60, v95, v97 
       v_mac_f32 v61, v95, v98 
       v_mac_f32 v62, v95, v99 
       v_mac_f32 v63, v95, v100 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v68, v96, v97 
       v_mac_f32 v69, v96, v98 
       v_mac_f32 v70, v96, v99 
       v_mac_f32 v71, v96, v100 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v40, v93, v101 
       v_mac_f32 v41, v93, v102 
       v_mac_f32 v42, v93, v103 
       v_mac_f32 v43, v93, v104 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v44, v94, v101 
       v_mac_f32 v45, v94, v102 
       v_mac_f32 v46, v94, v103 
       v_mac_f32 v47, v94, v104 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v48, v95, v101 
       v_mac_f32 v49, v95, v102 
       v_mac_f32 v50, v95, v103 
       v_mac_f32 v51, v95, v104 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v64, v96, v101 
       v_mac_f32 v65, v96, v102 
       v_mac_f32 v66, v96, v103 
       v_mac_f32 v67, v96, v104 
       
	;;#ASMEND
	;;#ASMSTART
	
     ds_read_b128 v[89:92], v73 offset:4*512 
     ds_read_b128 v[93:96], v73 offset:4*512+256 
     ds_read_b128 v[97:100], v72 offset:4*512 
     ds_read_b128 v[101:104], v72 offset:4*512+256 
     
	;;#ASMEND
	;;#ASMSTART
	
     s_waitcnt lgkmcnt(4) 
     
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v6, v105, v113 
       v_mac_f32 v7, v105, v114 
       v_mac_f32 v8, v105, v115 
       v_mac_f32 v9, v105, v116 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v16, v106, v113 
       v_mac_f32 v17, v106, v114 
       v_mac_f32 v18, v106, v115 
       v_mac_f32 v19, v106, v116 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v26, v107, v113 
       v_mac_f32 v27, v107, v114 
       v_mac_f32 v28, v107, v115 
       v_mac_f32 v29, v107, v116 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v36, v108, v113 
       v_mac_f32 v37, v108, v114 
       v_mac_f32 v38, v108, v115 
       v_mac_f32 v39, v108, v116 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v2, v105, v117 
       v_mac_f32 v3, v105, v118 
       v_mac_f32 v4, v105, v119 
       v_mac_f32 v5, v105, v120 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v12, v106, v117 
       v_mac_f32 v13, v106, v118 
       v_mac_f32 v14, v106, v119 
       v_mac_f32 v15, v106, v120 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v22, v107, v117 
       v_mac_f32 v23, v107, v118 
       v_mac_f32 v24, v107, v119 
       v_mac_f32 v25, v107, v120 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v32, v108, v117 
       v_mac_f32 v33, v108, v118 
       v_mac_f32 v34, v108, v119 
       v_mac_f32 v35, v108, v120 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v52, v109, v113 
       v_mac_f32 v53, v109, v114 
       v_mac_f32 v54, v109, v115 
       v_mac_f32 v55, v109, v116 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v56, v110, v113 
       v_mac_f32 v57, v110, v114 
       v_mac_f32 v58, v110, v115 
       v_mac_f32 v59, v110, v116 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v60, v111, v113 
       v_mac_f32 v61, v111, v114 
       v_mac_f32 v62, v111, v115 
       v_mac_f32 v63, v111, v116 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v68, v112, v113 
       v_mac_f32 v69, v112, v114 
       v_mac_f32 v70, v112, v115 
       v_mac_f32 v71, v112, v116 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v40, v109, v117 
       v_mac_f32 v41, v109, v118 
       v_mac_f32 v42, v109, v119 
       v_mac_f32 v43, v109, v120 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v44, v110, v117 
       v_mac_f32 v45, v110, v118 
       v_mac_f32 v46, v110, v119 
       v_mac_f32 v47, v110, v120 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v48, v111, v117 
       v_mac_f32 v49, v111, v118 
       v_mac_f32 v50, v111, v119 
       v_mac_f32 v51, v111, v120 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v64, v112, v117 
       v_mac_f32 v65, v112, v118 
       v_mac_f32 v66, v112, v119 
       v_mac_f32 v67, v112, v120 
       
	;;#ASMEND
	;;#ASMSTART
	
     ds_read_b128 v[105:108], v73 offset:5*512 
     ds_read_b128 v[109:112], v73 offset:5*512+256 
     ds_read_b128 v[113:116], v72 offset:5*512 
     ds_read_b128 v[117:120], v72 offset:5*512+256 
     
	;;#ASMEND
	;;#ASMSTART
	
     s_waitcnt lgkmcnt(4) 
     
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v6, v89, v97 
       v_mac_f32 v7, v89, v98 
       v_mac_f32 v8, v89, v99 
       v_mac_f32 v9, v89, v100 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v16, v90, v97 
       v_mac_f32 v17, v90, v98 
       v_mac_f32 v18, v90, v99 
       v_mac_f32 v19, v90, v100 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v26, v91, v97 
       v_mac_f32 v27, v91, v98 
       v_mac_f32 v28, v91, v99 
       v_mac_f32 v29, v91, v100 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v36, v92, v97 
       v_mac_f32 v37, v92, v98 
       v_mac_f32 v38, v92, v99 
       v_mac_f32 v39, v92, v100 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v2, v89, v101 
       v_mac_f32 v3, v89, v102 
       v_mac_f32 v4, v89, v103 
       v_mac_f32 v5, v89, v104 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v12, v90, v101 
       v_mac_f32 v13, v90, v102 
       v_mac_f32 v14, v90, v103 
       v_mac_f32 v15, v90, v104 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v22, v91, v101 
       v_mac_f32 v23, v91, v102 
       v_mac_f32 v24, v91, v103 
       v_mac_f32 v25, v91, v104 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v32, v92, v101 
       v_mac_f32 v33, v92, v102 
       v_mac_f32 v34, v92, v103 
       v_mac_f32 v35, v92, v104 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v52, v93, v97 
       v_mac_f32 v53, v93, v98 
       v_mac_f32 v54, v93, v99 
       v_mac_f32 v55, v93, v100 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v56, v94, v97 
       v_mac_f32 v57, v94, v98 
       v_mac_f32 v58, v94, v99 
       v_mac_f32 v59, v94, v100 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v60, v95, v97 
       v_mac_f32 v61, v95, v98 
       v_mac_f32 v62, v95, v99 
       v_mac_f32 v63, v95, v100 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v68, v96, v97 
       v_mac_f32 v69, v96, v98 
       v_mac_f32 v70, v96, v99 
       v_mac_f32 v71, v96, v100 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v40, v93, v101 
       v_mac_f32 v41, v93, v102 
       v_mac_f32 v42, v93, v103 
       v_mac_f32 v43, v93, v104 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v44, v94, v101 
       v_mac_f32 v45, v94, v102 
       v_mac_f32 v46, v94, v103 
       v_mac_f32 v47, v94, v104 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v48, v95, v101 
       v_mac_f32 v49, v95, v102 
       v_mac_f32 v50, v95, v103 
       v_mac_f32 v51, v95, v104 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v64, v96, v101 
       v_mac_f32 v65, v96, v102 
       v_mac_f32 v66, v96, v103 
       v_mac_f32 v67, v96, v104 
       
	;;#ASMEND
	;;#ASMSTART
	
     ds_read_b128 v[89:92], v73 offset:6*512 
     ds_read_b128 v[93:96], v73 offset:6*512+256 
     ds_read_b128 v[97:100], v72 offset:6*512 
     ds_read_b128 v[101:104], v72 offset:6*512+256 
     
	;;#ASMEND
	v_add_i32_e32 v77, vcc, s11, v76
	;;#ASMSTART
	
     s_waitcnt lgkmcnt(4) 
     
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v6, v105, v113 
       v_mac_f32 v7, v105, v114 
       v_mac_f32 v8, v105, v115 
       v_mac_f32 v9, v105, v116 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v16, v106, v113 
       v_mac_f32 v17, v106, v114 
       v_mac_f32 v18, v106, v115 
       v_mac_f32 v19, v106, v116 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v26, v107, v113 
       v_mac_f32 v27, v107, v114 
       v_mac_f32 v28, v107, v115 
       v_mac_f32 v29, v107, v116 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v36, v108, v113 
       v_mac_f32 v37, v108, v114 
       v_mac_f32 v38, v108, v115 
       v_mac_f32 v39, v108, v116 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v2, v105, v117 
       v_mac_f32 v3, v105, v118 
       v_mac_f32 v4, v105, v119 
       v_mac_f32 v5, v105, v120 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v12, v106, v117 
       v_mac_f32 v13, v106, v118 
       v_mac_f32 v14, v106, v119 
       v_mac_f32 v15, v106, v120 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v22, v107, v117 
       v_mac_f32 v23, v107, v118 
       v_mac_f32 v24, v107, v119 
       v_mac_f32 v25, v107, v120 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v32, v108, v117 
       v_mac_f32 v33, v108, v118 
       v_mac_f32 v34, v108, v119 
       v_mac_f32 v35, v108, v120 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v52, v109, v113 
       v_mac_f32 v53, v109, v114 
       v_mac_f32 v54, v109, v115 
       v_mac_f32 v55, v109, v116 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v56, v110, v113 
       v_mac_f32 v57, v110, v114 
       v_mac_f32 v58, v110, v115 
       v_mac_f32 v59, v110, v116 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v60, v111, v113 
       v_mac_f32 v61, v111, v114 
       v_mac_f32 v62, v111, v115 
       v_mac_f32 v63, v111, v116 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v68, v112, v113 
       v_mac_f32 v69, v112, v114 
       v_mac_f32 v70, v112, v115 
       v_mac_f32 v71, v112, v116 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v40, v109, v117 
       v_mac_f32 v41, v109, v118 
       v_mac_f32 v42, v109, v119 
       v_mac_f32 v43, v109, v120 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v44, v110, v117 
       v_mac_f32 v45, v110, v118 
       v_mac_f32 v46, v110, v119 
       v_mac_f32 v47, v110, v120 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v48, v111, v117 
       v_mac_f32 v49, v111, v118 
       v_mac_f32 v50, v111, v119 
       v_mac_f32 v51, v111, v120 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v64, v112, v117 
       v_mac_f32 v65, v112, v118 
       v_mac_f32 v66, v112, v119 
       v_mac_f32 v67, v112, v120 
       
	;;#ASMEND
	;;#ASMSTART
	
     ds_read_b128 v[105:108], v73 offset:7*512 
     ds_read_b128 v[109:112], v73 offset:7*512+256 
     ds_read_b128 v[113:116], v72 offset:7*512 
     ds_read_b128 v[117:120], v72 offset:7*512+256 
     
	;;#ASMEND
	;;#ASMSTART
	
       s_waitcnt vmcnt(0) 
       
	;;#ASMEND
	;;#ASMSTART
	
         ds_write_b128 v77, v[81:84] 
         
	;;#ASMEND
	;;#ASMSTART
	
           ds_write_b128 v77, v[85:88] offset:4096 
           
	;;#ASMEND
	;;#ASMSTART
	
     s_waitcnt lgkmcnt(2) 
     
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v6, v89, v97 
       v_mac_f32 v7, v89, v98 
       v_mac_f32 v8, v89, v99 
       v_mac_f32 v9, v89, v100 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v16, v90, v97 
       v_mac_f32 v17, v90, v98 
       v_mac_f32 v18, v90, v99 
       v_mac_f32 v19, v90, v100 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v26, v91, v97 
       v_mac_f32 v27, v91, v98 
       v_mac_f32 v28, v91, v99 
       v_mac_f32 v29, v91, v100 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v36, v92, v97 
       v_mac_f32 v37, v92, v98 
       v_mac_f32 v38, v92, v99 
       v_mac_f32 v39, v92, v100 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v2, v89, v101 
       v_mac_f32 v3, v89, v102 
       v_mac_f32 v4, v89, v103 
       v_mac_f32 v5, v89, v104 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v12, v90, v101 
       v_mac_f32 v13, v90, v102 
       v_mac_f32 v14, v90, v103 
       v_mac_f32 v15, v90, v104 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v22, v91, v101 
       v_mac_f32 v23, v91, v102 
       v_mac_f32 v24, v91, v103 
       v_mac_f32 v25, v91, v104 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v32, v92, v101 
       v_mac_f32 v33, v92, v102 
       v_mac_f32 v34, v92, v103 
       v_mac_f32 v35, v92, v104 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v52, v93, v97 
       v_mac_f32 v53, v93, v98 
       v_mac_f32 v54, v93, v99 
       v_mac_f32 v55, v93, v100 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v56, v94, v97 
       v_mac_f32 v57, v94, v98 
       v_mac_f32 v58, v94, v99 
       v_mac_f32 v59, v94, v100 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v60, v95, v97 
       v_mac_f32 v61, v95, v98 
       v_mac_f32 v62, v95, v99 
       v_mac_f32 v63, v95, v100 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v68, v96, v97 
       v_mac_f32 v69, v96, v98 
       v_mac_f32 v70, v96, v99 
       v_mac_f32 v71, v96, v100 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v40, v93, v101 
       v_mac_f32 v41, v93, v102 
       v_mac_f32 v42, v93, v103 
       v_mac_f32 v43, v93, v104 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v44, v94, v101 
       v_mac_f32 v45, v94, v102 
       v_mac_f32 v46, v94, v103 
       v_mac_f32 v47, v94, v104 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v48, v95, v101 
       v_mac_f32 v49, v95, v102 
       v_mac_f32 v50, v95, v103 
       v_mac_f32 v51, v95, v104 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v64, v96, v101 
       v_mac_f32 v65, v96, v102 
       v_mac_f32 v66, v96, v103 
       v_mac_f32 v67, v96, v104 
       
	;;#ASMEND
	;;#ASMSTART
	
     s_waitcnt lgkmcnt(0) 
     
	;;#ASMEND
	s_barrier
	s_xor_b32 s4, s4, s10
	s_add_i32 s5, s5, s10
	v_add_i32_e32 v73, vcc, s11, v74
	v_add_i32_e32 v72, vcc, s4, v75
	;;#ASMSTART
	
     ds_read_b128 v[101:104], v73 offset:0 
     ds_read_b128 v[89:92], v73 offset:256 
     ds_read_b128 v[97:100], v72 offset:0 
     ds_read_b128 v[93:96], v72 offset:256 
     
	;;#ASMEND
	s_cmp_lg_u32 s5, 0x3fe000
	;;#ASMSTART
	
       v_mac_f32 v6, v105, v113 
       v_mac_f32 v7, v105, v114 
       v_mac_f32 v8, v105, v115 
       v_mac_f32 v9, v105, v116 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v16, v106, v113 
       v_mac_f32 v17, v106, v114 
       v_mac_f32 v18, v106, v115 
       v_mac_f32 v19, v106, v116 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v26, v107, v113 
       v_mac_f32 v27, v107, v114 
       v_mac_f32 v28, v107, v115 
       v_mac_f32 v29, v107, v116 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v36, v108, v113 
       v_mac_f32 v37, v108, v114 
       v_mac_f32 v38, v108, v115 
       v_mac_f32 v39, v108, v116 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v2, v105, v117 
       v_mac_f32 v3, v105, v118 
       v_mac_f32 v4, v105, v119 
       v_mac_f32 v5, v105, v120 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v12, v106, v117 
       v_mac_f32 v13, v106, v118 
       v_mac_f32 v14, v106, v119 
       v_mac_f32 v15, v106, v120 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v22, v107, v117 
       v_mac_f32 v23, v107, v118 
       v_mac_f32 v24, v107, v119 
       v_mac_f32 v25, v107, v120 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v32, v108, v117 
       v_mac_f32 v33, v108, v118 
       v_mac_f32 v34, v108, v119 
       v_mac_f32 v35, v108, v120 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v52, v109, v113 
       v_mac_f32 v53, v109, v114 
       v_mac_f32 v54, v109, v115 
       v_mac_f32 v55, v109, v116 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v56, v110, v113 
       v_mac_f32 v57, v110, v114 
       v_mac_f32 v58, v110, v115 
       v_mac_f32 v59, v110, v116 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v60, v111, v113 
       v_mac_f32 v61, v111, v114 
       v_mac_f32 v62, v111, v115 
       v_mac_f32 v63, v111, v116 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v68, v112, v113 
       v_mac_f32 v69, v112, v114 
       v_mac_f32 v70, v112, v115 
       v_mac_f32 v71, v112, v116 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v40, v109, v117 
       v_mac_f32 v41, v109, v118 
       v_mac_f32 v42, v109, v119 
       v_mac_f32 v43, v109, v120 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v44, v110, v117 
       v_mac_f32 v45, v110, v118 
       v_mac_f32 v46, v110, v119 
       v_mac_f32 v47, v110, v120 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v48, v111, v117 
       v_mac_f32 v49, v111, v118 
       v_mac_f32 v50, v111, v119 
       v_mac_f32 v51, v111, v120 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v64, v112, v117 
       v_mac_f32 v65, v112, v118 
       v_mac_f32 v66, v112, v119 
       v_mac_f32 v67, v112, v120 
       
	;;#ASMEND
	s_cbranch_scc1 BB0_1
; BB#2:                                 ; %_ZZ4mainENK67HIP_kernel_functor_name_begin_unnamed_HIP_kernel_functor_name_end_5clERKN2hc11tiled_indexILi3EEE.exit
	;;#ASMSTART
	
     ds_read_b128 v[74:77], v73 offset:1*512 
     ds_read_b128 v[78:81], v73 offset:1*512+256 
     ds_read_b128 v[82:85], v72 offset:1*512 
     ds_read_b128 v[105:108], v72 offset:1*512+256 
     
	;;#ASMEND
	;;#ASMSTART
	
     s_waitcnt lgkmcnt(4) 
     
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v6, v101, v97 
       v_mac_f32 v7, v101, v98 
       v_mac_f32 v8, v101, v99 
       v_mac_f32 v9, v101, v100 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v16, v102, v97 
       v_mac_f32 v17, v102, v98 
       v_mac_f32 v18, v102, v99 
       v_mac_f32 v19, v102, v100 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v26, v103, v97 
       v_mac_f32 v27, v103, v98 
       v_mac_f32 v28, v103, v99 
       v_mac_f32 v29, v103, v100 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v36, v104, v97 
       v_mac_f32 v37, v104, v98 
       v_mac_f32 v38, v104, v99 
       v_mac_f32 v39, v104, v100 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v2, v101, v93 
       v_mac_f32 v3, v101, v94 
       v_mac_f32 v4, v101, v95 
       v_mac_f32 v5, v101, v96 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v12, v102, v93 
       v_mac_f32 v13, v102, v94 
       v_mac_f32 v14, v102, v95 
       v_mac_f32 v15, v102, v96 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v22, v103, v93 
       v_mac_f32 v23, v103, v94 
       v_mac_f32 v24, v103, v95 
       v_mac_f32 v25, v103, v96 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v32, v104, v93 
       v_mac_f32 v33, v104, v94 
       v_mac_f32 v34, v104, v95 
       v_mac_f32 v35, v104, v96 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v52, v89, v97 
       v_mac_f32 v53, v89, v98 
       v_mac_f32 v54, v89, v99 
       v_mac_f32 v55, v89, v100 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v56, v90, v97 
       v_mac_f32 v57, v90, v98 
       v_mac_f32 v58, v90, v99 
       v_mac_f32 v59, v90, v100 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v60, v91, v97 
       v_mac_f32 v61, v91, v98 
       v_mac_f32 v62, v91, v99 
       v_mac_f32 v63, v91, v100 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v68, v92, v97 
       v_mac_f32 v69, v92, v98 
       v_mac_f32 v70, v92, v99 
       v_mac_f32 v71, v92, v100 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v40, v89, v93 
       v_mac_f32 v41, v89, v94 
       v_mac_f32 v42, v89, v95 
       v_mac_f32 v43, v89, v96 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v44, v90, v93 
       v_mac_f32 v45, v90, v94 
       v_mac_f32 v46, v90, v95 
       v_mac_f32 v47, v90, v96 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v48, v91, v93 
       v_mac_f32 v49, v91, v94 
       v_mac_f32 v50, v91, v95 
       v_mac_f32 v51, v91, v96 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v64, v92, v93 
       v_mac_f32 v65, v92, v94 
       v_mac_f32 v66, v92, v95 
       v_mac_f32 v67, v92, v96 
       
	;;#ASMEND
	;;#ASMSTART
	
     ds_read_b128 v[86:89], v73 offset:2*512 
     ds_read_b128 v[90:93], v73 offset:2*512+256 
     ds_read_b128 v[94:97], v72 offset:2*512 
     ds_read_b128 v[98:101], v72 offset:2*512+256 
     
	;;#ASMEND
	;;#ASMSTART
	
     s_waitcnt lgkmcnt(4) 
     
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v6, v74, v82 
       v_mac_f32 v7, v74, v83 
       v_mac_f32 v8, v74, v84 
       v_mac_f32 v9, v74, v85 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v16, v75, v82 
       v_mac_f32 v17, v75, v83 
       v_mac_f32 v18, v75, v84 
       v_mac_f32 v19, v75, v85 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v26, v76, v82 
       v_mac_f32 v27, v76, v83 
       v_mac_f32 v28, v76, v84 
       v_mac_f32 v29, v76, v85 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v36, v77, v82 
       v_mac_f32 v37, v77, v83 
       v_mac_f32 v38, v77, v84 
       v_mac_f32 v39, v77, v85 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v2, v74, v105 
       v_mac_f32 v3, v74, v106 
       v_mac_f32 v4, v74, v107 
       v_mac_f32 v5, v74, v108 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v12, v75, v105 
       v_mac_f32 v13, v75, v106 
       v_mac_f32 v14, v75, v107 
       v_mac_f32 v15, v75, v108 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v22, v76, v105 
       v_mac_f32 v23, v76, v106 
       v_mac_f32 v24, v76, v107 
       v_mac_f32 v25, v76, v108 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v32, v77, v105 
       v_mac_f32 v33, v77, v106 
       v_mac_f32 v34, v77, v107 
       v_mac_f32 v35, v77, v108 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v52, v78, v82 
       v_mac_f32 v53, v78, v83 
       v_mac_f32 v54, v78, v84 
       v_mac_f32 v55, v78, v85 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v56, v79, v82 
       v_mac_f32 v57, v79, v83 
       v_mac_f32 v58, v79, v84 
       v_mac_f32 v59, v79, v85 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v60, v80, v82 
       v_mac_f32 v61, v80, v83 
       v_mac_f32 v62, v80, v84 
       v_mac_f32 v63, v80, v85 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v68, v81, v82 
       v_mac_f32 v69, v81, v83 
       v_mac_f32 v70, v81, v84 
       v_mac_f32 v71, v81, v85 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v40, v78, v105 
       v_mac_f32 v41, v78, v106 
       v_mac_f32 v42, v78, v107 
       v_mac_f32 v43, v78, v108 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v44, v79, v105 
       v_mac_f32 v45, v79, v106 
       v_mac_f32 v46, v79, v107 
       v_mac_f32 v47, v79, v108 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v48, v80, v105 
       v_mac_f32 v49, v80, v106 
       v_mac_f32 v50, v80, v107 
       v_mac_f32 v51, v80, v108 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v64, v81, v105 
       v_mac_f32 v65, v81, v106 
       v_mac_f32 v66, v81, v107 
       v_mac_f32 v67, v81, v108 
       
	;;#ASMEND
	;;#ASMSTART
	
     ds_read_b128 v[74:77], v73 offset:3*512 
     ds_read_b128 v[78:81], v73 offset:3*512+256 
     ds_read_b128 v[82:85], v72 offset:3*512 
     ds_read_b128 v[102:105], v72 offset:3*512+256 
     
	;;#ASMEND
	s_add_u32 s4, s0, 0x104000
	;;#ASMSTART
	
     s_waitcnt lgkmcnt(4) 
     
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v6, v86, v94 
       v_mac_f32 v7, v86, v95 
       v_mac_f32 v8, v86, v96 
       v_mac_f32 v9, v86, v97 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v16, v87, v94 
       v_mac_f32 v17, v87, v95 
       v_mac_f32 v18, v87, v96 
       v_mac_f32 v19, v87, v97 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v26, v88, v94 
       v_mac_f32 v27, v88, v95 
       v_mac_f32 v28, v88, v96 
       v_mac_f32 v29, v88, v97 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v36, v89, v94 
       v_mac_f32 v37, v89, v95 
       v_mac_f32 v38, v89, v96 
       v_mac_f32 v39, v89, v97 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v2, v86, v98 
       v_mac_f32 v3, v86, v99 
       v_mac_f32 v4, v86, v100 
       v_mac_f32 v5, v86, v101 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v12, v87, v98 
       v_mac_f32 v13, v87, v99 
       v_mac_f32 v14, v87, v100 
       v_mac_f32 v15, v87, v101 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v22, v88, v98 
       v_mac_f32 v23, v88, v99 
       v_mac_f32 v24, v88, v100 
       v_mac_f32 v25, v88, v101 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v32, v89, v98 
       v_mac_f32 v33, v89, v99 
       v_mac_f32 v34, v89, v100 
       v_mac_f32 v35, v89, v101 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v52, v90, v94 
       v_mac_f32 v53, v90, v95 
       v_mac_f32 v54, v90, v96 
       v_mac_f32 v55, v90, v97 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v56, v91, v94 
       v_mac_f32 v57, v91, v95 
       v_mac_f32 v58, v91, v96 
       v_mac_f32 v59, v91, v97 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v60, v92, v94 
       v_mac_f32 v61, v92, v95 
       v_mac_f32 v62, v92, v96 
       v_mac_f32 v63, v92, v97 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v68, v93, v94 
       v_mac_f32 v69, v93, v95 
       v_mac_f32 v70, v93, v96 
       v_mac_f32 v71, v93, v97 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v40, v90, v98 
       v_mac_f32 v41, v90, v99 
       v_mac_f32 v42, v90, v100 
       v_mac_f32 v43, v90, v101 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v44, v91, v98 
       v_mac_f32 v45, v91, v99 
       v_mac_f32 v46, v91, v100 
       v_mac_f32 v47, v91, v101 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v48, v92, v98 
       v_mac_f32 v49, v92, v99 
       v_mac_f32 v50, v92, v100 
       v_mac_f32 v51, v92, v101 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v64, v93, v98 
       v_mac_f32 v65, v93, v99 
       v_mac_f32 v66, v93, v100 
       v_mac_f32 v67, v93, v101 
       
	;;#ASMEND
	;;#ASMSTART
	
     ds_read_b128 v[86:89], v73 offset:4*512 
     ds_read_b128 v[90:93], v73 offset:4*512+256 
     ds_read_b128 v[94:97], v72 offset:4*512 
     ds_read_b128 v[98:101], v72 offset:4*512+256 
     
	;;#ASMEND
	;;#ASMSTART
	
     s_waitcnt lgkmcnt(4) 
     
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v6, v74, v82 
       v_mac_f32 v7, v74, v83 
       v_mac_f32 v8, v74, v84 
       v_mac_f32 v9, v74, v85 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v16, v75, v82 
       v_mac_f32 v17, v75, v83 
       v_mac_f32 v18, v75, v84 
       v_mac_f32 v19, v75, v85 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v26, v76, v82 
       v_mac_f32 v27, v76, v83 
       v_mac_f32 v28, v76, v84 
       v_mac_f32 v29, v76, v85 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v36, v77, v82 
       v_mac_f32 v37, v77, v83 
       v_mac_f32 v38, v77, v84 
       v_mac_f32 v39, v77, v85 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v2, v74, v102 
       v_mac_f32 v3, v74, v103 
       v_mac_f32 v4, v74, v104 
       v_mac_f32 v5, v74, v105 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v12, v75, v102 
       v_mac_f32 v13, v75, v103 
       v_mac_f32 v14, v75, v104 
       v_mac_f32 v15, v75, v105 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v22, v76, v102 
       v_mac_f32 v23, v76, v103 
       v_mac_f32 v24, v76, v104 
       v_mac_f32 v25, v76, v105 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v32, v77, v102 
       v_mac_f32 v33, v77, v103 
       v_mac_f32 v34, v77, v104 
       v_mac_f32 v35, v77, v105 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v52, v78, v82 
       v_mac_f32 v53, v78, v83 
       v_mac_f32 v54, v78, v84 
       v_mac_f32 v55, v78, v85 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v56, v79, v82 
       v_mac_f32 v57, v79, v83 
       v_mac_f32 v58, v79, v84 
       v_mac_f32 v59, v79, v85 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v60, v80, v82 
       v_mac_f32 v61, v80, v83 
       v_mac_f32 v62, v80, v84 
       v_mac_f32 v63, v80, v85 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v68, v81, v82 
       v_mac_f32 v69, v81, v83 
       v_mac_f32 v70, v81, v84 
       v_mac_f32 v71, v81, v85 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v40, v78, v102 
       v_mac_f32 v41, v78, v103 
       v_mac_f32 v42, v78, v104 
       v_mac_f32 v43, v78, v105 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v44, v79, v102 
       v_mac_f32 v45, v79, v103 
       v_mac_f32 v46, v79, v104 
       v_mac_f32 v47, v79, v105 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v48, v80, v102 
       v_mac_f32 v49, v80, v103 
       v_mac_f32 v50, v80, v104 
       v_mac_f32 v51, v80, v105 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v64, v81, v102 
       v_mac_f32 v65, v81, v103 
       v_mac_f32 v66, v81, v104 
       v_mac_f32 v67, v81, v105 
       
	;;#ASMEND
	;;#ASMSTART
	
     ds_read_b128 v[74:77], v73 offset:5*512 
     ds_read_b128 v[78:81], v73 offset:5*512+256 
     ds_read_b128 v[82:85], v72 offset:5*512 
     ds_read_b128 v[102:105], v72 offset:5*512+256 
     
	;;#ASMEND
	s_addc_u32 s5, s1, 0
	;;#ASMSTART
	
     s_waitcnt lgkmcnt(4) 
     
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v6, v86, v94 
       v_mac_f32 v7, v86, v95 
       v_mac_f32 v8, v86, v96 
       v_mac_f32 v9, v86, v97 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v16, v87, v94 
       v_mac_f32 v17, v87, v95 
       v_mac_f32 v18, v87, v96 
       v_mac_f32 v19, v87, v97 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v26, v88, v94 
       v_mac_f32 v27, v88, v95 
       v_mac_f32 v28, v88, v96 
       v_mac_f32 v29, v88, v97 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v36, v89, v94 
       v_mac_f32 v37, v89, v95 
       v_mac_f32 v38, v89, v96 
       v_mac_f32 v39, v89, v97 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v2, v86, v98 
       v_mac_f32 v3, v86, v99 
       v_mac_f32 v4, v86, v100 
       v_mac_f32 v5, v86, v101 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v12, v87, v98 
       v_mac_f32 v13, v87, v99 
       v_mac_f32 v14, v87, v100 
       v_mac_f32 v15, v87, v101 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v22, v88, v98 
       v_mac_f32 v23, v88, v99 
       v_mac_f32 v24, v88, v100 
       v_mac_f32 v25, v88, v101 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v32, v89, v98 
       v_mac_f32 v33, v89, v99 
       v_mac_f32 v34, v89, v100 
       v_mac_f32 v35, v89, v101 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v52, v90, v94 
       v_mac_f32 v53, v90, v95 
       v_mac_f32 v54, v90, v96 
       v_mac_f32 v55, v90, v97 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v56, v91, v94 
       v_mac_f32 v57, v91, v95 
       v_mac_f32 v58, v91, v96 
       v_mac_f32 v59, v91, v97 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v60, v92, v94 
       v_mac_f32 v61, v92, v95 
       v_mac_f32 v62, v92, v96 
       v_mac_f32 v63, v92, v97 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v68, v93, v94 
       v_mac_f32 v69, v93, v95 
       v_mac_f32 v70, v93, v96 
       v_mac_f32 v71, v93, v97 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v40, v90, v98 
       v_mac_f32 v41, v90, v99 
       v_mac_f32 v42, v90, v100 
       v_mac_f32 v43, v90, v101 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v44, v91, v98 
       v_mac_f32 v45, v91, v99 
       v_mac_f32 v46, v91, v100 
       v_mac_f32 v47, v91, v101 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v48, v92, v98 
       v_mac_f32 v49, v92, v99 
       v_mac_f32 v50, v92, v100 
       v_mac_f32 v51, v92, v101 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v64, v93, v98 
       v_mac_f32 v65, v93, v99 
       v_mac_f32 v66, v93, v100 
       v_mac_f32 v67, v93, v101 
       
	;;#ASMEND
	;;#ASMSTART
	
     ds_read_b128 v[86:89], v73 offset:6*512 
     ds_read_b128 v[90:93], v73 offset:6*512+256 
     ds_read_b128 v[94:97], v72 offset:6*512 
     ds_read_b128 v[98:101], v72 offset:6*512+256 
     
	;;#ASMEND
	;;#ASMSTART
	
     s_waitcnt lgkmcnt(4) 
     
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v6, v74, v82 
       v_mac_f32 v7, v74, v83 
       v_mac_f32 v8, v74, v84 
       v_mac_f32 v9, v74, v85 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v16, v75, v82 
       v_mac_f32 v17, v75, v83 
       v_mac_f32 v18, v75, v84 
       v_mac_f32 v19, v75, v85 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v26, v76, v82 
       v_mac_f32 v27, v76, v83 
       v_mac_f32 v28, v76, v84 
       v_mac_f32 v29, v76, v85 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v36, v77, v82 
       v_mac_f32 v37, v77, v83 
       v_mac_f32 v38, v77, v84 
       v_mac_f32 v39, v77, v85 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v2, v74, v102 
       v_mac_f32 v3, v74, v103 
       v_mac_f32 v4, v74, v104 
       v_mac_f32 v5, v74, v105 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v12, v75, v102 
       v_mac_f32 v13, v75, v103 
       v_mac_f32 v14, v75, v104 
       v_mac_f32 v15, v75, v105 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v22, v76, v102 
       v_mac_f32 v23, v76, v103 
       v_mac_f32 v24, v76, v104 
       v_mac_f32 v25, v76, v105 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v32, v77, v102 
       v_mac_f32 v33, v77, v103 
       v_mac_f32 v34, v77, v104 
       v_mac_f32 v35, v77, v105 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v52, v78, v82 
       v_mac_f32 v53, v78, v83 
       v_mac_f32 v54, v78, v84 
       v_mac_f32 v55, v78, v85 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v56, v79, v82 
       v_mac_f32 v57, v79, v83 
       v_mac_f32 v58, v79, v84 
       v_mac_f32 v59, v79, v85 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v60, v80, v82 
       v_mac_f32 v61, v80, v83 
       v_mac_f32 v62, v80, v84 
       v_mac_f32 v63, v80, v85 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v68, v81, v82 
       v_mac_f32 v69, v81, v83 
       v_mac_f32 v70, v81, v84 
       v_mac_f32 v71, v81, v85 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v40, v78, v102 
       v_mac_f32 v41, v78, v103 
       v_mac_f32 v42, v78, v104 
       v_mac_f32 v43, v78, v105 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v44, v79, v102 
       v_mac_f32 v45, v79, v103 
       v_mac_f32 v46, v79, v104 
       v_mac_f32 v47, v79, v105 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v48, v80, v102 
       v_mac_f32 v49, v80, v103 
       v_mac_f32 v50, v80, v104 
       v_mac_f32 v51, v80, v105 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v64, v81, v102 
       v_mac_f32 v65, v81, v103 
       v_mac_f32 v66, v81, v104 
       v_mac_f32 v67, v81, v105 
       
	;;#ASMEND
	;;#ASMSTART
	
     ds_read_b128 v[72:75], v73 offset:7*512 
     ds_read_b128 v[76:79], v73 offset:7*512+256 
     ds_read_b128 v[80:83], v72 offset:7*512 
     ds_read_b128 v[102:105], v72 offset:7*512+256 
     
	;;#ASMEND
	s_add_u32 s2, s0, 0x108000
	v_mov_b32_e32 v110, s7
	;;#ASMSTART
	
     s_waitcnt lgkmcnt(4) 
     
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v6, v86, v94 
       v_mac_f32 v7, v86, v95 
       v_mac_f32 v8, v86, v96 
       v_mac_f32 v9, v86, v97 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v16, v87, v94 
       v_mac_f32 v17, v87, v95 
       v_mac_f32 v18, v87, v96 
       v_mac_f32 v19, v87, v97 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v26, v88, v94 
       v_mac_f32 v27, v88, v95 
       v_mac_f32 v28, v88, v96 
       v_mac_f32 v29, v88, v97 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v36, v89, v94 
       v_mac_f32 v37, v89, v95 
       v_mac_f32 v38, v89, v96 
       v_mac_f32 v39, v89, v97 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v2, v86, v98 
       v_mac_f32 v3, v86, v99 
       v_mac_f32 v4, v86, v100 
       v_mac_f32 v5, v86, v101 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v12, v87, v98 
       v_mac_f32 v13, v87, v99 
       v_mac_f32 v14, v87, v100 
       v_mac_f32 v15, v87, v101 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v22, v88, v98 
       v_mac_f32 v23, v88, v99 
       v_mac_f32 v24, v88, v100 
       v_mac_f32 v25, v88, v101 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v32, v89, v98 
       v_mac_f32 v33, v89, v99 
       v_mac_f32 v34, v89, v100 
       v_mac_f32 v35, v89, v101 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v52, v90, v94 
       v_mac_f32 v53, v90, v95 
       v_mac_f32 v54, v90, v96 
       v_mac_f32 v55, v90, v97 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v56, v91, v94 
       v_mac_f32 v57, v91, v95 
       v_mac_f32 v58, v91, v96 
       v_mac_f32 v59, v91, v97 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v60, v92, v94 
       v_mac_f32 v61, v92, v95 
       v_mac_f32 v62, v92, v96 
       v_mac_f32 v63, v92, v97 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v68, v93, v94 
       v_mac_f32 v69, v93, v95 
       v_mac_f32 v70, v93, v96 
       v_mac_f32 v71, v93, v97 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v40, v90, v98 
       v_mac_f32 v41, v90, v99 
       v_mac_f32 v42, v90, v100 
       v_mac_f32 v43, v90, v101 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v44, v91, v98 
       v_mac_f32 v45, v91, v99 
       v_mac_f32 v46, v91, v100 
       v_mac_f32 v47, v91, v101 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v48, v92, v98 
       v_mac_f32 v49, v92, v99 
       v_mac_f32 v50, v92, v100 
       v_mac_f32 v51, v92, v101 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v64, v93, v98 
       v_mac_f32 v65, v93, v99 
       v_mac_f32 v66, v93, v100 
       v_mac_f32 v67, v93, v101 
       
	;;#ASMEND
	;;#ASMSTART
	
     s_waitcnt lgkmcnt(0) 
     
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v6, v72, v80 
       v_mac_f32 v7, v72, v81 
       v_mac_f32 v8, v72, v82 
       v_mac_f32 v9, v72, v83 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v16, v73, v80 
       v_mac_f32 v17, v73, v81 
       v_mac_f32 v18, v73, v82 
       v_mac_f32 v19, v73, v83 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v26, v74, v80 
       v_mac_f32 v27, v74, v81 
       v_mac_f32 v28, v74, v82 
       v_mac_f32 v29, v74, v83 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v36, v75, v80 
       v_mac_f32 v37, v75, v81 
       v_mac_f32 v38, v75, v82 
       v_mac_f32 v39, v75, v83 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v2, v72, v102 
       v_mac_f32 v3, v72, v103 
       v_mac_f32 v4, v72, v104 
       v_mac_f32 v5, v72, v105 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v12, v73, v102 
       v_mac_f32 v13, v73, v103 
       v_mac_f32 v14, v73, v104 
       v_mac_f32 v15, v73, v105 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v22, v74, v102 
       v_mac_f32 v23, v74, v103 
       v_mac_f32 v24, v74, v104 
       v_mac_f32 v25, v74, v105 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v32, v75, v102 
       v_mac_f32 v33, v75, v103 
       v_mac_f32 v34, v75, v104 
       v_mac_f32 v35, v75, v105 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v52, v76, v80 
       v_mac_f32 v53, v76, v81 
       v_mac_f32 v54, v76, v82 
       v_mac_f32 v55, v76, v83 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v56, v77, v80 
       v_mac_f32 v57, v77, v81 
       v_mac_f32 v58, v77, v82 
       v_mac_f32 v59, v77, v83 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v60, v78, v80 
       v_mac_f32 v61, v78, v81 
       v_mac_f32 v62, v78, v82 
       v_mac_f32 v63, v78, v83 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v68, v79, v80 
       v_mac_f32 v69, v79, v81 
       v_mac_f32 v70, v79, v82 
       v_mac_f32 v71, v79, v83 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v40, v76, v102 
       v_mac_f32 v41, v76, v103 
       v_mac_f32 v42, v76, v104 
       v_mac_f32 v43, v76, v105 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v44, v77, v102 
       v_mac_f32 v45, v77, v103 
       v_mac_f32 v46, v77, v104 
       v_mac_f32 v47, v77, v105 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v48, v78, v102 
       v_mac_f32 v49, v78, v103 
       v_mac_f32 v50, v78, v104 
       v_mac_f32 v51, v78, v105 
       
	;;#ASMEND
	;;#ASMSTART
	
       v_mac_f32 v64, v79, v102 
       v_mac_f32 v65, v79, v103 
       v_mac_f32 v66, v79, v104 
       v_mac_f32 v67, v79, v105 
       
	;;#ASMEND
	;;#ASMSTART
	
     global_store_dwordx4 v[0:1], v[6:9], off 
     
	;;#ASMEND
	;;#ASMSTART
	
     global_store_dwordx4 v[0:1], v[2:5], off offset:16*4*4 
     
	;;#ASMEND
	v_mov_b32_e32 v0, s4
	s_addc_u32 s3, s1, 0
	v_mov_b32_e32 v109, s6
	v_mov_b32_e32 v1, s5
	s_add_u32 s0, s0, 0x10c000
	;;#ASMSTART
	
     global_store_dwordx4 v[10:11], v[16:19], off 
     
	;;#ASMEND
	;;#ASMSTART
	
     global_store_dwordx4 v[10:11], v[12:15], off offset:16*4*4 
     
	;;#ASMEND
	;;#ASMSTART
	
     global_store_dwordx4 v[20:21], v[26:29], off 
     
	;;#ASMEND
	;;#ASMSTART
	
     global_store_dwordx4 v[20:21], v[22:25], off offset:16*4*4 
     
	;;#ASMEND
	;;#ASMSTART
	
     global_store_dwordx4 v[30:31], v[36:39], off 
     
	;;#ASMEND
	;;#ASMSTART
	
     global_store_dwordx4 v[30:31], v[32:35], off offset:16*4*4 
     
	;;#ASMEND
	;;#ASMSTART
	
     global_store_dwordx4 v[109:110], v[52:55], off 
     
	;;#ASMEND
	;;#ASMSTART
	
     global_store_dwordx4 v[109:110], v[40:43], off offset:16*4*4 
     
	;;#ASMEND
	;;#ASMSTART
	
     global_store_dwordx4 v[0:1], v[56:59], off 
     
	;;#ASMEND
	;;#ASMSTART
	
     global_store_dwordx4 v[0:1], v[44:47], off offset:16*4*4 
     
	;;#ASMEND
	v_mov_b32_e32 v0, s2
	v_mov_b32_e32 v1, s3
	s_addc_u32 s1, s1, 0
	;;#ASMSTART
	
     global_store_dwordx4 v[0:1], v[60:63], off 
     
	;;#ASMEND
	;;#ASMSTART
	
     global_store_dwordx4 v[0:1], v[48:51], off offset:16*4*4 
     
	;;#ASMEND
	v_mov_b32_e32 v0, s0
	v_mov_b32_e32 v1, s1
	;;#ASMSTART
	
     global_store_dwordx4 v[0:1], v[68:71], off 
     
	;;#ASMEND
	;;#ASMSTART
	
     global_store_dwordx4 v[0:1], v[64:67], off offset:16*4*4 
     
	;;#ASMEND
	;;#ASMSTART
	
       s_waitcnt vmcnt(0) 
       
	;;#ASMEND
	s_endpgm
.Lfunc_end0:
	.size	_ZZ4mainEN67HIP_kernel_functor_name_begin_unnamed_HIP_kernel_functor_name_end_519__cxxamp_trampolineEPDv4_fS1_S1_PiS2_, .Lfunc_end0-_ZZ4mainEN67HIP_kernel_functor_name_begin_unnamed_HIP_kernel_functor_name_end_519__cxxamp_trampolineEPDv4_fS1_S1_PiS2_
                                        ; -- End function
	.section	.AMDGPU.csdata
; Kernel info:
; codeLenInByte = 9740
; NumSgprs: 17
; NumVgprs: 121
; ScratchSize: 0
; FloatMode: 192
; IeeeMode: 1
; LDSByteSize: 0 bytes/workgroup (compile time only)
; SGPRBlocks: 2
; VGPRBlocks: 30
; NumSGPRsForWavesPerEU: 17
; NumVGPRsForWavesPerEU: 121
; ReservedVGPRFirst: 0
; ReservedVGPRCount: 0
; COMPUTE_PGM_RSRC2:USER_SGPR: 6
; COMPUTE_PGM_RSRC2:TRAP_HANDLER: 1
; COMPUTE_PGM_RSRC2:TGID_X_EN: 1
; COMPUTE_PGM_RSRC2:TGID_Y_EN: 0
; COMPUTE_PGM_RSRC2:TGID_Z_EN: 0
; COMPUTE_PGM_RSRC2:TIDIG_COMP_CNT: 0

	.ident	"HCC clang version 6.0.0  (based on HCC 1.0.17412-f590a25-821e6d8-64e7fc7 )"
	.section	".note.GNU-stack"
	.amdgpu_code_object_metadata
---
Version:         [ 1, 0 ]
Kernels:         
  - Name:            _ZZ4mainEN67HIP_kernel_functor_name_begin_unnamed_HIP_kernel_functor_name_end_519__cxxamp_trampolineEPDv4_fS1_S1_PiS2_
    Language:        OpenCL C
    LanguageVersion: [ 2, 0 ]
    Args:            
      - Size:            8
        Align:           8
        ValueKind:       GlobalBuffer
        ValueType:       F32
        AddrSpaceQual:   Generic
      - Size:            8
        Align:           8
        ValueKind:       GlobalBuffer
        ValueType:       F32
        AddrSpaceQual:   Generic
      - Size:            8
        Align:           8
        ValueKind:       GlobalBuffer
        ValueType:       F32
        AddrSpaceQual:   Generic
      - Size:            8
        Align:           8
        ValueKind:       GlobalBuffer
        ValueType:       I32
        AddrSpaceQual:   Generic
      - Size:            8
        Align:           8
        ValueKind:       GlobalBuffer
        ValueType:       I32
        AddrSpaceQual:   Generic
      - Size:            8
        Align:           8
        ValueKind:       HiddenGlobalOffsetX
        ValueType:       I64
      - Size:            8
        Align:           8
        ValueKind:       HiddenGlobalOffsetY
        ValueType:       I64
      - Size:            8
        Align:           8
        ValueKind:       HiddenGlobalOffsetZ
        ValueType:       I64
    CodeProps:       
      KernargSegmentSize: 40
      WavefrontNumSGPRs: 17
      WorkitemNumVGPRs: 121
      KernargSegmentAlign: 4
      GroupSegmentAlign: 4
      PrivateSegmentAlign: 4
      WavefrontSize:   6
...
	.end_amdgpu_code_object_metadata
