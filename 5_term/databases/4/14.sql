select trim(surname) from persons
where length(surname) > 0
group by surname
order by surname