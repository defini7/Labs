drop table if exists route_repair_persons cascade;
drop table if exists route_repairs cascade;
drop table if exists order_controls cascade;
drop table if exists station_road_info cascade;
drop table if exists station_departments cascade;
drop table if exists station_roads cascade;
drop table if exists dislocations cascade;
drop table if exists orders cascade;
drop table if exists routes cascade;
drop table if exists persons cascade;
drop table if exists departments cascade;
drop table if exists roads cascade;
drop table if exists stations cascade;
drop table if exists car_types cascade;


create table car_types (
    car_type_id integer primary key,
    car_type_name varchar(100) not null,
    max_weight_tons decimal(10,2) not null
);


create table stations (
    station_id char(6) primary key,
    station_name varchar(255) not null,
    min_cars integer not null,
    max_cars integer not null
);


create table roads (
    road_id integer primary key,
    road_name varchar(255) not null
);


create table departments (
    department_id integer primary key,
    department_name varchar(255) not null
);


create table persons (
    surname varchar(100) not null,
    first_name varchar(100) not null,
    middle_name varchar(100),
    pass_id char(6) primary key,
    sex char(1),
    supervisor_id char(6)
);


create table routes (
    route_id bigint primary key,
    station_from_id char(6) not null,
    station_to_id char(6) not null,
    avg_cost_rub decimal(14,2) not null,
    max_cars integer,
    opening_date date not null,

    constraint routes_station_from_fk
        foreign key (station_from_id)
        references stations(station_id),

    constraint routes_station_to_fk
        foreign key (station_to_id)
        references stations(station_id)
);


create table orders (
    order_id bigint primary key,
    station_from_id char(6) not null,
    station_to_id char(6) not null,
    revenue_per_car_rub decimal(14,2) not null,
    cars_required integer not null,
    escort_required boolean,
    load_time_hours_per_car decimal(8,2) not null,
    unload_time_hours_per_car decimal(8,2) not null,
    must_do boolean not null,
    created_at timestamp not null,
    canceled_at timestamp,

    constraint orders_station_from_fk
        foreign key (station_from_id)
        references stations(station_id),

    constraint orders_station_to_fk
        foreign key (station_to_id)
        references stations(station_id)
);


create table dislocations (
    dislocation_id bigint primary key,
    station_id char(6) not null,
    is_loaded boolean,
    cars_count integer not null,
    car_type_id integer not null,
    period_number integer not null,
    wait_time_range varchar(50) not null,

    constraint dislocations_station_fk
        foreign key (station_id)
        references stations(station_id),

    constraint dislocations_car_type_fk
        foreign key (car_type_id)
        references car_types(car_type_id)
);


create table station_roads (
    station_id char(6) not null,
    road_id integer not null,

    primary key (station_id, road_id),

    constraint station_roads_station_fk
        foreign key (station_id)
        references stations(station_id),

    constraint station_roads_road_fk
        foreign key (road_id)
        references roads(road_id)
);


create table station_departments (
    station_id char(6) not null,
    department_id integer not null,

    primary key (station_id, department_id),

    constraint station_departments_station_fk
        foreign key (station_id)
        references stations(station_id),

    constraint station_departments_department_fk
        foreign key (department_id)
        references departments(department_id)
);


create table station_road_info (
    road_name varchar(255) not null,
    station_id char(6) primary key,

    constraint station_road_info_station_fk
        foreign key (station_id)
        references stations(station_id)
);


create table order_controls (
    birth_date date,
    address varchar(255),
    pass_id char(6) not null,
    order_id bigint not null,

    primary key (pass_id, order_id),

    constraint order_controls_person_fk
        foreign key (pass_id)
        references persons(pass_id)
);


create table route_repairs (
    repair_id bigint generated always as identity primary key,
    route_id bigint not null,
    price_rub decimal(14,2),
    person_ids TEXT[],
    start_period_number integer,

    constraint route_repairs_route_fk
        foreign key (route_id)
        references routes(route_id)
);


copy car_types (
    car_type_id,
    car_type_name,
    max_weight_tons
)
from '/Users/def1ni7/Downloads/db_lab2/car_types.csv'
with (
    format csv,
    header true,
    encoding 'UTF8'
);


copy stations (
    station_id,
    station_name,
    min_cars,
    max_cars
)
from '/Users/def1ni7/Downloads/db_lab2/stations.csv'
with (
    format csv,
    header true,
    encoding 'UTF8',
    DELIMITER ';'
);


copy roads (
    road_id,
    road_name
)
from '/Users/def1ni7/Downloads/db_lab2/roads.csv'
with (
    format csv,
    header true,
    encoding 'UTF8'
);


copy departments (
    department_id,
    department_name
)
from '/Users/def1ni7/Downloads/db_lab2/departments.csv'
with (
    format csv,
    header true,
    encoding 'UTF8'
);


copy persons (
    surname,
    first_name,
    middle_name,
    pass_id,
    sex,
    supervisor_id
)
from '/Users/def1ni7/Downloads/db_lab2/persons.csv'
with (
    format csv,
    header true,
    encoding 'UTF8'
);


copy routes (
    route_id,
    station_from_id,
    station_to_id,
    avg_cost_rub,
    max_cars,
    opening_date
)
from '/Users/def1ni7/Downloads/db_lab2/routes.csv'
with (
    format csv,
    header true,
    encoding 'UTF8'
);


copy orders (
    order_id,
    station_from_id,
    station_to_id,
    revenue_per_car_rub,
    cars_required,
    escort_required,
    load_time_hours_per_car,
    unload_time_hours_per_car,
    must_do,
    created_at,
    canceled_at
)
from '/Users/def1ni7/Downloads/db_lab2/orders.csv'
with (
    format csv,
    header true,
    encoding 'UTF8'
);


copy dislocations (
    dislocation_id,
    station_id,
    is_loaded,
    cars_count,
    car_type_id,
    period_number,
    wait_time_range
)
from '/Users/def1ni7/Downloads/db_lab2/dislocations.csv'
with (
    format csv,
    header true,
    encoding 'UTF8'
);


copy station_roads (
    station_id,
    road_id
)
from '/Users/def1ni7/Downloads/db_lab2/station_roads.csv'
with (
    format csv,
    header true,
    encoding 'UTF8'
);


copy station_departments (
    station_id,
    department_id
)
from '/Users/def1ni7/Downloads/db_lab2/station_departments.csv'
with (
    format csv,
    header true,
    encoding 'UTF8'
);


copy station_road_info (
    road_name,
    station_id
)
from '/Users/def1ni7/Downloads/db_lab2/station_road_info.csv'
with (
    format csv,
    header true,
    encoding 'UTF8'
);


copy order_controls (
    birth_date,
    address,
    pass_id,
    order_id
)
from '/Users/def1ni7/Downloads/db_lab2/order_controls.csv'
with (
    format csv,
    header true,
    encoding 'UTF8'
);


copy route_repairs (
    route_id,
    price_rub,
    person_ids,
    start_period_number
)
from '/Users/def1ni7/Downloads/db_lab2/route_repairs.csv'
with (
    format csv,
    header true,
    encoding 'UTF8'
);