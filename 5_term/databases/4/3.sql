--create table dislocations_copy
--as select * from dislocations

--delete from dislocations_copy where dislocation_id = 688;

/*create sequence dislocations_copy_id_seq owned by dislocations_copy.dislocation_id;

alter table dislocations_copy
	alter column dislocation_id set default nextval('dislocations_copy_id_seq');

select setval(
  'dislocations_copy_id_seq',
  coalesce((select max(dislocation_id) from dislocations_copy), 0) + 1,
  false
);*/

insert into
	dislocations_copy (
		station_id, is_loaded, cars_count, car_type_id,
		period_number, wait_time_range)
values
	(971201, false, 1, 1, 1, 'от 0 до 7'),
	(921202, true, 1, 1, 1, 'от 0 до 6'),
	(843408, true, 1, 1, 1, 'от 0 до 6'),
	(843408, true, 1, 1, 1, 'от 0 до 6')
returning
	dislocation_id