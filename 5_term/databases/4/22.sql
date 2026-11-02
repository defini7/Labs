create temporary table temp_routes_ref (
    route_id bigint primary key
) on commit drop;

insert into temp_routes_ref (route_id)
select route_id from routes;

create temporary table repair_summary (
    route_id bigint primary key,
    repair_count integer not null,
    total_cost numeric(16,2) not null default 0,
    limit_rub numeric(16,2) not null default 10000 check (limit_rub >= 0),
    excess_rub numeric(16,2) generated always as (
        greatest(total_cost - limit_rub, 0)
    ) stored,
	
    constraint fk_repair_summary_route 
        foreign key (route_id) 
        references temp_routes_ref(route_id) 
        on delete cascade
) on commit drop;

insert into repair_summary (route_id, repair_count, total_cost)
select 
    r.route_id,
    (select count(*) from route_repairs rp where rp.route_id = r.route_id),
    (select coalesce(sum(rp.price_rub), 0) from route_repairs rp where rp.route_id = r.route_id)
from routes r
where (select count(*) from route_repairs rp where rp.route_id = r.route_id) >= 3;

update repair_summary
set limit_rub = limit_rub * 0.8
where total_cost > (select avg(total_cost) from repair_summary);

select 
    route_id,
    repair_count,
    total_cost,
    limit_rub,
    excess_rub
from repair_summary
order by 
    excess_rub desc, 
    route_id asc;