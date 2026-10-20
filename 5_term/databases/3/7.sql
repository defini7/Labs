--select * from persons where pass_id = '243038'

select
	pass_id,
	(
		case lower(sex)
			when 'м' then 'Мужчина: '
			when 'ж' then 'Женщина: '
			else 'Пол неизвестен: '
		end
	) || left(first_name, 1) || '.' ||
	coalesce(left(middle_name, 1) || '. ', ' ') || surname
from persons
where surname ilike '%ян' and surname not ilike '%с%'
order by surname, first_name, middle_name, pass_id nulls last