
-- uprwnienie wy³¹czania wyliczania stanu sprzeda¿y na zamówieniu obcym (abakosteel)
if not exists (select idobj from n5sod where strNazwa = 'Wy³¹czenie wyliczania stanu sprzeda¿y na zamówieniu obcym')
begin
	declare @idSodGroup int
	set @idSodGroup = (select idobj from n5sodgroup where strNazwa = 'Operacje specjalne')
	declare @maxSecId int
	set @maxSecId = (select max(nSecId)+1 from n5sod where pSODGroup = 230)
	declare @maxIdSod int
	set @maxIdSod = (select max(idobj)+1 from n5sod)
	insert into n5sod values (@maxIdSod,1,'Wy³¹czenie wyliczania stanu sprzeda¿y na zamówieniu obcym',@idSodGroup,@maxSecId,0,'EB')
end
go