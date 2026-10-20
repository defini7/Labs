select * from stations
where left(station_id, 1) = right(station_id, 1)
order by station_id