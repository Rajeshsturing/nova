rem copying version SQL files - DB version 11

copy ".\create_tables_eb.sql" + ".\custom_table_install_11.sql" ".\library\L50431_create_tbl.nxb"
copy ".\create_objects_eb.sql" + ".\custom_install_11.sql" ".\library\L50451_create_obj.nxb"
copy ".\custom_drop_11.sql" + ".\drop_objects_eb.sql" ".\library\L50471_drop.nxb"

pause
