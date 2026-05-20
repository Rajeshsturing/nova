
-- zamowienia
delete from Collections where IdCollection/1000=10172
truncate table n5zamowienie
truncate table n5pozzamowienie

-- sprzedaz
delete from Collections where IdCollection/1000=10129
truncate table n5sprzedaz
truncate table n5pozsprzedaz

-- zakup
delete from Collections where IdCollection/1000=10176
truncate table n5zakup
truncate table n5pozzakup

-- produkcja
delete from Collections where IdCollection/1000=10206
truncate table n5realprod
truncate table n5pozrealprod

delete from Collections where IdCollection/1000=10187
delete from n5zlecprod
truncate table n5pozzlecprod


delete from Collections where IdCollection/1000=10185
delete from n5recepta
truncate table n5pozrecepta
truncate table n5pozrecepta_oper
truncate table n5pozrecepta_zasob

-- inwentaryzacja
delete from Collections where IdCollection/1000=10290
truncate table n5inwark
truncate table n5pozinwark

-- magazyn
delete from Collections where IdCollection/1000=10162
truncate table n5dokmag
truncate table n5pozdokmag
truncate table n5pozdokmag_egz
truncate table n5gmop
truncate table n5gmop_arch
truncate table n5gmstan

-- naliczenia
delete from Collections where IdCollection/1000=10192
truncate table n5plnaliczenie
truncate table n5pldekret
truncate table n5plsklnal

-- umowy placowe
delete from Collections where IdCollection/1000=10202
truncate table n5plnieob
delete from Collections where IdCollection/1000=10201
truncate table n5plchoroba
delete from Collections where IdCollection/1000=10221
truncate table n5plpozostale

delete from Collections where IdCollection/1000=10199
delete from n5plumowa

truncate table n5plsklwyn
delete from  n5pllistaplac

-- platnosc
delete from Collections where IdCollection/1000=10150
truncate table n5platnosc
truncate table n5pozplatnosc
truncate table n5rapkas
truncate table n5ptop
truncate table n5ptstan

-- FK: ksiega g³ówna
delete from Collections where IdCollection/1000=10148
truncate table n5dowodksieg
truncate table n5dekret_sums
truncate table n5dekret
truncate table n5konto_budzet
delete from n5konto
update n5rejestrdok set pDefSchematdekr = 0
truncate table n5schematdekr

--transakcje
truncate table n5transakcja_operacja
delete from n5transakcja


-- eventlog
truncate table n5eventlog

-- !! usuwa wszystkie odwolania
truncate table n5pozrata
truncate table n5pozdok_zalacznik





--backup database navo2002 to disk='E:\__user_db_etc\tmp.sqkbak'
