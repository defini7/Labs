select distinct
	station_id, car_type_id, wait_time_range, period_number,
	substring(wait_time_range from 'от ([0-9]+)')::int as wait_from,
	substring(wait_time_range from 'до ([0-9]+)')::int as wait_to
from dislocations
order by wait_to desc, period_number, station_id, car_type_id, wait_from, wait_time_range