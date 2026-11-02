drop table if exists route_repairs_copy;
drop table if exists repair_persons;

create temporary table route_repairs_copy
as select * from route_repairs;

create temporary table repair_persons as
select
	repair_id,
	unnest(person_ids) as pass_id
from route_repairs;

alter table repair_persons add primary key (repair_id, pass_id);

select * from repair_persons limit 20