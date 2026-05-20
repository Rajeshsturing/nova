rem copying version SQL files - DB version 12

copy ".\create_tables_eb.sql" + ".\custom_table_install_12.sql" ".\library\L50432_create_tbl.nxb"
copy ".\create_objects_eb.sql" + ".\custom_install_12.sql" ".\library\L50452_create_obj.nxb"
copy ".\custom_drop_12.sql" + ".\drop_objects_eb.sql" ".\library\L50472_drop.nxb"

pause
