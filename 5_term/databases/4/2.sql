select
	station_id, station_name, max_cars,
	case
		when (select max(max_cars) from stations) = (select min(max_cars) from stations) then 'мин. и макс.'
		when max_cars = (select max(max_cars) from stations) then 'макс.'
		when max_cars = (select min(max_cars) from stations) then 'мин.'
	end
from stations
where
	max_cars = (select max(max_cars) from stations) or
	max_cars = (select min(max_cars) from stations)
order by station_id