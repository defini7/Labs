select
	order_id, must_do,
	(case escort_required
		when true then 'Нужно'
		when false then 'Не нужно'
		else 'Неизвестно'
	end) as escort_status,
	coalesce(canceled_at::text, 'Нет даты отмены') as cancellation_info
from orders
where must_do = true or escort_required is null
order by order_id