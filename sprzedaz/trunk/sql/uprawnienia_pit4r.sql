
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