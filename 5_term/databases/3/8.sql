select pass_id, order_id, birth_date, date_part('year', age('2026-01-01'::date, birth_date))::int as age_years
from order_controls
where
	birth_date is not null and
	birth_date <= '2026-01-01'::date and
	mod(order_id, 2) = 0 and
	length(pass_id) = 6 and
	mod(right(pass_id, 2)::int, 2) = 0 and
	mod(right(pass_id, 1)::int, 2) = 0
order by age_years desc, pass_id, order_id