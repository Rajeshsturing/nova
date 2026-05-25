/*
	NAVO Enterprise 2020
	setup application

	error codes
*/

#ifndef _SETUPERRORS_H_
#define _SETUPERRORS_H_

enum setuperror
{
	stpe_ok					= 0,
	stpe_not_enough_rights	= 1,
	stpe_syschk_bad_clsid	= 2,
	stpe_syschk_bad_progid	= 3,
	stpe_cant_read_param	= 4,
	stpe_cant_write_param	= 5,
	stpe_param_corrupted	= 6,
	stpe_user_break			= 7,
	stpe_bad_cmd_line		= 8,
	stpe_comobj_check_fail	= 9,
	stpe_restart_required	= 10,
	stpe_internal_error		= 11,
	stpe_appdb_create_fail	= 12,
	stpe_appdb_init_fail	= 13,
	stpe_appdb_unpack_fail	= 14,
	stpe_file_copy_failed	= 15,
	stpe_register_failed	= 16,
	stpe_openservice_failed	= 17,
	stpe_startservice_failed= 18,
	stpe_stopservice_failed = 19,
	stpe_getstateservice_fail=20,
	stpe_unable_2_open_file	= 21,
	stpe_download_failed	= 22,
	stpe_file_size_incorrect= 23,
	stpe_appdbman_create_fail=24,
	stpe_registry_write_fail= 25,
	stpe_finished			= 26,
	stpe_bad_monitor_command= 27,
	stpe_monitor_failed     = 28,
	stpe_file_not_found     = 29,
	stpe_not_enough_disk_spc= 30,
	stpe_dotnetregister_failed=31,
};

#else
	#error __FILE__ already included
#endif
