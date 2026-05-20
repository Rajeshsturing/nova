-- skrypt uprawnienia dla kreatora importu wyci¹gów bankowych
declare @idSodGroup int
set @idSodGroup = (select idobj from n5sodgroup where strNazwa = 'Operacja - Kreatory - EuroFinanse')
declare @maxSecId int
set @maxSecId = (select max(nSecId)+1 from n5sod where pSODGroup = @idSodGroup)
declare @maxIdSod int
set @maxIdSod = (select max(idobj)+1 from n5sod)
insert into n5sod values (@maxIdSod,1,'Importu wyci¹gów bankowych',@idSodGroup,1397,0,'EB')
go