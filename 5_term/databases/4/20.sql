drop table if exists orders_;

create temporary table orders_ (like orders including all);
insert into orders_ select * from orders;

delete from orders_ o
where
	canceled_at is null and
	not must_do and
	created_at::timestamp < '2025-01-01 00:00'::timestamp and
	not exists (
		select 1 from routes r
		where
			o.station_from_id = r.station_from_id and
			o.station_to_id = r.station_to_id)
returning order_id, canceled_at;

-- canceled_at будет иметь null?