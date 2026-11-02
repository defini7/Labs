select 
    s.station_id,
    s.station_name,
    (select count(*) 
     from orders o 
     where o.station_from_id = s.station_id 
       and o.must_do = true 
       and o.canceled_at is null 
       and exists (
           select 1 from routes r 
           where r.station_from_id = o.station_from_id 
             and r.station_to_id = o.station_to_id 
             and r.max_cars >= o.cars_required
       )
    ) as required_orders_count,
    
    (select sum(o.cars_required) 
     from orders o 
     where o.station_from_id = s.station_id 
       and o.must_do = true 
       and o.canceled_at is null 
       and exists (
           select 1 from routes r 
           where r.station_from_id = o.station_from_id 
             and r.station_to_id = o.station_to_id 
             and r.max_cars >= o.cars_required
       )
    ) as total_cars_required

from stations s
where exists (
    select 1 
    from orders o 
    where o.station_from_id = s.station_id 
      and o.must_do = true 
      and o.canceled_at is null 
      and exists (
          select 1 from routes r 
          where r.station_from_id = o.station_from_id 
            and r.station_to_id = o.station_to_id 
            and r.max_cars >= o.cars_required
      )
)
order by 
    total_cars_required desc, 
    s.station_id asc;