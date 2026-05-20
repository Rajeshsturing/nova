rem copying version SQL files - DB version 13

copy ".\create_tables_eb.sql" + ".\custom_table_install_13.sql" ".\library\L50433_create_tbl.nxb"
copy ".\create_objects_eb.sql" + ".\custom_install_13.sql" ".\library\L50453_create_obj.nxb"
copy ".\custom_drop_13.sql" + ".\drop_objects_eb.sql" ".\library\L50473_drop.nxb"

pause
