-- NAVO Enterprise SQL script--
-- custom create tables script (DB11) ---

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
--============================================================
-- GM Archive support
--============================================================

create table n5gmop_arch
(
	IdObj integer not null,
	VersionId integer not null,
	gmo_eTypOp integer not null,
	gmo_nNumOp integer not null,
	gmo_nLP integer not null,
	gmo_curIlosc decimal(14,4) not null,
	gmo_curCena decimal(14,4) not null,
	gmo_curWartosc decimal(12,2) not null,
	gmo_pProd integer not null,
	gmo_pOpak integer not null,
	gmo_pMag integer not null,
	gmo_idDost integer not null,
	gmo_idDostLP integer not null,
	gmo_dDataWazn datetime not null,
	gmo_nNumOpRel integer not null,
	gmo_nLPRel integer not null,
	gmo_curPrzel decimal(12,2) not null
)
go