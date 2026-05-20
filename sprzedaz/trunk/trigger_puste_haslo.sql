-- trigger zabezpieczajacy przed pustym haslem

use navo2002
go

create trigger n5uzytkownik_nonempty_password on n5uzytkownik
after insert, update
as
begin
if exists(select * from inserted where strHaslo ='')
begin
RAISERROR ('NAVO EB Trigger: Has³o nie mo¿e byæ puste.', 16, 1);
ROLLBACK TRANSACTION;
RETURN 
end 
end
go