select station_id, station_name from stations
where
	station_id like '%00%' and
	length(station_id) - length(replace(station_id, '0', '')) = 2
order by station_id