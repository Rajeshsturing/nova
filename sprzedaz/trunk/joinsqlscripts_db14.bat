rem copying version SQL files - DB version 14

copy ".\create_tables_auto_14.sql" + ".\custom_table_install_14.sql" ".\library\L50434_create_tbl.nxb"
copy ".\create_objects_auto_14.sql" + ".\custom_install_13.sql" + ".\custom_install_14.sql" ".\library\L50454_create_obj.nxb"
copy ".\custom_drop_14.sql" + ".\drop_objects_auto_14.sql" ".\library\L50474_drop.nxb"

pause
