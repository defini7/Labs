select *
from (
    select
        p.pass_id,
        p.surname,
        oc.birth_date
    from order_controls oc, orders o, persons p
    where oc.order_id = o.order_id
		and oc.pass_id = p.pass_id
		and oc.birth_date is not null
    group by p.pass_id, p.surname, oc.birth_date
    having count(distinct oc.order_id) > 1
    order by oc.birth_date desc
   	fetch first 1 row with ties
)
order by pass_id;