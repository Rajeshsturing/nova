-- NAVO Enterprise SQL script--
-- custom create tables script ---
use %DBNAME%
go

create table n5dekret_sums
(
	pKonto integer not null,
	curWn decimal(12,2) not null,
	curMa decimal(12,2) not null,
	dDataKsieg datetime not null,
	eTyp integer not null,
	eStatus integer not null,
	pKwalifikator integer not null
)
go
