select
	pass_id, order_id, address,
	trim(regexp_replace(address, '\s+', ' ', 'g')) as cleaned_address
from order_controls
where address like '%-%' or address like '%\_%'
order by cleaned_address, pass_id, order_id