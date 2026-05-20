
-- uprawnienia do obiektu n5ankieta_toral -----------------------------------------
declare @maxIdSodGroup int
set @maxIdSodGroup = (select max(idobj)+1 from n5sodgroup)
-- id grupy 'Typy danych'
declare @maxIdTypyDanych int
set @maxIdTypyDanych = (select idobj from n5sodgroup where strNazwa = 'Typy danych')
if not exists(select * from n5sodgroup where strNazwa = 'Obiekty typu: Ankieta')
begin
	-- dodanie grupy dla obiektu n5ankieta_toral
	insert into n5sodgroup values (@maxIdSodGroup,1,'Obiekty typu: Ankieta',@maxIdTypyDanych,'EB')

	-- kolejne uprawnienia
	declare @maxIdGroup int
	set @maxIdGroup = (select idobj from n5sodgroup where strNazwa = 'Obiekty typu: Ankieta')
	declare @maxIdSod int
	set @maxIdSod = (select max(idobj) from n5sod)
	insert into n5sod values (@maxIdSod+1,1,'Odczyt',@maxIdGroup,102861,0,'EB')
	insert into n5sod values (@maxIdSod+2,1,'Tworzenie',@maxIdGroup,102862,0,'EB')
	insert into n5sod values (@maxIdSod+3,1,'Edycja',@maxIdGroup,102863,0,'EB')
	insert into n5sod values (@maxIdSod+4,1,'Usuwanie',@maxIdGroup,102864,0,'EB')
end
go
------------------------------------------------------

-- uprawnienia do obiektu n5pozankieta_toral -----------------------------------------
declare @maxIdSodGroup int
set @maxIdSodGroup = (select max(idobj)+1 from n5sodgroup)
-- id grupy 'Typy danych'
declare @maxIdTypyDanych int
set @maxIdTypyDanych = (select idobj from n5sodgroup where strNazwa = 'Typy danych')
if not exists(select * from n5sodgroup where strNazwa = 'Obiekty typu: Pozycja ankiety')
begin
	-- dodanie grupy dla obiektu n5pozankieta_toral
	insert into n5sodgroup values (@maxIdSodGroup,1,'Obiekty typu: Pozycja ankiety',@maxIdTypyDanych,'EB')

	-- kolejne uprawnienia
	declare @maxIdGroup int
	set @maxIdGroup = (select idobj from n5sodgroup where strNazwa = 'Obiekty typu: Pozycja ankiety')
	declare @maxIdSod int
	set @maxIdSod = (select max(idobj) from n5sod)
	insert into n5sod values (@maxIdSod+1,1,'Odczyt',@maxIdGroup,102871,0,'EB')
	insert into n5sod values (@maxIdSod+2,1,'Tworzenie',@maxIdGroup,102872,0,'EB')
	insert into n5sod values (@maxIdSod+3,1,'Edycja',@maxIdGroup,102873,0,'EB')
	insert into n5sod values (@maxIdSod+4,1,'Usuwanie',@maxIdGroup,102874,0,'EB')
end
go
------------------------------------------------------

-- uprawnienia do obiektu n5maszyna_toral -----------------------------------------
declare @maxIdSodGroup int
set @maxIdSodGroup = (select max(idobj)+1 from n5sodgroup)
-- id grupy 'Typy danych'
declare @maxIdTypyDanych int
set @maxIdTypyDanych = (select idobj from n5sodgroup where strNazwa = 'Typy danych')
if not exists(select * from n5sodgroup where strNazwa = 'Obiekty typu: Maszyna')
begin
	-- dodanie grupy dla obiektu n5maszyna_toral
	insert into n5sodgroup values (@maxIdSodGroup,1,'Obiekty typu: Maszyna',@maxIdTypyDanych,'EB')

	-- kolejne uprawnienia
	declare @maxIdGroup int
	set @maxIdGroup = (select idobj from n5sodgroup where strNazwa = 'Obiekty typu: Maszyna')
	declare @maxIdSod int
	set @maxIdSod = (select max(idobj) from n5sod)
	insert into n5sod values (@maxIdSod+1,1,'Odczyt',@maxIdGroup,102881,0,'EB')
	insert into n5sod values (@maxIdSod+2,1,'Tworzenie',@maxIdGroup,102882,0,'EB')
	insert into n5sod values (@maxIdSod+3,1,'Edycja',@maxIdGroup,102883,0,'EB')
	insert into n5sod values (@maxIdSod+4,1,'Usuwanie',@maxIdGroup,102884,0,'EB')
end
go
------------------------------------------------------