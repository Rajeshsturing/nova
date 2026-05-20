
-- skrypt zarz¹dzania uprawnieniami do widocznoœci grup produktów w kartotece klienta
if not exists (select IdObj from n5sod where strNazwa = 'Widocznoœæ grup produktów')
begin
declare @idSodGroup int
set @idSodGroup = (select idobj from n5sodgroup where strNazwa = 'Operacje specjalne')
declare @maxIdSod int
set @maxIdSod = (select max(idobj)+1 from n5sod)
insert into n5sod values (@maxIdSod,1,'Widocznoœæ grup produktów',@idSodGroup,1200044,0,'EB')
end
go