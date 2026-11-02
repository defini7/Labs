select station_id, count(*) over () as codes_count
from (
	select distinct station_id
	from station_road_info r
	where not exists (select 1 from stations s where s.station_id = r.station_id)
)
order by station_id;
