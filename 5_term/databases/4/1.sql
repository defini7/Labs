select
	min(avg_cost_rub) as min_cost,
	max(avg_cost_rub) as max_cost,
	sum(avg_cost_rub) as sum_cost,
	avg(avg_cost_rub) as avg_cost,
	count(*) filter (where route_id::text ~ '(.).*\1') as count_cost
from routes
where route_id between 10001 and 20000