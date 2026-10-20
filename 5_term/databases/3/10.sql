select
    order_id,
    cars_required,
    round(revenue_per_car_rub * cars_required, 2) as total_revenue_rub,
    round(
        (load_time_hours_per_car + unload_time_hours_per_car) * cars_required,
        2
    ) as total_handling_hours,
    round(
        (revenue_per_car_rub * cars_required)
        / nullif((load_time_hours_per_car + unload_time_hours_per_car) * cars_required, 0),
        2
    ) as revenue_per_hour,
    case
        when must_do is true then 'Обязательная'
        when escort_required is null then 'Уточнить сопровождение'
        else 'Обычная'
    end as priority_label
from orders
where canceled_at is null
  and (
     cars_required between 20 and 30 or
     cars_required in (70, 71)
  )
order by
    case
        when must_do is true then 1
        when escort_required is null then 2
        else 3
    end,
    revenue_per_hour desc nulls last,
    total_revenue_rub desc,
    order_id
limit 15