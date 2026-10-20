select station_id, station_name from stations
where station_name ~ '[^А-Яа-яЁё ]+' or station_name ~ '^[А-Яа-яЁё]{3}$'
order by station_name, station_id
offset 2 limit 20