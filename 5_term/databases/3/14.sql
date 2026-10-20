select
	order_id, created_at, canceled_at,
	(canceled_at - created_at) as lifetime,
	round(extract(epoch from (canceled_at - created_at)) / 3600, 2) as lifetime_hours
from orders
where canceled_at - created_at >= '6 hours'::interval
order by lifetime desc, order_id
limit 15