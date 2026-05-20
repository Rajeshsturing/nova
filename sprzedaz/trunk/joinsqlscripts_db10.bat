rem copying version SQL files - version 10
copy ".\create_tables_10.sql" + ".\custom_table_install.sql" ".\library\L50430_create_tbl.nxb"
copy ".\create_objects_10.sql" + ".\custom_install.sql" ".\library\L50450_create_obj.nxb"
copy ".\custom_drop.sql" + ".\drop_objects_10.sql" ".\library\L50470_drop.nxb"


pause
