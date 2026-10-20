select station_id, station_name, upper(station_name), length(station_name)
where length(station_name) >= 7, length(station_name) - length(replace(lower(station_name), 'а', '')) >= 2
order by name_length desc, station_id