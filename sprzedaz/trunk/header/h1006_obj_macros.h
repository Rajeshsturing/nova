#macro XDF_EXTRAS_OBJ(_obj_)							\
	<embedded>											\
		<name>_obj_##strExtra1</name>					\	
		<sqltype>SQLvc32</sqltype>						\
		<humanname>strExtra1</humanname>				\
	</embedded>											\
	<embedded>											\
		<name>_obj_##strExtra2</name>					\	
		<sqltype>SQLvc128</sqltype>						\
		<humanname>strExtra2</humanname>				\
	</embedded>											\
	<embedded>											\
		<name>_obj_##dExtra3</name>						\
		<sqltype>SQLdate</sqltype>						\
		<humanname>dExtra3</humanname>					\
		<default>null</default>							\
	</embedded>											\
	<embedded>											\
		<name>_obj_##curExtra4</name>					\
		<sqltype>SQLcurrency</sqltype>					\
		<humanname>curExtra4</humanname>				\
	</embedded>											\
	<embedded>											\
		<name>_obj_##curExtra5</name>					\
		<sqltype>SQLcurrency</sqltype>					\
		<humanname>curExtra5</humanname>				\
	</embedded>											\
	<ref>												\
		<name>_obj_##pKwalifikatorEx</name>				\
		<humanname>Kwalifikator</humanname>				\
		<typeid>TYPEID_N5KWALIFIKATOR</typeid>			\
		<optional/>										\
	</ref>	




#macro XDF_NRDOK_OBJ(_obj_)								\
	<embedded>											\
		<name>_obj_##strNrDok</name>					\
		<sqltype>SQLvc32</sqltype>						\
		<humanname>Numer dokumentu</humanname>			\
		<unique/>										\
	</embedded>






#macro XDF_REJDOWSCHEM_OBJ(_obj_)						\
	<ref>												\
		<name>_obj_##pRejestrDok</name>					\
		<humanname>Rejestr dokumentów</humanname>		\
		<typeid>TYPEID_N5REJESTRDOK</typeid>			\
	</ref>												\
	<ref>												\
		<name>_obj_##pDowodKsieg</name>					\
		<humanname>Dowód ksiegowy</humanname>			\
		<typeid>TYPEID_N5DOWODKSIEG</typeid>			\
		<optional/>										\
	</ref>												\
	<ref>												\
		<name>_obj_##pSchematDekr</name>				\
		<humanname>Schemat dekretacji</humanname>		\
		<typeid>TYPEID_N5SCHEMATDEKR</typeid>			\
		<optional/>										\
	</ref>