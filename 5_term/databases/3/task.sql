select pass_id, trim(first_name) || ' ' || trim(surname) as full_name
from persons
where
	surname ilike 'а%' and
	(middle_name ~ '^\s*$' or middle_name is null)
order by surname, first_name, pass_id nulls last
