select count(distinct station_id), avg(cars_count)
from dislocations
group by period_number
having abs(avg(cars_count) - max(cars_count)) <= 5
order by avg(cars_count) desc, period_number