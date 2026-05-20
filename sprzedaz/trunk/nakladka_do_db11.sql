-- nazwa bazy danych
use [navo2002]
go

-- gm_archive ------------------------------------------------------------------
if not exists(select * from n5globprof where indeks = 1086)
	exec n2001_setprofile_value 1086, 0
go


-- kolejny nr p³atnoœci - FIFO w platnoœciach ----------------------------------
if not exists(select * from n5globprof where indeks = 1092)
	exec n2001_setprofile_value 1092, 0
go


-- uprawnienia do n5transakcja_operacja -----------------------------------------
-- max idSodGroup
declare @maxIdSodGroup int
set @maxIdSodGroup = (select max(idobj)+1 from n5sodgroup)
-- id grupy 'Typy danych'
declare @maxIdTypyDanych int
set @maxIdTypyDanych = (select idobj from n5sodgroup where strNazwa = 'Typy danych')
if not exists(select * from n5sodgroup where strNazwa = 'Obiekty typu: Transakcja operacja')
begin
	-- dodanie grupy dla obiektu n5transakcja
	insert into n5sodgroup values (@maxIdSodGroup,1,'Obiekty typu: Transakcja operacja',@maxIdTypyDanych,'EB')

	-- kolejne uprawnienia
	declare @maxIdGroup int
	set @maxIdGroup = (select idobj from n5sodgroup where strNazwa = 'Obiekty typu: Transakcja operacja')
	declare @maxIdSod int
	set @maxIdSod = (select max(idobj) from n5sod)
	insert into n5sod values (@maxIdSod+1,1,'Odczyt',@maxIdGroup,102521,0,'EB')
	insert into n5sod values (@maxIdSod+2,1,'Tworzenie',@maxIdGroup,102522,0,'EB')
	insert into n5sod values (@maxIdSod+3,1,'Edycja',@maxIdGroup,102523,0,'EB')
	insert into n5sod values (@maxIdSod+4,1,'Usuwanie',@maxIdGroup,102524,0,'EB')
end
go

-- uprawnienia do status dokumentu -----------------------------------------
declare @maxIdSodGroup int
set @maxIdSodGroup = (select max(idobj)+1 from n5sodgroup)
-- id grupy 'Typy danych'
declare @maxIdTypyDanych int
set @maxIdTypyDanych = (select idobj from n5sodgroup where strNazwa = 'Typy danych')
if not exists(select * from n5sodgroup where strNazwa = 'Obiekty typu: Status dokumentu')
begin
	-- dodanie grupy dla obiektu n5transakcja
	insert into n5sodgroup values (@maxIdSodGroup,1,'Obiekty typu: Status dokumentu',@maxIdTypyDanych,'EB')

	-- kolejne uprawnienia
	declare @maxIdGroup int
	set @maxIdGroup = (select idobj from n5sodgroup where strNazwa = 'Obiekty typu: Status dokumentu')
	declare @maxIdSod int
	set @maxIdSod = (select max(idobj) from n5sod)
	insert into n5sod values (@maxIdSod+1,1,'Odczyt',@maxIdGroup,102771,0,'EB')
	insert into n5sod values (@maxIdSod+2,1,'Tworzenie',@maxIdGroup,102772,0,'EB')
	insert into n5sod values (@maxIdSod+3,1,'Edycja',@maxIdGroup,102773,0,'EB')
	insert into n5sod values (@maxIdSod+4,1,'Usuwanie',@maxIdGroup,102774,0,'EB')
end
go

-- naprawa b³êdu, ¿e stare zlecenia produkcyjne (z przed upgrade bazy) siê nie realizuj¹
update n5zlecprod set zlp_eStatus = 1 where zlp_eStatus = 0
go

-- uprawnienia do pit4r   -----------------------------------------
declare @maxIdSodGroup int
set @maxIdSodGroup = (select max(idobj)+1 from n5sodgroup)
-- id grupy 'Typy danych'
declare @maxIdTypyDanych int
set @maxIdTypyDanych = (select idobj from n5sodgroup where strNazwa = 'Typy danych')
if not exists(select * from n5sodgroup where strNazwa = 'Obiekty typu: Pit 4r')
begin
	-- dodanie grupy dla obiektu n5transakcja
	insert into n5sodgroup values (@maxIdSodGroup,1,'Obiekty typu: Pit 4r',@maxIdTypyDanych,'EB')

	-- kolejne uprawnienia
	declare @maxIdGroup int
	set @maxIdGroup = (select idobj from n5sodgroup where strNazwa = 'Obiekty typu: Pit 4r')
	declare @maxIdSod int
	set @maxIdSod = (select max(idobj) from n5sod)
	insert into n5sod values (@maxIdSod+1,1,'Odczyt',@maxIdGroup,102401,0,'EB')
	insert into n5sod values (@maxIdSod+2,1,'Tworzenie',@maxIdGroup,102402,0,'EB')
	insert into n5sod values (@maxIdSod+3,1,'Edycja',@maxIdGroup,102403,0,'EB')
	insert into n5sod values (@maxIdSod+4,1,'Usuwanie',@maxIdGroup,102404,0,'EB')
end
go