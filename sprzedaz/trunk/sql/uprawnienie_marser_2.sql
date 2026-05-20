

-- skrypt uprawnienia dla raportu MARSER 2
declare @idSodGroup int
set @idSodGroup = (select idobj from n5sodgroup where strNazwa = 'Raport')
declare @maxSecId int
set @maxSecId = (select max(nSecId)+1 from n5sod where pSODGroup = @idSodGroup)
declare @maxIdSod int
set @maxIdSod = (select max(idobj)+1 from n5sod)
insert into n5sod values (@maxIdSod,1,'MARSER 2',@idSodGroup,13871,0,'EB')
go

