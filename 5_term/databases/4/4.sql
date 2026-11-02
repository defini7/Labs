/*create table no_loaded_cars as (
select
	cars_count, car_type_id, wait_time_range,
	period_number, station_id
from dislocations
where is_loaded is null or is_loaded = false)*/

select car_type_id, station_id, period_number, count(*)
from no_loaded_cars
group by car_type_id, station_id, period_number
having count(*) > 1