alter table orders
add column total_revenue_rub numeric(20,2);

update orders
set total_revenue_rub = revenue_per_car_rub * cars_required;

alter table orders
rename column total_revenue_rub to order_revenue_rub;

alter table orders
alter column order_revenue_rub set not null;

alter table orders
drop column escort_required;

select order_id, order_revenue_rub
from orders
order by order_id;