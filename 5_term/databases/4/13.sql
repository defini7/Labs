drop table if exists persons_temp cascade;
drop table if exists order_controls_temp cascade;

create temporary table persons_temp (like persons including all);
insert into persons_temp select * from persons;

create temporary table order_controls_temp (like order_controls including all);
insert into order_controls_temp select * from order_controls;

alter table order_controls_temp
add constraint order_controls_fk
foreign key (pass_id)
references persons_temp (pass_id)
on update cascade
on delete set null;

insert into persons_temp
values ('тест1', 'тест2', 'тест3', 999998, 'м', null);

update order_controls_temp
set pass_id = '999998'
where order_id = 5;

select * from order_controls_temp where order_id = 5;

update persons_temp
set pass_id = '999997'
where pass_id = '999998';

select * from order_controls_temp where order_id = 5;

delete from persons_temp
where pass_id = '999997';

select * from order_controls_temp where order_id = 5;
