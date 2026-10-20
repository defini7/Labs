select
	order_id,
	created_at::date as created_date,
	extract(year from created_at)::int as created_year,
	extract(month from created_at)::int as created_month,
	to_char(created_at, 'DD.MM.YYYY HH24:MI') as created_label
from orders
where created_at >= '2025-10-01 00:00'::timestamp and created_at < '2026-01-01 00:00'::timestamp
order by created_at, order_id