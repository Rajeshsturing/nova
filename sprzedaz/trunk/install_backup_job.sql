------------------------------------------------------------------
-- skrypt automatycznej archiwizacji
------------------------------------------------------------------
BEGIN TRANSACTION            
declare @param_sql_user_account nvarchar(64)
declare @param_sql_database nvarchar(64)
declare @param_backup_dir nvarchar(512)
declare @strTmp nvarchar(512)


------------------------------------------------------------------
-- PARAMETRY DO ZMIANY
------------------------------------------------------------------
select @param_sql_user_account = N'sa'
select @param_sql_database = N'navo2002'
select @param_backup_dir = N'C:\Program Files\NAVO Enterprise 2002\Archive' 
------------------------------------------------------------------
------------------------------------------------------------------
print 'starting script'

  DECLARE @JobID BINARY(16)  
  DECLARE @ReturnCode INT    
  SELECT @ReturnCode = 0     

IF (SELECT COUNT(*) FROM msdb.dbo.syscategories WHERE name = N'Database Maintenance') < 1 
  EXECUTE msdb.dbo.sp_add_category @name = N'Database Maintenance'

  -- Delete the job with the same name (if it exists)
  SELECT @JobID = job_id FROM   msdb.dbo.sysjobs WHERE (name = N'Zadanie archiwizacji w ramach ''Plan bezpieczenstwa''')       
  IF (@JobID IS NOT NULL)    
  BEGIN  
  -- Check if the job is a multi-server job  
  IF (EXISTS (SELECT  * 
              FROM    msdb.dbo.sysjobservers 
              WHERE   (job_id = @JobID) AND (server_id <> 0))) 
  BEGIN 
    -- There is, so abort the script 
    RAISERROR (N'Unable to import job ''Zadanie archiwizacji w ramach ''Plan bezpieczenstwa'''' since there is already a multi-server job with this name.', 16, 1) 
    GOTO QuitWithRollback  
  END 
  ELSE 
	print 'deleted exiting job zadanie archiwizacji'
    -- Delete the [local] job 
    EXECUTE msdb.dbo.sp_delete_job @job_name = N'Zadanie archiwizacji w ramach ''Plan bezpieczenstwa''' 
    SELECT @JobID = NULL
  END 

BEGIN 

  print 'adding job zadanie archiwizacji'
  EXECUTE @ReturnCode = msdb.dbo.sp_add_job @job_id = @JobID OUTPUT , @job_name = N'Zadanie archiwizacji w ramach ''Plan bezpieczenstwa''', 
	@owner_login_name = @param_sql_user_account, @description = N'No description available.', @category_name = N'Database Maintenance', @enabled = 1, @notify_level_email = 2, @notify_level_page = 0, @notify_level_netsend = 0, @notify_level_eventlog = 2, @delete_level= 0, @notify_email_operator_name = N''
  IF (@@ERROR <> 0 OR @ReturnCode <> 0) GOTO QuitWithRollback 

  -- Add the job steps
  -- -BkUpOnlyIfClean -CkDBRepair 
  select @strTmp  = N'EXECUTE master.dbo.xp_sqlmaint N''-D ' + @param_sql_database + 
	' -VrfyBackup  -BkUpMedia DISK ' +
	' -BkUpDB "' + @param_backup_dir + '" -DelBkUps 4WEEKS -CrBkSubDir -BkExt "BAK"'''
  EXECUTE @ReturnCode = msdb.dbo.sp_add_jobstep @job_id = @JobID, @step_id = 1, @step_name = N'Step 1', @command = @strTmp, 
	@database_name = N'master', @server = N'', @database_user_name = N'', @subsystem = N'TSQL', @cmdexec_success_code = 0, @flags = 4, @retry_attempts = 0, @retry_interval = 0, @output_file_name = N'', 
	@on_success_step_id = 0, @on_success_action = 1, @on_fail_step_id = 0, @on_fail_action = 2
  IF (@@ERROR <> 0 OR @ReturnCode <> 0) GOTO QuitWithRollback 
  EXECUTE @ReturnCode = msdb.dbo.sp_update_job @job_id = @JobID, @start_step_id = 1 

  IF (@@ERROR <> 0 OR @ReturnCode <> 0) GOTO QuitWithRollback 

  -- Add the job schedules
  EXECUTE @ReturnCode = msdb.dbo.sp_add_jobschedule @job_id = @JobID, @name = N'Schedule 1', @enabled = 1, @freq_type = 8, @active_start_date = 20030222, @active_start_time = 230000, @freq_interval = 62, @freq_subday_type = 1, @freq_subday_interval = 0, @freq_relative_interval = 0, @freq_recurrence_factor = 1, @active_end_date = 99991231, @active_end_time = 235959
  IF (@@ERROR <> 0 OR @ReturnCode <> 0) GOTO QuitWithRollback 

  -- Add the Target Servers
  EXECUTE @ReturnCode = msdb.dbo.sp_add_jobserver @job_id = @JobID, @server_name = N'(local)' 
  IF (@@ERROR <> 0 OR @ReturnCode <> 0) GOTO QuitWithRollback 

  print 'job zadanie archiwizacji added'
END

COMMIT TRANSACTION          
print 'script finished successfuly'

GOTO   EndSave              
QuitWithRollback:
  print 'script rolling back'
  IF (@@TRANCOUNT > 0) ROLLBACK TRANSACTION 
EndSave: 


go
