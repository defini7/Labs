select station_id, station_name, max_cars from stations
where max_cars between 100 and 600 order by max_cars desc, station_id limit 12