-- NAVO Enterprise SQL script--
-- upgrade DB14 to DB14a ---

use %DBNAME%
go

if exists (select * from sysobjects where name='ENUM_n5zakup_eTypZakup_53')
	alter table n5zakup drop constraint ENUM_n5zakup_eTypZakup_53
go

alter table n5zakup add constraint ENUM_n5zakup_eTypZakup_53 check (
eTypZakup between 0 and 6
)
go


if exists (select * from sysobjects where name='ENUM_n5rejestrdok_eTyp_3')
	alter table n5rejestrdok drop constraint ENUM_n5rejestrdok_eTyp_3
go
alter table n5rejestrdok add constraint ENUM_n5rejestrdok_eTyp_3 check (
eTyp between 0 and 66
)
go


-- uprawnienia Pit-4R
if not exists(select * from n5sodgroup where strNazwa = 'Obiekty typu: Pit 4R')
begin
	declare @maxIdSodGroup int
	set @maxIdSodGroup = (select max(idobj)+1 from n5sodgroup)

	-- id grupy 'Typy danych'
	declare @maxIdTypyDanych int
	set @maxIdTypyDanych = (select idobj from n5sodgroup where strNazwa = 'Typy danych')

	-- dodanie grupê 'Obiekty typu: Pit 4R'
	insert into n5sodgroup values (@maxIdSodGroup,1,'Obiekty typu: Pit 4R',@maxIdTypyDanych,'EB')

	-- kolejne uprawnienia
	declare @maxIdGroup int
	set @maxIdGroup = (select idobj from n5sodgroup where strNazwa = 'Obiekty typu: Pit 4R')
	declare @maxIdSod int
	set @maxIdSod = (select max(idobj) from n5sod)
	insert into n5sod values (@maxIdSod+1,1,'Odczyt',@maxIdGroup,102401,0,'EB')
	insert into n5sod values (@maxIdSod+2,1,'Tworzenie',@maxIdGroup,102402,0,'EB')
	insert into n5sod values (@maxIdSod+3,1,'Edycja',@maxIdGroup,102403,0,'EB')
	insert into n5sod values (@maxIdSod+4,1,'Usuwanie',@maxIdGroup,102404,0,'EB')
end
go

--- store current version detailed fix id
exec n2001_setprofile_value 1097, 'DB14-03'
go

raiserror('completed upgrade to DB14 (2019.02.06.00)',0,1)
go
