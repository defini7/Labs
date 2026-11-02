select
	order_id,
	coalesce((select station_name from stations s where s.station_id = station_from_id), 'Неизвестная_станция')
	|| '_to_' ||
	coalesce((select station_name from stations s where s.station_id = station_to_id), 'Неизвестная_станция')
from orders
where exists (
	select 1 from dislocations d
	where d.station_id = station_from_id and d.cars_count between 10 and 40)
order by order_id