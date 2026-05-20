use [navo2002]
go

-- uprawnienia do obiektu pojazd -----------------------------------------
declare @maxIdSodGroup int
set @maxIdSodGroup = (select max(idobj)+1 from n5sodgroup)
-- id grupy 'Typy danych'
declare @maxIdTypyDanych int
set @maxIdTypyDanych = (select idobj from n5sodgroup where strNazwa = 'Typy danych')
if not exists(select * from n5sodgroup where strNazwa = 'Obiekty typu: Pojazd')
begin
	-- dodanie grupy dla obiektu n5pojazd
	insert into n5sodgroup values (@maxIdSodGroup,1,'Obiekty typu: Pojazd',@maxIdTypyDanych,'EB')

	-- kolejne uprawnienia
	declare @maxIdGroup int
	set @maxIdGroup = (select idobj from n5sodgroup where strNazwa = 'Obiekty typu: Pojazd')
	declare @maxIdSod int
	set @maxIdSod = (select max(idobj) from n5sod)
	insert into n5sod values (@maxIdSod+1,1,'Odczyt',@maxIdGroup,102801,0,'EB')
	insert into n5sod values (@maxIdSod+2,1,'Tworzenie',@maxIdGroup,102802,0,'EB')
	insert into n5sod values (@maxIdSod+3,1,'Edycja',@maxIdGroup,102803,0,'EB')
	insert into n5sod values (@maxIdSod+4,1,'Usuwanie',@maxIdGroup,102804,0,'EB')
end
go
------------------------------------------------------
use navo2002
go
declare @idOpSpecGrp int
set @idOpSpecGrp = (select idobj from n5sodgroup where strNazwa = 'Operacje specjalne')

if not exists(select * from n5sod where strNazwa = 'Pokazuj ceny zakupu')
begin
	declare @maxIdSod int
	set @maxIdSod = (select max(idobj) from n5sod)
	insert into n5sod values (@maxIdSod+1,1, 'Pokazuj ceny zakupu', @idOpSpecGrp, 120035, 0, 'EB')
end
go
------------------------------------------------------
