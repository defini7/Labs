select station_to_id, (select station_name from stations s where s.station_id = station_to_id)
from orders
group by station_to_id
having min(case when canceled_at is null then revenue_per_car_rub end) > 7200
order by station_to_id::int