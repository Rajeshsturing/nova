
-- uprawnienia Zakup Import us³ug
if not exists(select * from n5sodgroup where strNazwa = 'Obiekty typu: Zakup Import us³ug')
begin
	declare @maxIdSodGroup int
	set @maxIdSodGroup = (select max(idobj)+1 from n5sodgroup)

	-- id grupy 'Typy danych'
	declare @maxIdTypyDanych int
	set @maxIdTypyDanych = (select idobj from n5sodgroup where strNazwa = 'Typy danych')

	-- dodanie grupê 'Obiekty typu: Zakup Import us³ug'
	insert into n5sodgroup values (@maxIdSodGroup,1,'Obiekty typu: Zakup Import us³ug',@maxIdTypyDanych,'EB')

	-- kolejne uprawnienia
	declare @maxIdGroup int
	set @maxIdGroup = (select idobj from n5sodgroup where strNazwa = 'Obiekty typu: Zakup Import us³ug')
	declare @maxIdSod int
	set @maxIdSod = (select max(idobj) from n5sod)
	insert into n5sod values (@maxIdSod+1,1,'Odczyt',@maxIdGroup,309810001,0,'EB')
	insert into n5sod values (@maxIdSod+2,1,'Tworzenie',@maxIdGroup,309810002,0,'EB')
	insert into n5sod values (@maxIdSod+3,1,'Edycja',@maxIdGroup,309810003,0,'EB')
	insert into n5sod values (@maxIdSod+4,1,'Usuwanie',@maxIdGroup,309810004,0,'EB')
end
go

