select
	period_number, station_id,
	avg(case when is_loaded then cars_count end) as avg_loaded,
	avg(case when not is_loaded then cars_count end) as avg_not_loaded,
	avg(case when is_loaded then cars_count end) + avg(case when not is_loaded then cars_count end) as avg_sum
from dislocations
where station_id like '%1%1%'
group by station_id, period_number
having
	avg(case when is_loaded then cars_count end) + avg(case when not is_loaded then cars_count end) is not null and
	avg(case when is_loaded then cars_count end) + avg(case when not is_loaded then cars_count end) <> 0
order by
	period_number desc, station_id