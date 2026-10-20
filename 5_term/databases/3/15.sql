select distinct
	route_id, station_from_id, station_to_id, opening_date, avg_cost_rub, max_cars,
	date_trunc('month', opening_date)::date as opening_month,
	(date_trunc('month', opening_date) + '3 months'::interval)::date as review_date,
	'2026-01-01'::date - opening_date as days_open
from routes
where avg_cost_rub > 0 and opening_date >= '2025-04-01'::date and opening_date <= '2025-06-30'::date
order by
	opening_date nulls last,
	avg_cost_rub desc nulls last,
	route_id nulls last,
	station_from_id nulls last,
	station_to_id nulls last,
	max_cars nulls last
limit 10