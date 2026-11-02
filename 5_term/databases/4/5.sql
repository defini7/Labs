create table routes_copy
as (select * from routes)

update routes_copy r
set avg_cost_rub = round(1.35 * r.avg_cost_rub / 1000) * 1000
where r.station_from_id in (
	select station_id from stations
	where min_cars > 0
)