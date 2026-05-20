-- diagnostyka transakcji, których suma jest niezgodna z transakcja-operacja
select 
'tr_idobj'= tr.IdObj, 
'tr_symb' = max(tr.strSymTrans),
'tr_data' = max(tr.dDataRozp),
'delta_wn' = sum(trop.trop_curWn) - max(tr.curWn), 
'delta_ma' = sum(trop.trop_curMa)-  max(tr.curMa),
'delta_wn_ewid' = sum(trop.trop_curWnEwid) - max(tr.curWnEwid), 
'delta_ma_ewid' = sum(trop.trop_curMaEwid)-  max(tr.curMaEwid)
from 
n5transakcja_operacja trop 
join n5transakcja tr on trop.trop_pTransakcja = tr.IdObj
group by tr.IdObj
having  
sum(trop.trop_curWn) <>  max(tr.curWn) or 
sum(trop.trop_curMa) <>  max(tr.curMa) or
sum(trop.trop_curWnEwid) <>  max(tr.curWnEwid) or 
sum(trop.trop_curMaEwid) <>  max(tr.curMaEwid)
order by 3,2

if (1=0)
begin
-- begin naprawa
update n5transakcja 
set 
curWn = isnull((select sum(trop_curWn) from n5transakcja_operacja where trop_pTransakcja = n5transakcja.IdObj),0),
curMa = isnull((select sum(trop_curMa) from n5transakcja_operacja where trop_pTransakcja = n5transakcja.IdObj),0),
curWnEwid = isnull((select sum(trop_curWnEwid) from n5transakcja_operacja where trop_pTransakcja = n5transakcja.IdObj),0),
curMaEwid = isnull((select sum(trop_curMaEwid) from n5transakcja_operacja where trop_pTransakcja = n5transakcja.IdObj),0)
-- end naprawa
end
