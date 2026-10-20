drop table if exists data_1;
drop table if exists data_2;

create table data_1 (
    id int,
    some_num float,
    letter char
);

create table data_2 (
    id int,
    some_num float,
    letter char
);

copy data_1 (id, some_num, letter)
from '/Users/def1ni7/Programming/db_lab2/large_data/15gb.csv'
with (
    format csv,
    delimiter ',',
    encoding 'UTF8',
	header true
);

copy data_2 (id, some_num, letter)
from '/Users/def1ni7/Programming/db_lab2/large_data/15gb_2.csv'
with (
    format csv,
    delimiter ',',
    encoding 'UTF8',
	header true
);