
-- skrypt uprawnienia dla raportu Produkty RP zalegaj¹ce
declare @idSodGroup int
set @idSodGroup = (select idobj from n5sodgroup where strNazwa = 'Raport - Magazyn - Inne')
insert into n5sod values ((select max(idobj)+1 from n5sod),1,'Produkty RP zalegaj¹ce',@idSodGroup,13921,0,'EB')
go

-- skrypt uprawnienia dla raportu Zlecenia produkcyjne niezrealizowane
declare @idSodGroup int
set @idSodGroup = (select idobj from n5sodgroup where strNazwa = 'Raport - Produkcja')
insert into n5sod values ((select max(idobj)+1 from n5sod),1,'Zlecenia produkcyjne niezrealizowane',@idSodGroup,13931,0,'EB')
go

