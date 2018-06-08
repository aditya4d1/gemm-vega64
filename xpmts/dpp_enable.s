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
		granulated_workitem_vgpr_count = 16
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
		workitem_vgpr_count = 67
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
	v_add_i32_e32 v1, vcc, s0, v7
	v_mov_b32_e32 v2, s1
	v_addc_u32_e32 v2, vcc, v2, v6, vcc
	flat_load_dwordx4 v[1:4], v[1:2]
	v_add_i32_e32 v8, vcc, 0x1000, v7
	v_add_i32_e32 v5, vcc, s2, v7
	v_mov_b32_e32 v9, s3
	v_addc_u32_e32 v6, vcc, v9, v6, vcc
	v_and_b32_e32 v9, 1, v0
	v_lshlrev_b32_e32 v9, 4, v9
	v_bfe_u32 v10, v0, 1, 3
	v_or_b32_e32 v9, v9, v10
	v_and_b32_e32 v11, 0xf0, v0
	v_add_i32_e32 v10, vcc, 0x1000, v11
	v_lshlrev_b32_e32 v9, 4, v9
	v_add_i32_e32 v11, vcc, 0x1100, v11
	s_load_dwordx2 s[4:5], s[4:5], 0x10
	v_lshlrev_b32_e32 v0, 8, v0
	s_waitcnt lgkmcnt(0)
	v_add_i32_e32 v65, vcc, s4, v0
	v_mov_b32_e32 v0, s5
	v_addc_u32_e32 v66, vcc, 0, v0, vcc
	s_waitcnt vmcnt(0)
	ds_write2_b64 v8, v[1:2], v[3:4] offset1:1
	flat_load_dwordx4 v[1:4], v[5:6]
	s_waitcnt vmcnt(0) lgkmcnt(0)
	ds_write2_b64 v7, v[1:2], v[3:4] offset1:1
	s_waitcnt lgkmcnt(0)
	s_barrier
	ds_read2_b64 v[1:4], v10 offset1:1
	ds_read2_b64 v[5:8], v11 offset1:1
	ds_read2_b64 v[9:12], v9 offset1:1
	s_waitcnt lgkmcnt(0)
	s_barrier
	;;#ASMSTART
	
    v_mac_f32_dpp v13, v1, v9 quad_perm:[0,0,2,2] 
    v_mac_f32_dpp v14, v1, v10 quad_perm:[0,0,2,2] 
    v_mac_f32_dpp v15, v1, v11 quad_perm:[0,0,2,2] 
    v_mac_f32_dpp v16, v1, v12 quad_perm:[0,0,2,2] 
    
     v_mac_f32_dpp v17, v1, v9 quad_perm:[1,1,3,3] 
    v_mac_f32_dpp v18, v1, v10 quad_perm:[1,1,3,3] 
    v_mac_f32_dpp v19, v1, v11 quad_perm:[1,1,3,3] 
    v_mac_f32_dpp v20, v1, v12 quad_perm:[1,1,3,3] 
    
	;;#ASMEND
	;;#ASMSTART
	
    v_mac_f32_dpp v21, v2, v9 quad_perm:[0,0,2,2] 
    v_mac_f32_dpp v22, v2, v10 quad_perm:[0,0,2,2] 
    v_mac_f32_dpp v23, v2, v11 quad_perm:[0,0,2,2] 
    v_mac_f32_dpp v24, v2, v12 quad_perm:[0,0,2,2] 
        v_mac_f32_dpp v25, v2, v9 quad_perm:[1,1,3,3] 
    v_mac_f32_dpp v26, v2, v10 quad_perm:[1,1,3,3] 
    v_mac_f32_dpp v27, v2, v11 quad_perm:[1,1,3,3] 
    v_mac_f32_dpp v28, v2, v12 quad_perm:[1,1,3,3] 
    
	;;#ASMEND
	;;#ASMSTART
	
    v_mac_f32_dpp v0, v3, v9 quad_perm:[0,0,2,2] 
    v_mac_f32_dpp v1, v3, v10 quad_perm:[0,0,2,2] 
    v_mac_f32_dpp v2, v3, v11 quad_perm:[0,0,2,2] 
    v_mac_f32_dpp v3, v3, v12 quad_perm:[0,0,2,2] 
        v_mac_f32_dpp v29, v3, v9 quad_perm:[1,1,3,3] 
    v_mac_f32_dpp v30, v3, v10 quad_perm:[1,1,3,3] 
    v_mac_f32_dpp v31, v3, v11 quad_perm:[1,1,3,3] 
    v_mac_f32_dpp v32, v3, v12 quad_perm:[1,1,3,3] 
    
	;;#ASMEND
	;;#ASMSTART
	
    v_mac_f32_dpp v33, v4, v9 quad_perm:[0,0,2,2] 
    v_mac_f32_dpp v34, v4, v10 quad_perm:[0,0,2,2] 
    v_mac_f32_dpp v35, v4, v11 quad_perm:[0,0,2,2] 
    v_mac_f32_dpp v36, v4, v12 quad_perm:[0,0,2,2] 
        v_mac_f32_dpp v37, v4, v9 quad_perm:[1,1,3,3] 
    v_mac_f32_dpp v38, v4, v10 quad_perm:[1,1,3,3] 
    v_mac_f32_dpp v39, v4, v11 quad_perm:[1,1,3,3] 
    v_mac_f32_dpp v40, v4, v12 quad_perm:[1,1,3,3] 
    
	;;#ASMEND
	;;#ASMSTART
	
    v_mac_f32_dpp v41, v5, v9 quad_perm:[0,0,2,2] 
    v_mac_f32_dpp v42, v5, v10 quad_perm:[0,0,2,2] 
    v_mac_f32_dpp v43, v5, v11 quad_perm:[0,0,2,2] 
    v_mac_f32_dpp v44, v5, v12 quad_perm:[0,0,2,2] 
        v_mac_f32_dpp v45, v5, v9 quad_perm:[1,1,3,3] 
    v_mac_f32_dpp v46, v5, v10 quad_perm:[1,1,3,3] 
    v_mac_f32_dpp v47, v5, v11 quad_perm:[1,1,3,3] 
    v_mac_f32_dpp v48, v5, v12 quad_perm:[1,1,3,3] 
    
	;;#ASMEND
	;;#ASMSTART
	
    v_mac_f32_dpp v49, v6, v9 quad_perm:[0,0,2,2] 
    v_mac_f32_dpp v50, v6, v10 quad_perm:[0,0,2,2] 
    v_mac_f32_dpp v51, v6, v11 quad_perm:[0,0,2,2] 
    v_mac_f32_dpp v52, v6, v12 quad_perm:[0,0,2,2] 
        v_mac_f32_dpp v53, v6, v9 quad_perm:[1,1,3,3] 
    v_mac_f32_dpp v54, v6, v10 quad_perm:[1,1,3,3] 
    v_mac_f32_dpp v55, v6, v11 quad_perm:[1,1,3,3] 
    v_mac_f32_dpp v56, v6, v12 quad_perm:[1,1,3,3] 
    
	;;#ASMEND
	;;#ASMSTART
	
    v_mac_f32_dpp v4, v7, v9 quad_perm:[0,0,2,2] 
    v_mac_f32_dpp v5, v7, v10 quad_perm:[0,0,2,2] 
    v_mac_f32_dpp v6, v7, v11 quad_perm:[0,0,2,2] 
    v_mac_f32_dpp v7, v7, v12 quad_perm:[0,0,2,2] 
        v_mac_f32_dpp v57, v7, v9 quad_perm:[1,1,3,3] 
    v_mac_f32_dpp v58, v7, v10 quad_perm:[1,1,3,3] 
    v_mac_f32_dpp v59, v7, v11 quad_perm:[1,1,3,3] 
    v_mac_f32_dpp v60, v7, v12 quad_perm:[1,1,3,3] 
    
	;;#ASMEND
	;;#ASMSTART
	
    v_mac_f32_dpp v8, v8, v9 quad_perm:[0,0,2,2] 
    v_mac_f32_dpp v9, v8, v10 quad_perm:[0,0,2,2] 
    v_mac_f32_dpp v10, v8, v11 quad_perm:[0,0,2,2] 
    v_mac_f32_dpp v11, v8, v12 quad_perm:[0,0,2,2] 
        v_mac_f32_dpp v61, v8, v9 quad_perm:[1,1,3,3] 
    v_mac_f32_dpp v62, v8, v10 quad_perm:[1,1,3,3] 
    v_mac_f32_dpp v63, v8, v11 quad_perm:[1,1,3,3] 
    v_mac_f32_dpp v64, v8, v12 quad_perm:[1,1,3,3] 
    
	;;#ASMEND
	flat_store_dwordx4 v[65:66], v[13:16]
	flat_store_dwordx4 v[65:66], v[21:24] offset:16
	flat_store_dwordx4 v[65:66], v[0:3] offset:32
	flat_store_dwordx4 v[65:66], v[33:36] offset:48
	flat_store_dwordx4 v[65:66], v[17:20] offset:64
	flat_store_dwordx4 v[65:66], v[25:28] offset:80
	flat_store_dwordx4 v[65:66], v[29:32] offset:96
	flat_store_dwordx4 v[65:66], v[37:40] offset:112
	flat_store_dwordx4 v[65:66], v[41:44] offset:128
	flat_store_dwordx4 v[65:66], v[49:52] offset:144
	flat_store_dwordx4 v[65:66], v[4:7] offset:160
	flat_store_dwordx4 v[65:66], v[8:11] offset:176
	flat_store_dwordx4 v[65:66], v[45:48] offset:192
	flat_store_dwordx4 v[65:66], v[53:56] offset:208
	flat_store_dwordx4 v[65:66], v[57:60] offset:224
	flat_store_dwordx4 v[65:66], v[61:64] offset:240
	s_endpgm
.Lfunc_end0:
	.size	_ZZ4mainEN67HIP_kernel_functor_name_begin_unnamed_HIP_kernel_functor_name_end_319__cxxamp_trampolineEPDv4_fS1_S1_, .Lfunc_end0-_ZZ4mainEN67HIP_kernel_functor_name_begin_unnamed_HIP_kernel_functor_name_end_319__cxxamp_trampolineEPDv4_fS1_S1_
                                        ; -- End function
	.section	.AMDGPU.csdata
; Kernel info:
; codeLenInByte = 864
; NumSgprs: 8
; NumVgprs: 67
; ScratchSize: 0
; FloatMode: 192
; IeeeMode: 1
; LDSByteSize: 8192 bytes/workgroup (compile time only)
; SGPRBlocks: 0
; VGPRBlocks: 16
; NumSGPRsForWavesPerEU: 8
; NumVGPRsForWavesPerEU: 67
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
  - Name:            _ZZ4mainEN67HIP_kernel_functor_name_begin_unnamed_HIP_kernel_functor_name_end_319__cxxamp_trampolineEPDv4_fS1_S1_
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
      KernargSegmentSize: 24
      WorkgroupGroupSegmentSize: 8192
      WavefrontNumSGPRs: 8
      WorkitemNumVGPRs: 67
      KernargSegmentAlign: 4
      GroupSegmentAlign: 4
      PrivateSegmentAlign: 4
      WavefrontSize:   6
...
	.end_amdgpu_code_object_metadata
