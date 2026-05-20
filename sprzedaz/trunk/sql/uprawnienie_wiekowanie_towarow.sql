
-- skrypt uprawnienia dla raportu Wiekowanie towarów
declare @idSodGroup int
set @idSodGroup = (select idobj from n5sodgroup where strNazwa = 'Raport - Magazyn - Inne')
insert into n5sod values ((select max(idobj)+1 from n5sod),1,'Wiekowanie towarow',@idSodGroup,13961,0,'EB')
go

