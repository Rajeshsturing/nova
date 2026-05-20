raiserror('starting upgrade to DB13B (2018.03.27)',0,1)
go

use %DBNAME%
go

---------------------------------------------------------------------------------
-- funkcja lex
---------------------------------------------------------------------------------
-- nx_lex_order ??

---------------------------------------------------------------------------------
-- nowy zakres wartosci eTypZakup w n5zakup
---------------------------------------------------------------------------------

if exists (select * from sysobjects where name='ENUM_n5zakup_eTypZakup_53')
	alter table n5zakup drop constraint ENUM_n5zakup_eTypZakup_53
go

alter table n5zakup add constraint ENUM_n5zakup_eTypZakup_53 check (
eTypZakup between 0 and 5
)
go

---------------------------------------------------------------------------------
-- ### manually always at end
---------------------------------------------------------------------------------

n2001_makegrants 'navo2002user'
go

raiserror('completed upgrade to DB13 (2018.03.27)',0,1)
go
