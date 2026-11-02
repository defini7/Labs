create temporary table repair_budget (
	budget_id bigint generated always as identity primary key,
	route_id bigint not null unique,
	limit_rub numeric(14, 2) not null default 10000 check (limit_rub >= 0)
);

insert into repair_budget (route_id)
values (3), (1), (2);

select * from repair_budget;
