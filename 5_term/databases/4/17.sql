select route_id, array_agg(distinct person_id order by person_id) as person_ids
from route_repairs, unnest(person_ids) as person_id
where person_id is not null and person_id <> ''
group by route_id
having count(distinct person_id) > 1
order by route_id