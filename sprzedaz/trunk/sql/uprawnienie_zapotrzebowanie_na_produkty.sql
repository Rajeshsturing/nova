-- skrypt uprawnienia dla raportu Zapotrzebowanie na produkty
if not exists (select 1 from n5sod where strNazwa = 'Zapotrzebowanie na produkty')
begin
	declare @idSodGroup int
	set @idSodGroup = (select idobj from n5sodgroup where strNazwa = 'Raport - Magazyn - Inne')
	insert into n5sod values ((select max(idobj)+1 from n5sod),1,'Zapotrzebowanie na produkty',@idSodGroup,14011,0,'EB')
end
go